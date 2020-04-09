#include "asmdefs.inc"

CODE_SEG
/******************************************************************************/
/*                                                                            */
/*                         RAINE 6x8 STRING PRINTING                          */
/*                                                                            */
/******************************************************************************/

/*

Transparent

*/

#define DEST_0		0
#define DEST_1		4
#define DEST_2		8
#define DEST_3		12
#define DEST_4		16
#define DEST_5		20

FUNC(draw_string_6x8_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx

	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	sall	$2,%eax
	movl	0xDEADBEEF(%eax),%edi
blin_00:
//	movl	32(%esp),%ecx			// cmap
	movl	$0xFFFFFFFF,%ecx		// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

6:
	xorl	%ebx,%ebx
	movb	(%esi),%bl
	subw	$0x20,%bx
	jl	8f
	jz	7f
	shl	$3,%bx

	pushl	%edi

	addl	$0xDEADBEEF,%ebx
font_00:
	movl	$8,%ebp		// Tile Height
9:
	movb	(%ebx),%al

	testb	$0x80,%al
	jz	1f
	movl	%ecx,DEST_0(%edi)
1:
	testb	$0x40,%al
	jz	1f
	movl	%ecx,DEST_1(%edi)
1:
	testb	$0x20,%al
	jz	1f
	movl	%ecx,DEST_2(%edi)
1:
	testb	$0x10,%al
	jz	1f
	movl	%ecx,DEST_3(%edi)
1:
	testb	$0x08,%al
	jz	1f
	movl	%ecx,DEST_4(%edi)
1:
	testb	$0x04,%al
	jz	1f
	movl	%ecx,DEST_5(%edi)
1:
	incl	%ebx			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_00:
	decl	%ebp
	jne	9b

	popl	%edi
7:
	incl	%esi

	addl	$24,%edi
	jmp	6b
8:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(init_str6x8asm_32)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	addl	%eax,%eax
	addl	%eax,%eax
	movl	%eax,bitw_00-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
	movl	%eax,blin_00-4

	movl	GLOBL(ingame_font),%eax	// Font
	movl	%eax,font_00-4

	ret


