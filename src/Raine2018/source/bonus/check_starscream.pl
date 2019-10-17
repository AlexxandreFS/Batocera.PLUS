use strict;

my $function;
my $level = 0;
our (@rb,@rw,@wb,@ww,@pref,@suf,@fetch) = ();
my $finish = 0;
our $last_prefix;

sub print3($$$) {
	my ($header,$cpu,$arg) = @_;
	my $pr = $pref[$cpu]{$arg};
	my $com = $suf[$cpu]{$arg};
	my @arg = split(/\,/,$arg);
	$last_prefix = $pr;
	print "$pr$header$cpu,$arg[0],$arg[1],$arg[3]);$com\n";
}

sub print4($$$) {
	my ($header,$cpu,$arg) = @_;
	my $pr = $pref[$cpu]{$arg};
	my $com = $suf[$cpu]{$arg};
	$last_prefix = $pr;
	print "$pr$header$cpu,$arg);$com\n";
}

sub handle($$$$) {
	my ($prefix,$name,$args,$comments) = @_;
	my @arg = split(/\,/,$args);
	# print STDERR "handle $name,$args\n";
	foreach (@arg) {
		s/^ *//;
		s/ *$//;
	}
	$args = join(",",@arg);
	my $cpu = 0;
	for ($name) {
		if (s/MC68000B//) {
			$cpu = 1;
		} elsif (s/MC68000C//) {
			$cpu = 2;
		} elsif (s/MC68000D//) {
			$cpu = 3;
		} else {
			$cpu = 0;
		}
		if (hex($arg[0]) == 0 && hex($arg[1]) == 0xffffff) {
			$finish |= (1<<$cpu);
			return 1;
		}
		if (/^ReadByte$/) {
			$rb[$cpu]{$args} = 1;
		} elsif (/^ReadWord$/) {
			$rw[$cpu]{$args} = 1;
		} elsif (/^WriteByte$/) {
			$wb[$cpu]{$args} = 1;
		} elsif (/^WriteWord$/) {
			$ww[$cpu]{$args} = 1;
		} elsif (/^ReadBW$/) {
			$rb[$cpu]{$args} = $rw[$cpu]{$args} = 1;
		} elsif (/^RWBW$/) {
			$rb[$cpu]{$args} = $rw[$cpu]{$args} = 
			$wb[$cpu]{$args} = $ww[$cpu]{$args} = 1;
		} elsif ($name eq "MemFetch") {
			$fetch[$cpu]{$args} = 1;
		} else {
			return 0; # not handled here
		}
	}
	if (!$rb[$cpu] && !$rw[$cpu] && !$ww[$cpu] && !$wb[$cpu]) {
		die "problem handle\n" if ($name ne "MemFetch");
	}
	$pref[$cpu]{$args} = $prefix;
	$suf[$cpu]{$args} = $comments;
	return 1;
}



while (<>) {
	if (/^[ \t]*\/\//) {
		print;
		next;
	}
	next if (/AddInitMemory/);
	if (/finish_conf_68000\(.+?\)/) {
		$finish |= (1<<$1);
		next;
	}
	if ($level == 0 && / ([a-zA-Z_0-9]+)\(/) {
		$function = $1;
		$function = undef if (/\;/);
	}
	my $old_level = $level;
	$level++ if (/\{/);
	if ($level && $function) {
		if (/^(.*)Add([a-zA-Z0-9]+)\((.+?)\)\;(.*)?/) {
			next if (handle($1,$2,$3,$4));
		} 
	}

	if (/\}/) {
		$level--;
	}
	die "level $level\n" if ($level < 0);
	if (($level != $old_level || (/^[ \t]*?if / && !/\;/)) && $function) {
		for (my $n=0; $n<=3; $n++) {
			if ($rb[$n] || $rw[$n] || $ww[$n] || $wb[$n] || $fetch[$n]) {
				my (@ram,@rom) = ();
				foreach (keys %{$fetch[$n]}) {
					my @arg = split(/\,/);
					$arg[2] =~ s/\-(.+)//;
					my $new = "$arg[0],$arg[1],NULL,$arg[2]";
					if (($rb[$n]{$new} && $rw[$n]{$new}) || $_ eq "-1,-1,NULL") {
						delete $fetch[$n]{$_};
					}
				}

				foreach (keys %{$rb[$n]}) {
					my @arg = split(/\,/);
					if ($rw[$n]{$_} && $wb[$n]{$_} && $ww[$n]{$_}) {
						if ($_ eq "-1,-1,NULL,NULL") {
							$finish |= (1<<$n);
						} elsif ($arg[2] eq "NULL") {
							push @ram,$_;
						}
						delete $rb[$n]{$_};
						delete $rw[$n]{$_};
						delete $wb[$n]{$_};
						delete $ww[$n]{$_};
					} elsif ($rw[$n]{$_} && $arg[2] eq "NULL") {
						push @rom,$_;
						delete $rb[$n]{$_};
						delete $rw[$n]{$_};
					} 
				}
				# print "function $function, cpu $n\n";
				foreach (keys %{$fetch[$n]}) {
					print4("add_68000_program_region(",$n,$_);
				}
				foreach (@rom) {
					print3("add_68000_rom(",$n,$_);
				}
				foreach (@ram) {
					print3("add_68000_ram(",$n,$_);
				}
				foreach (keys %{$rb[$n]}) {
					print4("add_68000_rb(",$n,$_);
				}
				foreach (keys %{$rw[$n]}) {
					print4("add_68000_rw(",$n,$_);
				}
				foreach (keys %{$wb[$n]}) {
					print4("add_68000_wb(",$n,$_);
				}
				foreach (keys %{$ww[$n]}) {
					print4("add_68000_ww(",$n,$_);
				}
				my $c=0;
				while ($finish) {
					if ($finish & (1<<$c)) {
						print $last_prefix."finish_conf_68000($c);\n";
						$finish &= ~(1<<$c);
					}
					$c++;
				}
			}
		}

		$finish = 0;
		(@rb,@rw,@wb,@ww,@pref,@suf,@fetch) = ();
	}
	if (/\}/ && $level == 0) {
		$function = undef;
	}
	print;
	die "MemFetch\n" if (/MemFetch/);
}

