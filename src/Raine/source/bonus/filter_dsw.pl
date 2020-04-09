use strict;

# This script compacts the old way DSW_DATA was written in raine
# to use "function" macros instead. It should be needed only when converting
# dsw from mame (run it after the converter then).

sub get_args {
	my ($args) = $_ =~ /\{(.+)\}/;
	my @par = split(/\,/,$args);
	foreach (@par) {
		s/"Continue Play"/MSG_CONTINUE_PLAY/;
		s/"Cabinet"/MSG_CABINET/;
		s/"Cocktail"/MSG_COCKTAIL/;
		s/MSG_COCKTAIL/MSG_TABLE/;
		s/"Upright"/MSG_UPRIGHT/;
		s/^[ \t]*//g;
		s/[ \t]*$//;
	}
	@par;
}

while (<>) {
	if (/DSW_DATA/) {
		print;
		while (<>) {
			my ($prefix) = $_ =~ /^([ \t]*)/;
			my @par = get_args();
			if ($par[0] =~ /MSG_(SCREEN|DEMO_SOUND|CONTINUE_PLAY|TEST_MODE|SERVICE|CABINET|UNUSED)/ && hex($par[2]) == 2) {
				my %arg = ();
				for (my $n=1; $n<=2; $n++) {
					$_ = <>;
					my @arg = get_args();
					$arg{$arg[0]} = $arg[1];
				}
				for($par[0]) {
					if (/MSG_SCREEN/) {
						if (defined($arg{MSG_NORMAL})) {
							print $prefix."DSW_SCREEN( $arg{MSG_NORMAL}, $arg{MSG_INVERT}),\n";
						} elsif (defined($arg{MSG_OFF})) {
							print $prefix."DSW_SCREEN( $arg{MSG_OFF}, $arg{MSG_ON}),\n";
						} else {
							die "MSG_SCREEN: no recognized argument\n";
						}
					} elsif (/CABINET/) {
						if (defined($arg{MSG_UPRIGHT})) {
							print $prefix."DSW_CABINET( $arg{MSG_UPRIGHT}, $arg{MSG_TABLE}),\n";
						} else {
							print STDERR "CABINET: unknown arguments\n";
							print "$prefix\{ $par[0], $par[1], 2 },\n";
							foreach (keys %arg) {
								print "$prefix\{ $_, $arg{$_} },\n";
							}
						}
					} else {
						$par[0] =~ s/MSG/DSW/;
						if (defined($arg{MSG_ON})) {
							print $prefix."$par[0]( $arg{MSG_ON}, $arg{MSG_OFF}),\n";
						} else {
							print STDERR "$par[0]: no known argument, trying to restore\n";
							$par[0] =~ s/DSW/MSG/;
							print "$prefix\{ $par[0], $par[1], 2 },\n";
							foreach (keys %arg) {
								print "$prefix\{ $_, $arg{$_} },\n";
							}
						}
					}
				}
				next;
			} 
			if (length($par[2])>0) {
				my $orig = $par[2];
				if ($par[2] =~ /0x/) {
					$par[2] = hex($par[2]);
				}
				if ($par[2] == 0) {
					print STDERR "cut $orig from $_";
					s/\,[ \t]*$orig[ \t]*//;
				}
			}
			print;
			last if (/\}\;/);
		}
		next;
	}
	print;
}
