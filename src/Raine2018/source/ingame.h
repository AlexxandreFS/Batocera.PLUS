
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*      INGAME (screen blit, eagle, message list                   )       */
/*                                                                            */
/******************************************************************************/

#include "raine.h"

/*

ingame message list

*/

extern char fps_buff[32];		// fps() message string
#ifdef RAINE_DOS
void print_ingame(int showtime, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
#else
void print_ingame(int showtime, const char *format, ...);
#endif
void clear_ingame_message_list(void);

#define MAX_LAYER_INFO	(16)

extern int key_data[MAX_LAYER_INFO];

typedef struct LAYER_INFO
{
   int enabled;
   int flip;
   UINT16 keycode;
   char *name;
} LAYER_INFO;

extern struct LAYER_INFO layer_info_list[MAX_LAYER_INFO];

extern int layer_info_count;

void reset_layer_switches(void);
#ifndef SDL
void check_layer_switches(void);
#endif
int add_layer_info(char *name);
int check_layer_enabled(int layer);
void BlitScreen(void);
void overlay_ingame_interface(int ogl);

#ifdef __cplusplus
}
#endif
