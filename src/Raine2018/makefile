########################################
##                                    ##
##                RAINE               ##
##                                    ##
########################################

##
## type make RAINECPS=1 to build rainecps
## The default is to build a dynamic version. Use make STATIC=1 to build a
## static version.
##
## Requirements: read the docs !
##

# version (when the version increases, raine shows the issue dialog on
# startup
VERSION = "2018 Batocera.PLUS"

# Comment out if you don't want the debug features
# RAINE_DEBUG = 1

# Be verbose ?
# VERBOSE = 1

# For osx : use frameworks or brew shared libs ?
# Actually frameworks are a convenience for end users, to build them use
# the make_framework.pl script in TOOLS directory to convert the brew
# shared libs to frameworks and then define FRAMEWORK here
# FRAMEWORK = 1

# Disable all asm, if you do that you'd better remove the cpu cores which
# currently exist only in asm. This will also disable the asm_video_core of
# course
# NO_ASM = 1

# Use asm video core ? (comment to use C core)
ASM_VIDEO_CORE = 1

# console ?
# HAS_CONSOLE = 1

# compile bezels (artwork) support ? (ignored if building neocd)
# USE_BEZELS=1

# use cz80 instead of the usual heavily modyfied asm-only mz80 ?
# CZ80 = 1

# Use C version of 68020 core ? (default is asm, commented out)
# C68020 = 1

# end of user options, after this line the real thing starts...

ifdef NO_ASM
ASM_VIDEO_CORE =
CZ80 = 1
C68020 = 1
endif

# Try to detect mingw... If you want to build the dos and the mingw
# version on the same system you should unset djdir before making
# the mingw version.
ifeq ("$(shell uname)","Linux")
OSTYPE=linux-gnu
endif

ifeq ($(CC),cc)
CC=gcc
endif

ifeq ("$(shell uname)","FreeBSD")
OSTYPE=linux-gnu
endif
ifeq ("$(shell uname)","Darwin")
# Mac os X
DARWIN=1
OSTYPE=darwin
# no need to make a 32 bit binary if disabling asm completely !
ifeq ("$(shell sysctl hw.optional.x86_64)","hw.optional.x86_64: 1")
ifndef NO_ASM
	CC +=  -m32
  	CXX +=  -m32
  	LD=$(CXX) -m32
else
    LD=$(CXX)
endif
endif

endif

ifeq ("$(OSTYPE)","msys")
MINGDIR=1
OSTYPE=mingw32
endif

ifndef DARWIN
ifeq ("$(shell uname -m)","x86_64")
  # autodetect x86_64 arch, and in this case build for 32 bit arch
  # notice that you still need to make a symbolic link for libstdc++.so to
  # libstdc++.so.6, and make sure that the 32 bit version of all the libraries
  # are installed in 32 bit (which might be a little tricky at first).
 ifndef CROSSCOMPILE
ifndef NO_ASM
  CC += -m32
  CXX += -m32
  LD=$(CXX) -L /usr/lib32
else
  LD=$(CXX)
endif
 else
	ifeq ("$(LD)","ld")
	LD = $(CXX)
    endif
 endif
else
ifeq ("$(LD)","ld")
  LD=$(CXX)
endif
endif
endif

WINDRES_V := $(shell windres --version 2>/dev/null)
ifdef WINDRES_V
	WINDRES:=windres
else
	WINDRES:=$(target)-windres
endif

NASM_V := $(shell nasm -v 2>/dev/null)
ifndef NASM_V
ifdef VERBOSE
ASM=nasmw
else
ASM=@nasmw
endif
else
ifdef VERBOSE
ASM=nasm
else
ASM=@nasm
endif
endif

ifdef mingdir
MINGDIR=1
endif

ifdef MINGDIR
# mingw
RAINE32 = 1
OSTYPE = mingw32
endif

RM =	@rm -f

# This test is for stupid win32 gcc ports with bad defaults
ifdef VERBOSE
CCV=$(CC)
CXXV=$(CXX)
LDV=$(LD)
else
CCV=@$(CC)
CXXV=@$(CXX)
LDV=@$(LD)
endif

GCC_MAJOR := $(shell $(CC) -dumpversion|sed 's/\..*//')
GCC_MINOR := $(shell $(CC) -dumpversion|sed 's/.\.\(.\)\..*/\1/')
GCC_PATCH := $(shell $(CC) -dumpversion|sed 's/.*\.//')

MD =	@mkdir

# error logging (djgpp - old stuff)
# CC =	redir -ea errorlog.txt gcc

# profiling
# CC =	gcc -pg

INCDIR=                 \
    -Isource            \
    -Isource/68000      \
    -Isource/sound      \
    -Isource/games      \
    -Isource/video      \
    -Isource/mini-unzip \
    -Isource/mame       \
    -Isource/6502       \
	-Isource/m68705

ifdef CZ80
INCDIR +=  -Isource/cz80
else
INCDIR +=  -Isource/z80
endif

ifdef C68020
INCDIR += -Isource/68020/c
else
INCDIR += -Isource/68020
endif

ifeq ($(OSTYPE),cygwin)

   # Cygwin

RAINE_EXE = raine32.exe

# -O1 is necessary for stupid hq2x16.asm
AFLAGS = -f coff -O1 -D__RAINE__ -DRAINE_WIN32

RAINE32 = 1

DEFINE = -D__RAINE__ \
	   -DRAINE_WIN32 \

   PNG_LFLAGS = "$(shell libpng-config --ldflags)"
   PNG_STATIC_LFLAGS = "$(shell libpng-config --static --ldflags)"
   LIBS = -lz -lalleg $(PNG_LFAGS)
   LIBS_STATIC = -lz -lalleg_s -lkernel32 -luser32 -lgdi32 -lcomdlg32 \
   -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound \
   -L/lib/mingw -lmoldname -lmsvcrt $(PNG_STATIC_LFLAGS)

LIBS_DEBUG = -lz -lalld $(PNG_LFLAGS)

  LFLAGS = -mno-cygwin -mwindows

else
ifdef RAINE32

   # MINGW32

SDL = 1
   RAINE_EXE = raine32.exe
ifdef CROSSCOMPILE
	ASM = @nasm
	MD = @mkdir
else
ifndef ASM
   ASM = @nasmw.exe # auto-detection broken for mingw !!!
endif
   MD = @mkdir.exe # to avoid the built-in command... strange it's necessary...
endif

   AFLAGS = -f coff -O1 -D__RAINE__ \
	   -DRAINE_WIN32

   PNG_CFLAGS = "$(shell libpng-config --cflags)"
   PNG_LFLAGS = $(shell libpng-config --ldflags)
   PNG_STATIC_LFLAGS = "$(shell libpng-config --static --ldflags)"
   DEFINE = -D__RAINE__ \
	   -DRAINE_WIN32 \

   LIBS = -lz $(PNG_LFLAGS) -lopengl32 -lglu32
   LIBS_STATIC = -lz $(PNG_STATIC_LFLAGS)
   INCDIR += $(PNG_CFLAGS)

LIBS_DEBUG = -lz $(PNG_LFLAGS) -lopengl32 -lglu32

ifndef SDL
LIBS += -lalleg
LIBS_STATIC += -lalleg_s -lkernel32 -luSer32 -lgdi32 -lcomdlg32 \
   -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound
LIBS_DEBUG += -lalld
endif

ifndef RAINE_DEBUG
# this one hides the console in windows
  LFLAGS = -mwindows
endif
else
ifdef DJDIR
   RAINE_EXE = Raine.exe
   RAINE_DOS = 1

ifdef CROSSCOMPILE
	ASM = @nasm
else
	ASM = @nasmw.exe # auto-detection broken for djgpp !!!
endif

   OSTYPE = dos
   HAS_CONSOLE =
   AFLAGS = -f coff -O1 -D__RAINE__ \
	   -DRAINE_DOS

   DEFINE = -D__RAINE__ \
	   -DRAINE_DOS

   LIBS = -lalleg -lpng -lz -lm
   LIBS_DEBUG = -lalleg -lpng -lz -lm
ifdef RAINE_DEBUG
   LFLAGS = -Xlinker -Ttext -Xlinker 0x68000
else
   LFLAGS = -Xlinker -Ttext -Xlinker 0x4000
endif
else
# linux

SDL = 1

ifdef DARWIN
# using C video core for the moment
# pb: how to run self modifying code on OSX ?
# And same problem for the 68020 apparently !
# ASM_VIDEO_CORE =
# C68020 = 1
DESTDIR = Raine.app
   prefix = $(DESTDIR)/Contents
   bindir = $(prefix)/MacOS
   sharedir = $(prefix)/Resources
   mandir = $(prefix)/man/man6
   rainedata = $(sharedir)
else
   prefix = $(DESTDIR)/usr
   bindir = $(prefix)/games
   sharedir = $(prefix)/share/games
   mandir = $(prefix)/man/man6
   rainedata = $(sharedir)/raine
endif
ifndef SDL
   langdir = $(rainedata)/languages
else
   bitmaps_dir = $(rainedata)/bitmaps
   shaders_dir = $(rainedata)/shaders
   fonts_dir = $(rainedata)/fonts
   langdir = $(rainedata)/locale
   scripts_dir = $(rainedata)/scripts/neocd
#   bld_dir = $(rainedata)/blend
endif
   romdir = $(rainedata)/roms
   artdir = $(rainedata)/artwork
   emudxdir = $(rainedata)/emudx

RAINE_EXE = raine

ifndef SDL
   RAINE_DAT = raine.dat
   RAINE_LNG = brasil.cfg dansk.cfg espanol.cfg french2.cfg german2.cfg japanese.cfg spanish.cfg turkish.cfg catala.cfg dutch.cfg euskera.cfg french.cfg german.cfg polish.cfg svenska.cfg czech.cfg english.cfg finnish.cfg galego.cfg italian.cfg portugal.cfg template.cfg
endif
   RAINE_UNIX = 1

ifdef VERBOSE
   INSTALL = /usr/bin/install
else
    INSTALL = @install
endif
   INSTALL_BIN = $(INSTALL) -m 755
   INSTALL_DATA = $(INSTALL) -m 644
   RD = rmdir --ignore-fail-on-non-empty
   CD = cd

   AFLAGS = -f elf -O1 -D__RAINE__ \
	   -DRAINE_UNIX

   PNG_CFLAGS = "$(shell libpng-config --cflags)"
ifndef SDL
ALLEGRO_CFLAGS = "$(shell allegro-config --cflags)"
endif

   INCDIR += $(PNG_CFLAGS) $(ALLEGRO_CFLAGS) -I$(X11BASE)/include -I$(LOCALBASE)/include


   DEFINE = -D__RAINE__ \
	   -DRAINE_UNIX

ifndef SDL
   LIBS = -lz $(shell allegro-config --libs) $(shell libpng-config --ldflags) -lm
   LIBS_DEBUG = -lz $(shell allegro-config --libs ) $(shell libpng-config --ldflags) -lm
   LIBS_STATIC = -lz $(shell allegro-config --static) $(shell libpng-config --static --ldflags) -lm
else
ifdef DARWIN
   LIBS = -lz /usr/local/lib/libpng.a -lm
   LIBS_DEBUG = -lz /usr/local/lib/libpng.a -lm
   LIBS_STATIC = -lz /usr/local/lib/libpng.a -lm
else
   LIBS = -lz $(shell libpng-config --ldflags) -lm
   LIBS_DEBUG = -lz $(shell libpng-config --ldflags) -lm
   LIBS_STATIC = -lz $(shell libpng-config --static --ldflags) -lm
endif
ifndef DARWIN
	LIBS += -lGL -lGLU
	LIBS_DEBUG += -lGL -lGLU
endif
endif

ifndef SDL
ifeq ("$(shell if [ -e /usr/include/vga.h ] || [ -e /usr/local/include/vga.h ]; then echo yes; fi)","yes")
GFX_SVGALIB=1
endif
endif

ifdef GFX_SVGALIB
   LIBS += -lvga
   LIBS_DEBUG += -lvga
   LIBS_STATIC += -lvga
endif # GFX_SVGALIB

endif # linux / mingw32
endif # djgpp
endif # if OSTYPE == cygwin

ifdef RAINE_DEBUG
 ifndef SDL
INCDIR +=	-Isource/alleg/debug
  endif
endif

ifndef VERBOSE
ASM := @$(ASM)
endif

# Uncomment if you want to use the SEAL audio library (linux, dos or win32)
# seal is dead since the end of 1998, and it's not actievely maintained anymore in raine,
# so expect problems if you enable this.
# In dos seal is better to handle pci soundcards.
ifdef RAINE_DOS
SEAL = 1
endif

ifdef SEAL
LIBS += -laudio
LIBS_DEBUG += -laudio
LIBS_STATIC += -laudio
ifdef RAINE32
LIBS += -lmsvcrt \
	-lkernel32 -lwinmm \
	-lole32 -luser32 \
 -ldsound
endif
endif

ifdef SDL
INCDIR += -I source/sdl
else
INCDIR += -Isource/alleg/gui
endif

# To allow cross-compilation, we need one dir / target
OBJDIR = $(OSTYPE)
ifdef SDL
OBJDIR = $(OSTYPE)-sdl
endif

ifndef NO_ASM
ifndef RAINE_DOS
include cpuinfo
else
_MARCH=-march=pentium -mtune=pentium
CPU=pentium
endif
endif

ifdef X86_64
OBJDIR := $(OBJDIR)64
endif

ifeq "$(RAINE32) $(STATIC) $(SDL)" "1 1 "
# Windows need a separate object dir for the static version (for allegro)
OBJDIR := $(OBJDIR)/static
else
OBJDIR := $(OBJDIR)/object
endif

ifdef RAINE_DEBUG
OBJDIR := $(OBJDIR)d
endif

ifdef ASM_VIDEO_CORE
VIDEO_CORE = $(OBJDIR)/video/i386
else
VIDEO_CORE = $(OBJDIR)/video/c
endif

OBJDIRS=$(OBJDIR)                \
    $(OBJDIR)/mame               \
    $(OBJDIR)/sound              \
    $(OBJDIR)/68000              \
    $(OBJDIR)/video              \
    $(OBJDIR)/video/c            \
    $(OBJDIR)/video/i386         \
    $(OBJDIR)/video/i386/newspr2 \
    $(VIDEO_CORE)/blit_x2        \
    $(OBJDIR)/mini-unzip         \
    $(OBJDIR)/7z                 \
    $(OBJDIR)/video/i386/packed  \
    $(VIDEO_CORE)/str            \
    $(OBJDIR)/video/zoom         \
    $(OBJDIR)/math               \
    $(OBJDIR)/games              \
    $(OBJDIR)/6502               \
    $(OBJDIR)/m68705             \
	$(OBJDIR)/neocd				 \
	locale/fr/LC_MESSAGES \
	locale/es/LC_MESSAGES \
	locale/pt/LC_MESSAGES

ifdef CZ80
OBJDIRS += $(OBJDIR)/cz80
else
OBJDIRS += $(OBJDIR)/z80
endif

ifdef C68020
OBJDIRS += $(OBJDIR)/68020/c
else
OBJDIRS += $(OBJDIR)/68020
endif

ifdef SDL
OBJDIRS += \
	$(OBJDIR)/sdl \
	$(OBJDIR)/sdl/SDL_gfx \
	$(OBJDIR)/sdl/gui \
	$(OBJDIR)/sdl/dialogs \
	$(OBJDIR)/sdl/console

else
OBJDIRS += $(OBJDIR)/alleg \
	$(OBJDIR)/alleg/png
ifdef RAINE_DEBUG
OBJDIRS += $(OBJDIR)/alleg/debug \
	$(OBJDIR)/alleg/debug/dz80
endif
endif

ifdef SEAL
OBJDIRS += $(OBJDIR)/seal
endif

ifdef RAINE32
  OBJDIRS += $(OBJDIR)/fnmatch
endif

ifndef CROSSCOMPILE
INCDIR += -I/usr/local/include
endif

ifdef RAINE_UNIX
	# windows uses /usr/include so it's handy when cross compiling from linux
ifeq ($(wildcard /usr/include/muParser),)
	INCDIR += -I/usr/local/include/muParser
else
	INCDIR += -I/usr/include/muParser
endif
endif

ifdef RAINE_DEBUG
CFLAGS_MCU = $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-format-truncation -Wno-write-strings -g -DRAINE_DEBUG
CFLAGS += $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-format-truncation -Wno-write-strings -g -DRAINE_DEBUG

else
# All the flags are optimisations except -fomit-frame-pointer necessary for
# the 68020 core in dos. -Wno-trigraphs suppress some anoying warnings with
# gcc-2.96
# These flags are for gcc-2.x

ifdef RAINE32
# when starting a game -> black screen if -O > 1 (bug in uint64 calculation)
CFLAGS += -O3
else
# Seems to work now, at least with the sdl version ? (to be tested with windows !)
CFLAGS = -O3
endif

CFLAGS += $(INCDIR) \
	$(DEFINE) \
	$(_MARCH) \
	-Wno-trigraphs \
	-fexpensive-optimizations \
	-ffast-math \
	-w \
	-fomit-frame-pointer

# This is required for gcc-2.9x (bug in -fomit-frame-pointer)
ifeq ($(GCC_MAJOR),2)
CFLAGS_MCU = $(_MARCH) -O3 -fexpensive-optimizations # switches for the 68705 mcus
else
CFLAGS_MCU := $(CFLAGS)
endif

ifdef RAINE_UNIX
CFLAGS += -pipe
endif
# The accumulate-outgoing-args is for gcc3, but I am not sure it has any
# effect... And I could not notice any improvement with my duron if I change
# the cpu and arch to athlon... For now I comment the gcc3 option for the
# win32 version (no gcc3 for win32 for now).
#	 -maccumulate-outgoing-args
#	-pedantic
endif

ifeq ("$(shell $(CC) --version|grep '^Apple'|sed 's/\(Apple LLVM\).*/\1/')","Apple LLVM")
	# gcc 4.8 emits warnings for all the game definitions because we
	# override the definition with the new macros...
	CFLAGS += -Wno-initializer-overrides \
			  -Wno-invalid-source-encoding
endif

ifdef GFX_SVGALIB
CFLAGS += -DGFX_SVGA
endif

ifdef X86_64
CFLAGS += -DX86_64
CFLAGS_MCU += -DX86_64
endif

ifdef HAS_CONSOLE
CFLAGS += -DHAS_CONSOLE
CFLAGS_MCU += -DHAS_CONSOLE
endif

ifdef NO_ASM
CFLAGS += -DNO_ASM
CFLAGS_MCU += -DNO_ASM
endif

ifdef CZ80
CFLAGS += -DHAS_CZ80
CFLAGS_MCU += -DHAS_CZ80
endif

ifdef USE_BEZELS
CFLAGS += -DUSE_BEZELS=1
CFLAGS_MCU += -DUSE_BEZELS=1
endif

ifdef SDL
CFLAGS += -DSDL
CFLAGS_MCU += -DSDL
else
OBJDIRS +=  \
	$(OBJDIR)/alleg/gui \
	$(OBJDIR)/alleg/jpg

endif

# assembler (gas)
SFLAGS= $(INCDIR) \
	$(DEFINE) \
	-Wall -Wno-write-strings \
	$(_MARCH) \
	-xassembler-with-cpp \

ifeq ($(OSTYPE),cygwin)
CFLAGS += -mno-cygwin
CFLAGS_MCU += -mno-cygwin
SFLAGS += -mno-cygwin
endif

ifdef RAINE_DEBUG

# Debuger

# dz80 interface

DZ80=	$(OBJDIR)/alleg/debug/dz80/dissz80.o \
	$(OBJDIR)/alleg/debug/dz80/dz80_raine.o \
	$(OBJDIR)/alleg/debug/dz80/tables.o

ifndef SDL
# in sdl the debuger will very probably use sdl_console
# for now there is no debuger at all
DEBUG= $(OBJDIR)/alleg/debug/dbg_gui.o \
	$(OBJDIR)/alleg/debug/breakpt.o \
	$(DZ80)
endif

endif

# ASM 68020 core

ifdef C68020
ASM020= $(OBJDIR)/68020/c/newcpu.o \
	$(OBJDIR)/68020/c/readcpu.o \
	$(OBJDIR)/68020/c/cpustbl.o \
	$(OBJDIR)/68020/c/cpudefs.o \
	$(OBJDIR)/68020/c/cpuemu_01.o \
	$(OBJDIR)/68020/c/cpuemu_02.o \
	$(OBJDIR)/68020/c/cpuemu_03.o
else
ASM020= $(OBJDIR)/68020/newcpu.o \
	$(OBJDIR)/68020/readcpu.o \
	$(OBJDIR)/68020/cpustbl.o \
	$(OBJDIR)/68020/cpudefs.o \
	$(OBJDIR)/68020/a020core.o
endif

# STARSCREAM 68000 core

SC000=	$(OBJDIR)/68000/s68000.o \
	$(OBJDIR)/68000/starhelp.o \

# MZ80 core

ifdef CZ80
MZ80= $(OBJDIR)/cz80/cz80.o \
      $(OBJDIR)/cz80/mz80help.o
else
MZ80=	$(OBJDIR)/z80/mz80.o \
	$(OBJDIR)/z80/mz80help.o
endif

# network core

NET=	$(OBJDIR)/net/d_system.o \
	$(OBJDIR)/net/d_net.o \
	$(OBJDIR)/net/d_netfil.o

# M6502 core

M6502=	$(OBJDIR)/6502/m6502.o \
	$(OBJDIR)/6502/m6502hlp.o \

# M68705 core

M68705= $(OBJDIR)/m68705/m68705.o \

# Video core

VIDEO=	$(OBJDIR)/video/tilemod.o \
	$(OBJDIR)/video/palette.o \
	$(OBJDIR)/video/priorities.o \
	$(OBJDIR)/video/newspr.o \
	$(OBJDIR)/video/spr64.o \
	$(OBJDIR)/video/cache.o \
	$(OBJDIR)/video/res.o \
	$(OBJDIR)/video/scale2x.o \
	$(OBJDIR)/video/scale3x.o \
	$(VIDEO_CORE)/str/6x8_8.o \
	$(VIDEO_CORE)/str/6x8_16.o \
	$(VIDEO_CORE)/str/6x8_32.o \
		\
	$(VIDEO_CORE)/16x8_8.o \
	$(VIDEO_CORE)/16x8_16.o \
	$(VIDEO_CORE)/16x8_32.o \
		\
	$(VIDEO_CORE)/blit_x2/8.o \
	$(VIDEO_CORE)/blit_x2/16.o \
	$(VIDEO_CORE)/blit_x2/24.o \
	$(VIDEO_CORE)/blit_x2/32.o \
	$(OBJDIR)/video/zoom/16x16.o \
	$(OBJDIR)/video/zoom/16x16_16.o \
	$(OBJDIR)/video/zoom/16x16_32.o \
	$(OBJDIR)/video/zoom/16x8.o \
	$(OBJDIR)/video/c/lscroll.o \
	$(OBJDIR)/video/alpha.o \
	$(OBJDIR)/video/c/str_opaque.o \
	$(OBJDIR)/video/c/common.o \
	$(OBJDIR)/video/c/pdraw.o

ifndef NO_ASM
VIDEO += \
	$(OBJDIR)/video/hq2x16.o \
	$(OBJDIR)/video/hq2x32.o \
	$(OBJDIR)/video/hq3x16.o \
	$(OBJDIR)/video/hq3x32.o
endif

ifdef ASM_VIDEO_CORE
    VIDEO += \
	$(VIDEO_CORE)/spr8x8_8.o \
	$(VIDEO_CORE)/spr8_16.o \
	$(VIDEO_CORE)/spr8_32.o \
	$(VIDEO_CORE)/16x16_8.o \
	$(VIDEO_CORE)/16x16_16.o \
	$(VIDEO_CORE)/16x16_32.o \
	$(OBJDIR)/video/i386/packed/8.o \
	$(OBJDIR)/video/i386/packed/16.o \
	$(OBJDIR)/video/i386/packed/32.o \
	$(OBJDIR)/video/i386/32x32_8.o \
	$(OBJDIR)/video/i386/32x32_16.o \
	$(OBJDIR)/video/i386/32x32_32.o \
	$(OBJDIR)/video/i386/newspr2/8.o \
	$(OBJDIR)/video/i386/newspr2/16.o \
	$(OBJDIR)/video/i386/newspr2/32.o \
	$(OBJDIR)/video/i386/move.o \

else
    VIDEO += $(VIDEO_CORE)/sprites.o
endif

# common to asm & c : 32bpp version of alpha blending
VIDEO += $(OBJDIR)/video/c/sprites32_a50.o \
	 $(OBJDIR)/video/c/mapped_alpha.o

ifndef SDL
VIDEO += \
	$(OBJDIR)/video/arcmon.o \
	$(OBJDIR)/video/arcmode.o \
	$(OBJDIR)/video/blitasm.o \
	$(OBJDIR)/video/eagle.o
endif

# Sound core

SOUND= \
    $(OBJDIR)/sound/ymdeltat.o \
    $(OBJDIR)/sound/fmopl.o    \
    $(OBJDIR)/sound/fm.o       \
    $(OBJDIR)/sound/emulator.o

ASSOC = $(OBJDIR)/sound/assoc.o

ifdef SDL
ASSOC += \
	$(OBJDIR)/sdl/dialogs/sound_commands.o \
	$(OBJDIR)/sdl/dialogs/neocd_options.o \
	$(OBJDIR)/sdl/dialogs/neo_softdips.o \
	$(OBJDIR)/sdl/dialogs/neo_debug_dips.o \
	$(OBJDIR)/sdl/dialogs/translator.o
endif

2151 = 	$(OBJDIR)/sound/ym2151.o \
	$(OBJDIR)/sound/2151intf.o

2203 = $(OBJDIR)/sound/2203intf.o

2413 = $(OBJDIR)/sound/2413intf.o \
	$(OBJDIR)/sound/ym2413.o

2610 = $(OBJDIR)/sound/2610intf.o

3812 = $(OBJDIR)/sound/3812intf.o

ADPCM = $(OBJDIR)/sound/adpcm.o

AY8910 = $(OBJDIR)/sound/ay8910.o

DAC = $(OBJDIR)/sound/dac.o

DXSMP = $(OBJDIR)/sound/dxsmp.o
ifdef RAINE_DOS
DXSMP += $(OBJDIR)/sound/wav.o # wav conversion for dos
endif

ENSONIQ = $(OBJDIR)/sound/es5506.o

M6585 = $(OBJDIR)/sound/m6585.o

MSM5205 = $(OBJDIR)/sound/msm5205.o

MSM5232 = $(OBJDIR)/sound/msm5232.o

NAMCO = $(OBJDIR)/sound/namco.o

QSOUND = $(OBJDIR)/sound/qsound.o

SMP16BIT = $(OBJDIR)/sound/smp16bit.o

YMZ280B = $(OBJDIR)/sound/ymz280b.o

YMF278B = $(OBJDIR)/sound/ymf278b.o

X1_010 = $(OBJDIR)/sound/x1_010.o

TOAPLAN2 = $(OBJDIR)/sound/toaplan2.o

include games.mak

# System drivers

SYSDRV= \
	$(OBJDIR)/games/games.o \
	$(OBJDIR)/games/default.o

# Interface

ifdef HAS_CONSOLE
CONSOLE = \
	$(OBJDIR)/sdl/console/console.o \
	$(OBJDIR)/sdl/console/parser.o \
	$(OBJDIR)/sdl/console/scripts.o \
	$(OBJDIR)/sdl/console/if.o \
	$(OBJDIR)/sdl/gui/tconsole.o \
	$(OBJDIR)/sdl/console/exec.o

ifdef DARWIN
ifdef FRAMEWORK
LIBS += -framework muparser
else
LIBS += -lmuparser
endif
else # DARWIN
LIBS += -lmuparser
endif
LIBS_DEBUG += -lmuparser
endif

ifdef SDL
GUI=	$(OBJDIR)/sdl/gui.o \
	$(OBJDIR)/sdl/dialogs/video_info.o \
	$(OBJDIR)/sdl/dialogs/fsel.o \
	$(OBJDIR)/sdl/dialogs/video_options.o \
	$(OBJDIR)/sdl/dialogs/sound_options.o \
	$(OBJDIR)/sdl/dialogs/gui_options.o \
	$(OBJDIR)/sdl/dialogs/dirs.o \
	$(OBJDIR)/sdl/dialogs/about.o \
	$(OBJDIR)/sdl/dialogs/messagebox.o \
	$(OBJDIR)/sdl/dialogs/controls.o \
	$(OBJDIR)/sdl/dialogs/cheats.o \
	$(OBJDIR)/sdl/dialogs/game_options.o \
	$(OBJDIR)/sdl/dialogs/sprite_viewer.o \
	$(OBJDIR)/sdl/dialogs/colors.o \
	$(OBJDIR)/sdl/gui/tfont.o \
	$(OBJDIR)/sdl/gui/menu.o \
	$(OBJDIR)/sdl/gui/widget.o \
	$(OBJDIR)/sdl/gui/tslider.o \
	$(OBJDIR)/sdl/gui/tedit.o \
	$(OBJDIR)/sdl/gui/tlift.o \
	$(OBJDIR)/sdl/gui/tbitmap.o \
	$(CONSOLE) \
	$(OBJDIR)/sdl/dialogs/game_selection.o \
	$(OBJDIR)/sdl/dialogs/romdirs.o \
	$(OBJDIR)/sdl/dialogs/dlg_dsw.o

else
GUI=	$(OBJDIR)/alleg/gui/gui.o \
	$(OBJDIR)/alleg/gui/rgui.o \
	$(OBJDIR)/alleg/gui/rguiproc.o \
	$(OBJDIR)/alleg/gui/rfsel.o \
	$(OBJDIR)/alleg/gui/about.o \
	$(OBJDIR)/alleg/gui/cheat.o \
	$(OBJDIR)/alleg/gui/dlg_dsw.o \
	$(OBJDIR)/alleg/gui/sound.o \
	$(OBJDIR)/alleg/gui/keys.o \
	$(OBJDIR)/alleg/gui/joystick.o
endif

ifdef RAINE32
  # There is a specific incompatibility in windows for fnmatch so we need
  # to add this files for fsel
  GUI += $(OBJDIR)/fnmatch/fnmatch.o
endif

# Core

CORE=	$(OBJDIR)/raine.o \
	$(OBJDIR)/romdir.o \
	$(OBJDIR)/hiscore.o \
	$(OBJDIR)/history.o \
	$(OBJDIR)/ingame.o \
	$(OBJDIR)/savegame.o \
	$(OBJDIR)/arpro.o \
	$(OBJDIR)/bld.o \
	$(OBJDIR)/debug.o \
	$(OBJDIR)/config.o \
	$(OBJDIR)/confile.o \
	$(OBJDIR)/files.o \
	$(OBJDIR)/newmem.o \
	$(OBJDIR)/cpuid.o \
	$(OBJDIR)/cpumain.o \
	$(OBJDIR)/emumain.o \
	$(OBJDIR)/demos.o \
	$(OBJDIR)/timer.o \
	$(OBJDIR)/soundcfg.o \
	$(OBJDIR)/speed_hack.o \
	$(OBJDIR)/savepng.o \
 	$(OBJDIR)/loadroms.o \
	$(OBJDIR)/bezel.o

ifdef RAINE32
    CORE += $(OBJDIR)/translate.o
endif

ifdef DARWIN
	CORE += $(OBJDIR)/SDLMain.o
endif

UNZIP = $(OBJDIR)/mini-unzip/unzip.o \
	$(OBJDIR)/mini-unzip/ioapi.o

D7Z = $(OBJDIR)/7z
P7Z = $(D7Z)/7zAlloc.o \
	  $(D7Z)/7zBuf2.o \
	  $(D7Z)/7zBuf.o \
	  $(D7Z)/7zCrc.o \
	  $(D7Z)/7zCrcOpt.o \
	  $(D7Z)/7zDec.o \
	  $(D7Z)/7zFile.o \
	  $(D7Z)/7zIn.o \
	  $(D7Z)/7zStream.o \
	  $(D7Z)/Bcj2.o \
	  $(D7Z)/Bra86.o \
	  $(D7Z)/Bra.o \
	  $(D7Z)/CpuArch.o \
	  $(D7Z)/LzmaDec.o \
	  $(D7Z)/Ppmd7.o \
	  $(D7Z)/Ppmd7Dec.o \
	  $(D7Z)/Lzma2Dec.o \
	  $(D7Z)/7zMain.o

ifndef SDL
CORE += $(OBJDIR)/alleg/jpg/jpeg.o \
	$(OBJDIR)/alleg/dsw.o \
	$(OBJDIR)/alleg/png/loadpng.o

else
CORE +=	$(OBJDIR)/sdl/dsw.o $(OBJDIR)/sdl/png.o
endif

ifndef RAINE_DOS
CORE += $(OBJDIR)/sdl/SDL_gfx/SDL_framerate.o
endif

ifdef SDL
CORE += \
	$(OBJDIR)/sdl/SDL_gfx/SDL_rotozoom.o \
	$(OBJDIR)/sdl/SDL_gfx/SDL_gfxPrimitives.o
endif

# Mame Support (eeprom and handlers for the sound interface)

MAME=	$(OBJDIR)/mame/memory.o \
	$(OBJDIR)/mame/eeprom.o

NEOCD =                       \
    $(OBJDIR)/neocd/pd4990a.o \
    $(OBJDIR)/neocd/cdrom.o   \
    $(OBJDIR)/neocd/cache.o   \
    $(OBJDIR)/neocd/cdda.o    \
    $(OBJDIR)/neocd/iso.o     \
	$(OBJDIR)/neocd/neocd.o

OBJS +=	 \
	$(VIDEO) \
	$(SOUND) \
	$(CORE) \
	$(UNZIP) \
	$(MAME) \
	$(P7Z) \
	$(GUI) \
	$(GAMES) \
	$(SYSDRV) \
	$(DEBUG)

ifdef SDL
OBJS +=	$(OBJDIR)/sdl/blit.o \
	$(OBJDIR)/sdl/display.o \
	$(OBJDIR)/sdl/winpos.o \
	$(OBJDIR)/sdl/compat.o \
	$(OBJDIR)/sdl/control.o \
	$(OBJDIR)/sdl/opengl.o \
	$(OBJDIR)/math/matrix.o \
	$(OBJDIR)/sdl/glsl.o \
	$(OBJDIR)/sdl/profile.o

ifndef NO_ASM
OBJS +=  $(OBJDIR)/sdl/gen_conv.o
endif

else
OBJS +=	$(OBJDIR)/alleg/blit.o \
	$(OBJDIR)/alleg/control.o \
	$(OBJDIR)/alleg/display.o \
	$(OBJDIR)/alleg/profile.o

endif

ifdef STATIC
LIBS = $(LIBS_STATIC)
CFLAGS += -DALLEGRO_STATICLINK
endif
ifdef RAINE_DEBUG
LIBS = $(LIBS_DEBUG)
# Uncomment only if you want to debug the cpu cores
# AFLAGS += -g
endif

ifdef X86_64
AFLAGS += -m amd64
endif

ifdef SEAL
OBJS += $(OBJDIR)/seal/sasound.o
CFLAGS += -DSEAL
else
ifdef RAINE_DOS
OBJS += $(OBJDIR)/alleg/sasound.o
CFLAGS += -DALLEGRO_SOUND
else
# avoid allegro when we can, sdl is much more reliable for sound
OBJS += $(OBJDIR)/sdl/sasound.o

ifdef DARWIN
# Official SDL1.2 frameworks (SDL / image / ttf) in /Library/Frameworks
CFLAGS += -I/usr/local/include/SDL/ -DDARWIN
ifdef FRAMEWORK
LIBS += -framework SDL -framework SDL_ttf -framework SDL_image -framework Cocoa -framework OpenGL
LIBS += -framework SDL_sound -framework intl -liconv
else
LIBS += -lSDL -lSDL_ttf -lSDL_image -framework Cocoa -framework OpenGL
LIBS += -lSDL_sound -lintl -liconv
endif
AFLAGS = -f macho -O1 -D__RAINE__ -DRAINE_UNIX -DDARWIN
SFLAGS += -DDARWIN
CFLAGS_MCU += -DDARWIN
LFLAGS += -Wl,-no_pie,-allow_heap_execute,-no_compact_unwind
else  #DARWIN
CFLAGS += $(shell sdl-config --cflags)
ifdef RAINE32
# I was unable to build a dll for SDL_sound or FLAC. So they must be here first
ifdef HAS_NEO
ifdef CROSSCOMPILE
  LIBS += -lSDL_sound -lFLAC # -lmodplug
else
LIBS += /usr/local/lib/libSDL_sound.a /usr/local/lib/libFLAC.a /usr/local/lib/libsmpeg.a
endif #CROSSCOMPILE
endif #HAS_NEO
endif #RAINE32
LIBS += $(shell sdl-config --libs) -lSDL_ttf -lSDL_image # -lefence
ifdef HAS_NEO
ifdef RAINE_UNIX
ifeq (,$(wildcard /usr/local/lib/libSDL_sound.a))
LIBS += -lSDL_sound
else
LIBS += /usr/local/lib/libSDL_sound.a -lFLAC -lvorbisfile
endif
else
# windows
# and these libs are used by SDL_sound/FLAC
LIBS += -logg -lvorbisfile -lws2_32 -lintl
endif
endif # HAS_NEO
endif
endif
endif

all:	source/version.h cpuinfo message maketree depend $(RAINE_EXE) \
	locale/raine.pot \
	locale/fr/LC_MESSAGES/raine.mo \
	locale/es/LC_MESSAGES/raine.mo\
	locale/pt/LC_MESSAGES/raine.mo

locale/raine.pot:
	xgettext --omit-header -C -k_ -kgettext -d raine -s -o locale/tmp `find source -name '*.c*'`
	cat locale/header locale/tmp > locale/raine.pot
	rm -f locale/tmp

locale/fr/LC_MESSAGES/raine.mo: locale/french.po
	msgfmt -c -v -o $@ $<

locale/es/LC_MESSAGES/raine.mo: locale/es.po
	msgfmt -c -v -o $@ $<

locale/pt/LC_MESSAGES/raine.mo: locale/pt.po
	msgfmt -c -v -o $@ $<

CFLAGS_BS := -Wall -O2 $(shell sdl-config --cflags) $(INCDIR) -DSTANDALONE -DNO_GZIP -c

# Using gcc here instead of $(CC) because we don't want a 32 bit binary in
# an amd64 arch.
byteswap: $(OBJDIR)/byteswap.o $(OBJDIR)/files_b.o $(OBJDIR)/newmem_b.o
	gcc -o byteswap $^

$(OBJDIR)/byteswap.o: source/byteswap.c
	gcc $(CFLAGS_BS) -DSDL -o $@ $<

$(OBJDIR)/files_b.o: source/files.c
	gcc $(CFLAGS_BS) -DSDL -o $@ $<

$(OBJDIR)/newmem_b.o: source/newmem.c
	gcc $(CFLAGS_BS) -DSDL -o $@ $<

depend:
	@echo dependencies : if you get an error here, install the required dev package
ifndef RAINE_DOS
	@echo -n libpng:
	@libpng-config --version
	@echo -n SDL:
	@sdl-config --version
endif
ifdef RAINE_UNIX
ifndef SDL
	@echo -n allegro:
	@allegro-config --version
endif
endif

$(wildcard /usr/local/lib/libSDL_sound.a)

#ifeq (,$(wildcard /usr/local/lib/libSDL_sound.a))
#	@echo using system SDL_sound (check that it uses libmpg123)...
#else
#	@echo using local static SDL_sound
#endif

source/version.h: makefile
# I have just removed the stuff about gcc --version.
# Too much trouble with it. And I didn't know the __GNUC__ macros...
ifeq ($(OSTYPE),dos)
ifdef CROSSCOMPILE
	@echo "#define VERSION \"$(VERSION)\"" > source/version.h
else
# The dos seems too stupid to redirect stderr to a file (lame command.com).
# Usually I use 4dos for that, but since most people don't I use redir here
# which is in the standard djgpp install...
# Even with bash installed it does not work (it calls the dos shell instead
# of sh).
	@djecho '#define VERSION $(VERSION)' > source/version.h
endif
else
# Carefull for the windows version you need sh.exe and echo.exe !
	@echo "#define VERSION \"$(VERSION)\"" > source/version.h
endif

ifdef RAINE32

# Add a nice little icon...

$(OBJDIR)/raine.res:	source/raine.rc
	$(WINDRES) -O coff -o $(OBJDIR)/raine.res -i source/raine.rc
endif

message:
ifdef RAINE_DEBUG
	@echo -n Building Raine, debug version
else
	@echo -n Building Raine, Fully optimized version
endif
ifdef GFX_SVGALIB
	@echo -n " with svgalib support"
endif
	@echo " with $(CC) for $(OSTYPE) CPU=$(CPU)"
ifndef ASM_VIDEO_CORE
	@echo "WARNING : move functions do not exist in the c"
	@echo "          video core. Using the asm functions for these..."
endif

ifdef RAINE32
$(RAINE_EXE):	$(OBJS) $(OBJDIR)/raine.res
else
$(RAINE_EXE):	$(OBJS)
endif

	@echo Linking Raine...
	$(LDV) $(LDFLAGS) $(LFLAGS) -g -Wall -Wno-write-strings -o $(RAINE_EXE) $^ $(LIBS)

$(D7Z)/%.o: source/7z/%.c
	@echo Compiling 7z $<...
	$(CCV) $(CFLAGS) -MD -c $< -D_7ZIP_PPMD_SUPPPORT -o $@
	@cp $(D7Z)/$*.d $(D7Z)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(D7Z)/$*.d >> $(D7Z)/$*.P; \
            rm -f $(D7Z)/$*.d

tags:
	ctags -R source

converter: source/bonus/converter.c
	$(CCV) $(CFLAGS) -c $< -o $(OBJDIR)/converter.o
ifdef RAINE_UNIX
	$(CCV) $(LFLAGS) -g -Wall -Wno-write-strings -o converter $(OBJDIR)/converter.o $(shell allegro-config --libs) -lz
else
	$(CCV) $(LFLAGS) -g -Wall -Wno-write-strings -o converter $(OBJDIR)/converter.o -lalleg -lz
endif

ASM020: $(ASM020)

VIDEO: $(VIDEO)

grabber: raine.dat
	   @echo Editing datafile...
	   grabber raine.dat

compress: $(RAINE_EXE)
	   @strip $(RAINE_EXE)
	   @echo Appending datafile...
	   exedat -a -c $(RAINE_EXE) raine.dat
	   upx -9 $(RAINE_EXE)

# compile object from standard c

$(OBJDIR)/%.o: source/%.m
	@echo Strange apple nib file $<...
	$(CCV) $(CFLAGS) -MD -c $< -o $@

$(OBJDIR)/%.o: source/%.c
	@echo Compiling $<...
	$(CCV) $(CFLAGS) -MD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
            rm -f $(OBJDIR)/$*.d

$(OBJDIR)/%.o: source/%.cpp
	@echo Compiling c++ $<...
	$(CXXV) $(CFLAGS) -MD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
            rm -f $(OBJDIR)/$*.d

-include $(OBJS:%.o=%.P)

# compile object from at&t asm

$(OBJDIR)/%.o: source/%.s
	@echo Assembling $<...
	$(CCV) $(SFLAGS) -c $< -o $@

# compile at&t asm from standard c

$(OBJDIR)/%.s: source/%.c
	@echo Compiling $<...
	$(CCV) $(CFLAGS) -S -c $< -o $@

# compile object from intel asm

# Rules to make video asm files...
$(OBJDIR)/%.o: source/%.asm
	@echo Assembling $<...
	$(ASM) -MD $(OBJDIR)/$*.d -o $@ $(AFLAGS) $<
	@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
            rm -f $(OBJDIR)/$*.d
# generate s68000.asm

$(OBJDIR)/68000/s68000.o: $(OBJDIR)/68000/s68000.asm
	@echo Assembling $<...
	$(ASM) -MD $*.d -o $@ $(AFLAGS) $<
	@cp $*.d $*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
            rm -f $*.d

ifdef CROSSCOMPILE
$(OBJDIR)/68000/s68000.asm: $(NATIVE)/object/68000/star.exe
	cp -fv $(NATIVE)/object/68000/star.exe $(OBJDIR)/68000/
else
$(OBJDIR)/68000/s68000.asm: $(OBJDIR)/68000/star.o
	$(CCV) $(LFLAGS) -o $(OBJDIR)/68000/star.exe $(OBJDIR)/68000/star.o
endif
# Notice : you can pass -addressbits 32 to star.exe to avoid addresses
# masks and win a few instructions. It works for most games, but not all of
# them, 1941 is a good example of a game which can't work with that, crash
# just after the hardware tests, just before the title screen with "pc out
# of bounds" in the console. So it's not used for now.
	$(OBJDIR)/68000/star.exe -hog $@

ifndef CZ80
# generate mz80.asm

$(OBJDIR)/z80/mz80.o: $(OBJDIR)/z80/mz80.asm
	@echo Assembling $<...
	$(ASM) -MD $*.d -o $@ $(AFLAGS) $<
	@cp $*.d $*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
            rm -f $*.d

ifdef CROSSCOMPILE
$(OBJDIR)/z80/mz80.asm: $(NATIVE)/object/z80/makez80.exe
	cp -fv $(NATIVE)/object/z80/makez80.exe $(OBJDIR)/z80/
else
$(OBJDIR)/z80/mz80.asm: $(OBJDIR)/z80/makez80.o
	$(CCV) $(LFLAGS) -s -o $(OBJDIR)/z80/makez80.exe $<
endif
ifdef DARWIN
	@$(OBJDIR)/z80/makez80.exe -s -cs -x86 $@
else
ifndef RAINE_UNIX
	@$(OBJDIR)/z80/makez80.exe -s -cs -x86 $@
else
	$(OBJDIR)/z80/makez80.exe -l -s -cs -x86 $@
endif
endif

endif # ifndef CZ80

# generate m6502.asm

$(OBJDIR)/6502/m6502.o: $(OBJDIR)/6502/m6502.asm
	@echo Assembling $<...
	$(ASM) -MD $*.d -o $@ $(AFLAGS) $<
	@cp $*.d $*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
            rm -f $*.d

$(OBJDIR)/6502/m6502.asm: $(OBJDIR)/6502/make6502.o
	@echo Building M6502 $(OBJDIR)...
ifdef CROSSCOMPILE
	cp -fv $(NATIVE)/object/6502/make6502.exe $(OBJDIR)/6502/
else
	$(CCV) $(LFLAGS) -o $(OBJDIR)/6502/make6502.exe $(OBJDIR)/6502/make6502.o
endif
ifdef DARWIN
	$(OBJDIR)/6502/make6502.exe -s -6510 $@
else
ifdef RAINE_UNIX
	$(OBJDIR)/6502/make6502.exe -l -s -6510 $@
else
	$(OBJDIR)/6502/make6502.exe -s -6510 $@
endif
endif

# This one is for a bug in gcc-4.8.3, 4.8.4 and 4.9.2 at least
# just launch kazan or iganinju, the sound effects are bad while the demo
# is playing -O is ok, -O1 has already the bug !
ifndef RAINE_DEBUG
$(OBJDIR)/sound/adpcm.o: source/sound/adpcm.c
	@echo Compiling less optimized $<...
	$(CCV) -O $(INCDIR) $(INCDIR) $(DEFINE) $(_MARCH) -Wall -Wno-write-strings -g -MD -c $< -o $@
	@cp $*.d $*.P; \
            sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
            rm -f $*.d
endif

# Notice : the following fix is specific to the frame pointer optimisation
# of gcc 2.81 and higher (< 3.00)

# kiki kai kai gcc bug

ifeq ($(GCC_MAJOR), 2)
$(OBJDIR)/games/kiki_mcu.o: source/games/kiki_mcu.c
	@echo Compiling mcu $<...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

# Same for kick and run...

$(OBJDIR)/games/kick_mcu.o: source/games/kick_mcu.c
	@echo Compiling mcu $<...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@
endif

ifeq ($(GCC_MAJOR),3)
# This one happens for gcc < 3.2.1 (even 3.2.0)
$(OBJDIR)/sound/ymf278b.o: source/sound/ymf278b.c
	@echo Compiling WITH frame pointer $<...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

$(OBJDIR)/games/bubl_mcu.o: source/games/bubl_mcu.c
	@echo "Compiling $< (gcc-3.3 bug work around)..."
	$(CCV) $(INCDIR) $(DEFINE) $(_MARCH) -c $< -o $@
endif

# SDL redefines the main function for windows programs, so we need to
# explicitely compile the cpu emulators without SDL (or link them with it
# which would be useless).

$(OBJDIR)/68000/star.o: source/68000/star.c
	@echo Compiling StarScream...
	$(CCV) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

ifndef CZ80
$(OBJDIR)/z80/makez80.o: source/z80/makez80.c
	@echo Compiling mz80...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@
endif

$(OBJDIR)/6502/make6502.o: source/6502/make6502.c
	@echo Compiling make6502...
	$(CCV) $(INCDIR) $(DEFINE) $(CFLAGS_MCU) -c $< -o $@

cpuinfo:
	@sh ./detect-cpu


# create directories

$(OBJDIRS):
ifndef OSTYPE
	@echo Your OSTYPE is not defined.
	@echo "If you are in Unix/Linux, make sure you are using bash/sh."
	@echo 'If this is the case, try to export OSTYPE : export OSTYPE=$OSTYPE'
	@echo "If not, you can type (for dos/windows) :"
	@echo "set OSTYPE=dos"
	@echo "before make."
	@exit 1
else
	$(MD) -p $@
endif

maketree: $(OBJDIRS)

# remove all object files

clean:
	@echo Deleting object tree ...
	$(RM) -r $(OBJDIR)
	@echo Deleting $(RAINE_EXE)...
	$(RM) $(RAINE_EXE) make.dep
#	$(RM) cpuinfo

vclean:
	@echo make vclean is no longer necessary, just type make clean

# Installation part (Only for Unix)
install: install_dirs $(RAINE_LNG) $(RAINE_EXE)
	strip $(RAINE_EXE)
ifdef RAINE_UNIX
	@echo installing $(RAINE_EXE) in $(bindir)
	$(INSTALL_BIN) $(RAINE_EXE) $(bindir)
ifndef SDL
	$(INSTALL_DATA) $(RAINE_DAT) $(rainedata)
else

	@echo installing fonts in $(fonts_dir)
	$(INSTALL_DATA) fonts/Vera.ttf fonts/10x20.fnt fonts/VeraMono.ttf fonts/font6x8.bin $(fonts_dir)
	@echo installing bitmaps in $(bitmaps_dir)
	$(INSTALL_DATA) bitmaps/cursor.png bitmaps/raine_logo.png $(bitmaps_dir)
	@echo installing shaders in $(shaders_dir)
	$(INSTALL_DATA) shaders/* $(shaders_dir)
	$(INSTALL_DATA) scripts/neocd/* $(scripts_dir)
#	$(INSTALL_DATA) blend/* $(bld_dir)
endif
	sh -c "if [ -f hiscore.dat ]; then install hiscore.dat $(rainedata); fi"
	sh -c "if [ -f command.dat ]; then install command.dat $(rainedata); fi"
	sh -c "if [ -f history.dat ]; then install history.dat $(rainedata); fi"
	$(INSTALL_DATA) config/debug_dips.txt $(rainedata)
	$(INSTALL_DATA) config/cheats.cfg $(rainedata)
ifndef DARWIN
	$(INSTALL_DATA) raine.desktop $(prefix)/share/applications
endif
	$(INSTALL_DATA) raine.png $(prefix)/share/pixmaps
	$(INSTALL_DATA) config/neocheats.cfg $(rainedata)
	@cp -rfv locale/fr locale/es /locale/pt $(langdir)
ifndef DARWIN
	$(INSTALL_DATA) neoraine.desktop $(prefix)/share/applications
endif
	$(INSTALL_DATA) neoraine.png $(prefix)/share/pixmaps
ifdef DARWIN
	@echo creating package $(DESTDIR)
	@cp Info.plist $(prefix)
	@cp new_logo.icns $(sharedir)
endif

install_dirs:
	$(MD) -p $(bindir) $(rainedata) $(langdir) $(romdir) $(artdir) $(emudxdir) $(prefix)/share/pixmaps
	$(MD) -p $(prefix)/share/applications $(bitmaps_dir) $(fonts_dir) $(scripts_dir) $(shaders_dir)

$(RAINE_LNG):
	$(INSTALL_DATA) config/language/$@ $(langdir)

else
	@echo There is no needs to install for a win32/dos system
endif


uninstall:
ifdef RAINE_UNIX
	$(RM) $(bindir)/$(RAINE_EXE)
	$(RM) $(rainedata)/$(RAINE_DAT)
	$(CD) $(langdir); rm -f $(RAINE_LNG)
	$(RD) $(langdir) $(romdir) $(emudxdir) $(artdir) $(rainedata)

else
	@echo There is no needs to uninstall for a win32/dos system
endif

