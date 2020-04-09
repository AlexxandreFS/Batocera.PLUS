# Post-process a M68705->C file, and print a list of all *used* labels

BEGIN { FS = "[ \t\(\)]+"; }

substr($1,1,3) ~ /L0x/ { last = substr($1, 2, 5); }
$2 ~ /JUMP_IMM/ { if (!($3 in used)) print $3; used[$3] = 1; }
$2 ~ /PUSHWORD/ { if (!($3 in used)) print $3; used[$3] = 1; }
substr($1,3,7) ~ /INIT_PC/ { if (used[last] != 1) print last; used[last] = 1; }
substr($1,3,3) ~ /BIH/ { if (!($2 in used)) print $2; used[$2] = 1; }
