/******************************************************************************/
/*                                                                            */
/*                          RAINE 8x8 TILE DRAWING                            */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "raine.h"
#include "video/palette.h"
#include "blit.h"

void init_str6x8asm_32(void)
{
}

void draw_string_6x8_32(char *STR, int x, int y, UINT32 cmap)
{
	int y_pos;
	int i = 0;
	UINT32 ch;
	UINT32 *line;

	while( STR[ i ] != 0 )
	{
		ch = STR[i++];
		if( ch <= 0x20 )
		{
			// Character is blank or unprintable, skip 6 pixels to accomidate
			x+= 6;
			continue;
		}

		// Get character into range, font table starts at character just after 0x20.
		ch -= 0x20;
		// Find character in table.  Table is arranged in such that 8 linear bytes
		// make up one character.  So need to multiply the index by 8 to find character.
		ch *= 8;
		for( y_pos = 0; y_pos < 8; y_pos++ )
		{
			line = ((UINT32 *)(GameBitmap->line[y_pos+y])) + x;
			if( ingame_font[ ch ] & 0x80 )
			{
				line[0] = cmap;
			}

			if( ingame_font[ ch ] & 0x40 )
			{
				line[1] = cmap;
			}

			if( ingame_font[ ch ] & 0x20 )
			{
				line[2] = cmap;
			}

			if( ingame_font[ ch ] & 0x10 )
			{
				line[3] = cmap;
			}

			if( ingame_font[ ch ] & 0x08 )
			{
				line[4] = cmap;
			}

			if( ingame_font[ ch ] & 0x04 )
			{
				line[5] = cmap;
			}
			ch++;
		}
		x+=6;
	}
}
