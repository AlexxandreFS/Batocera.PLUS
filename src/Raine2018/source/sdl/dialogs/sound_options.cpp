#include "../gui/menu.h"
#include "sasound.h"
#if HAS_ES5506
#include "es5506.h"
#endif
#include "neocd/neocd.h"
#include "neocd/cdda.h"
#include "games.h"
#include "sdl/dialogs/sound_commands.h"
#include "sound/assoc.h"

static TMenu *menu;

#if HAS_NEO
static int set_default_volumes(int sel) {
  sfx_volume = DEFAULT_SFX_VOLUME;
  music_volume = DEFAULT_MUSIC_VOLUME;
  menu->draw();
  mute_music = mute_sfx = 0;
  return 0;
}
#endif

menu_item_t sound_menu[] =
{
  { _("Emulate sound"), NULL, &RaineSoundCard, 2, { 0, 1 }, { _("No"), _("Yes") } },
  // we are obliged to give labels for the sample rates because a list of
  // 3 values is now considered to be an interval (start, end, step).
  { _("Sample rate"), NULL, &audio_sample_rate, 3, { 11025, 22050, 44100 },
      { "11025", "22050","44100" }} ,
#if HAS_ES5506
  { _("ES5506 voice filters"), NULL, &es5506_voice_filters, 2, { 0, 1 }, { _("No"), _("Yes") } },
#endif
#if HAS_NEO
{ _("Always stop CD music while loading"), NULL, &auto_stop_cdda, 2, { 0, 1 }, { _("No"), _("Yes") } },
  { _("Sfx volume"), NULL, &sfx_volume, 3, { 0, 200, 10 }, },
  { _("Music volume"), NULL, &music_volume, 3, { 0, 200, 10 }, },
  { _("Audio tracks format"), NULL, &neocd_cdda_format, 2, { AUDIO_S16LSB, AUDIO_S16MSB }, { _("lsb"),_("msb") }},
  { _("Mute SFX"), NULL, &mute_sfx, 2, { 0, 1 }, { _("No"), _("Yes") } },
  { _("Mute CD"), NULL, &mute_music, 2, { 0, 1 }, { _("No"), _("Yes") } },
  { _("Default volumes"), &set_default_volumes },
#endif
  { _("Record to raine_sound.wav"), NULL, &recording, 3, { 0, 1, 2 }, { _("No"), _("Without monitoring"), _("With monitoring") } },
#if HAS_NEO
{ _("Sound commands..."), &do_sound_cmd },
#endif
  { NULL },
};

class TSoundDlg : public TMenu {
  public:
    TSoundDlg(char *title,menu_item_t *menu) :
      TMenu(title,menu)
      {}

    int can_be_selected(int sel) {
#if HAS_NEO
	if (sound_menu[sel].menu_func == &do_sound_cmd)
	    return get_assoc_type() != 0;
#endif
      return TMenu::can_be_selected(sel);
    }
};

int do_sound_options(int sel) {
    int old = recording;
  menu = new TSoundDlg(_("Sound options"), sound_menu);
  menu->execute();
  delete menu;
  if (recording == 2)
    monitoring = 1;
  else
    monitoring = 0;
  if (old && !recording)
      end_recording();

  return 0;
}
