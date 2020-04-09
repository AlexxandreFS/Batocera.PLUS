Motorola M68705 static recompiler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Copyright (c) 1999 Richard Mitton (richard.mitton@bigfoot.com)
Visit the Emulator Technology Centre at http://etc.home.dhs.org/

This is the source code to my M68705 static recompiler that I wrote for Raine.
I've placed this code in the public domain, do what you will with it but
please give me some credit if you use it.

In this .zip you will find:
   readme.txt     - this file
   makefile       - use this to compile it all
   dasm.c         - command-line disassembler
   conv.c         - .asm to .c convertor
   example.rom    - an example 68705 ROM file
   post.bat       - run this to optimise the output
   post1.awk      - post-process pass 1
   post2.awk      - post-process pass 2

I'd like to point out this code is very dodgy.
You'll need GCC (or DJGPP) for this to work, as it uses a GCC extension.
p.s. you really have to know what you're doing to get this to work fully.

Usage
~~~~~
First, run make to compile it all.

Next, get your ROM dump. It should be 2048 bytes for the standard 68705.
Some dumps are only 1920 bytes. In this case, you need to put 128 bytes of
padding onto the beginning of the file.

Then disassemble it. Use DASM.EXE to do this (e.g. DASM example.rom example.asm)

Now you have a disassembly. Be warned that if the code has data mixed into it,
it may have disassembled some of the data as code. If this is the case, you
need to hand-edit the disassembly yourself :-(

In order to reduce code size, you can edit the diassembly and remove the empty
code from the end. Most ROMs are padded with 0x00, which gets disassembled to
the 'brset' instruction or something similiar. You will see a lot of these
in a row at the end of the disassembly. You can safely remove those lines as
they will not be needed.

Now you can recompile it. Use CONV.EXE to convert the .asm to a .c file.
Usage is 'CONV prefix input.asm output.c'. The prefix parameter is what
gets put in front of all the symbols, so that if you emulate more than 1 MCU
then they won't clash.

The code generated as-is is designed to slot straight into Raine. You probably
want to edit the CONV.C file and customise the headers etc that are emitted.

If you want to speed the final code up, run the POST.BAT on the outputted .c
file. You'll need AWK to do this though. It goes through and removes the
un-needed labels, which allows GCC to optimise it better.

**IMPORTANT**

This code was written solely to emulate Bubble Bobble. However, it's since
been hacked into other games such as Kiki Kai Kai. Bubble Bobble uses the
instruction 'BIH' to sync to the vertical blank. So, I used this as a counter
to know when to exit the loop. (otherwise, the mcu code would never return).

But, Kiki Kai Kai and others don't use this BIH instruction, so I had to patch
the recompiled code to (a) call the interrupt code once per frame, and (b)
actually exit the loop. You should really examine the files KIKI_MCU.C in the
Raine source code to get a good idea of how I did this.

Example
~~~~~~~
Do this to get a feel of it:
first run 'make'
dasm example.rom example.asm

Edit example.asm, and remove the code from addresses 0x3aa to 0x7ff inclusive.
It's not actually proper code, so is safe to remove.

conv Example example.asm example.c
post example.c       (only if you have GNU awk, don't worry if you don't)

The example.c file is now ready for use.

Calling method
~~~~~~~~~~~~~~
void Example_mcu_reset(void);

Call this once at startup, before using the MCU. Also call whenever you do
a reset.

void Example_mcu(int bih_count);

Call this once per frame. bih_count is how many BIH instructions should be
executed before quitting the loop.
If your target game doesn't use the BIH instruction in this way (and it most
probably doesn't), you have to put a hack somewhere in the recompiled code
to make it actually quit once per frame.
See the Raine source code for how this can be done.

Somewhere in your source you need to put these declarations in too:

M68705 m68705;
void *m68705_jump_table[0x800];

Enjoy =)
