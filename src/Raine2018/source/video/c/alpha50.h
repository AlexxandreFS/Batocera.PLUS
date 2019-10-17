
#undef ARG_DIR
#define ARG_DIR UINT8 *SPR, int x, int y, UINT8 cmap
#undef render
#define render(SIZE,BPP,READ)                                    \
void Draw##SIZE##x##SIZE##_Trans_Alpha50_##BPP(ARG_DIR)          \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=0; yy<SIZE; yy++){                                     \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){                    \
         if(READ(SPR) != emudx_transp)                           \
            blend50_##BPP(&line[xx], READ(SPR));                 \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha50_##BPP##_FlipX(ARG_DIR)  \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=SIZE-1; yy>=0; yy--){                                  \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){                    \
         if(READ(SPR) != emudx_transp)                           \
            blend50_##BPP(&line[xx], READ(SPR));                 \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha50_##BPP##_FlipY(ARG_DIR)  \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=0; yy<SIZE; yy++){                                     \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){                 \
         if(READ(SPR) != emudx_transp)                           \
            blend50_##BPP(&line[xx], READ(SPR));                 \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha50_##BPP##_FlipXY(ARG_DIR) \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=SIZE-1; yy>=0; yy--){                                  \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){                 \
         if(READ(SPR) != emudx_transp)                           \
            blend50_##BPP(&line[xx], READ(SPR));                 \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha_##BPP(ARG_DIR)            \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=0; yy<SIZE; yy++){                                     \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){                    \
         if(READ(SPR) != emudx_transp)                           \
            blend_##BPP(&line[xx], READ(SPR));                   \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha_##BPP##_FlipX(ARG_DIR)    \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=SIZE-1; yy>=0; yy--){                                  \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){                    \
         if(READ(SPR) != emudx_transp)                           \
            blend_##BPP(&line[xx], READ(SPR));                   \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha_##BPP##_FlipY(ARG_DIR)    \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=0; yy<SIZE; yy++){                                     \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){                 \
         if(READ(SPR) != emudx_transp)                           \
            blend_##BPP(&line[xx], READ(SPR));                   \
      }                                                          \
   }                                                             \
}                                                                \
                                                                 \
void Draw##SIZE##x##SIZE##_Trans_Alpha_##BPP##_FlipXY(ARG_DIR)   \
{                                                                \
   UINT##BPP *line;                                              \
   int xx,yy;                                                    \
                                                                 \
   for(yy=SIZE-1; yy>=0; yy--){                                  \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;        \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){                 \
         if(READ(SPR) != emudx_transp)                           \
            blend_##BPP(&line[xx], READ(SPR));                   \
      }                                                          \
   }                                                             \
}
