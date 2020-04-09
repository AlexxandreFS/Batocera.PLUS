#include "asmdefs.inc"

CODE_SEG
/******************************************************************************/
/*                                                                            */
/*                         RAINE 16x16 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

#define DEST_0		0
#define DEST_1		4
#define DEST_2		8
#define DEST_3		12
#define DEST_4		16
#define DEST_5		20
#define DEST_6		24
#define DEST_7		28
#define DEST_8		32
#define DEST_9		36
#define DEST_10		40
#define DEST_11		44
#define DEST_12		48
#define DEST_13		52
#define DEST_14		56
#define DEST_15		60

FUNC(Draw16x16_Mapped_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movb	31(%edi),%cl
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

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_8(%edi)
	movl	%edx,DEST_12(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_9(%edi)
	movl	%edx,DEST_13(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_10(%edi)
	movl	%edx,DEST_14(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_11(%edi)
	movl	%edx,DEST_15(%edi)

	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Mapped_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movb	31(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_15(%edi)
	movl	%edx,DEST_11(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_14(%edi)
	movl	%edx,DEST_10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_13(%edi)
	movl	%edx,DEST_9(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_12(%edi)
	movl	%edx,DEST_8(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_7(%edi)
	movl	%edx,DEST_3(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_6(%edi)
	movl	%edx,DEST_2(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_5(%edi)
	movl	%edx,DEST_1(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_4(%edi)
	movl	%edx,DEST_0(%edi)

	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Mapped_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movb	31(%edi),%cl
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

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_8(%edi)
	movl	%edx,DEST_12(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_9(%edi)
	movl	%edx,DEST_13(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_10(%edi)
	movl	%edx,DEST_14(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_11(%edi)
	movl	%edx,DEST_15(%edi)

	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Mapped_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movb	31(%edi),%cl
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_15(%edi)
	movl	%edx,DEST_11(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_14(%edi)
	movl	%edx,DEST_10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_13(%edi)
	movl	%edx,DEST_9(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_12(%edi)
	movl	%edx,DEST_8(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_7(%edi)
	movl	%edx,DEST_3(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_6(%edi)
	movl	%edx,DEST_2(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_5(%edi)
	movl	%edx,DEST_1(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,DEST_4(%edi)
	movl	%edx,DEST_0(%edi)

	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Trans_Mapped_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movw	30(%edi),%cx
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

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_12(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_9(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_13(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_14(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_11(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_15(%edi)
7:

	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Trans_Mapped_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movw	30(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_15(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_11(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_14(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_13(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_9(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_8(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_7(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_3(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_2(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_1(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_0(%edi)
7:
	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Trans_Mapped_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movw	30(%edi),%cx
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

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_12(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_9(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_13(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_14(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_11(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_15(%edi)
7:
	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_Trans_Mapped_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*16,%edx			// tile end
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
	movw	30(%edi),%cx
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_15(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_11(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_14(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_13(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_9(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_8(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_7(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_3(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_2(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_1(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,DEST_4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,DEST_0(%edi)
7:
	addl	$16,%esi		// Next Tile Line
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

FUNC(Draw16x16_32)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_08:
	movl	20(%esp),%eax			// x
	sall	$2,%eax
	addl	%eax,%edi
	movl	$16,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_08:
	movsl // 1 pixel !
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl
	movsl

	addl	%edx,%edi
	decl	%ecx
	jne	bitw_08

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#define HANDLE_2_PIXELS(offset)                 \
        movl        offset(%esi),%eax;          \
        movl        offset+4(%esi),%ebx;        \
        movl        %eax,16*4-(offset+4)(%edi); \
        movl        %ebx,16*4-(offset+8)(%edi);

FUNC(Draw16x16_32_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_09:
	movl	20(%esp),%eax			// x
	sall	$2,%eax
	addl	%eax,%edi

	movl	$16,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_09:
	HANDLE_2_PIXELS(0)
	HANDLE_2_PIXELS(4*2)
	HANDLE_2_PIXELS(4*4)
	HANDLE_2_PIXELS(4*6)
	HANDLE_2_PIXELS(4*8)
	HANDLE_2_PIXELS(4*10)
	HANDLE_2_PIXELS(4*12)
	HANDLE_2_PIXELS(4*14)

	addl	$16*4,%esi		// Next Tile Line
	addl	%edx,%edi	// Next Screen Line
	decl	%ecx
	jne	bitw_09

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_32_FlipX)
    ret	// doesn't work for now !

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_32_FlipXY)
    ret // doesn't work

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

	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_0(%edi)
	movl	%ebx,DEST_2(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,DEST_4(%edi)
	movl	%ebx,DEST_6(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#undef HANDLE_2_PIXELS
#define HANDLE_2_PIXELS(offset)  \
    movl    offset(%esi),%eax;   \
    movl    offset+4(%esi),%ebx; \
                                 \
    cmp    %ecx,%eax;            \
    je    7f;                    \
    mov    %eax,offset(%edi);    \
7:    cmp    %ecx,%ebx;          \
    je    7f;                    \
    movl    %ebx,offset+4(%edi); \
7:;

FUNC(Draw16x16_Trans_32)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_12:
	movl	20(%esp),%eax			// x
	sall    $2,%eax
	addl	%eax,%edi
	movl	$16,%edx			// tile height
	mov	GLOBL(emudx_transp),%ecx
9:
	HANDLE_2_PIXELS(0)
	HANDLE_2_PIXELS(8)
	HANDLE_2_PIXELS(4*4)
	HANDLE_2_PIXELS(6*4)
	HANDLE_2_PIXELS(8*4)
	HANDLE_2_PIXELS(10*4)
	HANDLE_2_PIXELS(12*4)
	HANDLE_2_PIXELS(14*4)
7:
	addl	$16*4,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#undef HANDLE_2_PIXELS
#define HANDLE_2_PIXELS(offset)         \
    movl    offset(%esi),%eax;          \
    movl    offset+4(%esi),%ebx;        \
                                        \
    cmp    %ecx,%eax;                   \
    je    7f;                           \
    mov    %eax,16*4-(offset+4)(%edi);  \
7:    cmp    %ecx,%ebx;                 \
    je    7f;                           \
    movl    %ebx,16*4-(offset+8)(%edi); \
7:;

FUNC(Draw16x16_Trans_32_FlipY)
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_13:
	movl	20(%esp),%eax			// x
	sall    $2,%eax
	addl	%eax,%edi
	movl	$16,%edx			// tile height
	mov	GLOBL(emudx_transp),%ecx
9:
	HANDLE_2_PIXELS(0)
	HANDLE_2_PIXELS(8)
	HANDLE_2_PIXELS(4*4)
	HANDLE_2_PIXELS(6*4)
	HANDLE_2_PIXELS(8*4)
	HANDLE_2_PIXELS(10*4)
	HANDLE_2_PIXELS(12*4)
	HANDLE_2_PIXELS(14*4)
7:
	addl	$16*4,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi

	ret

FUNC(Draw16x16_Trans_32_FlipX)
    ret // doesn't work

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
	movl	$16,%edx			// tile height
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
	movb	%ah,3(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_4(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,9(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,DEST_5(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,DEST_7(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,11(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,15(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Trans_32_FlipXY)
    ret // doesn't work

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
	movl	$16,%edx			// tile height
	mov	%ax,%cx				// cmap
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,15(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,15-4(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,15-1(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,15-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,15-2(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,15-6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,15-3(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,15-7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,15-8(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,15-12(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,15-9(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,15-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,15-10(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,15-14(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,15-11(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,DEST_0(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_spr16x16asm_32)


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
	push	%eax
	subl	$16*4,%eax
	movl	%eax,bitw_08-4
	pop	%eax
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
	addl	$15*4,%eax		// Line 15
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4

	ret



