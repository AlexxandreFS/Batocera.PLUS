#ifndef TCONSOLE_H
#define TCONSOLE_H

#include "menu.h"
#include "tedit.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  char *name;
  void (*handler)(int, char **);
  char *help, *long_help;
} commands_t;

UINT32 ansilen(const char *s);
char* ansistr(char *s,int n);
void split_command(char *field, char **argv, int *argc, int max);

#ifdef __cplusplus
}

#include <stddef.h>
#include <stdarg.h>

class ConsExcept {
  private:
    char str[256];
  public:
    ConsExcept(char *msg) {
      strcpy(str,msg);
    }
    ConsExcept(char *format, ...) {
      va_list ap;
      va_start(ap,format);
      vsprintf(str,format,ap);
      va_end(ap);
    }
    char *what() { return str; }
};

typedef void (*tinteractive)(char *);

class TConsole : public TDialog
{
  protected:
    int nb_alloc, nb_used;
    int key_console;
    int unicode,visible;
    menu_item_t edit_menu;
    TEdit *edit_child;
    TStatic **last_child;
    unsigned int len_max;
    commands_t *commands;
    char *field;
    tinteractive interactive;

    // handler is for internal use only, not supposed to be called from the
    // outside
    virtual int handler(int cause);
  public:
    TConsole(char *my_title, char *init_label, int maxlen, int maxlines, commands_t *mycmd);
    ~TConsole();
    // virtual void compute_nb_items();
    virtual void print(const char *format, ...);
    virtual void save_history();
    virtual void load_history();
    virtual void post_print(); // easier than overloading print
    virtual void setup_fg_layer();
    virtual int get_fglayer_footer_height();
    virtual int get_fglayer_footer_len();
    virtual void display_fglayer_footer(int x,int &y,int w, int xoptions);
    virtual void fglayer_footer_update();
    virtual int fglayer_footer_handle_key(SDL_Event *event);
    virtual void fglayer_footer_call_handler();
    virtual void unknown_command(int argc, char **argv);
    virtual void do_help(int argc, char **argv);
    virtual void draw();
    void set_interactive(void (*my_interactive)(char *)) {
      interactive = my_interactive;
    }
    void end_interactive() {
      interactive = NULL;
    }
    virtual void  execute();
    virtual int run_cmd(char *field);
    void set_visible() { visible = 1; }
};
#endif
#endif

