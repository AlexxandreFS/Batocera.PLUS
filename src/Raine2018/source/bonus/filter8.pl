use strict;

# conversion to LOAD8_16 and LOAD16_64 macros

my @tmp;

$| = 1;

sub get_list {
	my $list = undef;
	do {
		if (@tmp) {
			$_ = shift @tmp;
		} else {
			$_ = <>;
		}
		($list) = $_ =~ /\{ *?(.*) *?\}/;
	} while (!$list);
	$list;
}

while (<>) {
	if (/\{ *?(.*) *?\}/) {
		my $list = $1;
		my ($rom1, $size,$crc1, $region, $offset, $load) = split(/\,/,$list);
		if ($load =~ /LOAD_8_16/) {
			my (@temp,$rom2,$crc2,$offset2);
			my $list0 = $list;
			while (1) {
				$list = get_list();
				($rom2, $size,$crc2, $region, $offset2, $load) = split(/\,/,$list);
				$offset =~ s/^ //;
				$offset2 =~ s/^ //;
				if (hex($offset2) == hex($offset) - 1) {
					print STDERR "invert $rom1 & $rom2\n";
					my @tab = ($rom1, $size,$crc1, $region, $offset, $load);
					($rom1, $size,$crc1, $region, $offset, $load) =
					($rom2, $size,$crc2, $region, $offset2, $load);
					($rom2, $size,$crc2, $region, $offset2, $load) = @tab;
					last;
				} elsif (hex($offset) == hex($offset2) -1) {
					last;
				} else {
					# print STDERR "offsets:$offset,$offset2, diff offsets : ",(hex($offset)-hex($offset2))," from $list0\n";
					push @temp,$_;
				}
			};
			@tmp = @temp;

			print "  LOAD8_16( $region, $offset, $size,\n";
			print "            $rom1, $crc1, $rom2, $crc2),\n";
			next;
		} elsif ($load =~ /LOAD_16_64/) {
			$list = get_list();
			my ($rom2, $size,$crc2, $region, $offset2, $load) = split(/\,/,$list);
			$list = get_list();
			my ($rom3, $size,$crc3, $region, $offset3, $load) = split(/\,/,$list);
			$list = get_list();
			my ($rom4, $size,$crc4, $region, $offset4, $load) = split(/\,/,$list);
			print "  LOAD16_64( $region, $offset, $size,\n";
			print "            $rom1, $crc1, $rom2, $crc2,\n";
			print "            $rom3, $crc3, $rom4, $crc4),\n";
			next;
		}
	}
	print;
}




