
#ifdef __cplusplus
extern "C" {
#endif
#ifndef NBLINES

#define NBLINES 20
typedef char dz80_buff[NBLINES][60];

int process_adr(UINT8 *base, UINT16 dAddr, dz80_buff buff);
#endif



#ifdef __cplusplus
}
#endif
