#
# Copyright (C) 2015 Michal Kepien <github@kempniu.pl>
#
# This file is part of evmapy.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA

"""
:py:class:`Controller` class implementation
"""

import json
import logging
import os
import select
import socket
import stat

import evmapy.util


class SocketInUseError(Exception):
    """
    Exception raised when another instance of the program is already
    running.
    """
    pass


def _get_control_socket_path():
    """
    Return the path to the control socket.

    :returns: path to the control socket
    :rtype: str
    """
    info = evmapy.util.get_app_info()
    return os.path.join(info['config_dir'], '%s.socket' % info['name'])


def send_request(request):
    """
    Send the given request to the control socket and wait for a response
    if desired.

    :param request: request to send
    :type request: dict
    :returns: if desired, response to request
    :rtype: None or dict
    :raises ConnectionRefusedError: when no process is bound to the
        control socket
    :raises FileNotFoundError: when the control socket doesn't exist
    :raises TimeoutError: if no response is received from the control
        socket within 1 second
    """
    info = evmapy.util.get_app_info()
    client_socket_name = '%s-client.%d.socket' % (info['name'], os.getpid())
    client_socket_path = os.path.join(info['config_dir'], client_socket_name)
    try:
        client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)
        client_socket.bind(client_socket_path)
        os.chmod(client_socket_path, stat.S_IRUSR | stat.S_IWUSR)
        request_data = json.dumps(request).encode()
        client_socket.sendto(request_data, _get_control_socket_path())
        if request['wait']:
            (read_fds, _, _) = select.select([client_socket], [], [], 1.0)
            if read_fds:
                data = client_socket.recv(1024)
                return json.loads(data.decode())
            else:
                raise TimeoutError
    finally:
        os.remove(client_socket_path)


def perform_request(request):
    """
    Send the given request to the control socket and wait for a response
    if desired, exiting if an exception is raised.

    :param request: request to send
    :type request: dict
    :returns: if desired, response to request
    :rtype: None or dict
    """
    info = evmapy.util.get_app_info()
    try:
        return send_request(request)
    except (ConnectionRefusedError, FileNotFoundError):
        exit("No %s instance is running as %s" % (
            info['name'], info['user'].pw_name
        ))
    except TimeoutError:
        exit("Timeout waiting for a response from %s" % info['name'])


class Controller(object):

    """
    Class responsible for dynamically changing the behavior of a given
    :py:class:`evmapy.multiplexer.Multiplexer` by processing requests
    sent to a Unix domain socket.

    :param target: multiplexer to control
    :type target: evmapy.multiplexer.Multiplexer
    """

    def __init__(self, target):
        self._logger = logging.getLogger()
        self._target = target
        try:
            control_socket_path = _get_control_socket_path()
            os.mkdir(os.path.dirname(control_socket_path))
        except:
            pass
        try:
            send_request({
                'command':  'list',
                'wait':     True,
            })
            raise SocketInUseError
        except:
            try:
                self._logger.info("removing stale control socket")
                os.remove(control_socket_path)
            except:
                pass
        control_socket = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)
        control_socket.bind(control_socket_path)
        os.chmod(control_socket_path, stat.S_IRUSR | stat.S_IWUSR)
        self._socket = control_socket

    def fileno(self):
        """
        Return the control socket's file descriptor. This enables a
        :py:class:`Controller` instance to be used directly with
        :py:meth:`select.poll.poll()` and :py:func:`select.select()`.

        :returns: control socket's file descriptor
        :rtype: int
        """
        return self._socket.fileno()

    def process(self):
        """
        Read and process the request sent to the control socket.

        :returns: an empty list (to signal that no actions should be
            performed)
        :rtype: list
        """
        try:
            (data, peer) = self._socket.recvfrom(1024)
            request = json.loads(data.decode())
            command = request['command']
            method = getattr(self, 'do_' + command)
            try:
                result = method(request)
                if result is not None:
                    self._send_response(result, peer)
            except KeyError as exc:
                self._logger.error(
                    "missing parameter for command '%s': '%s'",
                    command, exc.args[0]
                )
        except ValueError:
            self._logger.error("invalid control request received")
        except KeyError:
            self._logger.error("no control command specified")
        except AttributeError:
            self._logger.error("unknown control command '%s'", command)
        return []

    def _send_response(self, result, peer):
        """
        Send the result of the request to the peer who sent the latter.

        :param result: result of the request issued by the peer
        :type result: dict
        :param peer: path to peer socket
        :type peer: str
        :returns: None
        """
        try:
            response = json.dumps(result).encode()
            self._socket.sendto(response, peer)
        except (ConnectionRefusedError, FileNotFoundError, PermissionError,
                TypeError):
            pass

    def cleanup(self):
        """
        Close the control socket and remove it from the filesystem.

        :returns: None
        """
        self._socket.close()
        os.remove(_get_control_socket_path())

    def do_config(self, request):
        """
        Load configuration for the given input device from the specified
        file.

        :param request: request issued by peer
        :type request: dict
        :returns: None
        """
        try:
            config_file = request['file']
        except KeyError:
            config_file = None
        self._target.load_device_config(request['device'], config_file)
        return None

    def do_list(self, _):
        """
        Return the list of currently handled devices.

        :returns: list of currently handled devices
        :rtype: list
        """
        devices = []
        for source in self._target.devices:
            devices.append({
                'name': source.device['name'],
                'path': source.device['path'],
            })
        return devices
