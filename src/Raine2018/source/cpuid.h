
#ifdef __cplusplus
extern "C" {
#endif

#undef CPU_MMX

  /* Allegro defines custom cpu flags !!!
     Allegro wants custom flags everywhere... what a mess...
     These are the standard cpuid bits (cpuid 1) that raine uses.
     Taken from include/asm-i386/cpufeature.h in the linux kernel */
#define CPU_MMX (1<<23)
#define CPU_TSC (1<<4)

extern UINT32 raine_cpu_capabilities;
extern void get_cpu_name(char *my_model);


#ifdef __cplusplus
}
#endif
