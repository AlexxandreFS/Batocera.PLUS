/*
 *  Header file for the PD4990A Serial I/O calendar & clock.
 */


struct pd4990a_s
{
	int seconds;
	int minutes;
	int hours;
	int days;
	int month;
	int year;
	int weekday;
};

extern struct pd4990a_s pd4990a;

void pd4990a_addretrace (void);
void pd4990a_init(void);
UINT32 pd4990a_testbit_r(UINT32 offset );
UINT32 pd4990a_databit_r(UINT32 offset );
void pd4990a_control_16_w(UINT32 offset, UINT16 data );
void pd4990a_increment_day(void);
void pd4990a_increment_month(void);

