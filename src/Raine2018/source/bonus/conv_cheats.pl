#!/usr/bin/perl

# Basic cheat converter from mame old format

use strict;

my %nb = ();

while (<>) {
  if (/^\;/) { # commentaire
    # allegro oblige à avoir # pour introduire les commentaires...
    # comme en perl, remarque...
    s/^\;/\#/;
  } elsif (/\:/) { # : est un séparateur de champ, on est sur un cheat
    my ($name, $cpu, $adr, $val, $type, $message, $info) = split(/\:/);
    my $raine_type = 0;
    if ($type >= 100 & $type <= 900) {
      $type -= int($type/100)*100;
    }
    if ($type == 999) {
      # Le cheat commentaire n'est pas prévu dans raine encore... Bah...
      print "# $message\n";
      next;
    }
    my $mask = 0;
    if ($type == 1) {
      $raine_type = 8; # temporary patch
    } elsif ($type == 0) {
      $raine_type = 0;
    } elsif ($type == 4) { # toutes les 5s
      $raine_type = 0x200;
    } elsif ($type == 71) { # editable base 1 (temp)
      $raine_type = 0x68;
      $mask = 1;
    } elsif ($type == 70) { # editable base 0 (temp)
      $raine_type = 0x28;
    } elsif ($type == 61) { # editable base 1 (temp) - onchange
      $raine_type = 0x168;
      $mask = 1;
    } elsif ($type == 20) { # apply mask (permanant)
      $raine_type = 4;
      $mask = $val;
    } elsif ($type == 21) { # apply mask (temp)
      $raine_type = 0xc;
      $mask = $val;
    } else {
      print STDERR "type $type non supporté\n";
      next;
    }
    my $nb = 0;
    if (defined($nb{$name})) {
      $nb = $nb{$name};
    } else {
      print "[$name]\n";
    }
    print sprintf("Cheat%02d = $adr:$val:%02X:%02X:$message",$nb,$mask,$raine_type);
    print ":$info" if ($info);
    $nb{$name} = ++$nb;
    next;
  }
  print;
}
