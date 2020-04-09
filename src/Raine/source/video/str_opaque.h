
#ifdef __cplusplus
extern "C" {
#endif

extern int opaque_hud,silent_hud;

void draw_string_6x8_opaque_32(char *STR, int x, int y, UINT32 cmap);
void draw_string_6x8_opaque_16(char *STR, int x, int y, UINT32 cmap);
void draw_string_6x8_opaque(char *STR, int x, int y, UINT32 cmap);

#ifdef __cplusplus
}
#endif
