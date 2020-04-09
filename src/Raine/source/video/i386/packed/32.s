/******************************************************************************/
/*                                                                            */
/*                   RAINE 8x8 PACKED 4 BPP TILE DRAWING                      */
/*                                                                            */
/******************************************************************************/

/*
	Functions for packed sprites (2 pixels/byte) 32bpp version
	Most comments are in spp8x8 and spp8x8_16...
*/

#include "asmdefs.inc"

CODE_SEG

FUNC(Draw8x8_Trans_Packed_Mapped_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_04:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_04-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
	
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_04:
	cmp	$0xDEADBEEF,%esi
endc_04:
	jne	9b
	
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_05:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_05-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
	
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-24(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_05:
	cmp	$0xDEADBEEF,%esi
endc_05:
	jne	9b
	
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_06:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_06-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
	
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_06:
	cmp	$0xDEADBEEF,%esi
endc_06:
	jne	9b

	popl	%ecx	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_07:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_07-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-12(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-8(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-24(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_07:
	cmp	$0xDEADBEEF,%esi
endc_07:
	jne	9b

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_32)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_12:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_12-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	cmp	$0xDEADBEEF,%esi
endc_12:
	jne	9b

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_13:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_13-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8	
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-24(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-12(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-8(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	cmp	$0xDEADBEEF,%esi
endc_13:
	jne	9b

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_14:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_14-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,24(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,12(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,8(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	cmp	$0xDEADBEEF,%esi
endc_14:
	jne	9b

	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	
	movl	24(%esp),%esi			// source
	movl	32(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_15:
	movl	28(%esp),%eax			// x
	movl	%edx,endc_15-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,4),%edi		// x (4 times in 32bpp)

	xorl	%edx,%edx
	jmp	9f

.align	8
9:
	movl	(%esi),%eax
	testl	%eax,%eax
	jz	8f

	movl	%eax,%ebx
	andl	$0x0F0F0F0F,%eax

	shrl	$4,%ebx
	andl	$0x0F0F0F0F,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-20(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-16(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-24(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-4(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-12(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movl	(%ebp,%edx,4),%ecx
	movl	%ecx,28-8(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	cmp	$0xDEADBEEF,%esi
endc_15:
	jne	9b
	
	popl	%ecx	
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(init_spp8x8asm_32)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
	addl	%eax,%eax
	addl	%eax,%eax
//	movl	%eax,bitw_00-4
//	movl	%eax,bitw_01-4
//	movl	%eax,bitw_02-4
//	movl	%eax,bitw_03-4
	movl	%eax,bitw_04-4
	movl	%eax,bitw_05-4
	movl	%eax,bitw_06-4
	movl	%eax,bitw_07-4
//	movl	%eax,bitw_08-4
//	movl	%eax,bitw_09-4
//	movl	%eax,bitw_10-4
//	movl	%eax,bitw_11-4
	movl	%eax,bitw_12-4
	movl	%eax,bitw_13-4
	movl	%eax,bitw_14-4
	movl	%eax,bitw_15-4

	movl	GLOBL(GameBitmap),%eax
	addl	$64,%eax		// Line 0
//	movl	%eax,blin_00-4
//	movl	%eax,blin_01-4
	movl	%eax,blin_04-4
	movl	%eax,blin_05-4
//	movl	%eax,blin_08-4
//	movl	%eax,blin_09-4
	movl	%eax,blin_12-4
	movl	%eax,blin_13-4
	addl	$7*4,%eax		// Line 7
//	movl	%eax,blin_02-4
//	movl	%eax,blin_03-4
	movl	%eax,blin_06-4
	movl	%eax,blin_07-4
//	movl	%eax,blin_10-4
//	movl	%eax,blin_11-4
	movl	%eax,blin_14-4
	movl	%eax,blin_15-4

	ret


