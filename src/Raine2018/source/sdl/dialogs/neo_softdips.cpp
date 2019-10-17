#include "../gui/menu.h"
#include "games.h"
#include "raine.h"
#include "starhelp.h"
#include "newmem.h"
#include "cpumain.h"
#include "neocd/neocd.h"
#include "files.h"

static menu_item_t menu[14]; // 14 soft dips max

/* Some rather lengthy code to be able to decode the soft dips since the games
 * don't give access to all of them, and sometimes none of them. It's
 * documented in the web, and you can get a bios which can display/change them
 * unibios for neogeo, and equivalent there for neocd :
 * http://smkdan.eludevisibility.org/ngcd/ */

static char* get_str(int &strings) {
    // Get a string from the string array
    char str[13];
    if (is_neocd())
	memcpy(str,&RAM[strings],12);
    else
	memcpy(str,&ROM[strings],12);

    for (int n=0; n<12; n++)
	if (str[n] == 0) {
	    printf("bad string %s\n",str);
	    throw 1; // Normally strings are padded with spaces, no 0 !
	}
    strings += 12;
    ByteSwap((UINT8*)str,12);
    int n = 11;
    while (str[n] == ' ')
	n--;
    str[++n] = 0;
    return strdup(str);
}

static void set_bcd(int &bcd1,int &nb, int &strings) {
    menu[nb].label = get_str(strings);
    menu[nb].value_int = &bcd1;
    menu[nb].values_list_size = ITEM_EDIT;
    menu[nb].values_list[0] = 5; // max len
    menu[nb].values_list[1] = 0; // history ?
    menu[nb].values_list[2] = 100; // pixels
    int low = bcd1 & 0xff;
    int high = bcd1 >> 8;
    low = (low >> 4)*10+(low & 0xf); // convert from bcd
    high = (high >> 4)*10+(high & 0xf);
    char buff[6];
    sprintf(buff,"%02d:%02d",high,low);
    menu[nb++].values_list_label[0] = strdup(buff);
}

static void get_bcd(int &nb,UINT8 *code) {
    char *s = menu[nb].values_list_label[0];
    char *sep = strchr(s,':');
    int min = 0,sec;
    if (sep) {
	min = atoi(s);
	sec = atoi(sep+1);
    } else
	sec = atoi(s);
    if (sec > 59) sec = 59;
    if (sec < 0) sec = 0;
    if (min < 0) min = 0;
    if (min > 99) min = 99;
    int val = bcd(min)*0x100+bcd(sec);
    WriteWord(code,val);
    nb++;
}

static int get_byte(int adr) {
    if (is_neocd()) return RAM[adr ^ 1];
    else return ROM[adr ^ 1];
}

int do_soft_dips(int sel) {
    if (!current_game) return 0;
    if (current_game->load_game != &load_neocd) return 0;
    int base = (is_neocd() ? ReadLongSc(&RAM[0x11e]) : ReadLongSc(&ROM[0x11e]));
    // mslug has a link to an address in its 1st rom bank, > 0x200000
    if (base > 0x200000) {
       if (is_neocd()) return 0;
       base -= 0x100000; // there is a hole between 100000 and 200000 for ram
    }
    char name[16];
    if (is_neocd())
	memcpy(name,&RAM[base],16);
    else
	memcpy(name,&ROM[base],16);
    int saveram_offs;
    UINT8 *ram;
    if (!is_neocd()) {
	// Find the offset of the game in the backup ram
	// apparently the only way to do it is to find the current
	// game name. Not sure it's perfect.
	ram = get_neogeo_saveram();
	if (!ram) return 0;
	for (saveram_offs=0; saveram_offs<8; saveram_offs++)
	    if (!memcmp(ram+0x2a0+saveram_offs*16,name,16))
		break;
	if (saveram_offs == 8) return 0;
    }
    UINT8 *code = (!is_neocd() ? ram + 0x220 + saveram_offs*16 : &RAM[0x10fd84]);
    UINT8 *bcode = code;
#define ReadCode(a) *((((a)-bcode) ^ 1) + bcode)
#define WriteCode(a,b) *((((a)-bcode) ^ 1) + bcode) = b
    if (ReadLong(code) == 0) return 0; // uninitialized yet
    int strings = base + 0x20;
    int bcd1,bcd2,val1,val2;
    int nb = 0;
    UINT8 *pbase = (is_neocd() ? &RAM[base+0x10] : &ROM[base + 0x10]);

    try {
	if (ReadWord(pbase) != 0xffff) {
	    bcd1 = ReadWord(code);
	    set_bcd(bcd1,nb,strings);
	}
	if (ReadWord(pbase+2) != 0xffff) {
	    bcd2 = ReadWord(code+2);
	    set_bcd(bcd2,nb,strings);
	}
	if ((val1 = ReadCode(code+4)) != 0xff) {
	    // special 1
	    menu[nb].label = get_str(strings);
	    menu[nb].value_int = &val1;
	    menu[nb].values_list_size = 3;
	    menu[nb].values_list[0] = 1;
	    menu[nb].values_list[1] = 99;
	    menu[nb++].values_list[2] = 1;
	}
	if ((val2 = ReadCode(code+5)) != 0xff) {
	    // special 2
	    menu[nb].label = get_str(strings);
	    menu[nb].value_int = &val2;
	    menu[nb].values_list_size = 3;
	    menu[nb].values_list[0] = 0;
	    menu[nb].values_list[1] = 100;
	    menu[nb++].values_list[2] = 1;
	}
	code += 6;
	int defs = base + 0x16;
	int val[10];
	int x = 0;
	int choices;
	while ((choices = get_byte(defs) & 0xf)) {
	    menu[nb].label = get_str(strings);
	    menu[nb].value_int = &val[x];
	    menu[nb].values_list_size = choices;
	    for (int n=0; n<choices; n++) {
		menu[nb].values_list[n] = n;
		menu[nb].values_list_label[n] = get_str(strings);
	    }
	    val[x] = ReadCode(code);
	    code++;
	    defs++;
	    x++;
	    if (choices <= 1) {
		free((char*)menu[nb].label);
		menu[nb].label = NULL; // just in case it's the last one !
		for (int n=0; n<choices; n++)
		    if (menu[nb].values_list_label[n])
			free(menu[nb].values_list_label[n]);
	    } else
		nb++;
	    if (defs == base + 0x16 + 10) // max nb of entries
		break;
	}
	TMenu *load = new TMenu(_("Soft dipswitches"),menu);
	load->execute();
	delete load;

	// Convert back to the native formats...
	code = (!is_neocd() ? ram + 0x220 + saveram_offs*16 : &RAM[0x10fd84]);
	nb = 0;
	if (ReadWord(pbase) != 0xffff)
	    get_bcd(nb,code);
	if (ReadWord(pbase+2) != 0xffff)
	    get_bcd(nb,code+2);
	WriteCode(code+4, val1);
	WriteCode(code+5, val2);
	code += 6;
	defs = base + 0x16;
	x = 0;
	while ((choices = get_byte(defs) & 0xf)) {
	    WriteCode(code, val[x++]);
	    code++;
	    if (defs++ == base + 0x16 + 10) // max nb of entries
		break;
	}
	if (!is_neocd()) {
	    // Do it once more like neocd, that is, write to ram
	    // it allows to have a direct effect instead of having to reload
	    // the game (or reset it).
	    code = &RAM[0xfd84];
	    bcode = code;
	    nb = 0;
	    if (ReadWord(pbase) != 0xffff)
		get_bcd(nb,code);
	    if (ReadWord(pbase+2) != 0xffff)
		get_bcd(nb,code+2);
	    WriteCode(code+4, val1);
	    WriteCode(code+5, val2);
	    code += 6;
	    defs = base + 0x16;
	    x = 0;
	    while ((choices = get_byte(defs) & 0xf)) {
		WriteCode(code, val[x++]);
		code++;
		if (defs++ == base + 0x16 + 10) // max nb of entries
		    break;
	    }
	}
    }
    catch(...) { MessageBox(_("Warning"),_("Bad soft dips"),_("OK")); }

    // Free everything !
    nb = 0;
    while (menu[nb].label) {
	free((void*)menu[nb].label);
	menu[nb].label = NULL;
	if (menu[nb].values_list_size == ITEM_EDIT) {
	    free(menu[nb].values_list_label[0]);
	    menu[nb].values_list_label[0] = NULL;
	}
	for (int n=0; n<menu[nb].values_list_size; n++)
	    if (menu[nb].values_list_label[n]) {
		free(menu[nb].values_list_label[n]);
		menu[nb].values_list_label[n] = NULL;
	    }
	nb++;
    }
    if (is_neocd()) {
	char path[FILENAME_MAX];
	snprintf(path,FILENAME_MAX,"%ssavedata" SLASH "%s.sdips", dir_cfg.exe_path, current_game->main_name);
	save_file(path,&RAM[0x10fd84],16);
    }
    return 0;
}
