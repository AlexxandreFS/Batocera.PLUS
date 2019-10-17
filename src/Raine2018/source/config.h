
#ifdef __cplusplus
extern "C" {
#endif

#include "loadroms.h"

/**************************************************************/
/* Command Line Processing                                    */
/**************************************************************/

void parse_command_line(int argc, char *argv[]);

#ifdef RAINE_DOS
void CLI_WaitKeyPress(void);
#endif

void load_main_config(void);
void save_main_config(void);

void load_game_config(void);
void save_game_config(void);

#define MAX_ROMOF 4
extern char *romof_list[MAX_ROMOF];
void find_romof(const struct DIR_INFO *dir_list, int *romof);
int load_neo_from_name(char *res);

#ifdef __cplusplus
}
#endif
