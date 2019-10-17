/******************************************************************************/
/*                                                                            */
/*                             PRO ACTION REPLAY                              */
/*                                                                            */
/******************************************************************************/

/* Description of the cheats.cfg file (taken from its header) :

 - For each game, upto 256 cheats can go in a [gamename]
   section. Each cheat can have the following fields:

    Cheat%02 = Addr:Data:Mask:Type:Name:Info

   . Addr = <32bit hex>
   . address in cpu memory map

   . Data = <8/16/32bit hex>
   . data to patch with

   . Mask = <8/16/32bit hex>
   . mask data for bit based cheats - set to 00 for non bit based cheats

   . Type = <8bit hex>
   . cheat patch type (see below)

   . Name = <string>
   . name for the cheat effect

   . Info = <string>
   . optional extra information string


 CHEAT TYPE
 ----------

 This determines how the cheat is applied to the memory. The following
 bits are used and can be combined together:

  bit#0 and bit#1:

  These control the size of the patch data in the following way:

  00 = patch data is 1 byte  ( 8 bit)
  01 = patch data is 2 bytes (16 bit)
  10 = patch data is 3 bytes (24 bit)
  11 = patch data is 4 bytes (32 bit)

  bit#2:

  This controls the use of mask data in the following way:

  0 = patch data directly (unmasked)
  1 = apply bitmask before patching data (masked)

  you can use a mask to patch a selection of individual bits
  mask data is the same size as patch data (see bit#0,1)

  bit#3:

  This controls the time the patch is active:

  0 = apply the patch constantly (permanent)
  1 = apply the patch once, then disable (temporary)

  bit#4:

  This determines if it's a watch cheat or not:

  0 = normal cheat
  1 = watch cheat

  in case of watch cheat, the "Data" field is used this way:
  4 left bits is Y coordonate and 4 right bits is X coordonate

  in case of watch cheat, the Info field is displayed with the watch.

 bit#5:

 1 = The cheat is editable. Serves as a level selector usually.

 bit#6-8: flags for editable cheats, see arpro.h

 bit#9:

 1 = the cheat becomes active every 5s (conversion of mame type 04)
     This cheat type is not supposed to be editable because the field old_value is used
     for the time counter

*/

#include <string.h>
#include "gameinc.h"
#include "arpro.h"
#include "profile.h"
#include "conf-cpu.h"
#ifdef HAVE_6502
#include "m6502hlp.h"
#endif

/*

SEARCH METHODS
--------------

   SEARCH_MODE_ABSOLUTE - Searches for absolute byte values
                    new - first value (non matching data removed)
               continue - subsequent values (non matching data removed)

   SEARCH_MODE_RELATIVE - Searches for differences between all bytes at the start
                    new - no data (all data assumed matching)
               continue - subsequent values (non matching data removed)

 SEARCH_MODE_SINGLE_BIT - Searches for a single bit value
                    new - no data (all data assumed matching)
               continue - non zero if the bit has flipped (non matching data removed)

       SEARCH_MODE_SLOW - Searches for greater, less or unchanged values
                    new - no data (all data assumed matching)
               continue - 0=equal 1=not equal 2=less 3=less/equal
                          4=greater 5=greater/equal (non matching data removed)

*/

#define MAX_RAM_BLOCKS	4	// Max number of memory blocks to search

typedef struct SEARCH_RANGE
{
   UINT32 start;						// start address
   UINT32 end;						// end address
   UINT32 size;						// size
   UINT8 *match;					// buffer for matching
   UINT8 *match_2;					// buffer 2 for matching in some modes
   UINT32 match_count;					// number of matches
} SEARCH_RANGE;

static struct SEARCH_RANGE search_list[MAX_RAM_BLOCKS];	// List of addresses to search
static UINT32 search_list_count = 0;			// Entries in search_list
UINT32 search_mode;
int CheatCount;			// Number of Cheats in List
struct CHEAT CheatList[CHEAT_MAX]; // List of Current Game cheats
int match_all_count;		// total of all match_count

void start_arpro_search(UINT8 data)
{
  UINT32 ta,tb;

  if( (!search_list_count) && (current_game) ){

    // Autodetect RAM[] (assume writeword[0] is the main cpu work ram)
    // ---------------------------------------------------------------

#if HAVE_68000
    if(StarScreamEngine>=1){
      search_list[0].start = M68000_dataregion_ww[0][0].lowaddr;
      search_list[0].end   = M68000_dataregion_ww[0][0].highaddr;
      ta = (search_list[0].end - search_list[0].start) + 1;
      if((ta>0x10)&&(search_list[0].end > search_list[0].start)){ 					// Make sure buffer length is valid
	search_list[0].match   = malloc(ta);
	search_list[0].match_2 = malloc(ta);
	if((search_list[0].match)&&(search_list[0].match_2)){ // Make sure memory is allocated
	  search_list_count++;
	}
      }
    }
    else
#endif
    {
#if HAVE_Z80
      if(MZ80Engine>=1){				// Guess it's a z80 game
	int cpu = 1;
	if (Z80_memory_wb[0][0].lowAddr != -1)
	  cpu = 0;

	ta=0;
	while((Z80_memory_wb[cpu][ta].lowAddr)!= -1){

	  if(!(Z80_memory_wb[cpu][ta].memoryCall)){

	    search_list[search_list_count].start = Z80_memory_wb[cpu][ta].lowAddr;
	    search_list[search_list_count].end   = Z80_memory_wb[cpu][ta].highAddr;
	    tb = (search_list[search_list_count].end - search_list[search_list_count].start) + 1;
	    if(tb>0){ 					// Make sure buffer length is valid
	      search_list[search_list_count].match   = malloc(tb);
	      search_list[search_list_count].match_2 = malloc(tb);
	      if((search_list[search_list_count].match)&&(search_list[search_list_count].match_2)){ // Make sure memory is allocated
		search_list_count++;
	      }
	    }

	  }

	  if (Z80_memory_wb[cpu][ta].lowAddr == 0 && Z80_memory_wb[cpu][ta].highAddr == 0xffff)
	    break; // -1, -1 should not be obligatory to end the list for arpro !!!
	  ta++;
	}

      }
      else
      {						// No z80 or 68000, probably an F3-68020 game
#endif
#if HAVE_68020
	search_list[0].start = 0x400000;
	search_list[0].end   = 0x41FFFF;
	ta = 0x20000;
	search_list[0].match   = malloc(ta);
	search_list[0].match_2 = malloc(ta);
	if((search_list[0].match)&&(search_list[0].match_2)){ // Make sure memory is allocated
	  search_list_count++;
	}
#endif
      }
    }
  }

  if(!(search_list_count)) return;

  // Reset match all data

  for(tb = 0; tb < search_list_count; tb++){
    ta = (search_list[tb].end - search_list[tb].start) + 1;
    memset(search_list[tb].match,  0x00,ta);
    memset(search_list[tb].match_2,0x00,ta);
    search_list[tb].match_count = 0;
    search_list[tb].size = ta;
  }
  match_all_count = 0;

  switch(search_mode){
    case SEARCH_MODE_ABSOLUTE:

      for(tb = 0; tb < search_list_count; tb++){
	for(ta = 0; ta < search_list[tb].size; ta++){
	  if(gen_cpu_read_byte(search_list[tb].start + ta)==data){
	    search_list[tb].match[ta] = 0xFF;
	    search_list[tb].match_count++;
	    match_all_count++;
	  }
	}
      }

      break;
    case SEARCH_MODE_RELATIVE:

      for(tb = 0; tb < search_list_count; tb++){
	for(ta = 0; ta < search_list[tb].size; ta++){
	  search_list[tb].match[ta] = 0xFF;
	  search_list[tb].match_2[ta] = gen_cpu_read_byte(search_list[tb].start + ta);
	  search_list[tb].match_count++;
	  match_all_count++;
	}
      }

      break;
    case SEARCH_MODE_SINGLE_BIT:

      for(tb = 0; tb < search_list_count; tb++){
	for(ta = 0; ta < search_list[tb].size; ta++){
	  search_list[tb].match[ta] = 0xFF;
	  search_list[tb].match_2[ta] = gen_cpu_read_byte(search_list[tb].start + ta);
	  search_list[tb].match_count++;
	  match_all_count++;
	}
      }

      break;
    case SEARCH_MODE_SLOW:

      for(tb = 0; tb < search_list_count; tb++){
	for(ta = 0; ta < search_list[tb].size; ta++){
	  search_list[tb].match[ta] = 0xFF;
	  search_list[tb].match_2[ta] = gen_cpu_read_byte(search_list[tb].start + ta);
	  search_list[tb].match_count++;
	  match_all_count++;
	}
      }

      break;
    default:
      match_all_count = 0;
      break;
  }

}

void continue_arpro_search(UINT8 data)
{
   UINT32 ta,tb;
	int tc,td,te,tf;

   switch(search_mode){
   case SEARCH_MODE_ABSOLUTE:

   for(tb = 0; tb < search_list_count; tb++){
   for(ta = 0; ta < search_list[tb].size; ta++){
      if(search_list[tb].match[ta]){
      if(gen_cpu_read_byte(search_list[tb].start + ta)!=data){
         search_list[tb].match[ta] = 0x00;
         search_list[tb].match_count--;
         match_all_count--;
      }
      }
   }
   }

   break;
   case SEARCH_MODE_RELATIVE:

   for(tb = 0; tb < search_list_count; tb++){
   for(ta = 0; ta < search_list[tb].size; ta++){
      if(search_list[tb].match[ta]){

      tc = search_list[tb].match_2[ta];
      td = gen_cpu_read_byte(search_list[tb].start + ta);

      if(((tc+data)&0xFF) != td){
         search_list[tb].match[ta] = 0x00;
         search_list[tb].match_count--;
         match_all_count--;
      }
      else{
         search_list[tb].match_2[ta] = td;	// Next search will be relative to current, not first
      }

      }
   }
   }

   break;
   case SEARCH_MODE_SINGLE_BIT:

   for(tb = 0; tb < search_list_count; tb++){
   for(ta = 0; ta < search_list[tb].size; ta++){
      for(te = 0; te < 8; te++){

      tf = 1<<te;

      if((search_list[tb].match[ta])&tf){

      tc = search_list[tb].match_2[ta];
      td = gen_cpu_read_byte(search_list[tb].start + ta);

      if(data){			// Fail on unchanged
         if((tc&tf)==(td&tf)){
            search_list[tb].match[ta] &= ~tf;
            if(!(search_list[tb].match[ta])){	// Byte is valid until all 8 bits are discounted
               search_list[tb].match_count--;
               match_all_count--;
            }
         }
         else{
            search_list[tb].match_2[ta] = td;	// Next search will be relative to current, not first
         }
      }
      else{			// Fail on changed
         if((tc&tf)!=(td&tf)){
            search_list[tb].match[ta] &= ~tf;
            if(!(search_list[tb].match[ta])){	// Byte is valid until all 8 bits are discounted
               search_list[tb].match_count--;
               match_all_count--;
            }
         }
         else{
            search_list[tb].match_2[ta] = td;	// Next search will be relative to current, not first
         }
      }

      }
      }
   }
   }

   break;
   case SEARCH_MODE_SLOW:

   for(tb = 0; tb < search_list_count; tb++){
   for(ta = 0; ta < search_list[tb].size; ta++){
      if(search_list[tb].match[ta]){

      tc = search_list[tb].match_2[ta];
      td = gen_cpu_read_byte(search_list[tb].start + ta);

      te = 0;

      switch(data){
      case 0x00:		// accept equal
      if(td == tc) te = 1;
      break;
      case 0x01:		// accept not equal
      if(td != tc) te = 1;
      break;
      case 0x02:		// accept less
      if(td <  tc) te = 1;
      break;
      case 0x03:		// accept less or equal
      if(td <= tc) te = 1;
      break;
      case 0x04:		// accept greater
      if(td >  tc) te = 1;
      break;
      case 0x05:		// accept greater or equal
      if(td >= tc) te = 1;
      break;
      }

      if(!(te)){
         search_list[tb].match[ta] = 0x00;
         search_list[tb].match_count--;
         match_all_count--;
      }
      else{
         search_list[tb].match_2[ta] = td;	// Next search will be relative to current, not first
      }

      }
   }
   }

   break;
   default:
   match_all_count = 0;
   break;
   }
}

/*

UINT32 get_search_range_start(UINT32 addr):

source: addr = 32bit cpu address

result: start address of the search range that the address lies inside
        0xFFFFFFFF otherwize (if the address is not in any search range)

   use: obtaining information about search area for hex view

*/

UINT32 get_search_range_start(UINT32 addr)
{
   UINT32 tb;

   for(tb = 0; tb < search_list_count; tb++){
      if((addr>=search_list[tb].start)&&(addr<=search_list[tb].end)) return search_list[tb].start;
   }
   return 0xFFFFFFFF;
}

/*

UINT32 get_search_range_end(UINT32 addr):

source: addr = 32bit cpu address

result: end address of the search range that the address lies inside
        0xFFFFFFFF otherwize (if the address is not in any search range)

   use: obtaining information about search area for hex view

*/

UINT32 get_search_range_end(UINT32 addr)
{
   UINT32 tb;

   for(tb = 0; tb < search_list_count; tb++){
      if((addr>=search_list[tb].start)&&(addr<=search_list[tb].end)) return search_list[tb].end;
   }
   return 0xFFFFFFFF;
}

/*

UINT8 get_address_status(UINT32 addr):

source: addr = 32bit cpu address

result: non-zero if the byte at addr is matched in the search results
        zero otherwize (if the byte is not matched)

   use: obtaining information about search area for hex view

*/

UINT8 get_address_status(UINT32 addr)
{
   UINT32 tb;

   for(tb = 0; tb < search_list_count; tb++){
      if((addr>=search_list[tb].start)&&(addr<=search_list[tb].end))
         return search_list[tb].match[addr-search_list[tb].start];
   }
   return 0x00;
}

static UINT32 *results = NULL;

void reset_arpro(void)
{
   UINT32 tb;

   for(tb = 0; tb < search_list_count; tb++){
      if(search_list[tb].match) free(search_list[tb].match);
      if(search_list[tb].match_2) free(search_list[tb].match_2);
   }

   CheatCount = 0;
   search_list_count = 0;

   if(results) free(results);
   results = NULL;

   match_all_count = 0;

   search_mode = SEARCH_MODE_ABSOLUTE;
}

UINT32 *get_arpro_results(int num)
{
   UINT32 ta,tb;
	int tc;

   if(results) free(results);
   results = NULL;

   if(match_all_count==0) return NULL;

   if(match_all_count<num) num=match_all_count;

   results = (UINT32 *)malloc(num*4);

   if(results){

   tc=0;
   for(tb = 0; tb < search_list_count; tb++){
   for(ta = 0; ta < search_list[tb].size; ta++){
      if(search_list[tb].match[ta]){
         results[tc] = search_list[tb].start + ta;
         tc++;
         if(tc>=num) return results;
      }
   }
   }

   }

   return results;
}

/**************************************************************/

void load_arpro_cheats(const char *mysection)
{
   UINT32 ta,tb;
   char A[32];

   char CheatLine[550];	/* Enough for 256+256+9+9+9+3+2 */
   char * ptr;		/* To parse the cheat line */
   int  ErrorFlag;	/* To avoid having invalid lines */
   char section[20];
   if (CheatCount)
     return;
   strcpy(section,raine_get_config_string(mysection,"clone",""));
   if (!section[0]) // no it's not a clone...
     strcpy(section,mysection);

   for(ta=0;ta<CHEAT_MAX;ta++)
   {

      sprintf(A,"Cheat%02d",ta);
      sprintf(CheatLine,"%s",raine_get_config_string(section,A,"<none>"));	/* load the line from the file */

      if(stricmp(CheatLine,"<none>"))
	{

		CheatLine[549] = 0;
		ErrorFlag = 0;

		if (!ErrorFlag)
		{
			ptr = strtok(CheatLine, ":");						/* Address */
			if (!ptr)
			{
				ErrorFlag = 1;
			}
			else
			{
				sscanf(ptr, "%X", &tb);
				CheatList[CheatCount].address = tb;
			}
		}


		if (!ErrorFlag)
		{
			ptr = strtok(NULL, ":");						/* Data */
			if (!ptr)
			{
				ErrorFlag = 1;
			}
			else
			{
				sscanf(ptr, "%X", &tb);
				CheatList[CheatCount].data = tb;
			}
		}

		if (!ErrorFlag)
		{
			ptr = strtok(NULL, ":");						/* Mask */
			if (!ptr)
			{
				ErrorFlag = 1;
			}
			else
			{
				sscanf(ptr, "%X", &tb);
				CheatList[CheatCount].mask = tb;
			}
		}

		if (!ErrorFlag)
		{
			ptr = strtok(NULL, ":");						/* Type */
			if (!ptr)
			{
				ErrorFlag = 1;
			}
			else
			{
				sscanf(ptr, "%X", &tb);
				CheatList[CheatCount].type = tb;
			}
		}

		if (!ErrorFlag)
		{
			ptr = strtok(NULL, ":");						/* Name */
			if (!ptr)
			{
				ErrorFlag = 1;
			}
			else
			{
				strcpy(CheatList[CheatCount].name, ptr);
			}
		}

		if (!ErrorFlag)
		{
			ptr = strtok(NULL, ":");						/* Info */
			if (!ptr)
			{
				ErrorFlag = 0;							/* no error here as it's an optional field ! */
		            CheatList[CheatCount].info[0] = 0;
			}
			else
			{
				strcpy(CheatList[CheatCount].info, ptr);
			}
		}


		if (!ErrorFlag)
		{
			CheatList[CheatCount].active = CheatList[CheatCount].old_value = 0;
			CheatCount++;
			if (CheatCount >= CHEAT_MAX) {
			  printf("cheats overflow\n");
			  exit(1);
			}
		}
	}
   }
}

void save_arpro_cheats(const char *section)
{
   int ta;
   char A[128];

   char CheatLine[550];	/* Enough for 256+256+9+9+9+3+2 */
   char buf[257];		/* Enough for the string fields ('name' and 'info') */

   // remove all old cheats or cheat delete will not work

   raine_clear_config_section(section);

   // now rewrite the whole cheat section

   for(ta=0;ta<CheatCount;ta++)
   {

	CheatLine[0] = 0;

      sprintf(buf,"%X",CheatList[ta].address);						/* Address */
	strcat(CheatLine,buf);

      switch(CheatList[ta].type & 0x03)							/* Data */
	{
      case CHEAT_8BIT:
		sprintf(buf,":%02X",CheatList[ta].data);
	      break;
      case CHEAT_16BIT:
		sprintf(buf,":%04X",CheatList[ta].data);
	      break;
      case CHEAT_24BIT:
		sprintf(buf,":%06X",CheatList[ta].data);
	      break;
      case CHEAT_32BIT:
		sprintf(buf,":%08X",CheatList[ta].data);
	      break;
	default:	/* To avoid having invalid lines */
		sprintf(buf,":%X",CheatList[ta].data);
	      break;
	}
	strcat(CheatLine,buf);

      switch(CheatList[ta].type & 0x03)							/* Mask */
	{
      case CHEAT_8BIT:
		sprintf(buf,":%02X",CheatList[ta].type & CHEAT_MASKED ? CheatList[ta].mask : 0);
	      break;
      case CHEAT_16BIT:
		sprintf(buf,":%04X",CheatList[ta].type & CHEAT_MASKED ? CheatList[ta].mask : 0);
	      break;
      case CHEAT_24BIT:
		sprintf(buf,":%06X",CheatList[ta].type & CHEAT_MASKED ? CheatList[ta].mask : 0);
	      break;
      case CHEAT_32BIT:
		sprintf(buf,":%08X",CheatList[ta].type & CHEAT_MASKED ? CheatList[ta].mask : 0);
	      break;
	default:	/* To avoid having invalid lines */
		sprintf(buf,":%X",CheatList[ta].type & CHEAT_MASKED ? CheatList[ta].mask : 0);
	      break;
	}
	strcat(CheatLine,buf);

      sprintf(buf,":%02X",CheatList[ta].type);						/* Type */
	strcat(CheatLine,buf);

     	sprintf(buf,":%s",CheatList[ta].name);						/* Name */
	strcat(CheatLine,buf);

      if(CheatList[ta].info[0])								/* Info */
	{
      	sprintf(buf,":%s",CheatList[ta].info);
		strcat(CheatLine,buf);
	}

      sprintf(A,"Cheat%02d",ta);
      raine_set_config_string(section, A, CheatLine);					/* save the line to the file */
   }
}

/**************************************************************/

UINT8 gen_cpu_read_byte(UINT32 address)
{
#ifndef NO020
  if (MC68020) {
    if (!R24[address>>16]) return 0;
    return R24[address>>16][address&0xFFFF];
  }
#endif
#if HAVE_68000
   if(StarScreamEngine>=1){
      return ReadStarScreamByte(address);
   }
#endif
#if HAVE_Z80
   if(MZ80Engine>=1)		// Guess it's a z80 game
     return ReadMZ80Byte(address);
#endif
#ifdef HAVE_6502
   if (M6502Engine>=1)
     return M6502ReadByte(address);
#endif
  return 0; // stupid warning
}

void gen_cpu_write_byte(UINT32 address, UINT8 data)
{
#ifndef NO020
  if (MC68020) { // 68020 is ALWAYS the main cpu !
    if (!R24[address>>16]) return;
    R24[address>>16][address&0xFFFF] = data;
  } else
#endif
    if(
#ifdef HAVE_68000
      StarScreamEngine
#else
      0
#endif
#ifndef NO020
	  && !MC68020
#endif
	  ){
#ifdef HAVE_68000
    WriteStarScreamByte(address,data);
#endif
  }
#ifdef HAVE_Z80
  else if(MZ80Engine>=1)		// Guess it's a z80 game
    WriteMZ80Byte(address,data);
#endif
#ifdef HAVE_6502
  else if (M6502Engine >= 1)
    M6502WriteByte(address,data);
#endif
}

/******************************************************************************/
/*                                                                            */
/*                   APPLY CHEAT EFFECTS (called every frame)                 */
/*                                                                            */
/******************************************************************************/
// Return the value pointed by a cheat, for types editable and watchpoint
// the return value is in hex in string form (param text)
void get_cheat_hex_value(int ta, char *text) {
   UINT32 type,addr;

   type = CheatList[ta].type;
   addr = CheatList[ta].address;
   switch (type & 3) { // size
   case CHEAT_8BIT:
     sprintf(text,"%02x",gen_cpu_read_byte(addr));
     break;
   case CHEAT_16BIT:
     sprintf(text,"%02x",gen_cpu_read_byte(addr));
     sprintf(&text[2],"%02x",gen_cpu_read_byte(addr+1));
     break;
   case CHEAT_24BIT:
     sprintf(text,"%02x",gen_cpu_read_byte(addr));
     sprintf(&text[2],"%02x",gen_cpu_read_byte(addr+1));
     sprintf(&text[4],"%02x",gen_cpu_read_byte(addr+2));
     break;
   case CHEAT_32BIT:
     sprintf(text,"%02x",gen_cpu_read_byte(addr));
     sprintf(&text[2],"%02x",gen_cpu_read_byte(addr+1));
     sprintf(&text[4],"%02x",gen_cpu_read_byte(addr+2));
     sprintf(&text[6],"%02x",gen_cpu_read_byte(addr+3));
     break;
   }
}

void update_arpro_cheats(void)
{
   UINT32 type,addr,data,mask,source;
   int ta;

   ta = CheatCount;

   while((--ta)>=0){
      if(CheatList[ta].active){

         type = CheatList[ta].type;
         addr = CheatList[ta].address;
         data = CheatList[ta].data;
         mask = CheatList[ta].mask;

	 if (type & CHEAT_EVERY_5S) {
	   if (CheatList[ta].old_value) {
	     CheatList[ta].old_value--;
	     continue;
	   }
	 }

	 if(type & CHEAT_WATCH) {
	   int x = ReadWord(&data);
	   int y = ReadWord(((UINT8*)&data)+2);
	   char text[256];

	   get_cheat_hex_value(ta,text);
	   snprintf(text,256,"%s %s",text,CheatList[ta].info);
	   textout_fast(text,x+current_game->video->border_size,
			y+current_game->video->border_size,
			get_white_pen());
	 } else
	   if(!(type & CHEAT_MASKED)){

	     if (type & CHEAT_EDITABLE) {
	       if (type & CHEAT_EDIT_ONCHANGE) {
		 char text[10];
		 int val;
		 get_cheat_hex_value(ta,text);
		 sscanf(text,"%x",&val);
		 if (val == CheatList[ta].old_value)
		   continue;
	       }
	       data = CheatList[ta].edit_value;
	     }
	     switch(type & 0x03){
	     case CHEAT_8BIT:
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_16BIT:
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_24BIT:
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >>16)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+2, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_32BIT:
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >>24)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >>16)&0xFF));
	       gen_cpu_write_byte(addr+2, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+3, (UINT8) ((data >> 0)&0xFF));
	       break;
	     }
	   }
	   else{
	     switch(type & 0x03){
	     case CHEAT_8BIT:
	       source  =  gen_cpu_read_byte(addr+0)<<0;
	       data   &=  mask;
	       source &= ~mask;
	       data   |=  source;
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_16BIT:
	       source  =  gen_cpu_read_byte(addr+0)<<8;
	       source |=  gen_cpu_read_byte(addr+1)<<0;
	       data   &=  mask;
	       source &= ~mask;
	       data   |=  source;
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_24BIT:
	       source  =  gen_cpu_read_byte(addr+0)<<16;
	       source |=  gen_cpu_read_byte(addr+1)<<8;
	       source |=  gen_cpu_read_byte(addr+2)<<0;
	       data   &=  mask;
	       source &= ~mask;
	       data   |=  source;
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >>16)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+2, (UINT8) ((data >> 0)&0xFF));
	       break;
	     case CHEAT_32BIT:
	       source  =  gen_cpu_read_byte(addr+0)<<24;
	       source |=  gen_cpu_read_byte(addr+1)<<16;
	       source |=  gen_cpu_read_byte(addr+2)<<8;
	       source |=  gen_cpu_read_byte(addr+3)<<0;
	       data   &=  mask;
	       source &= ~mask;
	       data   |=  source;
	       gen_cpu_write_byte(addr+0, (UINT8) ((data >>24)&0xFF));
	       gen_cpu_write_byte(addr+1, (UINT8) ((data >>16)&0xFF));
	       gen_cpu_write_byte(addr+2, (UINT8) ((data >> 8)&0xFF));
	       gen_cpu_write_byte(addr+3, (UINT8) ((data >> 0)&0xFF));
	       break;
	     }

	   }

         if(type & CHEAT_1_TIME)
	   CheatList[ta].active = 0;

	 if (type & CHEAT_EVERY_5S)
	   CheatList[ta].old_value = 5*fps;
      }
   }
}

char *get_search_mode_name(UINT32 mode)
{
   static char *search_mode_name[SEARCH_MODE_COUNT] =
   {
      "Absolute Search",
      "Relative Search",
      "Single Bit Search",
      "Slow Deep Search",
   };

   return search_mode_name[mode];
}

