/* Let's convert this to pure asm... */

// Only used Space Gun and othunder
// In fact the drivers use the zoom and zoom2 functions in spr64.c, which
// call these functions when no zoom is actually needed !

// 8bpp functions

#include "asmdefs.inc"

CODE_SEG

// Macro used to handle 8 pixels in the Draw64x64 function
// Thanks to the ';' it is much more readable now !

// Notice that emacs takes the ';' as a comment... IT IS NOT a comment !

#define HANDLE_8_PIXELS( base )						\
	movl	base(%esi),%eax	;					\
	movl	base+4(%esi),%ebx;					\
									\
	/* Still 3 instructions for 1 pixel (see 16bpp) */		\
	/* Actually that's a little more because of the bswaps... */	\
									\
	movb	%al,%dl	;						\
	movb	(%ecx,%edx,1),%al ;					\
	movb	%bl,%dl	;						\
	movb	(%ecx,%edx,1),%bl ;					\
	movb	%ah,%dl	;						\
	movb	(%ecx,%edx,1),%ah ;					\
	movb	%bh,%dl	;						\
	movb	(%ecx,%edx,1),%bh ;					\
									\
	bswap	%eax		;					\
	bswap	%ebx		;					\
									\
	movb	%al,%dl	;						\
	movb	(%ecx,%edx,1),%al ;					\
	movb	%bl,%dl	;						\
	movb	(%ecx,%edx,1),%bl ;					\
	movb	%ah,%dl	;						\
	movb	(%ecx,%edx,1),%ah ;					\
	movb	%bh,%dl	;						\
	movb	(%ecx,%edx,1),%bh ;					\
									\
	bswap	%eax		;					\
	bswap	%ebx		;					\
									\
	movl	%eax,base(%edi)	;					\
	movl	%ebx,base+4(%edi)	;

// Now the FlipY version. The same except edi is accessed the other way
// around...

// I am not sure this macro works actually : it writes 4 pixels in a row
// without flipping them, but flips groups of 4 pixels. Almost sure it
// does not work. Might be a good idea to test this, but it will probably
// be easier to do it with the _Rot interface, or only to remove these
// functions completely and replace them by 16x16 drawing...
#define HANDLE_8_PIXELS_FLIPY( base )					\
	movl	base(%esi),%eax	;					\
	movl	base+4(%esi),%ebx;					\
									\
	/* Still 3 instructions for 1 pixel (see 16bpp) */		\
	/* Actually that's a little more because of the bswaps... */	\
									\
	movb	%al,%dl	;						\
	movb	(%ecx,%edx,1),%al ;					\
	movb	%bl,%dl	;						\
	movb	(%ecx,%edx,1),%bl ;					\
	movb	%ah,%dl	;						\
	movb	(%ecx,%edx,1),%ah ;					\
	movb	%bh,%dl	;						\
	movb	(%ecx,%edx,1),%bh ;					\
									\
	bswap	%eax		;					\
	bswap	%ebx		;					\
									\
	movb	%al,%dl	;						\
	movb	(%ecx,%edx,1),%al ;					\
	movb	%bl,%dl	;						\
	movb	(%ecx,%edx,1),%bl ;					\
	movb	%ah,%dl	;						\
	movb	(%ecx,%edx,1),%ah ;					\
	movb	%bh,%dl	;						\
	movb	(%ecx,%edx,1),%bh ;					\
									\
	bswap	%eax		;					\
	bswap	%ebx		;					\
									\
	movl	%eax,60-base(%edi);					\
	movl	%ebx,56-base(%edi)	;

//void Draw64x64_Mapped(UINT8 *SPR, int x, int y, UINT8 *cmap)

FUNC( Draw64x64_Mapped_8 )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	// A nice mess to convert to 16bpp with all these registers !
	// Yes let's remove these and use Draw16x16 instead !!!

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_00:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop0		// Alignement

.align	8
loop0:
	HANDLE_8_PIXELS(0)
	HANDLE_8_PIXELS(8)
	HANDLE_8_PIXELS(16)
	HANDLE_8_PIXELS(24)
	HANDLE_8_PIXELS(32)
	HANDLE_8_PIXELS(40)
	HANDLE_8_PIXELS(48)
	HANDLE_8_PIXELS(56)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_00:

	decl	%ebp
	jne	loop0
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw64x64_Mapped_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
// Exactly the same function as before. It just uses another macro...

FUNC( Draw64x64_Mapped_8_FlipY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_01:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop1		// Alignement

.align	8
loop1:
	HANDLE_8_PIXELS_FLIPY(0)
	HANDLE_8_PIXELS_FLIPY(8)
	HANDLE_8_PIXELS_FLIPY(16)
	HANDLE_8_PIXELS_FLIPY(24)
	HANDLE_8_PIXELS_FLIPY(32)
	HANDLE_8_PIXELS_FLIPY(40)
	HANDLE_8_PIXELS_FLIPY(48)
	HANDLE_8_PIXELS_FLIPY(56)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_01:

	decl	%ebp
	jne	loop1

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

// void Draw64x64_Mapped_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
// This time we use the first macro, but we put the results backwards in the
// screen buffer...

FUNC( Draw64x64_Mapped_8_FlipX )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi	// This time we start at the end
blin_02:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop2		// Alignement

.align	8
loop2:
	HANDLE_8_PIXELS(0)
	HANDLE_8_PIXELS(8)
	HANDLE_8_PIXELS(16)
	HANDLE_8_PIXELS(24)
	HANDLE_8_PIXELS(32)
	HANDLE_8_PIXELS(40)
	HANDLE_8_PIXELS(48)
	HANDLE_8_PIXELS(56)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* prev Screen Line */
bitw_02:

	decl	%ebp
	jne	loop2

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw64x64_Mapped_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
// Combination of the 2 last functions : backwards, using the 2nd macro !

FUNC( Draw64x64_Mapped_8_FlipXY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi	// This time we start at the end
blin_03:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop3		// Alignement

.align	8
loop3:
	HANDLE_8_PIXELS_FLIPY(0)
	HANDLE_8_PIXELS_FLIPY(8)
	HANDLE_8_PIXELS_FLIPY(16)
	HANDLE_8_PIXELS_FLIPY(24)
	HANDLE_8_PIXELS_FLIPY(32)
	HANDLE_8_PIXELS_FLIPY(40)
	HANDLE_8_PIXELS_FLIPY(48)
	HANDLE_8_PIXELS_FLIPY(56)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* prev Screen Line */
bitw_03:

	decl	%ebp
	jne	loop3

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

/********************************************************************/

// Transparency. This requires 2 new macros.
// The screen is filled byte per byte now...

#define HANDLE_8_PIXELS_TRANSP(base) \
	movl	base(%esi),%eax	;		\
	movl	base+4(%esi),%ebx ;		\
						\
	cmpb	%dh,%al		;  /* 0 ? */	\
	je	7f		;		\
	movb	%al,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base(%edi)	;		\
7:	cmpb	%dh,%bl		;		\
	je	7f		;		\
	movb	%bl,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+4(%edi);		\
7:	cmpb	%dh,%ah		;		\
	je	7f		;		\
	movb	%ah,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+1(%edi);		\
7:	cmpb	%dh,%bh		;		\
	je	7f		;		\
	movb	%bh,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+5(%edi) ;		\
7:						\
	shr	$16,%eax	;		\
	shr	$16,%ebx	;		\
						\
	cmpb	%dh,%al		;		\
	je	7f		;		\
	movb	%al,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+2(%edi) ;		\
7:	cmpb	%dh,%bl		;		\
	je	7f		;		\
	movb	%bl,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+6(%edi) ;		\
7:	cmpb	%dh,%ah		;		\
	je	7f		;		\
	movb	%ah,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+3(%edi) ;		\
7:	cmpb	%dh,%bh		;		\
	je	7f		;		\
	movb	%bh,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,base+7(%edi) ;		\
7:

// flipy : the same but from 63 to 0
#define HANDLE_8_PIXELS_TRANSP_FLIPY(base) \
	movl	base(%esi),%eax	;		\
	movl	base+4(%esi),%ebx ;		\
						\
	cmpb	%dh,%al		;  /* 0 ? */	\
	je	7f		;		\
	movb	%al,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-base(%edi)	;		\
7:	cmpb	%dh,%bl		;		\
	je	7f		;		\
	movb	%bl,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-4-base(%edi);		\
7:	cmpb	%dh,%ah		;		\
	je	7f		;		\
	movb	%ah,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-1-base(%edi);		\
7:	cmpb	%dh,%bh		;		\
	je	7f		;		\
	movb	%bh,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-5-base(%edi) ;		\
7:						\
	shr	$16,%eax	;		\
	shr	$16,%ebx	;		\
						\
	cmpb	%dh,%al		;		\
	je	7f		;		\
	movb	%al,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-2-base(%edi) ;		\
7:	cmpb	%dh,%bl		;		\
	je	7f		;		\
	movb	%bl,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-6-base(%edi) ;		\
7:	cmpb	%dh,%ah		;		\
	je	7f		;		\
	movb	%ah,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-base-3(%edi) ;		\
7:	cmpb	%dh,%bh		;		\
	je	7f		;		\
	movb	%bh,%dl		;		\
	movb	(%ecx,%edx,1),%al ;		\
	movb	%al,63-base-7(%edi) ;		\
7:

//void Draw64x64_Trans_Mapped(UINT8 *SPR, int x, int y, UINT8 *cmap)
FUNC( Draw64x64_Trans_Mapped_8 )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_10:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop10		// Alignement

.align	8
loop10:
	HANDLE_8_PIXELS_TRANSP(0)
	HANDLE_8_PIXELS_TRANSP(8)
	HANDLE_8_PIXELS_TRANSP(16)
	HANDLE_8_PIXELS_TRANSP(24)
	HANDLE_8_PIXELS_TRANSP(32)
	HANDLE_8_PIXELS_TRANSP(40)
	HANDLE_8_PIXELS_TRANSP(48)
	HANDLE_8_PIXELS_TRANSP(56)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_10:

	decl	%ebp
	jne	loop10

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw64x64_Trans_Mapped_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
FUNC( Draw64x64_Trans_Mapped_8_FlipY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_11:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop11		// Alignement

.align	8
loop11:
	HANDLE_8_PIXELS_TRANSP_FLIPY(0)
	HANDLE_8_PIXELS_TRANSP_FLIPY(8)
	HANDLE_8_PIXELS_TRANSP_FLIPY(16)
	HANDLE_8_PIXELS_TRANSP_FLIPY(24)
	HANDLE_8_PIXELS_TRANSP_FLIPY(32)
	HANDLE_8_PIXELS_TRANSP_FLIPY(40)
	HANDLE_8_PIXELS_TRANSP_FLIPY(48)
	HANDLE_8_PIXELS_TRANSP_FLIPY(56)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_11:

	decl	%ebp
	jne	loop11

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

// void Draw64x64_Trans_Mapped_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
FUNC( Draw64x64_Trans_Mapped_8_FlipX )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi	// This time we start at the end
blin_12:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop12		// Alignement

.align	8
loop12:
	HANDLE_8_PIXELS_TRANSP(0)
	HANDLE_8_PIXELS_TRANSP(8)
	HANDLE_8_PIXELS_TRANSP(16)
	HANDLE_8_PIXELS_TRANSP(24)
	HANDLE_8_PIXELS_TRANSP(32)
	HANDLE_8_PIXELS_TRANSP(40)
	HANDLE_8_PIXELS_TRANSP(48)
	HANDLE_8_PIXELS_TRANSP(56)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* prev Screen Line */
bitw_12:

	decl	%ebp
	jne	loop12

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw64x64_Trans_Mapped_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
// Combination of the 2 last functions : backwards, using the 2nd macro !

FUNC( Draw64x64_Trans_Mapped_8_FlipXY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi	// This time we start at the end
blin_13:
	movl	36(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop13		// Alignement

.align	8
loop13:
	HANDLE_8_PIXELS_TRANSP_FLIPY(0)
	HANDLE_8_PIXELS_TRANSP_FLIPY(8)
	HANDLE_8_PIXELS_TRANSP_FLIPY(16)
	HANDLE_8_PIXELS_TRANSP_FLIPY(24)
	HANDLE_8_PIXELS_TRANSP_FLIPY(32)
	HANDLE_8_PIXELS_TRANSP_FLIPY(40)
	HANDLE_8_PIXELS_TRANSP_FLIPY(48)
	HANDLE_8_PIXELS_TRANSP_FLIPY(56)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* prev Screen Line */
bitw_13:

	decl	%ebp
	jne	loop13

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

/************************************************************/

// These are functions called by the f3 games (not all of them)
// They basically draw a sprite of 8 pixels wide and with an arbitrary heigh

// void Draw8xH_Trans_Packed_Mapped(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)

FUNC( Draw8xH_Trans_Packed_Mapped_8 )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_20:
	movl	40(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	36(%esp),%ebp	// Tile Height
	jmp	loop20		// Alignement

.align	8

loop20:
	movl	(%esi),%eax
	testl	%eax,%eax		// Skip Blank Lines
	jz	8f
	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax
	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,6(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_20:

	decl	%ebp
	jne	loop20

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw8xH_Trans_Packed_Mapped_FlipY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)

FUNC( Draw8xH_Trans_Packed_Mapped_8_FlipY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	push	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_21:
	movl	40(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	movl	36(%esp),%ebp	// Tile Height
	jmp	loop21		// Alignement

.align	8

loop21:
	movl	(%esi),%eax
	testl	%eax,%eax		// Skip Blank Lines
	jz	8f
	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,7(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,4(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,3(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,1(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_21:

	decl	%ebp
	jne	loop21

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

/* The same as the normal Mapped function but :
   begins at the last line and goes back to the begining (subl) */

//void Draw8xH_Trans_Packed_Mapped_FlipX(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)
FUNC( Draw8xH_Trans_Packed_Mapped_8_FlipX )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	36(%esp),%ebp	// Tile Height
	addl	%ebp,%eax			// tile height
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_22:
	movl	40(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	jmp	loop22		// Alignement

.align	8

loop22:
	movl	(%esi),%eax
	testl	%eax,%eax		// Skip Blank Lines
	jz	8f
	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,6(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* Previous Screen Line */
bitw_22:

	decl	%ebp
	jne	loop22

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

/* The 2 previous functions combined :
   starts at last line and goes back
   x offsets are taken backward (from 7 to 0) */

//void Draw8xH_Trans_Packed_Mapped_FlipXY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)
FUNC( Draw8xH_Trans_Packed_Mapped_8_FlipXY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	36(%esp),%ebp	// Tile Height
	addl	%ebp,%eax			// tile height
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_23:
	movl	40(%esp),%ecx			// cmap
	addl	28(%esp),%edi			// +x
	xorl	%edx,%edx

	jmp	loop23		// Alignement

.align	8

loop23:
	movl	(%esi),%eax
	testl	%eax,%eax		// Skip Blank Lines
	jz	8f
	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,7(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,4(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,3(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ecx,%edx,1),%al
	movb	%al,1(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* Previous Screen Line */
bitw_23:

	decl	%ebp
	jne	loop23

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(init_newspr2asm)
	movl	GLOBL(GameBitmap),%eax	// Adress of the GameBitmap's structure
	movl	(%eax),%eax			// Width
	movl	%eax,bitw_00-4
	movl	%eax,bitw_01-4
	movl	%eax,bitw_02-4
	movl	%eax,bitw_03-4

	movl	%eax,bitw_10-4
	movl	%eax,bitw_11-4
	movl	%eax,bitw_12-4
	movl	%eax,bitw_13-4

	movl	%eax,bitw_20-4
	movl	%eax,bitw_21-4
	movl	%eax,bitw_22-4
	movl	%eax,bitw_23-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax			// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4

	movl	%eax,blin_10-4
	movl	%eax,blin_11-4

	movl	%eax,blin_20-4
	movl	%eax,blin_21-4

	pushl	%eax
	addl	$63*4,%eax			// Line 63 !!!
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4

	movl	%eax,blin_12-4
	movl	%eax,blin_13-4
	popl	%eax

	subl	$1*4,%eax
	// We must point to the last line of the bitmap.
	// To speed things up we are doing (bitmap-1)+h instead of
	// bitmap+(h-1).
	// This will work as long as no one passes height=0 !
	movl	%eax,blin_22-4
	movl	%eax,blin_23-4
	ret
