/* In fact this file doesn't do anything related to dialogs, but since it's
 * called from a dialog...
 * All it does is just assign the right dsw to the current game's dsw and
 * then call the standard dsw dialog */

#include "raine.h"
#include "games.h"
#include "control.h"
#include "neocd/neocd.h"
#include "starhelp.h"
#include "sdl/dialogs/dlg_dsw.h"
#include "files.h"
#include "neo_debug_dips.h"

#define LEN 85
static char high[8][LEN];
static char low[8][LEN];

static struct DSW_DATA def_0[] =
{
    DSW_ON_OFF(high[0],1,0),
    DSW_ON_OFF(high[1],2,0),
    DSW_ON_OFF(high[2],4,0),
    DSW_ON_OFF(high[3],8,0),
    DSW_ON_OFF(high[4],16,0),
    DSW_ON_OFF(high[5],32,0),
    DSW_ON_OFF(high[6],64,0),
    DSW_ON_OFF(high[7],128,0),
  { NULL, 0, 0}
};

static struct DSW_DATA def_1[] =
{
    DSW_ON_OFF(low[0],1,0),
    DSW_ON_OFF(low[1],2,0),
    DSW_ON_OFF(low[2],4,0),
    DSW_ON_OFF(low[3],8,0),
    DSW_ON_OFF(low[4],16,0),
    DSW_ON_OFF(low[5],32,0),
    DSW_ON_OFF(low[6],64,0),
    DSW_ON_OFF(low[7],128,0),
  { NULL, 0, 0}
};

void init_debug_dips() {
    // Init the default values...
    for (int num=0; num<8; num++) {
	sprintf(high[num],"2-%d Unknown",num+1);
	sprintf(low[num],"1-%d Unknown",num+1);
    }
    char ln[200];
    strncpy(ln,current_game->long_name,200);
    ln[199] = 0;
    char *s = strstr(ln," (");
    if (s) *s = 0;
    s = strstr(ln," -");
    if (s) *s = 0;
    s = strstr(ln," /"); // Some of the names keep the /, but some don't
    if (s) *s = 0; // for example last blade 2 !
    int len = strlen(ln);
    if (!strncasecmp(ln,"The ",4)) {
	memmove(ln,&ln[4],len-4);
	len -= 4;
    }
    FILE *f = fopen(get_shared("debug_dips.txt"),"r");
    if (f) {
	int is_high = 0,num = -1;
	while (!feof(f)) {
	    char buff[200];
	    myfgets(buff,200,f);
	    num = -1;
	    if (buff[0] == ' ' || buff[0] == 0) continue;
	    if (!strncasecmp(ln,buff,len)) {
		print_debug("init_debug_dips: found name %s\n",buff);
		while (!feof(f)) {
		    myfgets(buff,200,f);
		    if (!buff[0]) num = -1;
		    s = &buff[0];
		    if (s[0] != ' ' && s[0]) break;
		    while (*s == ' ') s++;
		    if ((*s >= '0' && *s <= '9') &&
			    (s[1] == '-' || s[1] == ':') &&
			    s[2] >= '0' && s[2] <= '9') {
			is_high = (s[0] == '2');
			num = s[2] - '0'-1;

			if (is_high) strncpy(high[num],s,LEN);
			else strncpy(low[num],s,LEN);
		    } else if (num >= 0) {
			s = &buff[0];
			while (*s == ' ') s++;
			if (*s > '9') { // the text continues on the line below
			    s--; // keep the previous space !
			    char *dest = (is_high ? high[num] : low[num]);
			    strncat(dest,s,LEN);
			    strcpy(&dest[LEN-3],"..");
			}
		    }
		}
		break;
	    }
	}
	fclose(f);
    }
}

static struct DSW_INFO dsw_debug[] =
{
  { 0x1, 0, def_0 },
  { 0x0, 0, def_1 },
  { 0, 0, NULL }
};

int do_debug_dsw(int sel) {
    if (!current_game) return 0;
    if (current_game->load_game != &load_neocd) return 0;
    UINT8 *ram = (is_neocd() ? RAM : ROM);
    int base = ReadLongSc(&ram[0x10e]);
    if (dsw_debug[0].data) dsw_debug[0].offset = 11;
    /* factory_setting : remarkably, the dsw are write-only in ram, they
     * read their default value, and then can be changed only with the dsw
     * dialog, not from the ram. So there is nothing to read from the ram, and
     * here we must assign the factory_setting from what there is in ram... */
    if (is_neocd())
	dsw_debug[1].factory_setting = ram[base ^ 1];
    else
	dsw_debug[1].factory_setting = RAM[(base ^ 1) & 0xffff];
    dsw_debug[1].offset = 10;
    if (is_neocd())
	dsw_debug[0].factory_setting = ram[(base+1) ^ 1];
    else
	dsw_debug[0].factory_setting = RAM[((base + 1) ^ 1) & 0xffff];
    printf("init dsw %x %x\n",dsw_debug[0].factory_setting,dsw_debug[1].factory_setting);
    const DSW_INFO *old = current_game->dsw;
    current_game->dsw = NULL;
    current_game->dsw = dsw_debug;
    init_dsw();
    do_dlg_dsw(0);
    current_game->dsw = old;
    init_dsw();
    if (!is_neocd()) base &= 0xffff;
    printf("au final, debug dsw %x %x, go to %x\n",input_buffer[10],input_buffer[11],base);
    RAM[base ^ 1] = input_buffer[10];
    RAM[(base+1) ^ 1] = input_buffer[11];
    return 0;
}
