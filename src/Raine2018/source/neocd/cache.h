#ifdef __cplusplus
extern "C" {
#endif
int file_cache(char *filename, int offset, int size,int type);
int find_spec(char *spec, char *name, UINT32 *offset, UINT32 *size);
void restore_override();
void get_cache_origin(int type, int offset, char **name, int *nb);
void put_override(int type, char *name, UINT32 size_msg);
void clear_file_cache();
void cache_set_crc(int offset,int size,int type);
void prepare_cache_save();
char *get_override(char *name);

#ifdef __cplusplus
}
#endif
