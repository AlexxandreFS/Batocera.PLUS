###########################################################################
#   makefile - XJOYPAD Makefile  V0.01                                    #
###########################################################################
# Copyright (C) 2002 ITEK Ing. Erich Kitzmüller                           #
###########################################################################
# This program is free software; you can redistribute it and/or modify    #
# it under the terms of the GNU General Public License as published by    #
# the Free Software Foundation; either version 2 of the License, or       #
# (at your option) any later version.                                     #
#                                                                         #
# This program is distributed in the hope that it will be useful,         #
# but WITHOUT ANY WARRANTY; without even the implied warranty of          #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
# GNU General Public License for more details.                            #
#                                                                         #
# You should have received a copy of the GNU General Public License       #
# along with tis program; if not, write to the Free Software              #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston MA  02111-1307 USA #
###########################################################################
#xjoypad: sendevent.c xjoypad.c
#	cc -o xjoypad xjoypad.c sendevent.c /usr/X11R6/lib/libX11.a

xjoypad: sendevent.c xjoypad.c
	cc -o xjoypad -lX11 sendevent.c xjoypad.c

