/******************************************************************************/
/*                                                                            */
/*                          RAINE 8x8 TILE DRAWING                            */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

#include "asmdefs.inc"

CODE_SEG
#define DEST_0		0
#define DEST_1		4
#define DEST_2		8
#define DEST_3		12
#define DEST_4		16
#define DEST_5		20
#define DEST_6		24
#define DEST_7		28

FUNC(Draw8x8_Mapped_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_00:
	movl	%edx,endc_00-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_0(%edi)
	movl	%edx,DEST_4(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_1(%edi)
	movl	%edx,DEST_5(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_2(%edi)
	movl	%edx,DEST_6(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_3(%edi)
	movl	%edx,DEST_7(%edi)

	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_00:
	cmp	$0xDEADBEEF,%esi
endc_00:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Mapped_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_01:
	movl	%edx,endc_01-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_7(%edi)
	movl	%edx,DEST_3(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_6(%edi)
	movl	%edx,DEST_2(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_5(%edi)
	movl	%edx,DEST_1(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_4(%edi)
	movl	%edx,DEST_0(%edi)

	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_01:
	cmp	$0xDEADBEEF,%esi
endc_01:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Mapped_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_02:
	movl	%edx,endc_02-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_0(%edi)
	movl	%edx,DEST_4(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_1(%edi)
	movl	%edx,DEST_5(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_2(%edi)
	movl	%edx,DEST_6(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_3(%edi)
	movl	%edx,DEST_7(%edi)

	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_02:
	cmp	$0xDEADBEEF,%esi
endc_02:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Mapped_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_03:
	movl	%edx,endc_03-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_7(%edi)
	movl	%edx,DEST_3(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_6(%edi)
	movl	%edx,DEST_2(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_5(%edi)
	movl	%edx,DEST_1(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_4(%edi)
	movl	%edx,DEST_0(%edi)

	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_03:
	cmp	$0xDEADBEEF,%esi
endc_03:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Mapped_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_04:
	movl	%edx,endc_04-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movw	(%edi),%dx
	movb	(%esi),%al
	movw	14(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_0(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_4(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_5(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_6(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_3(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_7(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_04:
	cmp	$0xDEADBEEF,%esi
endc_04:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Mapped_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_05:
	movl	%edx,endc_05-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movw	(%edi),%dx
	movb	(%esi),%al
	movw	14(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_7(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_3(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_2(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_1(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_0(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_05:
	cmp	$0xDEADBEEF,%esi
endc_05:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Mapped_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_06:
	movl	%edx,endc_06-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movw	(%edi),%dx
	movb	(%esi),%al
	movw	14(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_0(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_4(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_5(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_6(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_3(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_7(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_06:
	cmp	$0xDEADBEEF,%esi
endc_06:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Mapped_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_07:
	movl	%edx,endc_07-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movw	(%edi),%dx
	movb	(%esi),%al
	movw	14(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_7(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_3(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_2(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_1(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_0(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_07:
	cmp	$0xDEADBEEF,%esi
endc_07:
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_32)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_08:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$0xDEADBEEF,%edx		// screen width
bitw_08:
	mov	%ax,%cx				// cmap
/*
	// This is an mmx version... It is faster? Not really :(

	movl	%ecx,DEST_0(%edi)
	movl	%ecx,DEST_2(%edi)
	movq	(%edi),%mm4

	movq	(%esi),%mm0
	movq	8(%esi),%mm1

	por	%mm4,%mm0
	por	%mm4,%mm1

	movq	16(%esi),%mm2
	movq	24(%esi),%mm3

	por	%mm4,%mm2
	por	%mm4,%mm3

	movq	%mm0,DEST_0(%edi)
	addl	%edx,%edi
	movq	%mm1,DEST_0(%edi)
	addl	%edx,%edi

	addl	$32,%esi

	movq	%mm2,DEST_0(%edi)
	addl	%edx,%edi
	movq	%mm3,DEST_0(%edi)
	addl	%edx,%edi

	movq	(%esi),%mm0
	movq	8(%esi),%mm1

	por	%mm4,%mm0
	por	%mm4,%mm1

	movq	16(%esi),%mm2
	movq	24(%esi),%mm3

	por	%mm4,%mm2
	por	%mm4,%mm3

	movq	%mm0,DEST_0(%edi)
	addl	%edx,%edi
	movq	%mm1,DEST_0(%edi)
	addl	%edx,%edi

	movq	%mm2,DEST_0(%edi)
	addl	%edx,%edi
	movq	%mm3,DEST_0(%edi)

	emms
*/
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_32_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_09:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$0xDEADBEEF,%edx		// screen width
bitw_09:
	mov	%ax,%cx				// cmap
	
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_32_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_10:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$0xDEADBEEF,%edx		// screen width
bitw_10:
	mov	%ax,%cx				// cmap
	
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_32_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_11:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$0xDEADBEEF,%edx		// screen width
bitw_11:
	mov	%ax,%cx				// cmap
	
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_32)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_12:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_0(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_2(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_1(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_3(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,DEST_1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,7(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_32_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_13:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,7(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,7-4(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,7-1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,7-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,7-2(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,7-6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,7-3(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,DEST_0(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_32_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_14:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_0(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_2(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_1(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_3(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,DEST_1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,7(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	decl	%edx
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_32_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_15:
	mov	%ax,%cx				// cmap
	addl	20(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,7(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,7-4(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,7-1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,7-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,7-2(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,7-6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,7-3(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,DEST_0(%edi)
7:
	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	decl	%edx
	jne	9b
	
	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_spr8x8asm_32)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	addl	%eax,%eax
	addl	%eax,%eax
	movl	%eax,bitw_00-4
	movl	%eax,bitw_01-4
	movl	%eax,bitw_02-4
	movl	%eax,bitw_03-4
	movl	%eax,bitw_04-4
	movl	%eax,bitw_05-4
	movl	%eax,bitw_06-4
	movl	%eax,bitw_07-4
	movl	%eax,bitw_08-4
	movl	%eax,bitw_09-4
	movl	%eax,bitw_10-4
	movl	%eax,bitw_11-4
	movl	%eax,bitw_12-4
	movl	%eax,bitw_13-4
	movl	%eax,bitw_14-4
	movl	%eax,bitw_15-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4
	movl	%eax,blin_04-4
	movl	%eax,blin_05-4
	movl	%eax,blin_08-4
	movl	%eax,blin_09-4
	movl	%eax,blin_12-4
	movl	%eax,blin_13-4
	addl	$7*4,%eax		// Line 7
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4

	ret


