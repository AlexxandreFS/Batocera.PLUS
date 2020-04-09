
#ifdef __cplusplus
extern "C" {
#endif
int cheatdata_edit_proc(int msg, DIALOG *d, int c);

void DoCheatEdit(void);
int cheat_edit_proc(int msg, DIALOG *d, int c);
int cheat_add_proc(int msg, DIALOG *d, int c);
int cheat_new_proc(int msg, DIALOG *d, int c);
int cheat_del_proc(int msg, DIALOG *d, int c);

int actionreplay_proc(int msg, DIALOG *d, int c);
char *cheatlist_getter(int index, int *list_size);

char *search_list_getter(int index, int *list_size);

extern DIALOG cheatdata_edit_dialog[];

extern DIALOG actionreplay_dialog[];
int cheat_search_new_proc(int msg, DIALOG *d, int c);
int cheat_search_cont_proc(int msg, DIALOG *d, int c);

extern DIALOG search_main_dialog[];

char *search_mode_getter(int index, int *list_size);

extern DIALOG search_mode_dialog[];

int byte_hex_edit_proc(int msg, DIALOG *d, int c);
int byte_dec_edit_proc(int msg, DIALOG *d, int c);
int byte_sgn_edit_proc(int msg, DIALOG *d, int c);
int byte_asc_edit_proc(int msg, DIALOG *d, int c);

extern DIALOG search_type_0a_dialog[];

extern DIALOG search_type_0b_dialog[];

extern DIALOG search_type_1a_dialog[];

extern DIALOG search_type_1b_dialog[];

#define search_type_2a_dialog search_type_1a_dialog

char *search_type_2b_getter(int index, int *list_size);

extern DIALOG search_type_2b_dialog[];

#define search_type_3a_dialog search_type_1a_dialog

char *search_type_3b_getter(int index, int *list_size);

extern DIALOG search_type_3b_dialog[];

char *hex_view_getter(int index, int *list_size);

extern DIALOG hex_view_dialog[];


#ifdef __cplusplus
}
#endif
