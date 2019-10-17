#include <stdio.h>
#include <stdarg.h>
#include <muParser.h>
#include "raine.h"
#include "version.h"
#include "tfont.h"
#include "tedit.h"
#include "control.h"
#include "sdl/control_internal.h"
#include "tconsole.h"
#include "sdl/dialogs/messagebox.h"
#include "games.h"

void split_command(char *field, char **argv, int *argc, int max) {
  char *s = field;
  *argc = 0;
  while (*s && (*s == ' ' || *s==9)) // skip the leading spaces
    s++;
  if (*s) argv[(*argc)++] = s;
  while (*s) {
    while (*s != ' ' && *s)  {
      if (*s == '"') {
	s++;
	while (*s != '"' && *s)
	  s++;
      } else if (*s == 0x27 /* ' */) {
	s++;
	while (*s != 0x27 /* ' */ && *s)
	  s++;
      }
      s++;
    }
    if (*s == ' ' || *s==9) {
      *s++ = 0;
      while (*s == ' ' || *s==9)
	s++;
      if (*s)
	argv[(*argc)++] = s;
    }
  }
}

static int dummy_handler(int cause) { return 0; }

TConsole::TConsole(char *my_title, char *init_label, int maxlen, int maxlines, commands_t *mycmd) :
  TDialog(my_title,NULL)
{
  int dummy_int;
  commands = mycmd;
  nb_alloc = maxlines;
  nb_disp_items = 0;
  menu = (menu_item_t*)malloc(sizeof(menu_item_t) * (nb_alloc+1));
  memset(&menu[0],0,sizeof(menu_item_t) * (nb_alloc+1));
  nb_items = 0;
  font_name = "VeraMono.ttf";
  len_max = maxlen;
  field = new char[len_max*2]; // len_max*2 to have room for eventual
  *field = 0;
  // expansions (base conversion...)
  edit_menu.label = init_label; // not used, but must not be NULL to show this field
  edit_menu.menu_func = dummy_handler;// must contain something to gain focus
  edit_menu.value_int = &dummy_int; // must also be != NULL for the extension
  // to be detected...
  edit_menu.values_list_size = ITEM_EDIT;
  edit_menu.values_list_label[0] = field;
  edit_menu.values_list[0] = maxlen;
  edit_menu.values_list[1] = 1; // use history
  edit_menu.values_list[2] = work_area.w*3/4; // width
  edit_child = new TEdit(&edit_menu);
  visible = 1;
  interactive = NULL;
  TConsole::print(pretty_emu_name " " VERSION " console based on muParser v%s", mu::Parser().GetVersion().c_str());
  visible = 0;
}

TConsole::~TConsole() {
  for (int n=0; n<nb_items; n++) {
    free((void*)menu[n].label);
  }
  free(menu);
  delete edit_child;
  delete field;
}

void TConsole::save_history() {
    char buf[FILENAME_MAX];
    snprintf(buf,FILENAME_MAX,"%ssavedata" SLASH "%s.hist", dir_cfg.exe_path, current_game->main_name);
    edit_child->save_history(buf);
}

void TConsole::load_history() {
    if (current_game) {
	char buf[FILENAME_MAX];
	snprintf(buf,FILENAME_MAX,"%ssavedata" SLASH "%s.hist", dir_cfg.exe_path, current_game->main_name);
	edit_child->load_history(buf);
    }
}

/* void TConsole::compute_nb_items() {
  // We must init nb_disp_itmes / menu_disp here
  nb_disp_items = nb_items;
  menu_disp = menu;
} */

void TConsole::draw() {
  TDialog::draw();
  visible = 1;
}

UINT32 ansilen(const char *s) {
  // strlen which skips ansi esc sequences
  int len = 0;
  while (*s) {
    if (*s == 27) {
      while (*s != 'm')
	s++;
      s++;
      continue;
    }
    len++;
    s++;
  }
  return len;
}

char* ansistr(char *s,int n) {
  // convert a len on a string without esc sequences to a len with esc
  while (*s && n>0) {
    if (*s == 27) {
      while (*s != 'm')
	s++;
      continue;
    }
    n--;
    s++;
  }
  return s;
}

void TConsole::print(const char *format, ...)
{
  if (!visible) {
    return;
  }
  char string[2048],*s;
  va_list ap = NULL;
  va_start(ap,format);
  vsprintf(string,format,ap);
  va_end(ap);

  // 1) split the string at \n if there are some...
  while ((s = strstr(string,"\n"))) {
    *s = 0;
    print(string);
    strcpy(string,&s[1]);
  }

  // 2 extend tabs
  while ((s = strchr(string,9))) {
    *s = 0;
    int len_tab = 8-ansilen(string)%8;
    *s = 9;
    if (len_tab > 1)
      memmove(s+len_tab-1,s,strlen(s)+1);
    int n;
    for (n=0; n<len_tab; n++)
      s[n] = ' ';
  }

  // limit the prints to len_max
  while (ansilen(string) > len_max) {
    char *pos = ansistr(string,len_max);
    char old = *pos;
    *pos = 0;
    char *s = strrchr(string,' ');
    if (s) {
      *s = 0;
      print(string);
      *pos = old;
      strcpy(string,s+1);
    } else {
      print(string);
      *pos = old;
      strcpy(string,pos);
    }
  }

  if (nb_items == nb_alloc) {
    free((void*)menu[0].label);
    memcpy(&menu[0],&menu[1],(nb_items-1)*sizeof(menu_item_t));
    /* The beauty of this thing is that the child array doesn't have to be
     * changed : its elements point to menu entries which don't move, it's the
     * contents of the menu entries which move, not the menu entries themselves
     */
    nb_items--;
  } else {
    nb_disp_items++;
    menu_disp = (int*)realloc(menu_disp,sizeof(int)*(nb_disp_items));
    menu_disp[nb_disp_items-1] = nb_disp_items-1;
    if (nb_items == 1 || child != last_child) { // 1st allocation after compute_nb_items
	int is_zero = (child == NULL);
      child = (TStatic **)realloc(child,sizeof(TStatic*)*nb_alloc);
      if (is_zero) {
	  memset(child,0,sizeof(TStatic*)*nb_alloc);
	  nb_items = 0;
      }
      last_child = child;
    }
  }
  // memcpy(&menu[nb_items],&menu[nb_items-1],sizeof(menu_item_t));
  menu[nb_items].label = strdup(string);
  if (child)
    child[nb_items] = new TStatic(&menu[nb_items]);
  nb_items++;

  draw();
  post_print();
}

void TConsole::post_print() {
  // this function is here only to be overloaded
}

int TConsole::get_fglayer_footer_height() {
  if (font)
    return edit_child->get_height(font);
  return 0;
}

int TConsole::get_fglayer_footer_len() {
  return edit_child->get_len();
}

static int myx, myy, myw, myh, myxoptions;
void TConsole::display_fglayer_footer(int x,int &y,int w, int xoptions) {
  myx = x; myy=y; myw =w; myh=edit_child->get_height(font);
  myxoptions=xoptions;
  edit_child->disp(fg_layer,font,x,y,w,myh,fg,bg,
    xoptions);
}

void TConsole::setup_fg_layer() {
  TDialog::setup_fg_layer();
  // keep the lift down when printing
  if (lift)
    top = nb_disp_items - rows;
}

void TConsole::fglayer_footer_update() {
  edit_child->update();
  SDL_Rect dst;
  dst.x = myx; dst.y = myy; dst.w = myw; dst.h = myh;
  SDL_FillRect(fg_layer,&dst,bgsdl);
  edit_child->disp(fg_layer,font,myx,myy,myw,myh,fg,bg,
	  myxoptions);
  SDL_Rect to;
  to.x = dst.x + fgdst.x; to.y = dst.y+fgdst.y;
  SDL_BlitSurface(fg_layer,&dst,sdl_screen,&to);
  do_update(&to);
}

int TConsole::fglayer_footer_handle_key(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    if (event->key.keysym.sym == SDLK_TAB) {
      // completion
      commands_t *cmd = commands;
      while (cmd->name) {
	if (!strncasecmp(field,cmd->name,strlen(field))) {
	  sprintf(field,"%s ",cmd->name);
	  event->key.keysym.sym = SDLK_END;
	  break;
	}
	cmd++;
      }
      if (!cmd->name) { // not found
	if (!strncasecmp(field,"help",strlen(field))) { // help is not a standard command
	  strcpy(field,"help ");
	  event->key.keysym.sym = SDLK_END;
	}
      }
    } else if ((key_console < 0x200 && event->key.keysym.sym == key_console) ||
               (key_console > 0x200 && event->key.keysym.scancode == key_console-0x200)) {
      // 0x200 is to handle "unknown" keys ie, keys without a SDLK constant
      exit_menu = 1;
      return 0;
    }
  }

  return edit_child->handle_key(event);
}

void TConsole::fglayer_footer_call_handler() {
  exit_menu = handler(1);
}

void TConsole::unknown_command(int argc, char **argv) {
  print("command unknown");
}

void TConsole::do_help(int argc, char **argv) {
  if (argc > 2) {
    print("syntax: help [command]");
    return;
  }

  commands_t *cmd = commands;
  while (cmd->name) {
    if (argc == 1) { // general help
      if (cmd->help) {
	if (cmd->long_help) {
	  print("*%s",cmd->help);
	} else
	  print(" %s",cmd->help);
      }
    } else if (!strcasecmp(argv[1],cmd->name)) {
      print(cmd->help);
      if (cmd->long_help) {
	print(cmd->long_help);
      } else {
	print("no more help");
      }
    }
    cmd++;
  }
  if (argc == 1) {
    print(" exit : exit (or use the ESC key !!!)");
    print("\nCommands preceded by * have an extended help, type\nhelp command for the details");
  }
  *field = 0;
}

int TConsole::run_cmd(char *string) {
  int len = strlen(string);
  while (len && string[len-1] < 32)
    string[--len] = 0;
  if (interactive) {
    interactive(string);
    return 0;
  }
  char *argv[10];
  int argc;
  if (field != string) {
    strncpy(field,string,len_max*2);
    field[len_max*2-1] = 0;
  }
  if (*field) {
    if (!strchr(field,'#'))
      print("\E[31m>\E[0m %s",field);
    if (!strcasecmp(field,"exit")) {
      *field = 0;
      return 1;
    }
    split_command(field,argv,&argc,10);
    if (argc < 1) { *field = 0; return 0; } // empty line (or spaces)
    if (argv[0][0] == '#') {
      *field = 0;
      return 0; // comment
    }
    if (!strcasecmp(argv[0],"help") || !strcmp(argv[0],"?")) {
      do_help(argc, argv);
      *field = 0;
      return 0;
    }
    commands_t *cmd = commands;
    try {
      while (cmd->name) {
	if (!strcasecmp(cmd->name,argv[0])) {
	  (*cmd->handler)(argc,argv);
	  break;
	}
	cmd++;
      }
      if (!cmd->name) {
	unknown_command(argc,argv);
      }
    }
    /* Exception handling :
     * C++ obliges to use classes if you want to do something as simple as
     * passing more than 1 parameter to the catch (message + value).
     * Anyway, the easiest way to do it I found until now is to have 2 handlers
     * 1 which takes a ConsExcept class as argument, and which can handle
     * any printf message
     * and the other one which handles a single string argument for simple
     * error messages without arguments.
     * Notice that if you pass a temporary string in which you use sprintf for
     * example by throw, then the temporary string is never freed (or so I have
     * read), so it's better to use a class by reference instead of this. */
    catch(ConsExcept &e) {
      if (visible) print(e.what());
      else {
	MessageBox("script error",e.what(),"ok");
      }
    }
    catch(const char *msg) {
      if (visible) print(msg);
      else {
	MessageBox("script error",(char *)msg,"ok");
      }
    }
    *field = 0;
  }
  return 0;
}

int TConsole::handler(int cause) {
  return run_cmd(field);
}

void TConsole::execute()
{
    key_console = get_console_key();
    TDialog::execute();
    visible = 0;
}
