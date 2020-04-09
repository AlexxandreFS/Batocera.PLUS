
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                         RAINE 6x8 STRING PRINTING                          */
/*                                                                            */
/******************************************************************************/

/*

Transparent

*/

void init_str6x8asm(void);

void draw_string_6x8(char *STR, int x, int y, UINT32 cmap);

void init_str6x8asm_16(void);

void draw_string_6x8_16(char *STR, int x, int y, UINT32 cmap);

void init_str6x8asm_32(void);

void draw_string_6x8_32(char *STR, int x, int y, UINT32 cmap);

#ifdef __cplusplus
}
#endif
