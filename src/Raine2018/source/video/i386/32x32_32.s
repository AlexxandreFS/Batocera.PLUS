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

This one is directly built from the 16bit version, with some strategic
search/replace :)
Hummm... Finally there were 128*4 of them... Maybe it would have been faster
by hand...

*/

FUNC(Draw32x32_Mapped_32)

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
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,(%edi)
	movl	%edx,16(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,4(%edi)
	movl	%edx,20(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,8(%edi)
	movl	%edx,24(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,12(%edi)
	movl	%edx,28(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,32(%edi)
	movl	%edx,48(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,36(%edi)
	movl	%edx,52(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,40(%edi)
	movl	%edx,56(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,44(%edi)
	movl	%edx,60(%edi)

// Let's play to copy & paste

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64(%edi)
	movl	%edx,64+16(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+4(%edi)
	movl	%edx,64+20(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+8(%edi)
	movl	%edx,64+24(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+12(%edi)
	movl	%edx,64+28(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+32(%edi)
	movl	%edx,64+48(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+36(%edi)
	movl	%edx,64+52(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+40(%edi)
	movl	%edx,64+56(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+44(%edi)
	movl	%edx,64+60(%edi)

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

FUNC(Draw32x32_Mapped_32_FlipY)

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
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124(%edi)
	movl	%edx,124-16(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-4(%edi)
	movl	%edx,124-20(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-8(%edi)
	movl	%edx,124-24(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-12(%edi)
	movl	%edx,124-28(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-32(%edi)
	movl	%edx,124-48(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-36(%edi)
	movl	%edx,124-52(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-40(%edi)
	movl	%edx,124-56(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-44(%edi)
	movl	%edx,124-60(%edi)

	// The copy /paste thing...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60(%edi)
	movl	%edx,60-16(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-4(%edi)
	movl	%edx,60-20(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-8(%edi)
	movl	%edx,60-24(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-12(%edi)
	movl	%edx,60-28(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-32(%edi)
	movl	%edx,60-48(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-36(%edi)
	movl	%edx,60-52(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-40(%edi)
	movl	%edx,60-56(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-44(%edi)
	movl	%edx,60-60(%edi)

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

FUNC(Draw32x32_Mapped_32_FlipX)

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
	addl	24(%esp),%edi			// x
	addl	24(%esp),%edi			// x

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,(%edi)
	movl	%edx,16(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,4(%edi)
	movl	%edx,20(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,8(%edi)
	movl	%edx,24(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,12(%edi)
	movl	%edx,28(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,32(%edi)
	movl	%edx,48(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,36(%edi)
	movl	%edx,52(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,40(%edi)
	movl	%edx,56(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,44(%edi)
	movl	%edx,60(%edi)

// Let's play to copy & paste (from the non flipping version)

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64(%edi)
	movl	%edx,64+16(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+4(%edi)
	movl	%edx,64+20(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+8(%edi)
	movl	%edx,64+24(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+12(%edi)
	movl	%edx,64+28(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+32(%edi)
	movl	%edx,64+48(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+36(%edi)
	movl	%edx,64+52(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+40(%edi)
	movl	%edx,64+56(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,64+44(%edi)
	movl	%edx,64+60(%edi)

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

FUNC(Draw32x32_Mapped_32_FlipXY)

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
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124(%edi)
	movl	%edx,124-16(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-4(%edi)
	movl	%edx,124-20(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-8(%edi)
	movl	%edx,124-24(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-12(%edi)
	movl	%edx,124-28(%edi)

	movb	8(%esi),%al
	movb	8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-32(%edi)
	movl	%edx,124-48(%edi)

	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-36(%edi)
	movl	%edx,124-52(%edi)

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-40(%edi)
	movl	%edx,124-56(%edi)

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,124-44(%edi)
	movl	%edx,124-60(%edi)

	// The copy /paste thing...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60(%edi)
	movl	%edx,60-16(%edi)

	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-4(%edi)
	movl	%edx,60-20(%edi)

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-8(%edi)
	movl	%edx,60-24(%edi)

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-12(%edi)
	movl	%edx,60-28(%edi)

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-32(%edi)
	movl	%edx,60-48(%edi)

	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-36(%edi)
	movl	%edx,60-52(%edi)

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-40(%edi)
	movl	%edx,60-56(%edi)

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl
	movl	(%ebp,%eax,4),%ecx
	movl	(%ebp,%ebx,4),%edx

	movl	%ecx,60-44(%edi)
	movl	%edx,60-60(%edi)

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

FUNC(Draw32x32_Trans_Mapped_32)

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
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,16(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,20(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,24(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,28(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,48(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,52(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,56(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60(%edi)
7:

// Copy... paste...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+16(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+20(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+24(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+28(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+48(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+52(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+56(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+60(%edi)
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

FUNC(Draw32x32_Trans_Mapped_32_FlipY)

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
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-16(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-20(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-24(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-28(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-48(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-52(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-56(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-60(%edi)
7:

// Copy...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-16(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-20(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-24(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-28(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-48(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-52(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-56(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-60(%edi)
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

FUNC(Draw32x32_Trans_Mapped_32_FlipX)

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
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,16(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,20(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,24(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,28(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,48(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,52(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,56(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60(%edi)
7:

// Copy... paste... (from the non flipping version)

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+16(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+20(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+24(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+28(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+48(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+52(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+56(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,64+44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,64+60(%edi)
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

FUNC(Draw32x32_Trans_Mapped_32_FlipXY)

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
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-16(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-20(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-24(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-28(%edi)
7:

	movb	8(%esi),%al
	movb	8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-48(%edi)
7:
	movb	8+1(%esi),%al
	movb	8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-52(%edi)
7:

	movb	8+2(%esi),%al
	movb	8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-56(%edi)
7:

	movb	8+3(%esi),%al
	movb	8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,124-44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,124-60(%edi)
7:

// Copy...

	movb	16(%esi),%al
	movb	16+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-16(%edi)
7:
	movb	16+1(%esi),%al
	movb	16+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-20(%edi)
7:

	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-24(%edi)
7:

	movb	16+3(%esi),%al
	movb	16+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-12(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-28(%edi)
7:

	movb	16+8(%esi),%al
	movb	16+8+4(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-32(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-48(%edi)
7:
	movb	16+8+1(%esi),%al
	movb	16+8+5(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-36(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-52(%edi)
7:

	movb	16+8+2(%esi),%al
	movb	16+8+6(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-40(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-56(%edi)
7:

	movb	16+8+3(%esi),%al
	movb	16+8+7(%esi),%bl

	testb	%al,%al
	jz	7f
	movl	(%ebp,%eax,4),%ecx
	movl	%ecx,60-44(%edi)
7:	testb	%bl,%bl
	jz	7f
	movl	(%ebp,%ebx,4),%edx
	movl	%edx,60-60(%edi)
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

FUNC(init_spr32x32asm_32)


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

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4
	movl	%eax,blin_04-4
	movl	%eax,blin_05-4
	addl	$31*4,%eax		// Line 31
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	ret
