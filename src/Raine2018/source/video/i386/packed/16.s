/******************************************************************************/
/*                                                                            */
/*                   RAINE 8x8 PACKED 4 BPP TILE DRAWING                      */
/*                                                                            */
/******************************************************************************/

/*

Transparent Mapped
Transparent Mapped Swapped
Transparent Mapped Swap Word

*/

#include "asmdefs.inc"

CODE_SEG

FUNC(Draw8x8_Trans_Packed_Mapped_16)

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
	// Notice that eax is initialised here and used later.
	// This is to allow the pentium to execute 2 instructions in //
	// which is possible only the 2 instructions are not doing read
	// and write operations on the same register...
	
	movl	28(%esp),%eax			// x
	movl	%edx,endc_04-4
	movl	36(%esp),%ebp			// cmap
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

	xorl	%edx,%edx
	jmp	9f

	// Explanation of this weirdness (from Karma) :
	// Tests showed that this loop is MUCH faster if it is aligned.
	// So this jump will make the whole thing faster because it will be
	// aligned...

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,4(%edi)
7:
	shr	$16,%eax	// High bits now, same principle
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,12(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_16_FlipY)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-4(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-12(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_16_FlipX)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,4(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,12(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_16_FlipXY)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-4(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-12(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_16)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,12(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,4(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipY)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-12(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-4(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipX)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,12(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,6(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,4(%edi)
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

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipXY)

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
	leal	(%edi,%eax,2),%edi		// x (doubled in 16bpp)

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
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-10(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-8(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-12(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-2(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-6(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movw	(%ebp,%edx,2),%cx
	movw	%cx,14-4(%edi)
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

FUNC(init_spp8x8asm_16)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
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


