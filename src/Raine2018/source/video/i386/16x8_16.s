#include "asmdefs.inc"

CODE_SEG
/******************************************************************************/
/*                                                                            */
/*                         RAINE 16x8 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

FUNC(Draw16x8_Mapped_16)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_00:
	movl	%edx,endc_00-4
	movl	32(%esp),%ebp			// cmap
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
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,(%edi)
	movw	%dx,8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,2(%edi)
	movw	%dx,10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,4(%edi)
	movw	%dx,12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,6(%edi)
	movw	%dx,14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,16(%edi)
	movw	%dx,24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,18(%edi)
	movw	%dx,26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,20(%edi)
	movw	%dx,28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,22(%edi)
	movw	%dx,30(%edi)

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

FUNC(Draw16x8_Mapped_16_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_01:
	movl	%edx,endc_01-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30(%edi)
	movw	%dx,30-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-2(%edi)
	movw	%dx,30-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-4(%edi)
	movw	%dx,30-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-6(%edi)
	movw	%dx,30-14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-16(%edi)
	movw	%dx,30-24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-18(%edi)
	movw	%dx,30-26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-20(%edi)
	movw	%dx,30-28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-22(%edi)
	movw	%dx,30-30(%edi)

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

FUNC(Draw16x8_Mapped_16_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_02:
	movl	%edx,endc_02-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,(%edi)
	movw	%dx,8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,2(%edi)
	movw	%dx,10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,4(%edi)
	movw	%dx,12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,6(%edi)
	movw	%dx,14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,16(%edi)
	movw	%dx,24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,18(%edi)
	movw	%dx,26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,20(%edi)
	movw	%dx,28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,22(%edi)
	movw	%dx,30(%edi)

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

FUNC(Draw16x8_Mapped_16_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_03:
	movl	%edx,endc_03-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30(%edi)
	movw	%dx,30-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-2(%edi)
	movw	%dx,30-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-4(%edi)
	movw	%dx,30-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-6(%edi)
	movw	%dx,30-14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-16(%edi)
	movw	%dx,30-24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-18(%edi)
	movw	%dx,30-26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-20(%edi)
	movw	%dx,30-28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-22(%edi)
	movw	%dx,30-30(%edi)

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

FUNC(Draw16x8_Trans_Mapped_16)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_04:
	movl	%edx,endc_04-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30(%edi)
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

FUNC(Draw16x8_Trans_Mapped_16_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_05:
	movl	%edx,endc_05-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-30(%edi)
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

FUNC(Draw16x8_Trans_Mapped_16_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_06:
	movl	%edx,endc_06-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30(%edi)
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

FUNC(Draw16x8_Trans_Mapped_16_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$16*8,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_07:
	movl	%edx,endc_07-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-30(%edi)
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

/* no cmap handling in 16bpp... (direct rendering here) */
/* It becomes exactly equivalent to the move code (see move.s), at least for the
   non flipped version */

FUNC(Draw16x8_16)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_08:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled normally ???
	movl	$8,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_08:

	movsl	// 2 pixels
	movsl
	movsl
	movsl

	movsl	// 2 pixels
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

// flipy version
#define HANDLE_4_PIXELS_2o(offset)   \
	mov	%ax,offset+6(%edi);\
	mov	%bx,offset+2(%edi);\
	shr	$16,%eax;\
	shr	$16,%ebx;\
	mov	%ax,offset+4(%edi);\
	mov	%bx,offset+0(%edi)

FUNC(Draw16x8_16_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_09:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x .// doubled ???
	movl	$8,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_09:

	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2o(24)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2o(16)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2o(8)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2o(0)

	addl	$16*2,%esi		// Next Tile Line
	addl	%edx,%edi	// Next Screen Line
	decl	%ecx
	jne	bitw_09

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x8_16_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_10:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$8,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_10:
	movsl	// 2 pixels
	movsl
	movsl
	movsl

	movsl	// 2 pixels
	movsl
	movsl
	movsl

	subl	%edx,%edi
	decl	%ecx
	jne	bitw_10

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x8_16_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_11:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$8,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_11:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2o(24)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2o(16)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2o(8)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2o(0)

	addl	$16*2,%esi		// Next Tile Line
	subl	%edx,%edi	// Next Screen Line
	decl	%ecx
	jne	bitw_11


	popl	%ebx
	popl	%esi
	popl	%edi
	ret

/* This code is specific to emudx. It takes the transparency color from the global
   emudx_transp. */

// Normal version
#define HANDLE_4_PIXELS_1(offset)   \
	cmp	%cx,%ax;\
	je	7f;\
	mov	%ax,offset(%edi);\
7:	cmp	%cx,%bx;\
	je	7f;\
	mov	%bx,offset+4(%edi);\
;\
7:;\
	shr	$16,%eax;\
	shr	$16,%ebx;\
	cmp	%cx,%ax;\
	je	7f;\
	mov	%ax,offset+2(%edi);\
7:	cmp	%cx,%bx;\
	je	7f;\
	mov	%bx,offset+6(%edi);\
7:

// flipy version
#define HANDLE_4_PIXELS_2(offset)   \
	cmp	%cx,%ax;\
	je	7f;\
	mov	%ax,offset+6(%edi);\
7:	cmp	%cx,%bx;\
	je	7f;\
	mov	%bx,offset+2(%edi);\
;\
7:;\
	shr	$16,%eax;\
	shr	$16,%ebx;\
	cmp	%cx,%ax;\
	je	7f;\
	mov	%ax,offset+4(%edi);\
7:	cmp	%cx,%bx;\
	je	7f;\
	mov	%bx,offset+0(%edi);\
7:

FUNC(Draw16x8_Trans_16)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_12:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$8,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_1(0)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_1(8)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_1(16)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_1(24)

	addl	$16*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x8_Trans_16_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_13:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	mov	GLOBL(emudx_transp),%cx
	movl	$8,%edx			// tile height
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2(24)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2(16)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2(8)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2(0)

	addl	$16*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x8_Trans_16_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_14:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	movl	$8,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_1(0)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_1(8)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_1(16)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_1(24)

	addl	$16*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x8_Trans_16_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_15:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$8,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2(24)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2(16)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2(8)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2(0)

	addl	$16*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_spr16x8asm_16)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	addl	%eax,%eax
	movl	%eax,bitw_00-4
	movl	%eax,bitw_01-4
	movl	%eax,bitw_02-4
	movl	%eax,bitw_03-4
	movl	%eax,bitw_04-4
	movl	%eax,bitw_05-4
	movl	%eax,bitw_06-4
	movl	%eax,bitw_07-4
	movl	%eax,bitw_09-4
	movl	%eax,bitw_11-4
	movl	%eax,bitw_12-4
	movl	%eax,bitw_13-4
	movl	%eax,bitw_14-4
	movl	%eax,bitw_15-4

	subl	$16*2,%eax  // minus the width of a sprite
	movl	%eax,bitw_08-4
	addl	$16*2*2,%eax // + 1 width in the other way (flipx)
	movl	%eax,bitw_10-4

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
	addl	$7*4,%eax		// Line 15
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4

	ret



