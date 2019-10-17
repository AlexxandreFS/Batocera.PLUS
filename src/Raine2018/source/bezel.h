#ifdef __cplusplus
extern "C" {
#endif

extern void load_bezel();
extern int bezel_fix_screen_size(int *myw,int *myh);
extern double get_bezel_ratio();
extern void bezel_fix_screen_coordinates(int *destx,int *desty,int viewx,int viewy,int screenx,int screeny);
extern void clear_bezel();
extern void display_bezel();

#ifdef __cplusplus
}
#endif
