
#ifdef __cplusplus
extern "C" {
#endif
#ifndef YM2151INTF_H
#define YM2151INTF_H

#include "mame/handlers.h"

#define MAX_2151 2

struct YM2151interface
{
	int num;
	int baseclock;
	int volume[MAX_2151]; /* need for use YM3012()_VOL macro */
	void (*irqhandler[MAX_2151])(int irq);
	mem_write_handler portwritehandler[MAX_2151];
};

READ_HANDLER( YM2151_status_port_0_r );
READ_HANDLER( YM2151_status_port_1_r );
READ_HANDLER( YM2151_status_port_2_r );

WRITE_HANDLER( YM2151_register_port_0_w );
WRITE_HANDLER( YM2151_register_port_1_w );
WRITE_HANDLER( YM2151_register_port_2_w );

WRITE_HANDLER( YM2151_data_port_0_w );
WRITE_HANDLER( YM2151_data_port_1_w );
WRITE_HANDLER( YM2151_data_port_2_w );
int YM2151_sh_start(const struct YM2151interface *msound);
int YM2151_ALT_sh_start(const struct YM2151interface *msound);
void YM2151_sh_stop(void);
void YM2151_sh_reset(void);

void YM2151UpdateRequest(int chip);
#endif

#ifdef __cplusplus
}
#endif
