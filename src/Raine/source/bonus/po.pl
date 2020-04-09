#!/usr/bin/env perl

use strict;

# Script to try to tag strings to translate in the sources
# It's called with a list of files to process in parameter, like
# po.pl `find source -name '*.c*'`
# The problem is that it's not some kind of magic wand and it will tag too many
# things by default, so some files must be restored manually after this, and
# there are quite a few, so use this with cautious !

my $file;
my $func = 0;
$| = 1;
while ($file = shift @ARGV) {
	next if ($file =~ /(alleg\/|confile.c|megasys1.c|psyforce.c|games\/tc\d|console\/)/);
	open(F,"<$file") || die "can't open $file\n";
	print "$file ... ";
	open(G,">truc.cpp");
	my $rep = 0;
	my $active = 0;
	while (<F>) {
		if (!$active) {
			if ((/(menu_item_t|DEF_INPUT_EMU|DSW_DATA) .*\=/ && !/;/) || # Declaration of a struct
				(/\= new /) || # Declaration of an object...
				(/\= ?"/ && !/\.[\w_]+ ?\= *"/)) { # Direct string affectation
				$active = 1;
			}
		}
	   	if (!$func) {
			if (/(print_ingame|print_menu_string|MessageBox|print_tf_state|add_layer_info|load_progress|load_message) *\(/) { # specific function
				$func = 1;
			}
		}

		# remove eventual _("...") already inserted...
		if ($active || ($func && $file =~ /cpp$/)) {
			$rep -= s/(gettext|_)\("((.|\n)+?)"\)/"$2"/g;
			$rep += s/"((.|\n)+?)"/_("$1")/g;
			$rep -= s/_\("([^a-zA-Z]+?)"\)/"$1"/g; # remove no chars
			$rep -= s/_\("(.+?\....)"\)/"$1"/g; # remove file with extension
		} elsif ($func) {
			$rep -= s/(gettext|_)\("((.|\n)+?)"\)/"$2"/g;
			$rep += s/"((.|\n)+?)"/gettext("$1")/g;
			$rep -= s/gettext\("([^a-zA-Z]+?)"\)/"$1"/g; # remove no chars
			$rep -= s/gettext\("(.+?\....)"\)/"$1"/g; # remove file with extension
		}
		if (/;/) {
			$active = 0;
			$func = 0;
		}
		print G;
	}
	close(F);
	if ($rep) {
		print "replacements $rep\n";
		unlink $file;
		rename "truc.cpp",$file;
	}
}

