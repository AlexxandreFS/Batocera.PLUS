/******************************************************************************/
/*                                                                            */
/*                            LOAD ROMS FROM ROM_INFO                         */
/*                                                                            */
/******************************************************************************/

#include "loadroms.h"
#include "files.h"
#include "gameinc.h"
#include "string.h"
#include "gui.h" // load_progress
#include "bezel.h"
#include "tc005rot.h"
#include "sasound.h"
#include "conf-cpu.h"
#if HAVE_6502
#include "6502/m6502hlp.h"
#endif
#include "7z.h"

#undef _
#define _(string) gettext(string)

UINT8 *GFX,*Z80ROM,*ROM,*PCMROM;
UINT8 *load_region[REGION_MAX];
// This is static, because it's accessed by get_region_size,
// which allows to change implementation.
static UINT32 region_size[REGION_MAX];
char *alt_names[8];
int load_error;
char *load_debug;
int roms_count,loaded_roms;

UINT8 *gfx[MAX_GFX], *gfx_solid[MAX_GFX];
UINT8 *gfx1, *gfx2, *gfx3;
UINT8 *gfx1_solid, *gfx2_solid, *gfx3_solid;
int max_sprites[MAX_GFX];

static UINT8 *temp_buffer;
static UINT32 temp_buffer_size;

static UINT8 *get_temp_buffer(UINT32 size)
{
   if((temp_buffer) && (temp_buffer_size >= size))
   {
      return temp_buffer;
   }
   else
   {
      if(temp_buffer)
         FreeMem(temp_buffer);

      if(!(temp_buffer = AllocateMem(size)))
         return NULL;

      temp_buffer_size = size;

      return temp_buffer;

   }
}

static int region_empty(const ROM_INFO *rom_list, UINT32 region) {
   while(rom_list->name)
   {
     if(rom_list->region == region) {
       if (!strcmp(rom_list->name,REGION_EMPTY)) {
	 return 1;
       }
     }
     rom_list++;
   }
   return 0;
}

static void free_temp_buffer(void)
{
   if(temp_buffer)
      FreeMem(temp_buffer);
}

static int get_region_size_from_rominfo(const struct ROM_INFO *rom_list, UINT32 region, const struct DIR_INFO *head, int *number_of_roms ) {
  UINT32 i=0, j=0;
  char *prev_name = NULL;
  int last_load = -1,flag;
  if (!rom_list) return 0;
  if (region_empty(rom_list,region))
      return 0;
   while(rom_list->name)
   {
     if(rom_list->region == region)
      {
	if (prev_name != rom_list->name && *rom_list->name) {
	  (*number_of_roms)++;
	  prev_name = rom_list->name;
	}
	flag = rom_list->flags;
	if (flag == LOAD_CONTINUE) {
	    flag = last_load;
	}

	switch(flag)
	  {
	  case LOAD_NORMAL:
	  case LOAD_SWAP_16:
	  case LOAD8X8_16X16:
	  case LOAD_FILL:
	    j = rom_list->offset + rom_list->size;
            break;
	  case LOAD_8_16:
	  case LOAD_8_16S:
	  case LOAD_BE:
	    j = rom_list->offset + (rom_list->size * 2) - 1;
            break;
	  case LOAD_8_32:
	    j = rom_list->offset + (rom_list->size * 4) - 3;
	    break;
	  case LOAD_8_64:
	    j = rom_list->offset + (rom_list->size * 8) - 7;
            break;
	  case LOAD_16_32:
	  case LOAD32_SWAP_16:
	    j = rom_list->offset + (rom_list->size * 2) - 2;
            break;
	  case LOAD_16_64:
	    j = rom_list->offset + (rom_list->size * 4) - 6;
            break;
         }
	last_load = flag;

         if(i < j)
         {
            i = j;
         }
      }

      rom_list++;
   }
   if (!i) {
     char *dir = head[0].maindir;

     /* If this region has a length of 0, and we are a romof, then check if the parent
	has the region... (recursion) */

     while ( dir){

       if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof){
	   i = get_region_size_from_rominfo(game_romof->rom_list,region,game_romof->dir_list,number_of_roms);
	   if (i)
	     return i;
	 }
       }
       head++;
       dir = head[0].maindir;
     }
   }

   return i;
}

UINT32 get_region_size(UINT32 region)
{
   const ROM_INFO *rom_list;
   UINT32 size;

   if (region_size[region]) {
     return region_size[region];
   }

   rom_list = current_game->rom_list;
   if (!rom_list) return 0;
   size = get_region_size_from_rominfo(rom_list,region,current_game->dir_list,&roms_count);

   print_debug("region: 0x%02x size: 0x%08x\n", region, size);
   region_size[region] = size;
   return size;
}

/*

find a game based on main_name (useful for looking up romof games)

*/

GAME_MAIN *find_game(char *main_name)
{
   UINT32 i;

   for(i=0 ; i<(UINT32)game_count ; i++){

      if(! stricmp(main_name, game_list[i]->main_name) )

         return game_list[i];

   }

   return NULL;
}

/* recursively search for a rom. recursion allows rom inheritance to */
/* any depth (eg. game a uses roms from game b, game b gets the roms */
/* from game c and game c gets them from game d! yes, I know it's a */
/* bit unlikely, but you never know and recursion makes it look nice). */

static ROM_INFO  rec_rom_info;      // the rom to load
static UINT8    *rec_dest;          // destination memory buffer

static UINT32 recursive_rom_load(const DIR_INFO *head, int actual_load)
{
   char *dir;

   dir = head[0].maindir;

   if( dir ){

      if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof){

            UINT32 len;

            len = recursive_rom_load( game_romof->dir_list, actual_load );

            if(len)

               return len;

         }

      }
      else{

         UINT32 ta;
         char path[512];

         for(ta = 0; dir_cfg.rom_dir[ta]; ta ++){

            if(dir_cfg.rom_dir[ta][0]){

		if (!strcmp(rec_rom_info.name,REGION_EMPTY))
		    return 1;

		sprintf(path, "%s%s.zip", dir_cfg.rom_dir[ta], dir);
		if((load_zipped(path, rec_rom_info.name, rec_rom_info.size, rec_rom_info.crc32, rec_dest, actual_load))){
		    // printf("loaded %s from %s\n",rec_rom_info.name,path);
		    return 1;
		}

		sprintf(path, "%s%s.7z", dir_cfg.rom_dir[ta], dir);
		if((load_7z(path, rec_rom_info.name, 0, rec_rom_info.size, rec_rom_info.crc32, rec_dest, actual_load))){
		    // printf("loaded %s from %s\n",rec_rom_info.name,path);
		    return 1;
		}

		sprintf(path, "%s%s/%s", dir_cfg.rom_dir[ta], dir, rec_rom_info.name);
		if((load_file(path, rec_dest, rec_rom_info.size)))
		    return 1;

            }
         }

      }

      return recursive_rom_load( head+1, actual_load );

   }
   else{

      return 0;

   }
}

static UINT32 recursive_rom_size(const DIR_INFO *head)
{
   char *dir;

   dir = head[0].maindir;

   if( dir ){

      if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof){

            UINT32 len;

            len = recursive_rom_size( game_romof->dir_list );

            if(len)

               return len;

         }

      }
      else{

         UINT32 ta,len;
         char path[512];

         for(ta = 0; dir_cfg.rom_dir[ta]; ta ++){
	   sprintf(path, "%s%s.zip", dir_cfg.rom_dir[ta], dir);
	   if( ( len=size_zipped(path, rec_rom_info.name,rec_rom_info.crc32) ) )
	     return len;

	   sprintf(path, "%s%s.7z", dir_cfg.rom_dir[ta], dir);
	   if((len=load_7z(path, rec_rom_info.name, 0, rec_rom_info.size, rec_rom_info.crc32, NULL, 0)))
	     return len;

	   sprintf(path, "%s%s/%s", dir_cfg.rom_dir[ta], dir, rec_rom_info.name);
	   if( ( len=size_file(path) ) )
	     return len;
         }

      }

      return recursive_rom_size( head+1 );

   }
   else{

      return 0;

   }
}

/*

dumps the search path for a dir_list. it recursively lists
any romof path list(s)

*/

static void dump_search_path(const DIR_INFO *dir_list)
{
   char *dir;

   while(dir_list->maindir){

      dir = dir_list->maindir;

      if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof)

            dump_search_path(game_romof->dir_list);

      }
      else{

         if( ! IS_CLONEOF(dir) ){

            UINT32 i;

	    for(i = 0; dir_cfg.rom_dir[i]; i ++){


	      sprintf(load_debug+strlen(load_debug),"%s%s [.zip|7z]\n",dir_cfg.rom_dir[i], dir);

	    }
         }
      }

      dir_list++;
   }
}

UINT32 find_alternative_file_names(const ROM_INFO *rom_info, const DIR_INFO *dir_list)
{
   GAME_MAIN *game_romof;
   const ROM_INFO  *rom_list_romof;
   char *dir;
   UINT32      alt_name_count;

   alt_name_count = 0;

   if((!rom_info->crc32) || (!rom_info->size))

      return 0;

   while(dir_list->maindir){

      dir = dir_list->maindir;

      if( IS_ROMOF(dir) ){

         game_romof = find_game(dir+1);

         if(game_romof){

            rom_list_romof = game_romof->rom_list;

            while(rom_list_romof->name){

               if( (rom_list_romof->size  == rom_info->size )
                && (rom_list_romof->crc32 == rom_info->crc32) ){

                  alt_names[alt_name_count] = rom_list_romof->name;
                  alt_name_count = (alt_name_count+1)&7;

               }

               rom_list_romof ++;

            }

         }

      }

      dir_list ++;
   }

   return alt_name_count;
}

// Hack to load correctly these 16x16x8 sprites...
// I know it's ugly, but I spent one hour trying to figure out how these
// gfx layout worked... After that, enough was enough !


int load_sprite_8_16b(char *rom, UINT8 *dst, UINT32 len){
  UINT8 *src;
  UINT32 ta,tb;

  // Called for (offsets & 1)==0

  src = get_temp_buffer(len);
  if(src){
    if(load_rom(rom, src, len)){
      for(ta = 0, tb=0; ta < len; ta++, tb += 2){
	dst[tb+1] = (src[ta] << 0) & 0xF0;
	dst[tb+0] = (src[ta] << 4) & 0xF0;
      }
      return 1;
    }
  }
  return 0;
}

int load_sprite_8_16(char *rom, UINT8 *dst, UINT32 len){
  UINT8 *src;
  UINT32 ta,tb;

  // Called for offsets & 1
  src = get_temp_buffer(len);
  if(src){
    if(load_rom(rom, src, len)){
      for(ta = 0,tb=0; ta < len; ta ++, tb += 2){
	dst[tb+1] |= (src[ta] >> 4) & 0x0F;
	dst[tb+0] |= (src[ta] >> 0) & 0x0F;
      }
      return 1;
    }
  }
  return 0;
}

// Byte Expand : 8 bits to 16 bits...
// Can't be static : called directly by f3 games.
int load_be(char *name, UINT8 *ROM, int size){
  UINT8 *TMP;
  int n;

  if(!(TMP=get_temp_buffer(size))) return 0;
  if(!load_rom(name, TMP, size)) return 0;
  for (n=0; n<size; n++)
    WriteWord68k(ROM+(n<<1),TMP[n]);
  return 1;
}

static int activate_continue;

static int load_region_files_from_rominfo(UINT32 region, UINT8 *dest, const ROM_INFO *rom_list, const struct DIR_INFO *head) {
  int found = 0,last_load,flag;

   while(rom_list->name)
   {
      if(rom_list->region == region)
      {
	flag = rom_list->flags;
	found = 1;
	if (flag == LOAD_CONTINUE && remaining_b) {
	    activate_continue = 1;
	    if (last_load == -1) {
		load_error |= LOAD_FATAL_ERROR;
		sprintf(load_debug+strlen(load_debug),
			"Can't use load_continue name %s\n",rom_list->name);
		return 0;
	    }
	    flag = last_load;
	} else
	    activate_continue = 0;

	switch(flag)
	  {
	  case LOAD_NORMAL:
	    if(!load_rom(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  case LOAD_FILL:
	    memset(dest + rom_list->offset,rom_list->crc32, rom_list->size);
	    break;
	  case LOAD_8_16S:
	    if (rom_list->offset & 1){
	      if(!load_sprite_8_16(rom_list->name, dest + (rom_list->offset & ~1), rom_list->size)) return 0;
	    } else {
	      if(!load_sprite_8_16b(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
	    }
	    break;
	  case LOAD_8_16:
	      if(!load_rom_8_16(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
	      break;
	  case LOAD_BE:
	    if(!load_be(rom_list->name,dest + rom_list->offset, rom_list->size)) return 0;
	    break;
	  case LOAD_8_32:
	    if(!load_rom_8_32(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  case LOAD_8_64:
	    if(!load_rom_8_64(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
	    break;
	  case LOAD_16_32:
	    if(!load_rom_16_32(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  case LOAD32_SWAP_16:
	    if(!load32_swap_16(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  case LOAD_16_64:
	    if(!load_rom_16_64(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  case LOAD_SWAP_16:
#if HAVE_68000
	    if(!load_rom_swap_16(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
#else
	    fprintf(stderr,"no 68000 compiled in for load_swap_16\n");
	    return 1;
#endif
            break;
	  case LOAD8X8_16X16:
	    if(!load_rom_8x8_16x16(rom_list->name, dest + rom_list->offset, rom_list->size)) return 0;
            break;
	  }
      }
      if (remaining_b)
	  last_load = flag;
      else
	  last_load = -1;

      rom_list++;
   }

   if (region_empty(rom_list,region)) found = 1;
   if (!found) {
     char *dir = head[0].maindir;
     int found = 0;

     /* If this region has a length of 0, and we are a romof, then check if the parent
	has the region... (recursion) */

     while ( dir && !found){

       if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof){
	   found = load_region_files_from_rominfo(region,dest,game_romof->rom_list, game_romof->dir_list);
	   if (found) {
	     return 1;
	   }
	 }
       }
       head++;
       dir = head[0].maindir;
     }
     return 0;
   }

   return found;
}

static UINT32 load_region_files(UINT32 region, UINT8 *dest)
{
   const ROM_INFO *rom_list;

   rom_list = current_game->rom_list;
   return load_region_files_from_rominfo(region,dest,rom_list,current_game->dir_list);
}

static UINT32 load_rom_region(UINT32 region)
{
   UINT32 region_size;

   region_size = get_region_size(region);

   if(region_size)
   {
      if(!(load_region[region] = AllocateMem(region_size+2))) return 0;

      memset(load_region[region], 0x00, region_size);

      if(!load_region_files(region, load_region[region])) {
	return 0;
      }
   }

   return 1;
}

static UINT32 load_gfx_region(UINT32 region)
{
   UINT32 reg_size = 0;
   const VIDEO_INFO *video;
   GFX_LIST *gfx_list;
   int nb = 0;
   UINT8 *buffer;

   video = current_game->video;
   gfx_list = video->gfx_list;
   if (!gfx_list) return 1; // Correct, but nothing to load
   int nb2;
   for (nb=1; gfx_list[nb].region > 0 && gfx_list[nb].region < REGION_MAX; nb++) {
       for (nb2=0; nb2<nb; nb2++) {
	   int region = gfx_list[nb].region;
	   if (gfx_list[nb2].region == region) {
	       int newr = gfx_list[nb].region+1;
	       while (load_region[newr] && newr <= REGION_GFX5)
		   newr++;
	       if (load_region[newr]) {
		   printf("duplicate region, and no more free region !\n");
		   exit(1);
	       }
	       load_region[newr] = AllocateMem(get_region_size(region));
	       if (!load_region[newr]) {
		   printf("can't allocate new region !\n");
		   exit(1);
	       }
	       memcpy(load_region[newr],load_region[region],region_size[region]);
	       region_size[newr] = region_size[region];
	       gfx_list[nb].region = newr;
	   }
       }
   }
   nb = 0;


   // now this function is called after the roms have been loaded in the region...
   buffer = load_region[region];
   reg_size = get_region_size(region);
   if (!buffer)
     return 1; // this region is empty

   do {
     while(gfx_list->region) // region 0 is NONE or end of list
       {
	 if(gfx_list->region == region || gfx_list->region == 0xffffffff)
	   {
	     break;
	   }

         gfx_list++;
	 nb++;
       }

     // Special case for 8x8 -> 16x16 sprites in cave games...
     // I want it included as the others types...
     if (!gfx_list->layout) {
       return 1;
     }

      if (nb >= MAX_GFX) {
	allegro_message("nb >= MAX_GFX in loadroms ! this is incredible !\n");
	exit(1);
      }

      if((gfx[nb] = load_region[region] = decode_gfx(buffer, reg_size, gfx_list->layout,&region_size[region]))) {
#if USE_TC005
	if (buffer != tc0005rot.GFX_ROT)
#endif
       	{ // if this buffer is used for tc005rot then
	  // don't rotate !!!
	  if (gfx_list->layout->width == 16 && gfx_list->layout->height == 16) {
	    gfx_solid[nb] = make_solid_region_16x16(region);
	    max_sprites[nb] = get_region_size(region)/0x100;
	  } else if (gfx_list->layout->width == 16 && gfx_list->layout->height == 8) {
	    gfx_solid[nb] = make_solid_region_16x8(region);
	    max_sprites[nb] = get_region_size(region)/0x10/8;
	  } else if (gfx_list->layout->width == 8) {
	    gfx_solid[nb] = make_solid_region_8x8(region);
	    max_sprites[nb] = get_region_size(region)/0x40;
	  }
	}
      } else
	return 0;
      gfx_list++; // check if there is more than 1 layout for this region...
      nb++;
   } while (gfx_list->region);

   return 1;
}

void decode_region(UINT32 region, const GFX_LAYOUT *gfx_layout) {
  // used to decode a region after manipulating it in the loading function
  UINT8 *tmp = decode_gfx(load_region[region], get_region_size(region), gfx_layout,&region_size[region]);
  // The FreeMem might not work because it's a temporary buffer, but it won't crash raine
  // neither
  FreeMem(load_region[region]);
  load_region[region] = tmp;
}

extern int call_init_tile_cache;

char *get_region_name(int reg) {
    static char region[25];
    if (reg >= REGION_ROM1 && reg <= REGION_ROM4)
	sprintf(region,"ROM%d",reg-REGION_ROM1+1);
    else if (reg >= REGION_GFX1 && reg <= REGION_GFX5)
	sprintf(region,"GFX%d",reg-REGION_GFX1+1);
    else if (reg >= REGION_SMP1 && reg <= REGION_SMP4)
	sprintf(region,"SMP%d",reg-REGION_SMP1+1);
    else if (reg == REGION_PROMS)
	strcpy(region,"proms");
    else if (reg == REGION_SPRITES)
	strcpy(region,"sprites");
    else if (reg == REGION_FIXED)
	strcpy(region,"fixed");
    else if (reg == REGION_FIXEDBIOS)
	strcpy(region,"bios fixed");
    else if (reg == REGION_YMSND_DELTAT)
	strcpy(region,"ym2610 sound (deltat)");
    else if (reg == REGION_MAINBIOS)
	strcpy(region,"bios");
    else if (reg == REGION_AUDIOCRYPT)
	strcpy(region,"crypted audio");
    else if (reg >= REGION_USER1 && reg <= REGION_USER2)
	sprintf(region,"USER%d",reg-REGION_USER1+1);
    else
	sprintf(region,"unknown");
    return region;
}

void load_game_rom_info(void)
{
   UINT32 i;

   for(i = 0; i < REGION_MAX; i++) {
      load_region[i] = NULL;
      region_size[i] = 0;
      if (i < MAX_GFX) {
	gfx[i] = NULL;
	gfx_solid[i] = NULL;
      }
   }

   temp_buffer = NULL;
   temp_buffer_size = 0;

   /*

   program rom regions

   */

   roms_count = 0;
   // Pre-init roms_count
   for (i=1; i<REGION_MAX; i++) {
     get_region_size(i);
   }
   // Add roms without region (manual loading)
   const ROM_INFO *rom_list;

   rom_list = current_game->rom_list;

   while(rom_list->name)
	{
	  if (!rom_list->region)
	    roms_count++;
	  rom_list ++;
	}
   loaded_roms = 0;

   load_message(_("Loading CPU code"));
   for (i=1; i<REGION_MAX; i++) {
     if (i == REGION_GFX1)
       load_message(_("Loading video regions"));
     else if (i == REGION_SMP1)
       load_message(_("Loading audio regions"));

     if(!load_rom_region(i)) return;
   }

   /*

   map to some old globals

   */

   ROM = load_region[REGION_ROM1];
   Z80ROM = load_region[REGION_ROM2]; // short cut
   PCMROM = load_region[REGION_SOUND1];

   load_message(_("Driver loading function..."));
   current_game->load_game();
   int test = 1;
#ifndef NO020
   test &= !MC68020;
#endif
#ifdef HAVE_6502
   test &= !M6502Engine;
#endif
#if HAVE_68000
   test &= !StarScreamEngine;
#endif
#if HAVE_Z80
   test &= !MZ80Engine;
#endif

   if (test) {
     sprintf(load_debug+strlen(load_debug),
       _("The game didn't initialise any CPU, this game can't work !\n"));
     load_error |= LOAD_FATAL_ERROR;
     return;
   }

   load_message(_("Applying graphics layouts..."));
   if(!load_gfx_region(REGION_GFX1)) return;
   if(!load_gfx_region(REGION_GFX2)) return;
   if(!load_gfx_region(REGION_GFX3)) return;
   if(!load_gfx_region(REGION_GFX4)) return;
   if(!load_gfx_region(REGION_GFX5)) return;

   if (load_region[REGION_GFX1]) {
     GFX = load_region[REGION_GFX1];
   }
   gfx1 = gfx[0];
   gfx2 = gfx[1];
   gfx3 = gfx[2];
   gfx1_solid = gfx_solid[0];
   gfx2_solid = gfx_solid[1];
   gfx3_solid = gfx_solid[2];

   if (call_init_tile_cache) {
     init_tile_cache();
     call_init_tile_cache = 0;
   }

   free_temp_buffer();

#if USE_BEZELS
   load_bezel();
#endif
}

/*

load rom from a filename

*/

static int load_rom_from_rominfo(char *rom, UINT8 *dest, UINT32 size, const ROM_INFO *rom_list, const struct DIR_INFO *head) {
   int found=0;
   while((rom_list->name) && (!rec_rom_info.crc32)){

      if(! stricmp(rom_list->name, rom) )
      {
         found++;
         rec_rom_info.crc32 = rom_list->crc32;
      }

      rom_list++;
   }

   if (!found) {
     char *dir = head[0].maindir;

     /* Implicitely search a rom in the parent's roms if it is not found */

     while ( dir && !found){

       if( IS_ROMOF(dir) ){

         GAME_MAIN *game_romof;

         game_romof = find_game(dir+1);

         if(game_romof){
	   found = load_rom_from_rominfo(rom,dest,size,game_romof->rom_list,game_romof->dir_list);
	 }
       }
       head++;
       dir = head[0].maindir;
     }
   }

   return found;
}

int load_rom(char *rom, UINT8 *dest, UINT32 size)
{
   const DIR_INFO *dir_list;
   const ROM_INFO *rom_list;
   UINT32     ta,tb,tc;
   int found;

   if (activate_continue) {
       if (remaining_size >= size) {
	   memcpy(dest,remaining_b,size);
	   if (remaining_size > size) {
	       memcpy(remaining_b,remaining_b+size,remaining_size-size);
	       remaining_size -= size;
	   } else {
	       FreeMem(remaining_b);
	       remaining_size = 0;
	       remaining_b = NULL;
	   }
       } else {
	   load_error |= LOAD_FATAL_ERROR;
	   sprintf(load_debug+strlen(load_debug),
		   _("Remaining size not enough for continue %s\n"),rom);
	   return 0;
       }
       return 1;
   }
   static char *last_rom;

   if (last_rom != rom) {
     loaded_roms++;
     last_rom = rom;
   }
   if (loaded_roms > roms_count) {
     printf("error loaded_roms > roms_count\n");
     exit(1);
   }
   load_progress(rom,loaded_roms*100/roms_count);
   dir_list = current_game->dir_list;

   // locate the full rom info (ie. crc32)

   rec_rom_info.name  = rom;
   rec_rom_info.size  = size;
   rec_rom_info.crc32 = 0;

   rom_list = current_game->rom_list;

   if (rom_list)
     found = load_rom_from_rominfo(rom,dest,size,rom_list, current_game->dir_list);
  else
    found = 0;

#if defined(RAINE_DEBUG)
   if (!found)
     {
       load_error |= LOAD_WARNING;

       sprintf(load_debug+strlen(load_debug),
	       "Warning: ROM not in gameinfo %s\n",rec_rom_info.name);
     }
#endif

   // now try loading it

   rec_dest = dest;

   ta = recursive_rom_load( dir_list, 1 );

   if(!ta){

   // try to locate alternative filenames via the crc32 & size data (merged sets)

   tc = find_alternative_file_names( &rec_rom_info, dir_list );

   // try loading with any alternative file names we found

   ta = 0;

   for(tb=0; tb<tc; tb++){

     rec_rom_info.name = alt_names[tb];

      ta = recursive_rom_load( dir_list, 1 );

      if(ta)
         tb = tc;

   }

   }

   // Error Logging

   if(!ta)
   {
      sprintf(load_debug+strlen(load_debug),_("Unable to open '%s'\n"),rom);
      sprintf(load_debug+strlen(load_debug),"\n");
      sprintf(load_debug+strlen(load_debug),_("Search path:\n"));
      sprintf(load_debug+strlen(load_debug),"\n");

      dump_search_path(dir_list);

      sprintf(load_debug+strlen(load_debug),"\n");

      load_error |= LOAD_FATAL_ERROR;

   }

   return ta;

}

/*

load rom from an index in the game rom_list[]

*/

int load_rom_index(UINT32 num, UINT8 *dest, UINT32 size)
{
   const ROM_INFO *rom_list;

   rom_list = current_game->rom_list;

   return load_rom(rom_list[num].name, dest, size);
}

// User specified dir_list, no error log

int load_rom_dir(const DIR_INFO *dir_list, char *rom, UINT8 *dest, UINT32 size, UINT32 crc32,int actual_load)
{
   UINT32 ta,tb,tc;

   // locate the full rom info (ie. crc32)

   rec_rom_info.name  = rom;
   rec_rom_info.size  = size;
   rec_rom_info.crc32 = crc32;

   // now try loading it

   rec_dest = dest;

   ta = recursive_rom_load( dir_list, actual_load );

   if(!ta){

   // try to locate alternative filenames via the crc32 & size data (merged sets)

   tc = find_alternative_file_names( &rec_rom_info, dir_list );

   // try loading with any alternative file names we found

   ta = 0;

   for(tb=0; tb<tc; tb++){

      rec_rom_info.name = alt_names[tb];

      ta = recursive_rom_load( dir_list,actual_load );

      if(ta)
         tb = tc;

   }

   }

   return ta;
}


static int load_rom_bytemap(char *rom, UINT8 *dest, UINT32 size, UINT32 mode)
{
   UINT8 *tmp;

   tmp = AllocateMem(size+2);

   if(tmp)
   {
      if(load_rom(rom, tmp, size))
      {
         UINT32 i;

         switch(mode)
         {
            case 0:
               for(i = 0; i < size; i ++)
                  dest[i << 1] = tmp[i];
            break;
            case 1:
               for(i = 0; i < size; i ++)
                  dest[i << 2] = tmp[i];
            break;
	 case 2: // load_16_32
               for(i = 0; i < size; i += 2)
                  WriteWord(&dest[i << 1], ReadWord(&tmp[i]));
            break;
	 case 3: // load_16_64
               for(i = 0; i < size; i+=2)
                  WriteWord(&dest[i << 2], ReadWord(&tmp[i]));
            break;
	 case 4: // load_8_64
               for(i = 0; i < size; i++)
                  dest[i << 3] = tmp[i];
            break;
	 case 5:
	   // LOAD32_SWAP_16 : as load_16_32 with words inversion
	   for(i = 0; i < size; i += 2)
	     WriteWord(&dest[i << 1], ReadWord68k(&tmp[i]));
	   break;
         }

         FreeMem(tmp);
         return 1;
      }
      else
      {
         FreeMem(tmp);
         return 0;
      }
   }
   else

      return 0;

}


int load_rom_8_16(char *rom, UINT8 *dest, UINT32 size)
{
   return load_rom_bytemap(rom, dest, size, 0);
}


int load_rom_8_32(char *rom, UINT8 *dest, UINT32 size)
{
   return load_rom_bytemap(rom, dest, size, 1);
}

int load_rom_8_64(char *rom, UINT8 *dest, UINT32 size)
{
   return load_rom_bytemap(rom, dest, size, 4);
}

int load_rom_16_32(char *rom, UINT8 *dest, UINT32 size)
{
   return load_rom_bytemap(rom, dest, size, 2);
}

int load32_swap_16(char *rom, UINT8 *dest, UINT32 size)
{
  return load_rom_bytemap(rom, dest, size, 5);
}

int load_rom_16_64(char *rom, UINT8 *dest, UINT32 size)
{
   return load_rom_bytemap(rom, dest, size, 3);
}

#if HAVE_68000
int load_rom_swap_16(char *rom, UINT8 *dest, UINT32 size)
{
   if(load_rom(rom, dest, size))
   {
      ByteSwap(dest, size);
      return 1;
   }
   else
   {
      return 0;
   }
}
#endif

void convert_8x8_16x16(UINT8* src, UINT8* dst, UINT32 len) {
  UINT32 ta,tb,line,row;
  for(ta = 0, tb=0; ta < len;){
    for (row=0; row<2; row++) { // 2 rows of 2 8x8 sprites
      for (line=0; line<8; line++) { // 8 lines of 16 pixels / row
	dst[tb+0]  = (src[ta+0] >> 4) & 0x0F;
	dst[tb+1]  = (src[ta+0] >> 0) & 0x0F;
	dst[tb+2]  = (src[ta+2] >> 4) & 0x0F;
	dst[tb+3]  = (src[ta+2] >> 0) & 0x0F;
	dst[tb+4]  = (src[ta+4] >> 4) & 0x0F;
	dst[tb+5]  = (src[ta+4] >> 0) & 0x0F;
	dst[tb+6]  = (src[ta+6] >> 4) & 0x0F;
	dst[tb+7]  = (src[ta+6] >> 0) & 0x0F;
	dst[tb+0] |= (src[ta+1] << 0) & 0xF0;
	dst[tb+1] |= (src[ta+1] << 4) & 0xF0;
	dst[tb+2] |= (src[ta+3] << 0) & 0xF0;
	dst[tb+3] |= (src[ta+3] << 4) & 0xF0;
	dst[tb+4] |= (src[ta+5] << 0) & 0xF0;
	dst[tb+5] |= (src[ta+5] << 4) & 0xF0;
	dst[tb+6] |= (src[ta+7] << 0) & 0xF0;
	dst[tb+7] |= (src[ta+7] << 4) & 0xF0;

	// Cool, we've just moved the 1st line of 8 pixels.
	// Now we need the next 8 pixels, on the next 8x8 sprite !

	tb+=8; ta+=64;
	dst[tb+0]  = (src[ta+0] >> 4) & 0x0F;
	dst[tb+1]  = (src[ta+0] >> 0) & 0x0F;
	dst[tb+2]  = (src[ta+2] >> 4) & 0x0F;
	dst[tb+3]  = (src[ta+2] >> 0) & 0x0F;
	dst[tb+4]  = (src[ta+4] >> 4) & 0x0F;
	dst[tb+5]  = (src[ta+4] >> 0) & 0x0F;
	dst[tb+6]  = (src[ta+6] >> 4) & 0x0F;
	dst[tb+7]  = (src[ta+6] >> 0) & 0x0F;
	dst[tb+0] |= (src[ta+1] << 0) & 0xF0;
	dst[tb+1] |= (src[ta+1] << 4) & 0xF0;
	dst[tb+2] |= (src[ta+3] << 0) & 0xF0;
	dst[tb+3] |= (src[ta+3] << 4) & 0xF0;
	dst[tb+4] |= (src[ta+5] << 0) & 0xF0;
	dst[tb+5] |= (src[ta+5] << 4) & 0xF0;
	dst[tb+6] |= (src[ta+7] << 0) & 0xF0;
	dst[tb+7] |= (src[ta+7] << 4) & 0xF0;

	// Go back to next line of 1st sprite and continue...
	ta -= 64-8; tb += 8;
      }
      // tb is where it should be.
      // ta is on the 2nd sprite. Must go to the third one now !
      ta += 64;
    }
    // Here we have just moved the 4 8x8 sprites.
    // ta would be on the 5th sprite which happens to be correct !
  }
}

int load_rom_8x8_16x16(char *rom, UINT8 *dst, UINT32 len){
  UINT8 *src;

  // Normally used in cave games to convert 8x8 sprites to 16x16...

  src = get_temp_buffer(len);
  if(src){
    if(load_rom(rom, src, len)){
      convert_8x8_16x16(src,dst,len);
      return 1;
    }  // if load_rom
  }
  return 0;
}

int rom_size_dir(const DIR_INFO *dir_list, char *rom, UINT32 size, UINT32 crc32)
{
   UINT32 ta,tb,tc;

   // locate the full rom info (ie. crc32)

   rec_rom_info.name  = rom;
   rec_rom_info.size  = size;
   rec_rom_info.crc32 = crc32;

   // now try loading it

   ta = recursive_rom_size( dir_list );

   if(!ta){

   // try to locate alternative filenames via the crc32 & size data (merged sets)

   tc = find_alternative_file_names( &rec_rom_info, dir_list );

   // try loading with any alternative file names we found

   ta = 0;

   for(tb=0; tb<tc; tb++){

      rec_rom_info.name = alt_names[tb];

      ta = recursive_rom_size( dir_list );

      if(ta)
         tb = tc;

   }

   }

   return ta;
}

void unpack_region_lsb(UINT32 region) {
  // unpack region : 1st four bits -> byte 0, 4 last bits -> byte 1
  if (load_region[region]) {
    UINT8 *src = load_region[region];
    UINT32 size = get_region_size(region);
    UINT8 *dest = AllocateMem(size * 2);
    UINT8 *dst = dest;
    UINT32 ta;
    for (ta=0; ta<size; ta++) {
      *dst++ = *src & 0xf;
      *dst++ = *src++ >> 4;
    }
    FreeMem(load_region[region]);
    load_region[region] = dest;
    region_size[region] = size * 2;
  }
}

void set_region_size(UINT32 region, UINT32 size) {
  // made for custom regions, for now only used by cps2 decryption
  region_size[region] = size;
}

void clear_regions() {
    int i;
    for(i = 0; i < REGION_MAX; i++) {
	if (load_region[i]) {
	    FreeMem(load_region[i]);
	    load_region[i] = NULL;
	    region_size[i] = 0;
	}
    }
}

