#!/usr/bin/perl

# This script is now quite unreadable because it does a quite crazy conversion
# it even knows how to convert macros included in the DSW definition from mame.
# and keep the default values even from the macros...

use strict;

my ($on,$off);
my %raine_dsw =
    (
     "None" => "MSG_UNKNOWN",

     "Coin_A" => "MSG_COIN1",
     "9C_1C" => "MSG_9COIN_1PLAY",
     "8C_1C" => "MSG_8COIN_1PLAY",
     "8C_3C" => "MSG_8COIN_3PLAY",
     "7C_1C" => "MSG_7COIN_1PLAY",

     "6C_1C" => "MSG_6COIN_1PLAY",
     "6C_2C" => "MSG_6COIN_2PLAY",
     "6C_3C" => "MSG_6COIN_3PLAY",
     "6C_4C" => "MSG_6COIN_4PLAY",

     "5C_1C" => "MSG_5COIN_1PLAY",
     "5C_2C" => "MSG_5COIN_2PLAY",
     "5C_3C" => "MSG_5COIN_3PLAY",
     "5C_4C" => "MSG_5COIN_4PLAY",

     "4C_1C" => "MSG_4COIN_1PLAY",
     "4C_2C" => "MSG_4COIN_2PLAY",
     "4C_3C" => "MSG_4COIN_3PLAY",
     "4C_4C" => "MSG_4COIN_4PLAY",
     "4C_5C" => "MSG_4COIN_5PLAY",
     "4C_6C" => "MSG_4COIN_6PLAY",
     "4C_7C" => "MSG_4COIN_7PLAY",
     "4C_8C" => "MSG_4COIN_8PLAY",

     "3C_1C" => "MSG_3COIN_1PLAY",
     "3C_2C" => "MSG_3COIN_2PLAY",
     "3C_3C" => "MSG_3COIN_3PLAY",
     "3C_4C" => "MSG_3COIN_4PLAY",
     "3C_5C" => "MSG_3COIN_5PLAY",
     "3C_6C" => "MSG_3COIN_6PLAY",
     "3C_7C" => "MSG_3COIN_7PLAY",
     "3C_8C" => "MSG_3COIN_8PLAY",

     "2C_1C" => "MSG_2COIN_1PLAY",
     "2C_2C" => "MSG_2COIN_2PLAY",
     "2C_3C" => "MSG_2COIN_3PLAY",
     "2C_4C" => "MSG_2COIN_4PLAY",
     "2C_5C" => "MSG_2COIN_5PLAY",
     "2C_6C" => "MSG_2COIN_6PLAY",
     "2C_7C" => "MSG_2COIN_7PLAY",
     "2C_8C" => "MSG_2COIN_8PLAY",

     "1C_1C" => "MSG_1COIN_1PLAY",
     "1C_2C" => "MSG_1COIN_2PLAY",
     "1C_3C" => "MSG_1COIN_3PLAY",
     "1C_4C" => "MSG_1COIN_4PLAY",
     "1C_5C" => "MSG_1COIN_5PLAY",
     "1C_6C" => "MSG_1COIN_6PLAY",
     "1C_7C" => "MSG_1COIN_7PLAY",
     "1C_8C" => "MSG_1COIN_8PLAY",
     "1C_9C" => "MSG_1COIN_9PLAY",

     "Coin_B" => "MSG_COIN2",
     "Demo_Sounds" => "MSG_DEMO_SOUND",
     "Flip_Screen" => "MSG_SCREEN",
     "Cocktail" => "MSG_TABLE",
     "Bonus_Life" => "MSG_EXTRA_LIFE",
     "Lives" => "MSG_LIVES",
     "Service_Mode" => "MSG_SERVICE",
     );

use vars qw(@dsw $name $nb @tab_data @tab_name);

my $port = $ARGV[1] || 0;
$port = value($port);
$port-=2;
my $port0 = $port;
my $default = 0;
my $output;
my $started = undef;
my $length;
my ($bit,$def,$function);
my $main_out="";
my $dsw_name;
my $roll = undef;

open(F,"<$ARGV[0]") || die "Impossible to open $ARGV[0]";
our @file = <F>;
close(F);

sub update_start() {
  if ($dsw_name) {
    if ($length) {
      if ($roll) {
	$port++;
#	$default >>= 8;
      }
      my $found = undef;
      for (my $n=0; $n<=$#tab_data; $n++) {
	if ($tab_data[$n] eq $main_out) {
	  print STDERR "Found $dsw_name = $tab_name[$n]\n";
	  push @dsw,[$tab_name[$n],$default,$port];
	  $found = 1;
	}
      }
      if ($dsw_name =~ /mspacman_4/ && !$found) {
	print "not found : $main_out\n";
	exit(1);
      }
      if (!$found) {
	push @dsw,[$dsw_name,$default,$port];
	print "static struct DSW_DATA $dsw_name\[\] =\n{\n";
# 	if ($started) {
# 	  $main_out .= "  added $length { $function, $bit, $length },\n" if ($length >= 1);
# 	  $main_out .= " output : $output";
# 	}
	print "$main_out  { NULL, 0, 0}\n};\n\n";
	push @tab_name,$dsw_name;
	push @tab_data,$main_out;
	$main_out = "";
      }
    }
  }
  $nb++;
  $length = 0;
  if ($roll) {
    $port++;
  } else {
    $port+=2;
  }
  $roll = undef;
  $default = 0;
  $main_out = "";
  $dsw_name = "dsw_data_$name\_$nb";
#   print STDERR "starting $dsw_name\n";
}

sub get_raine_dsw($) {
  my $dsw = shift;
  my $function;
  if ($raine_dsw{$dsw}) {
    $function = $raine_dsw{$dsw};
  } else {
    print STDERR "warning : Unknown DSW $dsw from $_\n";
    $function = "MSG_".uc($dsw);
  }
  $function;
}

sub value($) {
  my $a = shift;
  $a =~ s/^[ \t]*//;
  if ($a =~ /^0x/) {
    return hex($a);
  }
  return $a;
}

sub read_next_line() {
	while ($_ = shift @file) {
		next if (/^[ \t]*\/\//); # skip // comments
		if (/^[ \t]*\/\*/) { # /* comments
			while (!/\*\//) {
				$_ = shift @file;
			}
			s/^.+\*\///; # remove everything until */
		}
		last;
	}
	s/\r//;
	return $_;
}

my $macro = undef;
my %default_macro = ();

my $last_line = "";
my (%def,%args) = ();

sub define_macro {
	my $name = $1;
	my $fin = $2;
	my $args = undef;
	if ($name =~ s/\((.+)\)//) {
		$args = $1;
	}
	$fin =~ s/\r//;
	my $multi = undef;
	if ($fin =~ s/\\//) {
		$multi = 1;
	}
	$fin =~ s/^[ \t]*//;
	$def{$name} = $fin if ($fin);

	print STDERR "define $name found";
	print STDERR " args $args" if ($args);
	print STDERR " fin $fin" if ($fin);
	print STDERR " multi" if ($multi);
	if ($multi) {
		while ($_ = shift @file) {
			s/\r$//;
			my $rep = s/\\$//;
			$def{$name} .= $_;
			$args{$name} = $args;
			last if (!$rep);
		}
	}
	if (!$def{$name}) {
		$def{$name} = " ";
		print STDERR " empty";
	}
	print STDERR "\n";
}

while (read_next_line()) {
	if (/^#define (.+?)( .+)/ || /^#define (.+)/) {
		define_macro($1,$2);
	} elsif (/INPUT_PORTS_START\( (.+?) \)/ || $macro) {
		if (!$macro) {
			$name = $1;
			$name = "_".$name if ($name =~ /^\d/);
		} else {
			$macro = 2;
		}
		@dsw = ();
		$nb = -1;
		$dsw_name = undef;
		my $location = "";
		while ($macro == 2 || read_next_line()) {
			# Normalize spaces to be sure to find same dipswitches
			s/ ([\,\"\)])/$1/g;
			s/ +$//;
			s/ +/ /g;
			if (s/PORT_DIPLOCATION\((.+)\)//) {
				$main_out .= "  // $location\n" if ($location);
				$location = $1;
			}
			$macro = 1 if ($macro == 2);
			next if (/^[ \t]*\/\//);
			s/PORT_CODE.+?\)//; # PORT_CODE not supported (yet) in raine
			# mame has really crazy syntaxes sometimes !
			s/PORT_BIT\((.+)IPT_DIPSWITCH_NAME *\) *PORT_NAME\( *(\".+?\")/PORT_DIPNAME\($1$2/;
			if (/PORT_START/) {
				update_start();
				$started = undef;
			} elsif (/PORT_BITX\([ \t]?(.+)[ \t]?\)/) {
				# Not sure wether it will be enough...
				my $args = $1;
				my ($bit,$def,$function,$name,$rest) = split(/\, ?/,$args);
				if (value($bit) > 0) { # Be sure it looks like a dipname...
					$_ = "PORT_DIPNAME( $bit, $def, $name )";
					redo;
				}
			} elsif (/PORT_DIPNAME\( ?(.+) ?\)/) {
				my $args = $1;
				if ($started) {
					if ($function =~ /DEMO_SOUND/) {
						$main_out .= "  DSW_DEMO_SOUND( $on, $off ),";
					} elsif ($function =~ /SERVICE/) {
						$main_out .= "  DSW_SERVICE( $on, $off ),";
					} elsif ($function =~ /TEST/i) {
						$main_out .= "  DSW_TEST_MODE( $on, $off ),";
					} else {
						if ($length >= 1) {
							$main_out .= "  { $function, $bit, $length },\n";
						}
						chomp $output;
						$main_out .= $output;
					}
					$main_out .= "\n";
					$main_out .= "  // $location\n" if ($location);
					$location = undef;
				}
				$started = 1;
				my $rest;
				if ((($bit,$def,$function,$rest) = split(/\, ?/,$args))) {
					my $bit2 = value($bit);
					if ($bit2 > 0xff && !$roll) {
						update_start();
						$started = 1;
						$roll = 1;
					}
					$bit = "0x".sprintf("%x",$bit2 >> 8) if ($roll);
					$function .= ",$rest" if ($rest);
					$def = hex($def) if ($def =~ /^0x/);
					$def >>=8 if ($roll);
					$default |= $def;
					$output = "";
					$length = 0;
					if ($function =~ /DEF_STR\( ?(.+?) ?\)/) {
						$function = get_raine_dsw($1);
					}
				} else {
					print STDERR "Parsing error : $args\n";
					exit(1);
				}
			} elsif (/PORT_SERVICE.*\( *(.+) *\)/) {
				my $args = $1;
				my ($mask,$bit) = split(/\, */,$args);
				if (!$started) {
					$output = "";
					$started = 1;
				}
				if ($roll) {
					$mask = "0x".sprintf("%x",value($mask) >> 8);
				}
				if ($bit =~ /IP_ACTIVE_LOW/) {
					$output .= "  DSW_SERVICE( 0, $mask ),\n";
					$mask = hex($mask);
					$default |= $mask;
				} elsif ($bit =~ /IP_ACTIVE_HIGH/) {
					$output .= "  DSW_SERVICE( $mask, 0 ),\n";
				} else {
					print STDERR "Unknown service port $args ($bit)\n";
					exit(1);
				}
			} elsif (/PORT_DIPSETTING\( *(.+) *\)/) {
				my $args = $1;
				$args =~ s/\)[ \t]*\/[\/\*].+//; # remove comments from the args
				my ($mask,$f2,$rest) = split(/\, */,$args);
				my $bit2 = value($mask);
				$mask = "0x".sprintf("%x",$bit2 >> 8) if ($roll);
				$f2 .= $rest if ($rest);
				if ($f2 =~ /DEF_STR\( ?(.+?) ?\)/) {
					$f2 = get_raine_dsw($1);
					if ($f2 eq "MSG_ON") {
						$on = $mask;
					} elsif ($f2 eq "MSG_OFF") {
						$off = $mask;
					}
				}
				$output .= "  { $f2, $mask, 0x00 },";
				$output .= "\t// $1" if (/\/\/ (.+)/);
				$output .= "\n";
				$length++;
			} elsif (/([A-Z_0-9]+)\((.+)\)/ || /^[\t ]*([A-Z_0-9]+)/) {
				my ($function,$args) = ($1,$2);
				my @args = split /, */,$args;
				foreach (@args) {
					s/^[ \t]*//;
					s/[ \t]*$//;
				}
				if ($def{$function}) {
					print STDERR "macro found $function\n";
					my $xargs = $args{$function};
					my $def = $def{$function};
					if ($xargs) {
						my @xargs = split(/\, */,$xargs);
						for (my $n=0; $n<= $#xargs; $n++) {
							$def =~ s/$xargs[$n]/$args[$n]/g;
						}
					}
					unshift @file,split(/\n/,$def);
					next;
				} else {
					print STDERR "unknown $function\n";
				}
			} elsif ($started) { # end of the dsw section if started
				# difficulty
				$main_out .= "  { $function, $bit, $length },\n$output";
				$started = undef;
			}
			last if (/PORTS_END/);
			if ($macro && !(/\\$/)) {
				last;
			}
		} # while (<F>)
		if ($length) {
			if ($started) {
				$main_out .= "  { $function, $bit, $length },\n" if ($length >= 1);
				$main_out .= $output;
				$output = "";
				$started = undef;
			}

			my $found = undef;
			if (!$macro) {
				for (my $n=0; $n<=$#tab_data; $n++) {
					if ($tab_data[$n] eq $main_out) {
						print STDERR "Found $dsw_name = $tab_name[$n]\n";
						push @dsw,[$tab_name[$n],$default,$port];
						$found = 1;
					}
				}
			}
			if ($macro) {
				print $last_line;
				$main_out =~ s/\n/\\\n/mg;
				print "$main_out\n";
				my $macro_name = $last_line;
				$macro_name =~ s/^\#define //;
				$macro_name =~ s/[ \t]+//g;
				$macro_name =~ s/\\\n//;
				$default_macro{$macro_name} = $default;
				$macro = undef;
				$main_out = "";
			} elsif (!$found) {
				push @dsw,[$dsw_name,$default,$port];
				print "static struct DSW_DATA $dsw_name\[\] =\n{\n";
				if ($started) {
					$main_out .= "  { $function, $bit, $length },\n" if ($length >= 1);
					$main_out .= $output;
				}
				print "$main_out  { NULL, 0, 0}\n};\n\n";
				push @tab_name,$dsw_name;
				push @tab_data,$main_out;
				$main_out = "";
			}
		}
		$started = undef;
		$port = $port0;

		# dsw_info
		if ($#dsw>=0) {
			print "static struct DSW_INFO dsw_$name\[\] =\n{\n";
			for (my $n=0; $n<=$#dsw; $n++) {
				my ($dname, $def, $port) = @{$dsw[$n]};
				print "  { ".sprintf("0x%x",$port).", 0x",sprintf("%02x",$def),", $dname },\n";
			}
			print "  { 0, 0, NULL }\n";
			print "};\n\n";
		}
	} elsif (/PORT_DIPNAME\(/) {
		$macro = 1;
		redo;
	} else {
		$last_line = $_;
	}
}
close(F);

