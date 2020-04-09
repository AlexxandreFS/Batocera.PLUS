
#ifdef __cplusplus
extern "C" {
#endif
#include "deftypes.h"

void decode_ssmissin();
void DecodeStDragon(UINT8 *src);

void DecodePlusAlpha(UINT8 *src);

void DecodeRodlandE(UINT8 *src);

void DecodePipiBibi(UINT8 *src);

void DecodePlotting(UINT8 *src);

void DecodeBombJackTwin_OBJ(UINT8 *src, UINT32 size);

void DecodeBombJackTwin_BG0(UINT8 *src, UINT32 size);

void DecodeThunderDragon_OBJ(UINT8 *src);

void DecodeThunderDragon_ROM(UINT8 *src);

void kabuki_decode(unsigned char *src,unsigned char *dest_op,unsigned char *dest_data,
		   int base_addr,int length,int swap_key1,int swap_key2,int addr_key,int xor_key);

#define BIT(x,n) (((x)>>(n))&1)

#define BITSWAP8(val,B7,B6,B5,B4,B3,B2,B1,B0) \
		((BIT(val,B7) << 7) | \
		 (BIT(val,B6) << 6) | \
		 (BIT(val,B5) << 5) | \
		 (BIT(val,B4) << 4) | \
		 (BIT(val,B3) << 3) | \
		 (BIT(val,B2) << 2) | \
		 (BIT(val,B1) << 1) | \
		 (BIT(val,B0) << 0))

#define BITSWAP16(val,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
		(BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
		(BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
		(BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

#define BITSWAP24(val,B23,B22,B21,B20,B19,B18,B17,B16,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
		(((((val) >> (B23)) & 1) << 23) | \
		 ((((val) >> (B22)) & 1) << 22) | \
		 ((((val) >> (B21)) & 1) << 21) | \
		 ((((val) >> (B20)) & 1) << 20) | \
		 ((((val) >> (B19)) & 1) << 19) | \
		 ((((val) >> (B18)) & 1) << 18) | \
		 ((((val) >> (B17)) & 1) << 17) | \
		 ((((val) >> (B16)) & 1) << 16) | \
		 ((((val) >> (B15)) & 1) << 15) | \
		 ((((val) >> (B14)) & 1) << 14) | \
		 ((((val) >> (B13)) & 1) << 13) | \
		 ((((val) >> (B12)) & 1) << 12) | \
		 ((((val) >> (B11)) & 1) << 11) | \
		 ((((val) >> (B10)) & 1) << 10) | \
		 ((((val) >> ( B9)) & 1) <<  9) | \
		 ((((val) >> ( B8)) & 1) <<  8) | \
		 ((((val) >> ( B7)) & 1) <<  7) | \
		 ((((val) >> ( B6)) & 1) <<  6) | \
		 ((((val) >> ( B5)) & 1) <<  5) | \
		 ((((val) >> ( B4)) & 1) <<  4) | \
		 ((((val) >> ( B3)) & 1) <<  3) | \
		 ((((val) >> ( B2)) & 1) <<  2) | \
		 ((((val) >> ( B1)) & 1) <<  1) | \
		 ((((val) >> ( B0)) & 1) <<  0))

#ifdef __cplusplus
}
#endif
