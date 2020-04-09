#ifndef PAIR_H
#define PAIR_H

typedef union
{
#ifdef LSB_FIRST
	struct { UINT8 l,h,h2,h3; } b;
	struct { UINT16 l,h; } w;
	struct { INT8 l,h,h2,h3; } sb;
	struct { INT16 l,h; } sw;
#else
	struct { UINT8 h3,h2,h,l; } b;
	struct { INT8 h3,h2,h,l; } sb;
	struct { UINT16 h,l; } w;
	struct { INT16 h,l; } sw;
#endif
	UINT32 d;
	INT32 sd;
} PAIR;

#endif

