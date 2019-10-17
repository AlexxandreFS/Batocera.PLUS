
/* ##SIZE##x##SIZE## sprites */
/* These are for emudx */

#ifdef ARG_DIR
#undef ARG_DIR
#endif

#define ARG_DIR UINT8 *SPR, int x, int y, UINT8 cmap

#define unmapped(SIZE,BPP)                                     \
void Draw##SIZE##x##SIZE##_##BPP(ARG_DIR)                      \
{                                                              \
   UINT##BPP *line;                                            \
   int xx,yy;                                                  \
                                                               \
   for(yy=0; yy<SIZE; yy++){                                   \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;      \
      for(xx=0; xx<SIZE; xx++){                                \
         *line++ = ReadWord(SPR); SPR+=(BPP/8);                \
      }                                                        \
   }                                                           \
}                                                              \
                                                               \
void Draw##SIZE##x##SIZE##_##BPP##_FlipX(ARG_DIR)              \
{                                                              \
   UINT##BPP *line;                                            \
   int xx,yy;                                                  \
                                                               \
   for(yy=SIZE-1; yy>=0; yy--){                                \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x;      \
      for(xx=0; xx<SIZE; xx++){                                \
         *line++ = ReadWord(SPR); SPR+=(BPP/8);                \
      }                                                        \
   }                                                           \
}                                                              \
                                                               \
void Draw##SIZE##x##SIZE##_##BPP##_FlipY(ARG_DIR)              \
{                                                              \
   UINT##BPP *line;                                            \
   int xx,yy;                                                  \
                                                               \
   for(yy=0; yy<SIZE; yy++){                                   \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x + 15; \
      for(xx=0; xx<SIZE; xx++){                                \
         *line-- = ReadWord(SPR); SPR+=(BPP/8);                \
      }                                                        \
   }                                                           \
}                                                              \
                                                               \
void Draw##SIZE##x##SIZE##_##BPP##_FlipXY(ARG_DIR)             \
{                                                              \
   UINT##BPP *line;                                            \
   int xx,yy;                                                  \
                                                               \
   for(yy=SIZE-1; yy>=0; yy--){                                \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x + 15; \
      for(xx=0; xx<SIZE; xx++){                                \
         *line-- = ReadWord(SPR); SPR+=(BPP/8);                \
      }                                                        \
   }                                                           \
}                                                              \

/* ##SIZE##x##SIZE## transparent sprites */

#define unmapped_trans(SIZE,BPP,FUNC)                     \
void Draw##SIZE##x##SIZE##_Trans_##BPP(ARG_DIR)           \
{                                                         \
   UINT##BPP *line;                                       \
   int xx,yy;                                             \
                                                          \
   for(yy=0; yy<SIZE; yy++){                              \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x; \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){             \
         if(FUNC(SPR) != emudx_transp)                    \
            line[xx] = FUNC(SPR);                         \
      }                                                   \
   }                                                      \
}                                                         \
                                                          \
void Draw##SIZE##x##SIZE##_Trans_##BPP##_FlipX(ARG_DIR)   \
{                                                         \
   UINT##BPP *line;                                       \
   int xx,yy;                                             \
                                                          \
   for(yy=SIZE-1; yy>=0; yy--){                           \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x; \
      for(xx=0; xx<SIZE; xx++, SPR+=(BPP/8)){             \
         if(FUNC(SPR) != emudx_transp)                    \
            line[xx] = FUNC(SPR);                         \
      }                                                   \
   }                                                      \
}                                                         \
                                                          \
void Draw##SIZE##x##SIZE##_Trans_##BPP##_FlipY(ARG_DIR)   \
{                                                         \
   UINT##BPP *line;                                       \
   int xx,yy;                                             \
                                                          \
   for(yy=0; yy<SIZE; yy++){                              \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x; \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){          \
         if(FUNC(SPR) != emudx_transp)                    \
            line[xx] = FUNC(SPR);                         \
      }                                                   \
   }                                                      \
}                                                         \
                                                          \
void Draw##SIZE##x##SIZE##_Trans_##BPP##_FlipXY(ARG_DIR)  \
{                                                         \
   UINT##BPP *line;                                       \
   int xx,yy;                                             \
                                                          \
   for(yy=SIZE-1; yy>=0; yy--){                           \
      line = ((UINT##BPP *)(GameBitmap->line[y+yy])) + x; \
      for(xx=SIZE-1; xx>=0; xx--, SPR+=(BPP/8)){          \
         if(FUNC(SPR) != emudx_transp)                    \
            line[xx] = FUNC(SPR);                         \
      }                                                   \
   }                                                      \
}
