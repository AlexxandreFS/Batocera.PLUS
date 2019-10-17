#include "conf-sound.h"
#if HAS_NEO
#ifndef	CDROM_H
#define CDROM_H
#ifdef __cplusplus
extern "C" {
#endif

#define PRG_TYPE    0
#define FIX_TYPE    1
#define SPR_TYPE    2
#define Z80_TYPE    3
#define PCM_TYPE    4
#define PAT_TYPE    5

  typedef struct {
    int function; // 1: ipl, 2: load_files
    int file_to_load;
    int total_sectors,sectors_to_load,loaded_sectors;
    int bytes_loaded;
    int initial_cdrom_speed;
  } loading_params;

extern int get_cd_load_type();

enum{
  ZIP_TYPE = 0,
  IPL_TYPE,
  ISO_TYPE,
  CUE_TYPE,
  P7Z_TYPE,
};

extern loading_params neocd_lp;
extern int total_sectors, sectors_to_load,loaded_sectors, cdrom_speed,nb_tracks;

void init_load_type();
void neogeo_cdrom_load_title(void);
void    fix_conv(UINT8 *Src, UINT8 *Ptr, int Taille, unsigned char *usage_ptr);
void    fix_inv_conv(UINT8 *Src, UINT8 *Ptr, int Taille);
int    neogeo_cdrom_process_ipl(loading_params *params);
void    neogeo_cdrom_load_files(UINT8 *Ptr);
void spr_conv(UINT8 *src, UINT8 *dst, int len, unsigned char *usage_ptr);
void neogeo_cdrom_apply_patch(short *source, int offset);
int    neogeo_cdrom_load_spr_file(char *FileName, unsigned int Offset);
int    neogeo_cdrom_load_fix_file(char *FileName, unsigned int Offset);
int neogeo_cdrom_load_pcm_file(char *FileName, unsigned int Offset);
int    neogeo_cdrom_load_prg_file(char *FileName, unsigned int Offset);
char *get_mp3_track(int n);
void get_track_index(int track, int *start, int *end);
void update_spr_usage(UINT32 offset, UINT32 size);

void save_cdrom_config();
void restore_cdrom_config();
unsigned neogeo_cdrom_test_files(unsigned char *Ptr, loading_params *param);
void cdrom_load_neocd();
void fix_extension(char *FileName, char *extension);
int get_size(char *filename);

#ifdef __cplusplus
}
#endif
#endif
#endif
