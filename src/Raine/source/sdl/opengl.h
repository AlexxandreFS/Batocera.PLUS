#ifndef SDL_OPENGL_H
#define SDL_OPENGL_H

#ifdef __cplusplus
extern "C" {
#endif

void ogl_save_png(char *name);
void opengl_reshape(int w, int h);
void get_ogl_infos();
void draw_opengl(int linear);
void opengl_text(char *msg, int x, int y);
void finish_opengl();
void opengl_done();
void render_texture(int linear);

void check_error(char *msg);

#ifdef __cplusplus
}
#endif

#endif
