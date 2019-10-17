#include "raine.h"
#include "games.h"
#include "files.h"
#include "scripts.h"
#include "console.h"

typedef struct {
  char *title;
  // status : 0 = off, 1 = on (in dialog)
  int status, looping, nb_lines,hidden;
  char **lines;
} tscript;

tscript *script;
int nb_scripts;

char *get_script_name(int writeable) {
  char base[10];
   if (is_neocd())
       strcpy(base,"neocd");
   else
       strcpy(base,"raine");
  char buf[FILENAME_MAX];
  snprintf(buf,FILENAME_MAX,"scripts%s%s%s%s.txt",SLASH,base,SLASH,current_game->main_name);

  char *s = get_shared(buf);
  if (!exists(s)) {
      snprintf(buf,FILENAME_MAX,"scripts%s%s%s%s.txt",SLASH,base,SLASH,parent_name());
      s = get_shared(buf);
  }
  if (!writeable)
    return s;
  // if it must be writable, force the use of the personnal folder, and
  // create the dirs by the way
  static char shared[1024];
  snprintf(shared,1024, "%sscripts", dir_cfg.exe_path);
  mkdir_rwx(shared);
  snprintf(shared+strlen(shared),1024-strlen(shared),"%s%s",SLASH,base);
  mkdir_rwx(shared);
  snprintf(shared+strlen(shared),1024-strlen(shared),"%s%s.txt",SLASH,current_game->main_name);
  return shared;
}

void init_scripts() {
  if (nb_scripts) {
    for (int n=0; n<nb_scripts; n++) {
      free(script[n].title);
      for (int x=0; x<script[n].nb_lines; x++)
	free(script[n].lines[x]);
    }
    free(script);
    script = NULL;
    nb_scripts = 0;
  }
  // rb should allow fseek in windoze...
  FILE *f = fopen(get_script_name(0),"rb");
  int nb_alloc = 0;
  if (f) {
    while (!feof(f)) {
      char buff[1024];
      myfgets(buff,1024,f);
      if (!strncmp(buff,"script \"",8) ||
	      !strncmp(buff,"hidden \"",8)) {
	if (nb_scripts == nb_alloc) {
	  nb_alloc += 10;
	  script = (tscript *)realloc(script,sizeof(tscript)*nb_alloc);
	}
	script[nb_scripts].hidden = !strncmp(buff,"hidden",6);
	char *t = strchr(buff+8,'"');
	if (!t) {
	  print_debug("init_scripts: didn't find closing quote, line %s\n",buff);
	  fclose(f);
	  return;
	}
	*t = 0;
	script[nb_scripts].title = strdup(buff+8);
	t++;
	while (*t == ' ' || *t == '\t')
	  t++;
	if (*t) // any word after the script name makes it to loop !
	  script[nb_scripts].looping = 1;
	else
	  script[nb_scripts].looping = 0;
	script[nb_scripts].status = 0;
	int pos = ftell(f);
	script[nb_scripts].nb_lines = 0;
	while (!feof(f)) {
	  myfgets(buff,1024,f);
	  int n=0;
	  // skip spaces, tabs, and comments
	  while (buff[n] == ' ' || buff[n] == 9)
	    n++;
	  if (buff[n] == 0)
	    break;
	  if (buff[n] == '#')
	    continue; // don't keep comments !
	  script[nb_scripts].nb_lines++;
	}
	fseek(f,pos,SEEK_SET);
	int l = 0;
	script[nb_scripts].lines = (char**)malloc(sizeof(char*)*script[nb_scripts].nb_lines);
	while (!feof(f)) {
	  myfgets(buff,1024,f);
	  int n=0;
	  // skip spaces, tabs, and comments
	  while (buff[n] == ' ' || buff[n] == 9)
	    n++;
	  if (buff[n] == 0)
	    break;
	  if (buff[n] == '#')
	    continue;
	  script[nb_scripts].lines[l++] = strdup(&buff[n]);
	}
	nb_scripts++;
      } else // script line
	  run_console_command(buff); // pre-init, usually for variables
    } // feof
    fclose(f);
  } // if (f)
}

void add_scripts(menu_item_t *menu) {
  for (int n=0; n<nb_scripts; n++) {
      if (script[n].hidden) continue;
      menu->label = script[n].title;
      menu->value_int = &script[n].status;
      menu->values_list_size = 2;
      menu->values_list[0] = 0;
      menu->values_list[1] = 1;
      menu->values_list_label[0] = _("Off");
      menu->values_list_label[1] = _("On");
      menu++;
  }
}

void update_scripts() {
    int *status;
    if (!nb_scripts) return;
    status = new int[nb_scripts];
    int n;
    /* We want that the start_script command starts the script in the next
     * frame, so we must make a backup of the current status array otherwise
     * the script is started at the same frame if coming after the current one
     * */
    for (n=0; n<nb_scripts; n++)
	status[n] = script[n].status;
    for (n=0; n<nb_scripts; n++) {
	if (status[n]) {
	    for (int l=0; l<script[n].nb_lines; l++)
		run_console_command(script[n].lines[l]);
	    if (!script[n].looping)
		script[n].status = 0;
	}
    }
    delete status;
}

static FILE *fscript;

static void get_script_commands(char *field) {
  if (strcmp(field,".")) {
    fprintf(fscript,"  %s\n",field);
    cons->print("  %s",field);
    *field = 0;
  } else {
    fprintf(fscript,"\n");
    fclose(fscript);
    cons->print("your script has been recorded");
    cons->end_interactive();
  }
}

static void get_script_mode(char *field) {
  if (!*field) {
    cons->print("executed only once");
  } else {
    cons->print("looping script");
    fprintf(fscript," always");
  }
  *field = 0;
  fprintf(fscript,"\n");
  cons->print("now type your commands, a . to finish...");
  cons->set_interactive(&get_script_commands);
}

static void get_script_name(char *field) {
  fprintf(fscript,"script \"%s\"",field);
  cons->print("  %s",field);
  *field = 0;
  cons->print("Type return for a script which is executed only once, or type any text + return for a script which loops until manually stopped");
  cons->set_interactive(&get_script_mode);
}

void do_start_script(int argc, char **argv) {
    if (argc != 2)
	throw "Syntax : start_script name\n";
    for (int n=0; n<nb_scripts; n++) {
	if (!strcmp(script[n].title,argv[1])) {
	    script[n].status = 1;
	    return;
	}
    }
    cons->print("Didn't find script %s",argv[1]);
}

void do_script(int argc, char **argv) {
  char *s = get_script_name(1);
  fscript = fopen(s,"a");
  if (!fscript) {
    cons->print("can't create file %s",s);
    return;
  }
  if (argc == 1) {
    cons->print("Please type the script description (spaces allowed)");
    cons->set_interactive(&get_script_name);
  } else {
    fprintf(fscript,"script \"%s\"",argv[1]);
    if (argc == 3) {
      get_script_mode(argv[2]);
    } else {
      get_script_mode("");
    }
  }
}

