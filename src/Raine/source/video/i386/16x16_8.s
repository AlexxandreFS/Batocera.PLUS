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

FUNC(Draw16x16_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$16*16,%edx			// tile end

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw16x16_Mapped_8_FlipY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$16*16,%edx			// tile end

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
	movb	%al,15-0(%edi)
	movb	%bl,15-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-1(%edi)
	movb	%dl,15-5(%edi)

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
	movb	%al,15-2(%edi)
	movb	%bl,15-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-3(%edi)
	movb	%dl,15-7(%edi)

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
	movb	%al,15-8(%edi)
	movb	%bl,15-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-9(%edi)
	movb	%dl,15-13(%edi)

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
	movb	%al,15-10(%edi)
	movb	%bl,15-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-11(%edi)
	movb	%dl,15-15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw16x16_Mapped_8_FlipX)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$16*16,%edx			// tile end

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw16x16_Mapped_8_FlipXY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$16*16,%edx			// tile end

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
	movb	%al,15-0(%edi)
	movb	%bl,15-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-1(%edi)
	movb	%dl,15-5(%edi)

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
	movb	%al,15-2(%edi)
	movb	%bl,15-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-3(%edi)
	movb	%dl,15-7(%edi)

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
	movb	%al,15-8(%edi)
	movb	%bl,15-12(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-9(%edi)
	movb	%dl,15-13(%edi)

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
	movb	%al,15-10(%edi)
	movb	%bl,15-14(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,15-11(%edi)
	movb	%dl,15-15(%edi)

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

	ret			// Arg ! I have nothing rest to pair with the ret
				// instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw16x16_Trans_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$16*16,%edx			// tile end

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

7:	addl	$16,%esi			// Next Tile Line
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

FUNC(Draw16x16_Trans_Mapped_8_FlipY)

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
	movl	$16,%ebp			// Tile Height
	addl	24(%esp),%edi			// x
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

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
	addl	$16,%esi		//	Next	Tile	Line
	addl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_05:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw16x16_Trans_Mapped_8_FlipX)

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
	movl	$16,%ebp			// Tile Height
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
	addl	$16,%esi		//	Next	Tile	Line
	subl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_06:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw16x16_Trans_Mapped_8_FlipXY)

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
	movl	$16,%ebp			// Tile Height
	addl	24(%esp),%edi			// x
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

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
	addl	$16,%esi		//	Next	Tile	Line
	subl	$0xDEADBEEF,%edi	//	Next	Screen	Line
bitw_07:
	decl	%ebp
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw16x16_8)

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_8_FlipY)

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

	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	addl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_8_FlipX)

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_8_FlipXY)

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
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)
	addl	$16,%esi
	subl	%edx,%edi
	movl	12(%esi),%eax
	movl	8(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)
	movl	4(%esi),%eax
	movl	(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,8(%edi)
	movl	%ebx,12(%edi)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Mask)

	pushl	%edi
	pushl	%ebx
	movl	20(%esp),%ebx			// y
	movl	24(%esp),%eax			// cmap
	sall	$2,%ebx
	movb	%al,%ah				// cmap
	movl	0xDEADBEEF(%ebx),%edi
blin_16:
	mov	%ax,%cx				// cmap
	addl	16(%esp),%edi			// x
	shll	$16,%ecx			// cmap
	movl	$0xDEADBEEF,%edx		// screen width
bitw_16:
	mov	%ax,%cx				// cmap

	// 1
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 2
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 3
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 4
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 5
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 6
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 7
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 8
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 9
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 10
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 11
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 12
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 13
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 14
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi
	// 15
	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)
	addl	%edx,%edi

	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)
	movl	%ecx,8(%edi)
	movl	%ecx,12(%edi)

	popl	%ebx
	popl	%edi
	ret

FUNC(Draw16x16_Trans_8)

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
	movl	$16,%edx			// tile height
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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,8(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,12(%edi)
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
	movb	%al,10(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,14(%edi)
7:	cmpb	%ch,%ah
	je	7f
	movb	%ah,11(%edi)
7:	cmpb	%ch,%bh
	je	7f
	movb	%bh,15(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Mask_Trans)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%ecx			// cmap
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_20:
	addl	20(%esp),%edi			// x
	movl	$16,%edx			// tile height
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,4(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,1(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,2(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,6(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,3(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,8(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,12(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,9(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,10(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,14(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,11(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_20:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Trans_8_FlipY)

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
	movb	%bh,(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Mask_Trans_FlipY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%ecx			// cmap
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_21:
	addl	20(%esp),%edi			// x
	movl	$16,%edx			// tile height
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-4(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-1(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-2(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-6(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-3(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-8(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-12(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-9(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-10(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-14(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-11(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_21:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Trans_8_FlipX)

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
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx

	cmpb	%ch,%al
	je	7f
	movb	%al,8(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,12(%edi)
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
	movb	%al,10(%edi)
7:	cmpb	%ch,%bl
	je	7f
	movb	%bl,14(%edi)
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

FUNC(Draw16x16_Mask_Trans_FlipX)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%ecx			// cmap
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_22:
	addl	20(%esp),%edi			// x
	movl	$16,%edx			// tile height
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,4(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,1(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,2(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,6(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,3(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,8(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,12(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,9(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,10(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,14(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,11(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_22:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw16x16_Trans_8_FlipXY)

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
	movb	%bh,(%edi)
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

FUNC(Draw16x16_Mask_Trans_FlipXY)

	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp),%esi			// source
	movl	24(%esp),%ebx			// y
	movl	28(%esp),%ecx			// cmap
	sall	$2,%ebx
	movl	0xDEADBEEF(%ebx),%edi
blin_23:
	addl	20(%esp),%edi			// x
	movl	$16,%edx			// tile height
9:
	movl	(%esi),%eax
	movl	4(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-4(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-1(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-5(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-2(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-6(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-3(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-7(%edi)
7:
	movl	8(%esi),%eax
	movl	12(%esi),%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-8(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-12(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-9(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,15-13(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	je	7f
	movb	%cl,15-10(%edi)
7:	testb	%bl,%bl
	je	7f
	movb	%cl,15-14(%edi)
7:	testb	%ah,%ah
	je	7f
	movb	%cl,15-11(%edi)
7:	testb	%bh,%bh
	je	7f
	movb	%cl,(%edi)
7:
	addl	$16,%esi		// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_23:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(init_spr16x16asm_8)


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



FUNC(init_spr16x16asm_mask)
	movl	4(%esp),%eax // pbitmap is sent on stack !
	movl	(%eax),%eax		// Width
	movl	%eax,bitw_16-4

	movl	%eax,bitw_20-4
	movl	%eax,bitw_21-4
	movl	%eax,bitw_22-4
	movl	%eax,bitw_23-4

	movl	4(%esp),%eax
	addl	$64,%eax		// Line 0

	movl	%eax,blin_16-4
	movl	%eax,blin_20-4
	movl	%eax,blin_21-4

	addl	$15*4,%eax		// Line 15

	movl	%eax,blin_22-4
	movl	%eax,blin_23-4

	ret
