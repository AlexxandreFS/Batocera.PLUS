
#ifdef __cplusplus
extern "C" {
#endif
extern char *history;
#ifdef SDL
#include "gui/menuitem.h"
/* Can now read also command.dat which has almost the same format as history.dat
 * in this case this menu_commands is filled with the sub-section names
 * and commands_buff contains the associated text */
extern menu_item_t *menu_commands;
#endif

extern int nb_commands;
extern char **commands_buff;

void hist_open(char *name,const char *game);


#ifdef __cplusplus
}
#endif
