/* --------------------------------------------------
  Functions for setting 320x240 Arcade Monitor mode
 --------------------------------------------------*/

#include "arcmon.h"

/* indices into our register array */
#define	CLOCK_INDEX				0
#define	H_TOTAL_INDEX			1
#define	H_DISPLAY_INDEX			2
#define	H_BLANKING_START_INDEX	3
#define	H_BLANKING_END_INDEX	4
#define	H_RETRACE_START_INDEX	5
#define	H_RETRACE_END_INDEX		6
#define	V_TOTAL_INDEX			7
#define	OVERFLOW_INDEX			8
#define	MAXIMUM_SCANLINE_INDEX	10
#define	V_RETRACE_START_INDEX	11
#define	V_RETRACE_END_INDEX		12
#define	V_END_INDEX				13
#define	MEM_OFFSET_INDEX		14
#define	V_BLANKING_START_INDEX	16
#define	V_BLANKING_END_INDEX	17

//functions
//set the horizontal and vertical timings
void setarcadetimings(void);
//center the arcade monitor mode
void centerarcademode(void);

//asm function to set arcade monitor mode (in arcmode.s)
void setarcademode(void);

//timing values
unsigned char arcade_h_timing = 105;  // horizontal timing, range 0-255, default 105
unsigned char arcade_v_timing = 9;    // vertical timing,   range 0-255, default 9

//center values
unsigned char center_x = 8;           // center x, range 0 to 16, default 8
unsigned char center_y = 4;           // center y, range 0 to 8,  default 4

//array of register values to set arcade mode
unsigned char vgaregs320x240[]=
{
   0xe7,0x69,0x4f,0x4f,0x91,0x55,0x1f,0x09,0x11,0x00,0x40,0xf2,0xa4,0xef,0x28,0x00,0xf0,0xf2,0xe3,
   0x09,
   0x06,0x40,0x05,0x41,0x00
};

void arcade_monitor_mode(int h, int v, int x, int y)
{
#if !defined( RAINE_WIN32 )
   arcade_h_timing = h;
   arcade_v_timing = v;
   center_x = x;
   center_y = y;

//update array with 'tweak' horizontal and vertical counts
	setarcadetimings();
//update array with centering values
	centerarcademode();
//then set the registers
	setarcademode();
#endif
}

void setarcadetimings(void)
{
//just copy the values in
#if !defined( RAINE_WIN32 )
	vgaregs320x240[H_TOTAL_INDEX] = arcade_h_timing;
	vgaregs320x240[V_TOTAL_INDEX] = arcade_v_timing;
#endif
}

void centerarcademode(void)
{
#if !defined( RAINE_WIN32 )
	int hrt, vrt_start, temp, vert_total, vert_display, center, hrt_start;
	int vblnk_start,vrt,vblnk,actx,acty;
	int hblnk = 3;
//get +/- versions of the center vars
	actx =(int)center_x - 8;
	acty =(int)center_y - 4;

//horizontal retrace width
	hrt = 11;
/* our center 'tweak' variable */
	center = actx;
/* set the hz retrace */
	hrt_start = vgaregs320x240[H_RETRACE_START_INDEX];
	hrt_start += center;
/* make sure it's legal */
	if (hrt_start <= vgaregs320x240[H_DISPLAY_INDEX])
		hrt_start = vgaregs320x240[H_DISPLAY_INDEX] + 1;

	vgaregs320x240[H_RETRACE_START_INDEX] = hrt_start;
	temp = hrt_start + hrt;
	vgaregs320x240[H_RETRACE_END_INDEX] = temp&0x1f;

 /* set the hz blanking */
	temp = vgaregs320x240[H_DISPLAY_INDEX];
   	vgaregs320x240[H_BLANKING_START_INDEX] = temp;
   	temp += hblnk;
   	vgaregs320x240[H_BLANKING_END_INDEX] = (temp&0x1f) | 0x80;


/* get the vt retrace */
	vrt_start = vgaregs320x240[V_RETRACE_START_INDEX] | ((vgaregs320x240[OVERFLOW_INDEX] & 0x04) << 6) |
				((vgaregs320x240[OVERFLOW_INDEX] & 0x80) << 2);

/* get the width of it */
	temp = vrt_start & ~0x0f;
	temp |=	(vgaregs320x240[V_RETRACE_END_INDEX] & 0x0f);

	vrt = temp - vrt_start;


/* set the new retrace start */
	vrt_start += acty;
/* check it's legal, get the display line count */
	vert_display = (vgaregs320x240[V_END_INDEX] | ((vgaregs320x240[OVERFLOW_INDEX] & 0x02) << 7) |
				((vgaregs320x240[OVERFLOW_INDEX] & 0x40) << 3)) + 1;

 	if (vrt_start < vert_display)
		vrt_start = vert_display;

/* and get the vertical line count */
	vert_total = vgaregs320x240[V_TOTAL_INDEX] | ((vgaregs320x240[OVERFLOW_INDEX] & 0x01) << 8) |
				((vgaregs320x240[OVERFLOW_INDEX] & 0x20) << 4);



	vgaregs320x240[V_RETRACE_START_INDEX] = (vrt_start & 0xff);
	vgaregs320x240[OVERFLOW_INDEX] &= ~0x84;
	vgaregs320x240[OVERFLOW_INDEX] |= ((vrt_start & 0x100) >> 6);
	vgaregs320x240[OVERFLOW_INDEX] |= ((vrt_start & 0x200) >> 2);
	temp = vrt_start + vrt;


	if (temp > vert_total)
		temp = vert_total;


	vgaregs320x240[V_RETRACE_END_INDEX] &= ~0x0f;
	vgaregs320x240[V_RETRACE_END_INDEX] |= (temp & 0x0f);

/* get the start of vt blanking */
	vblnk_start = vgaregs320x240[V_BLANKING_START_INDEX] | ((vgaregs320x240[OVERFLOW_INDEX] & 0x08) << 5) |
					((vgaregs320x240[MAXIMUM_SCANLINE_INDEX] & 0x20) << 4);

/* and the end */
	temp = vblnk_start & ~0xff;
	temp |= vgaregs320x240[V_BLANKING_END_INDEX];

/* get the width */
	vblnk = temp - vblnk_start;
/* get the new value */
	vblnk_start += acty;
/* check it's legal */
	if (vblnk_start < vert_display)
		vblnk_start = vert_display;
	if (vblnk_start > vert_total)
		vblnk_start = vert_total;

/* set vblank start */
	vgaregs320x240[V_BLANKING_START_INDEX] = (vblnk_start & 0xff);
	vgaregs320x240[OVERFLOW_INDEX] &= ~0x08;
	vgaregs320x240[OVERFLOW_INDEX] |= ((vblnk_start & 0x100) >> 5);
	vgaregs320x240[MAXIMUM_SCANLINE_INDEX] &= ~0x20;
	vgaregs320x240[MAXIMUM_SCANLINE_INDEX] |= ((vblnk_start &0x200) >> 4);
/* set the vblank end */
	temp = vblnk_start + vblnk;
/* check it's legal */
	if (temp > vert_total)
		temp = vert_total;
	vgaregs320x240[V_BLANKING_END_INDEX] = (temp & 0xff);
#endif
}
