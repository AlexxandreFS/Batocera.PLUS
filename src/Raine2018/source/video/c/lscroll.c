#include "deftypes.h"
#include "raine.h"
#include "priorities.h"
#include "blit.h"

extern int disp_x_16,disp_x_16,disp_x_8,disp_x_8;

/* This single macro replaces a whole directory.
   It's a little less readable, but if you use a good editor with some functions to
   handle macros like this one, it's not too bad.
   It's much better than 1 file / size and / depth, it reduces the number of possible
   bugs. Use filter.pl in this directory to generate the headers if you need to */

#define declare( SIZE, DEPTH )												     \
void ldraw##SIZE##x##SIZE##_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)				     \
{															     \
  UINT##DEPTH *line;													     \
  INT16 xx,yy,dx;													     \
  for(yy=0; yy<(SIZE); yy++){												     \
    dx = x+dy[yy];													     \
    if (dx < 0 || dx > disp_x_##SIZE) {											     \
      SPR += (SIZE);													     \
      continue;														     \
    }															     \
    line = ((UINT##DEPTH *)(GameBitmap->line[y+yy]))+ dx;								     \
    for(xx=0; xx<(SIZE); xx++){												     \
      *line++ = ((UINT##DEPTH *)cmap)[ *SPR++ ];									     \
    }															     \
  }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)		     \
{															     \
  UINT8 *pline;														     \
  UINT##DEPTH *line;													     \
  INT16 xx,yy,dx;													     \
															     \
  for(yy=0; yy<(SIZE); yy++, SPR+=SIZE){												     \
    dx = x+dy[yy];													     \
    if (dx < 0 || dx > disp_x_##SIZE) {											     \
      continue;														     \
    }															     \
    pline = pbitmap->line[y+yy]+ dx;											     \
    line = ((UINT##DEPTH *)(GameBitmap->line[y+yy]))+ dx;								     \
    for(xx=0; xx<(SIZE); xx++){												     \
      if (pline[xx] <= pri) {												     \
	pline[xx] = pri;												     \
	line[xx] = ((UINT##DEPTH *)cmap)[ SPR[xx] ];									     \
      }															     \
    }															     \
  }															     \
}															     \
															     \
/* The column draw is designed to replace the line scroll when the screen */						     \
/* is rotated by 270°. If a game uses 90 or 180° we will use 2 other famillies */					     \
/* of functions. */													     \
/* This cdraw##SIZE##x##SIZE## is very unefficient compared to the usual Draw##SIZE##x##SIZE## */			     \
/* functions because : */												     \
/* - the line scroll indexes follow y (on screen) */									     \
/* - the sprite follows x. */												     \
/* This whole thing should probably be entierly rewritten, and preferably using */					     \
/* a macro this time to have only 1 version for 8,16 and 32 bpp. */							     \
															     \
void cdraw##SIZE##x##SIZE##_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)				     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
  UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE*w); yy+=w){											     \
       line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
       spr += 16;													     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)		     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
  UINT##DEPTH *line;													     \
   UINT8 *pline,*spr;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w;														     \
   w = pbitmap->w;													     \
															     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x + xx ;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     spr = &SPR[xx];													     \
     for(yy=0; yy<(SIZE)*w; yy+=w){											     \
       if (pline[yy] <= pri) {												     \
	 line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
	 pline[yy] = pri;												     \
       }														     \
       spr += (SIZE);													     \
     }															     \
   }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)			     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy]))+ dx;								     \
     for(xx=0; xx<(SIZE); xx++){											     \
       *line++ = ((UINT##DEPTH *)cmap)[ *SPR++ ];									     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)			     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
  UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1); yy>=0; yy--){											     \
       line[yy*w] = ((UINT##DEPTH *)cmap)[ spr[(SIZE)*((SIZE-1)-yy)] ];							     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)	     \
{															     \
   UINT##DEPTH *line;													     \
   UINT8 *pline;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--, SPR += SIZE){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy]))+ dx;								     \
     pline = ((UINT8 *)(pbitmap->line[y+yy]))+dx ;									     \
     for(xx=0; xx<(SIZE); xx++){											     \
       if (pline[xx] <= pri) {												     \
	 pline[xx] = pri;												     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ SPR[xx] ];									     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)	     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
  UINT##DEPTH *line;													     \
  UINT8 *pline;														     \
  UINT8 *spr;														     \
  INT16 xx,yy,dy;													     \
  UINT32 w = GameBitmap->w;												     \
															     \
  for(xx=0; xx<=(SIZE-1); xx++){											     \
    dy = y-dx[xx];													     \
    if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
      continue;														     \
    }															     \
    spr = &SPR[xx];													     \
    line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
    pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx ;									     \
    for(yy=(SIZE-1)*w; yy>=0; yy-=w){											     \
      if (pline[yy] <= pri) {												     \
	pline[yy] = pri;												     \
	line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
      }															     \
      spr += 16;													     \
    }															     \
  }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)			     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx+(SIZE-1);							     \
     for(xx=0; xx<(SIZE); xx++){											     \
       *line-- = ((UINT##DEPTH *)cmap)[ *SPR++ ];									     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)			     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE); yy++){											     \
       line[yy*w] = ((UINT##DEPTH *)cmap)[ spr[(SIZE)*yy] ];								     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)	     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
   UINT8 *pline;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     pline = ((UINT8 *)(pbitmap->line[y+yy]))+dx;									     \
     for(xx=(SIZE-1); xx>=0; xx--){											     \
       if (pline[xx] <= pri) {												     \
	 pline[xx] = pri;												     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
       }														     \
       SPR++;														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)	     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr,*pline;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx;									     \
     for(yy=0; yy<(SIZE)*w; yy+=w){											     \
       if (pline[yy] <= pri) {												     \
	 pline[yy] = pri;												     \
	 line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
       }														     \
       spr += SIZE;													     \
     }															     \
   }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)			     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx + (SIZE-1);							     \
     for(xx=0; xx<(SIZE); xx++){											     \
       *line-- = ((UINT##DEPTH *)cmap)[ *SPR++ ];									     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)			     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1); yy>=0; yy--){											     \
       line[yy*w] = ((UINT##DEPTH *)cmap)[ spr[(SIZE)*((SIZE-1)-yy)] ];							     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)	     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
   UINT8 *pline;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     pline = ((UINT8 *)(pbitmap->line[y+yy]))+dx;									     \
     for(xx=SIZE-1; xx>=0; xx--){											     \
       if (pline[xx] <= pri) {												     \
	 pline[xx] = pri;												     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
       }														     \
       SPR++;														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)	     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr,*pline;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx;									     \
     for(yy=(SIZE-1)*w; yy>=0; yy-=w){											     \
       if (pline[yy] <= pri) {												     \
	 pline[yy] = pri;												     \
	 line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
       }														     \
       spr += SIZE;													     \
     }															     \
   }															     \
}															     \
															     \
/* mapped transparent sprites */											     \
															     \
void ldraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy)			     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=0; xx<(SIZE); xx++, SPR++){											     \
       if(*SPR)														     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri)	     \
{															     \
   UINT##DEPTH *line;													     \
   UINT8 *pline;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < (SIZE) || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     pline = pbitmap->line[y+yy] + dx;											     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=0; xx<(SIZE); xx++, SPR++){											     \
       if(*SPR) {													     \
	 if (pline[xx] <= pri) {											     \
	   pline[xx] = pri;												     \
	   line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
	 }														     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)			     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE); yy++){											     \
       UINT8 myspr = spr[yy*16];											     \
       if(myspr) {													     \
	 line[yy*w] = ((UINT##DEPTH *)cmap)[ myspr ];									     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)	     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT8 *pline,*spr;													     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = pbitmap->w;												     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx ;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE)*w; yy+=w){											     \
       if(*spr) {													     \
	 if (pline[yy] <= pri) {											     \
	   line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
	   pline[yy] = pri;												     \
	 }														     \
       }														     \
       spr += (SIZE);													     \
     }															     \
   }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)		     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=0; xx<(SIZE); xx++, SPR++){											     \
       if(*SPR)														     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)  \
{															     \
   UINT8 *pline;													     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     pline = ((UINT8 *)(pbitmap->line[y+yy])) + dx;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=0; xx<(SIZE); xx++, SPR++){											     \
       if(*SPR) {													     \
	 if (pline[xx] <= pri) {											     \
	   pline[xx] = pri;												     \
	   line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
	 }														     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)		     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1); yy>=0; yy--){											     \
       UINT8 myspr = spr[(SIZE)*((SIZE-1)-yy)];										     \
       if (myspr) {													     \
	 line[yy*w] = ((UINT##DEPTH *)cmap)[ myspr ];									     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)  \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT8 *pline,*spr;													     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = pbitmap->w;												     \
															     \
   for(xx=0; xx<=(SIZE-1); xx++){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[xx];													     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx ;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1)*w; yy>=0; yy-=w){											     \
       if (*spr) {													     \
	 if (pline[yy] <= pri) {											     \
	   pline[yy] = pri;												     \
	   line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
	 }														     \
       }														     \
       spr += (SIZE);													     \
     }															     \
   }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)		     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=(SIZE-1); xx>=0; xx--, SPR++){										     \
       if(*SPR)														     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri)  \
{															     \
   UINT##DEPTH *line;													     \
   UINT8 *pline;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=0; yy<(SIZE); yy++){												     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     pline = ((UINT8 *)(pbitmap->line[y+yy])) + dx;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=(SIZE-1); xx>=0; xx--, SPR++){										     \
       if(*SPR)														     \
	 if (pline[xx] <= pri) {											     \
	   pline[xx] = pri;												     \
	   line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
	 }														     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)		     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = GameBitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE); yy++){											     \
       UINT8 myspr = spr[(SIZE)*(yy)];											     \
       if (myspr) {													     \
	 line[yy*w] = ((UINT##DEPTH *)cmap)[ myspr ];									     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri)  \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   UINT8 *pline;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = pbitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx ;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=0; yy<(SIZE)*w; yy+=w){											     \
       if (*spr) {													     \
	 if (pline[yy] <= pri) {											     \
	   pline[yy] = pri;												     \
	   line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
	 }														     \
       }														     \
       spr += (SIZE);													     \
     }															     \
   }															     \
}															     \
															     \
void ldraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy)		     \
{															     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=(SIZE-1); xx>=0; xx--, SPR++){										     \
       if(*SPR)														     \
	 line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
     }															     \
   }															     \
}															     \
															     \
void pldraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri) \
{															     \
   UINT##DEPTH *line;													     \
   UINT8 *pline;													     \
   INT16 xx,yy,dx;													     \
															     \
   for(yy=(SIZE-1); yy>=0; yy--){											     \
     dx = x+dy[yy];													     \
     if (dx < 0 || dx > disp_x_##SIZE) {										     \
       SPR += (SIZE);													     \
       continue;													     \
     }															     \
     pline = ((UINT8 *)(pbitmap->line[y+yy])) + dx;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[y+yy])) + dx;								     \
     for(xx=(SIZE-1); xx>=0; xx--, SPR++){										     \
       if(*SPR) {													     \
	 if (pline[xx] <= pri) {											     \
	   pline[xx] = pri;												     \
	   line[xx] = ((UINT##DEPTH *)cmap)[ *SPR ];									     \
	 }														     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void cdraw##SIZE##x##SIZE##_Trans_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx)		     \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT##DEPTH *line;													     \
   UINT8 *spr;														     \
   INT16 xx,yy,dy;													     \
   UINT32 w = pbitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1); yy>=0; yy--){											     \
       UINT8 myspr = spr[(SIZE)*((SIZE-1)-yy)];										     \
       if (myspr) {													     \
	 line[yy*w] = ((UINT##DEPTH *)cmap)[ myspr ];									     \
       }														     \
     }															     \
   }															     \
}															     \
															     \
void pcdraw##SIZE##x##SIZE##_Mask_Trans_Mapped_##DEPTH##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri) \
{															     \
  /* Column draw, or line scroll rotated by 270° */									     \
   UINT8 *pline,*spr;													     \
   UINT##DEPTH *line;													     \
   INT16 xx,yy,dy;													     \
   UINT32 w = pbitmap->w;												     \
															     \
   for(xx=(SIZE-1); xx>=0; xx--){											     \
     dy = y-dx[xx];													     \
     if (dy < (SIZE) || dy > GameBitmap->h-SIZE) {										     \
       continue;													     \
     }															     \
     spr = &SPR[(SIZE-1)-xx];												     \
     pline = ((UINT8 *)(pbitmap->line[dy]))+x+xx ;									     \
     line = ((UINT##DEPTH *)(GameBitmap->line[dy]))+x+xx ;								     \
     for(yy=(SIZE-1)*w; yy>=0; yy-=w){											     \
       if (*spr) {													     \
	 if (pline[yy] <= pri) {											     \
	   pline[yy] = pri;												     \
	   line[yy] = ((UINT##DEPTH *)cmap)[ *spr ];									     \
	 }														     \
       }														     \
       spr += (SIZE);													     \
     }															     \
   }															     \
}

declare(16,8);
declare(16,16);
declare(16,32);
declare(8,8);
declare(8,16);
declare(8,32);
