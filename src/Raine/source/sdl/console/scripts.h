#ifdef __cplusplus
extern "C" {
#endif

#include "sdl/gui/menuitem.h"

void init_scripts();
void add_scripts(menu_item_t *menu);
void update_scripts();
char *get_script_name(int writeable);
void do_script(int argc, char **argv);
void do_start_script(int argc, char **argv);

extern int nb_scripts;

#ifdef __cplusplus
}
#endif
