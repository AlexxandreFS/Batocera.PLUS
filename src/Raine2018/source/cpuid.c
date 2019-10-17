/* The following cpuid functions are extracted from the linux kernel source, a reference
   for this kind of problems ! Thanks to them...
   When the cpu does not contain its name then it's usually an "old" cpu, and we can
   extract its name from cputable.h (found in the sources of mplayer, but it comes from
   somewhere else, clearly).

   I try to avoid to use the cpu_xxxx variables from allegro because they are not
   initialised when the library is compiled without asm, and it happens very often
   in the linux distributions...
*/

#include "deftypes.h"
#include "cputable.h"
#include <string.h>
#include <stdio.h>
#ifdef SDL
#include <SDL_cpuinfo.h>
#endif
#include "cpuid.h"

UINT32 raine_cpu_capabilities;
/*
 * Generic CPUID function
 */
#ifndef NO_ASM
static inline void cpuid(int op, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
        __asm__("pushl %%ebx \n\t" /* saves ebx */
		"cpuid \n\t"
		"movl %%ebx, %%esi \n\t" /* saves what cpuid just put in ebx */
		"popl %%ebx \n\t" /* restore the old ebx */
                : "=a" (*eax),
                  "=S" (*ebx),
                  "=c" (*ecx),
                  "=d" (*edx)
                : "0" (op));
}

/*
 * CPUID functions returning a single datum
 */
static inline unsigned int cpuid_eax(unsigned int op)
{
        unsigned int eax;

        __asm__("pushl %%ebx; cpuid; popl %%ebx"
                : "=a" (eax)
                : "0" (op)
                : "dx");
        return eax;
}

/* Standard macro to see if a specific flag is changeable */
static inline int flag_is_changeable_p(UINT32 flag)
{
	UINT32 f1, f2;

	asm("pushfl\n\t"
	    "pushfl\n\t"
	    "popl %0\n\t"
	    "movl %0,%1\n\t"
	    "xorl %2,%0\n\t"
	    "pushl %0\n\t"
	    "popfl\n\t"
	    "pushfl\n\t"
	    "popl %0\n\t"
	    "popfl\n\t"
	    : "=&r" (f1), "=&r" (f2)
	    : "ir" (flag));

	return ((f1^f2) & flag) != 0;
}

/* Probe for the CPUID instruction */

#define X86_EFLAGS_ID   0x00200000 /* CPUID detection flag */

static int have_cpuid_p(void)
{
	return flag_is_changeable_p(X86_EFLAGS_ID);
}

static int get_model_name(char *modelname)
{
	unsigned int *v;
	char *p, *q;

	if (cpuid_eax(0x80000000) < 0x80000004)
		return 0;

	v = (unsigned int *) modelname;
	cpuid(0x80000002, &v[0], &v[1], &v[2], &v[3]);
	cpuid(0x80000003, &v[4], &v[5], &v[6], &v[7]);
	cpuid(0x80000004, &v[8], &v[9], &v[10], &v[11]);
	modelname[48] = 0;

	/* Intel chips right-justify this string for some dumb reason;
	   undo that brain damage */
	p = q = &modelname[0];
	while ( *p == ' ' )
	     p++;
	if ( p != q ) {
	     while ( *p )
		  *q++ = *p++;
	     while ( q <= &modelname[48] )
		  *q++ = '\0';	/* Zero-pad the rest */
	}
	// And remove eventual spaces at the end...
	p = q = &modelname[strlen(modelname)-1];
	while (*p == ' ' && p > &modelname[0])
	    p--;
	if (p != q)
	    p[1] = 0;

	return 1;
}
#endif

void get_cpu_name(char *my_model) {
  raine_cpu_capabilities = 0;
#ifndef NO_ASM
  if (have_cpuid_p()) {
    UINT32 cpu_family,cpuid_level,tfms,cpu_model,junk;
    int cpu_vendor = -1,i;
    char vendor_id[16];
    /* Get vendor name */
    cpuid(0x00000000, &cpuid_level,
	  (unsigned int *)&vendor_id[0],
	  (unsigned int *)&vendor_id[8],
	  (unsigned int *)&vendor_id[4]);

    vendor_id[12] = 0;

    /* Intel-defined flags: level 0x00000001 */
    if ( cpuid_level >= 0x00000001 ) {
      cpuid(0x00000001, &tfms, &junk, &junk,
	    &raine_cpu_capabilities);
      // Not used yet. Might be used one day to include amd specific features
      // but rather unlikely (raine will never emulate any 3dnow stuff)
      // fprintf(stderr,"CPU vendor_id : %s\n",vendor_id);
/*       fprintf(stderr,"CPU capabilities : "); */
/*       for (i=0; i<=31; i++) { */
/* 	if (raine_cpu_capabilities & (1<<i)) { */
/* 	  fprintf(stderr,"%02d ",i); */
/* 	} */
/*       } */
/*       fprintf(stderr,"\n"); */
      cpu_family = (tfms >> 8) & 15;
      cpu_model = (tfms >> 4) & 15;
    } else {
      /* Have CPUID level 0 only - unheard of */
      cpu_family = 4;
    }

    if (!get_model_name(my_model)) {

      for (i=0; i<MAX_VENDORS; i++)
	if (!strcmp(vendor_id,cpuvendors[i].string)) {
	  cpu_vendor = i;
	  break;
	}

      if (cpu_vendor > -1)
	strcpy(my_model,cpuname[cpu_vendor][cpu_family][cpu_model]);
      else
	*my_model = 0;
      if (!*my_model)
	sprintf(my_model,"%s family %d model %d",vendor_id,cpu_family,cpu_model);
    }
  }
#elif defined(SDL)
  if (SDL_HasRDTSC()) raine_cpu_capabilities |= CPU_TSC;
  if (SDL_HasMMX()) raine_cpu_capabilities |= CPU_MMX;
#endif
}
