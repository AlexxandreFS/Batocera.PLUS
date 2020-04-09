#!/usr/bin/perl

my $lib = shift @ARGV || die "pass lib in argument\n";
make_framework($lib);

sub get_name {
	# extract the name of a shared lib
	my $first = shift;
	$first =~ s/^.+\///; # get rid of path
	my ($res) = $first =~ /lib([_a-zA-Z0-9]+)/;
	$res;
}

sub mysys {
	my $cmd = shift;
	my $ret = system($cmd);
	if ($ret) {
		die "system $cmd failed, exit $ret\n";
	}
}

sub handle_otool($) {
    my $first = shift;
    $first =~ s/^.+name (\/.+) \(.+/$1/;
    chomp $first;
    $first;
}

sub make_framework($) {
    my $lib = shift;
    my $name = get_name($lib);
    print "making $name framework...\n";
    system("rm -rf $name.framework");
    mkdir "$name.framework";
    chdir "$name.framework";
    mkdir "Versions";
    mkdir "Versions/A";
    symlink("A","Versions/Current");
    mysys("cp $lib Versions/A/$name && chmod +w Versions/A/$name");
    symlink("Versions/Current/$name","$name");
    chdir "..";
    my $path = "$name.framework/$name";
    my $f;
	open($f,"otool -l $path|grep 'name /'|");
	my $first = handle_otool(<$f>);
	mysys("install_name_tool -id \@executable_path/../$name.framework/Versions/A/$name $path");
	while (<$f>) {
		$first = handle_otool($_);
		if ($first =~ /local/) {
			my ($file) = $first =~ /lib\/(.+)/;
			if (!-e $first) {
				if (-e "/usr/local/lib/$file") {
					$first = "/usr/local/lib/$file";
					print "fixing lib path for $first\n";
				} elsif (! -e "/usr/lib/$file") {
					die "pas trouvé $first ni /usr/local/lib/$file\n";
				}
			}
			print "handling $first\n";
			if (! -e "/usr/lib/$file" && -e "$first") {
				$name = get_name($first);
				if (!-d "$name.framework") {
					make_framework($first);
				} else {
					print "$name framework already exists\n";
				}
				mysys("install_name_tool -change $first \@executable_path/../$name.framework/Versions/A/$name $path");
			} else {
				print "existe pas $first\n";
			}
		}
	}
	close($f);
}

