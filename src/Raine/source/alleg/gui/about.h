
#ifdef __cplusplus
extern "C" {
#endif

  extern char raine_cpu_model[80]; // initialisation in raine.c, at startup

int about_proc(int msg, DIALOG *d, int c);
int cycle_proc(int msg, DIALOG *d, int c);
int about_game_proc(int msg, DIALOG *d, int c);

extern DIALOG about_raine[];
extern DIALOG about_game[];

#ifdef __cplusplus
}
#endif
