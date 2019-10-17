// extensions for SDL

#ifndef DISPLAY_SDL_H
#define DISPLAY_SDL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "deftypes.h"

typedef struct {
    int dbuf;
    int overlay,save;
    int info;
    char shader[FILENAME_MAX];
    // render : 0 for drawpixels, 1 for textures
    int render;
    char *vendor,*renderer,*version;
    struct {
	int dbuf,fsaa_buffers,fsaa_samples,accel,vbl;
    } infos;
    int filter;
} togl_options;

extern togl_options ogl;

extern int prefered_yuv_format;
#ifdef DARWIN
extern int overlays_workarounds;
#endif
extern UINT32 screen_flags; // flags of the game screen, before gui adjustement
extern const SDL_VideoInfo *video;

void resize();
int lock_surface(SDL_Surface *s);
void adjust_gui_resolution();
void set_opengl_filter(int filter);
#ifdef RAINE_WIN32
void setup_video_driver();
#endif

#ifdef __cplusplus
}
#endif

#endif

