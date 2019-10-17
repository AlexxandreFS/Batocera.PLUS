
#ifdef __cplusplus
extern "C" {
#endif
/*

joystick controls

*/

int joy_keys_radio_proc(int msg, DIALOG *d, int c);
int joy_keys_radio_proc_2(int msg, DIALOG *d, int c);
int joy_select_proc(int msg, DIALOG *d, int c);
char *joy_inputlist_getter(int index, int *list_size);
int joy_key_edit_proc(int msg, DIALOG *d, int c);
UINT8 joy_read_new_keycode(void);
int joy_key_select_proc(int msg, DIALOG *d, int c);
void joy_axis_proc(int num);


#define JOY_KEY_TYPE_LIST		5
#define JOY_KEY_VIEW_LIST		8

extern DIALOG joy_input_select[];
extern DIALOG joy_key_editing[];
extern DIALOG joy_axis_select[];

#ifdef __cplusplus
}
#endif
