                         dZ80 Version 1.50 Source Code

                       Copyright 1996-2001 Mark Incley.

                         E-mail: dz80@inkland.demon.co.uk
                          http://www.inkland.demon.co.uk


Serious Bit
-----------

I have made this source code available so that it may be compiled on platforms
other than MS-DOS. You may compile it and distribute the resulting executable
only if no monies are charged for it.

       ** YOU ARE NOT ALLOWED TO DISTRIBUTE THIS SOFTWARE COMMERICIALLY **


Not So Serious Bit
------------------

If you make any feature modifications to the dZ80 source code, please let me
know, so that I can make them to my source too. I didn't intend for dZ80 to
grow into an all singing and dancin' disassembler, but, if features are added,
I would like to add them to the Messy-Dos version as well.


Source Code Notes
-----------------

File            Purpose
----            -------
TYPES.H         Sets up the typedefs
TABLES.C        Tables for dZ80
DZ80.C/H        Main entry point   
DISSZ80.C/H     The disassembler
DISSZ80P.H      Private dZ80 header file - check out EXAMPLE.C
PARSECMD.C/H    Command line parser
LOADFL32.C      File loader and memory allocator

DZ80.MAK        GNU makefile for 32-bit version of dZ80
MAKEFILE.UNX    Simple makefile for unix builds

SKIP.C          A self-contained dZ80 opcode map file generator by
                Raffaele Sena

EXAMPLE.C	An example of how to drop dZ80 into your own programs to gain
		a disassembler.

If you have any problems, just e-mail me on dz80@inkland.demon.co.uk

Cheers,

        Mark
