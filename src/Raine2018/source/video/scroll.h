
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                               SCROLL MACROS                                */
/*                                                                            */
/******************************************************************************/

#define SCROLL_REGS             \
   int x,y,x16,y16,zzzz,zzz,zz; \

#define MAKE_SCROLL_512x512_4_16_R(scr_x,scr_y) \
   zzz=~(scr_x);                                \
   zzzz=(zzz&0x1F0)>>2;                         \
   x16=15-(zzz&15);                             \
   zzz=~(scr_y);                                \
   zzzz|=(zzz&0x1F0)<<3;                        \
   y16=15-(zzz&15);                             \

#define MAKE_SCROLL_1024x512_4_16_R(scr_x,scr_y) \
   zzz=~(scr_x);                                 \
   zzzz=(zzz&0x3F0)>>2;                          \
   x16=15-(zzz&15);                              \
   zzz=~(scr_y);                                 \
   zzzz|=(zzz&0x1F0)<<4;                         \
   y16=15-(zzz&15);                              \

// =============================================================================

#define START_SCROLL_8(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                           \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=8){      \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=8){      \

#define START_SCROLL_8_YX(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                           \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=8){      \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=8){      \

#define START_SCROLL_8_R180(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                \
   for(y=(view_y+start_y+y16-8);(UINT32)y>(start_y-8);y-=8){       \
   for(x=(view_x+start_x+x16-8);(UINT32)x>(start_x-8);x-=8){       \

#define START_SCROLL_8_R270(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                \
   for(x=(start_x-y16);(UINT32)x<(view_x+start_x);x+=8){           \
   for(y=(view_y+start_y+x16-8);(UINT32)y>(start_y-8);y-=8){       \

#define START_SCROLL_8_FLIPY(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                 \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=8){            \
   for(x=(view_x+start_x+x16-8);(UINT32)x>(start_x-8);x-=8){        \

// -----------------------------------------------------------------------------

#define START_SCROLL_16(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                            \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=16){      \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=16){      \

#define START_SCROLL_16_YX(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                            \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=16){      \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=16){      \

#define START_SCROLL_16_R180(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                 \
   for(y=(view_y+start_y+y16-16);(UINT32)y>(start_y-16);y-=16){     \
   for(x=(view_x+start_x+x16-16);(UINT32)x>(start_x-16);x-=16){     \

#define START_SCROLL_16_R270(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                 \
   for(x=(start_x-y16);(UINT32)x<(view_x+start_x);x+=16){           \
   for(y=(view_y+start_y+x16-16);(UINT32)y>(start_y-16);y-=16){     \

// -----------------------------------------------------------------------------

// Some games draw by column, now row (swap x,y loops)

#define START_SCROLL_16_YX(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                               \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=16){         \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=16){         \

#define START_SCROLL_16_YX_R180(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                    \
   for(x=(view_x+start_x+x16-16);(UINT32)x>(start_x-16);x-=16){        \
   for(y=(view_y+start_y+y16-16);(UINT32)y>(start_y-16);y-=16){        \

#define START_SCROLL_16_YX_R270(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                                    \
   for(y=(view_y+start_y+x16-16);(UINT32)y>(start_y-16);y-=16){        \
   for(x=(start_x-y16);(UINT32)x<(view_x+start_x);x+=16){              \

// =============================================================================

#define MAKE_SCROLL_256x256_2_8(scr_x,scr_y) \
   zzz=(scr_x);                              \
   zzzz=(zzz&0x0F8)>>2;                      \
   x16=zzz&7;                                \
   zzz=(scr_y);                              \
   zzzz|=(zzz&0x0F8)<<3;                     \
   y16=zzz&7;                                \

#define START_SCROLL_256x256_2_8		START_SCROLL_8
#define START_SCROLL_256x256_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_256x256_2_8_R270		START_SCROLL_8_R270
#define START_SCROLL_256x256_2_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_256x256_2_8()    \
      zz=(zz&0x07C0)|((zz+2)&0x3F); \
   }                                \
   zz = zzzz = (zzzz+0x40)&0x07FF;  \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x256_2_8(scr_x,scr_y) \
   zzz=(scr_x);                              \
   zzzz=(zzz&0x1F8)>>2;                      \
   x16=zzz&7;                                \
   zzz=(scr_y);                              \
   zzzz|=(zzz&0x0F8)<<4;                     \
   y16=zzz&7;                                \

#define MAKE_SCROLL_512x256_2_8_no16(scr_x,scr_y) \
   zzz=(scr_x);                                   \
   zzzz=(zzz&0x1F8)>>2;                           \
   zzz=(scr_y);                                   \
   zzzz|=(zzz&0x0F8)<<4;                          \

#define START_SCROLL_512x256_2_8		START_SCROLL_8
#define START_SCROLL_512x256_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_512x256_2_8_R270		START_SCROLL_8_R270
#define START_SCROLL_512x256_2_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_512x256_2_8()    \
      zz=(zz&0x0F80)|((zz+2)&0x7F); \
   }                                \
   zz = zzzz = (zzzz+0x80)&0x0FFF;  \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x512_1_8_no16(scr_x,scr_y) \
   zzz=(scr_x);                                   \
   zzzz=(zzz&0x1F8)>>3;                           \
   zzz=(scr_y);                                   \
   zzzz|=(zzz&0x1F8)<<3;

#define START_SCROLL_512x512_1_8		START_SCROLL_8
#define START_SCROLL_512x512_1_8_R180		START_SCROLL_8_R180
#define START_SCROLL_512x512_1_8_R270		START_SCROLL_8_R270
#define START_SCROLL_512x512_1_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_512x512_1_8()    \
      zz=(zz&0x07C0)|((zz+1)&0x3F); \
   }                                \
   zz = zzzz = (zzzz+0x40)&0x07FF;  \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x512_2_8(scr_x,scr_y) \
   zzz=(scr_x);                              \
   zzzz=(zzz&0x1F8)>>2;                      \
   x16=zzz&7;                                \
   zzz=(scr_y);                              \
   zzzz|=(zzz&0x1F8)<<4;                     \
   y16=zzz&7;

#define MAKE_SCROLL_512x512_2_8_no16(scr_x,scr_y) \
   zzz=(scr_x);                                   \
   zzzz=(zzz&0x1F8)>>2;                           \
   zzz=(scr_y);                                   \
   zzzz|=(zzz&0x1F8)<<4;

#define START_SCROLL_512x512_2_8		START_SCROLL_8
#define START_SCROLL_512x512_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_512x512_2_8_R270		START_SCROLL_8_R270
#define START_SCROLL_512x512_2_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_512x512_2_8()    \
      zz=(zz&0x1F80)|((zz+2)&0x7F); \
   }                                \
   zz = zzzz = (zzzz+0x80)&0x1FFF;  \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x1024_2_8(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x1F8)>>2;                       \
   x16=zzz&7;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x3F8)<<4;                      \
   y16=zzz&7;                                 \

#define START_SCROLL_512x1024_2_8		START_SCROLL_8
#define START_SCROLL_512x1024_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_512x1024_2_8_R270		START_SCROLL_8_R270
#define START_SCROLL_512x1024_2_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_512x1024_2_8()   \
      zz=(zz&0x3F80)|((zz+2)&0x7F); \
   }                                \
   zz = zzzz = (zzzz+0x80)&0x3FFF;  \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x512_4_8(scr_x,scr_y) \
   zzz=(scr_x);                              \
   zzzz=(zzz&0x1F8)>>1;                      \
   x16=zzz&7;                                \
   zzz=(scr_y);                              \
   zzzz|=(zzz&0x1F8)<<5;                     \
   y16=zzz&7;                                \

#define START_SCROLL_512x512_4_8		START_SCROLL_8
#define START_SCROLL_512x512_4_8_R180		START_SCROLL_8_R180
#define START_SCROLL_512x512_4_8_R270		START_SCROLL_8_R270
#define START_SCROLL_512x512_4_8_FLIPY		START_SCROLL_8_FLIPY

#define END_SCROLL_512x512_4_8()    \
      zz=(zz&0x3F00)|((zz+4)&0xFF); \
   }                                \
   zz = zzzz = (zzzz+0x100)&0x3FFF; \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x1024_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                 \
   zzzz=(zzz&0x3F0)>>3;                         \
   x16=zzz&15;                                  \
   zzz=(scr_y);                                 \
   zzzz|=(zzz&0x3F0)<<3;                        \
   y16=zzz&15;                                  \

#define MAKE_SCROLL_n_16(width,height,n,scr_x,scr_y)	\
   zzz=(scr_x);						\
   zzzz=(zzz&(width-16))/16*n;				\
   x16=zzz&15;						\
   zzz=(scr_y);						\
   zzzz|=(zzz&(height-16))*(width/16*n)/16;		\
   y16=zzz&15;

#define MAKE_SCROLL_n_8(width,height,n,scr_x,scr_y)	\
   zzz=(scr_x);						\
   zzzz=(zzz&(width-8))/8*n;				\
   x16=zzz&7;						\
   zzz=(scr_y);						\
   zzzz|=(zzz&(height-8))*(width/8*n)/8;		\
   y16=zzz&7;

#define START_SCROLL_1024x1024_2_16		START_SCROLL_16
#define START_SCROLL_1024x1024_2_16_R180	START_SCROLL_16_R180
#define START_SCROLL_1024x1024_2_16_R270	START_SCROLL_16_R270

#define END_SCROLL_n_16(width,height,n) \
      zz=(zz&(width*height*n/(16*16)-width*n/16))|((zz+n)&(width*n/16-1)); \
   }                                                                       \
   zz = zzzz = (zzzz+(width*n/16))&(width*height*n/(16*16)-1);             \
   }

#define END_SCROLL_n_8(width,height,n) \
      zz=(zz&(width*height*n/(8*8)-width*n/8))|((zz+n)&(width*n/8-1)); \
   }                                                                       \
   zz = zzzz = (zzzz+(width*n/8))&(width*height*n/(8*8)-1);             \
   }

#define END_SCROLL_1024x1024_2_16() \
  END_SCROLL_n_16(1024,1024,2)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x512_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0x3F0)>>3;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0x1F0)<<3;                       \
   y16=zzz&15;                                 \

#define START_SCROLL_1024x512_2_16		START_SCROLL_16
#define START_SCROLL_1024x512_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_1024x512_2_16_R270		START_SCROLL_16_R270

#define END_SCROLL_1024x512_2_16() \
  END_SCROLL_n_16(1024,512,2)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x512_4_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0x3F0)>>2;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0x1F0)<<4;                       \
   y16=zzz&15;                                 \

#define START_SCROLL_1024x512_4_16		START_SCROLL_16
#define START_SCROLL_1024x512_4_16_R180		START_SCROLL_16_R180
#define START_SCROLL_1024x512_4_16_R270		START_SCROLL_16_R270

#define END_SCROLL_1024x512_4_16()  \
  END_SCROLL_n_16(1024,512,4)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x512_2_8(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x3F8)>>2;                       \
   x16=zzz&7;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x1F8)<<5;                      \
   y16=zzz&7;                                 \

#define START_SCROLL_1024x512_2_8		START_SCROLL_8
#define START_SCROLL_1024x512_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_1024x512_2_8_R270		START_SCROLL_8_R270

#define END_SCROLL_1024x512_2_8()   \
      zz=(zz&0x3F00)|((zz+2)&0xFF); \
   }                                \
   zz = zzzz = (zzzz+0x100)&0x3FFF; \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x256_4_16(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x1F0)>>2;                       \
   x16=zzz&15;                                \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x0F0)<<3;                      \
   y16=zzz&15;                                \

#define START_SCROLL_512x256_4_16		START_SCROLL_16
#define START_SCROLL_512x256_4_16_R180		START_SCROLL_16_R180
#define START_SCROLL_512x256_4_16_R270		START_SCROLL_16_R270

#define END_SCROLL_512x256_4_16()  \
  END_SCROLL_n_16(512,256,4)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x512_4_16(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x1F0)>>2;                       \
   x16=zzz&15;                                \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x1F0)<<3;                      \
   y16=zzz&15;                                \

#define START_SCROLL_512x512_4_16		START_SCROLL_16
#define START_SCROLL_512x512_4_16_R180		START_SCROLL_16_R180
#define START_SCROLL_512x512_4_16_R270		START_SCROLL_16_R270

#define END_SCROLL_512x512_4_16()  \
  END_SCROLL_n_16(512,512,4)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x512_4_8(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x3F8)>>1;                       \
   x16=zzz&7;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x1F8)<<6;                      \
   y16=zzz&7;                                 \

#define START_SCROLL_1024x512_4_8		START_SCROLL_8
#define START_SCROLL_1024x512_4_8_R180		START_SCROLL_8_R180
#define START_SCROLL_1024x512_4_8_R270		START_SCROLL_8_R270

#define END_SCROLL_1024x512_4_8()    \
      zz=(zz&0x7E00)|((zz+4)&0x1FF); \
   }                                 \
   zz = zzzz = (zzzz+0x200)&0x7FFF;  \
   }                                 \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x256_2_8(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x3F8)>>2;                       \
   x16=zzz&7;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x0F8)<<5;                      \
   y16=zzz&7;                                 \

#define START_SCROLL_1024x256_2_8		START_SCROLL_8
#define START_SCROLL_1024x256_2_8_R180		START_SCROLL_8_R180
#define START_SCROLL_1024x256_2_8_R270		START_SCROLL_8_R270

#define END_SCROLL_1024x256_2_8()   \
      zz=(zz&0x1F00)|((zz+2)&0xFF); \
   }                                \
   zz = zzzz = (zzzz+0x100)&0x1FFF; \
   }                                \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_1024x256_4_8_YX(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x3F8)>>2;                       \
   x16=zzz&7;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x0F8)<<6;                      \
   y16=zzz&7;                                 \

#define START_SCROLL_1024x256_4_8_YX		START_SCROLL_8_YX

#define END_SCROLL_1024x256_4_8_YX() \
      zz=(zz&0x3F80)|((zz+4)&0x7F);  \
   }                                 \
   zz = zzzz = (zzzz+0x80)&0x3FFF;   \
   }                                 \

#define MAKE_SCROLL_2048x512_4_16_YX(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x7F0)>>3;                       \
   x16=zzz&15;                                 \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x1F0)<<5;                      \
   y16=zzz&15;                                 \

#define START_SCROLL_2048x512_4_16_YX		START_SCROLL_16_YX

#define END_SCROLL_2048x512_4_16_YX() \
      zz=(zz&0x3F80)|((zz+4)&0x7F);  \
   }                                 \
   zz = zzzz = (zzzz+0x80)&0x3FFF;   \
   }                                 \

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x512_2_16(scr_x,scr_y) \
   zzz=(scr_x);                               \
   zzzz=(zzz&0x1F0)>>3;                       \
   x16=zzz&15;                                \
   zzz=(scr_y);                               \
   zzzz|=(zzz&0x1F0)<<2;                      \
   y16=zzz&15;                                \

#define START_SCROLL_512x512_2_16		START_SCROLL_16
#define START_SCROLL_512x512_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_512x512_2_16_R270		START_SCROLL_16_R270
#define START_SCROLL_512x512_2_16_FLIPY		START_SCROLL_16_FLIPY

#define END_SCROLL_512x512_2_16()   \
  END_SCROLL_n_16(512,512,2)

// -----------------------------------------------------------------------------

#define MAKE_SCROLL_512x1024_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0x1F0)>>3;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0x3F0)<<2;                       \
   y16=zzz&15;                                 \

#define START_SCROLL_512x1024_2_16		START_SCROLL_16
#define START_SCROLL_512x1024_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_512x1024_2_16_R270		START_SCROLL_16_R270
#define START_SCROLL_512x1024_2_16_FLIPY	START_SCROLL_16_FLIPY

#define END_SCROLL_512x1024_2_16()  \
  END_SCROLL_n_16(512,1024,2)

// =============================================================================

#define MAKE_SCROLL_512x2048_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0x1F0)>>3;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0x7F0)<<2;                       \
   y16=zzz&15;                                 \

#define MAKE_SCROLL_2048x512_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0x7F0)>>3;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0x1F0)<<4;                       \
   y16=zzz&15;                                 \

#define MAKE_SCROLL_4096x256_2_16(scr_x,scr_y) \
   zzz=(scr_x);                                \
   zzzz=(zzz&0xff0)>>3;                        \
   x16=zzz&15;                                 \
   zzz=(scr_y);                                \
   zzzz|=(zzz&0xF0)<<5;                       \
   y16=zzz&15;

#define START_SCROLL_512x2048_2_16		START_SCROLL_16
#define START_SCROLL_512x2048_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_512x2048_2_16_R270		START_SCROLL_16_R270
#define START_SCROLL_512x2048_2_16_FLIPY	START_SCROLL_16_FLIPY

#define START_SCROLL_2048x512_2_16		START_SCROLL_16
#define START_SCROLL_2048x512_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_2048x512_2_16_R270		START_SCROLL_16_R270
#define START_SCROLL_2048x512_2_16_FLIPY	START_SCROLL_16_FLIPY

#define START_SCROLL_4096x256_2_16		START_SCROLL_16
#define START_SCROLL_4096x256_2_16_R180		START_SCROLL_16_R180
#define START_SCROLL_4096x256_2_16_R270		START_SCROLL_16_R270
#define START_SCROLL_4096x256_2_16_FLIPY	START_SCROLL_16_FLIPY

#define END_SCROLL_512x2048_2_16()  \
  END_SCROLL_n_16(512,2048,2)

#define END_SCROLL_2048x512_2_16()  \
  END_SCROLL_n_16(2048,512,2)

#define END_SCROLL_4096x256_2_16()  \
  END_SCROLL_n_16(4096,256,2)

// =============================================================================

#ifdef __cplusplus
}
#endif
