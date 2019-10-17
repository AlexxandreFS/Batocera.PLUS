#!/usr/bin/perl

# Convert mostly what other scripts don't : WRITE_HANDLER syntax (horrible),
# and GFX_LAYOUT mostly.

use strict;
use genres;

$| = 1;
my $cps2_mode;
my $cps1_mode;

while (<>) {
	if (!$cps1_mode && !$cps2_mode) {
		if (/\( cps1_/) {
			$cps1_mode = 1;
		} elsif (/\( cps2_/) {
			$cps2_mode = 1;
		}
	}
	if (s/READ8?_HANDLER\((.+)\)/UINT8 $1\(UINT32 offset\)/ ||
		s/READ16_HANDLER\((.+)\)/UINT16 $1\(UINT32 offset\)/ ||
		s/WRITE8?_HANDLER\((.+)\)/void $1\(UINT32 offset, UINT8 data\)/ ||
		s/WRITE16_HANDLER\((.+)\)/void $1\(UINT32 offset, UINT16 data\)/) {
		chomp;
		my $line = <>;
		if ($line =~ /^\{/) {
			print "$_ {\n";
			while (<>) {
				print;
				last if ($_ =~ /^\}/);
			}
			print "\n";
		} else {
			print "$_\n";
			$_ = $line;
			redo;
		}
	}

	# copy the gfxlayouts blocks
	if (/GfxLayout.+\=/) {
		print;
		while (<>) {
			print;
			chomp;
			last if ($_ eq "};");
		}
		print "\n";
	}

	# convert gfxdecodeinfo stuff
	if (s/GfxDecodeInfo(.+\=)/GFX_LIST$1/) {
		print;
		while (<>) {
			my ($region, $start,$layout,$start_col,$banks) = split(/\, ?/);
			if ($banks) {
				$banks =~ s/ ?\}//;
				print "$region, $layout }, // $banks color banks\n";
				if ($start > 0) {
					print STDERR "WARNING : GfxDecodeInfo has $region starting at $start\nYou will have to manually adjust this.\n";
				}
			} else {
				s/\-1/0\, NULL/;
				print;
			}
			chomp;
			last if ($_ eq "};");
		}
		print "\n";
	}
	if (/^(GAME|CONS)\( (.+) ?\)/) {
		my $func = $1;
		my $string = $2;
		while ($string =~ s/"(.+?),(.+?)", *"(.+)" *,/"$1\£$2", "$3",/g) {}
		while ($string =~ s/"(.+?)", *"(.+?),(.+?)" *,/"$1", "$2\£$3",/g) {}

		my ($year,$name,$parent,$machine,$input, $class, $init,
			$rot,$company,$long_name,$reste) = split(/\, */,$string);
		if ($func eq "CONS") {
			($year,$name,$parent,undef,$machine,$input, $class, $init,
				$company,$long_name,$reste) = split(/\, */,$string);
			$rot = "ROT0";
		}

		$long_name =~ s/\£/\,/g;
		$company =~ s/\£/\,/g;
		$name =~ s/ //g;
		$parent =~ s/ //g;
		$input =~ s/ //g;
		$rot =~ s/ //g;
		$machine =~ s/ //g;

		$company =~ s/ \/.+//;
		$company =~ s/"//g;
		$company = uc($company);
		my $genre;
		my $genre = ($parent !~ /^(0|neogeo)$/ ? genres::get_genre($parent) : genres::get_genre($name));
		if ($cps1_mode || $cps2_mode) {
			if ($rot eq "ROT0") {
				$rot = undef;
			} elsif ($rot eq "ROT270") {
				$rot = "&video_cps1_270";
			} else {
				die "angle $rot not handled yet, sorry this is a case of error\n";
			}
		}
		if ($cps1_mode) {
			my $game;
			if ($long_name =~ /(Capcom Word|Quiz )/i) {
				$game = "cps1b4_";
			} elsif ($machine =~ /qsound/) {
				$game = "qsound_";
			} elsif ($long_name =~ /Forgotten worlds|Lost Worlds/i) {
				$game = "forgottn_";
			} elsif ($name =~ /sf2/) {
				$game = "sf2_";
			} elsif ($name =~ /sfzch/) {
				$game = "sfzch_";
			} else {
				$game = "cps1_";
			}
		} elsif ($cps2_mode) {
			if ($input eq "cps2_2p6b") {
				$input = "p2b6";
			} elsif ($input eq "cps2_2p3b") {
				$input = "p2b3";
			} elsif ($input eq "cps2_4p4b") {
				$input = "p4b4";
			} elsif ($input eq "cps2_3p4b") {
				$input = "p4b4";
			} elsif ($input eq "cps2_3p3b") {
				$input = "p3b3";
			} elsif ($input eq "cybots") {
				$input = "p2b4";
			} elsif ($input eq "cps2_2p2b") {
				$input = "p2b2";
			} elsif ($input eq "cps2_2p3b") {
				$input = "p2b3";
			} elsif ($input eq "qndream") {
				$input .= "";
			} elsif ($input eq "cps2_4p2b") {
				$input = "p4b2";
			} elsif ($input eq "cps2_4p3b") {
				$input = "p4b3";
			} elsif ($input eq "cps2_1p2b") {
				$input = "p1b2";
			} elsif ($input eq "cps2_1p3b" || $input eq "choko") {
				$input = "p1b3";
			} elsif ($input eq "cps2_1p4b") {
				$input = "p1b4";
			} elsif ($input eq "cps2_2p1b" || $input eq "pzloop2") {
				$input = "p2b1";
			} elsif ($input eq "cps2_2p6bt") {
				$input = "p2b6t";
			} else {
				print "controls unknown $input\n";
				exit(1);
			}
			$input = undef if ($input eq "p2b6"); # default inputs for driver
		}
		# not working, bad clones
		next if ($cps1_mode && $machine eq "knightsb" || $machine eq "cpspicb");
		if ($parent ne "0") {
			print "CLNEI( $name, $parent, $long_name, $company, $year, $genre";
		} else {
			print "GMEI( $name, $long_name, $company, $year, $genre";
		}
		print ",\n  .input = input_$input" if ($input && $input ne $name && $input ne $parent);
		print ", .dsw = dsw_$input" if ($input && $cps1_mode && $input ne
			$name && $input ne $parent);
		print ",\n  .video = $rot" if ($rot);
		if ($cps1_mode) {
			$_ = $machine;
			my ($load,$exec) = ();
			if ($_ eq "cps1_10MHz") {
				# $load = "load_cps1_10";
				# default load, driver untouched
			} elsif (/(cps1_12MHz|wofhfh|pang3)/) {
				$load = "load_cps1_12";
			} elsif ($_ eq "qsound") {
				$load = "load_qsound";
				$exec = "execute_qsound_frame";
			} elsif (/^sf2m3$/) {
				$load = "load_sf2m3";
			} elsif ($_ eq "ganbare") {
				$exec = "execute_ganbare";
			} else {
				die "unknown machine $_\n";
			}
			print ",\n  .load_game = $load" if ($load && $load ne
				"load_$name" && $load ne "load_$parent");
			print ",\n  .exec = $exec" if ($exec && $exec ne
				"execute_$name");
		}
		print ");\n";
	}
}

