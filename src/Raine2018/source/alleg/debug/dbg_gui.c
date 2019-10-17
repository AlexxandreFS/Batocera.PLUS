#include <raine.h>
#include "rguiproc.h"
#include "gui.h"
#include "rgui.h"
#include "cpumain.h"
#include "mz80help.h"
#include "breakpt.h"
#include "dbg_gui.h"
#include "dz80.h"

int current_cpu;
static int pc;
static UINT8 *base;
static dz80_buff z80_buff;
struct mz80context *ztx;
static int centered_adr = 0;

#define REGLEN 26
#define NBREGS 3
static char reg[4][REGLEN+1];
// Defines du dialogue
#define LIST 1
// Listing width
#define LW 220

#define SEL_CPU 3
#define REGS 7

static char *listing_getter(int index, int *list_size);
static int z80_radio_proc(int msg, DIALOG *d, int c);
static int step_proc(int msg, DIALOG *d, int c);
static int notyet_proc(int msg, DIALOG *d, int c);
static void init_z80();
static void listing_color_getter(int index, int *fg, int *bg);
static void update_regs();

typedef char editf[6];

editf reg_af,reg_bc,reg_de,reg_ix,reg_iy,reg_hl;

DIALOG regs_gui[] = // Not static to be centered
{
   { d_raine_window_proc,0,   00,   170, 170,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Breakpoints"},

   { x_raine_button_proc,10,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Ok"},
   { x_raine_button_proc,60,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'Q',  D_EXIT,  0,    0,    "&Quit"},

   { x_text_proc, 10,  20,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "AF", NULL, NULL},
   { x_text_proc, 10,  30,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "BC", NULL, NULL},
   { x_text_proc, 10,  40,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "DE", NULL, NULL},

   { x_text_proc, 10,  60,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "IX", NULL, NULL},
   { x_text_proc, 10,  70,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "IY", NULL, NULL},
   { x_text_proc, 10,  80,   0,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "HL", NULL, NULL},

   { x_edit_proc, 30,  20,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_af},
   { x_edit_proc, 30,  30,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_bc},
   { x_edit_proc, 30,  40,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_de},

   { x_edit_proc, 30,  60,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_ix},
   { x_edit_proc, 30,  70,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_iy},
   { x_edit_proc, 30,  80,   4*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    reg_hl},

   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

static void redraw_interf();

static int irq_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);
   if (ret == D_CLOSE) {
     cpu_interrupt(current_cpu, 0x38);
     return D_REDRAW;
   }
   /* otherwise just return */
   return ret;
}

static int nmi_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);
   if (ret == D_CLOSE) {
     cpu_int_nmi(current_cpu);
     return D_REDRAW;
   }
   /* otherwise just return */
   return ret;
}

static int regs_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);
   if (ret == D_CLOSE) {
     sprintf(reg_af,"%04x",ztx->z80af);
     sprintf(reg_bc,"%04x",ztx->z80bc);
     sprintf(reg_de,"%04x",ztx->z80de);

     sprintf(reg_ix,"%04x",ztx->z80ix);
     sprintf(reg_iy,"%04x",ztx->z80iy);
     sprintf(reg_hl,"%04x",ztx->z80hl);

     ret = do_dialog(regs_gui,-1);
     if (ret == 1) {
       sscanf(reg_af,"%hx",&ztx->z80af);
       sscanf(reg_bc,"%hx",&ztx->z80bc);
       sscanf(reg_de,"%hx",&ztx->z80de);

       sscanf(reg_ix,"%hx",&ztx->z80ix);
       sscanf(reg_iy,"%hx",&ztx->z80iy);
       sscanf(reg_hl,"%hx",&ztx->z80hl);
       update_regs();
     }
     return D_REDRAW;
   }
   /* otherwise just return */
   return ret;
}

static int exit_irq_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);

   if (ret == D_CLOSE) {
     if (base) {
       ExitOnEI = 1; // Exit at the end of the interrupt
       cpu_execute_cycles(current_cpu, 60000 );
       // fprintf(stderr,"%d cycles more\n",dwElapsedTicks - elapsed);
       ExitOnEI = 0;
       init_z80();
       redraw_interf();
       return D_REDRAW;
     }
   }

   /* otherwise just return */
   return ret;
}

DIALOG debuger_gui[] = // Not static to be centered
  {
   // Type of the game, status
   { d_raine_window_proc,0,   00,   375,  205,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Debuger"},
   { d_raine_list_proc,       10,   20,  LW,  170,   255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    listing_getter,NULL, listing_color_getter},

   // CPU Selection

   { x_text_proc,  LW+20,    20,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Z80:"},
   { z80_radio_proc, LW+50,  15,15,   16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',    0,  1,    1,    "&A"},
   { z80_radio_proc, LW+70,  15,15,   16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'B',    0,  1,    1,    "&B"},
   { z80_radio_proc, LW+90,  15,15,   16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',    0,  1,    1,    "&C"},
   { z80_radio_proc, LW+110,  15,15,   16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',    0,  1,    1,    "&D"},

   // Registers

   { x_text_proc, LW+20,  40,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    reg[0], NULL, NULL},
   { x_text_proc, LW+20,  50,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    reg[1], NULL, NULL},
   { x_text_proc, LW+20,  60,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    reg[2], NULL, NULL},
   { x_text_proc, LW+20,  70,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    reg[3], NULL, NULL},


   { step_proc,LW+20,   80,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Step"},
   { notyet_proc,LW+70,   80,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'N',  D_EXIT,  0,    0,    "&Next"},
   { break_proc,LW+20,   100,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'B',  D_EXIT,  0,    0,    "Brea&k"},
   { notyet_proc,LW+70,   100,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "&Run"},
   { regs_proc,LW+20,   120,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "Re&gs"},
   { irq_proc,LW+70,   120,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "&IRQ"},
   { nmi_proc,LW+70,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "&NMI"},
   { exit_irq_proc,LW+20,   140,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "&Exit irq"},

   { x_raine_button_proc,LW+20,   160,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'Q',  D_EXIT,  0,    0,    "&Quit"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
  };

static void redraw_interf() {
  int n;
  SEND_MESSAGE(&debuger_gui[LIST], MSG_DRAW, 0);
  for (n=REGS; n<REGS+NBREGS; n++)
    SEND_MESSAGE(&debuger_gui[n], MSG_DRAW, 0);
}

static int get_adr_index(UINT16 pc) {
  int n;
  for (n=0; n<NBLINES; n++) {
    int val;
    sscanf(z80_buff[n],"%x",&val);
    if (val == pc) break;
  }
  return n;
}

static void centre_adr(UINT16 pc) {
  int n,offset = -29;
  centered_adr = pc;
  do {
    offset++;
    if (pc + offset < 0) {
      offset = -pc; // start at 0
    }
    process_adr(base,pc+offset,z80_buff);
    n = get_adr_index(pc);
  } while (n>10);
  update_regs();
}

static void get_index_adr(int index) {
  sscanf(z80_buff[index],"%x",&centered_adr);
  centre_adr(centered_adr);
}

static void get_prev_adr() {
  int n = get_adr_index(centered_adr);
  if (n>0) {
    sscanf(z80_buff[n-1],"%x",&centered_adr);
    centre_adr(centered_adr);
  }
}

static char *listing_getter(int index, int *list_size)
{
  static int selected = 0;
  if (index == -1){ // Nb of indexes
    *list_size = NBLINES;
  } else if (index == -3) {
    int c = *list_size >> 8;
    if (c == KEY_DOWN && selected == 19 && centered_adr < 0xffff)
      get_index_adr(11);
    else if (c == KEY_UP && selected == 0 && centered_adr > 0)
      get_prev_adr();
    else if (c == KEY_PGUP)
      get_index_adr(2); // 0 is too dangerous (out of flow very often)
    else if (c == KEY_PGDN && centered_adr < 0xffff)
      get_index_adr(NBLINES-1);
  } else if (index == -4) { // clic !
    selected = *list_size;
  } else if (index >= 0 && index<NBLINES) {
    return z80_buff[index];
  }
  return NULL;
}


static void listing_color_getter(int index, int *fg, int *bg) {
  if (base && index >= 0 && index<NBLINES) {
    int adr;
    sscanf(z80_buff[index],"%x",&adr);
    if (adr == pc) {
      *bg = CGUI_COL_TEXT_1; // white... normally !
      *fg = CGUI_COL_BLACK;
    }
  }
  // Else keep default colors...
}

static int notyet_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);

  /* trap the close return value and change the font */
   if (ret == D_CLOSE) {
     raine_alert(raine_translate_text("Warning"),raine_translate_text("Not working yet"),"","",raine_translate_text("&Okay"),NULL,'O',0);
     return D_REDRAW;
   }

   /* otherwise just return */
   return ret;
}

static int step_proc(int msg, DIALOG *d, int c)
{
  int ret = x_raine_button_proc(msg, d, c);

  /* trap the close return value and change the font */
   if (ret == D_CLOSE) {
     if (base) {
       cpu_execute_cycles(current_cpu,1);
       init_z80();
       redraw_interf();
       return D_REDRAW;
     }
   }

   /* otherwise just return */
   return ret;
}

static int z80_radio_proc(int msg, DIALOG *d, int c)
{
  int n,ret,old = current_cpu;
  // z80 selection
  ret = d_raine_radio_button_proc(msg, d, c);

  if (msg == D_GOTFOCUS) {
    for (n=SEL_CPU; n<SEL_CPU+4; n++)
      if (debuger_gui[n].flags & D_SELECTED) {
	current_cpu = n+CPU_Z80_0-SEL_CPU;
	break;
      }
    if (current_cpu != old) {
      init_z80();
      redraw_interf();
    }
  }
  return ret;
}

static void update_regs() {
  char buff[REGLEN+1];
  char flags[10];
  sprintf(flags,"%%-%ds",REGLEN);
  sprintf(buff,"A:%02x B:%02x C:%02x D:%02x E:%02x",ztx->z80af >> 8,
	  ztx->z80bc >> 8,ztx->z80bc & 0xff,ztx->z80de >> 8,ztx->z80de & 0xff);
  sprintf(reg[0],flags,buff);

  sprintf(buff,"HL:%04x IX:%04x IY:%04x",ztx->z80hl,ztx->z80ix,ztx->z80iy);
  sprintf(reg[1],flags,buff);

  sprintf(buff,"SP:%04x PC:%04x IFF:",ztx->z80sp,ztx->z80pc);

  // IFF status : 1 for ints enabled, 2 for iff2 enabled, P for ints pending

  if (ztx->z80intPending)
    strcat(buff,"P");
  else
    strcat(buff," ");
  if (ztx->z80iff & 2)
    strcat(buff,"2");
  else
    strcat(buff," ");
  if (ztx->z80iff & 1)
    strcat(buff,"1");
  else
    strcat(buff," ");
  sprintf(reg[2],flags,buff);
  sprintf(reg[3],"R:%02x",ztx->z80r);
}

static void init_z80() {
  int n,z80id;
  switch_cpu(current_cpu);
  switch_cpu(current_cpu+1); // force context switch
  z80id = current_cpu & 0xf;
  ztx = &Z80_context[z80id];
  base = ztx->z80Base;

  if (base) {
    // Get the asm source, starting before the pc if possible
    if (ztx->z80halted)
      raine_alert(raine_translate_text("Warning"),raine_translate_text("This cpu is halted"),"","",raine_translate_text("&Okay"),NULL,'O',0);

    pc = ztx->z80pc;
    centre_adr(pc);
  } else {
    sprintf(z80_buff[0],"No RomBase");
    for (n=1; n<NBLINES; n++)
      z80_buff[n][0] = 0;
    update_regs();
  }
}

static void setup_select_cpu() {
  int n;
  for (n=CPU_Z80_0; n<=CPU_Z80_3; n++) {
    if (current_cpu == n) {
      debuger_gui[(n & 0xf)+SEL_CPU].flags = D_SELECTED;
    } else
      debuger_gui[(n & 0xf)+SEL_CPU].flags=0;
  }
}

int debuger_proc(int msg, DIALOG *d, int c)
{
  int ret;
  int maxz80;

  if (d)
    ret = x_raine_button_proc(msg, d, c); // Called from a button
  else
    ret = D_CLOSE;

   if(ret==D_CLOSE){
/*       if (!MZ80Engine) { */
/*         raine_alert(raine_translate_text("Error"),raine_translate_text("No Z80 initialised"),"","",raine_translate_text("&Okay"),NULL,'O',0); */
/*         return D_REDRAW; */
/*       } */

     // Init values

     goto_debuger = 0;

     maxz80 = CPU_Z80_0+MZ80Engine-1;
     current_cpu = current_cpu_num[CPU_Z80_0 >> 4] | CPU_Z80_0;
     if (current_cpu > maxz80)
       current_cpu = maxz80; // if debuger is called before the game is started
     setup_select_cpu();
     init_z80();

     if (d) {
       Unselect_Button(d);
       FadeGUI();
     }
     ret = do_dialog(debuger_gui,-1);
     return D_REDRAW;
   }

   return ret;
}
