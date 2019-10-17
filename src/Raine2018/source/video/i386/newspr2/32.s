// See newspr2.s for more comments...

// 32bpp functions

#include "asmdefs.inc"

CODE_SEG

//void Draw64x64_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap)

// In the 16bpp and 32bpp versions, I need one more register
// I can't just swap parts of ax as in the 8bpp version.
// The best choice seems to be bx so far. It will force to process
// only 4 pixels at a time, but it isn't a big deal !

#define HANDLE_4_PIXELS( base )						\
	movl	base(%esi),%eax						;\
									;\
	/* 3 instructions for 1 pixel... is there any way to do better ? */ ;\
	movb	%al,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,base*4(%edi)					;\
									;\
	movb	%ah,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,base*4+4(%edi)					;\
									;\
	bswap	%eax /* is it faster than reading twice ax ??? probably... */;\
	movb	%al,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,base*4+8(%edi)					;\
									;\
	movb	%ah,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,base*4+12(%edi)

// FlipY : just invert the order for edi
#define HANDLE_4_PIXELS_FLIPY( base )						\
	movl	base(%esi),%eax						;\
									;\
	/* 3 instructions for 1 pixel... is there any way to do better ? */ ;\
	movb	%al,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,252-base*4(%edi)					;\
									;\
	movb	%ah,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,248-base*4(%edi)					;\
									;\
	bswap	%eax /* is it faster than reading twice ax ??? probably... */;\
	movb	%al,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,244-base*4(%edi)					;\
									;\
	movb	%ah,%dl							;\
	movl	(%ecx,%edx,4),%ebx					;\
	movl	%ebx,240-base*4(%edi)


FUNC( Draw64x64_Mapped_32 )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_00:
	movl	28(%esp),%eax			// x
	movl	36(%esp),%ecx			// cmap
	leal	(%edi,%eax,4),%edi		// x (*4 in 32bpp)

	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop0		// Make sure we are aligned...

.align	8

loop0:

	HANDLE_4_PIXELS(0)
	HANDLE_4_PIXELS(4)
	HANDLE_4_PIXELS(8)
	HANDLE_4_PIXELS(12)
	HANDLE_4_PIXELS(16)
	HANDLE_4_PIXELS(20)
	HANDLE_4_PIXELS(24)
	HANDLE_4_PIXELS(28)
	HANDLE_4_PIXELS(32)
	HANDLE_4_PIXELS(36)
	HANDLE_4_PIXELS(40)
	HANDLE_4_PIXELS(44)
	HANDLE_4_PIXELS(48)
	HANDLE_4_PIXELS(52)
	HANDLE_4_PIXELS(56)
	HANDLE_4_PIXELS(60)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_00:

	decl	%ebp
	jne	loop0

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC( Draw64x64_Mapped_32_FlipY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi           // Goto the end...
blin_01:
	movl	28(%esp),%eax			// x
	movl	36(%esp),%ecx			// cmap
	leal	(%edi,%eax,4),%edi		// x (*4 in 32bpp)

	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop01		// Make sure we are aligned...

.align	8

loop01:

	HANDLE_4_PIXELS_FLIPY(0)
	HANDLE_4_PIXELS_FLIPY(4)
	HANDLE_4_PIXELS_FLIPY(8)
	HANDLE_4_PIXELS_FLIPY(12)
	HANDLE_4_PIXELS_FLIPY(16)
	HANDLE_4_PIXELS_FLIPY(20)
	HANDLE_4_PIXELS_FLIPY(24)
	HANDLE_4_PIXELS_FLIPY(28)
	HANDLE_4_PIXELS_FLIPY(32)
	HANDLE_4_PIXELS_FLIPY(36)
	HANDLE_4_PIXELS_FLIPY(40)
	HANDLE_4_PIXELS_FLIPY(44)
	HANDLE_4_PIXELS_FLIPY(48)
	HANDLE_4_PIXELS_FLIPY(52)
	HANDLE_4_PIXELS_FLIPY(56)
	HANDLE_4_PIXELS_FLIPY(60)

	addl	$64,%esi		/* Next Tile Line */
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_01:

	decl	%ebp
	jne	loop01

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC( Draw64x64_Mapped_32_FlipX )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_02:
	movl	28(%esp),%eax			// x
	movl	36(%esp),%ecx			// cmap
	leal	(%edi,%eax,4),%edi		// x (*4 in 32bpp)

	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop02		// Make sure we are aligned...

.align	8

loop02:

	HANDLE_4_PIXELS(0)
	HANDLE_4_PIXELS(4)
	HANDLE_4_PIXELS(8)
	HANDLE_4_PIXELS(12)
	HANDLE_4_PIXELS(16)
	HANDLE_4_PIXELS(20)
	HANDLE_4_PIXELS(24)
	HANDLE_4_PIXELS(28)
	HANDLE_4_PIXELS(32)
	HANDLE_4_PIXELS(36)
	HANDLE_4_PIXELS(40)
	HANDLE_4_PIXELS(44)
	HANDLE_4_PIXELS(48)
	HANDLE_4_PIXELS(52)
	HANDLE_4_PIXELS(56)
	HANDLE_4_PIXELS(60)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xDEADBEEF,%edi	// Prev Screen Line
bitw_02:

	decl	%ebp
	jne	loop02

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC( Draw64x64_Mapped_32_FlipXY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_03:
	movl	28(%esp),%eax			// x
	movl	36(%esp),%ecx			// cmap
	leal	(%edi,%eax,4),%edi		// x (*4 in 32bpp)

	xorl	%edx,%edx

	movl	$64,%ebp	// Tile Height
	jmp	loop03		// Make sure we are aligned...

.align	8

loop03:

	HANDLE_4_PIXELS_FLIPY(0)
	HANDLE_4_PIXELS_FLIPY(4)
	HANDLE_4_PIXELS_FLIPY(8)
	HANDLE_4_PIXELS_FLIPY(12)
	HANDLE_4_PIXELS_FLIPY(16)
	HANDLE_4_PIXELS_FLIPY(20)
	HANDLE_4_PIXELS_FLIPY(24)
	HANDLE_4_PIXELS_FLIPY(28)
	HANDLE_4_PIXELS_FLIPY(32)
	HANDLE_4_PIXELS_FLIPY(36)
	HANDLE_4_PIXELS_FLIPY(40)
	HANDLE_4_PIXELS_FLIPY(44)
	HANDLE_4_PIXELS_FLIPY(48)
	HANDLE_4_PIXELS_FLIPY(52)
	HANDLE_4_PIXELS_FLIPY(56)
	HANDLE_4_PIXELS_FLIPY(60)

	addl	$64,%esi		/* Next Tile Line */
	subl	$0xDEADBEEF,%edi	// Prev Screen Line
bitw_03:

	decl	%ebp
	jne	loop03

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

/************************************************************
Notice : for now, I don't translate the Trans version of the
64x64 functions. I am not sure they will be usefull...
************************************************************/

// These are functions called by the f3 games (not all of them)
// They basically draw a sprite of 8 pixels wide and with an arbitrary heigh

// void Draw8xH_Trans_Packed_Mapped(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)

// What was supposed to happen has finally happened : I am out of registers!
// I need to create a counter in memory instead of using ebp for the height
// of the sprite. cx will be used for reading the palette...

counter:	.long	 0

FUNC( Draw8xH_Trans_Packed_Mapped_32 )
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
	movl	28(%esp),%eax			// +x
	movl	40(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x doubled in 16bpp

	xorl	%edx,%edx

	// Tsss 2 instructions for memory -> memory transfer...
	movl	36(%esp),%eax		// Tile Height
	movl	%eax,counter

	jmp	loop20			// Alignement

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
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_20:

	decl	counter
	jne	loop20

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

//void Draw8xH_Trans_Packed_Mapped_FlipY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap)

FUNC( Draw8xH_Trans_Packed_Mapped_32_FlipY )
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
	movl	28(%esp),%eax			// +x
	movl	40(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x doubled in 16bpp
	xorl	%edx,%edx

	movl	36(%esp),%eax	// Tile Height
	movl	%eax,counter
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
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	addl	$0xdeadbeef,%edi	/* Next Screen Line */
bitw_21:

	decl	counter
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
FUNC( Draw8xH_Trans_Packed_Mapped_32_FlipX )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	36(%esp),%eax	// Tile Height
	movl	%eax,counter
	addl	%ebp,%eax			// tile height
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_22:
	movl	28(%esp),%eax			// +x
	movl	40(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x doubled in 16bpp
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
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* Previous Screen Line */
bitw_22:

	decl	counter
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
FUNC( Draw8xH_Trans_Packed_Mapped_32_FlipXY )
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx

	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	36(%esp),%eax	// Tile Height
	movl	%eax,counter
	addl	%ebp,%eax			// tile height
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_23:
	movl	28(%esp),%eax			// +x
	movl	40(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x doubled in 16bpp
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
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
8:
	addl	$4,%esi		/* Next Tile Line */
	subl	$0xdeadbeef,%edi	/* Previous Screen Line */
bitw_23:

	decl	counter
	jne	loop23

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(init_newspr2asm_32)
	movl	GLOBL(GameBitmap),%eax	// Adress of the GameBitmap's structure
	movl	(%eax),%eax			// Width
	addl	%eax,%eax
	addl	%eax,%eax			// *4 for 32bpp
	movl	%eax,bitw_00-4
	movl	%eax,bitw_01-4
	movl	%eax,bitw_02-4
	movl	%eax,bitw_03-4

	//movl	%eax,bitw_10-4
	//movl	%eax,bitw_11-4
	//movl	%eax,bitw_12-4
	//movl	%eax,bitw_13-4

	movl	%eax,bitw_20-4
	movl	%eax,bitw_21-4
	movl	%eax,bitw_22-4
	movl	%eax,bitw_23-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax			// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4

	//movl	%eax,blin_10-4
	//movl	%eax,blin_11-4

	movl	%eax,blin_20-4
	movl	%eax,blin_21-4

	pushl	%eax
	addl	$63*4,%eax			// Line 63 !!!
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4

	//movl	%eax,blin_12-4
	//movl	%eax,blin_13-4
	popl	%eax

	subl	$1*4,%eax			// This time line 7 really!
	movl	%eax,blin_22-4
	movl	%eax,blin_23-4
	ret
