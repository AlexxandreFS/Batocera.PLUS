XJOYPAD 0.01B Manual

(C) 2002 Erich Kitzmueller  erich.kitzmueller@itek.at

Introduction

xjoypad allows an USB joypad (probably a USB joystick, too) to be used with 
games on linux (probably other unix-like operating systems too).
This is done by mapping the joypad events to X keyboard events which are sent
to the window currently having the focus. Therefore only keyboard-controlled
games are currently supported by xjoypad. xjoypad was written to add joypad
support to the playstation emulator epsxe.


Installation

Unzip xjoypad.zip into a new directory, then run make. You need the X header
files and libraries for this.


Prequesites

Before you start xjoypad, USB must be up and running, including joystick
support. You can check this by running
	od -xw8 /dev/input/js0
this should create output like this:
0000000 d900 0026 0000 0081
0000010 d900 0026 0000 0181
0000020 d900 0026 0000 0281
0000030 d900 0026 0000 0381
0000040 d900 0026 0000 0481
0000050 d900 0026 0000 0581
0000060 d900 0026 0000 0681
0000070 d900 0026 0000 0781
0000100 d900 0026 0000 0881
0000110 d900 0026 0000 0981
0000120 d900 0026 0000 0a81
0000130 d900 0026 0000 0b81
0000140 d900 0026 0000 0082
0000150 d900 0026 0000 0182
0000160 d900 0026 0000 0282

If this doesn't work, try
	modprobe joydev
and try again.


Running xjoypad

usage: xjoypad [-display display] [-devicefilename filename] [-verbose] [-up keycode] [-down keycode] [-left keycode] [-right keycode] [-buttons keycode keycode ...]

There are reasonable default values for all paramters, see below.

Parameters:
	-display display		X-Display (default: $DISPLAY)
	-devicefilename filename	device file for input (default: /dev/input/js0)
	-verbose			report USB events
	-up keycode			keycode for Joypad-Up (default: 98)
	-down keycode			keycode for Joypad-Down (default: 104)
	-left keycode			keycode for Joypad-Down (default: 100)
	-right keycode			keycode for Joypad-Down (default: 102)
	-buttons keycode1 keycode2...	keycodes for Buttons (default: 10,11,...)

Please note that keycodes are not the same like the symbols they are mapped to.
To find out the appropriate keycodes for your program, use xev. The default
mappings map the stick or pad to the cursor keys and the buttons to the
keys 1,2,3,4,5,6,7,8,9,0,Q,W,E,R,T,Z.
Buttons mapped to keycode 0 will keep their default mapping.

