#define NOGDI // define this before including windows.h to avoid BITMAP !
#ifdef ANDROID
#include <GLES/gl.h>
#else
#include <SDL_opengl.h>
#endif
#undef WINAPI
#include "../gui/menu.h"
#include "raine.h" // display_cfg
#include "video_info.h"
#include "blit.h"
#include "sdl/blit_sdl.h"
#include "control.h"
#include "sdl/control_internal.h"
#include "display.h"
#include "sdl/display_sdl.h"
#ifdef MessageBox
#undef MessageBox
#endif
#include "sdl/dialogs/messagebox.h"
#include "sdl/dialogs/fsel.h"
#include "bld.h"
#include "files.h"

class TVideo : public TMenu
{
  public:
  TVideo(char *my_title, menu_item_t *mymenu) :
    TMenu(my_title,mymenu)
    {}
};

static TVideo *video_options;

static int my_toggle_fullscreen(int sel) {
    // int oldx = display_cfg.screen_x, oldy = display_cfg.screen_y;
  display_cfg.fullscreen ^= 1;
  toggle_fullscreen();
  adjust_gui_resolution();
  video_options->draw();
  if (!(sdl_screen->flags & SDL_DOUBLEBUF) && !emulate_mouse_cursor)
    SDL_ShowCursor(SDL_ENABLE);
  clear_raine_screen();
  video_options->draw();
  return 0; // (oldx < display_cfg.screen_x || oldy < display_cfg.screen_y);
}

static int my_toggle_border(int sel) {
    ScreenChange();
    return 0;
}

static int update_scaler(int sel) {
  if (display_cfg.scanlines && display_cfg.stretch) { // scaling options
    MessageBox(_("Warning"),_("You can't have at the same time a scaler + scanlines,\nChoose 1"),_("Ok"));
    display_cfg.stretch = 0; // no scaling if scanlines
    video_options->draw();
  }
  return 0;
}

static menu_item_t overlays_options[] =
{
    { _("Prefered YUV format"), NULL, &prefered_yuv_format, 2, { 0, 1 }, { _("YUY2"), _("YV12 (mpeg)") } },
    { _("Fix aspect ratio to 4:3"), NULL, (int*)&display_cfg.fix_aspect_ratio, 2, {0,1}, {_("No"), _("Yes") } },
#ifdef DARWIN
    { _("Overlays workarounds"), NULL, &overlays_workarounds, 2, { 0, 1}, {_("No"),_("Yes")}},
#endif
    { _("Keep aspect ratio"), NULL, &display_cfg.keep_ratio, 2, {0, 1}, {_("No"),_("Yes")} },
    {  NULL },
};

static menu_item_t blits_options[] =
{
    { _("Change video mode"), NULL, (int*)&display_cfg.auto_mode_change, 3, {0, 1, 2},
	{ _("Never"), _("To match game resolution (low res most of the time)"), _("To match 2x game resolution") } },
    { _("Scaler"), &update_scaler, (int*)&display_cfg.stretch, 4, { 0, 1, 2, 3 },
	{ _("None"), _("Scale2x/3x"), _("Pixel double"), _("hq2x/3x") } },
    { _("Scanlines"), &update_scaler, (int*)&display_cfg.scanlines, 4, { 0, 1, 2, 3 },
	{ _("Off"), _("Halfheight"), _("Fullheight"), _("Fullheight + Double width") } },
    {  NULL },
};

static void preinit_ogl_options();

static int choose_shader(int sel) {
    // This part is a little tricky because I want the fileselector when I
    // select this, but I don't want the whole path to be displayed, just
    // the filename selected alone. Tricky, but not long... !
    /* Something prevents glsl shaders from working. Tried to convert them from
     * cg shaders, got an error about "must write to gl_Position" when linking.
     * So they are disabled for now */
    char *exts[] = { "*.shader","*.glsl", NULL };
    char *dir,old[FILENAME_MAX];
    dir = get_shared("shaders");
    strcpy(old,ogl.shader);
    if (!strcmp(ogl.shader,"None"))
	*ogl.shader = 0;
    else {
	strcpy(dir,ogl.shader);
	char *p = strrchr(dir,SLASH[0]);
	if (p) *p = 0;
    }
    fsel(dir,exts,ogl.shader,"Select shader");
    if (ogl.shader[strlen(ogl.shader)-1] == SLASH[0] &&
	    strcmp(old,"None")) { // cancelled ?
	if (MessageBox(_("Confirmation"),_("Disable shaders ?"),_("Yes|No")) == 1)
	    strcpy(ogl.shader,"None");
	else
	    strcpy(ogl.shader,old);
    } else {
	ogl.render = 1;
    }
    preinit_ogl_options();
    return 0;
}

static int bidon;
static TMenu *menu;

static menu_item_t ogl_options[] =
{
    { _("Rendering"), NULL, &ogl.render, 2, { 0, 1 }, { _("DrawPixels (no shaders)"), _("Texture (possible shaders)") }, },
    { _("Double buffer"), NULL, &ogl.dbuf, 2, { 0, 1 }, {_("No"),_("Yes")} },
    { _("Save opengl screenshots"), NULL, &ogl.save, 2, {0, 1}, {_("No"), _("Yes")} },
    { _("Shader"), &choose_shader,&bidon,1,{0},{ogl.shader}},
    { _("OpenGL overlay interface"), NULL, &ogl.overlay, 2, { 0, 1 }, {_("No"),_("Yes")} },
    { _("Fix aspect ratio to 4:3"), NULL, (int*)&display_cfg.fix_aspect_ratio, 2, {0,1}, {_("No"), _("Yes") } },
    { _("Keep aspect ratio"), NULL, &display_cfg.keep_ratio, 2, {0, 1}, {_("No"),_("Yes")} },
    { _("OpenGL filtering"), NULL, &ogl.filter, 2, { GL_NEAREST, GL_LINEAR }, { _("Nearest"), _("Linear") } },
    {  NULL },
};

static void preinit_ogl_options() {
    char *p = strrchr(ogl.shader,SLASH[0]);
    if (p) ogl_options[3].values_list_label[0] = p+1;
    else
	ogl_options[3].values_list_label[0] = _("None");
    if (menu)
	menu->update_list_label(3,0,ogl_options[3].values_list_label[0]);
}

int renderer_options(int sel) {
    preinit_ogl_options();
    switch(display_cfg.video_mode) {
    case 0: menu = new TDialog(_("OpenGL Options"), ogl_options); break;
    case 1: menu = new TDialog(_("Overlays Options"), overlays_options); break;
    case 2: menu = new TDialog(_("Blits Options"), blits_options); break;
    default:
	    MessageBox(_("Error"),_("No options for this renderer ? Strange !"),_("OK"));
	    return 0;
    }
    menu->set_transparency(0);
    menu->execute();
    delete menu;
    menu = NULL;
    return 0;
}

static int reset_bld;

static int reset_transp(int sel) {
    // There's a catch here : we want to reset 2 values below, but if we
    // change them directly here, then the can_exit handler of the 2 intedit
    // fields will copy back the value displayed when the dialog will close !
    // So we must set a variable here, and reseting the values after the
    // dialog has closed !
    reset_bld = 1;
    return 1;
}

static int bld1,bld2;

static menu_item_t bld_options[] =
{
{ _("Use blending files (.bld)"),NULL,&use_bld,2,{0,1},{_("No"),_("Yes")} },
{ _("Reset transparency values to default"), &reset_transp },
{ _("Transparency for 1 (25% default)"), NULL, &bld1, ITEM_INTEDIT,
    { 3, 0, 50, 0, 100},{""} },
{ _("Transparency for 2 (50% default)"), NULL, &bld2, ITEM_INTEDIT,
    { 3, 0, 50, 0, 100},{""} },
{ NULL },
    };

static int do_bld(int sel) {
    reset_bld = 0;
    bld1 = get_bld1();
    bld2 = get_bld2();
    TMenu *menu = new TMenu(_("bld options"), bld_options);
    menu->execute();
    delete menu;
    if (reset_bld) {
	bld1 = 25;
	bld2 = 50;
    }
    set_bld1(bld1);
    set_bld2(bld2);
    return 0;
}

static menu_item_t video_items[] =
{
#ifdef RAINE_WIN32
{  _("SDL video driver"), NULL, (int*)&display_cfg.video_driver, 3, {0, 1, 2},
  { _("SDL default (windib since 1.2.10)"), _("windib (good for ogl)"),_("directx (good for hw overlays/blits)")} },
#endif
{  _("Video renderer"), NULL, (int*)&display_cfg.video_mode, 3, {0, 1, 2},
  { _("OpenGL"), _("YUV overlays"),_("Normal blits")} },
{ _("Fullscreen"), &my_toggle_fullscreen, &display_cfg.fullscreen, 2, {0, 1}, {_("No"), _("Yes")}},
{ _("Borderless"), &my_toggle_border, &display_cfg.noborder, 2, {0, 1}, {_("No"), _("Yes")} },
{ _("Use double buffer (ignored by opengl)"), NULL, &display_cfg.double_buffer, 3, {0, 1, 2}, {_("Never"), _("When possible"), _("Even with overlays") } },
{ _("Blend file options..."), &do_bld },
{ _("Video info..."), &do_video, },
{ _("Renderer options"), &renderer_options },
{ _("General options:") },
{ _("Limit framerate <= 60fps"), NULL, (int*)&display_cfg.limit_speed, 2, {0, 1}, {_("No"),_("Yes")} },
{ _("Frame skip"), NULL, (int*)&display_cfg.frame_skip, 10, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  {_("Auto"), "1", "2", "3", "4", "5", "6", "7", "8", "9" } },
{ _("Screen rotation"), NULL, (int*)&display_cfg.user_rotate, 4, {0, 1, 2, 3 },
  { _("None"), "90°", "180°", "270°" } },
{ _("Flip screen"), NULL, (int*)&display_cfg.user_flip, 4, {0, 1, 2, 3 },
  { _("None"), _("Flip X"), _("Flip Y"), _("Flip XY") } },
{ _("Save per game screen settings"), NULL, (int*)&raine_cfg.save_game_screen_settings, 2, {0, 1}, _("No"),_("Yes")},
{  NULL },
};

int do_video_options(int sel) {
    int old_stretch = display_cfg.stretch;
#ifdef RAINE_WIN32
    UINT32 old_driver = display_cfg.video_driver;
#endif
    // int oldx = display_cfg.screen_x,oldy = display_cfg.screen_y;
    video_options = new TVideo(_("Video options"), video_items);
    video_options->execute();
#ifdef RAINE_WIN32
    if (old_driver != display_cfg.video_driver) {
	if (sdl_overlay) {
	    SDL_FreeYUVOverlay(sdl_overlay);
	    sdl_overlay = NULL;
	}
	sdl_screen = NULL;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	setup_video_driver();
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	ScreenChange();
    }
#endif
    SetupScreenBitmap();
    if ((sdl_overlay != NULL || display_cfg.video_mode == 1) &&
	    display_cfg.video_mode != 2) {
	// explicitely clear scanlines when overlays are enabled
	display_cfg.scanlines = 0;
    }
    if (old_stretch != display_cfg.stretch && display_cfg.stretch == 3 &&
	    sdl_game_bitmap) {
	DestroyScreenBitmap(); // init hq2x/3x, switch gamebitmap to 16bpp
	// + recall InitLUTs by recreating game_bitmap when enabling hq2x/3x
    }
    return 0; // (oldx != display_cfg.screen_x || oldy != display_cfg.screen_y);
}

