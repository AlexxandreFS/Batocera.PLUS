#ifndef DLG_DSW
#define DLG_DSW

#include "dsw.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct DSW
{
   char *DSWName;		// Switch or setting name
   UINT8 bits;			// Switch bitmask or setting bitpattern
   UINT8 values;		// Number of settings defined for this switch
} DSW;

typedef struct DSTAT
{
   UINT8 pos;			//
   UINT8 offset;		//
} DSTAT;

typedef struct DIPSW
{
   UINT8 value;			// Current value
   UINT8 def;			// Default value (factory setting)
   UINT32 count;			// Items in diplist
   UINT32 address;		// RAM[] address to place dsw
   DSW   diplist[64];
   UINT32 statcount;		// Items in statlist
   DSTAT statlist[16];
} DIPSW;

struct DIPSW dipswitch[MAX_DIPSWITCHES];

int dsw_select_proc(int msg, DIALOG *d, int c);
char *dswlist_getter(int index, int *list_size);
int dsw_edit_proc(int msg, DIALOG *d, int c);
void DoDSWEdit(void);
int dsw_reset_proc(int msg, DIALOG *d, int c);

extern DIALOG dsw_select[];

#ifdef __cplusplus
}
#endif
#endif

