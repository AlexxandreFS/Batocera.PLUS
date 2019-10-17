#ifdef __cplusplus
extern "C" {
#endif

#ifdef RAINE_DOS
#include "alleg/gui/rgui.h"
#else
#include "sdl/dialogs/messagebox.h"
#endif

#define IRQ1CTRL_AUTOANIM_STOP		0x08
// Issues an interrupt when counter = 0 :
#define IRQ1CTRL_ENABLE			0x10
// When timer low register is set, timer counter is simultaneously set
#define IRQ1CTRL_LOAD_LOW		0x20
// Timer counter is set at the beginning of the horizontal blanking of the 1st
// vertical line
#define IRQ1CTRL_AUTOLOAD_VBLANK	0x40
// Timer counter is set to initial value when it reaches 0
#define IRQ1CTRL_AUTOLOAD_REPEAT	0x80

extern int neocd_id,allowed_speed_hacks,disable_irq1;
extern int loading_animation_fix,loading_animation_pal;
extern int exit_to_code,neogeo_bios;

extern UINT8 *neogeo_fix_memory,*video_fix_usage,*video_spr_usage;
extern char neocd_path[FILENAME_MAX],neocd_dir[FILENAME_MAX];
extern char neocd_bios_file[FILENAME_MAX];
extern int sfx_volume, music_volume;
extern int capture_new_pictures;
extern struct VIDEO_INFO neocd_video;

extern UINT8 *neocd_bios;
UINT8* get_neogeo_saveram();
void setup_neocd_bios();
void set_neocd_exit_to(int code);
void execute_neocd();
void load_neocd();
void clear_neocd();
void loading_progress_function();
void neocd_function(int vector);
void save_fix(int vidram);
void restore_fix(int vidram);
void postprocess_ipl();
void write_reg_b(UINT32 offset, UINT8 data);
void fix_disable(UINT32 offset, UINT8 data);
void update_game_vectors();
void myStop68000(UINT32 adr, UINT8 data);
void draw_neocd_paused();
void neogeo_read_gamename(void);
void restore_neocd_config();
void save_neocd_config();

extern struct GAME_MAIN game_neocd;

#ifdef __cplusplus
}
#endif
