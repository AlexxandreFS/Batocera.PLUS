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
Various helper functions used by other modules
"""

import collections
import os
import pwd


def as_list(var):
    """
    Return a one-element list containing `var` or `var` itself if it is
    already a list.

    :param var: variable to process
    :returns: processed variable
    :rtype: list
    """
    return [var] if not isinstance(var, list) else var


def first_element(var):
    """
    Return the first element of `var` or `var` itself if it is neither a
    list nor a tuple.

    :param var: variable to process
    :returns: first element of variable or variable itself
    """
    if isinstance(var, list) or isinstance(var, tuple):
        return var[0]
    else:
        return var


def get_app_info():
    """
    Return a dictionary of frequently used application information.

    :returns: frequently used application information
    :rtype: dict
    """
    info = {
        'name':     'evmapy',
        'version':  '1.0',
        'user':     pwd.getpwuid(os.geteuid()),
    }
    info['config_dir'] = "/var/run/evmapy"
    return info


def ordered_dict(data):
    """
    Generate a :py:class:`collections.OrderedDict` out of a list of
    tuples.

    :param data: list of *(key, value)* tuples
    :type data: list
    :returns: ordered dictionary generated out of passed data
    :rtype: collections.OrderedDict
    """
    retval = collections.OrderedDict()
    for (key, value) in data:
        retval[key] = value
    return retval
