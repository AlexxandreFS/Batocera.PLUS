#ifdef __cplusplus
extern "C" {
#endif

extern int iso_sector_size;

void init_iso();
void init_iso_gz();
int iso_size(char *iso, char *name);
int load_from_iso(char *iso, char *name, unsigned char *dest, int offset, int size);

#ifdef __cplusplus
}
#endif

