#ifndef display_h
#define display_h

#include "games/games.h"

#ifdef __cplusplus
extern "C" {
#endif

void display_read_config();
void display_write_config();
void load_screen_settings(char *section);
void save_screen_settings(char *section);

void init_display();
void ScreenChange(void);
void set_default_video_mode();
void clear_raine_screen();

extern int bestw,besth,bestbpp;
void setup_gfx_modes();
int switch_res(const VIDEO_INFO *vid);


#ifdef __cplusplus
}
#endif
#endif
