/******************************************************************************/
/*                                                                            */
/*                               RAINE GAME LISTS                             */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "games.h"
#include "neocd/neocd.h"

struct GAME_MAIN *current_game;
int game_count;

char *game_type[NB_GAME_TYPE] =
{ "All",
  "Breakout",
  "Shoot'em up",
  "Beat'em up",
  "Puzzle",
  "Platform",
  "Misc",
  "Sport",
  "Adult",
  "Race",
  "Quizz",
  "Maze",
  "Fight",
};

char *company_name[] =
{
   "Unknown",
   "Bootleg",
   "Capcom",
   "Data East",
   "Irem",
   "Jaleco",
   "Konami",
   "Nichibutsu",
   "Sega",
   "SNK",
   "Taito",
   "Tecmo",
   "Toaplan",
   "Banpresto",
   "UPL",
   "Namco",
   "NTC",
   "Visco",
   "Face",
   "Seibu",
   "Sammy",
   "Video System",
   "Alpha Denshi",
   "Nazca",
   "Technos",
   "NMK",
   "Sunsoft",
   "Aicom",
   "Yumekobo",
   "Hudson Soft",
   "Tad",
   "Comad",
   "Seta",
   "Excellent System",
   "Kaneko",
   "Raizing",
   "Cave",
   "Zeus",
   "Gaelco",
   "Psikyo",
   "East Technology",
   "Williams",
   "Hot-B",
   "Marble",
   "Wintechno",
   "Allumer",
   "Athena",
   "Yang Cheng",
   "Midway",
   "Nintendo",
   "Mitchell",
   "SemiCom",
   "ESD",
   "Spacy Industrial, Ltd.",
   "Electronic Devices",
   "NIX",
   "ADK",
   "Hack",
   "Takumi",
   "Viccom",
   "Eighting",
   "Saurus",
   "Eleven / Gavaking",
   "Noise Factory",
   "Eolith / SNK",
   "Mega / Playmore",
   "Evoga / Playmore",
   "Eolith / Playmore",
   "Noise Factory / Atlus",
   "Aiky / Taito",
   "SNK / Playmore",
   "Kyle Hodgetts",
   "F2 System",
};

const int nb_companies = sizeof(company_name)/4;

#include "driver.c"

void init_game_list(void)
{
   GAME_MAIN *swap;
   int i,j;

   /*

   count the games

   */

   game_count = sizeof(game_list) / sizeof(GAME_MAIN *);

   /*

   sort game_list by long_name (bubble sort)

   */

   for(i = game_count-1; i > 0; i --){

      for(j = 1; j <= i; j ++){

         if( stricmp(game_list[j-1]->long_name, game_list[j]->long_name) > 0){

            swap           = game_list[j-1];
            game_list[j-1] = game_list[j];
            game_list[j]   = swap;

         }

      }

   }

   /*

   no game is loaded

   */

   current_game = NULL;

}

char *game_company_name(UINT8 company_id)
{
   return company_name[company_id];
}

int is_current_game(char *main_name)
{
    if (!current_game) return 0;
   return (!stricmp(current_game->main_name, main_name));
}

int is_neocd()
{
    if (!current_game) return 0;
    // A way to recognize a neocd game : no roms !
    // There shouldn't ever be any other driver without roms !
    return current_game->rom_list == NULL;
}

/*

Return the name of the parent if current game is a clone
else return current game name

*/

const char *parent_name() {
  char *dir;
  const DIR_INFO* dlist = current_game->dir_list;
  if (!dlist) return current_game->main_name;
  while (dlist->maindir) {
    dir = dlist->maindir;
    if( IS_ROMOF(dir) ){

      GAME_MAIN *game_romof;

      game_romof = find_game(dir+1);
      if (game_romof)
	return game_romof->main_name;
    }
    dlist++;
  }
  return current_game->main_name;
}

int is_clone(struct GAME_MAIN *current_game) {
  const DIR_INFO* dlist = current_game->dir_list;
  char *dir;
  while (dlist->maindir) {
    dir = dlist->maindir;
    if( IS_ROMOF(dir) || IS_CLONEOF(dir)){
	return 1;
    }
    dlist++;
  }
  return 0;
}

int game_exists(GAME_MAIN **my_game_list,int num)
{
   const DIR_INFO *dir_list;
   char str[256];
   UINT32 ta;

   dir_list = my_game_list[num]->dir_list;

   while( (dir_list->maindir) ){

      if((dir_list->maindir[0] != '#')&&(dir_list->maindir[0] != '$')){

	 for(ta = 0; dir_cfg.rom_dir[ta]; ta ++){

	    if(dir_cfg.rom_dir[ta][0]){

	       sprintf(str,"%s%s.zip", dir_cfg.rom_dir[ta], dir_list->maindir);
	       if((exists(str))) return 1;

	       sprintf(str,"%s%s.7z", dir_cfg.rom_dir[ta], dir_list->maindir);
	       if((exists(str))) return 1;

	       sprintf(str,"%s%s", dir_cfg.rom_dir[ta], dir_list->maindir);
	       if((exists(str))) return 1;

	    }

	 }

      }

      dir_list++;
   }

   return 0;

}

