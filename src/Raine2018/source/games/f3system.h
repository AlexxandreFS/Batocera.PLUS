
#ifdef __cplusplus
extern "C" {
#endif
// sound defs
extern int max_banks_this_game; //=memory_region_length(REGION_SOUND1)/0x200000;
extern char f3_shared_ram[]; // In case a driver needs to map this...

extern int int7_active; // Triggered when the pulse irq 7 begins...
extern int f3_cycles_68000,f3_slices;

extern UINT8 *M68000ROM, *M68000RAM; // sound 68000 memory...

void f3_timer_callback(); // function to call when int7_active is true

extern struct SOUND_INFO f3_sound[];

// end of sound defs !

extern struct INPUT_INFO f3_system_inputs[];
extern struct INPUT_INFO f3_system_inputs_6_button[];
extern struct INPUT_INFO f3_system_inputs_4_player[];

void AddF3MemoryMap(UINT32 romsize);

int f3_bg0_id;
int f3_bg1_id;
int f3_bg2_id;
int f3_bg3_id;

int f3_bg5_id;
int f3_bg6_id;

// I/O controller type

#define F3_IOC_2P_3BUTTON	(0x0000)
#define F3_IOC_2P_6BUTTON	(0x0001)
#define F3_IOC_4P_3BUTTON	(0x0002)

#define F3_IOC_TRACKBALL	(0x0010)

void init_f3_system_ioc(UINT32 type);

void IntF3System(void);
void ExecuteF3SystemFrame(void);
void ExecuteF3SystemFrameB(void);
void ExecuteF3SystemFrame_NoInt5(void);
void ExecuteF3SystemFrame_NoInt5B(void);
void ExecuteF3SystemFrame_int2(void);

void F3SysEEPROMAccessMode1(UINT8 data);
void F3SysEEPROMAccessMode1B(UINT8 data);
void F3SysEEPROMAccessMode2(UINT8 data);
void setup_sound_68000();

UINT8 *F3ModData;

UINT32 ddd[32];

#ifdef __cplusplus
}
#endif
