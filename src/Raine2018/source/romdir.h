#ifdef __cplusplus
extern "C" {
#endif

void init_rom_dir();
void alloc_romdir(int n);
void add_rom_dir(char *s);
void remove_rom_dir(int sel);

#ifdef __cplusplus
}
#endif
