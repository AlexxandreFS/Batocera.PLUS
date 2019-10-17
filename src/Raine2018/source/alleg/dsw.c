/******************************************************************************/
/*                                                                            */
/*                              DIPSWITCH SUPPORT                             */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "games.h"
#include "dsw.h"
#include "control.h"
#include "arpro.h"
#include "starhelp.h"
#ifdef HAVE_6502
#include "6502/m6502hlp.h"
#endif
#include "gui/rgui.h"

#define MAX_DIPSWITCHES		10

int override_region = -10; // 0 is 1st region, -1 displays values, so -10 here

typedef struct DSW
{
   char *DSWName;		// Switch or setting name
   UINT8 bits;			// Switch bitmask or setting bitpattern
   UINT8 values;		// Number of settings defined for this switch
} DSW;

typedef struct DSTAT
{
   UINT8 pos;			//
   UINT8 offset;		//
} DSTAT;

typedef struct DIPSW
{
   UINT8 value;			// Current value
   UINT8 def;			// Default value (factory setting)
   UINT32 count;			// Items in diplist
   UINT32 address;		// RAM[] address to place dsw
   DSW   diplist[64];
   UINT32 statcount;		// Items in statlist
   DSTAT statlist[16];
} DIPSW;


// Fill stat list from DSW bytes

void make_dipswitch_statlist(void);
struct DIPSW dipswitch[MAX_DIPSWITCHES];
struct ROMSW LanguageSw;	// ROMSwitch for Language Selection (Taito roms)

void write_dsw(int index)
{
  UINT32 address = dipswitch[index].address, data = dipswitch[index].value;
   if(address < 0x100)

      input_buffer[address] = data;

   else

      RAM[address] = data;
}

void make_dipswitch_bytes(void)
{
   UINT32 ta,tb,tc,i;

   for(i=0;i<MAX_DIPSWITCHES; i++){

   if(dipswitch[i].count){

      for(ta=0;ta<dipswitch[i].statcount;ta++){
         tb = dipswitch[i].statlist[ta].pos;
         tc = dipswitch[i].statlist[ta].pos + dipswitch[i].statlist[ta].offset + 1;
         tb = dipswitch[i].diplist[tb].bits;
         tc = dipswitch[i].diplist[tc].bits;
         dipswitch[i].value &= ~tb;			// Clear bits
         dipswitch[i].value |= (tc & tb);		// Set bits
      }
      write_dsw(i);
      print_debug("DSW %d: %02x\n",i,dipswitch[i].value);

   }

   }

   make_dipswitch_statlist();
}

void make_dipswitch_statlist(void)
{
   UINT32 ta,tb,tc,td,te,i;

   for(i=0;i<MAX_DIPSWITCHES;i++){

      if(dipswitch[i].count){
         for(ta=0;ta<dipswitch[i].statcount;ta++){
            tb = dipswitch[i].statlist[ta].pos;
            tc = dipswitch[i].diplist[tb].bits;
            td = dipswitch[i].value & tc;

            for(te=0;te<dipswitch[i].diplist[tb].values;te++){
               tc = dipswitch[i].diplist[tb+te+1].bits;
               if(td==tc){
                  dipswitch[i].statlist[ta].offset = te;
               }
            }
         }
         write_dsw(i);
      }

   }

}

// RestoreDSWDefault():
// Restores DSW to the factory settings
// Does not modify DSW info lists, call make_dipswitch_statlist
// to update them...

void RestoreDSWDefault(void)
{
   int i;

   for(i=0;i<MAX_DIPSWITCHES;i++)
      dipswitch[i].value = dipswitch[i].def;
}

void init_dsw(void)
{
   const DSW_INFO *dsw_src;
   DSW_DATA *dsw_data;
   int ta,tb,tc;

   for(ta = 0; ta < MAX_DIPSWITCHES; ta++){

      dipswitch[ta].address   = 0;
      dipswitch[ta].count     = 0;
      dipswitch[ta].statcount = 0;

   }

   dsw_src = current_game->dsw;

   if(dsw_src){

   ta=0;

   while(dsw_src[ta].data){

   dsw_data = dsw_src[ta].data;

   dipswitch[ta].def       = dsw_src[ta].factory_setting;
   dipswitch[ta].value     = dsw_src[ta].factory_setting;
   dipswitch[ta].address   = dsw_src[ta].offset;

   tb = 0;
   tc = 0;

   while(dsw_data[tb].name){

      dipswitch[ta].diplist[tb].DSWName = dsw_data[tb].name;
      dipswitch[ta].diplist[tb].bits    = dsw_data[tb].bit_mask;
      dipswitch[ta].diplist[tb].values  = dsw_data[tb].count;

      if(dsw_data[tb].count){
         dipswitch[ta].statlist[tc].pos    = tb;
         dipswitch[ta].statlist[tc].offset = 0;
         tc++;
      }

      tb++;

   }

   dipswitch[ta].count     = tb;
   dipswitch[ta].statcount = tc;

   ta++;

   }

   }
}

struct DSW_DATA dsw_data_default_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { NULL,                    0,    0,   },
};

struct DSW_DATA dsw_data_default_1[] =
{
   { MSG_DSWB_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWB_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { NULL,                    0,    0,   },
};

struct DSW_DATA dsw_data_default_2[] =
{
   { MSG_DSWC_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { MSG_DSWC_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80, 0x00 },
   { MSG_ON,                  0x00, 0x00 },
   { NULL,                    0,    0,   },
};


UINT8 get_dsw(int i)
{
   return dipswitch[i].value;
}

static char *save_name[MAX_DIPSWITCHES] =
{
  "dswa", "dswb", "dswc", "dswd", "dswe", "dswf", "dswg", "dswh", "dswi",
  "dswj"
};

void load_dipswitches(char *section)
{
   int i;

   for(i = 0; i < MAX_DIPSWITCHES; i++)
      if(dipswitch[i].count)
         dipswitch[i].value = raine_get_config_hex(section, save_name[i], dipswitch[i].value);

   make_dipswitch_statlist();
}

void save_dipswitches(char *section)
{
   int i;

   for(i = 0; i < MAX_DIPSWITCHES; i++)
      if(dipswitch[i].count)
         raine_set_config_hex(section, save_name[i], dipswitch[i].value);
}

/******************************************************************************/
/*                                                                            */
/*         ROM SWITCH SUPPORT (consider them unofficial dip switches)         */
/*                                                                            */
/******************************************************************************/

/*

todo:

- multiple romswitch support : required for sfzch
   you are allowed to specify multiple offsets in the ROMSW_INFO struct
   but this address will get the same data from the ROMSW_DATA struct.
- multiple byte patchin support (also not required)
- remove array limit on number of rom switch states (better code)

*/

extern UINT8 read_z80_from_rom(UINT32 address);
extern void write_z80_to_rom(UINT32 address, UINT8 data);

static void gen_cpu_write_byte_rom(UINT32 address, UINT8 data)
{
#ifndef NO020
  if (MC68020) { // 68020 is ALWAYS the main cpu !
    if (!R24[address>>16]) return;
    R24[address>>16][address&0xFFFF] = data;
  } else
#endif
  if(StarScreamEngine>=1
#ifndef NO020
	  && !MC68020
#endif
	  ){
    WriteStarScreamByte(address,data);
  }
  else if(MZ80Engine>=1)		// Guess it's a z80 game
    write_z80_to_rom(address,data);
#ifdef HAVE_6502
  else if (M6502Engine >= 1)
    M6502WriteByte(address,data);
#endif
}

static UINT8 gen_cpu_read_byte_rom(UINT32 address)
{
#ifndef NO020
  if (MC68020) {
    if (!R24[address>>16]) return 0;
    return R24[address>>16][address&0xFFFF];
  }
  else
#endif
   if(StarScreamEngine>=1){
      return ReadStarScreamByte(address);
   }
   else if(MZ80Engine>=1)		// Guess it's a z80 game
     return read_z80_from_rom(address);
#ifdef HAVE_6502
   else if (M6502Engine>=1)
     return M6502ReadByte(address);
#endif
  return 0; // stupid warning
}

void init_romsw(void)
{
  const ROMSW_INFO *romsw_src;
  ROMSW_DATA *romsw_data;
  int ta,tb;

  LanguageSw.Address = 0;
  LanguageSw.Count   = 0;

  ta=0;

  romsw_src = current_game->romsw;

  if(romsw_src){

    while(romsw_src[ta].data){

      romsw_data = romsw_src[ta].data;

      LanguageSw.Address      = romsw_src[ta].offset;
      LanguageSw.def          = romsw_src[ta].factory_setting;

      tb = 0;

      while(romsw_data[tb].name){

	LanguageSw.Mode[tb] = romsw_data[tb].name;
	LanguageSw.Data[tb] = romsw_data[tb].data;
	tb++;

      }

      LanguageSw.Count    = tb;
      gen_cpu_write_byte_rom(LanguageSw.Address,LanguageSw.def);

      ta++;

    }
  }
}

void SetupLanguageSwitch(UINT32 addr)
{
   LanguageSw.Address=addr;
   LanguageSw.Count=0;
}

void AddLanguageSwitch(UINT8 ldata, char *lname)
{
   LanguageSw.Mode[LanguageSw.Count]=lname;
   LanguageSw.Data[LanguageSw.Count]=ldata;
   LanguageSw.Count++;
}

void (*write_region_byte)(int data);
int (*read_region_byte)();

void SetLanguageSwitch(int number)
{
  const ROMSW_INFO *romsw_src;
  int ta;

  romsw_src = current_game->romsw;
  ta = 0;
  if (number < 0 || number >= LanguageSw.Count) {
      char buf[1024];
      sprintf(buf,"Region out of bounds (%d). Possible values :\n",number);
      int n;
      for (n=0; n<LanguageSw.Count; n++)
	  sprintf(&buf[strlen(buf)],"%d: %s\n",n,LanguageSw.Mode[n]);
      MessageBox("Warning",buf,"Ok");
      return;
  }

  if(romsw_src){

      if (write_region_byte)
	  (*write_region_byte)(LanguageSw.Data[number]);
      else {
	  while(romsw_src[ta].data){

	      LanguageSw.Address      = romsw_src[ta++].offset;
	      gen_cpu_write_byte_rom(LanguageSw.Address,LanguageSw.Data[number]);
	  }
      }
  }
  make_dipswitch_statlist();
}

int GetLanguageSwitch(void)
{
   int ta,tb;

   if(LanguageSw.Address){

       if (read_region_byte)
	   tb = (*read_region_byte)();
       else
	   tb = gen_cpu_read_byte_rom(LanguageSw.Address);

      for(ta=0;ta<LanguageSw.Count;ta++){
          if(LanguageSw.Data[ta]==tb)
             return ta;
      }

   }
   return 0;
}

void load_romswitches(char *section)
{
   if(LanguageSw.Address)
      SetLanguageSwitch( raine_get_config_hex(section,"Version",GetLanguageSwitch()) );
}

void save_romswitches(char *section)
{
   if(LanguageSw.Address)
      raine_set_config_hex(section,"Version",GetLanguageSwitch());
}

/******************************************************************************/
/*                                                                            */
/*                ROM PATCHING SUPPORT (something like an .ips)               */
/*                                                                            */
/******************************************************************************/

void patch_rom(UINT8 *src, ROM_PATCH *patch)
{
   int ta;

   ta = 0;

   while(patch[ta].offset != -1){

      WriteLong68k(&src[patch[ta].offset + 0], patch[ta].data_0);
      WriteLong68k(&src[patch[ta].offset + 4], patch[ta].data_1);

      ta++;
   };

}

/******************************************************************************/

