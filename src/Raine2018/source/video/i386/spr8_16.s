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
	
FUNC(Draw8x8_Mapped_16)

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

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
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

FUNC(Draw8x8_Mapped_16_FlipY)

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

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14(%edi)
	movw	%dx,14-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-2(%edi)
	movw	%dx,14-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-4(%edi)
	movw	%dx,14-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-6(%edi)
	movw	%dx,14-14(%edi)

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

FUNC(Draw8x8_Mapped_16_FlipX)

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

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
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

FUNC(Draw8x8_Mapped_16_FlipXY)

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

	xorl	%edx,%edx
	xorl	%ecx,%ecx
	xorl	%ebx,%ebx
	xorl	%eax,%eax
9:
	movb	(%edi),%dl
	movb	(%esi),%al
	movb	15(%edi),%cl
	movb	4(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14(%edi)
	movw	%dx,14-8(%edi)

	movb	1(%esi),%al
	movb	5(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-2(%edi)
	movw	%dx,14-10(%edi)

	movb	2(%esi),%al
	movb	6(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-4(%edi)
	movw	%dx,14-12(%edi)

	movb	3(%esi),%al
	movb	7(%esi),%bl
	movw	(%ebp,%eax,2),%cx
	movw	(%ebp,%ebx,2),%dx

	movw	%cx,14-6(%edi)
	movw	%dx,14-14(%edi)

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

FUNC(Draw8x8_Trans_Mapped_16)

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

FUNC(Draw8x8_Trans_Mapped_16_FlipY)

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
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-14(%edi)
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

FUNC(Draw8x8_Trans_Mapped_16_FlipX)

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

FUNC(Draw8x8_Trans_Mapped_16_FlipXY)

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
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-8(%edi)
7:
	movb	1(%esi),%al
	movb	5(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-10(%edi)
7:

	movb	2(%esi),%al
	movb	6(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-12(%edi)
7:

	movb	3(%esi),%al
	movb	7(%esi),%bl

	testb	%al,%al
	jz	7f
	movw	(%ebp,%eax,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bl,%bl
	jz	7f
	movw	(%ebp,%ebx,2),%dx
	movw	%dx,14-14(%edi)
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

FUNC(Draw8x8_16)

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

	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_16_FlipY)

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
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	addl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_16_FlipX)

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
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_16_FlipXY)

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
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	addl	$8,%esi
	subl	%edx,%edi
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_16)

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
	movb	%al,(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,4(%edi)
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
	movb	%al,2(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,3(%edi)
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

FUNC(Draw8x8_Trans_16_FlipY)

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
	movb	%bh,(%edi)
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

FUNC(Draw8x8_Trans_16_FlipX)

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
	movb	%al,(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,4(%edi)
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
	movb	%al,2(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,6(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,3(%edi)
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

FUNC(Draw8x8_Trans_16_FlipXY)

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
	movb	%bh,(%edi)
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

FUNC(init_spr8x8asm_16)


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


