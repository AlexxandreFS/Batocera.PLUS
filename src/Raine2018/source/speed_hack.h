#ifdef __cplusplus
extern "C" {
#endif

extern int speed_hack;
void undo_hack();
void apply_hack(UINT32 pc, int kind);
void apply_rom_hack(UINT8 *ROM, UINT32 pc, int kind);
void pWriteWord(UINT8* myadr, UINT16 val);
UINT8 *get_speed_hack_adr(int n);

#ifdef __cplusplus
}
#endif
