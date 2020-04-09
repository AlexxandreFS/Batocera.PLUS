/******************************************************************************/
/*                                                                            */
/*                         RAINE DOUBLE SIZE BLITTING                         */
/*                                                                            */
/******************************************************************************/

#include "raine.h"

void raine_blit_x2_y1_16(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
	int x, y;
	int new_x;

	acquire_bitmap(dest);
	for( y = 0; y < h ; y++ )
	{
		for( x = 0, new_x = 0; x < w; x++, new_x+=4 )
		{
			dest->line[ y + d_y ][ new_x + d_x   ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ y + d_y ][ new_x + d_x+1 ] = src->line[ y + s_y ][ x + s_x+1 ];
			dest->line[ y + d_y ][ new_x + d_x+2 ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ y + d_y ][ new_x + d_x+3 ] = src->line[ y + s_y ][ x + s_x+1 ];
		}
	}
	release_bitmap(dest);
}

void raine_blit_x2_y2_16(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
	int x, y;
	int new_x, new_y;

	acquire_bitmap(dest);
	for( y = 0, new_y = 0; y < h ; y++, new_y+=2 )
	{
		for( x = 0, new_x = 1; x < w; x++, new_x+=4 )
		{
			dest->line[ new_y + d_y   ][ new_x + d_x   ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ new_y + d_y   ][ new_x + d_x+1 ] = src->line[ y + s_y ][ x + s_x+1 ];
			dest->line[ new_y + d_y   ][ new_x + d_x+2 ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ new_y + d_y   ][ new_x + d_x+3 ] = src->line[ y + s_y ][ x + s_x+1 ];

			dest->line[ new_y + d_y+1 ][ new_x + d_x   ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ new_y + d_y+1 ][ new_x + d_x+1 ] = src->line[ y + s_y ][ x + s_x+1 ];
			dest->line[ new_y + d_y+1 ][ new_x + d_x+2 ] = src->line[ y + s_y ][ x + s_x   ];
			dest->line[ new_y + d_y+1 ][ new_x + d_x+3 ] = src->line[ y + s_y ][ x + s_x+1 ];
		}
	}
	release_bitmap(dest);
}
