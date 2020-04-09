#include "asmdefs.inc"

CODE_SEG
/******************************************************************************/
/*                                                                            */
/*                         RAINE 32x32 TILE DRAWING                           */
/* We'd better find a way to merge the 8x8, 16x16, and 32x32 files... Later.  */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

FUNC(Draw32x32_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$32*32,%edx			// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_00-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_00:

	addl	24(%esp),%edi			// x
	jmp	9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	1(%esi),%cl
	movb	5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,(%edi)
	movb	%bl,4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,1(%edi)
	movb	%dl,5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	3(%esi),%cl
	movb	7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,2(%edi)
	movb	%bl,6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,3(%edi)
	movb	%dl,7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	8(%esi),%al
	movb	12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	9(%esi),%cl
	movb	13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,8(%edi)
	movb	%bl,12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,9(%edi)
	movb	%dl,13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	10(%esi),%al
	movb	14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	11(%esi),%cl
	movb	15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,10(%edi)
	movb	%bl,14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,11(%edi)
	movb	%dl,15(%edi)

//  Ok, I need to double all this code.
//  I am not going to make a macro with plenty of "\ " because it s ugly.
//  So I am just going to copy/paste the whole thing... cleverly

	xorl	%eax,%eax
	xorl	%ebx,%ebx

	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+1(%esi),%cl
	movb	16+5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16(%edi)
	movb	%bl,16+4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+1(%edi)
	movb	%dl,16+5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+3(%esi),%cl
	movb	16+7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+2(%edi)
	movb	%bl,16+6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+3(%edi)
	movb	%dl,16+7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+8(%esi),%al
	movb	16+12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+9(%esi),%cl
	movb	16+13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+8(%edi)
	movb	%bl,16+12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+9(%edi)
	movb	%dl,16+13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+10(%esi),%al
	movb	16+14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+11(%esi),%cl
	movb	16+15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+10(%edi)
	movb	%bl,16+14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+11(%edi)
	movb	%dl,16+15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw32x32_Mapped_8_FlipY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$32*32,%edx			// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_01-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_01:

	addl	24(%esp),%edi			// x
	jmp	9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	1(%esi),%cl
	movb	5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-0(%edi)
	movb	%bl,31-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-1(%edi)
	movb	%dl,31-5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	3(%esi),%cl
	movb	7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-2(%edi)
	movb	%bl,31-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-3(%edi)
	movb	%dl,31-7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	8(%esi),%al
	movb	12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	9(%esi),%cl
	movb	13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-8(%edi)
	movb	%bl,31-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-9(%edi)
	movb	%dl,31-13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	10(%esi),%al
	movb	14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	11(%esi),%cl
	movb	15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-10(%edi)
	movb	%bl,31-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-11(%edi)
	movb	%dl,31-15(%edi)

// Again all this copy/paste thing.

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+1(%esi),%cl
	movb	16+5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-0(%edi)
	movb	%bl,31-16-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-1(%edi)
	movb	%dl,31-16-5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+3(%esi),%cl
	movb	16+7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-2(%edi)
	movb	%bl,31-16-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-3(%edi)
	movb	%dl,31-16-7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+8(%esi),%al
	movb	16+12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+9(%esi),%cl
	movb	16+13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-8(%edi)
	movb	%bl,31-16-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-9(%edi)
	movb	%dl,31-16-13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+10(%esi),%al
	movb	16+14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+11(%esi),%cl
	movb	16+15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-10(%edi)
	movb	%bl,31-16-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-11(%edi)
	movb	%dl,31-16-15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw32x32_Mapped_8_FlipX)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$32*32,%edx			// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_02-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_02:

	addl	24(%esp),%edi			// x
	jmp	9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	1(%esi),%cl
	movb	5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,(%edi)
	movb	%bl,4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,1(%edi)
	movb	%dl,5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	3(%esi),%cl
	movb	7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,2(%edi)
	movb	%bl,6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,3(%edi)
	movb	%dl,7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	8(%esi),%al
	movb	12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	9(%esi),%cl
	movb	13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,8(%edi)
	movb	%bl,12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,9(%edi)
	movb	%dl,13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	10(%esi),%al
	movb	14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	11(%esi),%cl
	movb	15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,10(%edi)
	movb	%bl,14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,11(%edi)
	movb	%dl,15(%edi)

// Copy/paste always...

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+1(%esi),%cl
	movb	16+5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16(%edi)
	movb	%bl,16+4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+1(%edi)
	movb	%dl,16+5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+3(%esi),%cl
	movb	16+7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+2(%edi)
	movb	%bl,16+6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+3(%edi)
	movb	%dl,16+7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+8(%esi),%al
	movb	16+12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+9(%esi),%cl
	movb	16+13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+8(%edi)
	movb	%bl,16+12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+9(%edi)
	movb	%dl,16+13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+10(%esi),%al
	movb	16+14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+11(%esi),%cl
	movb	16+15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,16+10(%edi)
	movb	%bl,16+14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,16+11(%edi)
	movb	%dl,16+15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw32x32_Mapped_8_FlipXY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$32*32,%edx			// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_03-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_03:

	addl	24(%esp),%edi			// x
	jmp	9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	1(%esi),%cl
	movb	5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-0(%edi)
	movb	%bl,31-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-1(%edi)
	movb	%dl,31-5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	3(%esi),%cl
	movb	7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-2(%edi)
	movb	%bl,31-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-3(%edi)
	movb	%dl,31-7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	8(%esi),%al
	movb	12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	9(%esi),%cl
	movb	13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-8(%edi)
	movb	%bl,31-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-9(%edi)
	movb	%dl,31-13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	10(%esi),%al
	movb	14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	11(%esi),%cl
	movb	15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-10(%edi)
	movb	%bl,31-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-11(%edi)
	movb	%dl,31-15(%edi)

// Same treatement...

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+1(%esi),%cl
	movb	16+5(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-0(%edi)
	movb	%bl,31-16-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-1(%edi)
	movb	%dl,31-16-5(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+3(%esi),%cl
	movb	16+7(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-2(%edi)
	movb	%bl,31-16-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-3(%edi)
	movb	%dl,31-16-7(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+8(%esi),%al
	movb	16+12(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+9(%esi),%cl
	movb	16+13(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-8(%edi)
	movb	%bl,31-16-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-9(%edi)
	movb	%dl,31-16-13(%edi)

	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	16+10(%esi),%al
	movb	16+14(%esi),%bl
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	movb	16+11(%esi),%cl
	movb	16+15(%esi),%dl
	movb	(%ebp,%eax),%al
	movb	(%ebp,%ebx),%bl
	movb	%al,31-16-10(%edi)
	movb	%bl,31-16-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,31-16-11(%edi)
	movb	%dl,31-16-15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw32x32_Trans_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$32*32,%edx			// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_04-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_04:

	addl	24(%esp),%edi			// x
	xorl	%eax,%eax			// pixels 0, 1, 4 and 5 of the line
	xorl	%ebx,%ebx
	xorl	%ecx,%ecx
	xorl	%edx,%edx
	jmp   9f

.align 8
9:
	movb	(%esi),%al
	movb	4(%esi),%bl
	movb	1(%esi),%cl
	movb	5(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,4(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,1(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,5(%edi)

7:
	movb	2(%esi),%al
	movb	6(%esi),%bl
	movb	3(%esi),%cl
	movb	7(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,2(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,6(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,3(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,7(%edi)

7:
	movb	8(%esi),%al
	movb	12(%esi),%bl
	movb	9(%esi),%cl
	movb	13(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,8(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,12(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,9(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,13(%edi)

7:
	movb	10(%esi),%al
	movb	14(%esi),%bl
	movb	11(%esi),%cl
	movb	15(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,10(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,14(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,11(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,15(%edi)

// Copy / paste always... How long...

7:
	movb	16(%esi),%al
	movb	16+4(%esi),%bl
	movb	16+1(%esi),%cl
	movb	16+5(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,16(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,16+4(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,16+1(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,16+5(%edi)

7:
	movb	16+2(%esi),%al
	movb	16+6(%esi),%bl
	movb	16+3(%esi),%cl
	movb	16+7(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,16+2(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,16+6(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,16+3(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,16+7(%edi)

7:
	movb	16+8(%esi),%al
	movb	16+12(%esi),%bl
	movb	16+9(%esi),%cl
	movb	16+13(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,16+8(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,16+12(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,16+9(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,16+13(%edi)

7:
	movb	16+10(%esi),%al
	movb	16+14(%esi),%bl
	movb	16+11(%esi),%cl
	movb	16+15(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,16+10(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,16+14(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,16+11(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,16+15(%edi)
7:
	addl	$32,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_04:

	cmp	$0xDEADBEEF,%esi
endc_04:
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp

	ret

FUNC(Draw32x32_Trans_Mapped_8_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	28(%esp),%eax			// y
	xorl	%edx,%edx
	sall	$2,%eax
	movl	20(%esp),%esi			// source
	movl	0xDEADBEEF(%eax),%edi
blin_05:
	movl	32(%esp),%ecx			// cmap
	movl	$32,%ebp			// Tile Height
	addl	24(%esp),%edi			// x
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-15(%edi)
7:

// And again...

	movl	16(%esi),%eax
	movl	16+4(%esi),%ebx
	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-7(%edi)
7:
	movl	16+8(%esi),%eax
	movl	16+12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,(%edi)
7:

	addl	$32,%esi		//	Next	Tile	Line
	addl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_05:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw32x32_Trans_Mapped_8_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	28(%esp),%eax			// y
	xorl	%edx,%edx
	sall	$2,%eax
	movl	20(%esp),%esi			// source
	movl	0xDEADBEEF(%eax),%edi
blin_06:
	movl	32(%esp),%ecx			// cmap
	movl	$32,%ebp			// Tile Height
	addl	24(%esp),%edi			// x
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15(%edi)
7:
// Oh, yes ! Let s do it again...

	movl	16(%esi),%eax
	movl	16+4(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+7(%edi)
7:
	movl	16+8(%esi),%eax
	movl	16+12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,16+15(%edi)

7:
	addl	$32,%esi		//	Next	Tile	Line
	subl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_06:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw32x32_Trans_Mapped_8_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	28(%esp),%eax			// y
	xorl	%edx,%edx
	sall	$2,%eax
	movl	20(%esp),%esi			// source
	movl	0xDEADBEEF(%eax),%edi
blin_07:
	movl	32(%esp),%ecx			// cmap
	movl	$32,%ebp			// Tile Height
	addl	24(%esp),%edi			// x
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,31-15(%edi)
7:
// Pfff !

	movl	16(%esi),%eax
	movl	16+4(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-1(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-6(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-7(%edi)
7:
	movl	16+8(%esi),%eax
	movl	16+12(%esi),%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-8(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-12(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-9(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ecx,%edx),%al
	movb	%al,15-11(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ecx,%edx),%al
	movb	%al,(%edi)

7:
	addl	$32,%esi		//	Next	Tile	Line
	subl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_07:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

#define HANDLE_32 \
	movl	(%esi),%eax   ;\
	movl	4(%esi),%ebx  ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	movl	%eax,(%edi)   ;\
	movl	%ebx,4(%edi)  ;\
	movl	8(%esi),%eax  ;\
	movl	12(%esi),%ebx ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	movl	%eax,8(%edi)  ;\
	movl	%ebx,12(%edi) ;\
                              ;\
	movl	16(%esi),%eax ;\
	movl	20(%esi),%ebx ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	movl	%eax,16(%edi)  ;\
	movl	%ebx,20(%edi)  ;\
	movl	16+8(%esi),%eax ;\
	movl	16+12(%esi),%ebx ;\
	orl	%ecx,%eax        ;\
	orl	%ecx,%ebx        ;\
	movl	%eax,16+8(%edi)  ;\
	movl	%ebx,16+12(%edi)

FUNC(Draw32x32_8)

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

	// 1
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 2
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 3
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 4
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 5
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 6
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 7
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 8
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 9
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 10
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 11
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 12
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 13
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 14
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 15
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 16
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 17
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 18
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 19
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 20
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 21
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 22
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 23
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 24
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 25
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 26
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 27
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 28
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 29
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 30
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi
	// 31
	HANDLE_32
	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#define HANDLE_32_FlipY ;\
	movl	12(%esi),%eax ;\
	movl	8(%esi),%ebx  ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	bswap	%eax          ;\
	bswap	%ebx          ;\
	movl	%eax,16(%edi)   ;\
	movl	%ebx,16+4(%edi)  ;\
	movl	4(%esi),%eax  ;\
	movl	(%esi),%ebx   ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	bswap	%eax          ;\
	bswap	%ebx          ;\
	movl	%eax,16+8(%edi)  ;\
	movl	%ebx,16+12(%edi) ;\
	                      ;\
	movl	16+12(%esi),%eax ;\
	movl	16+8(%esi),%ebx  ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	bswap	%eax          ;\
	bswap	%ebx          ;\
	movl	%eax,(%edi)   ;\
	movl	%ebx,4(%edi)  ;\
	movl	16+4(%esi),%eax  ;\
	movl	16(%esi),%ebx   ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	bswap	%eax          ;\
	bswap	%ebx          ;\
	movl	%eax,8(%edi)  ;\
	movl	%ebx,12(%edi)

FUNC(Draw32x32_8_FlipY)

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

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	addl	$32,%esi
	addl	%edx,%edi

	HANDLE_32_FlipY

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#define HANDLE_32_FlipX ;\
	movl	(%esi),%eax  ;\
	movl	4(%esi),%ebx ;\
	orl	%ecx,%eax    ;\
	orl	%ecx,%ebx    ;\
	movl	%eax,(%edi)  ;\
	movl	%ebx,4(%edi) ;\
	movl	8(%esi),%eax ;\
	movl	12(%esi),%ebx ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	movl	%eax,8(%edi)  ;\
	movl	%ebx,12(%edi) ;\
	                      ;\
	movl	16(%esi),%eax  ;\
	movl	16+4(%esi),%ebx ;\
	orl	%ecx,%eax    ;\
	orl	%ecx,%ebx    ;\
	movl	%eax,16(%edi)  ;\
	movl	%ebx,16+4(%edi) ;\
	movl	16+8(%esi),%eax ;\
	movl	16+12(%esi),%ebx ;\
	orl	%ecx,%eax     ;\
	orl	%ecx,%ebx     ;\
	movl	%eax,16+8(%edi)  ;\
	movl	%ebx,16+12(%edi)


FUNC(Draw32x32_8_FlipX)

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

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipX

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

#define HANDLE_32_FlipXY ;\
	movl	16+12(%esi),%eax   ;\
	movl	16+8(%esi),%ebx    ;\
	orl	%ecx,%eax       ;\
	orl	%ecx,%ebx       ;\
	bswap	%eax            ;\
	bswap	%ebx            ;\
	movl	%eax,(%edi)     ;\
	movl	%ebx,4(%edi)    ;\
	movl	16+4(%esi),%eax ;\
	movl	16(%esi),%ebx   ;\
	orl	%ecx,%eax       ;\
	orl	%ecx,%ebx       ;\
	bswap	%eax            ;\
	bswap	%ebx            ;\
	movl	%eax,8(%edi)    ;\
	movl	%ebx,12(%edi)   ;\
	                        ;\
	movl	12(%esi),%eax   ;\
	movl	8(%esi),%ebx    ;\
	orl	%ecx,%eax       ;\
	orl	%ecx,%ebx       ;\
	bswap	%eax            ;\
	bswap	%ebx            ;\
	movl	%eax,16(%edi)     ;\
	movl	%ebx,16+4(%edi)    ;\
	movl	4(%esi),%eax ;\
	movl	(%esi),%ebx   ;\
	orl	%ecx,%eax       ;\
	orl	%ecx,%ebx       ;\
	bswap	%eax            ;\
	bswap	%ebx            ;\
	movl	%eax,16+8(%edi)    ;\
	movl	%ebx,16+12(%edi)

FUNC(Draw32x32_8_FlipXY)

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

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	addl	$32,%esi
	subl	%edx,%edi

	HANDLE_32_FlipXY

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

// I leave the Draw32x32_Trans functions for now... Probably useless anyway
FUNC(init_spr32x32asm_8)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width

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

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4
	movl	%eax,blin_04-4
	movl	%eax,blin_05-4
	movl	%eax,blin_08-4
	movl	%eax,blin_09-4
	addl	$31*4,%eax		// Last line
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4

	ret
