#!/usr/bin/perl

# Equivalent of the i386 version, but for C files this time
#
# Syntax : perl gen_size.pl < input > output

use strict;

while (<>) {
  s/16x16/16x8/g;
  s/yy\<16/yy\<8/;
  s/yy\=15/yy\=7/;
  print;
}

