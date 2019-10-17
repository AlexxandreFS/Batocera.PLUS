#!/usr/bin/perl

# Convert all clones to new format
# that is the redundant regions are not listed anymore

use strict;

my $filename = shift @ARGV;
open(F,"<$filename") || die "syntax conv_clones.pl <file name> [ > dest ]\n";

my $romset;
my (%romsets,@clones);
while (<F>) {
	if (/ROM_INFO/) {
		if (!/.+ rom_(.+?)\[/) {
			die "format of ROM_INFO incorrect : $_";
		} else {
			$romset = $1;
			my %regions = ();
			while (<F>) {
				if (/\{ ?(.+)\ ?}/) {
					my $args = $1;
					my ($name,$size,$crc,$region_name,$offset,$method) = split(/\, ?/,$args);
					if ($method && $region_name =~ /[a-z]/i) {
						push @{$regions{$region_name}},$crc;
					}
				}
				last if (/\;/);
			}
			$romsets{$romset} = \%regions;
		}
	}

	if (/DIR_INFO/) {
		if (!/ dir_(.+)\[/) {
			die "format of DIR_INFO incorrect (expected dir_) : $_";
		} else {
			my $dir_name = $1;
			while (<F>) {
				if (/\{ ?(.+) ?\}/) {
					if (/ROMOF.+\"(.+)\"/) {
						push @clones,[$dir_name,$1];
					} elsif (!/\(/) {	# No cloneof, romof...
						if (/\"(.+)\"/) {	# get name
							if (length($1) < length($dir_name)) {
								$dir_name = $1;
							}
						}
					}
				}
				last if (/\;/);
			}
		}
	} elsif (/(CLONE|CLNE|CLNEI)\((.+)[$\)]/) {
		my $args = $2;
		my @args = split /, */,$args;
		foreach (@args) {
			s/^[ \t]*//;
			s/[ \t]*$//;
		}
		push @clones,[$args[0],$args[1]];
	}
	if (!/\#define/) { # avoid macro definitions

		if (/^CLONE.*\( (.+)\,/) { # limited support for CLONE syntax (games.h)
			my $name = $1;
			$_ = <F>;
			my ($parent) = /[ \t]+(.+)\,/;
			push @clones,[$name,$parent];
		}
	}

} # while (<F>) ...
close(F);

print STDERR "list of clones :\n";
foreach my $rtab (@clones) {
  print STDERR "$$rtab[0]\t\[$$rtab[1]\]\n";
  my $romset_clone = $romsets{$$rtab[0]};
  my $romset_parent = $romsets{$$rtab[1]};
  if (!$romset_clone) {
    die "pas de romset pour le clone !!!\n";
  }
  if (!$romset_parent) {
    print STDERR "no parent romset... not a clone anymore $$rtab[0] !\n";
  }

  if ($romset_clone == $romset_parent) {
    die "same romsets : $romset_parent & $romset_clone\n";
  }
  foreach my $region (keys %$romset_parent) {
	  print STDERR "region $region... ";
	  my $rtab = $romset_parent->{$region};
	  my $rtab2 = $romset_clone->{$region};
	  if ($rtab && !$rtab2) {
		  print STDERR "not present in clone !!!\n";
		  $romset_clone->{$region} = [ "EMPTY" ];
	  } else {
		  my $different = 0;
		  for (my $n=0; $n<=$#$rtab; $n++) {
			  if ($$rtab[$n] ne $$rtab2[$n]) {
				  $different = 1;
				  last;
			  }
		  }
		  if ($different) {
			  print STDERR "differ\n";
		  } else {
			  print STDERR "the same (".($#$rtab+1)." & ".($#$rtab2+1)." roms)\n";
		  }
	  }
  }
}

# The code to generate the new format on stdout is not fast at all, but it does not
# need to be fast. At least it's easy to understand !

open(F,"<$filename");
while (<F>) {
  if (/ROM_INFO/) {
    if (/.+ rom_(.+?)\[/) {
      $romset = $1;
      my $parent = undef;
      foreach my $rtab (@clones) {
	if ($$rtab[0] eq $romset) {
	  $parent = $$rtab[1];
	  last;
	}
      }
      $parent = undef if (!$romsets{$parent});
      if ($parent) {
	my $romset_clone = $romsets{$romset};
	my $romset_parent = $romsets{$parent};
	chomp;
	if (!s/\*\//clone of $parent \*\/\n/) {
		$_ .= " // clone of $parent\n";
	}
	print;
	while (<F>) {
		if (/\{ ?(.+)\ ?}/) {
			my $args = $1;
			my ($name,$size,$crc,$region_name,$offset,$method) = split(/\, ?/,$args);
			if ($method && $region_name =~ /[a-z]/i) {
				# 1st put the empty regions if we have some...
				foreach my $region (keys %$romset_clone) {
					my $rtab = $romset_clone->{$region};
					if ($$rtab[0] eq "EMPTY") {
						print STDERR "detected $region EMPTY\n";
						print "  { REGION_EMPTY, 0, 0 , $region, 0, LOAD_NORMAL },\n";
						delete $romset_clone->{$region};
					}
				}
				my $rtab = $romset_parent->{$region_name};
				my $rtab2 = $romset_clone->{$region_name};
				my $different = 0;
				if ($#$rtab != $#$rtab2) {
					$different = 1;
				} else {
					for (my $n=0; $n<=$#$rtab; $n++) {
						if ($$rtab[$n] ne $$rtab2[$n]) {
							$different = 1;
							last;
						}
					}
				}
				if (!$different) {
					next;
				}
			}
		}
		last if (/\;/);
		print;
	}
}
    } # if /rom_/
  }
  print;
}
