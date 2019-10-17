#ifndef _EEPROM_H
#define _EEPROM_H
#ifdef __cplusplus
extern "C" {
#endif
#ifndef EEPROM_H
#define EEPROM_H

struct EEPROM_interface
{
	int address_bits;	/* EEPROM has 2^address_bits cells */
	int data_bits;		/* every cell has this many bits (8 or 16) */
	char *cmd_read;		/*  read command string, e.g. "0110" */
	char *cmd_write;	/* write command string, e.g. "0111" */
	char *cmd_erase;	/* erase command string, or 0 if n/a */
	char *cmd_lock;		/* lock command string, or 0 if n/a */
	char *cmd_unlock;	/* unlock command string, or 0 if n/a */
	int enable_multi_read;/* set to 1 to enable multiple values to be read from one read command */
};

#ifndef CLEAR_LINE
#define CLEAR_LINE		0		/* clear (a fired, held or pulsed) line */
#define ASSERT_LINE     1       /* assert an interrupt immediately */
#define HOLD_LINE       2       /* hold interrupt line until enable is true */
#define PULSE_LINE		3		/* pulse interrupt line for one instruction */
#endif
void EEPROM_init(struct EEPROM_interface *interface);

void EEPROM_write_bit(int bit);
int EEPROM_read_bit(void);
void EEPROM_set_cs_line(int state);
void EEPROM_set_clock_line(int state);
UINT8 * EEPROM_get_data_pointer(int * length);

void EEPROM_load(void *file);
void EEPROM_save(void *file);

void EEPROM_set_data(UINT8 *data, int length);

extern struct EEPROM_interface eeprom_interface_93C46;

#endif

#ifdef __cplusplus
}
#endif
#endif
