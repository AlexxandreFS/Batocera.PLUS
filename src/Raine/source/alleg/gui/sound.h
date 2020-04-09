
#ifdef __cplusplus
extern "C" {
#endif

extern void *old_draw;

int sound_setup_proc(int msg, DIALOG *d, int c);
char *soundcardlist_getter(int index, int *list_size);

extern DIALOG sound_setup_dialog[];
void set_sound_variables(UINT8 update);

void switch_mixer();

#ifdef __cplusplus
}
#endif
