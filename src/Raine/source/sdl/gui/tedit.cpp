#include "tedit.h"
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "sdl/dialogs/messagebox.h"
#include "menu.h"
#include "files.h"

TEdit::TEdit(menu_item_t *my_menu) : TStatic(my_menu)
{
    maxl = menu->values_list[0];
    use_hist = menu->values_list[1];
    maxw = menu->values_list[2];
    cursor_on = 0;
    used_hist = update_count = 0;
    current_hist = -1;
    history[MAX_HISTORY-1] = NULL;
    pos_cursor = old_pos = 0;
    field = menu->values_list_label[0];
    pos = strlen(field);
    is_utf = 0;
}

TEdit::~TEdit()
{
    free_history();
}

void TEdit::free_history() {
    for (int n=0; n<used_hist; n++) {
	free(history[n]);
    }
    used_hist = 0;
}

void TEdit::disp(SDL_Surface *s, TFont *myfont, int x, int y, int w,int h,
  int fg, int bg, int xoptions) {
  font = myfont;
  font->set_utf(is_utf);
  if (*menu->label) {
      // Draw the static without a changing bg
    TStatic::disp(s,myfont,x,y,xoptions-x,h,mymakecol(255,255,255),0,xoptions);
    w -= xoptions - x;
    x = xoptions;
  }
  rectangleColor(s,x,y,x+maxw-1,y+h-1,mymakecol(255,255,255));
  // boxColor(s,x+1,y+1,x+maxw-3,y+h-3,bg_color);
  if (field[0]) {
      int w,h;
      font->dimensions(field,&w,&h);
      // -8 for the size of the cursor in the end..
      int max = (pos == strlen(field) ? maxw-8 : maxw);
      if (w > max) {
	  unsigned int p;
	  char old = 0;
	  int end;
	  for (p=0; p<strlen(field) && p<pos; p++) {
	      font->dimensions(&field[p],&w,&h);
	      if (w <= max) break;
	  }
	  if (w > max) {
	      for (end=strlen(field)-1; end>=0; end--) {
		  old = field[end];
		  field[end] = 0;
		  font->dimensions(&field[p],&w,&h);
		  if (w <= max) break;
		  field[end] = old;
	      }
	  }
	  font->surf_string(s,x+1,y+1,&field[p],fg_color,0,0);
	  if (old) field[end] = old;
	  old = field[pos]; field[pos] = 0;
	  font->dimensions(&field[p],&curx,&curh);
	  curx += x+1;
	  field[pos] = old;
      } else {
	  font->surf_string(s,x+1,y+1,field,fg_color,0,0);
	  char old = field[pos]; field[pos] = 0;
	  font->dimensions(field,&curx,&curh);
	  curx += x+1;
	  field[pos] = old;
      }
  } else {
      curx = x+1; curh = h;
  }
  cury = y; mys = s;
  if (bg && cursor_on) {
    update_cursor();
  }
}

int TEdit::get_width(TFont *font) {
    if (menu->label) return TStatic::get_width(font);
    return maxw;
}

int TEdit::get_width_max_options(TFont *font) {
    if (!menu->label) return 0;
    return maxw;
}

void TEdit::update_cursor() {
  disp_cursor(mys,curx,cury,8,curh);
}

int TEdit::get_height(TFont *font) {
  int w,h;
  font->dimensions("3",&w,&h);
  return h+2;
}

void TEdit::update() {
  if (update_count++ & 32) {
    if (cursor_on) {
      cursor_on = 0;
      update_cursor();
    }
  } else {
    if (!cursor_on) {
      cursor_on = 1;
      update_cursor();
    }
  }
}

int TEdit::get_len_max_options() {
    if (*menu->label)
	return strlen(field);
    return 0;
}

int TEdit::get_len() {
    if (*menu->label)
	return TStatic::get_len();
    return maxl;
}

int TEdit::valid_chars(int sym, int unicode) {
    return ((sym >= ' ' && sym < 255) || (sym == 0 && unicode));
}

int TEdit::handle_key(SDL_Event *event) {
  unsigned int oldpos = pos;
  switch (event->type) {
    case SDL_KEYDOWN:
      int sym = event->key.keysym.sym;
      if (sym != SDLK_UP && sym != SDLK_DOWN)
	current_hist = -1; // reset history position
      switch(sym) {
	case SDLK_HOME: pos = 0; break;
	case SDLK_END:  pos = strlen(field); break;
	case SDLK_DELETE: if (pos < strlen(field)) {
	  memmove(&field[pos],&field[pos+1],strlen(field)-pos);
	}
	break;
	case SDLK_BACKSPACE: if (pos > 0) {
	  memmove(&field[pos-1],&field[pos],strlen(field)-pos+1);
	  pos--;
	}
	break;
	case SDLK_ESCAPE:
	return 0;
	case SDLK_LEFT:
	  if (pos) pos--;
	  break;
	case SDLK_RIGHT:
	  if (pos < strlen(field)) pos++;
	  break;
	case SDLK_UP:
	case SDLK_DOWN:
	{
	  if (!use_hist) return 0;
	  if (used_hist <= 0) break;
	  if (current_hist == -1) { // start to browse history
            strncpy(prefix_hist,field,80);
	    prefix_hist[79] = 0;
	  }
	  int len = strlen(prefix_hist);
	  int direction = (sym == SDLK_UP ? 1 : -1);
	  int loop = 0;
	  do {
	    current_hist += direction;
	    if (current_hist >= used_hist) {
	      current_hist = 0;
	      loop++;
	    } else if (current_hist < 0) {
	      current_hist = used_hist -1;
	      loop++;
	    }
	  } while (strncasecmp(history[current_hist],prefix_hist,len) && loop<2);
	  if (loop == 2) printf("%c",7); // bell
	  else {
	    strcpy(field,history[current_hist]);
	    pos = strlen(field);
	  }
	  break;
	}
	case SDLK_RETURN:
	case SDLK_KP_ENTER:
	  pos = 0;
	  current_hist = -1;
	  add_history();
	  return 1; // call the handler !!!
	default:
	  int unicode = event->key.keysym.unicode;
	  if (sym >= SDLK_KP0 && sym <= SDLK_KP9) sym = '0' + sym-SDLK_KP0;
	  switch(sym) {
	      case SDLK_KP_PERIOD: sym = '.'; break;
	      case SDLK_KP_DIVIDE: sym = '/'; break;
	      case SDLK_KP_MULTIPLY: sym = '*'; break;
	      case SDLK_KP_MINUS: sym = '-'; break;
	      case SDLK_KP_PLUS: sym = '+'; break;
	      case SDLK_KP_EQUALS: sym = '='; break;
	  }
	  if (strlen(field) < maxl && valid_chars(sym,unicode)) {
	    memmove(&field[pos+1],&field[pos],maxl-pos);
	    if (unicode) sym = unicode;
	    field[pos++] = sym;
	  } else if (!valid_chars(sym,unicode))
	      return 0;
      }
  }
  if (cursor_on) {
    if (oldpos != pos) {
      int tmp = pos;
      pos = oldpos;
      update_cursor();
      pos = tmp;
      cursor_on = 0;
    }
  }
  update_count = 0; // cursor visible, now !
  return -1;
}

void TEdit::add_history() {
  if (!use_hist) return;
  if (used_hist && !strcmp(history[0],field))
    return; // don't store repeated commands !!!
  if (used_hist == MAX_HISTORY) {
    used_hist--;
    if (history[used_hist])
      free(history[used_hist]);
  }
  if (used_hist)
    memmove(&history[1],&history[0],used_hist*sizeof(char*));
  history[0] = strdup(field);
  used_hist++;
}

void TEdit::save_history(char *name) {
    if (!use_hist || !used_hist) return;
    FILE *f = fopen(name,"w");
    if (f) {
	for (int n=0; n<used_hist; n++)
	    fprintf(f,"%s\n",history[n]);
	fclose(f);
    }
}

void TEdit::load_history(char *name) {
    if (!use_hist) return;
    FILE *f = fopen(name,"r");
    if (f) {
	free_history();
	while (!feof(f)) {
	    myfgets(prefix_hist,80,f);
	    if (*prefix_hist) {
		if (used_hist == MAX_HISTORY) {
		    used_hist--;
		    free(history[used_hist]);
		}
		history[used_hist++] = strdup(prefix_hist);
	    }
	}
	fclose(f);
    }
}

void TEdit::insert(char *s) {
  int len = strlen(s);
  if (strlen(field) + len > maxl) {
    printf("%c",7);
    return;
  }
  memmove(&field[pos+len],&field[pos],strlen(&field[pos])+1);
  memcpy(&field[pos],s,len);
  pos += len;
}

static int bidon,valid_input;

static int valid_edit(int sel) {
    valid_input = 1;
    return 1;
}

static menu_item_t menu[] =
{
  { _("label"), valid_edit, &bidon, ITEM_EDIT },
  { NULL },
};

void EditDlg(char *label, char *dest,int max_len) {
    valid_input = 0;
    menu[0].label = label;
    menu[0].values_list[0] = max_len;
    menu[0].values_list[1] = 0; // use_hist
    menu[0].values_list[2] = 12*max_len;
    menu[0].values_list_label[0] = dest;
    TDialog *dlg = new TDialog(_("Edition"),menu);
    dlg->execute();
    delete dlg;
    if (!valid_input) dest[0] = 0;
}

// TFloatEdit

TFloatEdit::TFloatEdit(menu_item_t *my_menu) : TEdit(my_menu)
{
    maxl = menu->values_list[0];
    field = (char*)malloc(maxl+1);
    the_float = (float*)menu->values_list_label[1];
    sscanf(menu->values_list_label[2],"%f",&min);
    sscanf(menu->values_list_label[3],"%f",&max);
    sprintf(field,"%g",*the_float);
    use_hist = 0;
    pos = strlen(field);
}

TFloatEdit::~TFloatEdit() {
    free(field);
}

int TFloatEdit::valid_chars(int sym, int unicode) {
    if (unicode && unicode != sym) sym = unicode;
    return ((sym >= '0' && sym <= '9') || sym == '.');
}

int TFloatEdit::can_exit() {
  sscanf(field,"%f",the_float);
  if (min != max && (*the_float < min || *the_float > max)) {
      char content[80];
      sprintf(content,_("The field %g must have a value between %g and %g"),*the_float,min,max);
      MessageBox(_("Error"),content);
      return 0;
  }
  return 1;
}

// THexEdit

static char upcase(char s) {
    return (s & (~32));
}

static void copy_hex(char *dest, char *src, int max) {
    *dest = 0;
    if (src[0]!='0' || upcase(src[1]) != 'X')
	strcpy(dest,"0x");
    strncat(dest,src,max);
    dest[max-1] = 0;
}

THexEdit::THexEdit(menu_item_t *my_menu) : TEdit(my_menu)
{
    maxl = menu->values_list[0];
    field = (char*)malloc(maxl+1);
    the_hex = (UINT32 *)menu->values_list_label[1];
    char buf[20];
    copy_hex(buf,menu->values_list_label[2],20);
    sscanf(buf,"%i",&min);
    copy_hex(buf,menu->values_list_label[3],20);
    sscanf(buf,"%i",&max);
    sprintf(field,"%x",*the_hex);
    use_hist = 0;
    pos = strlen(field);
}

THexEdit::~THexEdit() {
    free(field);
}

int THexEdit::valid_chars(int sym, int unicode) {
    if (unicode && unicode != sym) sym = unicode;
    return ((sym >= '0' && sym <= '9') || (upcase(sym) >= 'A' && upcase(sym)<='F'));
}

int THexEdit::handle_key(SDL_Event *event) {
    int ret = TEdit::handle_key(event);
    // The handler is called by the dialog when handle_key returns 1, so we do
    // the conversion just before
    if (ret == 1) {
	char buf[20];
	copy_hex(buf,field,20);
	sscanf(buf,"%i",the_hex);
    }
    return ret;
}

int THexEdit::can_exit() {
    if ((*the_hex < min || *the_hex > max) && min != max) {
	char content[80];
	sprintf(content,_("The field %x must have a value between %x and %x"),*the_hex,min,max);
	MessageBox(_("Error"),content);
	return 0;
    }
    return 1;
}


TIntEdit::TIntEdit(menu_item_t *my_menu) : TEdit(my_menu)
{
    maxl = menu->values_list[0];
    field = (char*)malloc(maxl+1);
    if (menu->values_list[3] != menu->values_list[4] &&
	    (*menu->value_int < menu->values_list[3] ||
	     *menu->value_int > menu->values_list[4]))
	*menu->value_int = menu->values_list[3]; // init to min
    sprintf(field,"%d",*menu->value_int);
    use_hist = 0;
    pos = strlen(field);
}

TIntEdit::~TIntEdit() {
    free(field);
}

int TIntEdit::valid_chars(int sym, int unicode) {
    if (unicode && unicode != sym) sym = unicode;
    return (sym >= '0' && sym <= '9');
}

int TIntEdit::handle_key(SDL_Event *event) {
    int ret = TEdit::handle_key(event);
    // The handler is called by the dialog when handle_key returns 1, so we do
    // the conversion just before
    if (ret == 1) {
	*menu->value_int = atoi(field);
    }
    return ret;
}

int TIntEdit::can_exit() {
    *menu->value_int = atoi(field);
    if ((*menu->value_int < menu->values_list[3] || *menu->value_int > menu->values_list[4]) && menu->values_list[3] != menu->values_list[4]) {
	char content[80];
	sprintf(content,_("The field %d must have a value between %d and %d"),*menu->value_int,menu->values_list[3],menu->values_list[4]);
	MessageBox(_("Error"),content);
	return 0;
    }
    return 1;
}

