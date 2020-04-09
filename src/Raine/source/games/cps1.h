
#ifdef __cplusplus
extern "C" {
#endif
#include "mame/eeprom.h"

struct SOUND_INFO sound_qsound[2];
struct VIDEO_INFO video_cps1;
struct VIDEO_INFO video_cps1_270;

struct EEPROM_interface pang3_eeprom_interface;

void load_cps1_10(void);
void load_cps1_12(void);
void load_sf2m3(void);
void load_sf2m8(void);
void clear_cps1(void);
void execute_cps1_frame(void);
void execute_ganbare(void);
void draw_cps1(void);
void load_qsound();
void load_cps2();
void execute_qsound_frame();
void execute_cps2_frame();


#ifdef __cplusplus
}
#endif
