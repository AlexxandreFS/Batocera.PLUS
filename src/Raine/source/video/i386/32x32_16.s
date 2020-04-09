#include "asmdefs.inc"

CODE_SEG
/******************************************************************************/
/*                                                                            */
/*                         RAINE 32x32 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

FUNC(Draw32x32_Mapped_16)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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
	// I suppose the reads from di are some weird cache initialisation...
	// Message for the guy who wrote that :	 do u know about comments ???

	movb	(%edi),%dl
	movb	(%esi),%al
	movb	63(%edi),%cl
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

// Let's play to copy & paste

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32(%edi)
	movw	%dx,32+8(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+2(%edi)
	movw	%dx,32+10(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+4(%edi)
	movw	%dx,32+12(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+6(%edi)
	movw	%dx,32+14(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+16(%edi)
	movw	%dx,32+24(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+18(%edi)
	movw	%dx,32+26(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+20(%edi)
	movw	%dx,32+28(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+22(%edi)
	movw	%dx,32+30(%edi)

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Mapped_16_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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

	movw	%cx,62(%edi)
	movw	%dx,62-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-2(%edi)
	movw	%dx,62-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-4(%edi)
	movw	%dx,62-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-6(%edi)
	movw	%dx,62-14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-16(%edi)
	movw	%dx,62-24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-18(%edi)
	movw	%dx,62-26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-20(%edi)
	movw	%dx,62-28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-22(%edi)
	movw	%dx,62-30(%edi)

	// The copy /paste thing...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30(%edi)
	movw	%dx,30-8(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-2(%edi)
	movw	%dx,30-10(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-4(%edi)
	movw	%dx,30-12(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-6(%edi)
	movw	%dx,30-14(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-16(%edi)
	movw	%dx,30-24(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-18(%edi)
	movw	%dx,30-26(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-20(%edi)
	movw	%dx,30-28(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-22(%edi)
	movw	%dx,30-30(%edi)

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Mapped_16_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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

// Let's play to copy & paste (from the non flipping version)

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32(%edi)
	movw	%dx,32+8(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+2(%edi)
	movw	%dx,32+10(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+4(%edi)
	movw	%dx,32+12(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+6(%edi)
	movw	%dx,32+14(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+16(%edi)
	movw	%dx,32+24(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+18(%edi)
	movw	%dx,32+26(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+20(%edi)
	movw	%dx,32+28(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,32+22(%edi)
	movw	%dx,32+30(%edi)

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Mapped_16_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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

// Copy this whole thing from the FlipX function... Cool...

	movb	(%esi),%al
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62(%edi)
	movw	%dx,62-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-2(%edi)
	movw	%dx,62-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-4(%edi)
	movw	%dx,62-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-6(%edi)
	movw	%dx,62-14(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-16(%edi)
	movw	%dx,62-24(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-18(%edi)
	movw	%dx,62-26(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-20(%edi)
	movw	%dx,62-28(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,62-22(%edi)
	movw	%dx,62-30(%edi)

	// The copy /paste thing...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30(%edi)
	movw	%dx,30-8(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-2(%edi)
	movw	%dx,30-10(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-4(%edi)
	movw	%dx,30-12(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-6(%edi)
	movw	%dx,30-14(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-16(%edi)
	movw	%dx,30-24(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-18(%edi)
	movw	%dx,30-26(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-20(%edi)
	movw	%dx,30-28(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,30-22(%edi)
	movw	%dx,30-30(%edi)

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Trans_Mapped_16)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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

// Copy... paste...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+8(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+10(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+12(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+14(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+24(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+26(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+28(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+30(%edi)
7:

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Trans_Mapped_16_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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
	movw	%cx,62(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-30(%edi)
7:

// Copy...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-8(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-10(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-12(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-14(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-24(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-26(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-28(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-30(%edi)
7:

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Trans_Mapped_16_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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

// Copy... paste... (from the non flipping version)

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+8(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+10(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+12(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+14(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+24(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+26(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+28(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,32+22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,32+30(%edi)
7:

	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_Trans_Mapped_16_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$32*32,%edx			// tile end
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
// copy all this from the FlipY version...

	movb	(%esi),%al
	movb	4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-14(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-24(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-26(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-28(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,62-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,62-30(%edi)
7:

// Copy...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-8(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-10(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-12(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-14(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-24(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-18(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-26(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-28(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,30-22(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,30-30(%edi)
7:
	addl	$32,%esi		// Next Tile Line
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

FUNC(Draw32x32_16)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_08:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled (16 bpp)
	movl	$32,%ecx
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

FUNC(Draw32x32_16_FlipY)

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
	movl	$32,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_09:

	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2o(56)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2o(48)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2o(40)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2o(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_2o(24)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_2o(16)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_2o(8)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_2o(0)

	addl	$32*2,%esi		// Next Tile Line
	addl	%edx,%edi	// Next Screen Line
	decl	%ecx
	jne	bitw_09

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_16_FlipX)

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
	movl	$32,%ecx
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

FUNC(Draw32x32_16_FlipXY)

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
	movl	$32,%ecx
	movl	$0xDEADBEEF,%edx		// screen width
bitw_11:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2o(56)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2o(48)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2o(40)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2o(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_2o(24)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_2o(16)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_2o(8)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_2o(0)

	addl	$32*2,%esi		// Next Tile Line
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

FUNC(Draw32x32_Trans_16)

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
	movl	$32,%edx			// tile height
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

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_1(32)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_1(32+8)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_1(32+16)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_1(32+24)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_16_FlipY)

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
	movl	$32,%edx			// tile height
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2(56)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2(48)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2(40)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_2(24)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_2(16)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_2(8)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_2(0)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_16_FlipX)

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
	movl	$32,%edx			// tile height
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

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_1(32)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_1(32+8)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_1(32+16)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_1(32+24)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_16_FlipXY)

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
	movl	$32,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	movl	4(%esi),%ebx

	HANDLE_4_PIXELS_2(56)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	HANDLE_4_PIXELS_2(48)

	movl	16(%esi),%eax
	movl	20(%esi),%ebx

	HANDLE_4_PIXELS_2(40)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx

	HANDLE_4_PIXELS_2(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	movl	32+4(%esi),%ebx

	HANDLE_4_PIXELS_2(24)

	movl	32+8(%esi),%eax
	movl	32+12(%esi),%ebx

	HANDLE_4_PIXELS_2(16)

	movl	32+16(%esi),%eax
	movl	32+20(%esi),%ebx

	HANDLE_4_PIXELS_2(8)

	movl	32+24(%esi),%eax
	movl	32+28(%esi),%ebx

	HANDLE_4_PIXELS_2(0)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

/* alpha50 version : there is a more complex version with mmx and varying alpha factor,
	but for a start this version should be enough...
	So this code produces a 50% alpha blending effect */

#define HANDLE_2_PIXELS_1a(offset)   \
	cmp	%cx,%ax;\
	je	7f;\
	mov     offset(%edi),%bx;\
	and	$0xF7DE,%ax;\
	and	$0xF7DE,%bx;\
	rorw	$1,%ax;\
	rorw	$1,%bx;\
	addw	%ax,%bx;\
	movw    %bx,offset(%edi);\
7:;\
	shr	$16,%eax;\
	cmp	%cx,%ax;\
	je	7f;\
	mov     offset+2(%edi),%bx;\
	and	$0xF7DE,%ax;\
	and	$0xF7DE,%bx;\
	rorw	$1,%ax;\
	rorw	$1,%bx;\
	addw	%ax,%bx;\
	movw    %bx,offset+2(%edi);\
7:


// flipy version
#define HANDLE_2_PIXELS_2a(offset)   \
	cmp	%cx,%ax;\
	je	7f;\
	movw	offset+6(%edi),%bx ; \
	andw	$0xF7DE,%ax	; \
	andw	$0xF7DE,%bx ; \
	rorw	$1,%ax		; \
	rorw	$1,%bx	; \
	add	%ax,%bx; \
	mov	%bx,offset+6(%edi) ; \
7:;\
	shr	$16,%eax;\
	cmp	%cx,%ax;\
	je	7f;\
	movw	offset+4(%edi),%bx ; \
	and	$0xF7DE,%ax	; \
	and	$0xF7DE,%ebx ; \
	rorw	$1,%ax		; \
	rorw	$1,%bx	; \
	add	%ax,%bx; \
	movw	%bx,offset+4(%edi) ; \
7:

/* The advanced mmx algorythm along with this trick for the 50% alpha blending are
	described here : http://www.gamedev.net/reference/articles/article817.asp */
/* Notice that the only difference with the normal asm functions is that the alpha50
	macros need 1 more register, and so they can only handle 2 pixels at a time,
	not 4 */

FUNC(Draw32x32_Trans_Alpha50_16)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_16:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$32,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(0)
	movl	4(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(4)

	movl	8(%esi),%eax
	HANDLE_2_PIXELS_1a(8)
	movl	12(%esi),%eax
	HANDLE_2_PIXELS_1a(12)

	movl	16(%esi),%eax
	HANDLE_2_PIXELS_1a(16)
	movl	20(%esi),%eax
	HANDLE_2_PIXELS_1a(20)

	movl	24(%esi),%eax
	HANDLE_2_PIXELS_1a(24)
	movl	28(%esi),%eax
	HANDLE_2_PIXELS_1a(28)

	movl	32+0(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(32)
	movl	32+4(%esi),%eax
	HANDLE_2_PIXELS_1a(32+4)

	movl	32+8(%esi),%eax
	HANDLE_2_PIXELS_1a(32+8)
	movl	32+12(%esi),%eax
	HANDLE_2_PIXELS_1a(32+12)

	movl	32+16(%esi),%eax
	HANDLE_2_PIXELS_1a(32+16)
	movl	32+20(%esi),%eax
	HANDLE_2_PIXELS_1a(32+20)

	movl	32+24(%esi),%eax
	HANDLE_2_PIXELS_1a(32+24)
	movl	32+28(%esi),%eax
	HANDLE_2_PIXELS_1a(32+28)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_16:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha50_16_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_17:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	mov	GLOBL(emudx_transp),%cx
	movl	$32,%edx			// tile height
9:
	movl	(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_2a(60)
	movl	4(%esi),%eax
	HANDLE_2_PIXELS_2a(56)

	movl	8(%esi),%eax
	HANDLE_2_PIXELS_2a(52)
	movl	12(%esi),%eax
	HANDLE_2_PIXELS_2a(48)


	movl	16(%esi),%eax
	HANDLE_2_PIXELS_2a(44)
	movl	20(%esi),%eax
	HANDLE_2_PIXELS_2a(40)

	movl	24(%esi),%eax
	HANDLE_2_PIXELS_2a(36)
	movl	28(%esi),%eax
	HANDLE_2_PIXELS_2a(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_2a(28)
	movl	32+4(%esi),%eax
	HANDLE_2_PIXELS_2a(24)

	movl	32+8(%esi),%eax
	HANDLE_2_PIXELS_2a(20)
	movl	32+12(%esi),%eax
	HANDLE_2_PIXELS_2a(16)

	movl	32+16(%esi),%eax
	HANDLE_2_PIXELS_2a(12)
	movl	32+20(%esi),%eax
	HANDLE_2_PIXELS_2a(8)

	movl	32+24(%esi),%eax
	HANDLE_2_PIXELS_2a(4)
	movl	32+28(%esi),%eax
	HANDLE_2_PIXELS_2a(0)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_17:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha50_16_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_18:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	movl	$32,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(0)
	movl	4(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(4)

	movl	8(%esi),%eax
	HANDLE_2_PIXELS_1a(8)
	movl	12(%esi),%eax
	HANDLE_2_PIXELS_1a(12)

	movl	16(%esi),%eax
	HANDLE_2_PIXELS_1a(16)
	movl	20(%esi),%eax
	HANDLE_2_PIXELS_1a(20)

	movl	24(%esi),%eax
	HANDLE_2_PIXELS_1a(24)
	movl	28(%esi),%eax
	HANDLE_2_PIXELS_1a(28)

	movl	32+0(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_1a(32)
	movl	32+4(%esi),%eax
	HANDLE_2_PIXELS_1a(32+4)

	movl	32+8(%esi),%eax
	HANDLE_2_PIXELS_1a(32+8)
	movl	32+12(%esi),%eax
	HANDLE_2_PIXELS_1a(32+12)

	movl	32+16(%esi),%eax
	HANDLE_2_PIXELS_1a(32+16)
	movl	32+20(%esi),%eax
	HANDLE_2_PIXELS_1a(32+20)

	movl	32+24(%esi),%eax
	HANDLE_2_PIXELS_1a(32+24)
	movl	32+28(%esi),%eax
	HANDLE_2_PIXELS_1a(32+28)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_18:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha50_16_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_19:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$32,%edx			// tile height
	mov	GLOBL(emudx_transp),%cx
9:
	movl	(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_2a(60)
	movl	4(%esi),%eax
	HANDLE_2_PIXELS_2a(56)

	movl	8(%esi),%eax
	HANDLE_2_PIXELS_2a(52)
	movl	12(%esi),%eax
	HANDLE_2_PIXELS_2a(48)


	movl	16(%esi),%eax
	HANDLE_2_PIXELS_2a(44)
	movl	20(%esi),%eax
	HANDLE_2_PIXELS_2a(40)

	movl	24(%esi),%eax
	HANDLE_2_PIXELS_2a(36)
	movl	28(%esi),%eax
	HANDLE_2_PIXELS_2a(32)

	movl	32+0(%esi),%eax // 2 pixels at a time
	HANDLE_2_PIXELS_2a(28)
	movl	32+4(%esi),%eax
	HANDLE_2_PIXELS_2a(24)

	movl	32+8(%esi),%eax
	HANDLE_2_PIXELS_2a(20)
	movl	32+12(%esi),%eax
	HANDLE_2_PIXELS_2a(16)

	movl	32+16(%esi),%eax
	HANDLE_2_PIXELS_2a(12)
	movl	32+20(%esi),%eax
	HANDLE_2_PIXELS_2a(8)

	movl	32+24(%esi),%eax
	HANDLE_2_PIXELS_2a(4)
	movl	32+28(%esi),%eax
	HANDLE_2_PIXELS_2a(0)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_19:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

/* Generic alpha blending : these functions apply the global variable alpha (ranging
	from 0 to 255) as alpha blending, and supposes you called init_alpha from alpha.c
	before calling them... */

/* For reference, what could be used for varying alpha blender (mmx code)

	push edi ;Save off to restore later
	push esi ;Save off to restore later


	mov edi,lpDest	; Move the destination pointer into edi
	mov esi,lpSprite; Move the source pointer into esi

SPAN_RUN_565: movq mm7,[edi]	; Copy the 8 bytes pointed to by edi into mm7
	movq mm6,[esi]	; Copy the 8 bytes pointed to by esi into mm6

	movq mm2,ALPHA64; Copy ALPHA64 into mm2
	movq mm0,mm7	; RED - Copy mm7 to mm0, destination pixels

	pand mm0,MASKRED; RED - and mm0 with the red channel mask [0r00 0r00 0r00 0r00]
	movq mm1,mm6	; RED - Copy mm6 to mm1, source pixels

	pand mm1,MASKRED	; RED - and mm1 with red channel mask [0r00 0r00 0r00 0r00]
	psrlw mm0,11	; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]

	movq mm5,mm7	; GRN - Copy destination pixels (mm7) to mm5
	psrlw mm1,11	; RED - shift each pixel to the right by 11 [000r 000r 000r 000r]


	paddw mm1, ADD64


	movq mm3,mm6	; GRN - Copy source pixels (mm6) to mm3
	psubsw mm1,mm0	; RED - Subtract the destination from the source

	pand mm5,MASKGREEN; GRN - and mm5 with the green channel mask [00g0 00g0 00g0 00g0]
	pmullw mm1,mm2	; RED - multiple the subtraction result by the ALPHA value

	pand mm3,MASKGREEN; GRN - and mm3 with the green channel mask [00g0 00g0 00g0 00g0]
	psrlw mm5,5	; GRN - shift each pixel to the right by 5 [000g 000g 000g 000g]

	psrlw mm3,5	; GRN - Shift green source to the right by 5
	nop		; Do nothing


	paddw mm3, ADD64


	psrlw mm1,8	; RED - Divide by 256 this is done to avoid floating point math
	psubsw mm3,mm5	; GRN - Subtract the green source and destination components

	pmullw mm3,mm2	; GRN - Multiple the result from the subtraction by the alpha value
	paddw mm1,mm0	; RED - Add the destination red component value


	psubw mm1, ALPHABY4


	psllw mm1,11	; RED - Shift the red component back into place, 11 to the left
	movq mm0,mm7	; BLU - Copy the destination pixels to mm0

	pand mm0, MASKBLUE; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
	psrlw mm3,8	; GRN - Divide by 256 this is done to avoid floating point math

	paddw mm3,mm5	; GRN - Add the destination green component value
	movq mm4, mm6	; BLU - Copy the source into mm4


	psubw mm3, ALPHABY4


	pand mm4, MASKBLUE; BLU - 'and' mm0 with the blue channel mask [000b 000b 000b 000b]
	psllw mm3,5	; GRN - Shift the green component back into place, 5 to the left


	paddw mm4, ADD64


	psubsw mm4,mm0	; BLU - Subtract the blue source and destination components
	por mm1,mm3	; GRN - 'or' the red and green components results back together

	pmullw mm4,mm2	; BLU - Multiple the result from the subtraction by the alpha value
	movq mm3,COLORKEY64	; Load COLORKEY64 into mm4

	psrlw mm4,8	; BLU - Divide by 256 this is done to avoid floating point math
	pcmpeqw mm3,mm6	; Compare colorKey to original source

	paddw mm4,mm0	; BLU - Add the destination blue component value
	movq mm5,mm3	; Copy mm3 to mm5


	psubw mm4, ALPHABY4


	por mm1,mm4	; BLU - 'or' the blue result to the red and green results
	pand mm5,mm7	; 'and' mm5 and the original destination pixels

	pandn mm3,mm1	; not's mm3 then performs and "AND" with mm1

	por mm3,mm5	; And mm3 and mm5

	movq [edi],mm3	; Copy the 4 alpha blended pixels to the destination

	Which translates to the following macro :
*/

#define load_normal_mmx(offset) \
	movq offset(%edi), %mm7	;\
	movq offset(%esi),%mm6	;\

/* Intel in its great wisdom, forgot an instruction to swap words in its 64 bits registers
	so I can't seem to be able to swap these words in less than 6 instructions and
	I am obliged to use a 2nd 32bits register for that... */

#define load_flipy_register(src,reg) \
       mov src(%esi),%eax		; \
       rol $16,%eax		; \
       movd %eax,%mm1		; \
	;; \
       mov src+4(%esi),%eax		; \
       rol $16,%eax		; \
       movd %eax,reg		; \
       punpckldq %mm1,reg

#define mmx_blender_4_pixels(offset) \
	movq GLOBL(ALPHA64),%mm2	;\
	movq %mm7,%mm0	;\
	pand GLOBL(MASKRED),%mm0	;\
	movq %mm6,%mm1	;\
	pand GLOBL(MASKRED),%mm1	;\
	psrlw $11,%mm0	;\
	movq %mm7,%mm5	;\
	psrlw $11,%mm1	;\
	paddw  GLOBL(ADD64),%mm1	;\
	movq %mm6,%mm3	;\
	psubsw %mm0,%mm1	;\
	pand GLOBL(MASKGREEN),%mm5	;\
	pmullw %mm2,%mm1	;\
	pand GLOBL(MASKGREEN),%mm3	;\
	psrlw $5,%mm5	;\
	psrlw $5,%mm3	;\
	nop	;\
	paddw  GLOBL(ADD64),%mm3	;\
	psrlw $8,%mm1	;\
	psubsw %mm5,%mm3	;\
	pmullw %mm2,%mm3	;\
	paddw %mm0,%mm1	;\
	psubw  GLOBL(ALPHABY4),%mm1	;\
	psllw $11,%mm1	;\
	movq %mm7,%mm0	;\
	pand  GLOBL(MASKBLUE),%mm0	;\
	psrlw $8,%mm3	;\
	paddw %mm5,%mm3	;\
	movq  %mm6,%mm4	;\
	psubw  GLOBL(ALPHABY4),%mm3	;\
	pand  GLOBL(MASKBLUE),%mm4	;\
	psllw $5,%mm3	;\
	paddw  GLOBL(ADD64),%mm4	;\
	psubsw %mm0,%mm4	;\
	por %mm3,%mm1	;\
	pmullw %mm2,%mm4	;\
	movq GLOBL(COLORKEY64),%mm3	;\
	psrlw $8,%mm4	;\
	pcmpeqw %mm6,%mm3	;\
	paddw %mm0,%mm4	;\
	movq %mm3,%mm5	;\
	psubw  GLOBL(ALPHABY4),%mm4	;\
	por %mm4,%mm1	;\
	pand %mm7,%mm5	;\
	pandn %mm1,%mm3	;\
	por %mm5,%mm3

#define mmx_blender_4(offset) 	; \
	load_normal_mmx(offset)	; \
	mmx_blender_4_pixels(offset) ; \
	movq %mm3,offset(%edi)


#define mmx_blender_4_flipy(offset) 	; \
	load_flipy_register(offset, %mm6)	;\
	movq 56-(offset)(%edi),%mm7	;\
	mmx_blender_4_pixels(offset) ; \
	movq %mm3,56-(offset)(%edi)

FUNC(Draw32x32_Trans_Alpha_16)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_20:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$32,%edx			// tile height
9:
	mmx_blender_4(0)
	mmx_blender_4(8)
	mmx_blender_4(16)
	mmx_blender_4(24)
	mmx_blender_4(32)
	mmx_blender_4(32+8)
	mmx_blender_4(32+16)
	mmx_blender_4(32+24)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_20:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha_16_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_21:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	movl	$32,%edx			// tile height
9:
	mmx_blender_4_flipy(0)
	mmx_blender_4_flipy(8)
	mmx_blender_4_flipy(16)
	mmx_blender_4_flipy(24)
	mmx_blender_4_flipy(32)
	mmx_blender_4_flipy(32+8)
	mmx_blender_4_flipy(32+16)
	mmx_blender_4_flipy(32+24)

	addl	$32*2,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_21:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha_16_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_22:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !
	movl	$32,%edx			// tile height
9:
	mmx_blender_4(0)
	mmx_blender_4(8)
	mmx_blender_4(16)
	mmx_blender_4(24)
	mmx_blender_4(32)
	mmx_blender_4(32+8)
	mmx_blender_4(32+16)
	mmx_blender_4(32+24)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_22:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw32x32_Trans_Alpha_16_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_23:
	addl	20(%esp),%edi			// x
	addl	20(%esp),%edi			// x doubled !!!
	movl	$32,%edx			// tile height
9:
	mmx_blender_4_flipy(0)
	mmx_blender_4_flipy(8)
	mmx_blender_4_flipy(16)
	mmx_blender_4_flipy(24)
	mmx_blender_4_flipy(32)
	mmx_blender_4_flipy(32+8)
	mmx_blender_4_flipy(32+16)
	mmx_blender_4_flipy(32+24)

	addl	$32*2,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_23:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_spr32x32asm_16)


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
	movl	%eax,bitw_20-4
	movl	%eax,bitw_21-4
	movl	%eax,bitw_22-4
	movl	%eax,bitw_23-4

	/* alpha 50 */
	movl	%eax,bitw_16-4
	movl	%eax,bitw_17-4
	movl	%eax,bitw_18-4
	movl	%eax,bitw_19-4

	subl	$32*2,%eax  // minus the width of a sprite
	movl	%eax,bitw_08-4
	addl	$32*2*2,%eax // + 1 width in the other way (flipx)
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
	movl	%eax,blin_16-4
	movl	%eax,blin_17-4
	movl	%eax,blin_20-4
	movl	%eax,blin_21-4
	addl	$31*4,%eax		// Line 31
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4
	movl	%eax,blin_18-4
	movl	%eax,blin_19-4
	movl	%eax,blin_22-4
	movl	%eax,blin_23-4

	ret
