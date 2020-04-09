#include "raine.h"
#include "console.h"
#include "parser.h"

static void exec_if(char *field);
static int level,inner;
/* I am not 100% certain this code is correct for unlimited imbrication of ifs
 * there are 2 variables, inner and level, which count respectively the number
 * of imbricated ifs in a true test and in a false test.
 * The variables have priorities, and if we are executing there can't be any
 * level of false ifs, so it should work in all the cases... */

static void restore_field(char *field, int argc) {
  while (argc > 1) {
    field[strlen(field)] = ' ';
    argc--;
  }
}

static void skip_if(char *field) {
  int argc; char *argv[10];
  split_command(field,argv,&argc,10);
  if (!stricmp(argv[0],"else")) {
    if (!level)
      cons->set_interactive(&exec_if);
  } else if (!stricmp(argv[0],"elsif") && !level) {
    if (argc != 2) throw "elsif takes exactly 1 argument !";
    int cond = parse(argv[1]);
    if (cond)
      cons->set_interactive(&exec_if);
  } else if (!stricmp(argv[0],"endif")) {
    if (level) level--;
    else {
      if (inner) {
	inner--;
	cons->set_interactive(&exec_if);
      } else
	cons->end_interactive();
    }
  } else if (!stricmp(argv[0],"if"))
    level++;
  restore_field(field,argc);
} 

static void exec_if(char *field) {
  int argc; char *argv[10];
  split_command(field,argv,&argc,10);
  if (!stricmp(argv[0],"else") || !stricmp(argv[0],"elsif")) {
    cons->set_interactive(&skip_if);
  } else if (!stricmp(argv[0],"endif")) {
    if (inner) {
      /* Apparently the only consequence of having another if executing
       * is only the handling of endif... */
      cons->end_interactive();
    } else
      inner--;
  } else {
    // just execute the instruction, then come back here
    // 1st restore field...
    int other_if = 0;
    if (!stricmp(argv[0],"if")) other_if=1;
    restore_field(field,argc);
    cons->end_interactive();
    cons->run_cmd(field);
    if (!other_if)
      cons->set_interactive(&exec_if);
    else
      inner++;
    return;
  } 
  restore_field(field,argc);
}

void do_if(int argc, char **argv) {
  if (argc != 2) throw "if takes exactly 1 argument !";
  int cond = parse(argv[1]);
  if (cond) {
    cons->set_interactive(&exec_if);
  } else {
    cons->set_interactive(&skip_if);
  }
}

