/******************************************************************************/
/*                                                                            */
/*                   RAINE 8x8 PACKED 4 BPP TILE DRAWING                      */
/*                                                                            */
/******************************************************************************/

/*
	Functions for packed sprites (2 pixels/byte)
*/

#include "asmdefs.inc"

CODE_SEG

FUNC(Draw8x8_Trans_Packed_Mapped_8)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_04:
	movl	%edx,endc_04-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,6(%edi)
8:
	addl	$4,%esi			// Next Tile Line
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

FUNC(Draw8x8_Trans_Packed_Mapped_8_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_05:
	movl	%edx,endc_05-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,7-1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-6(%edi)
8:
	addl	$4,%esi			// Next Tile Line
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

FUNC(Draw8x8_Trans_Packed_Mapped_8_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_06:
	movl	%edx,endc_06-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,6(%edi)
8:
	addl	$4,%esi			// Next Tile Line
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

FUNC(Draw8x8_Trans_Packed_Mapped_8_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_07:
	movl	%edx,endc_07-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,7-1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-3(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-2(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-6(%edi)
8:
	addl	$4,%esi			// Next Tile Line
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

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_8)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_12:
	movl	%edx,endc_12-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,6(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,2(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_12:
	cmp	$0xDEADBEEF,%esi
endc_12:
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_13:
	movl	%edx,endc_13-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,7-5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-6(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-3(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-2(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	addl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_13:
	cmp	$0xDEADBEEF,%esi
endc_13:
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipX)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_14:
	movl	%edx,endc_14-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,6(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,3(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,2(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_14:
	cmp	$0xDEADBEEF,%esi
endc_14:
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipXY)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp),%esi			// source
	movl	28(%esp),%eax			// y
	movl	%esi,%edx
	sall	$2,%eax
	addl	$8*4,%edx			// tile end
	movl	0xDEADBEEF(%eax),%edi
blin_15:
	movl	%edx,endc_15-4
	movl	32(%esp),%ebp			// cmap
	addl	24(%esp),%edi			// x

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
	movb	(%ebp,%edx),%al
	movb	%al,7-5(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-4(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,(%edi)
7:	testb	%bh,%bh
	jz	7f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-6(%edi)
7:
	shr	$16,%eax
	shr	$16,%ebx

	testb	%al,%al
	jz	7f
	movb	%al,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-1(%edi)
7:	testb	%bl,%bl
	jz	7f
	movb	%bl,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-0(%edi)
7:	testb	%ah,%ah
	jz	7f
	movb	%ah,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-3(%edi)
7:	testb	%bh,%bh
	jz	8f
	movb	%bh,%dl
	movb	(%ebp,%edx),%al
	movb	%al,7-2(%edi)
8:
	addl	$4,%esi			// Next Tile Line
	subl	$0xDEADBEEF,%edi	// Next Screen Line
bitw_15:
	cmp	$0xDEADBEEF,%esi
endc_15:
	jne	9b

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(init_spp8x8asm_8)


	movl	GLOBL(GameBitmap),%eax
	movl	(%eax),%eax		// Width
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


