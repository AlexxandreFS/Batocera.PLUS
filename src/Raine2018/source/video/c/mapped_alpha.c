#include "deftypes.h"
#include "raine.h"
#include "emudx.h"
#include "blit.h"
#include "alpha.h"
#include "mapped_alpha.h"

#undef render
#define render(SIZE,BPP)                                              \
void Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP(ARG_MAP)          \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=0; yy<SIZE; yy++){                                          \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=0; xx<SIZE; xx++, SPR++){                                \
         if(*SPR)                                                     \
            blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);      \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipX(ARG_MAP)  \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=SIZE-1; yy>=0; yy--){                                       \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=0; xx<SIZE; xx++, SPR++){                                \
         if(*SPR)                                                     \
            blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);      \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipY(ARG_MAP)  \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=0; yy<SIZE; yy++){                                          \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=SIZE-1; xx>=0; xx--, SPR++){                             \
         if(*SPR)                                                     \
            blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);      \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipXY(ARG_MAP) \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=SIZE-1; yy>=0; yy--){                                       \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=SIZE-1; xx>=0; xx--, SPR++){                             \
         if(*SPR)                                                     \
            blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);      \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP(ARG_MAP)                \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=0; yy<SIZE; yy++){                                          \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=0; xx<SIZE; xx++, SPR++){                                \
          blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);        \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipX(ARG_MAP)        \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=SIZE-1; yy>=0; yy--){                                       \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=0; xx<SIZE; xx++, SPR++){                                \
          blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);        \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipY(ARG_MAP)        \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=0; yy<SIZE; yy++){                                          \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=SIZE-1; xx>=0; xx--, SPR++){                             \
          blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);        \
      }                                                               \
   }                                                                  \
}                                                                     \
                                                                      \
void Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipXY(ARG_MAP)       \
{                                                                     \
   UINT##BPP *line;                                                   \
   int xx,yy;                                                         \
                                                                      \
   for(yy=SIZE-1; yy>=0; yy--){                                       \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;             \
      for(xx=SIZE-1; xx>=0; xx--, SPR++){                             \
          blend_##BPP(&line[xx], ((UINT##BPP *)cmap)[ *SPR ]);        \
      }                                                               \
   }                                                                  \
}
render(16,8);
render(16,16);
render(16,32);
