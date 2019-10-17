#!/usr/bin/perl -w

# Rotizifier : converts all style Drawxxx to Drawxxx_Rot
# and map_palette to map_palette_new

# in the end the converted script is moved to the current directory,
# the old one is placed in old.

# Knows about JumpListR and MAP_PALETTE_MULTI_xxx

# Syntax : perl rotizifier <filename>
# put the converted source in new/filename
# and then moves it to replace the old file (system mv)

use strict;

my %corresp =
  (
   "Map_24bit_xRGB" => "col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb",
   "Map_12bit_RGBxxxxx" => "col_map_12bit_rgbxxxx",
   "Map_12bit_RGBx" => "col_map_rrrr_gggg_bbbb_xxxx",
   "Map_15bit_xRGB" => "col_map_xrrr_rrgg_gggb_bbbb",
   "Map_15bit_xBGR" => "col_map_xbbb_bbgg_gggr_rrrr",
   "Map_12bit_xBGR_Rev" => "col_map_xxxx_bbbb_gggg_rrrr_rev",
   "Map_15bit_RRRRGGGGBBBBRGBx" => "col_Map_15bit_RRRRGGGGBBBBRGBx",
   "Map_12bit_xBGR" => "col_map_xxxx_bbbb_gggg_rrrr",
   "Map_12bit_xxxxRRRRGGGGBBBB_Rev" => "col_map_12bit_xxxxRRRRGGGGBBBB_Rev",
  );

my $warn_rot = 0;

mkdir "old",0777;
mkdir "new",0777; # Better be sure these exist...

while ((my $name = shift @ARGV)) {
  print "file $name\n";
  # Grab the mapper(s)
  my $draw8h = 0;
  my $mapper = undef;
  open(F,"<$name") || die "File $name not found ??!";
  while (<F>) {
    if (/^[ \t]*MAP_PALETTE_MAPPED_NEW/) {
      print STDERR "$name already new style !\n";
      last;
    }
    if (/MAP_PALETTE_(MULTI_)?MAPPED\(/) {
      # Let's hope that the same syntax was kept everywhere...
      my $temp = <F>; # next line
      chomp $temp;
      $temp =~ s/^[ \t]*([\w_\d]+).*/$1/; # Extract what we need...
      if (!$mapper) {
	$mapper = $temp;
      } elsif (!($mapper eq $temp)) {
	print STDERR "mappers found $mapper and then $temp\n";
	die "stopping";
      }
    } elsif (/(\w+) *\= *MAP_PALETTE\(/) {
      my $temp = <F>; # next line
      chomp $temp;
      $temp =~ s/^[ \t]*([\w_\d]+).*/$1/; # Extract what we need...
      if (!$mapper) {
	$mapper = $temp;
      } elsif (!($mapper eq $temp)) {
	print STDERR "mappers found \"$mapper\" and then2 \"$temp\"\n";
	die "stopping";
      }
    } elsif (/mapper[ \t]*\=[ \t]*\&([\w_\d]+)/) {
      if (!$mapper) {
	$mapper = $1;
      } elsif (!($mapper eq $1)) {
	print STDERR "mappers found $mapper and then $1\n";
	die "stopping";
      }
    } elsif (/Draw.+_Rot/) {
      $warn_rot = 1;
    } elsif (/Draw8xH/) {
      $draw8h = 1;
    }
  }
  close(F);
  if ($mapper) {
    print STDERR "Mapper correctly extracted : $mapper\n";
  } else {
    print STDERR "no mapper found\n";
    next;
  }
  if ($warn_rot) {
    print STDERR "WARNING : Draw_xxx_Rot already present...\n";
  }

  chomp $mapper;
  $mapper = $corresp{$mapper};
  #die "Unknown mapper" if (!$mapper);

  # Rewrite in new
  open(F,"<$name") || die "File $name not found ??!";
  open(G,">new/$name");
  while (<F>) {
    if (/^([ \t]*)InitPaletteMap/) {
      print G "$1set_colour_mapper(&",$mapper,");\n";
    } elsif (/^([ \t]*)MAP_PALETTE_(MULTI_)?MAPPED\(/) {
      my $tab = $1;
      print G $tab,"MAP_PALETTE_$2MAPPED_NEW(\n";
      <F>; # bye bye mapper
      $_ = <F>;
      print G $_; # bank
      $_ = <F>;
      print G $_; # colors
      $_ = <F>;
      print G $_; # map
      $_ = <F>; # close
    } elsif (/^([ \t]*)(\w+) *\= *MAP_PALETTE\(/) {
      my $tab = $1;
      my $var = $2;
      print G $tab,"MAP_PALETTE_MAPPED_NEW(\n";
      <F>; # bye bye mapper
      $_ = <F>;
      print G $_; # bank
      $_ = <F>;
      chomp;
      if (!(/\,/)) {
	$_ .= ",";
      }
      print G $_; # colors
      print G "$tab  $var\n"; # map
      $_ = <F>; # close
    } elsif (/Draw(\d[\w\d_]+?)\(/) {
      my $type = $1;
      if (!($type =~ /_Rot/)) {
	s/Draw(.+?)\(/Draw$1_Rot\(/;
      }
    } elsif (/Draw(\d[\w\d_]+?)JumpListR\[/) {
      my $type = $1;
      if (!($type =~ /_Rot/)) {
	s/Draw(.+?)JumpListR\[/Draw$1Flip_Rot\[3\-/;
      }
    } elsif (/VIDEO_ROTAT/) {
      if (!/VIDEO_ROTATABLE/ && !$draw8h) { # After all, Rot means Rotatable
	# Carefull Draw8xH does not support rotation for now because :
	# 1) its ram buffer is generated on the fly, so it can't be pre-
	#    rotated
	# 2) with a 90° rotation, it should draw rows, not columns !!!

	s/\,/\| VIDEO_ROTATABLE\,/;
      }
    }
    print G $_;
  }
  close(G);
  close(F);

  system("mv $name old");
  system("mv new/$name .");
}

