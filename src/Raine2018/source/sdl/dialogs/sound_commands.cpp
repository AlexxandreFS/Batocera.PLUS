#include <string.h>
#include "../gui/menu.h"
#include "sasound.h"
#include "games.h"
#include "z80/mz80help.h"
#include "timer.h"
#include "cpumain.h"
#include "raine.h"
#include "sdl/dialogs/messagebox.h"
#include "profile.h"
#include "files.h"
#include "sound/assoc.h"
#include "sdl/dialogs/fsel.h"
#include "neocd/cdda.h"

static TMenu *menu;
static int command;

static int test_command(int sel) {
    latch = command;
    cpu_int_nmi(audio_cpu);
    return 0;
}

static void send(int cmd) {
    command = cmd;
    test_command(0);
    execute_z80_audio_frame();
}

static int stop(int sel) {
    int old = command;
    if (get_assoc_type() == 10) { // gunbird
	send(1);
    } else if (get_assoc_type() == 11) // bublbobl
	send(0);
    else if (get_assoc_type() < 10) { // default : neogeo
	send(3); // stop / music mode for mslug
	if (get_assoc_type() != 4) { // except mslug/2/3/x
	    send(7); // music mode for 3countb and most neogeo games
	}
    }
    command = old;
    return 0;
}

class TSoundCmd : public TMenu {
  public:
    TSoundCmd(char *title,menu_item_t *menu) :
      TMenu(title,menu)
      {}
    void update_fg_layer(int nb_to_update) {
	execute_z80_audio_frame();
	execute_z80_audio_frame();
	TMenu::update_fg_layer(nb_to_update);
    }
};

// This should be placed somewhere more useful... !
static char *strrstr(char *path, char *sub) {
    if (!path || !*path) return NULL;
    char *s=path,*old;
    int found = 0;
    do {
	old = s;
	s = strstr(old+1,SLASH);
	if (s) found = 1;
    } while (s);
    if (found) return old;
    return NULL;
}

static int associate(int sel) {
    static char path[FILENAME_MAX+1];
    char res[FILENAME_MAX+1];
    char *exts[] = { ".mp3",
	".ogg", ".flac", ".wav",
	// extensions supported by modplug, from the doc...
	".mod", ".s3m", ".xm", ".it", ".669", ".amf", ".ams", ".dbm", ".dmf",
	".dsn", ".far", ".mdl", ".med", ".mtm", ".okt", ".ptm", ".stm", ".ult",
	".umx", ".mt2", ".psm",
	// And compressed versions...
	".mdz",".s3z", ".xmz",".itz",
	".mdr",".s3r", ".xmr",".itr",
	".mdgz",".s3gz", ".xmgz",".itgz",
	NULL };
    char *s = get_assoc(command);
    stop(0);
    if (s && *s) {
	strcpy(path,s);
	strcpy(res,s);
	s = strrstr(path,SLASH);
	if (s) *s = 0;
    } else
	*res = 0;
    fsel(path,exts,res,"Choose audio track");
    if (res[strlen(res)-1] == SLASH[0])
	assoc(command,"");
    else {
	assoc(command,res);
	strcpy(path,res);
	s = strrstr(path,SLASH);
	if (s) *s = 0;
    }
    return 0;
}

static menu_item_t *asso = NULL;
static int redraw_assoc;

static int exit_pb(int sel) {
    return 1;
}

menu_item_t playback[] =
{
    { _("Close this dialog to stop playback (Return, ESC or mouse button)"),&exit_pb},
    { NULL },
};

int menu_asso(int sel) {
    int cmd = asso[sel].values_list[0];
    char *t;
    int old;
    TSoundCmd *menu;
    int nb = MessageBox(_("Choice"),_("Track options"),
	    _("Play track|Test command|Silence track|Change track|Remove association"));
    switch (nb) {
    case 4: // change track
	old = command;
	command = cmd;
	associate(0);
	command = old;
	break;
    case 5: // remove assoc
	del_assoc(cmd);
	break;
    case 3: // silence
	assoc(cmd,"");
	break;
    case 1: // play
	t = get_assoc(cmd);
	if (t && *t) {
	    cdda.skip_silence = 1;
	    load_sample(t);
	    menu = new TSoundCmd(_("Playback"), playback);
	    menu->execute();
	    delete menu;
	    cdda.playing = CDDA_STOP;
	}
	return 0;
    case 2: // test command
	old = command;
	command = cmd;
	test_command(sel);
	menu = new TSoundCmd(_("Playback"), playback);
	menu->execute();
	delete menu;
	stop(sel);
	command = old;
	return 0;
    default:
	return 0; // cancelled
    }
    redraw_assoc = 1;
    return 1;
}

static int associations(int sel) {
    int *loop = NULL;
    int last_nb = 0, last_sel;
    do {
	redraw_assoc = 0;
	int nb = 0,bidon;
	asso = (menu_item_t*)realloc(asso,sizeof(menu_item_t)*(nb+1));
	asso[nb].label = _("Track");
	asso[nb].value_int = &bidon;
	asso[nb].values_list_size = 1;
	asso[nb].values_list_label[0] = _("File");
	nb++;
	for (int cmd=2; cmd<256; cmd++) {
	    char *s = get_assoc(cmd);
	    if (s) {
		asso = (menu_item_t*)realloc(asso,sizeof(menu_item_t)*(nb+1));
		loop = (int*)realloc(loop,sizeof(int)*(nb+1));
		char key[4];
		sprintf(key,"%xh",cmd);
		asso[nb].label = strdup(key);
		asso[nb].menu_func = &menu_asso;
		asso[nb].value_int = &bidon;
		asso[nb].values_list_size = 1;
		asso[nb].values_list[0] = cmd;
		loop[nb] = get_asso_loop(cmd);
		if (*s) {
		    char *s2 = strrstr(s,SLASH);
		    asso[nb++].values_list_label[0] = strdup(s2 ? s2+1 : s);
		} else
		    asso[nb++].values_list_label[0] = strdup("Silence");
	    }
	}
	asso = (menu_item_t*)realloc(asso,sizeof(menu_item_t)*(nb+1));
	asso[nb].label = NULL;
	if (!nb) {
	    MessageBox(_("Error"),_("No associations yet"),_("OK"));
	    return 0;
	}
	TMenuPostCb *dlg = new TMenuPostCb(_("Sound associations"),asso,
		loop,_("Loop"));
	if (last_nb == nb)
	    dlg->set_sel(last_sel);
	dlg->execute();
	last_sel = dlg->get_seldisp();
	last_nb = nb;
	delete dlg;
	for (int n=1; n<nb; n++) {
	    int cmd;
	    sscanf(asso[n].label,"%x",&cmd);
	    set_asso_loop(cmd,loop[n]);
	    free((void*)asso[n].label);
	    free(asso[n].values_list_label[0]);
	}
	free(asso);
	free(loop);
	asso = NULL;
	loop = NULL;
    } while (redraw_assoc);
    return 0;
}

static menu_item_t sound_menu[] =
{
    { _("Command"), NULL, &command, 3, {32, 57, 1} },
    { _("Test"), &test_command },
#ifdef RAINE_DEBUG
    // There is not much point in having this outside debug builds
    { _("Test this"), &test_command, &command, ITEM_HEXEDIT, { 2, 0, 150 },
       	{ "",(char*)&command,"0","0"} },
#endif
    { _("Stop"), &stop },
    { _("Associate..."), &associate },
    { _("Manage associations"), &associations },
    { _("Disable associations"), NULL, &disable_assoc, 2, {0, 1}, {_("No"),_("Yes")}},
  { NULL },
};

static void add_value(int v) {
    int n = sound_menu[0].values_list_size++;
    if (n<NB_VALUES) {
	sound_menu[0].values_list[n] = v;
	char hex[4];
	sprintf(hex,"%xh",v);
	sound_menu[0].values_list_label[n] = strdup(hex);
    }
}

int do_sound_cmd(int sel) {
    if (!GameSound || !RaineSoundCard)
	return 0;
    int ticks = dwElapsedTicks;
    sound_menu[0].values_list_size = 0;
    int adr;
    if (get_assoc_type() < 10) add_value(2);
    cdda.playing = CDDA_STOP;
    switch (get_assoc_type()) {
    case 1: // garou
	adr = get_assoc_adr();
	for (int n=0; n<0xe0; n++) {
	    if (Z80ROM[adr+n] == 2)
		add_value(n+0x20);
	}
	break;
    case 2: // galaxyfg
	adr = get_assoc_adr();
	for (int n=0; n<0x100; n++) {
	    if (Z80ROM[adr+n] == 2)
		add_value(n);
	}
	break;
    case 3:  // sonicwi2/3
	for (int n=0x20; n<Z80ROM[0x30d]; n++)
	    add_value(n);
	break;
    case 11: // bublbobl !
	// Not sure I have everything, musics and sounds are mixed !
	for (int n=7; n<=11; n++)
	    add_value(n);
	add_value(0xf);
	add_value(0x14);
	add_value(0x18);
	add_value(0x29);
	add_value(0x2b);
	add_value(0x2d);
	add_value(0x30);
	add_value(0x32);
	break;
    default: // includes mslug and gunbird...
	for (int n=0x20; n<0x40; n++)
	    add_value(n);
	break;
    }

    if (sound_menu[0].values_list_size >= NB_VALUES) {
	printf("too many values : %d\n",sound_menu[0].values_list_size);
	exit(1);
    }
    command = sound_menu[0].values_list[0];

    reset_ingame_timer(); // For sound we'd better init this here...
    start_cpu_main();
    saInitSoundCard( RaineSoundCard, audio_sample_rate );
    if (is_neocd())
	sa_unpause_sound();
    execute_z80_audio_frame(); // start the z80 if it was not already done !
    stop(0);
    command = last_song;
    menu = new TSoundCmd(_("Sound commands"), sound_menu);
    menu->execute();
    delete menu;
    stop(0);
    if (is_neocd())
	sa_pause_sound();
    else
	saDestroySound(0);
    stop_cpu_main();
    stop_ingame_timer();

    for (int x=0; x<sound_menu[0].values_list_size; x++) {
	if (sound_menu[0].values_list_label[x])
	    free(sound_menu[0].values_list_label[x]);
    }
    dwElapsedTicks = ticks;
    if (disable_assoc && !is_neocd())
	cdda.playing = CDDA_STOP;
    return 0;
}
