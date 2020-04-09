#!/usr/bin/perl

use strict;

my %raine_inputs =
    (
     "IPT_COIN1a" => ["KB_DEF_COIN1", "MSG_COIN1"],
     "IPT_COIN2a" => ["KB_DEF_COIN2", "MSG_COIN2"],
     "IPT_COIN3a" => ["KB_DEF_COIN3", "MSG_COIN3"],
     "IPT_COIN4a" => ["KB_DEF_COIN4", "MSG_COIN4"],
     "IPT_UNKNOWN" => ["KB_DEF_UNKNOWN", "MSG_UNKNOWN"],
     "IPT_SERVICE1a" => ["KB_DEF_SERVICE", "MSG_SERVICE"],
     "IPT_SERVICE" => ["KB_DEF_SERVICE", "MSG_SERVICE"],
     "IPT_TILT" => ["KB_DEF_TILT","MSG_TILT"],
     "IPT_START1a" => ["KB_DEF_P1_START","MSG_P1_START"],
     "IPT_START2a" => ["KB_DEF_P2_START","MSG_P2_START"],
     "IPT_START3a" => ["KB_DEF_P3_START","MSG_P3_START"],
     "IPT_START4a" => ["KB_DEF_P4_START","MSG_P4_START"],

     "IPT_JOYSTICK_RIGHTa" => ["KB_DEF_P1_RIGHT","MSG_P1_RIGHT"],
     "IPT_JOYSTICK_LEFTa" => ["KB_DEF_P1_LEFT", "MSG_P1_LEFT"],
     "IPT_JOYSTICK_DOWNa" => ["KB_DEF_P1_DOWN", "MSG_P1_DOWN"],
     "IPT_JOYSTICK_UPa" => ["KB_DEF_P1_UP", "MSG_P1_UP"],

     # some old drivers do not even mention player1 or 2...
     "IPT_JOYSTICK_RIGHT" => ["KB_DEF_P1_RIGHT","MSG_P1_RIGHT"],
     "IPT_JOYSTICK_LEFT" => ["KB_DEF_P1_LEFT", "MSG_P1_LEFT"],
     "IPT_JOYSTICK_DOWN" => ["KB_DEF_P1_DOWN", "MSG_P1_DOWN"],
     "IPT_JOYSTICK_UP" => ["KB_DEF_P1_UP", "MSG_P1_UP"],

	 "IPT_MAHJONG_A" => ["KB_DEF_P1_A", "MSG_P1_A"],
	 "IPT_MAHJONG_B" => ["KB_DEF_P1_B", "MSG_P1_B"],
	 "IPT_MAHJONG_C" => ["KB_DEF_P1_C", "MSG_P1_C"],
	 "IPT_MAHJONG_D" => ["KB_DEF_P1_D", "MSG_P1_D"],
	 "IPT_MAHJONG_E" => ["KB_DEF_P1_E", "MSG_P1_E"],
	 "IPT_MAHJONG_F" => ["KB_DEF_P1_F", "MSG_P1_F"],
	 "IPT_MAHJONG_G" => ["KB_DEF_P1_G", "MSG_P1_G"],
	 "IPT_MAHJONG_H" => ["KB_DEF_P1_H", "MSG_P1_H"],
	 "IPT_MAHJONG_I" => ["KB_DEF_P1_I", "MSG_P1_I"],
	 "IPT_MAHJONG_J" => ["KB_DEF_P1_J", "MSG_P1_J"],
	 "IPT_MAHJONG_K" => ["KB_DEF_P1_K", "MSG_P1_K"],
	 "IPT_MAHJONG_L" => ["KB_DEF_P1_L", "MSG_P1_L"],
	 "IPT_MAHJONG_M" => ["KB_DEF_P1_M", "MSG_P1_M"],
	 "IPT_MAHJONG_N" => ["KB_DEF_P1_N", "MSG_P1_N"],

     "IPT_BUTTON1a" => ["KB_DEF_P1_B1", "MSG_P1_B1"],
     "IPT_BUTTON2a" => ["KB_DEF_P1_B2", "MSG_P1_B2"],
     "IPT_BUTTON3a" => ["KB_DEF_P1_B3", "MSG_P1_B3"],
     "IPT_BUTTON4a" => ["KB_DEF_P1_B4", "MSG_P1_B4"],
     "IPT_BUTTON5a" => ["KB_DEF_P1_B5", "MSG_P1_B5"],
     "IPT_BUTTON6a" => ["KB_DEF_P1_B6", "MSG_P1_B6"],

     "IPT_JOYSTICK_RIGHTb" => ["KB_DEF_P2_RIGHT","MSG_P2_RIGHT"],
     "IPT_JOYSTICK_LEFTb" => ["KB_DEF_P2_LEFT", "MSG_P2_LEFT"],
     "IPT_JOYSTICK_DOWNb" => ["KB_DEF_P2_DOWN", "MSG_P2_DOWN"],
     "IPT_JOYSTICK_UPb" => ["KB_DEF_P2_UP", "MSG_P2_UP"],
     "IPT_BUTTON1b" => ["KB_DEF_P2_B1", "MSG_P2_B1"],
     "IPT_BUTTON2b" => ["KB_DEF_P2_B2", "MSG_P2_B2"],
     "IPT_BUTTON3b" => ["KB_DEF_P2_B3", "MSG_P2_B3"],
     "IPT_BUTTON4b" => ["KB_DEF_P2_B4", "MSG_P2_B4"],
     "IPT_BUTTON5b" => ["KB_DEF_P2_B5", "MSG_P2_B5"],
     "IPT_BUTTON6b" => ["KB_DEF_P2_B6", "MSG_P2_B6"],

     "IPT_JOYSTICK_RIGHTc" => ["KB_DEF_P3_RIGHT","MSG_P3_RIGHT"],
     "IPT_JOYSTICK_LEFTc" => ["KB_DEF_P3_LEFT", "MSG_P3_LEFT"],
     "IPT_JOYSTICK_DOWNc" => ["KB_DEF_P3_DOWN", "MSG_P3_DOWN"],
     "IPT_JOYSTICK_UPc" => ["KB_DEF_P3_UP", "MSG_P3_UP"],
     "IPT_BUTTON1c" => ["KB_DEF_P3_B1", "MSG_P3_B1"],
     "IPT_BUTTON2c" => ["KB_DEF_P3_B2", "MSG_P3_B2"],
     "IPT_BUTTON3c" => ["KB_DEF_P3_B3", "MSG_P3_B3"],
     "IPT_BUTTON4c" => ["KB_DEF_P3_B4", "MSG_P3_B4"],
     "IPT_BUTTON5c" => ["KB_DEF_P3_B5", "MSG_P3_B5"],
     "IPT_BUTTON6c" => ["KB_DEF_P3_B6", "MSG_P3_B6"],

     "IPT_JOYSTICK_RIGHTd" => ["KB_DEF_P4_RIGHT","MSG_P4_RIGHT"],
     "IPT_JOYSTICK_LEFTd" => ["KB_DEF_P4_LEFT", "MSG_P4_LEFT"],
     "IPT_JOYSTICK_DOWNd" => ["KB_DEF_P4_DOWN", "MSG_P4_DOWN"],
     "IPT_JOYSTICK_UPd" => ["KB_DEF_P4_UP", "MSG_P4_UP"],
     "IPT_BUTTON1d" => ["KB_DEF_P4_B1", "MSG_P4_B1"],
     "IPT_BUTTON2d" => ["KB_DEF_P4_B2", "MSG_P4_B2"],
     "IPT_BUTTON3d" => ["KB_DEF_P4_B3", "MSG_P4_B3"],
     "IPT_BUTTON4d" => ["KB_DEF_P4_B4", "MSG_P4_B4"],
     "IPT_BUTTON5d" => ["KB_DEF_P4_B5", "MSG_P4_B5"],
     "IPT_BUTTON6d" => ["KB_DEF_P4_B6", "MSG_P4_B6"],

     "\"Service A\"" => ["KB_DEF_SERVICE_A", "MSG_SERVICE_A"],
     "\"Service B\"" => ["KB_DEF_SERVICE_B", "MSG_SERVICE_B"],
     "\"Service C\"" => ["KB_DEF_SERVICE_C", "MSG_SERVICE_C"],

     # Mahjong / jeux de cartes

     "P1 Deal"   => ["KB_DEF_P1_KAN", "MSG_P1_KAN"],
     "P1 A"      => ["KB_DEF_P1_A", "MSG_P1_A"],
     "P1 B"      => ["KB_DEF_P1_B", "MSG_P1_B"],
     "P1 C"      => ["KB_DEF_P1_C", "MSG_P1_C"],
     "P1 D"      => ["KB_DEF_P1_D", "MSG_P1_D"],
     "P1 E"      => ["KB_DEF_P1_E", "MSG_P1_E"],
     "P1 Cancel" => ["KB_DEF_P1_PON", "MSG_P1_PON"],
     "P1 Flip"   => ["KB_DEF_P1_CHI", "MSG_P1_CHI"],
     );

my %raine_bits =
    ( "IP_ACTIVE_LOW" => "INP0",
      "IP_ACTIVE_HIGH" => "INP1" );

sub handle_bitx() {
  if (/PORT_BITX\( ?(.+) \)/) {
    my $args = $1;
    my ($mask, $active, $bidon, $name, $end) = split(/\, ?/,$args);
    if ($raine_inputs{$name}) {
      s/X\(.+$/\( $mask, $active, $name \)/;
    } elsif ($name =~ /\"P1 (.+)\"/) {
      my $arg = uc($1);
      $raine_inputs{$name} = ["KB_DEF_P1_$arg","MSG_P1_$arg"];
      s/X\(.+$/\( $mask, $active, $name \)/;
    } else {
      print STDERR "bitx inconnu:$name.\n";
    }
  }
}

my $port = $ARGV[1] || 0;
if ($port =~ /^0x/) {
  $port = hex($port);
}
$port-=2;
my $port0 = $port;
my $started = undef;

sub mychomp {
	s/\r//;
	chomp;
}

my %ports;
open(F,"<$ARGV[0]") || die "Impossible to open $ARGV[0]";
while (<F>) {
	mychomp;
	my $name_inp;
	my $name_incl = undef;
	if (/INPUT_PORTS_START\( (.+?) *\)/) {
		my $name = $1;
		my $nb = -1;
		while (<F>) {
			mychomp;
			if (/PORT_START\((.+?)\)/) {
				$nb++;
				$port+=2;
				print STDERR "adding ports $name:$1\n";
				$ports{"$name:$1"} = $port;
				die "debile\n" if (!defined($ports{"$name:$1"}));
			} elsif (/PORT_MODIFY\( *(.+?) *\)/) {
				if (defined($ports{"$name_incl:$1"})) {
					$port = $ports{"$name_incl:$1"};
				} else {
					print STDERR "port_modify: unknown port $name_incl:$1\n";
					exit(1);
				}
			}
			handle_bitx();
			if (/(PORT_BIT|PORT_SERVICE|PORT_INCLUDE)\( *(.+?) ?\)/) {
				my $whole_line = $_;
				my $args = $2;
				my $func = $1;
				if ($started) {
					print "\n";
				} else {
					print "static struct INPUT_INFO input_$name\[\] =\n";
					print "{\n";
					$started = 1;
				}
				$nb++;
				while ((my ($nb,$bit,$function) = split(/\, */,$args))) {
					$function = "IPT_SERVICE1" if (!$function && $func eq "PORT_SERVICE");
					$function =~ s/ +$//;
					$function = 1 if ($func eq "PORT_INCLUDE");
					if ($function =~ /\|/) {
						my @parts = split(/[ \t]*\|[ \t]*/,$function);
						$function = $parts[0];
						if ($parts[$#parts] eq "IPF_PLAYER1") {
							$function .= "a";
						} elsif ($parts[$#parts] eq "IPF_PLAYER2" || $parts[$#parts] eq "IPF_COCKTAIL") {
							$function .= "b";
						} elsif ($parts[$#parts] eq "IPF_PLAYER3") {
							$function .= "c";
						} elsif ($parts[$#parts] eq "IPF_PLAYER4") {
							$function .= "d";
						} elsif ($parts[$#parts] =~ /^IPF_\dWAY$/ ) {
							$function .= "a"; # Suppose it's player1 by default...
						} else {
							print STDERR "Unknown attribute $parts[$#parts] in ",join(" | ",@parts),"\n";
							exit;
						}
					} elsif (/PORT_PLAYER\((\d)/) {
						$function .= chr(ord('a')+$1-1);
					}
					if ($function =~ /\d$/) { # number at the end...
						# player 1 by default.
						$function .= "a";
					}
					if (/PORT_NAME\((.+?)\)/) {
						$name_inp = $1;
					}

					if ($function eq "IPT_OTHER") {
						if (/PORT_NAME\(\"(.+?)\"\)/) {
							$function = $1;
							if ($function =~ s/^P2/P1/) {
								print "/* P2 Control */\n";
							}
						}
					}

					if ($function) {
						if ($raine_inputs{$function}) {
							my ($key,$input) = @{$raine_inputs{$function}};
							if ($key) {
								$bit = $raine_bits{$bit} || "INP1";
								$input =~ s/MSG_//;
								;
								$nb = hex($nb) if ($nb =~ /^0x/);
								if ($name_inp) {
									print "  { $key, $name_inp, ";
									if ($bit eq "INP1") {
										$bit = "BIT_ACTIVE_1";
									} else {
										$bit = "BIT_ACTIVE_0";
									}
								} else {
									print "  $bit( $input, ";
								}
								if ($nb > 255) {
									print sprintf("0x%02x, ",$port+1), sprintf("0x%02x",$nb>>8);
								} else {
									print sprintf("0x%02x, ",$port), sprintf("0x%02x",$nb);
								}
								if ($name_inp) {
									print ", $bit },";
									$name_inp = undef;
								} else {
									print "),";
								}
								print " //$1" if (/\/\/(.+)/);
								print "\n";
							}
						} elsif ($func eq "PORT_INCLUDE") {
							$args =~ s/^ *//;
							$args =~ s/ *$//;
							$name_incl = $args;
							print STDERR "port_include $name_incl\n";
							$port = 0;
							foreach (keys %ports) {
								if (/^$name_incl\:(.*)/) {
									$ports{"$name:$1"} = $ports{$_};
									$port = $ports{$_} if ($ports{$_} > $port);
								}
							}
							print "  INCL_INP( $args ),\n";
						} elsif (!($function =~ /IPT_(UNKNOWN|UNUSED)/) && !($function =~ /IPT_SPECIAL/) && !($function =~ /IPT_SERVICE/)) {
							print STDERR "Unknown function \'$function\'\n";
						}
					}
					$_ = <F>;
					mychomp;
					handle_bitx();
					if (/(PORT_BIT|PORT_SERVICE)\( *(.+?) ?\)/) {
						$args = $2;
						$func = $1;
						next;
					} else {
						last;
					}
				} # while
			} # if (/PORT_BIT/
			last if (/PORTS_END/);
		} # while (<F>)
		print "  END_INPUT\n";
		print "};\n\n";
		$started = undef;
		$port = $port0;
	}
}
close(F);

