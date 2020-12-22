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
:py:class:`Multiplexer` class implementation
"""

import logging
import os
import select
import signal
import time

import evdev
import json

import evmapy.config
import evmapy.controller
import evmapy.source
import evmapy.util
from evdev import ecodes

class SIGHUPReceivedException(Exception):
    """
    Exception raised when a SIGHUP signal is received.
    """
    pass


class SIGTERMReceivedException(Exception):
    """
    Exception raised when a SIGTERM signal is received.
    """
    pass


class Multiplexer(object):

    """
    Class monitoring input device file descriptors and the control
    socket for incoming data. Whenever any of these is ready for
    reading, its associated object (:py:class:`evmapy.source.Source` or
    :py:class:`evmapy.controller.Controller` instance, respectively) is
    asked to process pending data. If the result of this processing in
    an action list, these actions are then performed.
    """

    def __init__(self):
        self._fds = {}
        self._delayed = []
        self._logger = logging.getLogger()
        self._poll = None
        self._uinput = None
        self._mousePosition = { "x": 0, "y": 0, "last": time.time(), "every": 0.006, "deadzone": 0.05, "speed": 4.0 }
        global_config_filepath = "/etc/evmapy.json"
        # { "mouse_config": { "every": 0.005, "deadzone": 0.06 } }
        if os.path.exists(global_config_filepath):
            with open(global_config_filepath) as config_file:
                global_config = json.load(config_file)
                if "mouse_config" in global_config:
                    for key in ["every", "deadzone", "speed"]:
                        if key in global_config["mouse_config"]:
                            self._mousePosition[key] =  global_config["mouse_config"][key]

        valid_events={
            ecodes.EV_REL: [
            evdev.ecodes.REL_X,
            evdev.ecodes.REL_Y,
            evdev.ecodes.REL_WHEEL
            ],
            ecodes.EV_KEY: [
            evdev.ecodes.BTN_LEFT,
            evdev.ecodes.BTN_RIGHT,
            evdev.ecodes.BTN_MIDDLE,
            evdev.ecodes.KEY_ESC,
            evdev.ecodes.KEY_1,
            evdev.ecodes.KEY_2,
            evdev.ecodes.KEY_3,
            evdev.ecodes.KEY_4,
            evdev.ecodes.KEY_5,
            evdev.ecodes.KEY_6,
            evdev.ecodes.KEY_7,
            evdev.ecodes.KEY_8,
            evdev.ecodes.KEY_9,
            evdev.ecodes.KEY_0,
            evdev.ecodes.KEY_MINUS,
            evdev.ecodes.KEY_EQUAL,
            evdev.ecodes.KEY_BACKSPACE,
            evdev.ecodes.KEY_TAB,
            evdev.ecodes.KEY_Q,
            evdev.ecodes.KEY_W,
            evdev.ecodes.KEY_E,
            evdev.ecodes.KEY_R,
            evdev.ecodes.KEY_T,
            evdev.ecodes.KEY_Y,
            evdev.ecodes.KEY_U,
            evdev.ecodes.KEY_I,
            evdev.ecodes.KEY_O,
            evdev.ecodes.KEY_P,
            evdev.ecodes.KEY_LEFTBRACE,
            evdev.ecodes.KEY_RIGHTBRACE,
            evdev.ecodes.KEY_ENTER,
            evdev.ecodes.KEY_LEFTCTRL,
            evdev.ecodes.KEY_A,
            evdev.ecodes.KEY_S,
            evdev.ecodes.KEY_D,
            evdev.ecodes.KEY_F,
            evdev.ecodes.KEY_G,
            evdev.ecodes.KEY_H,
            evdev.ecodes.KEY_J,
            evdev.ecodes.KEY_K,
            evdev.ecodes.KEY_L,
            evdev.ecodes.KEY_SEMICOLON,
            evdev.ecodes.KEY_APOSTROPHE,
            evdev.ecodes.KEY_GRAVE,
            evdev.ecodes.KEY_LEFTSHIFT,
            evdev.ecodes.KEY_BACKSLASH,
            evdev.ecodes.KEY_Z,
            evdev.ecodes.KEY_X,
            evdev.ecodes.KEY_C,
            evdev.ecodes.KEY_V,
            evdev.ecodes.KEY_B,
            evdev.ecodes.KEY_N,
            evdev.ecodes.KEY_M,
            evdev.ecodes.KEY_COMMA,
            evdev.ecodes.KEY_DOT,
            evdev.ecodes.KEY_SLASH,
            evdev.ecodes.KEY_RIGHTSHIFT,
            evdev.ecodes.KEY_KPASTERISK,
            evdev.ecodes.KEY_LEFTALT,
            evdev.ecodes.KEY_SPACE,
            evdev.ecodes.KEY_CAPSLOCK,
            evdev.ecodes.KEY_F1,
            evdev.ecodes.KEY_F2,
            evdev.ecodes.KEY_F3,
            evdev.ecodes.KEY_F4,
            evdev.ecodes.KEY_F5,
            evdev.ecodes.KEY_F6,
            evdev.ecodes.KEY_F7,
            evdev.ecodes.KEY_F8,
            evdev.ecodes.KEY_F9,
            evdev.ecodes.KEY_F10,
            evdev.ecodes.KEY_NUMLOCK,
            evdev.ecodes.KEY_SCROLLLOCK,
            evdev.ecodes.KEY_KP7,
            evdev.ecodes.KEY_KP8,
            evdev.ecodes.KEY_KP9,
            evdev.ecodes.KEY_KPMINUS,
            evdev.ecodes.KEY_KP4,
            evdev.ecodes.KEY_KP5,
            evdev.ecodes.KEY_KP6,
            evdev.ecodes.KEY_KPPLUS,
            evdev.ecodes.KEY_KP1,
            evdev.ecodes.KEY_KP2,
            evdev.ecodes.KEY_KP3,
            evdev.ecodes.KEY_KP0,
            evdev.ecodes.KEY_KPDOT,
            evdev.ecodes.KEY_ZENKAKUHANKAKU,
            evdev.ecodes.KEY_102ND,
            evdev.ecodes.KEY_F11,
            evdev.ecodes.KEY_F12,
            evdev.ecodes.KEY_RO,
            evdev.ecodes.KEY_KATAKANA,
            evdev.ecodes.KEY_HIRAGANA,
            evdev.ecodes.KEY_HENKAN,
            evdev.ecodes.KEY_KATAKANAHIRAGANA,
            evdev.ecodes.KEY_MUHENKAN,
            evdev.ecodes.KEY_KPJPCOMMA,
            evdev.ecodes.KEY_KPENTER,
            evdev.ecodes.KEY_RIGHTCTRL,
            evdev.ecodes.KEY_KPSLASH,
            evdev.ecodes.KEY_SYSRQ,
            evdev.ecodes.KEY_RIGHTALT,
            evdev.ecodes.KEY_LINEFEED,
            evdev.ecodes.KEY_HOME,
            evdev.ecodes.KEY_UP,
            evdev.ecodes.KEY_PAGEUP,
            evdev.ecodes.KEY_LEFT,
            evdev.ecodes.KEY_RIGHT,
            evdev.ecodes.KEY_END,
            evdev.ecodes.KEY_DOWN,
            evdev.ecodes.KEY_PAGEDOWN,
            evdev.ecodes.KEY_INSERT,
            evdev.ecodes.KEY_DELETE,
            evdev.ecodes.KEY_MACRO,
            evdev.ecodes.KEY_MUTE,
            evdev.ecodes.KEY_VOLUMEDOWN,
            evdev.ecodes.KEY_VOLUMEUP,
            evdev.ecodes.KEY_POWER,
            evdev.ecodes.KEY_KPEQUAL,
            evdev.ecodes.KEY_KPPLUSMINUS,
            evdev.ecodes.KEY_PAUSE,
            evdev.ecodes.KEY_SCALE,
            evdev.ecodes.KEY_KPCOMMA,
            evdev.ecodes.KEY_HANGEUL,
            evdev.ecodes.KEY_HANGUEL,
            evdev.ecodes.KEY_HANJA,
            evdev.ecodes.KEY_YEN,
            evdev.ecodes.KEY_LEFTMETA,
            evdev.ecodes.KEY_RIGHTMETA,
            evdev.ecodes.KEY_COMPOSE,
            evdev.ecodes.KEY_STOP,
            evdev.ecodes.KEY_AGAIN,
            evdev.ecodes.KEY_PROPS,
            evdev.ecodes.KEY_UNDO,
            evdev.ecodes.KEY_FRONT,
            evdev.ecodes.KEY_COPY,
            evdev.ecodes.KEY_OPEN,
            evdev.ecodes.KEY_PASTE,
            evdev.ecodes.KEY_FIND,
            evdev.ecodes.KEY_CUT,
            evdev.ecodes.KEY_HELP,
            evdev.ecodes.KEY_MENU,
            evdev.ecodes.KEY_CALC,
            evdev.ecodes.KEY_SETUP,
            evdev.ecodes.KEY_SLEEP,
            evdev.ecodes.KEY_WAKEUP,
            evdev.ecodes.KEY_FILE,
            evdev.ecodes.KEY_SENDFILE,
            evdev.ecodes.KEY_DELETEFILE,
            evdev.ecodes.KEY_XFER,
            evdev.ecodes.KEY_PROG1,
            evdev.ecodes.KEY_PROG2,
            evdev.ecodes.KEY_WWW,
            evdev.ecodes.KEY_MSDOS,
            evdev.ecodes.KEY_COFFEE,
            evdev.ecodes.KEY_SCREENLOCK,
            evdev.ecodes.KEY_DIRECTION,
            evdev.ecodes.KEY_CYCLEWINDOWS,
            evdev.ecodes.KEY_MAIL,
            evdev.ecodes.KEY_BOOKMARKS,
            evdev.ecodes.KEY_COMPUTER,
            evdev.ecodes.KEY_BACK,
            evdev.ecodes.KEY_FORWARD,
            evdev.ecodes.KEY_CLOSECD,
            evdev.ecodes.KEY_EJECTCD,
            evdev.ecodes.KEY_EJECTCLOSECD,
            evdev.ecodes.KEY_NEXTSONG,
            evdev.ecodes.KEY_PLAYPAUSE,
            evdev.ecodes.KEY_PREVIOUSSONG,
            evdev.ecodes.KEY_STOPCD,
            evdev.ecodes.KEY_RECORD,
            evdev.ecodes.KEY_REWIND,
            evdev.ecodes.KEY_PHONE,
            evdev.ecodes.KEY_ISO,
            evdev.ecodes.KEY_CONFIG,
            evdev.ecodes.KEY_HOMEPAGE,
            evdev.ecodes.KEY_REFRESH,
            evdev.ecodes.KEY_EXIT,
            evdev.ecodes.KEY_MOVE,
            evdev.ecodes.KEY_EDIT,
            evdev.ecodes.KEY_SCROLLUP,
            evdev.ecodes.KEY_SCROLLDOWN,
            evdev.ecodes.KEY_KPLEFTPAREN,
            evdev.ecodes.KEY_KPRIGHTPAREN,
            evdev.ecodes.KEY_NEW,
            evdev.ecodes.KEY_REDO,
            evdev.ecodes.KEY_F13,
            evdev.ecodes.KEY_F14,
            evdev.ecodes.KEY_F15,
            evdev.ecodes.KEY_F16,
            evdev.ecodes.KEY_F17,
            evdev.ecodes.KEY_F18,
            evdev.ecodes.KEY_F19,
            evdev.ecodes.KEY_F20,
            evdev.ecodes.KEY_F21,
            evdev.ecodes.KEY_F22,
            evdev.ecodes.KEY_F23,
            evdev.ecodes.KEY_F24,
            evdev.ecodes.KEY_PLAYCD,
            evdev.ecodes.KEY_PAUSECD,
            evdev.ecodes.KEY_PROG3,
            evdev.ecodes.KEY_PROG4,
            evdev.ecodes.KEY_DASHBOARD,
            evdev.ecodes.KEY_SUSPEND,
            evdev.ecodes.KEY_CLOSE,
            evdev.ecodes.KEY_PLAY,
            evdev.ecodes.KEY_FASTFORWARD,
            evdev.ecodes.KEY_BASSBOOST,
            evdev.ecodes.KEY_PRINT,
            evdev.ecodes.KEY_HP,
            evdev.ecodes.KEY_CAMERA,
            evdev.ecodes.KEY_SOUND,
            evdev.ecodes.KEY_QUESTION,
            evdev.ecodes.KEY_EMAIL,
            evdev.ecodes.KEY_CHAT,
            evdev.ecodes.KEY_SEARCH,
            evdev.ecodes.KEY_CONNECT,
            evdev.ecodes.KEY_FINANCE,
            evdev.ecodes.KEY_SPORT,
            evdev.ecodes.KEY_SHOP,
            evdev.ecodes.KEY_ALTERASE,
            evdev.ecodes.KEY_CANCEL,
            evdev.ecodes.KEY_BRIGHTNESSDOWN,
            evdev.ecodes.KEY_BRIGHTNESSUP,
            evdev.ecodes.KEY_MEDIA,
            evdev.ecodes.KEY_SWITCHVIDEOMODE,
            evdev.ecodes.KEY_KBDILLUMTOGGLE,
            evdev.ecodes.KEY_KBDILLUMDOWN,
            evdev.ecodes.KEY_KBDILLUMUP,
            evdev.ecodes.KEY_SEND,
            evdev.ecodes.KEY_REPLY,
            evdev.ecodes.KEY_FORWARDMAIL,
            evdev.ecodes.KEY_SAVE,
            evdev.ecodes.KEY_DOCUMENTS,
            evdev.ecodes.KEY_BATTERY,
            evdev.ecodes.KEY_BLUETOOTH,
            evdev.ecodes.KEY_WLAN,
            evdev.ecodes.KEY_UWB,
            evdev.ecodes.KEY_UNKNOWN,
            evdev.ecodes.KEY_VIDEO_NEXT,
            evdev.ecodes.KEY_VIDEO_PREV,
            evdev.ecodes.KEY_BRIGHTNESS_CYCLE,
            evdev.ecodes.KEY_BRIGHTNESS_ZERO,
            evdev.ecodes.KEY_DISPLAY_OFF,
            evdev.ecodes.KEY_WIMAX,
            evdev.ecodes.KEY_OK,
            evdev.ecodes.KEY_SELECT,
            evdev.ecodes.KEY_GOTO,
            evdev.ecodes.KEY_CLEAR,
            evdev.ecodes.KEY_POWER2,
            evdev.ecodes.KEY_OPTION,
            evdev.ecodes.KEY_INFO,
            evdev.ecodes.KEY_TIME,
            evdev.ecodes.KEY_VENDOR,
            evdev.ecodes.KEY_ARCHIVE,
            evdev.ecodes.KEY_PROGRAM,
            evdev.ecodes.KEY_CHANNEL,
            evdev.ecodes.KEY_FAVORITES,
            evdev.ecodes.KEY_EPG,
            evdev.ecodes.KEY_PVR,
            evdev.ecodes.KEY_MHP,
            evdev.ecodes.KEY_LANGUAGE,
            evdev.ecodes.KEY_TITLE,
            evdev.ecodes.KEY_SUBTITLE,
            evdev.ecodes.KEY_ANGLE,
            evdev.ecodes.KEY_ZOOM,
            evdev.ecodes.KEY_MODE,
            evdev.ecodes.KEY_KEYBOARD,
            evdev.ecodes.KEY_SCREEN,
            evdev.ecodes.KEY_PC,
            evdev.ecodes.KEY_TV,
            evdev.ecodes.KEY_TV2,
            evdev.ecodes.KEY_VCR,
            evdev.ecodes.KEY_VCR2,
            evdev.ecodes.KEY_SAT,
            evdev.ecodes.KEY_SAT2,
            evdev.ecodes.KEY_CD,
            evdev.ecodes.KEY_TAPE,
            evdev.ecodes.KEY_RADIO,
            evdev.ecodes.KEY_TUNER,
            evdev.ecodes.KEY_PLAYER,
            evdev.ecodes.KEY_TEXT,
            evdev.ecodes.KEY_DVD,
            evdev.ecodes.KEY_AUX,
            evdev.ecodes.KEY_MP3,
            evdev.ecodes.KEY_AUDIO,
            evdev.ecodes.KEY_VIDEO,
            evdev.ecodes.KEY_DIRECTORY,
            evdev.ecodes.KEY_LIST,
            evdev.ecodes.KEY_MEMO,
            evdev.ecodes.KEY_CALENDAR,
            evdev.ecodes.KEY_RED,
            evdev.ecodes.KEY_GREEN,
            evdev.ecodes.KEY_YELLOW,
            evdev.ecodes.KEY_BLUE,
            evdev.ecodes.KEY_CHANNELUP,
            evdev.ecodes.KEY_CHANNELDOWN,
            evdev.ecodes.KEY_FIRST,
            evdev.ecodes.KEY_LAST,
            evdev.ecodes.KEY_AB,
            evdev.ecodes.KEY_NEXT,
            evdev.ecodes.KEY_RESTART,
            evdev.ecodes.KEY_SLOW,
            evdev.ecodes.KEY_SHUFFLE,
            evdev.ecodes.KEY_BREAK,
            evdev.ecodes.KEY_PREVIOUS,
            evdev.ecodes.KEY_DIGITS,
            evdev.ecodes.KEY_TEEN,
            evdev.ecodes.KEY_TWEN,
            evdev.ecodes.KEY_VIDEOPHONE,
            evdev.ecodes.KEY_GAMES,
            evdev.ecodes.KEY_ZOOMIN,
            evdev.ecodes.KEY_ZOOMOUT,
            evdev.ecodes.KEY_ZOOMRESET,
            evdev.ecodes.KEY_WORDPROCESSOR,
            evdev.ecodes.KEY_EDITOR,
            evdev.ecodes.KEY_SPREADSHEET,
            evdev.ecodes.KEY_GRAPHICSEDITOR,
            evdev.ecodes.KEY_PRESENTATION,
            evdev.ecodes.KEY_DATABASE,
            evdev.ecodes.KEY_NEWS,
            evdev.ecodes.KEY_VOICEMAIL,
            evdev.ecodes.KEY_ADDRESSBOOK,
            evdev.ecodes.KEY_MESSENGER,
            evdev.ecodes.KEY_DISPLAYTOGGLE,
            evdev.ecodes.KEY_SPELLCHECK,
            evdev.ecodes.KEY_LOGOFF,
            evdev.ecodes.KEY_DOLLAR,
            evdev.ecodes.KEY_EURO,
            evdev.ecodes.KEY_FRAMEBACK,
            evdev.ecodes.KEY_FRAMEFORWARD,
            evdev.ecodes.KEY_CONTEXT_MENU,
            evdev.ecodes.KEY_MEDIA_REPEAT,
            evdev.ecodes.KEY_DEL_EOL,
            evdev.ecodes.KEY_DEL_EOS,
            evdev.ecodes.KEY_INS_LINE,
            evdev.ecodes.KEY_DEL_LINE,
            evdev.ecodes.KEY_FN,
            evdev.ecodes.KEY_FN_ESC,
            evdev.ecodes.KEY_FN_F1,
            evdev.ecodes.KEY_FN_F2,
            evdev.ecodes.KEY_FN_F3,
            evdev.ecodes.KEY_FN_F4,
            evdev.ecodes.KEY_FN_F5,
            evdev.ecodes.KEY_FN_F6,
            evdev.ecodes.KEY_FN_F7,
            evdev.ecodes.KEY_FN_F8,
            evdev.ecodes.KEY_FN_F9,
            evdev.ecodes.KEY_FN_F10,
            evdev.ecodes.KEY_FN_F11,
            evdev.ecodes.KEY_FN_F12,
            evdev.ecodes.KEY_FN_1,
            evdev.ecodes.KEY_FN_2,
            evdev.ecodes.KEY_FN_D,
            evdev.ecodes.KEY_FN_E,
            evdev.ecodes.KEY_FN_F,
            evdev.ecodes.KEY_FN_S,
            evdev.ecodes.KEY_FN_B,
            evdev.ecodes.KEY_BRL_DOT1,
            evdev.ecodes.KEY_BRL_DOT2,
            evdev.ecodes.KEY_BRL_DOT3,
            evdev.ecodes.KEY_BRL_DOT4,
            evdev.ecodes.KEY_BRL_DOT5,
            evdev.ecodes.KEY_BRL_DOT6,
            evdev.ecodes.KEY_BRL_DOT7,
            evdev.ecodes.KEY_BRL_DOT8,
            evdev.ecodes.KEY_BRL_DOT9,
            evdev.ecodes.KEY_BRL_DOT10,
            evdev.ecodes.KEY_NUMERIC_0,
            evdev.ecodes.KEY_NUMERIC_1,
            evdev.ecodes.KEY_NUMERIC_2,
            evdev.ecodes.KEY_NUMERIC_3,
            evdev.ecodes.KEY_NUMERIC_4,
            evdev.ecodes.KEY_NUMERIC_5,
            evdev.ecodes.KEY_NUMERIC_6,
            evdev.ecodes.KEY_NUMERIC_7,
            evdev.ecodes.KEY_NUMERIC_8,
            evdev.ecodes.KEY_NUMERIC_9,
            evdev.ecodes.KEY_NUMERIC_STAR,
            evdev.ecodes.KEY_NUMERIC_POUND
        ]}

        try:
            signal.signal(signal.SIGHUP, signal.SIG_IGN)
            info = evmapy.util.get_app_info()
            app_with_user = (info['name'], info['user'].pw_name)
            # Create the control socket
            self._controller = evmapy.controller.Controller(self)
            # Try to open /dev/uinput, failing gracefully
            try:
                self._uinput = evdev.UInput(name='evmapy', events=valid_events)
            except evdev.uinput.UInputError as exc:
                self._logger.warning(
                    "injecting keypresses will not be possible: %s", str(exc)
                )
            # Start processing events from all configured devices
            self._poll = select.poll()
            self._scan_devices()
            # Start monitoring the control socket
            self._fds[self._controller.fileno()] = self._controller
            self._poll.register(self._controller, select.POLLIN)
        except evmapy.controller.SocketInUseError:
            error_msg = "%s is already running as %s" % app_with_user
            self._logger.error(error_msg)
            exit(1)
        except:
            self._logger.exception("unhandled exception while initializing:")
            raise

    @property
    def devices(self):
        """
        Return a list of handled :py:class:`evmapy.source.Source`
        instances.

        :returns: list of handled :py:class:`evmapy.source.Source`
            instances
        :rtype: list
        """
        retval = []
        for processor in self._fds.values():
            if getattr(processor, 'device', 'socket') != 'socket':
                retval.append(processor)
        return retval

    def _log_device_count(self):
        """
        Log the number of currently handled devices.

        :returns: None
        """
        self._logger.info("handling %d device(s)", len(self.devices))

    def _scan_devices(self):
        """
        Scan all evdev devices in the system and attempt to subscribe to
        their events.

        :returns: None
        """
        self._logger.info("scanning devices...")
        processed_devices = [source.device['path'] for source in self.devices]
        for dev_path in evdev.list_devices():
            if dev_path not in processed_devices:
                self._add_device(dev_path)
        self._log_device_count()

    def _add_device(self, path):
        """
        Start processing events emitted by the device under the given
        path.

        :param path: path to device whose events to listen to
        :type path: str
        :returns: None
        """
        device = evdev.InputDevice(path)
        self._logger.debug("trying to add %s (%s)", device.fn, device.name)
        try:
            source = evmapy.source.Source(device)
            self._fds[source.device['fd']] = source
            self._poll.register(source.device['fd'], select.POLLIN)
        except evmapy.config.ConfigError as exc:
            if not exc.not_found:
                self._logger.error(str(exc))

    def _remove_device(self, source, quiet=False):
        """
        Stop processing events emitted by the device associated with the
        given source.

        :param source: source to stop listening to
        :type source: evmapy.source.Source
        :param quiet: whether to log device removal or not
        :type quiet: bool
        :returns: None
        """
        del self._fds[source.device['fd']]
        self._poll.unregister(source.device['fd'])
        if not quiet:
            self._logger.info("removed %(path)s (%(name)s)", source.device)
            self._log_device_count()

    def run(self):
        """
        Run a :py:meth:`select.poll.poll()` loop while handling
        exceptions nicely.

        :returns: None
        """
        try:
            self._run()
        except KeyboardInterrupt:
            self._logger.info("user requested shutdown")
        except SIGTERMReceivedException:
            self._logger.info("SIGTERM received")
        except:
            self._logger.exception("unhandled exception:")
            raise
        finally:
            # Always cleanup, even if an unhandled exception was raised
            del self._fds[self._controller.fileno()]
            self._poll.unregister(self._controller)
            self._controller.cleanup()
            for source in self.devices:
                self._remove_device(source, quiet=True)
            if self._uinput:
                self._uinput.close()
            self._logger.info("quitting")

    def _run(self):

        """
        Run a :py:meth:`select.poll.poll()` loop processing both
        synchronous and asynchronous events.

        :returns: None
        """

        def raise_signal_exception(signum, _):     # pragma: no cover
            """
            Raise an exception based on received signal.

            :raises evmapy.multiplexer.SIGHUPReceivedException:
                when SIGHUP is received
            :raises evmapy.multiplexer.SIGTERMReceivedException:
                when SIGTERM is received
            """
            if signum == signal.SIGHUP:
                raise SIGHUPReceivedException
            elif signum == signal.SIGTERM:
                raise SIGTERMReceivedException

        signal.signal(signal.SIGHUP, raise_signal_exception)
        signal.signal(signal.SIGTERM, raise_signal_exception)
        while True:
            # Calculate time until the next delayed action triggers
            now = time.time()
            timeout = 0
            if 0 in self._delayed and 'when' in self._delayed[0]:
                timeout = max(timeout, (self._delayed[0]['when'] - now) * 1000)

            mouse_timeout = self._mouse_timeout(now)
            if mouse_timeout != None:
                timeout = max(timeout, mouse_timeout*1000)

            if timeout == 0:
                timeout = None

            # Wait for either an input event or the moment when the next
            # delayed action should be triggered, whichever comes first
            try:
                results = self._poll.poll(timeout)
            except SIGHUPReceivedException:
                self._logger.info("SIGHUP received")
                self._scan_devices()
                continue
            for (fdesc, _) in results:
                try:
                    processor = self._fds[fdesc]
                    actions = processor.process()
                except evmapy.source.DeviceRemovedException:
                    self._remove_device(processor)
                    continue
                if actions:
                    self._perform_normal_actions(actions)
            if not results:
                # It's time for the next delayed action
                self._perform_delayed_actions()

            # perform mouse events
            self._perform_mouse_actions(now)

    def _perform_normal_actions(self, actions):
        """
        Start/stop actions requested by a source in response to the
        events it processed.

        :param actions: list of *(action, start)* tuples, each of which
            specifies which action to start (if *start* is *True*) or
            stop (if *start* is *False*)
        :type actions: list
        :returns: None
        """
        for (action, start, event_infos) in actions:
            self._logger.debug("action=%s, start=%s", action, start)
            if action['hold'] == 0:
                if start:
                    if action['type'] == 'key':
                        self._uinput_synthesize(action, press=True)
                    elif action['type'] == 'exec':
                        self._execute_program(action)
                    elif action['type'] == 'mouse':
                        self._uinput_mouse(action, event_infos)
                else:
                    if action['type'] == 'key':
                        self._uinput_synthesize(action, press=False)
                    elif action['type'] == 'mouse':
                        self._uinput_mouse(action, event_infos)
            else:
                if start:
                    # Schedule delayed action to trigger after hold time
                    action['when'] = time.time() + action['hold']
                    action['direction'] = 'down'
                    self._delayed.append(action)
                else:
                    # Cancel delayed action
                    try:
                        index = next(
                            i for (i, a) in enumerate(self._delayed)
                            if a['id'] == action['id']
                        )
                        del self._delayed[index]
                    except StopIteration:
                        # Action has already been removed from the queue
                        # by _perform_delayed_actions()
                        pass

    def _perform_delayed_actions(self):
        """
        Perform the next queued delayed action.

        :returns: None
        """
        if 0 not in self._delayed:
            return
        action = self._delayed[0]
        if action['type'] == 'key':
            if action['direction'] == 'down':
                # Simulate a key press and queue its release in 30 ms to
                # make the synthesized event semi-realistic
                self._uinput_synthesize(action, press=True)
                action['when'] = time.time() + 0.03
                action['direction'] = 'up'
                self._delayed.append(action)
            else:
                self._uinput_synthesize(action, press=False)
        elif action['type'] == 'exec':
            self._execute_program(action)
        del self._delayed[0]

    def _uinput_synthesize(self, action, press):
        """
        Inject a fake key press into the input subsystem using uinput

        :param action: action dictionary containing a `target` key which
            specifies the key to synthesize
        :type action: dict
        :param press: whether to simulate a key press (`True`) or a key
            release (`False`)
        :type press: bool
        :returns: None
        """
        if not self._uinput:
            return
        keys = evmapy.util.as_list(action['target'])
        for key in keys:
            etype = evdev.ecodes.ecodes['EV_KEY']
            ecode = evdev.ecodes.ecodes[key]
            self._logger.debug(
                "writing: code %02d, type %02d, val %02d", ecode, etype, press
            )
            self._uinput.write(etype, ecode, int(press))
            self._logger.debug("writing: code 00, type 00, val 00")
            self._uinput.syn()

    def _uinput_mouse(self, action, value):
        keys = evmapy.util.as_list(action['target'])
        for axis in keys:
            if axis == "X":
                self._mousePosition["x"] = value
            elif axis == "Y":
                self._mousePosition["y"] = value

    def _mouse_timeout(self, now):
        if abs(self._mousePosition["x"]) < self._mousePosition["deadzone"] and abs(self._mousePosition["y"]) < self._mousePosition["deadzone"]:
            return None
        return self._mousePosition["every"]

    def _perform_mouse_actions(self, now):
        if abs(self._mousePosition["x"]) < self._mousePosition["deadzone"] and abs(self._mousePosition["y"]) < self._mousePosition["deadzone"]:
            return
        if now < self._mousePosition["last"] + self._mousePosition["every"]:
            return

        if abs(self._mousePosition["x"]) >= self._mousePosition["deadzone"]:
            self._uinput.write(evdev.ecodes.ecodes['EV_REL'], evdev.ecodes.ecodes['REL_X'], self._mouse_move_per_to_abs(self._mousePosition["x"]))

        if abs(self._mousePosition["y"]) >= self._mousePosition["deadzone"]:
            self._uinput.write(evdev.ecodes.ecodes['EV_REL'], evdev.ecodes.ecodes['REL_Y'], self._mouse_move_per_to_abs(self._mousePosition["y"]))

        self._uinput.syn()
        self._mousePosition["last"] = now

    def _mouse_move_per_to_abs(self, per):
        order = per * per
        order = order * self._mousePosition["speed"]
        if per < 0:
            order = order * -1
            order = order -1
        else:
            order = order +1
        return int(order)
        
    def _execute_program(self, action):
        """
        Run external program(s) associated with the given action.

        :param action: action dictionary containing a `target` key which
            specifies the command(s) to be run
        :type action: dict
        :returns: None
        """
        commands = evmapy.util.as_list(action['target'])
        for command in commands:
            self._logger.debug("running: '%s'", command)
            os.system(command)

    def load_device_config(self, dev_path, config_file):
        """
        Loads configuration for the :py:class:`evmapy.source.Source`
        instance associated with the device under the given path from
        the configuration file with the given name.

        :param dev_path: path to the device which the
            :py:class:`evmapy.source.Source` to be configured is
            associated with
        :type dev_path: str
        :param config_file: name of the configuration file to load
        :type config_file: str
        :returns: None
        """
        for source in self.devices:
            if source.device['path'] == dev_path:
                try:
                    source.load_config(config_file)
                except evmapy.config.ConfigError as exc:
                    self._logger.error(
                        "%s: failed to load %s",
                        source.device['path'], str(exc)
                    )
