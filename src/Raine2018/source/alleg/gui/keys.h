
#ifdef __cplusplus
extern "C" {
#endif
/*

keyboard controls

*/

int keys_radio_proc(int msg, DIALOG *d, int c);
int keys_radio_proc_2(int msg, DIALOG *d, int c);
int input_select_proc(int msg, DIALOG *d, int c);
char *inputlist_getter(int index, int *list_size);
int key_edit_proc(int msg, DIALOG *d, int c);
UINT8 read_new_keycode(void);
int key_select_proc(int msg, DIALOG *d, int c);
void do_key_edit(void);
char *KeyName(UINT16 scancode);

#define KEY_TYPE_LIST		5
#define KEY_VIEW_LIST		8

extern DIALOG input_select[];
extern DIALOG key_editing[];
extern int key_view_mode;

#ifdef __cplusplus
}
#endif
