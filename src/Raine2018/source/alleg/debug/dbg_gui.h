
#ifdef __cplusplus
extern "C" {
#endif
#ifdef RAINE_DEBUG

extern int goto_debuger,current_cpu;
extern struct mz80context *ztx;

int debuger_proc(int msg, DIALOG *d, int c);

#endif

#ifdef __cplusplus
}
#endif
