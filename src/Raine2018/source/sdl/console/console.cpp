#include "raine.h"
#include "console.h"
#include "starhelp.h"
#include "newmem.h"
#include "files.h" // get_shared
#include "games.h"
#include "parser.h"
#include "scripts.h"
#include "68000/starcpu.h"
#include "sdl/gui.h"
#include "console/exec.h"
#include "conf-cpu.h"
#include "cpumain.h"
#include "z80/mz80help.h"
#include "68020/u020help.h"
#include "neocd/cache.h"

static int cpu_id;
extern void do_if(int argc, char **argv);
static UINT32 ram[0x100*2],ram_size[0x100],nb_ram;
static UINT8 *ram_buf[0x100],*search_size;
static UINT32 nb_search, nb_alloc_search, *search;
#define getadr(a) ((cpu_id>>4) == 1 ? ((a)^1) : (a))

int get_cpu_id() { return cpu_id; }

#define MAX_WATCH 10

typedef struct {
  UINT32 adr,pc;
  int size,read,value;
  char *cond;
} twatch;
static twatch watch[MAX_WATCH];
static int nb_watch;

static void init_cpuid() {
    cpu_id = 0;
#ifndef NO020
  if (MC68020)
      cpu_id = CPU_M68020_0;
  else
#endif
#if HAVE_68000
    if(StarScreamEngine>=1){
	cpu_id = CPU_68K_0; // default : 68k, 1st cpu
    } else
#endif
#if HAVE_Z80
   if(MZ80Engine>=1) {		// Guess it's a z80 game
       cpu_id = CPU_Z80_0;
       if (!Z80_context[0].z80Base)
	   cpu_id++; // why did Antiriad skip the 1st z80 sometimes ???
   }
#endif
  switch_cpu(cpu_id);
}

UINT8 *get_ptr(UINT32 adr, UINT32 *the_block) {
  UINT32 block;
  for (block=0; block<nb_ram; block+=2) {
    if (adr >= ram[block] && adr <= ram[block+1])
      break;
  }
  if (block >= nb_ram) {
    return NULL;
  }
  if (the_block) *the_block = block;

  return get_userdata(cpu_id,ram[block]);
}

typedef int (thandler)(UINT32 offset, UINT32 data);

static UINT16 exec_watchw(UINT32 offset, UINT16 data);
static UINT8 exec_watchb(UINT32 offset, UINT8 data) {
    int n;
    for (n=0; n<nb_watch; n++) {
	if (offset == watch[n].adr && watch[n].size == 1) {
	    if (watch[n].cond) get_regs();
	    UINT8 *ptr = get_ptr(offset,NULL);
	    thandler *func;
	    if (!ptr) {
		int off_start = 0;
		void *temp;
		do {
		    temp = get_userfunc(0,watch[n].read, watch[n].size, off_start, offset);
		    if (!temp) return 0;
		    off_start++;
		} while (temp == exec_watchb || temp == exec_watchw);
		func = (thandler *)temp;
	    }
	    if (watch[n].value == -1 ||
		    (!watch[n].read && watch[n].value == data) ||
		    (watch[n].read && ptr && watch[n].value == ptr[getadr(offset)])) {
		if (!watch[n].cond || parse(watch[n].cond)) {
		    watch[n].pc = s68000readPC();
		    Stop68000(0,0);
		    goto_debuger = n+100;
		}
	    }
	    if (ptr) {
		printf("watchb: changing offset %x,%x\n",getadr(offset),data);
		if (!watch[n].read)
		    ptr[getadr(offset)] = data;
		else
		    return ptr[getadr(offset)];
	    } else if (func) {
		return (*func)(offset,data);
	    } else {
		cons->print("no handler found for %x",offset);
	    }
	    break;
	}
    }
    if (n>=nb_watch) {
	printf("exec_watchb: %x not found !!!\n",offset);
    }
    return 0;
}

static UINT16 exec_watchw(UINT32 offset, UINT16 data) {
  // the code is almost the same as exec_watchb but I am forced to separate
  // them or otherwise I couldn't tell the difference between access to a word
  // and access to its first byte
    int n;
    for (n=0; n<nb_watch; n++) {
	if (offset >= watch[n].adr && offset < watch[n].adr+watch[n].size &&
		watch[n].size >= 2) {
	    if (watch[n].cond) get_regs();
	    UINT8 *ptr = get_ptr(offset,NULL);
	    thandler *func;
	    if (!ptr) {
		int off_start = 0;
		void *temp;
		do {
		    temp = get_userfunc(0,watch[n].read, watch[n].size, off_start, offset);
		    if (!temp) return 0;
		    off_start++;
		} while (temp == exec_watchb || temp == exec_watchw);
		func = (thandler *)temp;
	    }
	    if (watch[n].value == -1 ||
		    (!watch[n].read && watch[n].value == data) ||
		    (watch[n].read && ptr && watch[n].value == ReadWord(&ptr[offset]))) {
		if (!watch[n].cond || parse(watch[n].cond)) {
		    watch[n].pc = s68000readPC();
		    Stop68000(0,0);
		    goto_debuger = n+100;
		}
	    }
	    if (ptr) {
		if (!watch[n].read)
		    WriteWord(&ptr[offset],data);
		else {
		    return ReadWord(&ptr[offset]);
		}
	    } else if (func) {
		return (*func)(offset,data);
	    } else {
		cons->print("no handler found for %x",offset);
	    }
	    break;
	}
    }
    if (n>=nb_watch) {
	UINT8 *ptr = get_ptr(offset,NULL);
	if (ptr) {
	    printf("watchw: changing offset %x,%x\n",offset,data);
	    if (!watch[n].read)
		WriteWord(&ptr[offset],data);
	    else {
		return ReadWord(&ptr[offset]);
	    }
	} else
	    printf("exec_watchw: %x not found !!!\n",offset);
    }
    return 0;
}

static int add_watch(UINT32 adr, int size, int read, int value=-1) {
  for (int n=0; n<nb_watch; n++) {
    if (watch[n].adr == adr && watch[n].size == size &&
	    watch[n].read == read) {
      cons->print("this watchpoint already exists (#%d)",n);
      return 0;
    }
  }
  if (nb_watch < MAX_WATCH) {
    if (read) {
      if (size == 1) {
	insert_rb(0,0,adr,adr,(void*)exec_watchb,NULL);
      } else if (size == 2)
	insert_rw(0,0,adr,adr+1,(void*)exec_watchw,NULL);
      else
	insert_rw(0,0,adr,adr+size-1,(void*)exec_watchw,NULL);
    } else {
      if (size == 1) {
	insert_wb(0,0,adr,adr,(void*)exec_watchb,NULL);
      } else if (size == 2)
	insert_ww(0,0,adr,adr+1,(void*)exec_watchw,NULL);
      else {
	insert_ww(0,0,adr,adr+size-1,(void*)exec_watchw,NULL);
	cons->print("added watch, size %d bytes\n",size);
      }
    }
    watch[nb_watch].adr = adr;
    watch[nb_watch].size = size;
    watch[nb_watch].read = read;
    watch[nb_watch].value = value;
    watch[nb_watch].cond = NULL; // clear cond
    nb_watch++;
    return 1;
  } else
    cons->print("maximum number of watch points reached");
  return 0;
}

static int del_watch(int nb) {
  if (nb >= nb_watch) return 0;
  int read = watch[nb].read;
  int size = watch[nb].size;
  UINT32 adr = watch[nb].adr;

  if (read) {
    if (size == 1) {
      del_rb(0,adr,adr,(void*)exec_watchb,NULL);
    } else if (size == 2)
      del_rw(0,adr,adr+1,(void*)exec_watchw,NULL);
    else
      del_rw(0,adr,adr+size-1,(void*)exec_watchw,NULL);
  } else {
    if (size == 1) {
      del_wb(0,adr,adr,(void*)exec_watchb,NULL);
    } else if (size == 2)
      del_ww(0,adr,adr+1,(void*)exec_watchw,NULL);
    else {
      del_ww(0,adr,adr+size-1,(void*)exec_watchw,NULL);
      cons->print("added watch, size %d bytes\n",size);
    }
  }
  if (watch[nb].cond)
      free(watch[nb].cond);
  if (nb < nb_watch-1)
    memmove(&watch[nb],&watch[nb+1],(nb_watch-nb-1)*sizeof(twatch));
  nb_watch--;
  cons->print("watch point #%d deleted",nb);
  return 1;
}

int TRaineConsole::run_cmd(char *string) {
  int ret;
  if (*string) {
    char *s = string;
    while (*s == ' ') s++;
    char *end = strchr(s,' ');
    if (end) *end = 0;
    strcpy(last_cmd,s);
    if (end) *end = ' ';
    ret = TConsole::run_cmd(string);
  } else {
    ret = TConsole::run_cmd(last_cmd);
  }
  return ret;
}

void TRaineConsole::execute() {
  TConsole::execute();
  // Take a snapshot of the ram to be able to look for variations
  for (UINT32 n=0; n<nb_ram; n+=2) {
    UINT32 size = ram[n+1]-ram[n]+1;
    if (!ram_buf[n/2] || ram_size[n/2] < size) {
	if (ram_buf[n/2]) {
	    FreeMem(ram_buf[n/2]);
	}
	ram_buf[n/2] = (UINT8*)AllocateMem(size);
	if (ram_size[n/2] < size)
	    ram_size[n/2] = size;
    }
    UINT8 *ptr = get_userdata(cpu_id,ram[n]);
    memcpy(ram_buf[n/2],ptr+ram[n],size);
  }
  pointer_on = 0;
}

static char striped[200];

static char * strip_ansi(const char *s) {
  char *d = striped;
  while (*s) {
    if (*s == 27) {
      while (*s != 'm')
	s++;
      s++;
    } else {
      *d++ = *s++;
    }
  }
  *d = 0;
  return striped;
}

void TRaineConsole::handle_mouse(SDL_Event *event) {
  TConsole::handle_mouse(event);
  /* This handle_mouse is quite messy, but I am not sure it's possible to do
   * any better. The idea is to 1st locate where we clicked in the list of
   * menu_item_t, then try to recognise this menu. For now we only recognise
   * dump lines */
  switch (event->type) {
    case SDL_MOUSEMOTION:
    {
      int mx = event->motion.x;
      int my = event->motion.y;
      int cw = font->get_font_width();
      int y = HMARGIN;
      static SDL_Rect r;
      skip_fglayer_header(y);
      int y0 = y;
      my -= y;
      mx -= HMARGIN;
      if ((mx & 0x8000) || (my & 0x8000)) return;
      int n = -1, cx = -1;
      int ch;
      if (my>=0 && mx>=0) {
	for (n=top; n<top+rows; n++) {
	  ch = child[n]->get_height(font);
	  my -= ch;
	  y += ch;
	  if (my<0) break;
	}
	y -= ch;
	cx = (mx/cw - 7) / 3;
	if (cx >= dump_cols) cx = (mx/cw - (7+dump_cols*3));
	if (pointer_on==1 && (pointer_x != cx || pointer_n != n)) {
	  if (pointer_n >= top && pointer_n < top+rows &&
	      pointer_top == top && pointer_rows == rows) {
	    disp_cursor(sdl_screen,r.x,r.y,r.w,r.h);
	    r.x = (7+pointer_x*3)*cw+fgdst.x+HMARGIN;
	    r.w = 2*cw;
	    disp_cursor(sdl_screen,r.x,r.y,r.w,r.h);
	  }
	} else if (pointer_on == 2) {
	  if (pointer_top == top) {
	    int dx = mx/cw;
	    if (n == pointer_n && dx >= pointer_x && dx <= pointer_end)
	      break; // still on the number
	    disp_cursor(sdl_screen,pointer_x*cw+fgdst.x+HMARGIN,
		y0+(pointer_n-pointer_top)*ch+fgdst.y,(pointer_end-pointer_x)*cw,font->get_font_height());
	  }
	  pointer_top = top;
	  pointer_on = 0;
	}
	if (my < 0) {
	  if (n>=0) {
	    int x = 0;
	    const char *s = menu[n].label;
	    while (isdigit(s[x]) || (s[x] >= 'a' && s[x]<='f')) {
	      x++;
	    }
	    if (x == 6 && s[x] == 32) { // dump detected
	      if (cx >= 0 && (!pointer_on ||
		  (pointer_on && (cx != pointer_x || pointer_n != n)))) {
		if (cx >= 0 && cx < dump_cols) {
		  r.x = (7+cx*3)*cw+fgdst.x+HMARGIN;
		  r.y = y+fgdst.y;
		  r.w = 2*cw;
		  r.h = font->get_font_height();
		  disp_cursor(sdl_screen,r.x,r.y,r.w,r.h);
		  r.x = (dump_cols*3+7+cx)*cw+fgdst.x+HMARGIN;
		  r.w = cw;
		  disp_cursor(sdl_screen,r.x,r.y,r.w,r.h);
		  pointer_on = 1;
		  pointer_n = n;
		  pointer_x = cx;
		  pointer_top = top;
		  pointer_rows = rows;
		}
		break;
	      }
	    } else {
	      cx = mx/cw;
	      // Try to find a hex number under the mouse
	      int l = ansilen(s);
	      if (cx < l) {
		char *s2 = strip_ansi(s);
		if ((isdigit(s2[cx]) || (s2[cx]>='a' && s2[cx]<='f'))) {
		  int start = cx-1;
		  while (start >= 0 && (isdigit(s2[start]) || (s2[start]>='a' && s2[start]<='f')))
		    start--;
		  start++;
		  int end = cx+1;
		  while (end < l && (isdigit(s2[end]) || (s2[end]>='a' && s2[end]<='f')))
		    end++;
		  pointer_on = 2;
		  pointer_n =n;
		  pointer_x = start;
		  pointer_top = top;
		  pointer_rows = rows;
		  pointer_end = end;
		  disp_cursor(sdl_screen,pointer_x*cw+fgdst.x+HMARGIN,
		    y+fgdst.y,(pointer_end-pointer_x)*cw,font->get_font_height());
		  break;
		}
	      }
	    }
	  }
	}
      }
      if (pointer_on && (pointer_x != cx || pointer_n != n))
	pointer_on = 0;
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
      if (event->button.button == 1) {
	if (pointer_on && pointer_rows == rows && pointer_top == top) {
	  int adr;
	  switch(pointer_on) {
	    case 1:
	      sscanf(menu[pointer_n].label,"%x",&adr);
	      adr += pointer_x;
	      break;
	    case 2:
	      char old = striped[pointer_end];
	      striped[pointer_end] = 0;
	      sscanf(&striped[pointer_x],"%x",&adr);
	      striped[pointer_end] = old;
	      break;
	  }
	  char buff[40];
	  sprintf(buff,"$%x ",adr);
	  edit_child->insert(buff);
	}
      } else
        pointer_on = 0;
      break;
  }
}

void TRaineConsole::unknown_command(int argc, char **argv) {
  // instead of just writing "unknown command", pass this to the parser...
  if (argc > 1) {
    throw(ConsExcept("token unknown %s",argv[0]));
  }
  int val = parse(argv[0]);
  print("%d ($%x)",val,val);
}

TRaineConsole *cons;

static void do_watch(int argc, char **argv) {
  if (argc == 1) {
    if (nb_watch == 0) {
      cons->print("no watch defined yet");
      return;
    }
    for (int n=0; n<nb_watch; n++) {
      cons->print("watch #%d: adr:%x size:%d read:%d cond:%s",n,watch[n].adr,watch[n].size,watch[n].read,(watch[n].cond ? watch[n].cond : "none"));
    }
    return;
  }
  int read=0;
  UINT32 adr;
  int size = 0;
  int value = -1;
  if (!strcasecmp(argv[1],"del")) {
    if (argc != 3)
      throw "syntax watch del nb";
    int nb = parse(argv[2]);
    del_watch(nb);
    return;
  }

  if (!strcasecmp(argv[1],"read")) {
    read = 1;
    adr = parse(argv[2]);
    if (argc >= 4)
      size = parse(argv[3]);
    if (argc == 5)
      value = parse(argv[4]);
  } else {
    adr = parse(argv[1]);
    if (argc >= 3)
      size = parse(argv[2]);
    if (argc == 4)
      value = parse(argv[3]);
  }
  if (!strcasecmp(argv[1],"cond")) {
      int nb = atoi(argv[2]);
      if (argc != 4)
	  throw "syntax : watch cond <nb_watch> <condition>";
      parse(argv[3]); // to be sure it has no errors
      watch[nb].cond = strdup(argv[3]);
      cons->print("ok");
      return;
  }
  if (size > 2) {
    add_watch(adr,size,read);
  } else if (size) { // precise size
    add_watch(adr,size,read,value);
  } else if (adr & 1) {
    add_watch(adr,1,read);
    if (add_watch(adr-1,2,read))
      cons->print("watch #%d & %d added",nb_watch,nb_watch-1);
  } else {
    add_watch(adr,1,read);
    if (add_watch(adr,2,read))
      cons->print("watch #%d & %d added",nb_watch,nb_watch-1);
  }
}

static void do_map(int argc, char **argv) {
  for (UINT32 n=0; n<nb_ram; n+=2) {
    cons->print("$%06x-$%06x",ram[n],ram[n+1]);
  }
}

void do_regs(int argc, char **argv) {
  char buf[1024];
  *buf = 0;
  set_regs(cpu_id);
  int num = cpu_id & 0xf;
  switch (cpu_id >> 4) {
  case 1:
      for (int n=0; n<8; n++) {
	  sprintf(buf+strlen(buf),"\E[36mD%d:\E[0m%08x ",n,s68000context.dreg[n]);
	  if (n==3 || n==7) {
	      cons->print(buf);
	      *buf = 0;
	  }
      }
      for (int n=0; n<8; n++) {
	  sprintf(buf+strlen(buf),"\E[36mA%d:\E[0m%08x ",n,s68000context.areg[n]);
	  if (n==3 || n==7) {
	      cons->print(buf);
	      *buf = 0;
	  }
      }
      cons->print("\E[36mSR:\E[0m%04x \E[36mPC:\E[0m%08x",s68000context.sr,
	      s68000context.pc);
      break;
  case 2:
      cons->print("\E[36mAF:\E[0m%04x \E[36mBC:\E[0m%04x"
	      " \E[36mDE:\E[0m%04x \E[36mHL:\E[0m%04x\n",
	      Z80_context[num].z80af,
	      Z80_context[num].z80bc,
	      Z80_context[num].z80de,
	      Z80_context[num].z80hl);
      cons->print("\E[36mSP:\E[0m%04x \E[36mPC:\E[0m%04x \E[36mIFF:\E[0m%d \E[36mIX:%04x \E[36mIY:%04x",
	      Z80_context[num].z80sp,
	      Z80_context[num].z80pc,
	      Z80_context[num].z80iff,
	      Z80_context[num].z80ix,
	      Z80_context[num].z80iy);
      break;
#ifndef NO020
  case 3:
      for (int n=0; n<8; n++) {
	  sprintf(buf+strlen(buf),"\E[36mD%d:\E[0m%08x ",n,regs.regs[n]);
	  if (n==3 || n==7) {
	      cons->print(buf);
	      *buf = 0;
	  }
      }
      for (int n=0; n<8; n++) {
	  sprintf(buf+strlen(buf),"\E[36mA%d:\E[0m%08x ",n,regs.regs[n+8]);
	  if (n==3 || n==7) {
	      cons->print(buf);
	      *buf = 0;
	  }
      }
      cons->print("\E[36mSR:\E[0m%04x \E[36mPC:\E[0m%08x",regs.sr,regs.pc);
      break;
#endif
  }
}

static void do_poke(int argc, char **argv) {
  if (argc != 3)
    throw("syntax: poke adr value");

  UINT32 adr = parse(argv[1]);
  UINT32 val  = parse(argv[2]);
  UINT8 *ptr = get_ptr(adr);
  if (!ptr) throw "poke outside of ram";

  if (!strcasecmp(argv[0],"poke")) {
      if (cpu_id >> 4== 1) // 68k
	  ptr[adr^1] = val;
      else
	  ptr[adr] = val;
  } else if (!strcasecmp(argv[0],"dpoke")) {
    WriteWord(&ptr[adr],val);
  } else if (!strcasecmp(argv[0],"lpoke")) {
    WriteLongSc(&ptr[adr],val);
  }
  cons->print("ok");
}

static void do_save(int argc, char **argv) {
  if (argc != 4)
    throw("syntax: save name adr_beg adr_end");

  UINT32 adr1 = parse(argv[2]);
  UINT32 adr2  = parse(argv[3]);
  UINT8 *ptr = get_ptr(adr1);
  if (!ptr) return;
  UINT8 *ptr2 = get_ptr(adr2);
  if (ptr2 != ptr) throw "both adresses must be in the same memory range";

  if (save_file(argv[1],&ptr[adr1],adr2-adr1))
    cons->print("ok");
  else
    cons->print("failure");
}

static void do_restore(int argc, char **argv) {
  if (argc < 3 || argc > 4)
    throw("syntax: restore name adr_beg [adr_end]");

  UINT32 adr1 = parse(argv[2]);
  UINT32 adr2;
  if (argc == 4) adr2 = parse(argv[3]);
  else adr2 = adr1 + size_file(argv[1]);
  UINT8 *ptr = get_ptr(adr1);
  if (!ptr) return;
  UINT8 *ptr2 = get_ptr(adr2);
  if (ptr2 != ptr) throw "both adresses must be in the same memory range";

  if (load_file(argv[1],&ptr[adr1],adr2-adr1))
    cons->print("ok");
  else
    cons->print("failure");
}

static void do_dump(int argc, char **argv) {
  static int last_dump_adr;
  static UINT32 last_dump_search;
  if (argc != 2 && !last_dump_adr) {
    cons->print("syntax: dump <start adress|search>");
    return;
  }

  UINT32 adr,block;
  UINT32 found_search = 0,dump_search = 0;
  if (argc >= 2) {
    if (!strncasecmp(argv[1],"search",6)) {
      adr = search[0];
      if (nb_search <= 0) {
	cons->print("No search results to dump");
	return;
      }
      dump_search = 1;
      if (search_size[0] == 1 && cpu_id >> 4 == 1) adr ^= 1;
    } else {
      adr = parse(argv[1]);
    }
  } else {
    adr = last_dump_adr;
    dump_search = last_dump_search;
  }

  UINT8 *ptr = get_ptr(adr,&block);
  if (!ptr) throw "can't dump this adress";
  UINT8 *buf = ram_buf[block/2];
  int dump_cols = cons->get_dump_cols();
  if (buf) buf -= ram[block];
  int tab_found[32];
  for (int l=0; l<8; l++) {
    char buff[1024];
    sprintf(buff,"%06x ",adr);
    for (int n=0; n<dump_cols; n++) {
      if (adr+n > ram[block+1]) break;
      // search results are in ascending order, so we can maintain
      // found_search, which always points to the next search result to see.
      while (found_search < nb_search &&
	((search_size[found_search]==1 && getadr(search[found_search]) < adr+n) ||
	(search_size[found_search]>1 && (int)(adr+n - search[found_search]) >= search_size[found_search])))
	found_search++;
      if (found_search < nb_search &&
	((search_size[found_search] == 1 && getadr(search[found_search]) == adr+n) ||
	(search_size[found_search] == 2 && adr+n-search[found_search] <= 1))) {
	// display it in green (code 2).
	sprintf(buff+strlen(buff),"\E[32m%02x\E[0m ",ptr[getadr(adr+n)]);
	tab_found[n] = 1;
      } else if (buf && ptr[getadr(adr+n)] != buf[getadr(adr+n)]) {
	// display differences from last console in cyan
	sprintf(buff+strlen(buff),"\E[36m%02x\E[0m ",ptr[getadr(adr+n)]);
	tab_found[n] = 0;
      } else {
	sprintf(buff+strlen(buff),"%02x ",ptr[getadr(adr+n)]);
	tab_found[n] = 0;
      }
    }
    for (int n=0; n<dump_cols; n++) {
      if (adr+n > ram[block+1]) break;
      UINT8 car = ptr[getadr(adr+n)];
      if (car < 32 || car > 127) car = '.';
      if (tab_found[n])
	sprintf(buff+strlen(buff),"\E[32m%c\E[0m",car);
      else if (buf && ptr[getadr(adr+n)] != buf[getadr(adr+n)])
	sprintf(buff+strlen(buff),"\E[36m%c\E[0m",car);
      else if (car == '%')
	strcat(buff,"%%");
      else
	sprintf(buff+strlen(buff),"%c",car);
    }
    adr += dump_cols;
    if (dump_search) {
      while (found_search < nb_search &&
	((search_size[found_search]==1 && getadr(search[found_search]) < adr) ||
	(search_size[found_search]>1 && (int)(adr-search[found_search]) >= search_size[found_search])))
	found_search++;
      if (found_search < nb_search)
	adr = search[found_search];
      if (search_size[found_search] == 1 && cpu_id >> 4 == 1)
	adr ^= 1;
    }
    cons->print(buff);
    if (adr > ram[block+1]) break;
  }
  last_dump_adr = adr;
  last_dump_search = dump_search;
}

static void do_loaded(int argc, char **argv) {
    int offset;
    int type = 0;
    if (argc == 3) {
	type = parse(argv[1]);
	offset = parse(argv[2]);
    } else if (argc == 2)
	offset = parse(argv[1]);
    else {
	cons->print("syntax: loaded [type] offset");
	return;
    }

    if (!is_neocd()) {
	cons->print("for neocd only !");
	return;
    }

    char *name = NULL;
    int nb = 0;
    get_cache_origin(type,offset,&name,&nb);
    if (!name) {
	cons->print("unknown");
	return;
    }
    cons->print("%s loaded at %x",name,offset-nb);
}

static void add_search(UINT32 n,UINT8 size) {
  if (nb_search == nb_alloc_search) {
    nb_alloc_search += 100;
    search = (UINT32*)realloc(search,sizeof(UINT32)*nb_alloc_search);
    search_size = (UINT8*)realloc(search_size,sizeof(UINT8)*nb_alloc_search);
  }
  search[nb_search] = n;
  search_size[nb_search++] = size;
}

/* The ability to include operators in macros allows to write all this
 * much quicker... */
#define SEARCH_BUF(op) \
  if (size == 1) { \
    for (UINT32 n=start; n<end; n++) { \
      if (ptr[n] op buf[n]) { \
        add_search(n,size); \
      } \
    } \
  } else if (size == 2) { \
    for (UINT32 n=start; n<end; n++) { \
      if (ReadWord(&ptr[n]) op ReadWord(&buf[n])) { \
        add_search(n,size); \
      } \
    } \
  } else if (size == 4) { \
    for (UINT32 n=start; n<end; n++) { \
      if (ReadLongSc(&ptr[n]) op ReadLongSc(&buf[n])) { \
        add_search(n,size); \
      } \
    } \
  }

#define SEARCH_WHAT(op)                                   \
  if (size == 1) {                                        \
    for (UINT32 n=start; n<end; n++) {                    \
      if (ptr[n] op what) {                               \
        add_search(n,size);                               \
      }                                                   \
    }                                                     \
  } else if (size == 2) {                                 \
    for (UINT32 n=start; n<end; n+=2) {                   \
      if (ReadWord(&ptr[n]) op what) {                    \
        add_search(n,size);                               \
      }                                                   \
    }                                                     \
  } else if (size == 4) {                                 \
      if ((cpu_id >> 4) == 3) { /* 68020 ! */             \
          for (UINT32 n=start; n<end; n+=2) {             \
              if ((UINT32)ReadLong68k(&ptr[n]) op what) { \
                  add_search(n,size);                     \
              }                                           \
          }                                               \
      } else {                                            \
          for (UINT32 n=start; n<end; n+=2) {             \
              if ((UINT32)ReadLongSc(&ptr[n]) op what) {  \
                  add_search(n,size);                     \
              }                                           \
          }                                               \
      }                                                   \
  }                                                       \

#define INC_SRCH_BUF(op) \
      UINT32 n; \
      for (n=0; n<nb_search; n++) { \
	UINT32 end = n; \
	/* one of the search results is not valid anymore... */ \
	if (size == 1) { \
	  while (end < nb_search && (ptr[search[end]]) op (buf[search[end]])) \
	    end++; \
	} else if (size == 2) { \
	  while (end < nb_search && \
	    (ReadWord(&ptr[search[end]])) op (ReadWord(&buf[search[end]]))) \
	      end++; \
	} else if (size == 4) { \
	  while (end < nb_search && \
	    (ReadLongSc(&ptr[search[end]])) op (ReadLongSc(&buf[search[end]])))\
	      end++; \
	} \
	if (end > n) { \
	  if (nb_search > end) \
	    memmove(&search[n],&search[end],(nb_search-(end))*sizeof(UINT32)); \
	  nb_search-=end-n; \
	  n--; \
	} \
      }

#define INC_SRCH_WHAT(op) \
      UINT32 n; \
      for (n=0; n<nb_search; n++) { \
	UINT32 end = n; \
	/* one of the search results is not valid anymore... */ \
	if (size == 1) { \
	  while (end < nb_search && (ptr[search[end]]) op what) \
	    end++; \
	} else if (size == 2) { \
	  while (end < nb_search && \
	    (ReadWord(&ptr[search[end]])) op what) \
	      end++; \
	} else if (size == 4) { \
	  while (end < nb_search && \
	    ((UINT32)ReadLongSc(&ptr[search[end]])) op what)\
	      end++; \
	} \
	if (end > n) { \
	  if (nb_search > end) \
	    memmove(&search[n],&search[end],(nb_search-(end))*sizeof(UINT32)); \
	  nb_search-=end-n; \
	  n--; \
	} \
      }

static void do_search(int argc, char **argv) {
  static UINT32 start,end;
  UINT32 what;
  static int block = -1;
  static UINT8 *ptr;
  int size;
  if (!strcasecmp(argv[0],"search"))
    size = 1;
  else if (!strcasecmp(argv[0],"searchw"))
    size = 2;
  else if (!strcasecmp(argv[0],"searchl"))
    size = 4;

  if (argc < 2 || argc > 3) {
    cons->print("syntax: search what [where]");
    return;
  }
  if (!strcasecmp(argv[1],"clear")) {
    if (!nb_search) {
      cons->print("search results already cleared");
    } else {
      nb_search = 0;
      cons->print("search results cleared");
    }
    return;
  }

  if (!nb_search) {
    // find range to search
    if (argc == 2) {
      start = ram[0];
      end = ram[1];
      block = 0;
    } else {
      start = parse(argv[2]);
      char *s = strchr(argv[2],'-');
      if (s)
	end = parse(s+1);
      else {
	end = 0;
	for (UINT32 n=0; n<nb_ram; n+=2) {
	  if (ram[n] <= start && start <= ram[n+1]) {
	    end = ram[n+1];
	    block = n;
	    break;
	  }
	}
	if (!end) {
	  cons->print("didn't find $%x in ram ranges",start);
	  return;
	}
      }
    }
    if ((cpu_id >> 4) == 3) { // 68020
	// Fix the end of search
	for (int n=REGION_ROM1; n<=REGION_ROM4; n++)
	    if (R24[start>>16] == load_region[n]) {
		end = get_region_size(n);
		break;
	    }

	printf("end adjusted %x\n",end);
    }

    if (end < start) {
      cons->print("end adr should be > start adr");
      return;
    }

    // find userdata
    if (block < 0) {
      for (block = 0; block < (int)nb_ram; block += 2) {
	if (ram[block] <= start && end <= ram[block+1]) {
	  break;
	}
      }
    }

    if (block < 0) {
      cons->print("couldn't find $%x-$%x in ram ranges, see map command",start,end);
      return;
    }

    ptr = get_userdata(cpu_id,ram[block]);

    if (argv[1][0] == '"' || argv[1][0] == 0x27 /* ' */) {
      // search for string
      char *s = argv[1] + 1;
      UINT32 len = strlen(s)-1;
      s[len] = 0; // remove trailing "
      // it's like search byte, but we must invert bytes while progressing
      UINT32 n,idx = 0;
      for (n=start; n<end; n++) {
	while (ptr[getadr(n+idx)] == s[idx])
	  idx++;
	if (idx == len) { // found the string !
	  add_search(n,1);
	}
	idx = 0;
      }
    } else if (!strcmp(argv[1],"!=") ||
      !strcmp(argv[1],"<") ||
      !strcmp(argv[1],"<=") ||
      !strcmp(argv[1],">=") ||
      !strcmp(argv[1],">")) {
      // Variation searches
      if (!ram_buf[block/2]) {
	cons->print("I don't have any variation data yet, retry later");
	return;
      }
      UINT8 *buf = ram_buf[block/2]-start;
      if (!strcmp(argv[1],"!=")) {
	SEARCH_BUF( !=);
      } else if (!strcmp(argv[1],"<")) {
	SEARCH_BUF(<);
      } else if (!strcmp(argv[1],"<=")) {
	SEARCH_BUF(<=);
      } else if (!strcmp(argv[1],">")) {
	SEARCH_BUF(>);
      } else if (!strcmp(argv[1],">=")) {
	SEARCH_BUF(>=);
      }
    } else if (!strncmp(argv[1],"<=",2) ||
      !strncmp(argv[1],">=",2)) {
      what = parse(argv[1]+2);
      if ((what & 0xff) != what) {
	cons->print("sorry, this kind of search is limited to bytes only");
	return;
      }
      if (!strncmp(argv[1],"<=",2)) {
	SEARCH_WHAT(<=);
      } else {
	SEARCH_WHAT(>=);
      }
    } else if (*argv[1] == '<' || *argv[1] == '>') {
      what = parse(argv[1]+1);
      if ((what & 0xff) != what) {
	cons->print("sorry, this kind of search is limited to bytes only");
	return;
      }
      if (*argv[1] == '<') {
	SEARCH_WHAT(<);
      } else {
	SEARCH_WHAT(>);
      }
    } else {
      what = parse(argv[1]);
      if ((what & 0xff) == what && size <= 1) {
	// search byte
	size = 1;
      } else if ((what & 0xffff) == what && size <= 2) {
	// word search
	if (start & 1) {
	  cons->print("start adr must be a multiple of 2");
	  return;
	}
	size = 2;
      } else {
	// search for long
	if (start & 1) {
	  cons->print("start adr must be a multiple of 2");
	  return;
	}
	size = 4;
      }
      SEARCH_WHAT( ==);
    }
  } else { // incremental searches
    if (argc > 2) {
      cons->print("ranges are forbiden when search results are already avail");
      cons->print("use search clear if you want to start a new search");
      return;
    }
    if (argv[1][0] == '"' || argv[1][0] == 0x27 /* ' */) {
      cons->print("incremental searches for strings are not supported");
      return;
    } else if (!strcmp(argv[1],"!=") ||
      !strcmp(argv[1],"<") ||
      !strcmp(argv[1],"<=") ||
      !strcmp(argv[1],">") ||
      !strcmp(argv[1],">=") ||
      !strcmp(argv[1],"==")) {
      // Variation searches
      if (!ram_buf[block/2]) {
	cons->print("I don't have any variation data yet, retry later");
	return;
      }
      UINT8 *buf = ram_buf[block/2]-start;
      if (!strcmp(argv[1],"!=")) {
	INC_SRCH_BUF( ==);
      } else if (!strcmp(argv[1],"<")) {
	INC_SRCH_BUF(>=);
      } else if (!strcmp(argv[1],"<=")) {
	INC_SRCH_BUF(>);
      } else if (!strcmp(argv[1],">")) {
	INC_SRCH_BUF(<=);
      } else if (!strcmp(argv[1],">=")) {
	INC_SRCH_BUF(<);
      } else if (!strcmp(argv[1],"==")) {
	INC_SRCH_BUF(!=);
      }
    } else if (!strncmp(argv[1],"<=",2) ||
      !strncmp(argv[1],">=",2)) {
      what = parse(argv[1]+2);
      if ((what & 0xff) != what) {
	cons->print("sorry, this kind of search is limited to bytes only");
	return;
      }
      if (!strncmp(argv[1],"<=",2)) {
	INC_SRCH_WHAT(>);
      } else {
	INC_SRCH_WHAT(<);
      }
    } else if (*argv[1] == '<' || *argv[1] == '>') {
      what = parse(argv[1]+1);
      if ((what & 0xff) != what) {
	cons->print("sorry, this kind of search is limited to bytes only");
	return;
      }
      if (*argv[1] == '<') {
	INC_SRCH_WHAT(>=);
      } else {
	INC_SRCH_WHAT(<=);
      }
    } else {
      what = parse(argv[1]);
      if ((what & 0xff) == what && size <= 1) {
	size = 1;
      } else if ((what & 0xffff) == what && size <= 2) {
	size = 2;
      } else {
	size = 4;
      }
      INC_SRCH_WHAT( !=);
    }
  } // end of searches

  cons->print("%d result(s) found",nb_search);
  if (nb_search < 10 && nb_search > 0) {
    cons->print("valid adresses :");
    for (UINT32 n=0; n<nb_search; n++) {
      cons->print("$%x",((what & 0xff) == what ? getadr(search[n]) : search[n]));
    }
    if (nb_search == 1) {
      nb_search = 0;
      cons->print("only 1 result -> search results cleared");
    }
  }
}

static void do_cpu(int argc, char **argv) {
    char buff[80];
    sprintf(buff,"active cpu : ");
    int has_68020=0, has_68k=0,has_z80=0;
#ifndef NO020
  if (MC68020) {
      strcat(buff,"68020 ");
      has_68020 = 1;
  }
#endif
#if HAVE_68000
  if(StarScreamEngine>=1){
      strcat(buff," 68000a ");
      has_68k |= 1;
  }
  if(StarScreamEngine>=2){
      strcat(buff," 68000b ");
      has_68k |= 2;
  }
#endif
#if HAVE_Z80
   if(MZ80Engine>=1) {		// Guess it's a z80 game
       for (int n=0; n<4; n++) {
	   if (Z80_context[n].z80Base) {
	       sprintf(buff+strlen(buff)," z80%c ",'a'+n);
	       has_z80 |= (1<<n);
	   }
       }
   }
#endif
   cons->print(buff);
   if (argc > 1) {
       int old = cpu_id,nb;
       set_regs();
       strlwr(argv[1]);
       if (!strcmp(argv[1],"68020") && has_68020)
	   cpu_id = CPU_M68020_0;
       else if (!strncmp(argv[1],"68000",5) &&
	       (has_68k & (1<<(nb = argv[1][5] - 'a'))))
	   cpu_id = CPU_68K_0+nb;
       else if (!strncmp(argv[1],"z80",3) &&
	       (has_z80 & (1<<(nb = argv[1][3] - 'a'))))
	   cpu_id = CPU_Z80_0 + nb;
       else
	   throw "cpu not recognized or not active";
       if (cpu_id != old) {
	   switch_cpu(cpu_id);
	   get_regs();
	   cpu_get_ram(cpu_id,ram,&nb_ram);
	   disp_instruction();
       }
   }
}

commands_t commands[] =
{
    { "cpu", &do_cpu, "cpu [cpu] : show/set active cpu(s)."},
  { "map", &do_map, "map  : show locations of ram in memory map"},
  { "searchw", &do_search, NULL },
  { "searchl", &do_search, NULL },
  { "search", &do_search, "search/searchw/searchl what [where]  : search the byte/word/long in ram", "if where is not specified, take 1st ram range\n"
  "otherwise range can be $adr or $adr1-$adr2\n"
  "\n"
  "what can be a number, the command adapts to its size\n"
  "(byte/word/long), or a string (enclose it in quotes\n"
  "to be able to search for spaces), or you can use\n"
  "these to search for variations :\n"
  "!=, ==, <, <=, >, >=, in this case search for this\n"
  "difference compared to the last time the console was\n"
  "called. You can also use search <=3 for example to look\n"
  "for numbers <= 3.\n"
  "\n"
  "The first time you call search, the search is done in ram\n"
  "after this if there is more than 1 result, following\n"
  "searches are made on the previous results. See rainemu\n"
  "forum for some examples.\n"
  "\n"
  "You can also use searchw or searchl instead of search to force searching "
  "for respectively a word and a long (usefull for the relative searches like "
  "< or >)\n"
  "Use search clear to clear the last results and start a new search.\nSee also : dump search"},
  { "poke", &do_poke, "poke/dpoke/lpoke adr value : put the byte/word/long in ram"},
  { "dpoke", &do_poke },
  { "lpoke", &do_poke },
  { "dump", &do_dump,"dump adr : dump the contents of ram, starting at adr",
  "a click on a value of a dump gives you the corresponding adress in the command line. If some search results are in the dump, they appear in green. You can also use 'dump search' to dump the search results (in this mode, all the lines start with a search result). In a dump the numbers which have changed since the last time you called the console and which are not search results are displayed in cyan."},
  { "script", &do_script, "script ['description' [always]]",
  "Record a script, a list of instructions, to be called later, generally as a cheat. You can run this command without parameters, in this case it will just ask for the missing information. Usually you should first test your instructions, and once you are sure they are correct, run this command, and use the history feature of the command to record the right instructions.\n"
  "Notice that you can edit scripts with a text editor, they are saved in scripts/neocd/gamename.txt or scripts/raine/gamename.txt where gamename is the short game name (given on the status line)" },
  { "start_script", &do_start_script, "start_script \"name\" : enable a script when next frame is drawn",
      "Equivalent to turn a script on using the cheats dialog (when it's not hidden)" },
  { "regs", &do_regs, "regs : show registers" },
  { "watch", &do_watch, "watch [read] [adr] [size] [value] : adds/lists watchpoints", "when passing adr, adds a watch point on adr (2 actually, 1 for the byte, and 1 for the word), which are trigered everytime something is writen to this adress.\n"
  "Without argument, list the watch points defined.\n"
 "If read is passed, then watch for the reads (the default is to watch for the writes). If size is passed in the last argument, then watch for a zone of size bytes instead of just 1 adress. if size > 2, then only the word accesses are watched for now.\n"
 "And finally if value is passed, the watch point is executed only if this value is read or written.\nPass watch del nb to delete a watch point" },
  { "cond", &do_cond, "cond test","Execute up to 16M cycles until the condition passed in parameter becomes true. The condition can use registers like :\n"
  "cond a2==$101f00\n"
  "Don't forget that the condition must be in 1 parameter, no spaces allowed."},
  { "if", &do_if, "if cond ... [else|elsif]...endif",
    "it's a simple if, it takes only 1 argument which is the test, then the "
      "instructions to execute on the following lines if the test is true, "
      "until it finds either elsif followed by another test, else, or endif\n\n"
      "Example :\n"
      "if dpeek($100000)==$ffff\n"
      "  poke $100123,1\n"
      "elsif dpeek($100000)==$fffe\n"
      "  poke $100123,2\n"
      "endif"},
  { "save", &do_save, "save name adr1 adr2 : saves the memory range between adr1 & adr2 to disk" },
  { "restore", &do_restore, "restore name adr1 [adr2] : load file at adr1, until adr2 or end of file" },
  { "step", &do_step, "(s)tep : execute next instruction" },
  { "s", &do_step },
  { "next", &do_next, "(n)ext : like step, but don't step into subprograms or traps - can be interrupted by ESC or Ctrl-C" },
  { "n", &do_next },
  { "irq", &do_irq, "irq [nb] : execute instructions until we are out of the irq. Can be executed anywhere, even if some values have been put onto the stack. When passing an irq number trigers this irq (but don't execute any cycles)" },
  { "list", &do_list, "list [address] : disassemble at address or around current pc if asm listing is available (ram.bin.s for neocd, ROM.bin.s for normal roms)." },
  { "l", &do_list, },
  { "break", &do_break, "break [adr]|break del nb : without parameter, lists breakpoints. With adr, set breakpoint at adr\nPass del and the breakpoint number to delete a breakpoint", },
  { "until", &do_until, "(u)ntil pc : executes cycles until pc reaches value given in parameter. Can be interrupted with ESC or Ctrl-C" },
  { "u", &do_until },
  { "loaded", &do_loaded, "loaded [type] offset : neocd only, returns what is loaded at this offset", "type is 0 (PRG) if ommited\n"
      "Oterwise it can be :\n"
"PRG 0\n"
"FIX 1\n"
"SPR 2\n"
"Z80 3\n"
"PCM 4\n"
"PAT 5\n"},
  { NULL, NULL, },
};

int do_console(int sel) {
    init_cpuid();
    cpu_get_ram(cpu_id,ram,&nb_ram);
    int irq = 0;
    if (!cons)
	cons = new TRaineConsole(_("Console"),"", sdl_screen->w/min_font_size-4,1000, commands);
    get_regs(cpu_id); // 1st thing to do here !!!
    if (goto_debuger >= 100) {
	cons->set_visible();
	int n = goto_debuger - 100;
	irq = check_irq(watch[n].pc);
	UINT8 *ptr = get_ptr(watch[n].adr,NULL);
	if (ptr) {
	    if (watch[n].size == 1) {
		if (watch[n].read)
		    cons->print("watch #%d byte at %x has just been read",n,watch[n].adr);
		else
		    cons->print("watch #%d: byte at %x changed, new value: %x",n,watch[n].adr,ptr[getadr(watch[n].adr) ]);
	    } else { // word
		if (watch[n].read)
		    cons->print("watch #%d word at %x has just been read",n,watch[n].adr);
		else
		    cons->print("watch #%d: word at %x changed, new value: %x",n,watch[n].adr,ReadWord(&ptr[watch[n].adr]));
	    }
	} else {
	    cons->print("watch %d: for adr:%x, size:%d, but no direct mapping",n,watch[n].adr,watch[n].size);
	}
#if 0
	if (s68000context.sr >= 0x2100 && s68000context.sr < 0x2700 && goto_debuger < 100) {
	    cons->print("geting out of the irq...");
	    get_regs(0);
	    do_irq(0,NULL); // get out of the irq...
	    set_regs(0);
	}
#endif
	goto_debuger = 0;
    } else
	irq = check_breakpoint();
    if (cons) {
	cons->set_visible();
	char buff[256];
	switch (cpu_id >> 4) {
	case 0:
	    cons->print("no cpu initialised yet"); break;
	case 1:
	    sprintf(buff,"using 68000"); break;
	case 2: sprintf(buff,"using Z80"); break;
	case 3: sprintf(buff,"using 68020"); break;
	default:
		cons->print("unknown cpu");
		cpu_id = 0;
	}
	if (cpu_id) {
	    sprintf(buff+strlen(buff),"%c",65+(cpu_id & 0xf));
	    cons->print(buff);
	}
    }
    if (goto_debuger >= 0) {
	cons->execute();
	goto_debuger = 0;
    } else
	goto_debuger = 0;
    restore_breakpoints();
    set_regs(cpu_id);
    if (irq) {
	cpu_interrupt(CPU_68K_0,irq);
    } else
	printf("no irq\n");
    return 0;
}

void preinit_console() {
    if (cons) {
	delete cons;
	cons = NULL;
    }
}

void done_console() {
  if (cons) {
      cons->save_history();
      delete cons;
      cons = NULL;
  }
  if (search) {
    nb_search = nb_alloc_search = 0;
    free(search);
  }
  for (UINT32 n=0; n<nb_ram/2; n++) {
    if (ram_buf[n]) {
      FreeMem(ram_buf[n]);
      ram_buf[n] = NULL;
    }
  }
  done_breakpoints();
  nb_watch = 0;
}

void run_console_command(char *command) {
    if (!*command) return;
  init_cpuid();
  cpu_get_ram(cpu_id,ram,&nb_ram);
  if (!cons)
    cons = new TRaineConsole(_("Console"),"", sdl_screen->w/min_font_size-4,50, commands);
  get_regs(cpu_id);
  cons->run_cmd(command);
  set_regs(cpu_id);
}

