
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************
*
* eagle.h
*
* eagle header for use with DJGPP
* needs eagle.o to link
*
* Date : 15 September 1998
*
* Eagle Version : 0.40
*
* Includes the MMX version (autodetect)
*
* Please distribute this file with the complete eagle package
*
**************************************************************/

#ifdef RAINE_UNIX
// Stupid dos assembler, here is the easiest fix
#define eagle _eagle
#define eagle_mmx16 _eagle_mmx16
// The bmp version is useless, I wonder why I keep it ?!!
#define eagle_bmp _eagle_bmp
#endif

extern void eagle
    ( 	unsigned long *lb,
		unsigned long *lb2,
		short width,
		int destination_segment,
		int screen_address1,
		int screen_address2 );

extern void eagle_mmx16
    ( 	unsigned long *lb,
		unsigned long *lb2,
		short width,
		int destination_segment,
		int screen_address1,
		int screen_address2 );

extern void eagle_bmp
    ( 	unsigned long *lb,
		unsigned long *lb2,
		short width,
		int destination_segment,
		int screen_address1,
		int screen_address2 );


#ifdef __cplusplus
}
#endif
