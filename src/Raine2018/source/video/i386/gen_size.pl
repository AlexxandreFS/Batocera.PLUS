#!/usr/bin/perl

# generates a 16x8.s asm file from a 16x16 one (there are 4 files to generate)
# this could maybe be done with C macros instead, but these macros are really unreadable
# and this kind of asm code is already hard to read by itself, so a perl script here
# seems like the perfect solution.
# We'll just need to remember to use it to regenerate the 16x8 files in case we update
# the 16x16 ones !

# Syntax : perl gen_size.pl < input > output

use strict;

while (<>) {
  s/16x16/16x8/g;
  s/16\*16/16\*8/g;
  s/movl\t\$16,/movl\t\$8,/;
  s/addl\t\$15\*4,/addl\t\$7\*4,/;
  print;
}

