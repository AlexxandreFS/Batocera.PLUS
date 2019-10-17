#include "asmdefs.inc"

CODE_SEG

FUNC(Move8x8_16)
FUNC(Move8x8_16_FlipX)
FUNC(Move8x8_16_FlipY)
FUNC(Move8x8_16_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_00:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x
	movl	$8,%ecx

9:
	movsl	// 2 pixels
	movsl
	movsl
	movsl

	addl	$0xDEADBEEF,%esi	// Next Screen Line
bitw_00:
	addl	$0xDEADBEEF,%edi
bitw_01:

	loop	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Move8x8_8)
FUNC(Move8x8_8_FlipX)
FUNC(Move8x8_8_FlipY)
FUNC(Move8x8_8_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_01:
	addl	20(%esp),%edi			// x
	movl	$8,%ecx

9:
	movsl	// 4 pixels !
	movsl

	addl	$0xDEADBEEF,%esi	// Next Screen Line
bitw_02:
	addl	$0xDEADBEEF,%edi
bitw_03:

	loop	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Move8x8_32)
FUNC(Move8x8_32_FlipX)
FUNC(Move8x8_32_FlipY)
FUNC(Move8x8_32_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_02:
	movl	20(%esp),%eax			// x
	roll	$2,%eax
	addl	%eax,%edi			// x
	movl	$8,%ecx

9:
	movsl	// 1 pixel :-(
	movsl
	movsl
	movsl

	movsl
	movsl
	movsl
	movsl

	addl	$0xDEADBEEF,%esi	// Next Screen Line
bitw_04:
	addl	$0xDEADBEEF,%edi
bitw_05:

	loop	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_moveasm)

	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	subl	$8,%eax
	movl	%eax,bitw_02-4
	movl	%eax,bitw_03-4

	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	addl	%eax,%eax	// double for 16 bits
	subl	$16,%eax	// width of a sprite
	movl	%eax,bitw_00-4
	movl	%eax,bitw_01-4

	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	roll	$2,%eax	// 4x for 32 bits
	subl	$32,%eax	// width of a sprite
	movl	%eax,bitw_04-4
	movl	%eax,bitw_05-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4
	movl	%eax,blin_02-4
	ret
