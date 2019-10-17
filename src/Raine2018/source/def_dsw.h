// edf, hachoo, iganinju, plusalph, rodland, tshingen
#define COINAGE_6BITS \
   { MSG_COIN1,               0x07, 0x08 },\
   { MSG_3COIN_1PLAY,         0x04 },\
   { MSG_2COIN_1PLAY,         0x02 },\
   { MSG_1COIN_1PLAY,         0x07 },\
   { MSG_1COIN_2PLAY,         0x03 },\
   { MSG_1COIN_3PLAY,         0x05 },\
   { MSG_1COIN_4PLAY,         0x01 },\
   { MSG_1COIN_5PLAY,         0x06 },\
   { MSG_FREE_PLAY,           0x00 },\
   { MSG_COIN2,               0x38, 0x08 },\
   { MSG_4COIN_1PLAY,         0x00 },\
   { MSG_3COIN_1PLAY,         0x20 },\
   { MSG_2COIN_1PLAY,         0x10 },\
   { MSG_1COIN_1PLAY,         0x38 },\
   { MSG_1COIN_2PLAY,         0x18 },\
   { MSG_1COIN_3PLAY,         0x28 },\
   { MSG_1COIN_4PLAY,         0x08 },\
   { MSG_1COIN_5PLAY,         0x30 },

// lomakai, p47, peekaboo, stdragon, soldamj
#define COINAGE_6BITS_ALT \
   { MSG_COIN1,               0x07, 0x08 },\
   { MSG_4COIN_1PLAY,         0x01 },\
   { MSG_3COIN_1PLAY,         0x02 },\
   { MSG_2COIN_1PLAY,         0x03 },\
   { MSG_1COIN_1PLAY,         0x07 },\
   { MSG_1COIN_2PLAY,         0x06 },\
   { MSG_1COIN_3PLAY,         0x05 },\
   { MSG_1COIN_4PLAY,         0x04 },\
   { MSG_FREE_PLAY,           0x00 },\
   { MSG_COIN2,               0x38, 0x08 },\
   { MSG_4COIN_1PLAY,         0x08 },\
   { MSG_3COIN_1PLAY,         0x10 },\
   { MSG_2COIN_1PLAY,         0x18 },\
   { MSG_1COIN_1PLAY,         0x38 },\
   { MSG_1COIN_2PLAY,         0x30 },\
   { MSG_1COIN_3PLAY,         0x28 },\
   { MSG_1COIN_4PLAY,         0x20 },\
   { MSG_FREE_PLAY,           0x00 },

#define DSW_TAITO_COINAGE_US                        \
   DSW_REGION(1),                                   \
     { MSG_COIN1,           0x30, 0x04 },           \
     { MSG_1COIN_1PLAY,          0x30},             \
     { MSG_2COIN_1PLAY,          0x20},             \
     { MSG_3COIN_1PLAY,          0x10},             \
     { MSG_4COIN_1PLAY,          0x00},             \
     { "Price to continue",           0xC0, 0x04 }, \
     { "Same as start",          0xC0},             \
     { MSG_1COIN_1PLAY,          0x80},             \
     { MSG_2COIN_1PLAY,          0x40},             \
     { MSG_3COIN_1PLAY,	      0x00}

#define DSW_TAITO_COINAGE_WORLD           \
     { MSG_COIN1,           0x30, 0x04 }, \
     { MSG_1COIN_1PLAY,          0x30},   \
     { MSG_2COIN_1PLAY,          0x20},   \
     { MSG_3COIN_1PLAY,          0x10},   \
     { MSG_4COIN_1PLAY,          0x00},   \
     { MSG_COIN2,           0xC0, 0x04 }, \
     { MSG_1COIN_2PLAY,          0xC0},   \
     { MSG_1COIN_3PLAY,          0x80},   \
     { MSG_1COIN_4PLAY,          0x40},   \
     { MSG_1COIN_6PLAY,	      0x00}

#define DSW_TAITO_COINAGE_OLD_JAPAN       \
     { MSG_COIN1,           0x30, 0x04 }, \
     { MSG_1COIN_1PLAY,          0x30},   \
     { MSG_1COIN_2PLAY,          0x20},   \
     { MSG_2COIN_1PLAY,          0x10},   \
     { MSG_2COIN_3PLAY,          0x00},   \
     { MSG_COIN2,           0xC0, 0x04 }, \
     { MSG_1COIN_1PLAY,          0xC0},   \
     { MSG_1COIN_2PLAY,          0x80},   \
     { MSG_2COIN_1PLAY,          0x40},   \
     { MSG_2COIN_3PLAY,	      0x00}

#define DSW_TAITO_CAB_SCREEN_TEST_DEMO \
   DSW_CABINET( 0x00, 0x01),           \
   DSW_SCREEN( 0x02, 0x00),            \
   DSW_TEST_MODE( 0x00, 0x04),         \
   DSW_DEMO_SOUND( 0x08, 0x00)

#define DSW_TAITO_SCREEN_TEST_DEMO \
   DSW_SCREEN( 0x02, 0x00),        \
   DSW_TEST_MODE( 0x00, 0x04),     \
   DSW_DEMO_SOUND( 0x08, 0x00)
