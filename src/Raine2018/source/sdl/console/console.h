#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef __cplusplus
extern "C" {

#include "sdl/gui/tconsole.h"
#include "parser.h"

class TRaineConsole : public TConsole
{
  char last_cmd[80];
  int pointer_on, pointer_n, pointer_x,pointer_top,pointer_rows,pointer_end;
  int dump_cols;
  public:
    TRaineConsole(char *my_title, char *init_label, int maxlen, int maxlines, commands_t *mycmd) : TConsole(my_title,init_label,maxlen,maxlines,mycmd)
    {
	load_history();
      pointer_on = 0;
      dump_cols = ((maxlen-7)/4)&~7;
      use_transparency = 0;
    }
    virtual void  execute();
    virtual void handle_mouse(SDL_Event *event);
    virtual void unknown_command(int argc, char **argv);
    virtual int run_cmd(char *field);
    virtual void post_print() {
      pointer_on = 0; // erase mouse cursor after a print
    }
    int get_dump_cols() { return dump_cols; }
};

extern TRaineConsole *cons;
int get_cpu_id();
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

int do_console(int sel);
void preinit_console();
void done_console();
void run_console_command(char *command);
void do_regs(int argc, char **argv);
#ifdef __cplusplus
UINT8 *get_ptr(UINT32 addr, UINT32 *the_block = NULL);

}
#endif
#endif
