
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                          CONFIG FILE ROUTINES                              */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

void raine_set_config_file(char *filename);

void raine_push_config_state(void);
void raine_pop_config_state(void);

char *raine_get_config_string(const char *section, const char *name, char *def);
int   raine_get_config_int(const char *section, const char *name, int def);
int   raine_get_config_hex(char *section, char *name, int def);
float raine_get_config_float(char *section, char *name, float def);
int   raine_get_config_id(char *section, char *name, int def);
char *raine_get_config_text(char *msg);

void raine_set_config_string(const char *section, const char *name, char *val);
void raine_set_config_int(const char *section, const char *name, int val);
void raine_set_config_hex(char *section, char *name, int val);
void raine_set_config_8bit_hex(char *section, char *name, UINT32 val);
void raine_set_config_16bit_hex(char *section, char *name, UINT32 val);
void raine_set_config_24bit_hex(char *section, char *name, UINT32 val);
void raine_set_config_32bit_hex(char *section, char *name, UINT32 val);
void raine_set_config_id(char *section, char *name, int val);

void raine_clear_config_section(const char *section);
void raine_config_cleanup();

#define raine_translate_text(src) raine_get_config_text(src)

#ifdef __cplusplus
}
#endif
