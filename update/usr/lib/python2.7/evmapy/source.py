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
:py:class:`Source` class implementation
"""

import errno
import logging

import evdev

import evmapy.config
import evmapy.util


class DeviceRemovedException(Exception):
    """
    Exception raised when the associated input device gets disconnected.
    """
    pass


class Source(object):

    """
    Class encapsulating an :py:class:`evdev.InputDevice` instance which
    translates the events emitted by it to a list of actions to be
    performed by a :py:class:`evmapy.multiplexer.Multiplexer`.

    :param device: input device to use
    :type device: evdev.InputDevice
    """

    def __init__(self, device):
        self.device = {
            'fd':   device.fd,
            'name': device.name,
            'path': device.fn,
        }
        self._device = device
        self._config = {}
        self._raw_config = None
        self._grabbed = False
        self._event_history = [None, None]
        self._logger = logging.getLogger()
        self.load_config()

    def load_config(self, name=None):
        """
        Load configuration from the given path.

        :param name: name of the configuration file to load (`None`
            and `''` cause the default configuration file to be used)
        :type name: str
        :returns: None
        :raises evmapy.config.ConfigError: if an error occurred while
            loading the specified configuration file
        """
        (self._config, self._raw_config) = evmapy.config.load(
            self._device, name, self._raw_config
        )
        if self._config['grab'] is True and self._grabbed is False:
            self._device.grab()
            self._grabbed = True
            self._logger.info("%s: device grabbed", self.device['path'])
        elif self._config['grab'] is False and self._grabbed is True:
            self._device.ungrab()
            self._grabbed = False
            self._logger.info("%s: device ungrabbed", self.device['path'])

    def process(self):
        """
        Translate input events into actions to be performed.

        :returns: list of actions to be performed
        :rtype: list
        """
        pending = []
        for event in self._pending_events():
            self._logger.debug(event)
            supported_events = [
                evdev.ecodes.ecodes['EV_ABS'],
                evdev.ecodes.ecodes['EV_KEY'],
            ]
            if event.type not in supported_events:
                continue
            (event_name, event_active, event_infos) = self._normalize_event(event)
            if not event_name:
                continue
            if event_active:
                self._event_history[0] = self._event_history[1]
                self._event_history[1] = event_name
            for action in self._config['map'][event.code]:
                pending.extend(
                    self._process_action(action, event_name, event_active, event_infos)
                )
        return pending

    def _pending_events(self):
        """
        Return a generator yielding pending input events and raising an
        exception if the device is no longer available.

        :returns: generator yielding pending input events
        :rtype: generator
        :raises DeviceRemovedException: when the input device is no
            longer available
        """
        try:
            for event in self._device.read():
                yield event
        except OSError as exc:
            if exc.errno == errno.ENODEV:
                raise DeviceRemovedException()
            else:
                raise

    def _normalize_event(self, event):
        """
        Translate an event structure into a tuple containing the
        normalized name of the event and its new state (active or not).

        :param event: event to process
        :type event: evdev.events.InputEvent
        :returns: normalized event name and event state
        :rtype: tuple
        """
        retval = (None, None, None)
        try:
            event_info = self._config['events'][event.code]
        except KeyError:
            return retval
        name = event_info['name']
        previous = event_info['previous']
        current = event.value
        if 'min' in event_info and 'max' in event_info:
            # Axis event
            minimum = event_info['min']
            maximum = event_info['max']
            axisval = (event.value - (minimum + maximum)/2.0) / (maximum - (minimum + maximum)/2.0) # percentage of avancement
            if previous > minimum and current <= minimum:
                retval = (name + ':min', True, axisval)
            elif previous <= minimum and current > minimum:
                retval = (name + ':min', False, axisval)
            elif previous < maximum and current >= maximum:
                retval = (name + ':max', True, axisval)
            elif previous >= maximum and current < maximum:
                retval = (name + ':max', False, axisval)
            else:
                retval = (name + ':val', True, axisval)
        else:
            # Button event
            if current == evdev.KeyEvent.key_hold:
                return retval
            elif current > previous:
                retval = (name, True, None)
            else:
                retval = (name, False, None)
        event_info['previous'] = current
        return retval

    def _process_action(self, action, event_name, event_active, event_infos):
        """
        Process the given event in the context of the given action.

        :param action: action in the context of which the given event
            should be processed
        :type action: dict
        :param event_name: normalized name of the event to be processed
        :type event_name: str
        :param event_active: whether the event is active or not
        :type event_active: bool
        :returns: list of actions to be performed
        :rtype: list
        """
        retval = []
        try:
            event_index = action['trigger'].index(event_name)
        except ValueError:
            # event is ':min' but we're looking for ':max' or vice versa
            return retval
        if not action['mode'] == 'sequence':
            if event_active:
                action['trigger_active'][event_index] = True
                if action['mode'] == 'any' or all(action['trigger_active']):
                    retval.append((action, True, event_infos))
            else:
                if action['mode'] == 'any' or all(action['trigger_active']):
                    retval.append((action, False, event_infos))
                action['trigger_active'][event_index] = False
        else:
            sequence = action['trigger']
            current = action['sequence_cur']
            if event_active:
                if (event_name == sequence[current] and
                        self._event_history[0] == sequence[current-1]):
                    action['sequence_cur'] += 1
                    if action['sequence_cur'] == len(sequence):
                        retval.append((action, True, event_infos))
                        action['sequence_cur'] = 1
                        action['sequence_done'] = True
                        self._event_history[1] = None
                else:
                    action['sequence_cur'] = 1
            else:
                if action['sequence_done'] and event_name == sequence[-1]:
                    retval.append((action, False, event_infos))
                    action['sequence_done'] = False
        return retval
