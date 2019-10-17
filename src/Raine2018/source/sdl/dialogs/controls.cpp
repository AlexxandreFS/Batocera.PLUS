#include "../gui/menu.h"
#include "../compat.h"
#include "control.h"
#include "sdl/control_internal.h"
#include "sdl/dialogs/messagebox.h"
#include "sdl/dialogs/about.h" // TMoveStatic
#include "games.h" // current_game
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "ingame.h"
#include "newmem.h"
#include "sdl/gui/tedit.h"
#include "files.h"

/* This is currently the bigest file in the dialogs directory.
 * But it's not because of long complicated code, it's just because it does
 * a lot of things, like translating inputs to text for keyboard, joystick
 * and mouse, mapping the hat to joystick events, setup the autofire, and
 * finally setup the analog inputs.
 * None of this is complicated, but together it produces a big file... ! */

static UINT32 inp_key,inp_joy,inp_mouse;
static menu_item_t *menu;

static char *get_joy_name(int code) {
  if (!code)
    return strdup("");
  else if ((code & 0xff)-1 >= SDL_NumJoysticks())
      return strdup("Not here");
  char name[80];
  // sprintf(name,"Joy %d ",code & 0xff);
  snprintf(name,30,"Joy %d (%s",code & 0xff,joy_name[(code & 0xff)-1]);
  name[30] = 0;
  if (strlen(name) == 29)
      strcat(name,"...");
  strcat(name,") ");

  int stick = (code >> 8) & 0xff;
  int btn = (code >> 16) & 0xff;
  if (!btn) {
    char *direction;
    if (stick & 2) {
      if (stick & 1)
        direction = _("DOWN");
      else
	direction = _("UP");
    } else {
      if (stick & 1)
	direction = _("RIGHT");
      else
	direction = _("LEFT");
    }
    sprintf(&name[strlen(name)],"Stick %d %s",stick/4,direction);
    return strdup(name);
  }
  sprintf(&name[strlen(name)],"Btn %d",btn);
  return strdup(name);
}

static char *get_key_name(int key) {
  char keyname[80];
  keyname[0] = 0;
  int mod = key>>16;
  key &= 0xffff;
  if (mod & KMOD_LCTRL)
    strcat(keyname,"LCTRL ");
  if (mod & KMOD_RCTRL)
    strcat(keyname,"RCTRL ");
  if (mod & KMOD_LSHIFT)
    strcat(keyname,"LSHIFT ");
  if (mod & KMOD_RSHIFT)
    strcat(keyname,"RSHIFT ");
  if (mod & KMOD_LALT)
    strcat(keyname,"LALT ");
  if (mod & KMOD_RALT)
    strcat(keyname,"RALT ");
  strcat(keyname,SDL_GetKeyName((SDLKey)key));
  if (key & 0x200) { // special scancode encoding for unknown keys
    sprintf(&keyname[strlen(keyname)]," (%x)",key & 0x1ff);
  }
  return strdup(keyname);
}

static char *get_mouse_name(int btn) {
  if (!btn) return strdup("");
  char text[20];
  sprintf(text,"Mouse btn %d",btn);
  return strdup(text);
}

class TMyMenuMultiCol : public TMenuMultiCol
{
    public:
    TMyMenuMultiCol(char *my_title, menu_item_t *mymenu, int nbcol, char **mycols) : TMenuMultiCol(my_title,mymenu,nbcol,mycols)
    {}
    void create_child(int n) {
	if (!menu[n].value_int)
	    child[n] = new TMoveStatic(&menu[n]);
	else
	    TMenu::create_child(n);
    }
};

static TMyMenuMultiCol *controls;

class TInput : public TDialog {
  private:
    int must_handle_mouse,ignore_mod,must_handle_joy;
  public:
    TInput(char *my_title, menu_item_t *menu,int hmouse,int imod, int hjoy=1) : TDialog(my_title,menu)
    { must_handle_mouse = hmouse;
		  must_handle_joy = hjoy;
      ignore_mod = imod;
    }
    virtual void handle_key(SDL_Event *event);
    virtual void handle_mouse(SDL_Event *event);
    virtual void handle_joystick(SDL_Event *event);
};

void TInput::handle_key(SDL_Event *event) {
  switch (event->type) {
    case SDL_KEYDOWN:
      if (ignore_mod) {
	switch(event->key.keysym.sym) {
        case SDLK_LCTRL:
	case SDLK_RCTRL:
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
	case SDLK_LALT:
	case SDLK_RALT:
	  return;
	default:
	  break;
	}
      }
      if (event->key.keysym.sym) {
	inp_key = event->key.keysym.sym | ((event->key.keysym.mod & 0x4fc3) << 16);
      } else {
	inp_key = (event->key.keysym.scancode|0x200) | ((event->key.keysym.mod & 0x4fc3) << 16);
      }
      exit_menu = 1;
  }
}

void TInput::handle_joystick(SDL_Event *event) {
	if (!must_handle_joy)
		return;
  int which, axis, value,hat;
  switch (event->type) {
    case SDL_JOYAXISMOTION:
      which = event->jaxis.which+1;
      axis = event->jaxis.axis;
      value = event->jaxis.value;
      if (which >= MAX_JOY || axis >= MAX_AXIS) {
	return;
      }
      if (bad_axes[MAX_AXIS*(which-1)+axis]) {
	  printf("skipping bad axis\n");
	  return;
      }
      if (axis > SDL_JoystickNumAxes(joy[which-1]))
	  return;
      if (value < -20000) {
	inp_joy = JOY(which,AXIS_LEFT(axis),0,0);
	exit_menu = 1;
      } else if (value > 20000) {
	inp_joy = JOY(which,AXIS_RIGHT(axis),0,0);
	exit_menu = 1;
      }
      break;
    case SDL_JOYBUTTONUP:
      inp_joy = JOY(event->jbutton.which+1,0,event->jbutton.button+1,0);
      exit_menu = 1;
      break;
    case SDL_JOYHATMOTION:
      which = event->jhat.which;
      hat = event->jhat.hat;
      axis = get_axis_from_hat(which,hat);
      which++;
      switch(event->jhat.value) { // take only 1 of the 4 positions
	case SDL_HAT_LEFT:
	  inp_joy = JOY(which,AXIS_LEFT(axis),0,0);
	  exit_menu = 1;
	  break;
	case SDL_HAT_UP:
	  inp_joy = JOY(which,AXIS_LEFT(axis+1),0,0);
	  exit_menu = 1;
	  break;
	case SDL_HAT_RIGHT:
	  inp_joy = JOY(which,AXIS_RIGHT(axis),0,0);
	  exit_menu = 1;
	  break;
	case SDL_HAT_DOWN:
	  inp_joy = JOY(which,AXIS_RIGHT(axis+1),0,0);
	  exit_menu = 1;
	  break;
      }
      break;
  }
}

void TInput::handle_mouse(SDL_Event *event) {
  if (event->type == SDL_MOUSEBUTTONUP && must_handle_mouse) {
    inp_mouse = event->button.button;
    exit_menu = 1;
  }
}

static menu_item_t menu_input[] =
{
  { _("Press a key, a button, or move a joystick...") },
  { _("or escape to delete this control") },
  { NULL },
};

static menu_item_t kb_only[] =
{
  { _("Press a key...") },
  { NULL },
};

static char **cols;
static int base_input;

static int get_def_indice(const char *name) {
    int nb = raine_get_emu_nb_ctrl();
    for (int n=0; n<nb; n++)
	if (!strcmp(def_input_emu[n].name,name))
	    return n;
    printf("not found def_input_emu name : %s\n",name);
    exit(1);
    return -1;
}

static int do_input(int sel) {
  inp_key = inp_joy = inp_mouse = 0;
  int indice = get_def_indice(menu[sel].label);
  TInput *input = new TInput(_("Input"),menu_input,0,1);
  input->execute();
  delete input;
  if (inp_key) {
    if (inp_key == SDLK_ESCAPE) {
      int ret = MessageBox(_("Question"),_("What do you want to do ?"),
        _("Delete the key|"
	"Delete the joystick ctrl|"
	"Really use ESC here"));
      switch(ret) {
	case 1: def_input_emu[indice].scancode = 0;
		free(cols[sel*2+0]);
		cols[sel*2+0] = strdup("no key");
		break;
	case 2: def_input_emu[indice].joycode = 0;
		free(cols[sel*2+1]);
		cols[sel*2+1] = strdup("");
		break;
	case 3:
		def_input_emu[indice].scancode = inp_key;
		free(cols[sel*2+0]);
		cols[sel*2+0] = get_key_name(inp_key);
		break;
      }
    } else {
      def_input_emu[indice].scancode = inp_key;
      free(cols[sel*2+0]);
      cols[sel*2+0] = get_key_name(inp_key);
    }
  } else {
    def_input_emu[indice].joycode = inp_joy;
    free(cols[sel*2+1]);
    cols[sel*2+1] = get_joy_name(def_input_emu[sel].joycode);
  }
  controls->setup_font(40);
  controls->draw();
  return 0;
}

static int do_kb_input(int sel) {
  // same thing as do_input, but keyboard only (for layers)
  inp_key = inp_joy = inp_mouse = 0;
  TInput *input = new TInput(_("Input"),kb_only,0,1,0);
  input->execute();
  delete input;
  if (inp_key) {
    if (inp_key == SDLK_ESCAPE) {
      int ret = MessageBox(_("Question"),_("What do you want to do ?"),
        _("Delete the key"));
      switch(ret) {
	case 1:
		layer_info_list[sel].keycode = 0;
		free(cols[sel]);
		cols[sel] = strdup("no key");
		break;
      }
    } else {
      layer_info_list[sel].keycode = inp_key;
      free(cols[sel]);
      cols[sel] = get_key_name(inp_key);
    }
  }
  controls->setup_font(40);
  controls->draw();
  return 0;
}

static int do_input_ingame(int sel) {
  inp_key = inp_joy = inp_mouse = 0;
  int nb = menu[sel].values_list[0];
  TInput *input = new TInput(_("Input"),menu_input,1,0);
  input->execute();
  delete input;
  if (inp_key) {
    if (inp_key == SDLK_ESCAPE) {
      int ret = MessageBox(_("Question"),_("What do you want to do ?"),
        _("Delete the key|"
	"Delete the joystick ctrl|"
	"Del the mouse button"));
      switch(ret) {
	case 1:
		InputList[nb].Key = 0;
		if (!use_custom_keys)
		    def_input[InputList[nb].default_key & 0xFF].scancode = 0;
		free(cols[sel*3+0]);
		cols[sel*3+0] = strdup("no key");
		break;
	case 2:
		InputList[nb].Joy = 0;
		if (!use_custom_keys)
		    def_input[InputList[nb].default_key & 0xFF].joycode = 0;
		free(cols[sel*3+1]);
		cols[sel*3+1] = strdup("");
		break;
	case 3:
		InputList[nb].mousebtn = 0;
		if (!use_custom_keys)
		    def_input[InputList[nb].default_key & 0xFF].mousebtn = 0;
		free(cols[sel*3+2]);
		cols[sel*3+2] = strdup("");
		break;
      }
    } else {
      InputList[nb].Key = inp_key;
      if (!use_custom_keys && !base_input) {
	def_input[InputList[nb].default_key & 0xff].scancode = inp_key;
	printf("defaults updated\n");
      } else {
	printf("defaults not updated use_custom %d base_input %d\n",use_custom_keys,base_input);
      }
      free(cols[sel*3+0]);
      cols[sel*3+0] = get_key_name(inp_key);
    }
  } else if (inp_joy) {
    InputList[nb].Joy = inp_joy;
    if (!use_custom_keys && !base_input)
      def_input[InputList[nb].default_key & 0xff].joycode = inp_joy;
    free(cols[sel*3+1]);
    cols[sel*3+1] = get_joy_name(inp_joy);
  } else if (inp_mouse) {
    InputList[nb].mousebtn = inp_mouse;
    if (!use_custom_keys && !base_input)
      def_input[InputList[nb].default_key & 0xff].mousebtn = inp_mouse;
    free(cols[sel*3+2]);
    cols[sel*3+2] = get_mouse_name(inp_mouse);
  }

  controls->setup_font(40);
  controls->draw();
  return 0;
}

static int do_emu_controls(int sel) {
  int nb = raine_get_emu_nb_ctrl();
  menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  cols = (char**)malloc(sizeof(char*)*nb*2);
  for (int n=0; n<nb; n++) {
    menu[n].label = def_input_emu[n].name;
    menu[n].menu_func = &do_input;
    cols[n*2+0] = get_key_name(def_input_emu[n].scancode);
    cols[n*2+1] = get_joy_name(def_input_emu[n].joycode);
  }
  for (int a=0; a<nb; a++)
      for (int b=a+1; b<nb; b++)
	  if (strcmp(menu[b].label,menu[a].label) < 0) {
	      menu_item_t temp = menu[a];
	      menu[a] = menu[b];
	      menu[b] = temp;
	      char *str = cols[a*2+0];
	      cols[a*2] = cols[b*2];
	      cols[b*2] = str;
	      str = cols[a*2+1];
	      cols[a*2+1] = cols[b*2+1];
	      cols[b*2+1] = str;
	  }

  controls = new TMyMenuMultiCol(_("Raine Controls"),menu,2,cols);
  controls->execute();
  delete controls;
  for (int n=0; n<nb*2; n++) {
    free(cols[n]);
  }
  free(cols);
  free(menu);
  return 0;
}

static int do_layers_controls(int sel) {
  int nb = layer_info_count;
  menu_item_t *menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  cols = (char**)malloc(sizeof(char*)*nb);
  for (int n=0; n<nb; n++) {
    menu[n].label = layer_info_list[n].name;
    menu[n].menu_func = &do_kb_input;
    cols[n] = get_key_name(layer_info_list[n].keycode);
  }
  // A multi column dialog of only 1 column... oh well it is to copy the way
  // the other inputs dialogs work, and it might be easier this way anyway...
  controls = new TMyMenuMultiCol(_("Raine Controls"),menu,1,cols);
  controls->execute();
  delete controls;
  for (int n=0; n<nb; n++) {
    free(cols[n]);
  }
  free(cols);
  free(menu);
  return 0;
}

static char* convert_command(char *cmd) {
    // Convert a standard input string to a command.dat string
    char buff[40];
    char *start = cmd;
    buff[0] = 0;
    if (strncmp(cmd,"Player",6) ||
	    (cmd[7] != ' ')) {
	if (cmd[0] != 'P' || cmd[1] < '1' || cmd[1] > '4' || cmd[2] != ' ')
	    return strdup(cmd);
	else
	    cmd += 3;
    } else
	cmd += 8;
    char *end = buff+strlen(buff);
    sprintf(end,_("Player"));
    end += strlen(end);
    sprintf(end,"%c ",cmd[-2]);
    end += 2;

    // standard controls (b1..b6) ar converted to cps format when displayed
    // by command.dat processing
    if (!strncmp(cmd,"Button",6) && cmd[6] >= '1' && cmd[6] <= '6')
	sprintf(end,"^%c",'E'+cmd[6]-'1');
    // cps1 6 buttons naming
    else if (!strcmp(cmd,"Jab Punch"))
	sprintf(end,"^E");
    else if (!strcmp(cmd,"Strong Punch"))
	sprintf(end,"^F");
    else if (!strcmp(cmd,"Fierce Punch"))
	sprintf(end,"^G");
    else if (!strcmp(cmd,"Short Kick"))
	sprintf(end,"^H");
    else if (!strcmp(cmd,"Forward Kick"))
	sprintf(end,"^I");
    else if (!strcmp(cmd,"Roundhouse Kick"))
	sprintf(end,"^J");
    else if (!strcmp(cmd,"3P") || !strcmp(cmd,"B1+B2+B3"))
	sprintf(end,"^U");
    else if (!strcmp(cmd,"3K") || !strcmp(cmd,"B4+B5+B6"))
	sprintf(end,"^T");

    else if (!strcmp(cmd,"Up"))
	sprintf(end,"_8");
    else if (!strcmp(cmd,"Down"))
	sprintf(end,"_2");
    else if (!strcmp(cmd,"Left"))
	sprintf(end,"_4");
    else if (!strcmp(cmd,"Right"))
	sprintf(end,"_6");
    else if (cmd[1] == 0 && (cmd[0] >= 'A' && cmd[0] <= 'D')) // Single button
	sprintf(end,"_%c",cmd[0]);
    else if (!strcmp(cmd,"A+B"))
	sprintf(end,"_A+_B");
    else if (!strcmp(cmd,"B1+B2"))
	sprintf(end,"^E+^F");
    else if (!strcmp(cmd,"B+C"))
	sprintf(end,"_B+_C");
    else if (!strcmp(cmd,"C+D"))
	sprintf(end,"_C+_D");
    else if (!strcmp(cmd,"A+B+C"))
	sprintf(end,"_A+_B+_C");
    else if (!strcmp(cmd,"B+C+D"))
	sprintf(end,"_B+_C+_D");
    else
	return strdup(start);
    return strdup(buff);
}

static int do_ingame_controls(int sel) {
  int nb = InputCount,mynb;
  menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  cols = (char**)malloc(sizeof(char*)*nb*3);
  mynb = 0;
  base_input = 0;
  int categ[0x100];
  int n;
  for (n=0; n<nb; n++) {
    if ((sel >= 0 && (InputList[n].link == 0 || InputList[n].link > n)) ||
        (sel < 0 && InputList[n].link > 0 && InputList[n].link < n)) {
      if (sel < 0 && !base_input)
	base_input = n;
      menu[mynb].label = convert_command(InputList[n].InputName);
      menu[mynb].menu_func = &do_input_ingame;
      menu[mynb].values_list[0] = n;
      cols[mynb*3+0] = get_key_name(InputList[n].Key);
      cols[mynb*3+1] = get_joy_name(InputList[n].Joy);
      cols[mynb*3+2] = get_mouse_name(InputList[n].mousebtn);
      categ[mynb] = def_input[InputList[n].default_key & 0xff].categ;
      mynb++;
    }
  }
  for (int a=0; a<mynb; a++)
      for (int b=a+1; b<mynb; b++)
	  if (categ[b] < categ[a] || (categ[b] == categ[a] &&
		      strcmp(menu[b].label,menu[a].label) < 0)) {
	      int truc = categ[a];
	      categ[a] = categ[b];
	      categ[b] = truc;
	      menu_item_t temp = menu[a];
	      menu[a] = menu[b];
	      menu[b] = temp;
	      char *str = cols[a*3+0];
	      cols[a*3] = cols[b*3];
	      cols[b*3] = str;
	      str = cols[a*3+1];
	      cols[a*3+1] = cols[b*3+1];
	      cols[b*3+1] = str;
	      str = cols[a*3+2];
	      cols[a*3+2] = cols[b*3+2];
	      cols[b*3+2] = str;
	  }
  controls = new TMyMenuMultiCol(_("Ingame Controls"),menu,3,cols);
  controls->execute();
  delete controls;
  for (n=0; n<mynb*3; n++) {
    free(cols[n]);
  }
  free(cols);
  for (n=0; n<mynb; n++) {
      free((void*)menu[n].label);
  }
  free(menu);
  return 0;
}

class TControl : public TMenu {
  public:
    TControl(char *myname, menu_item_t *menu) : TMenu(myname,menu)
    {}
    int can_be_displayed(int n) {
      if (n == 1 && !current_game)
	return 0;
      if (n == 5) { // autofire controls
	int n,nb = InputCount,nb_autofire;
	nb_autofire = 0;
	for (n=0; n<nb; n++) {
	  if (InputList[n].auto_rate) {
	    nb_autofire++;
	    break;
	  }
	}
	return nb_autofire; // works only if some controls have autofire
      }
      if (n == 3) // layers
	return layer_info_count;
      if (n >= 7) // all load/save inputs
	  return use_custom_keys;
      return 1;
    }
};

static int revert_to_default(int);
static int switch_to_custom(int);
static TControl *ctrl;

static int setup_autofire(int sel) {
  int nb = InputCount,mynb,x,n;
  menu_item_t *menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  mynb=0;
  for (n=0; n<nb; n++) {
    if ((strstr(InputList[n].InputName,"utton") ||
	  (InputList[n].default_key >= KB_DEF_P1_B1 &&
	   InputList[n].default_key <= KB_DEF_P1_B8) ||
	  (InputList[n].default_key >= KB_DEF_P2_B1 &&
	   InputList[n].default_key <= KB_DEF_P2_B8) ||
	  (InputList[n].default_key >= KB_DEF_P3_B1 &&
	   InputList[n].default_key <= KB_DEF_P3_B8) ||
	  (InputList[n].default_key >= KB_DEF_P4_B1 &&
	   InputList[n].default_key <= KB_DEF_P4_B8)) &&
	  InputList[n].link < n) {
      menu[mynb].label = InputList[n].InputName;
      menu[mynb].value_int = &InputList[n].auto_rate;
      menu[mynb].values_list_size = 6;
      for (x=0; x<6; x++)
	menu[mynb].values_list[x] = x;
      menu[mynb].values_list_label[0] = _("Off");
      menu[mynb].values_list_label[1] = _("30 fps");
      menu[mynb].values_list_label[2] = _("15 fps");
      menu[mynb].values_list_label[3] = _("10 fps");
      menu[mynb].values_list_label[4] = _("7 fps");
      menu[mynb].values_list_label[5] = _("6 fps");
      mynb++;
    }
  }
  if (mynb == 0) {
    MessageBox(_("Error"),_("No buttons mapped by this game for autofire, sorry !"));
    free(menu);
    return 0;
  }
  TMenu *controls = new TMenu(_("Autofire..."),menu);
  controls->execute();
  delete controls;
  // Now we must check if autofire was disabled for a newly created control
  for (n=0; n<nb; n++) {
    if (InputList[n].link && InputList[n].link < n && !InputList[n].auto_rate){
      InputList[InputList[n].link].link = 0;
      if (n < InputCount-1) { // This isn't the last input, bad luck !
	for (x=0; x<n; x++) {
	  if (InputList[x].link > n)
	    InputList[x].link--;
	}
	memcpy(&InputList[n],&InputList[n+1],(InputCount-1-n)*sizeof(INPUT));
      }
      InputCount--;
    }
  }
  if (!use_custom_keys) {
    // check if auto fire was enabled, in this case switch to custom controls
    for (n=0; n<nb; n++) {
      if (InputList[n].auto_rate) {
	use_custom_keys = 1;
	break;
      }
    }
  }
  free(menu);
  return 0;
}

static int autofire_controls(int sel) {
  /* When this function is called, there are some controls with autofire
   * enabled. We'll just create new entries in InputList for them and allow
   * the user to choose new controls for these */
  int n;
  for (n=0; n<InputCount; n++) {
    if (InputList[n].auto_rate && InputList[n].link == 0) {
      if (InputCount >= MAX_INPUTS-1) {
	MessageBox(_("Error"),_("Too many controls have been defined for this game, sorry !"));
	return 0;
      }
      InputList[InputCount] = InputList[n];
      InputList[n].link = InputCount;
      InputList[InputCount].link = n;
      InputList[n].auto_rate = 0;
      InputList[InputCount].Key = 0;
      InputList[InputCount].Joy = 0;
      InputList[InputCount].mousebtn = 0;
      char s[120];
      sprintf(s,"%s %s",_("Autofire"),_(InputList[n].InputName));
      InputList[InputCount].InputName = (char*)AllocateMem(strlen(s)+1);
      strcpy(InputList[InputCount].InputName,s);
      InputCount++;
    }
  }
  return do_ingame_controls(-1);
}

class TCalibrate : public TBitmap_menu {
  protected:
    int cx,cy; // coordinates of the stick (real time)
    int myy; // remember y start of bitmap
  public:
    TCalibrate(char *my_title, menu_item_t *mymenu) :
      TBitmap_menu(my_title,mymenu," ") { cx = cy = 0; }
    virtual void setup_font(unsigned int len_frame);
    virtual int compute_fglayer_height();
    virtual void display_fglayer_header(int &y);
    virtual void skip_fglayer_header(int &y);
    virtual void handle_joystick(SDL_Event *event);
};

void TCalibrate::setup_font(unsigned int len_frame) {
  TMenu::setup_font(len_frame);
  int h;
  h = (sdl_screen->h-width_max-2)/(nb_items + 4 + 6); // margin
  if (h < font->get_font_height() && h < font->get_font_width()) {
    delete font;
    font = new TFont_ttf(h);
    compute_width_from_font();
  }
}

int TCalibrate::compute_fglayer_height() {
  int h = TMenu::compute_fglayer_height();
  h+=width_max;
  return h;
}

#define analog2screen(x) ((w-20)/2+(x)*(w-20)/(2*32767))

void TCalibrate::display_fglayer_header(int &y) {
  int w = fg_layer->w;
  int by = y+(w-20)/2; // center
  int bx = w/2;
  myy = y;

  boxColor(fg_layer,10,by-10,w-20,by+10,bg_frame);
  boxColor(fg_layer,bx-10,y,bx+10,y+w-20,bg_frame);

  // Horizontal
  if (analog_minx || analog_maxx)
    boxColor(fg_layer,10+analog2screen(analog_minx),by-10,
     10+analog2screen(analog_maxx),by+10,mymakecol(255,0,0));
  if (cx)
    vlineColor(fg_layer,10+analog2screen(cx),by-10,by+10,mymakecol(255,255,255));

  // vertical
  if (analog_miny || analog_maxy)
    boxColor(fg_layer,bx-10,y+analog2screen(analog_miny),
      bx+10,y+analog2screen(analog_maxy),mymakecol(255,0,0));
  if (cy)
    hlineColor(fg_layer,bx-10,bx+10,y+analog2screen(cy),mymakecol(255,255,255));
  y += fg_layer->w-18;
}

void TCalibrate::skip_fglayer_header(int &y) {
  if (fg_layer)
    y += fg_layer->w-18;
}

void TCalibrate::handle_joystick(SDL_Event *event) {
  switch (event->type) {
  case SDL_JOYAXISMOTION:
    if (event->jaxis.which == analog_num) {
      if (event->jaxis.axis == 2*analog_stick) {
	cx = event->jaxis.value;
	if (cx < analog_minx)
	  analog_minx = cx;
	else if (cx > analog_maxx)
	  analog_maxx = cx;
      } else if (event->jaxis.axis == 2*analog_stick+1) { // vertical
        cy = event->jaxis.value;
	if (cy < analog_miny)
	  analog_miny = cy;
	else if (cy > analog_maxy)
	  analog_maxy = cy;
      } else
        break;
      int y = myy;
      display_fglayer_header(y);
      SDL_Rect dest,from;
      dest.x = fgdst.x+10;
      dest.y = fgdst.y+10;
      dest.w = fg_layer->w-20;
      dest.h = fg_layer->w-20;
      from.x = 10; from.y = 10;
      from.w = from.h = fg_layer->w-20;
      SDL_FillRect(sdl_screen,&dest,0);
      SDL_BlitSurface(fg_layer,&from,sdl_screen,&dest);
      do_update(&dest);
      // printf("redraw %d %d %d %d cx %d cy %d\n",analog_minx,analog_maxx,analog_miny,analog_maxy,cx,cy);
    }
    break;
  case SDL_JOYBUTTONUP:
    exit_menu = 1;
    break;
  }
}

static int selected;

static int select_joy(int sel) {
  selected = sel;
  return 1;
}

static int setup_analog(int sel) {
  int nb = SDL_NumJoysticks(),n;
  menu_item_t *menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+2));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  selected = nb;
  for (n=0; n<nb; n++) {
    menu[n].label = strdup(joy_name[n]);
    menu[n].menu_func = &select_joy;
  }
  menu[n].label = _("No analog device");
  menu[n].menu_func = &select_joy;
  menu[n+1].label = NULL;
  TMenu *dlg = new TMenu(_("Select analog device"),menu);
  dlg->execute();
  delete dlg;
  if (analog_num != selected) {
    // reset calibration info if the device changes
    analog_minx = analog_maxx = analog_miny = analog_maxy = 0;
  }
  analog_num = selected;
  if (analog_num < nb)
    strcpy(analog_name,menu[analog_num].label);
  for (n=0; n<nb; n++)
    free((void*)menu[n].label);
  free(menu);

  if (analog_num >= nb) {
    analog_num = -1;
    analog_name[0] = 0;
    return 0;
  }
  nb = SDL_JoystickNumAxes(joy[analog_num])/2;
  if (nb == 1) {
    analog_stick = 0;
  } else {
    menu_item_t *menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
    memset(menu,0,sizeof(menu_item_t)*(nb+1));
    for (n=0; n<nb; n++) {
      char buff[20];
      sprintf(buff,"Stick %d",n);
      menu[n].label = strdup(buff);
      menu[n].menu_func = &select_joy;
    }
    selected = 999;
    TMenu *dlg = new TMenu(_("Select the stick to use..."),menu);
    dlg->execute();
    delete dlg;
    for (n=0; n<nb; n++)
      free((void*)menu[n].label);
    free(menu);
    if (selected == 999) {
      // canceled !
      analog_num = -1;
      analog_name[0] = 0;
      return 0;
    }
    analog_stick = selected*2;
  }
  nb = 4;
  menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+1));
  memset(menu,0,sizeof(menu_item_t)*(nb+1));
  menu[0].label = _("Move the stick to all the extreme positions");
  menu[1].label = "If it's a steering wheel, then move it to the max";
  menu[2].label = _("left and right positions, and press then release");
  menu[3].label = _("each pedal separately");
  TCalibrate *cal = new TCalibrate(_("Calibration"),menu);
  cal->execute();
  delete cal;
  free(menu);
  if (analog_minx >= 0 || analog_miny >= 0 || analog_maxx <= 0 ||
      analog_maxy <= 0) {
    // calibration not finished -> give up
    analog_num = -1;
    analog_name[0] = 0;
  }
  return 0;
}

static int do_load(int sel) {
    char str[FILENAME_MAX];
    menu_item_t *menu = NULL;
    int nb_used = 0, nb_alloc = 0;

    snprintf(str,FILENAME_MAX,"%sconfig/games.cfg", dir_cfg.exe_path);
    FILE *f = fopen(str,"r");
    while (f && !feof(f)) {
	myfgets(str,FILENAME_MAX,f);
	char *s = strstr(str,":keyconfig");
	if (s && !strncmp(str,"[$",2)) {
	    if (nb_used == nb_alloc) {
		nb_alloc += 10;
		menu = (menu_item_t*)realloc(menu,sizeof(menu_item_t)*(nb_alloc+1));
		memset(&menu[nb_used],0,sizeof(menu_item_t)*11);
	    }
	    *s = 0;
	    s = &str[2];
	    while ((s = strchr(s,'_')))
		*s = ' ';
	    menu[nb_used].label = strdup(&str[2]);
	    menu[nb_used++].menu_func = &select_joy;
	}
    }
    if (f) fclose(f);
    if (!nb_used) {
	MessageBox(_("Error"),_("Save 1st some custom inputs using\nSave inputs as"));
	return 0;
    }
    selected = -1;
    TDialog *dlg = new TDialog(_("Load from which ?"),menu);
    dlg->execute();
    delete dlg;
    if (selected > -1) {
	raine_push_config_state();

	snprintf(str,FILENAME_MAX,"%sconfig/games.cfg", dir_cfg.exe_path);
	raine_set_config_file(str);

	snprintf(str,FILENAME_MAX,"$%s:keyconfig", menu[selected].label);
	char *s = str;
	while ((s = strchr(s,' ')))
	    *s = '_';
	printf("loading keys from %s\n",str);
	load_game_keys(str);
	raine_pop_config_state();
    }
    for (int n=0; n<nb_used; n++)
	free((void*)menu[n].label);
    free(menu);

    return 0;
}

static int do_save(int sel) {
    char dest[80];
    dest[0] = 0;
    EditDlg("Save as ",dest,20);
    if (dest[0]) {
	char *s = dest;
	while ((s = strchr(s,' ')))
	    *s = '_';
	// Sections must not contain ' ' !
	char str[FILENAME_MAX];
	raine_push_config_state();

	snprintf(str,FILENAME_MAX,"%sconfig/games.cfg", dir_cfg.exe_path);
	raine_set_config_file(str);

	// Save Key Settings

	sprintf(str,"$%s:keyconfig", dest);
	save_game_keys(str);
	raine_pop_config_state();
    }
    return 0;
}

static int get_inputs(int sel) {
    // Looks a lot like do_load, except that it loads directly another game
    // instead, actually a little easier...
    char str[FILENAME_MAX];
    menu_item_t *menu = NULL;
    int nb_used = 0, nb_alloc = 0;

    snprintf(str,FILENAME_MAX,"%sconfig/games.cfg", dir_cfg.exe_path);
    FILE *f = fopen(str,"r");
    char conf[256];
    conf[0] = 0;
    while (f && !feof(f)) {
	myfgets(str,FILENAME_MAX,f);
	char *s = strstr(str,":keyconfig]");
	if (s && strncmp(str,"[$",2) && str[0] == '[') {
	    *s = 0;
	    strncpy(conf,&str[1],256);
	    conf[255] = 0;
	}
	if (!strcmp(str,"use_custom_keys = 1") && conf[0]) {
	    if (nb_used == nb_alloc) {
		nb_alloc += 10;
		menu = (menu_item_t*)realloc(menu,sizeof(menu_item_t)*(nb_alloc+1));
		memset(&menu[nb_used],0,sizeof(menu_item_t)*11);
	    }
	    menu[nb_used].label = strdup(conf);
	    conf[0] = 0;
	    menu[nb_used++].menu_func = &select_joy;
	}
    }
    if (f) fclose(f);
    if (!nb_used) {
	MessageBox(_("Error"),_("No game uses custom inputs in your config file yet"));
	return 0;
    }
    selected = -1;
    TMenu *dlg = new TMenu(_("Load from which ?"),menu);
    dlg->execute();
    delete dlg;
    if (selected > -1) {
	raine_push_config_state();

	snprintf(str,FILENAME_MAX,"%sconfig/games.cfg", dir_cfg.exe_path);
	raine_set_config_file(str);

	snprintf(str,FILENAME_MAX,"%s:keyconfig", menu[selected].label);
	printf("loading keys from %s\n",str);
	load_game_keys(str);
	raine_pop_config_state();
    }
    for (int n=0; n<nb_used; n++)
	free((void*)menu[n].label);
    free(menu);

    return 0;
}

static menu_item_t controls_menu[] =
{
  { _("Raine controls"), &do_emu_controls },
  { "", &do_ingame_controls },
  { _("Revert to default game controls"), &revert_to_default },
  { _("Video layers"), &do_layers_controls },
  { _("Autofire..."), &setup_autofire },
  { _("Autofire controls"), &autofire_controls },
  { _("Analog controls..."), &setup_analog },
  { _("Load inputs from..."), &do_load },
  { _("Save inputs as..."), &do_save },
  { _("Get inputs from another game"), &get_inputs },
  { NULL },
};

static int revert_to_default(int sel) {
  reset_game_keys();
  use_custom_keys = 0;
  controls_menu[1].label = _("Edit default game inputs");
  controls_menu[2].label = _("Switch to custom game controls");
  controls_menu[2].menu_func = &switch_to_custom;
  if (ctrl) {
      ctrl->update_label(1,_("Edit default game inputs"));
      ctrl->update_label(2,_("Switch to custom game controls"),&switch_to_custom);
      ctrl->draw();
  }
  return 0;
}

static int switch_to_custom(int sel) {
  use_custom_keys = 1;
  controls_menu[1].label = _("Edit custom game inputs");
  controls_menu[2].label = _("Revert to default game controls");
  controls_menu[2].menu_func = &revert_to_default;
  if (ctrl) {
      ctrl->update_label(1,_("Edit custom game inputs"));
      ctrl->update_label(2,_("Revert to default game controls"),&revert_to_default);
      ctrl->draw();
  }
  return 0;
}

int do_controls(int sel) {
  if (use_custom_keys) {
    switch_to_custom(0);
  } else if (current_game) {
    revert_to_default(0);
  } else
    controls_menu[2].label = NULL;

  ctrl = new TControl(_("Controls"), controls_menu);
  ctrl->execute();
  delete ctrl;
  ctrl = NULL;
  return 0;
}

