#include "../gui/menu.h"
#include "raine.h"
#include "blit.h"
#include "palette.h"
#include "newspr.h"
#include "translator.h"
#include "sdl/gui/tbitmap.h"
#include "sdl/blit_sdl.h"
#include "sdl/dialogs/messagebox.h"
#include "neocd/neocd.h"
#include "neocd/cdrom.h"
#include "neocd/cache.h"
#include "files.h"
#include "starhelp.h"
#if HAS_CONSOLE
#include "sdl/console/parser.h"
#endif
#include "games.h"

static int cursorx, cursory,len; // these must stay out of a class because
// of the draw function (pure C). Not sure it was a good idea to use this
// function as C...

class TTransBitmap : public TBitmap {
    protected:
	UINT16 *map;
	int size_map, used_map;
	int sprites_changed;
    public:
	UINT8 *font;
	TTransBitmap(menu_item_t *my_menu);
	~TTransBitmap();
	virtual int handle_key(SDL_Event *event);
	void put_char(UINT8 *gfx, UINT8 *font);
};

typedef struct {
    UINT32 offset,size;
} tcombo_loc;

tcombo_loc combo_loc[] = {
    { 0x201, 0xff },
    { 0xa01, 0xff },
    { 0, 0 }
};

typedef struct {
    UINT32 adr,size;
    UINT32 ref[4];
} tref;

// These 2 msg areas are referenced in these adresses in prog.prg
// and I might have to move them if I insert something in the msg area
tref reference[] = {
/*    { 0x60dec, { 0x6668, 0x6718, 0x17bd8 } },
    { 0x62b34, { 0x66a8, 0x1ed24, 0x54530, 0x55004 }},
    { 0x634e0, { 0x1fe58 }},
    { 0x63542, { 0x1e278, 0x1e2f4 } }, */

/*    { 0x64696, This one is not a msg entry !!!
 *    The 1st offset referenced after this is 646a0 and it's still not one
 *    so we have a real problem here if we want to insert something ! */
    { 0x71d82, 0x73908-0x71d82, { 0x52160, 0x52b14, 0x54274 } },
};

#define END_PROG_MSG 0x73a88

static int get_map_size() {
    int n=0;
    int size = 0;
    while (combo_loc[n].size)
	size += combo_loc[n++].size;
    return size;
}

static int is_in_map(UINT32 spr) {
    int x = 0;
    while (combo_loc[x].size) {
	if (spr >= combo_loc[x].offset &&
	       	spr < combo_loc[x].offset+combo_loc[x].size)
	    return 1;
	x++;
    }
    return 0;
}
// returns the sprite number corresponding to the nth mapping
static int get_sprite_map(UINT32 n) {
    int x = 0;
    while (combo_loc[x].size) {
	if (combo_loc[x].size > n)
	    return combo_loc[x].offset+n;
	n -= combo_loc[x].size;
	x++;
    }
    printf("map overflow\n");
    exit(1);
}

TTransBitmap::TTransBitmap(menu_item_t *my_menu) : TBitmap(my_menu)
{
    cursorx = cursory = 0;
    printf("clearing colors\n");
    memset(&pal[8],0,sizeof(SDL_Color)*8); // clear parasite colors in font
    FILE *f = fopen(get_shared("fonts/8x16.fnt"),"rb");
    sprites_changed = 0;
    if (!f) {
	ErrorMsg("no 8x16 font available !!!");
	font = NULL;
	map = NULL;
	return;
    }
    fseek(f,0L,SEEK_END);
    int taille = ftell(f);
    font = (UINT8*)malloc(taille);
    fseek(f,0L,SEEK_SET);
    fread(font,1,taille,f);
    fclose(f);
    int size = get_map_size();
    map = (UINT16*)calloc(size,sizeof(UINT16));
    size_map = size;
    used_map = 0;
    f = fopen(get_shared("savedata/ssrpg.map"),"rb");
    if (f) {
	fread(map,1,size*2,f);
	fclose(f);
	while (used_map < size_map && map[used_map]) {
	    used_map++;
	}
	printf("used_map %x\n",used_map);
    }
}

static UINT32 base,offset;
static int size_msg, cur_entry;

TTransBitmap::~TTransBitmap() {
    if (font) free(font);
    if (map) {
	char path[1024];
	snprintf(path,1024,"%ssavedata/ssrpg.map",dir_cfg.exe_path);
	FILE *f = fopen(path,"wb");
	int size = get_map_size();
	if (f) {
	    fwrite(map,1,size*2,f);
	    fclose(f);
	} else
	    printf("could not save map\n");
    }
    if (sprites_changed &&
	    MessageBox("Confirmation","Save the changes ?","Yes|No")==1) {
	char path[1024];
	printf("Saving the changes...\n");
	snprintf(path,1024,"%soverride",dir_cfg.exe_path);
	mkdir_rwx(path);
	snprintf(path,1024,"/%s",current_game->main_name);
	mkdir_rwx(path);
	int n = 0;
	while (combo_loc[n].offset) {
	    if (n == 0)
		snprintf(path,1024,"%soverride/%s/combos.spr",dir_cfg.exe_path,
			current_game->main_name);
	    else
		snprintf(path,1024,"%soverride/%s/combos%d.spr",dir_cfg.exe_path,
			current_game->main_name,n);
	    printf("saving %s size %d\n",path,combo_loc[n].size*0x100);
	    save_file(path,&GFX[combo_loc[n].offset*0x100],
		    combo_loc[n].size*0x100);
	    n++;
	}
	char *name;
	int nb;
	get_cache_origin(PRG_TYPE,base+offset,&name,&nb);
	printf("got name %s for origin %x base %x\n",name,base+offset,base);
	put_override(PRG_TYPE,name,size_msg);
    }
}

void TTransBitmap::put_char(UINT8 *gfx, UINT8 *font) {
    int i,j;
    sprites_changed = 1;
    for (i=0;i<16;i++){
	for (j=7;j>=0;j--){
	    if (font[i] & (1<<j))
		gfx[7-j] = 6;
	    else
		gfx[7-j] = GFX[0x30100+7-j+j*16];
	}
	gfx += 16;
    }
}

class TTransMenu : public TDialog {
    public:
	TTransMenu(char *my_title, menu_item_t *mymenu) : TDialog(my_title,mymenu)
    { }
	virtual void create_child(int n);
};

void TTransMenu::create_child(int n) {
    if (menu[n].values_list_size == ITEM_TBITMAP) {
	child[n] = new TTransBitmap(&menu[n]);
	if (!((TTransBitmap *)child[n])->font) {
	    exit_menu = 1;
	    printf("asked for exit\n");
	}
    } else
	TMenu::create_child(n);
}

static TMenu *sprite_menu;

static UINT16 validchars[256];
static char str_offset[15];

#define OFFS_SPRITES 0xe1d6

static int screens;

static void disp_offset() {
    if (screens)
	sprintf(str_offset,"$%x",base+offset+(cursory+cursorx*16)*4);
    else
	sprintf(str_offset,"$%x",base+offset+(cursory*20+cursorx)*2);
    sprite_menu->draw();
}

static UINT32 get_entry_offset(UINT32 base, int cur_entry) {
    if (screens) {
	int ret;
	if (ReadWord(&RAM[base]) == 0xffff)
	    ret = ReadWord(&RAM[base+(cur_entry+1)*2])*4;
	else
	    ret = ReadWord(&RAM[base+cur_entry*2])*4;
	printf("get_entry_offset %d -> %x (base %x)\n",cur_entry,ret,base);
	return ret;
    }

    if (cur_entry == 0)
	return ReadWord(&RAM[base]);
    return ReadWord(&RAM[base]) + ReadWord(&RAM[base+4+(cur_entry-1)*2]);
}

// find the size of a msg in ram, usefull for variable sizes in prog.prg
static UINT32 get_msg_size(UINT32 base) {
    int last_entry = (ReadWord(&RAM[base])-4)/2;
    UINT32 off = get_entry_offset(base,last_entry);
    while (ReadWord(&RAM[base+off]) != 0xffff)
	off += 2;
    return off+2;
}

static void insert_char() {
    int last_entry = (ReadWord(&RAM[base])-4)/2;
    if (base < 0x80000 && base != 0x71d82) {
	MessageBox("Error","Insertion in this area not handled yet","OK");
	return;
    }
    UINT32 last_offset;
    UINT8 *offs;
    offs = &RAM[base+offset+(cursorx+20*cursory)*2];
    if (cur_entry < last_entry)
	last_offset = get_entry_offset(base, cur_entry+1)-2;
    else {
	last_offset = size_msg - 2;
    }
    if (base < 0x80000 && base + size_msg + 2 >= END_PROG_MSG) {
	MessageBox("Error","Can't insert, reaching the end of the zone",
		"OK");
	return;
    }
    if (offs <= &RAM[base+last_offset]) {
	printf("inserting a char !\n");
	memmove(offs+2,offs,size_msg-last_offset);
	size_msg += 2;
	len++;
	UINT16 *entries = (UINT16*)&RAM[base+4];
	for (int n = cur_entry+1; n<=last_entry; n++)
	    entries[n-1] += 2;
    }
}

static void move_ref(int diff) {
    for (int n=0; n<2; n++) {
	if (base < reference[n].adr) {
	    memmove(&RAM[reference[n].adr-diff],
		    &RAM[reference[n].adr],
		    reference[0].size);
	    for (int x=0; x<4; x++) {
		if (!reference[n].ref[x])
		    continue;
		if ((UINT32)ReadLongSc(&RAM[reference[n].ref[x]]) !=
			reference[n].adr) {
		    printf("reference mismatch base %x ref %d\n",base,x);
		    exit(1);
		}
		WriteLongSc(&RAM[reference[n].ref[x]],
			reference[n].adr-diff);
	    }
	}
    }
}

int TTransBitmap::handle_key(SDL_Event *event) {
    int offs;
    switch (event->type) {
    case SDL_KEYDOWN:
	int sym = event->key.keysym.sym;
	switch (sym) {
	case SDLK_RIGHT:
	    if ((size_msg && cursory*20+(cursorx+1)==len))
		insert_char();
	    if (cursory*20+(cursorx+1)<len) {
		cursorx++;
		if (cursorx == 20) {
		    cursorx = 0; cursory++;
		}
		disp_offset();
		return 1;
	    }
	    break;
	case SDLK_LEFT:
	    if (cursory*20+(cursorx-1)>=0) {
		cursorx--;
		if (cursorx < 0) {
		    cursorx = 19; cursory--;
		}
		disp_offset();
		return 1;
	    }
	    break;
	case SDLK_DOWN:
	    if ((cursory+1)*20+(cursorx)<len) {
		cursory++;
		disp_offset();
		return 1;
	    }
	    break;
	case SDLK_UP:
	    if ((cursory-1)*20+(cursorx)>=0) {
		cursory--;
		disp_offset();
		return 1;
	    }
	    break;
	case SDLK_RETURN:
	case SDLK_PAGEDOWN:
	    if (screens) break;
	    WriteWord(&RAM[base+offset+(cursorx+20*cursory)*2],
		    0); // line break
	    sprites_changed = 1;
	    event->key.keysym.sym = SDLK_RIGHT;
	    return handle_key(event);
	case SDLK_END:
	    if (screens) break;
	    offs = offset+(cursorx+20*cursory)*2;
	    WriteWord(&RAM[base+offs],
		    0xffff); // end of text
	    sprites_changed = 1;
	    if (size_msg) {
		int last_entry = (ReadWord(&RAM[base])-4)/2;
		int n;
		UINT32 last_offset;
		if (cur_entry < last_entry)
		    last_offset = get_entry_offset(base, cur_entry+1)-2;
		else {
		    last_offset = size_msg - 2;
		}
		int diff = last_offset - offs;
		if (base < 0x80000 && base != 0x71d82) {
		    MessageBox("Error","Can't reduce this area for now","OK");
		    break;
		}
		if (diff) {
		    printf("reducing size by %d\n",diff);
		    UINT16 *entries = (UINT16*)&RAM[base+4];
		    for (n = cur_entry+1; n<=last_entry; n++)
			entries[n-1] -= diff;
		    memmove(&RAM[base+offs+2],
			    &RAM[base+last_offset+2],
			    size_msg - last_offset - 2);
		    size_msg -= diff;
		    move_ref(diff);
		}
	    }

	    event->key.keysym.sym = SDLK_LEFT; // text ends earlier now
	    return handle_key(event);
	case SDLK_INSERT:
	    if (screens) break;
	    sprites_changed = 1;
	    insert_char();
	    break;
	case SDLK_DELETE:
	    if (screens || !size_msg) break;
	    offs = offset+(cursorx+20*cursory)*2;
	    if (base < 0x80000 && base != 0x71d82) {
		MessageBox("Error","Can't reduce this area for now","OK");
		break;
	    }
	    sprites_changed = 1;
	    {
		int last_entry = (ReadWord(&RAM[base])-4)/2;
		UINT16 *entries = (UINT16*)&RAM[base+4];
		for (int n = cur_entry+1; n<=last_entry; n++)
		    entries[n-1] -= 2;
		memmove(&RAM[base+offs],
			&RAM[base+offs+2],
			size_msg - 2);
		size_msg -= 2;
		move_ref(2);
	    }
	    break;
	default:
	    int unicode = event->key.keysym.unicode;
	    if (unicode >= ' ' && unicode < 256 && validchars[unicode]) {
		sprites_changed = 1;
		UINT8 *offs;
		UINT16 prevchar;
		if (screens) {
		    offs = &RAM[base+offset+(cursorx*16+cursory)*4];
		    prevchar = ReadWord(offs-16*4);
		} else {
		    offs = &RAM[base+offset+(cursorx+20*cursory)*2];
		    prevchar = ReadWord(offs-2)+OFFS_SPRITES;
		}
		if (size_msg) {
		    // find the real len, that is the len of the current
		    // entry, not the length before the next end of string
		    // code
		} else if (cursory*20+(cursorx+1)==len && is_in_map(prevchar)) {
		    if (screens) {
			prevchar = ReadWord(offs); // exception for the very last char
			offs += 4;
		    } else {
			prevchar = ReadWord(offs)+OFFS_SPRITES; // exception for the very last char
			offs += 2;
		    }
		}

		if ((cursorx > 0 || cursory > 0) && ((prevchar >= 0x301 && prevchar <= 0x410))) {
		    // 1 get prevchar code
		    int n;
		    for (n= 32; n<255; n++) {
			if (validchars[n] == prevchar) {
			    prevchar = n;
			    break;
			}
		    }
		    printf("found prevchar %d\n",prevchar);
		    if (prevchar == 0x27 &&
			    (unicode == 0x2e || unicode == 0x20))
			prevchar = 0x2e;
		    if (prevchar < 127) {
			int combi = (prevchar<<8) | unicode;
			for (n=0; n<used_map; n++) {
			    if (map[n] == combi) {
				int loc = get_sprite_map(n);
				printf("inserting combi prevchar %x unicode %x found at pos %x loc %x\n",prevchar,unicode,n,loc);
				video_spr_usage[loc]=1;
				put_char(&GFX[loc*0x100],&font[prevchar*16+4]);
				put_char(&GFX[loc*0x100+8],&font[unicode*16+4]);
				if (screens)
				    WriteWord(offs-16*4,loc);
				else
				    WriteWord(offs-2,loc-OFFS_SPRITES);
				return 1;
			    }
			}
			if (used_map < size_map) {
			    map[used_map] = combi;
			    int loc = get_sprite_map(used_map);
			    video_spr_usage[loc]=1;
			    put_char(&GFX[loc*0x100],&font[prevchar*16+4]);
			    put_char(&GFX[loc*0x100+8],&font[unicode*16+4]);
			    if (screens)
				WriteWord(offs-16*4,loc);
			    else
				WriteWord(offs-2,loc-OFFS_SPRITES);
			    used_map++;
			    printf("creating new combination at %x used_map %x\n",loc,used_map);
			    return 1;
			} else {
			    printf("map full %d >= %d\n",used_map,size_map);
			    exit(1);
			}
		    }
		}
		if (screens) {
		    WriteWord(offs,
			    validchars[unicode]);
		    WriteWord(offs+2,0xf000);
		} else {
		    if (ReadWord(offs) == 0xffff) {
			if (size_msg)
			    insert_char();
			if (ReadWord(offs) == 0xffff)
			    offs -= 2; // very last char fix
		    }
		    WriteWord(offs,
			    validchars[unicode]-OFFS_SPRITES);
		}
		event->key.keysym.sym = SDLK_RIGHT;
		return handle_key(event);
	    }
	}
	break;
    }
    return 0;
}

static void draw_cursor(int x,int y) {
    int cx,cy;
    for (cx=0; cx<16; cx++) {
	for (cy=0; cy<16; cy++) {
	    UINT8 *px = &GameBitmap->line[y+cy][x+cx];
	    if (*px < 8) // ssrpg fonts use "parasite" colors >= 8
		*px ^= 255;
	    else
		*px = 255;
	}
    }
}

static int base_no;

static int draw_translator(int sel) {
    if (bitmap_color_depth(GameBitmap) != 8) {
	sprite_menu->draw();
	return 0;
    }
    clear_game_screen(0);
    ClearPaletteMap();
    UINT8 map[16];

    int x = 0, y = 0;
    int n;
    for (n=0; n<16; n++)
	map[n] = n; // direct mapping
    n = 0;
    UINT16 spriteno;
    int cx = cursorx*16;
    int cy = cursory*16;
    if (screens) {
	for (x=0; x<=19; x++)
	    for (y=0; y<16; y++) {
		UINT32 ofs = (x*16+y)*4+base+offset;
		spriteno = ReadWord(&RAM[ofs]);
		if (base < 0x80000) spriteno += 0x1200;
		if (spriteno < 0x8000)
		    Draw16x16_Trans_Mapped_8(&GFX[(spriteno)<<8],x*16,y*16,map);
		if (x == cursorx && y == cursory) {
		    draw_cursor(x*16,y*16);
		}
	    }
	len = 20*15;
	return 0;
    }

    while ((spriteno = ReadWord(&RAM[base+offset+n])) != 0xffff) {
	// printf("%d,%d,%x (%x+%x+%x)\n",x,y,spriteno,base,offset,n);
	if (!spriteno)
	    spriteno = 0x400; // note (line break)
	else
	    spriteno += OFFS_SPRITES;
	// printf("%d,%d,%x\n",x,y,spriteno);
	if (spriteno < 0x8000)
	    Draw16x16_Trans_Mapped_8(&GFX[(spriteno)<<8],x,y,map);
	if (x == cx && y == cy) {
	    draw_cursor(x,y);
	}
	x += 16;
	if (x+16 > GameBitmap->w) {
	    x = 0;
	    y += 16;
	    if (y+16 > GameBitmap->h) break;
	}
	n+=2;
    }
    len = n/2;

    return 0;
}

#if 0
static UINT32 location[] = { 0x72014, 0x73aca, // intro 71d82
    /* Referenced from
     * 52160
     * 52b14
     * 54274 */
    0x60ff8, 0x62b32, // ingame (prog.prg) 60dec
    /* referenced from
     * 6668
     * 6718
     * 17bd8 */
    // miniature 60d62
    /* referenced from
     * 66cc
     * 6d58 */
    // inconnu 73908-73a88
    /* Referenced from nowhere !!! */
    // followed by dsk! at 73ace (offsets)
    // followed by dsk! at 73b44 which contains long ascii strings
    // which should allow some shrinking ?
    0xc6028, 0xca000, // screens
    0x9782c, 0xa8000, // screens 2
    0x7b39a, 0x1fffff}; // unknown
#endif

static void init_valid_chars() {
    memset(validchars,0,sizeof(validchars));
    int n;
    for (n='0'; n<='9'; n++)
	validchars[n] = 0x3a9+n-'0';
    for (n='A'; n<='Z'; n++)
	validchars[n] = 0x3b3+n-'A';
    for (n='a'; n<='z'; n++)
	validchars[n] = 0x3cd+n-'a';
    validchars[' '] = 0x301;
    validchars[39] = 0x403; // ' doesn't exist in the font, but we need it!
    validchars[34] = 0x404;
    validchars[','] = 0x405;
    validchars[';'] = 0x405;
    validchars['!'] = 0x401;
    validchars['?'] = 0x402;
    validchars['.'] = 0x403;
    validchars['('] = 0x407;
    validchars[')'] = 0x408;
    validchars['['] = 0x409;
    validchars[']'] = 0x40a;
    validchars['/'] = 0x40b;
    validchars[':'] = 0x40e;
    validchars['+'] = 0x40f;
    validchars['-'] = 0x410;
    /*validchars['é'] = validchars['è'] = validchars['ê'] = validchars['ë'] =
      0x3cd+'e'-'a';
      validchars['ù'] = 0x3cd+'u'-'a';
      validchars['â'] = validchars['à'] = 0x3cd+'a'-'a'; */
}

static int selected;

static int do_exit(int sel) {
    selected = sel;
    return 1;
}

int set_entry(int sel) {
    offset = get_entry_offset(base, cur_entry);
    sprintf(str_offset,"Offset %x",base+offset);
    cursorx = cursory = 0;
    if (sprite_menu) sprite_menu->draw();
    return 0;
}

static int insert_code(int sel) {
    int ret = MessageBox("Insertion",
	    "Which portrait do you want to insert ?",
	    "Haohmaru|"
	    "Haohmaru's master|Angry master"
	    "Genjuro|Angry Genjuro|"
	    "Amakusa|"
	    "Ironic Haohmaru|");
    int offs = offset+(cursorx+20*cursory)*2;
    if (ret <= 0) return 0;
    int val[] = { 0x00060005, 0x00070035, 0x00070038, 0x00090008, 0x0009000b,
	0x00070057, 0x00090000 };
    WriteLongSc(&RAM[base+offs],val[ret-1]);
    return 0;
}

static menu_item_t msg_menu[] =
{
    { str_offset, &set_entry, &cur_entry, 3, {0, 1000, 1}, { _("hidden") } },
    { _("Insert special code..."), &insert_code },
    { "", &draw_translator, &base_no, ITEM_TBITMAP, { 320, 256, 8 } },
    { NULL, NULL, NULL }
};

static menu_item_t screen_menu[] =
{
    { str_offset, &set_entry, &cur_entry, 3, {0, 1000, 1}, { _("hidden") } },
    { "", &draw_translator, &base_no, ITEM_TBITMAP, { 320, 256, 8 } },
    { NULL, NULL, NULL }
};

int do_screen(int sel) {
    char name[30];
    UINT32 offset,size;
    init_valid_chars();
    name[0] = 0;
    int nb = 10;
    UINT32 loff[10],lsize[10];
    int n = 0;
    char buff[1024];
    buff[0] = 0;

#if 0
    // 100% experimental, this screen is just a part of a screen (5x3)
    // with offset $1200 on the chars which seems to be used during the
    // fights. Given this size it's probably not a good idea to try to
    // edit it directly in the gui
    strcpy(buff,"prog.prg offset:7a9ca|");
    loff[n] = 0x7a9ca;
    lsize[0] = 20*16*4+4;
    n = 1;
#endif

    while (find_spec("f_bg",name,&offset,&size)) {
	sprintf(&buff[strlen(buff)],"%s offset:%x|",name,offset);
	loff[n] = offset;
	lsize[n] = size;
	n++;
	if (n == nb) {
	    ErrorMsg("too many msg, only the 1st 10 are displayed");
	    break;
	}
    }
    buff[strlen(buff)-1] = 0; // remove last |
    selected = -1;
    selected = MessageBox("Selection","File to edit ?",buff);

    if (selected < 0) return 0;
    selected--;

    /* The format of the screens is a little weird :
     * word 0 : $ffff
     * then offsets to screens / 4 ($a -> screen at $a*4=$28)
     * until the 1st screen which is 20x16, 4 bytes / sprite,
     * see draw_translator for details */
    base = loff[selected];
    int last_entry;
    if (ReadWord(&RAM[base]) == 0xffff) {
	last_entry =
	    screen_menu[0].values_list[1] = (ReadWord(&RAM[base+2])*4-2)/2-1;
    } else {
	last_entry =
	    screen_menu[0].values_list[1] = (ReadWord(&RAM[base])*4-2)/2-1;
    }
    size_msg = lsize[selected];
    screens = 1;
    sprintf(str_offset,"Offset 0000");
    if (cur_entry > last_entry)
	cur_entry = 0;

    sprite_menu = new TTransMenu(_("Edit screen"),screen_menu);
    set_entry(0);
    sprite_menu->execute();
    delete sprite_menu;
    sprite_menu = NULL;
    size_msg = 0;
    return 0;
}

int do_msg(int sel) {
    char name[30];
    UINT32 offset,size;
    screens = 0;
    init_valid_chars();
    name[0] = 0;
    int nb = 10;
    menu_item_t *menu = (menu_item_t*)calloc(nb,sizeof(menu_item_t));
    UINT32 loff[10],lsize[10];
    int n = 0;
    menu[n].label = "prog.prg miniatures (60d62)";
    loff[n] = 0x60d62;
    lsize[n++] = 0x60dec-0x60d62;

    // init references...
    size = get_msg_size(loff[0]);
    if (size != lsize[0]) {
	printf("size detection problem got %x, should be %x\n",
		size,lsize[0]);
	exit(1);
    }

    menu[n].label = "prog.prg ingame texts (60dec)";
    loff[n] = 0x60dec;
    lsize[n] = get_msg_size(loff[n]);
    n++;

    if (loff[0] + size != loff[1]) {
	printf("adr1 mismatch: %x, should be %x\n",loff[0]+size,
		loff[1]);
	exit(1);
    }

    menu[n].label = "prog.prg intro texts (71d82)";
    loff[n] = 0x71d82;
    lsize[n] = get_msg_size(loff[n]);
    n++;

    int start_n = n;
    while (find_spec("msg",name,&offset,&size)) {
	char buff[80];
	sprintf(buff,"%s offset:%x",name,offset);
	menu[n].label = strdup(buff);
	loff[n] = offset;
	lsize[n] = size;
	n++;
	if (n == nb) {
	    ErrorMsg("too many msg, only the 1st 10 are displayed");
	    break;
	}

    }
    int x;
    for (x=0; x<n; x++)
	menu[x].menu_func = &do_exit;
    selected = -1;
    TMenu *dlg = new TMenu(_("msg to edit"),menu);
    dlg->execute();
    delete dlg;

    while (n > start_n)
	free((void*)menu[--n].label);
    free(menu);
    if (selected < 0) return 0;

    /* The format of these msg files is very simple :
     * Word 0 contains the offset of the 1st entry of text
     * word 1 is 0
     * word 2 and next ones contain offsets to the following entries relative
     * to the offset given in word 0
     * until the offset of the 1st entry
     * Notice the order in which the entries are displayed is unknown for now!
     *
     * Then these are usual messages, see draw_translator for the details of
     * the messages format */
    base = loff[selected];
    msg_menu[0].values_list[1] = (ReadWord(&RAM[base])-4)/2;
    size_msg = lsize[selected];
    base_no = 0;
    sprintf(str_offset,"Offset 0000");
    int last_entry = (ReadWord(&RAM[base])-4)/2;
    if (cur_entry > last_entry)
	cur_entry = 0;

    sprite_menu = new TTransMenu(_("Edit msg"),msg_menu);
    set_entry(0);
    sprite_menu->execute();
    delete sprite_menu;
    sprite_menu = NULL;
    size_msg = 0;
    return 0;
}

/* TTransSS2 : same thing, but for SS2 (samurai shodown 2).
 * This time it uses the fix layer so it has a real 8x16 font (made of 2 fix
 * sprites on top of each other). The print function reads a code on a word,
 * puts this word as the value of the first sprite, then puts this code+1 just
 * under the 1st one to make the 8x16 char.
 * Since there is already a font available this time, the code will be easier */

class TTransSS2 : public TTransBitmap {
    public:
	TTransSS2(menu_item_t *my_menu) : TTransBitmap(my_menu)
    {
	cursorx = cursory = 0;
	sprites_changed = 0;
	font = NULL;
	map = NULL;
    }
	virtual int handle_key(SDL_Event *event);
};

int TTransSS2::handle_key(SDL_Event *event) {
    switch (event->type) {
	case SDL_KEYDOWN:
	    int sym = event->key.keysym.sym;
	    switch (sym) {
		case SDLK_RIGHT:
		case SDLK_LEFT:
		case SDLK_DOWN:
		case SDLK_UP:
		    return TTransBitmap::handle_key(event);
		case SDLK_RETURN:
		case SDLK_PAGEDOWN:
		    WriteWord(&RAM[base+offset+(cursorx+20*cursory)*2],
			    0x1000); // line break (0x1000 or 0x2000 ???)
		    event->key.keysym.sym = SDLK_RIGHT;
		    return handle_key(event);
		case SDLK_END:
		    WriteWord(&RAM[base+offset+(cursorx+20*cursory)*2],
			    0x0000); // end of text (not sure yet this one is usefull)
		    sprites_changed = 1;
		    event->key.keysym.sym = SDLK_LEFT; // text ends earlier now
		    return handle_key(event);
		default:
		    int unicode = event->key.keysym.unicode;
		    if (unicode >= ' ' && unicode < 256 && validchars[unicode]) {
			UINT8 *offs = &RAM[base+offset+(cursorx+20*cursory)*2];
			if (ReadWord(offs) == 0x0)
			    offs -= 2; // very last char fix
			WriteWord(offs,
				validchars[unicode]);
			event->key.keysym.sym = SDLK_RIGHT;
			return handle_key(event);
		    }
	    }
	    break;
    }
    return 0;
}

class TTransSS2Menu : public TMenu {
    public:
	TTransSS2Menu(char *my_title, menu_item_t *mymenu) : TMenu(my_title,mymenu)
    { }
	virtual void create_child(int n);
};

void TTransSS2Menu::create_child(int n) {
    if (menu[n].values_list_size == ITEM_TBITMAP) {
	child[n] = new TTransSS2(&menu[n]);
    } else
	TMenu::create_child(n);
}

#if 0
static int draw_translator_ss2(int sel) {
    if (bitmap_color_depth(GameBitmap) != 8) {
	sprite_menu->draw();
	return 0;
    }
    clear_screen(0);
    ClearPaletteMap();
    UINT8 map[16];

    int x = 0, y = 0;
    int n;
    for (n=0; n<16; n++)
	map[n] = n; // direct mapping
    n = 0;
    UINT16 spriteno;
    int cx = cursorx*16;
    int cy = cursory*16;
    while ((spriteno = ReadWord(&RAM[base+offset+n])) != 0x0000) {
	// printf("%d,%d,%x (%x+%x+%x)\n",x,y,spriteno,base,offset,n);
	if (!spriteno)
	    spriteno = 0x400; // note (line break)
	// printf("%d,%d,%x\n",x,y,spriteno);
	if (spriteno < 0x1000) {
	    Draw8x8_Trans_Mapped(&neogeo_fix_memory[(spriteno)<<6],x,y,map);
	    Draw8x8_Trans_Mapped(&neogeo_fix_memory[(spriteno+1)<<6],x,y,map);
	}
	if (x == cx && y == cy) {
	    int cx,cy;
	    for (cx=0; cx<8; cx++) {
		for (cy=0; cy<16; cy++) {
		    UINT8 *px = &GameBitmap->line[y+cy][x+cx];
		    if (*px < 8) // ssrpg fonts use "parasite" colors >= 8
			*px ^= 255;
		    else
			*px = 255;
		}
	    }
	}
	x += 8;
	if (x+8 > GameBitmap->w) {
	    x = 0;
	    y += 16;
	    if (y+16 > GameBitmap->h) break;
	}
	n+=2;
    }
    len = n/2;

    return 0;
}

int do_translate_ss2(int sel) {
    memset(validchars,0,sizeof(validchars));
    int n;
    for (n='A'; n<='Z'; n++)
	validchars[n] = 0x7440+n-'A';
    for (n='a'; n<='z'; n++)
	validchars[n] = 0x7440+n-'a'; // no lower case chars apparently...
    validchars[' '] = 0x74fc;
    validchars['!'] = 0x7478;
    validchars['?'] = 0x74b2;
    validchars['.'] = 0x2000;
    /*validchars['é'] = validchars['è'] = validchars['ê'] = validchars['ë'] =
      0x3cd+'e'-'a';
      validchars['ù'] = 0x3cd+'u'-'a';
      validchars['â'] = validchars['à'] = 0x3cd+'a'-'a'; */
    set_location(0);
    sprite_menu = new TTransSS2Menu(_("Translator"),sprites_menu);
    sprite_menu->execute();
    delete sprite_menu;
    sprite_menu = NULL;
    return 0;
}
#endif

