# Post-process a M68705->C file, and remove all un-needed labels.

BEGIN { FS = "[ \t,]+"; used[0] = 1; }

p==1 { used[$1] = 1 }
p==2 && !($2 ~ /{/ && !($3 in used)) {
      #if ((substr($0, 1, 3) ~ /L0x/) && !(substr($0, 1, 5) in used))
      if (substr($0, 1, 3) ~ /L0x/)
      {
         x = substr($0, 2, 5);
         if (used[x] != 1) printf("//");
      }
      print $0;
   }
