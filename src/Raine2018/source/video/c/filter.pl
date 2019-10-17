#!/usr/bin/perl

while (<>) {
  s/ \\$//;
  s/[ \t]+$//;
  s/\#\#SIZE..x..SIZE../16x16/;
  s/\(.+\)//;
  s/void //;
  chomp;
  s/\#\#//g;
  my $bis = $_;
  s/_DEPTH//;
  $bis =~ s/DEPTH/8/;
  print "#define $_ $bis\n";
  s/16x16/8x8/;
  $bis =~ s/16x16/8x8/;
  print "#define $_ $bis\n";
}

