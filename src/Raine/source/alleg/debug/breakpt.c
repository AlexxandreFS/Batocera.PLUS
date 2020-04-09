#include "raine.h"
#include "rguiproc.h"
#include "mz80help.h"
#include "dbg_gui.h"
#include "breakpt.h"

// Breakpoints

#define LISTBREAK 2
#define FROM_FIELD (LISTBREAK+2)
#define TO_FIELD (FROM_FIELD+2)
#define ADD_BTN (TO_FIELD+1)
#define DEL_BTN (ADD_BTN +1)

typedef char editf[10];

static editf fromadr,toadr;
static char *break_getter(int index, int *list_size);

DIALOG break_gui[] = // Not static to be centered
{
   { d_raine_window_proc,0,   00,   170, 170,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Breakpoints"},

   { x_text_proc, 10,  20,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Only Read handlers for now", NULL, NULL},

   { d_raine_list_proc,       10,   40,  100,  50,   255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    break_getter,NULL, NULL},


   { x_text_proc, 10,  100,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "From", NULL, NULL},
   { x_edit_proc, 50,  100,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    fromadr},

   { x_text_proc, 10,  110,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "To", NULL, NULL},
   { x_edit_proc, 50,  110,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    toadr},
   { x_raine_button_proc,10,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',  D_EXIT,  0,    0,    "&Add"},
   { x_raine_button_proc,110,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Del"},
   { x_raine_button_proc,60,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'Q',  D_EXIT,  0,    0,    "&Quit"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

static char breaklist[MAX_BREAK][50];
static int selected_breakpoint;
int goto_debuger = 0;
extern UINT32 quit_loop;
static int nb_break = 0;

tclassic_break classic_bl[MAX_BREAK];

static void classic_break(UINT16 adr, UINT8 data, struct z80PortWrite *unused)
{
  goto_debuger = 1;
  quit_loop = 1;
  mz80ReleaseTimeslice();
}

#if 0
static void add_classic_break(UINT16 adr) {
  UINT8 *base = ztx->z80Base;

  if (nb_break < MAX_BREAK) {
    classic_bl[nb_break].adr = adr;
    classic_bl[nb_break++].content = ReadWord(base+adr);
  }
}

static void del_classic_break(UINT16 adr) {
  int n;
  for (n=0; n<nb_break; n++)
    if (classic_bl[n].adr == adr) {
      if (n<nb_break-1)
	memmove(&classic_bl[n],&classic_bl[n+1],sizeof(tclassic_break)*(nb_break-n-1));
      nb_break--;
      break;
    }
}
#endif

void set_breakpoints() {
  int n;
  UINT8 *base = ztx->z80Base;
  for (n=0; n<nb_break; n++)
    WriteWord(base+classic_bl[n].adr,0xd3ab); // outa (abh)

  add_z80_port_wb(current_cpu & 0xf,0xab,0xab,classic_break);
}

static UINT8 break_read(UINT32 adr, struct MemoryReadByte *unused) {
  int n;
  int cpu = current_cpu & 0xf;
  adr &= 0xffff;
  goto_debuger = 1;
  quit_loop = 1;
  mz80ReleaseTimeslice();

  // Skip breakpoints
  for (n=0; Z80_memory_rb[cpu][n].memoryCall == break_read; n++);

  // Find the adr in the normal list...
  while (Z80_memory_rb[cpu][n].lowAddr > adr ||
	 Z80_memory_rb[cpu][n].highAddr < adr)
    n++;
  if (Z80_memory_rb[cpu][n].memoryCall) // function
    return (*Z80_memory_rb[cpu][n].memoryCall)(adr,unused);
  else {
    UINT8 *zone = (UINT8*)Z80_memory_rb[cpu][n].pUserArea;
    return zone[adr];
  }
}

static char *break_getter(int index, int *list_size)
{
  int n;
  int cpu = current_cpu & 0xf;
  if (index == -1){ // Nb of indexes
    for (n=0; Z80_memory_rb[cpu][n].memoryCall == break_read; n++);
    *list_size = n;
  } else if (index == -4) { // clic !
    selected_breakpoint = n = *list_size;
    fprintf(stderr,"selected %d\n",n);
    sprintf(fromadr,"%x",Z80_memory_rb[cpu][n].lowAddr);
    sprintf(toadr,"%x",Z80_memory_rb[cpu][n].highAddr);
    SEND_MESSAGE(&break_gui[FROM_FIELD], MSG_DRAW, 0);
    SEND_MESSAGE(&break_gui[TO_FIELD], MSG_DRAW, 0);
  } else if (index >= 0 && index < MAX_BREAK) {
    sprintf(breaklist[index],"%04x %04x",Z80_memory_rb[cpu][index].lowAddr,
	    Z80_memory_rb[cpu][index].highAddr);
    return breaklist[index];
  }
  return NULL;
}

int break_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);
  int cpu = current_cpu & 0xf;

   if (ret == D_CLOSE) {
     selected_breakpoint = 0;
     ret = do_dialog(break_gui,-1);
     if (ret == ADD_BTN) {
       int from,to;
       sscanf(fromadr,"%x",&from);
       sscanf(toadr,"%x",&to);
       add_z80_debug_rb(cpu,from,to,break_read);
     } else if (ret == DEL_BTN && selected_breakpoint >= 0) {
       if (Z80_memory_rb[cpu][selected_breakpoint].memoryCall == break_read)
	 remove_z80_debug_rb(current_cpu & 0xf,selected_breakpoint);
     }
     return D_REDRAW;
   }
   /* otherwise just return */
   return ret;
}
