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
Functions handling configuration generation, saving and loading
"""

import copy
import json
import logging
import os
import re

import evdev

import evmapy.util


class ConfigError(Exception):

    """
    Exception thrown when an error occurs when trying to load a device
    configuration file.

    :param path: path to the configuration file which caused the error
    :type path: str
    :param reason: last raised exception
    :type reason: Exception
    """

    def __init__(self, reason, path=None):
        super(Exception, self).__init__()
        self.path = path
        self.not_found = False
        if isinstance(reason, ConfigError):
            self.error = reason.error
        elif isinstance(reason, ValueError):
            self.error = "Invalid JSON file: %s" % str(reason)
        else:
            self.error = str(reason)

    def __str__(self):
        return "%s: %s" % (self.path, self.error)


def _get_device_config_path(device):
    """
    Return the path to the default configuration file for the given
    input device.

    :param device: input device to get the default configuration file
        path for
    :type device: evdev.InputDevice
    :returns: path to the default configuration file for the given input
        device
    :rtype: str
    """
    info = evmapy.util.get_app_info()
    config_filename = os.path.basename(device.fn) + '.json'
    return os.path.join(info['config_dir'], config_filename)


def create(dev_path, with_actions=True):
    """
    Generate and save a default configuration file for the input device
    under the given path.

    :param dev_path: path to the device to create configuration for
    :type dev_path: str
    :param with_actions: whether to include default actions in the
        configuration created
    :type with_actions: bool
    :returns: nothing on success, error string otherwise
    :rtype: None or str
    """
    try:
        device = evdev.InputDevice(dev_path)
    except FileNotFoundError:
        return "No such device %s" % dev_path
    config_path = _get_device_config_path(device)
    if os.path.exists(config_path):
        return "%s already exists, not overwriting" % config_path
    config = generate(device)
    if not with_actions:
        config['actions'] = []
    save(config_path, config)


def generate(device):
    """
    Generate a default configuration dictionary for a given input
    device.

    :param device: device to generate configuration for
    :type device: evdev.InputDevice
    :returns: default configuration dictionary
    :rtype: dict
    """

    config = evmapy.util.ordered_dict([
        ('actions', []),
        ('grab', False),
        ('axes', []),
        ('buttons', []),
    ])
    capabilities = device.capabilities(verbose=True, absinfo=True)
    for ((_, event_type_id), events) in capabilities.items():
        for (event_names, activator) in events:
            event_name = evmapy.util.first_element(event_names)
            action_base = evmapy.util.ordered_dict([
                ('trigger', None),
                ('type', 'exec'),
                ('target', 'echo %s' % event_name),
            ])
            if event_type_id == evdev.ecodes.ecodes['EV_KEY']:
                config['buttons'].append(evmapy.util.ordered_dict([
                    ('name', event_name),
                    ('code', activator),
                ]))
                action = action_base.copy()
                action['trigger'] = event_name
                config['actions'].append(action)
            elif event_type_id == evdev.ecodes.ecodes['EV_ABS']:
                config['axes'].append(evmapy.util.ordered_dict([
                    ('name', event_name),
                    ('code', event_names[1]),
                    ('min', activator.min),
                    ('max', activator.max),
                ]))
                for limit in ('min', 'max'):
                    action = action_base.copy()
                    action['trigger'] = '%s:%s' % (event_name, limit)
                    action['target'] += ' %s' % limit
                    config['actions'].append(action)
    return config


def save(path, config):
    """
    Save provided configuration under the given path, creating the
    configuration directory if necesary.

    :param path: path to save configuration under
    :type path: str
    :param config: configuration dictionary to save
    :type config: dict
    :returns: None
    """
    try:
        info = evmapy.util.get_app_info()
        os.mkdir(info['config_dir'])
    except FileExistsError:
        pass
    with open(path, 'w') as config_file:
        json.dump(config, config_file, indent=4)


def load(device, name, old_config=None):
    """
    Load configuration for the given device.

    :param device: device to load configuration for
    :type device: evdev.InputDevice
    :param name: name of the configuration file to load (`None` and `''`
        cause the default configuration file to be used)
    :type name: str
    :param old_config: configuration dictionary returned by the previous
        `read()` call
    :type old_config: dict
    :returns: *(config, raw)* tuple, where *config* is the processed
        configuration from the loaded configuration file and *raw* is
        the configuration dictionary represented by the loaded
        configuration file (possibly with some keys inherited from the
        previously loaded configuration dictionary)
    :rtype: tuple
    :raises evmapy.config.ConfigError: if an error occurred while
        loading the specified configuration file
    """
    if name:
        info = evmapy.util.get_app_info()
        path = os.path.join(info['config_dir'], os.path.basename(name))
    else:
        path = _get_device_config_path(device)
    try:
        config_input = read(path)
        if old_config:
            for inheritable in ('axes', 'buttons'):
                if inheritable not in config_input:
                    config_input[inheritable] = old_config[inheritable]
        config = parse(config_input)
    except Exception as exc:
        raise ConfigError(exc, path)
    logging.getLogger().info("%s: loaded %s", device.fn, path)
    return (config, config_input)


def read(path):
    """
    Read configuration file under the given path and return the
    dictionary it represents.

    :param path: path to the file to read
    :type path: str
    :returns: configuration dictionary represented by the given file
    :rtype: dict
    """
    with open(path) as config_file:
        config_input = json.load(config_file)
    return config_input


def parse(config_input):
    """
    Transform the given configuration dictionary into one ready to use
    by the application.

    :param config_input: configuration dictionary to process
    :type config_input: dict
    :returns: processed configuration dictionary
    :rtype: dict
    :raises evmapy.config.ConfigError: when an error is found while
        processing the configuration
    """
    config_input_copy = copy.deepcopy(config_input)
    validate_parameters(config_input_copy)
    config = {
        'events':   {},
        'grab':     config_input_copy['grab'],
        'map':      {},
    }
    defaults = {
        'hold':     0.0,
        'mode':     'all',
    }
    # Every action needs a unique identifier in order for the event
    # multiplexer to be able to remove it from the list of delayed
    # actions; note that we can't directly compare the dictionaries as
    # there may be identical actions configured for two different events
    current_id = 0
    events = config_input_copy['axes'] + config_input_copy['buttons']
    validate_events(events)
    for event in events:
        try:
            # Axis event
            idle = (event['min'] + event['max']) // 2
        except KeyError:
            # Button event
            idle = 0
        event['previous'] = idle
        config['events'][event['code']] = event
        config['map'][event['code']] = []
    for action in config_input_copy['actions']:
        for (parameter, default) in defaults.items():
            if parameter not in action:
                action[parameter] = default
        action['trigger'] = evmapy.util.as_list(action['trigger'])
        action['trigger_active'] = [False for trigger in action['trigger']]
        action['sequence_cur'] = 1
        action['sequence_done'] = False
        validate_action(action)
        for trigger in action['trigger']:
            try:
                # Axis event
                (event_name, suffix) = trigger.split(':', 1)
            except ValueError:
                # Button event
                event_name = trigger
                suffix = None
            try:
                event = next(e for e in events if e['name'] == event_name)
            except StopIteration:
                raise ConfigError("unknown event '%s'" % event_name)
            if suffix and suffix not in event and suffix != "val":
                raise ConfigError("invalid event suffix '%s'" % suffix)
            if action not in config['map'][event['code']]:
                config['map'][event['code']].append(action)
        action['id'] = current_id
        current_id += 1
    return config


def validate_parameters(config):
    """
    Perform some checks on the keys and types of values found in the
    configuration dictionary.

    :param config: configuration dictionary read from configuration file
    :type config: dict
    :returns: None
    :raises evmapy.config.ConfigError: when an error is detected
    """
    level_names = evmapy.util.ordered_dict([
        ('top', 'top-level'),
        ('actions', 'action'),
        ('axes', 'axis'),
        ('buttons', 'button'),
    ])
    required = {
        'top': [
            ('actions', list),
            ('axes', list),
            ('buttons', list),
            ('grab', bool),
        ],
        'actions': [
            ('target', [str, list]),
            ('trigger', [str, list]),
            ('type', str),
        ],
        'axes': [
            ('code', int),
            ('min', int),
            ('max', int),
            ('name', str),
        ],
        'buttons': [
            ('code', int),
            ('name', str),
        ],
    }
    optional = {
        'top':      [],
        'actions':  [
            ('hold', [float, int]),
            ('mode', str),
        ],
        'axes':     [],
        'buttons':  [],
    }
    config_copy = config.copy()
    config_copy['top'] = [config]
    for (key, level) in level_names.items():
        valid = dict(required[key] + optional[key])
        for obj in config_copy[key]:
            for (param, _) in required[key]:
                if param not in obj:
                    raise ConfigError(
                        "required %s parameter '%s' not set" % (level, param)
                    )
            for param in obj:
                if param not in valid:
                    raise ConfigError(
                        "unknown %s parameter '%s'" % (level, param)
                    )
                valid_types = evmapy.util.as_list(valid[param])
                #valid_type_names = [t.__name__ for t in valid_types]
                #if type(obj[param]).__name__ not in valid_type_names:
                #    raise ConfigError(
                #        "'%s' has to be of type %s" % (
                #            param, " or ".join(valid_type_names)
                #        )
                #    )


def validate_events(events):
    """
    Check a list of events for duplicates.

    :param events: list of events to check
    :type events: list
    :returns: None
    :raises evmapy.config.ConfigError: when a duplicate event is found
    """
    unique = {
        'name': [],
        'code': [],
    }
    for event in events:
        for key in unique:
            if event[key] in unique[key]:
                raise ConfigError(
                    "duplicate event %s '%s'" % (key, event[key])
                )
            else:
                unique[key].append(event[key])


def validate_action(action):
    """
    Perform some error checks on an action.

    :param action: action to check
    :type action: dict
    :returns: None
    :raises evmapy.config.ConfigError: when an error is detected
    """
    hold = action['hold']
    trigger = action['trigger']
    target = evmapy.util.as_list(action['target'])
    if action['type'] not in ('exec', 'key', 'mouse'):
        raise ConfigError("invalid action type '%s'" % action['type'])
    if action['mode'] not in ('all', 'any', 'sequence'):
        raise ConfigError("invalid action mode '%s'" % action['mode'])
    if hold < 0:
        raise ConfigError("hold time cannot be negative")
    if action['type'] == 'key':
        for key in target:
            if key not in evdev.ecodes.ecodes:
                raise ConfigError("unknown key '%s'" % key)
        if len(set(target)) != len(target):
            raise ConfigError("duplicate event(s) in action target")
    if action['mode'] == 'sequence':
        if hold > 0:
            raise ConfigError("hold time cannot be positive for sequences")
        if len(trigger) < 2:
            raise ConfigError("sequence must contain more than 1 event")
    else:
        if len(set(trigger)) != len(trigger):
            raise ConfigError("duplicate event(s) in action trigger")
