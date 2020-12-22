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
Functions used by the console script
"""

import argparse
import logging
import logging.handlers
import os
import sys

import evdev

import evmapy.controller
import evmapy.multiplexer
import evmapy.util


def initialize_logging(appname, debug):
    """
    Create and configure a logger used throughout the application.

    :param appname: application name to use for the logger
    :type appname: str
    :param debug: whether to enable debug output or not
    :type debug: bool
    :returns: configured logger
    :rtype: :py:class:`logging.Logger`
    """
    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG if debug else logging.INFO)
    if os.isatty(sys.stdout.fileno()):
        stdout = logging.StreamHandler(stream=sys.stdout)
        if debug:
            formatter = logging.Formatter('%(created)f: %(message)s')
            stdout.setFormatter(formatter)
        logger.addHandler(stdout)
    else:
        syslog = logging.handlers.SysLogHandler(
            address='/dev/log',
            facility=logging.handlers.SysLogHandler.LOG_DAEMON,
        )
        name = '%s[%d]' % (appname, os.getpid())
        formatter = logging.Formatter(name + ': %(message)s')
        syslog.setFormatter(formatter)
        logger.addHandler(syslog)
    return logger


def main(argv=sys.argv[1:]):
    """
    Parse command line arguments and act accordingly.

    :param argv: command line arguments
    :type argv: list
    :returns: application exit code
    :rtype: int
    """
    info = evmapy.util.get_app_info()
    parser = argparse.ArgumentParser(prog=info['name'])
    group = parser.add_mutually_exclusive_group()
    group.add_argument("-L", "--list-all", action='store_true',
                       help="list available devices")
    group.add_argument("-l", "--list", action='store_true',
                       help="list currently handled devices")
    group.add_argument("-G", "--generate", metavar="DEVICE",
                       help="generate a sample configuration for DEVICE")
    group.add_argument("-g", "--generate-minimal", metavar="DEVICE",
                       help="generate a minimal configuration for DEVICE")
    group.add_argument("-c", "--configure", metavar="DEVICE:FILE",
                       help="load DEVICE configuration from FILE")
    group.add_argument("-D", "--debug", action='store_true',
                       help="run in debug mode")
    args = parser.parse_args(argv)
    if args.list_all:
        for dev_path in evdev.list_devices():
            device = evdev.InputDevice(dev_path)
            print("%s: %s" % (device.fn, device.name))
    elif args.list:
        devices = evmapy.controller.perform_request({
            'command':  'list',
            'wait':     True,
        })
        for device in devices:
            print("%(path)s: %(name)s" % device)
    elif args.generate:
        exit(evmapy.config.create(args.generate))
    elif args.generate_minimal:
        exit(evmapy.config.create(args.generate_minimal, with_actions=False))
    elif args.configure:
        try:
            (dev_path, config_file) = args.configure.split(':')
        except ValueError:
            exit("Bad --configure argument syntax")
        evmapy.controller.perform_request({
            'command':  'config',
            'device':   dev_path,
            'file':     config_file,
            'wait':     False,
        })
    else:
        info = evmapy.util.get_app_info()
        logger = initialize_logging(info['name'], args.debug)
        logger.info("%s %s initializing", info['name'], info['version'])
        logger.info("running as user %s", info['user'].pw_name)
        logger.info("using configuration directory %s", info['config_dir'])
        evmapy.multiplexer.Multiplexer().run()


if __name__ == "__main__":  # pragma: no cover
    main()
