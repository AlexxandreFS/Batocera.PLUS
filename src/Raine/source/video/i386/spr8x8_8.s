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

FUNC(Draw8x8_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx			      // tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_00-4
	movl	20(%esp),%esi                 // source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_00:

	addl	24(%esp),%edi			// x
      jmp   9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.
      // please believe blindly in karma's knowledge :-)

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

	addl	$8,%esi               // Next Tile Line
	addl	$0xDEADBEEF,%edi	    // Next Screen Line
bitw_00:

	cmp	$0xDEADBEEF,%esi
endc_00:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret                // Arg ! I have nothing rest to pair with the ret
                         // instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw8x8_Mapped_8_FlipY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx			      // tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_01-4
	movl	20(%esp),%esi                 // source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_01:

	addl	24(%esp),%edi			// x
      jmp   9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.
      // please believe blindly in karma's knowledge :-)

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
	movb	%al,7-0(%edi)
	movb	%bl,7-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,7-1(%edi)
	movb	%dl,7-5(%edi)

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
	movb	%al,7-2(%edi)
	movb	%bl,7-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,7-3(%edi)
	movb	%dl,7-7(%edi)

	addl	$8,%esi               // Next Tile Line
	addl	$0xDEADBEEF,%edi	    // Next Screen Line
bitw_01:

	cmp	$0xDEADBEEF,%esi
endc_01:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret                // Arg ! I have nothing rest to pair with the ret
                         // instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw8x8_Mapped_8_FlipX)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx			      // tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_02-4
	movl	20(%esp),%esi                 // source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_02:

	addl	24(%esp),%edi			// x
      jmp   9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.
      // please believe blindly in karma's knowledge :-)

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

	addl	$8,%esi               // Next Tile Line
	subl	$0xDEADBEEF,%edi	    // Next Screen Line
bitw_02:

	cmp	$0xDEADBEEF,%esi
endc_02:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret                // Arg ! I have nothing rest to pair with the ret
                         // instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw8x8_Mapped_8_FlipXY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx			      // tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_03-4
	movl	20(%esp),%esi                 // source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_03:

	addl	24(%esp),%edi			// x
      jmp   9f

	//xorl	%eax,%eax // No! It's not the good way to do fast things.
	//xorl	%ebx,%ebx // I know that it could appears strange, but the
	//xorl	%ecx,%ecx // best thing to do is to zeroing registers just
	//xorl	%edx,%edx // 1 cycle before to use them as 8bits registers.
      // please believe blindly in karma's knowledge :-)

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
	movb	%al,7-0(%edi)
	movb	%bl,7-4(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,7-1(%edi)
	movb	%dl,7-5(%edi)

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
	movb	%al,7-2(%edi)
	movb	%bl,7-6(%edi)
	movb	(%ebp,%ecx),%cl
	movb	(%ebp,%edx),%dl
	movb	%cl,7-3(%edi)
	movb	%dl,7-7(%edi)

	addl	$8,%esi               // Next Tile Line
	subl	$0xDEADBEEF,%edi	    // Next Screen Line
bitw_03:

	cmp	$0xDEADBEEF,%esi
endc_03:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret                // Arg ! I have nothing rest to pair with the ret
                         // instruction : Here is a waste of 1/2 cycle ... :-)

FUNC(Draw8x8_Trans_Mapped_8)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx				// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_04-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_04:

	xorl	%ecx,%ecx
	xorl	%edx,%edx

	addl	24(%esp),%edi			// x
	jmp   9f

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
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

7:	xorl	%eax,%eax
	xorl	%ebx,%ebx
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

7:	addl	$8,%esi			// Next Tile Line
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

FUNC(Draw8x8_Trans_Mapped_8_FlipY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx				// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_05-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_05:

	xorl	%ecx,%ecx
	xorl	%edx,%edx

	addl	24(%esp),%edi			// x
	jmp   9f

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	movb	1(%esi),%cl
	movb	5(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,7-0(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,7-4(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,7-1(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,7-5(%edi)

7:	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	movb	3(%esi),%cl
	movb	7(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,7-2(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,7-6(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,7-3(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,(%edi)

7:	addl	$8,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_05:

	cmp	$0xDEADBEEF,%esi
endc_05:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret

FUNC(Draw8x8_Trans_Mapped_8_FlipX)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx				// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_06-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_06:

	xorl	%ecx,%ecx
	xorl	%edx,%edx

	addl	24(%esp),%edi			// x
	jmp   9f

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
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

7:	xorl	%eax,%eax
	xorl	%ebx,%ebx
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

7:	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_06:

	cmp	$0xDEADBEEF,%esi
endc_06:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret

FUNC(Draw8x8_Trans_Mapped_8_FlipXY)

	movl	12(%esp),%eax			// y
	movl	4(%esp),%edx			// source

	shll	$2,%eax
	addl	$8*8,%edx				// tile end

	pushl	%ebp
	pushl	%edi

	pushl	%esi
	pushl	%ebx

	movl	%edx,endc_07-4
	movl	20(%esp),%esi			// source

	movl	32(%esp),%ebp			// cmap
	movl	0xDEADBEEF(%eax),%edi
blin_07:

	xorl	%ecx,%ecx
	xorl	%edx,%edx

	addl	24(%esp),%edi			// x
	jmp   9f

.align 8
9:
	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	(%esi),%al
	movb	4(%esi),%bl
	movb	1(%esi),%cl
	movb	5(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,7-0(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,7-4(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,7-1(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,7-5(%edi)

7:	xorl	%eax,%eax
	xorl	%ebx,%ebx
	movb	2(%esi),%al
	movb	6(%esi),%bl
	movb	3(%esi),%cl
	movb	7(%esi),%dl

	testb	%al,%al
	jz	7f
	movb	(%ebp,%eax),%al
	movb	%al,7-2(%edi)

7:	testb	%bl,%bl
	jz	7f
	movb	(%ebp,%ebx),%bl
	movb	%bl,7-6(%edi)

7:	testb	%cl,%cl
	jz	7f
	movb	(%ebp,%ecx),%cl
	movb	%cl,7-3(%edi)

7:	testb	%dl,%dl
	jz	7f
	movb	(%ebp,%edx),%dl
	movb	%dl,(%edi)

7:	addl	$8,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_07:

	cmp	$0xDEADBEEF,%esi
endc_07:
	jne	9b

	popl	%ebx
	popl	%esi

	popl	%edi
	popl	%ebp

	ret

FUNC(Draw8x8_8)

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
	shll	$16,%ecx				// cmap
	movl	$0xDEADBEEF,%edx			// screen width
bitw_08:
	mov	%ax,%cx				// cmap

//#define OPTIMIZATION_MMX

#ifdef OPTIMIZATION_MMX
	// This is an mmx version... It is faster? Not really :(

	movl	%ecx,(%edi)
	movl	%ecx,4(%edi)

	movq	(%edi),%mm0

	movq	(%esi),%mm1

	movq	8(%esi),%mm2
	por	%mm0,%mm1

	movq	16(%esi),%mm3
	por	%mm0,%mm2

	movq	24(%esi),%mm4
	por	%mm0,%mm3

	movq	%mm1,(%edi)
	por	%mm0,%mm4

	movq	32(%esi),%mm1

	movq	%mm2,0xDEADBEEF(%edi);	mmx_w01:
	por	%mm0,%mm1

	movq	40(%esi),%mm2

	movq	%mm3,0xDEADBEEF(%edi);	mmx_w02:
	por	%mm0,%mm2

	movq	48(%esi),%mm3

	movq	%mm4,0xDEADBEEF(%edi);	mmx_w03:
	por	%mm0,%mm3

	movq	56(%esi),%mm4

	movq	%mm1,0xDEADBEEF(%edi);	mmx_w04:
	por	%mm0,%mm4

	movq	%mm2,0xDEADBEEF(%edi);	mmx_w05:

	movq	%mm3,0xDEADBEEF(%edi);	mmx_w06:

	movq	%mm4,0xDEADBEEF(%edi);	mmx_w07:

	emms				// This instruction costs a lot of CPU !

#else

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
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	16(%esi),%eax
	movl	20(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	32(%esi),%eax
	movl	36(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	40(%esi),%eax
	movl	44(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	48(%esi),%eax
	movl	52(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	56(%esi),%eax
	movl	60(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

#endif

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_8_FlipY)

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
	shll	$16,%ecx				// cmap
	movl	$0xDEADBEEF,%edx			// screen width
bitw_09:
	mov	%ax,%cx				// cmap

	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	16(%esi),%eax
	movl	20(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	32(%esi),%eax
	movl	36(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	40(%esi),%eax
	movl	44(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	48(%esi),%eax
	movl	52(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	56(%esi),%eax
	movl	60(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_8_FlipX)

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
	neg	%edx

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
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	16(%esi),%eax
	movl	20(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	32(%esi),%eax
	movl	36(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	40(%esi),%eax
	movl	44(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	48(%esi),%eax
	movl	52(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi)
	movl	%ebx,4(%edi)

	movl	56(%esi),%eax
	movl	60(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	movl	%eax,(%edi,%edx)
	movl	%ebx,4(%edi,%edx)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_8_FlipXY)

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
	neg	%edx

	movl	(%esi),%eax
	movl	4(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	16(%esi),%eax
	movl	20(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	24(%esi),%eax
	movl	28(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	32(%esi),%eax
	movl	36(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	40(%esi),%eax
	movl	44(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	leal	(%edi,%edx,2),%edi
	movl	48(%esi),%eax
	movl	52(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi)
	movl	%ebx,(%edi)

	movl	56(%esi),%eax
	movl	60(%esi),%ebx
	orl	%ecx,%eax
	orl	%ecx,%ebx
	bswap	%eax
	bswap	%ebx
	movl	%eax,4(%edi,%edx)
	movl	%ebx,(%edi,%edx)

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_8)

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
	shll	$16,%ecx				// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
	jmp	9f

.align 8
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
	addl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_12:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_8_FlipY)

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
	shll	$16,%ecx				// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
	jmp	9f

.align 8
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
	addl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_13:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_8_FlipX)

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
	shll	$16,%ecx				// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
	jmp	9f

.align 8
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
	subl	$0xDEADBEEF,%edi		// Next Screen Line
bitw_14:
	decl	%edx
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	ret

FUNC(Draw8x8_Trans_8_FlipXY)

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
	shll	$16,%ecx				// cmap
	movl	$8,%edx				// tile height
	mov	%ax,%cx				// cmap
	jmp	9f

.align 8
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

FUNC(init_spr8x8asm_8)


	movl	GLOBL(GameBitmap),%eax	// Adress of the GameBitmap's structure
	movl	(%eax),%eax			// Width
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
	addl	$64,%eax			// Line 0
	movl	%eax,blin_00-4
	movl	%eax,blin_01-4
	movl	%eax,blin_04-4
	movl	%eax,blin_05-4
	movl	%eax,blin_08-4
	movl	%eax,blin_09-4
	movl	%eax,blin_12-4
	movl	%eax,blin_13-4
	addl	$7*4,%eax			// Line 7
	movl	%eax,blin_02-4
	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
	movl	%eax,blin_10-4
	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4

#ifdef OPTIMIZATION_MMX
	push	%ebx
	movl	GLOBL(GameBitmap),%ebx	// Adress of the GameBitmap's structure
	movl	(%ebx),%ebx			// Width
	movl	%ebx,%eax
	movl	%eax,mmx_w01-4		// Width * 1
	addl	%ebx,%eax
	movl	%eax,mmx_w02-4		// Width * 2
	addl	%ebx,%eax
	movl	%eax,mmx_w03-4		// Width * 3
	addl	%ebx,%eax
	movl	%eax,mmx_w04-4		// Width * 4
	addl	%ebx,%eax
	movl	%eax,mmx_w05-4		// Width * 5
	addl	%ebx,%eax
	movl	%eax,mmx_w06-4		// Width * 6
	addl	%ebx,%eax
	movl	%eax,mmx_w07-4		// Width * 7
	pop	%ebx
#endif

	ret


