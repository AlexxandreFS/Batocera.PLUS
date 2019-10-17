/******************************************************************************/
/*                                                                            */
/*                         RAINE DOUBLE SIZE BLITTING                         */
/*                                                                            */
/******************************************************************************/

#include "raine.h"

void raine_blit_x2_y1(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
	int x, y;
	int new_x;
	int total_x = (w<<1);

	for( y = 0; y < h ; y++ )
	{
		for( x = 0, new_x = 0; x < total_x; x++, new_x+=2 )
		{
			dest->line[ y + d_y ][ new_x + d_x ] = src->line[ y + s_y ][ x + s_x ];
			dest->line[ y + d_y ][ new_x + d_x+1 ] = src->line[ y + s_y ][ x + s_x ];
		}
	}
}

void raine_blit_x2_y2(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
	int x, y;

	for( y = 0; y < h ; y++ )
	{
	  int dy = y*2 + d_y;
		for( x = 0; x < w; x++ )
		{
		  int new_x = d_x+x*2;
		  UINT8 sx = src->line[ y + s_y ][ x + s_x ];
			dest->line[ dy ][ new_x ] = sx;
			dest->line[ dy+1 ][ new_x ] = sx;

			dest->line[ dy ][ new_x+1 ] = sx;
			dest->line[ dy+1 ][ new_x+1 ] = sx;

		}
	}
}
