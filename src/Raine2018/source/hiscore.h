
#ifdef __cplusplus
extern "C" {
#endif
#ifndef HISCORE_H
#define HISCORE_H

/* call hs_open once after loading a game */
void hs_open();
void hs_init( void );
void hs_update( void );
void hs_close( void );
void hs_load (void);

void computer_writemem_byte(int cpu, int addr, int value);
int computer_readmem_byte(int cpu, int addr);
int current_game_has_hiscores();

#endif



#ifdef __cplusplus
}
#endif
