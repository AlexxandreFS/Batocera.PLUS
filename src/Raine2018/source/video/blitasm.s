/******************************************************************************/
/*                                                                            */
/*                   SOME CUSTOM ASM VIDEO SUPPORT ROUTINES                   */
/*                                                                            */
/******************************************************************************/

#include "asmdefs.inc"

CODE_SEG

/*
 *  BLIT USING REP-MOVSL (slowest)
 */

FUNC(fast_blit_movsl)

	pushal
	pushw	%es

	pushl	%esp

	movl	GLOBL(DestSeg),%eax
	movw	%ax,%es

	pushw	%ds				// Store Data Segment 

	cld					// Set Fowards Copying

	movl	GLOBL(SourceSeg),%eax
	movw	%ax,%ds

	movl	GLOBL(SourceStart),%esi

	movl	GLOBL(DestStart),%edi

	movl	GLOBL(BlitWidth),%eax

	movl	GLOBL(BlitHeight),%ebp

	movl	GLOBL(SourceAdd),%ebx

	movl	GLOBL(DestAdd),%edx

	.align	4,0x90
9:
	movl	%eax,%ecx

	rep
	movsl

	addl	%ebx,%esi
	addl	%edx,%edi

	decl	%ebp
	jne	9b

	popw	%ds				// Restore Data Segment

	popl	%esp

	popw	%es
	popal
	ret

/*
 *  BLIT USING MOVL (faster than rep movsl)
 */

FUNC(fast_blit_movl)

	pushal
	pushw	%es

	pushl	%esp

	movl	GLOBL(DestSeg),%eax
	movw	%ax,%es

	pushw	%ds				// Store Data Segment

	movl	GLOBL(SourceSeg),%eax
	movw	%ax,%ds

	movl	GLOBL(SourceAdd),%eax
	movl	GLOBL(DestAdd),%ebx

	movl	%eax,SMC1-4
	movl	%ebx,SMC2-4

	movl	GLOBL(SourceStart),%esi

	movl	GLOBL(DestStart),%edi

	movl	GLOBL(BlitWidth),%edx

	movl	GLOBL(BlitHeight),%ebp

	shrl	$3,%edx

	.align	4,0x90
9:
	movl	%edx,%ecx
8:
	movl	(%esi),%eax
	movl	4(%esi),%ebx
	movl	%eax,%es:(%edi)
	movl	%ebx,%es:4(%edi)
	movl	8(%esi),%eax
	movl	12(%esi),%ebx
	movl	%eax,%es:8(%edi)
	movl	%ebx,%es:12(%edi)
	movl	16(%esi),%eax
	movl	20(%esi),%ebx
	movl	%eax,%es:16(%edi)
	movl	%ebx,%es:20(%edi)
	movl	24(%esi),%eax
	movl	28(%esi),%ebx
	movl	%eax,%es:24(%edi)
	movl	%ebx,%es:28(%edi)
	addl	$32,%esi
	addl	$32,%edi
	decl	%ecx
	jne	8b

	addl	$0x2164334A,%esi
SMC1:	addl	$0x2164334A,%edi
SMC2:
	decl	%ebp
	jne	9b

	popw	%ds				// Restore Data Segment

	popl	%esp

	popw	%es
	popal
	ret

/*
 *  BLIT USING MMX MOVQ (faster than rep movsl, or movl)
 */

FUNC(fast_blit_movq)

	pushal
#ifdef RAINE_DOS
	pushw	%es
#endif

	pushl	%esp

#ifdef RAINE_DOS
	movl	GLOBL(DestSeg),%eax
	movw	%ax,%es

	pushw	%ds				// Store Data Segment

	movl	GLOBL(SourceSeg),%eax
	movw	%ax,%ds
#endif

	movl	GLOBL(SourceAdd),%eax
	movl	GLOBL(DestAdd),%ebx

	movl	%eax,SMC3-4
	movl	%ebx,SMC4-4

	movl	GLOBL(SourceStart),%esi

	movl	GLOBL(DestStart),%edi

	movl	GLOBL(BlitWidth),%edx

	movl	GLOBL(BlitHeight),%ebp

	shrl	$3,%edx

	.align	4,0x90
9:
	movl	%edx,%ecx
8:
	movq	(%esi),%mm0
	movq	8(%esi),%mm1
	movq	16(%esi),%mm2
	movq	24(%esi),%mm3
#ifdef RAINE_DOS
	movq	%mm0,%es:(%edi)
	movq	%mm1,%es:8(%edi)
	movq	%mm2,%es:16(%edi)
	movq	%mm3,%es:24(%edi)
#else
	movq	%mm0,(%edi)
	movq	%mm1,8(%edi)
	movq	%mm2,16(%edi)
	movq	%mm3,24(%edi)
#endif
	addl	$32,%esi
	addl	$32,%edi
	decl	%ecx
	jne	8b

	addl	$0x2164334A,%esi
SMC3:	addl	$0x2164334A,%edi
SMC4:
	decl	%ebp
	jne	9b

	emms					// Restore MMX regs (fpu regs)?

#ifdef RAINE_DOS
	popw	%ds				// Restore Data Segment
#endif
	popl	%esp

#ifdef RAINE_DOS
	popw	%es
#endif
	popal
	ret

FUNC(fast_palette_update)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx

	cmpl	$0,8+20(%esp)			// test	vsync flag
	jz	set_pallete_no_vsync

	movl	$0x3DA,%edx			// vsync port

vs_loop1:					// wait for retrace to end
	inb	%dx,%al
	testb	$8,%al
	jnz	vs_loop1

vs_loop2:					// wait for retrace to start again
	inb	%dx,%al
	testb	$8,%al
	jz	vs_loop2

set_pallete_no_vsync:
	xorl	%eax,%eax			// eax = start position
	movl	0+20(%esp),%esi			// esi is start of palette
	movl	4+20(%esp),%edi			// edi is start of palette
	movl	$256,%ebp			// ecx = end position
	movl	$0x3C8,%edx			// edx = port index
	outb	%al,%dx				// output palette index
	cld
	incl	%edx

set_pal_loop:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jz	skip_col
tt:
	movl	%ebx,(%edi)
	outsb					// output r
	outsb					// output g
	outsb					// output b
	incl	%esi				// skip filler byte

	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop
	jmp	pal_done

new_col:
	decl	%edx
	outb	%al,%dx				// output palette index
	incl	%edx
	jmp	tt

set_pal_loop2:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jnz	new_col

skip_col:
	addl	$4,%esi
	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop2
pal_done:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

FUNC(fast_palette_update_8) // Same thing for 8bits colours

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx

	cmpl	$0,8+20(%esp)			// test	vsync flag
	jz	3f

	movl	$0x3DA,%edx			// vsync port

1:					// wait for retrace to end
	inb	%dx,%al
	testb	$8,%al
	jnz	1b

2:					// wait for retrace to start again
	inb	%dx,%al
	testb	$8,%al
	jz	2b

3:
	xorl	%eax,%eax			// eax = start position
	movl	0+20(%esp),%esi			// esi is start of palette
	movl	4+20(%esp),%edi			// edi is start of palette
	movl	$256,%ebp			// ecx = end position
	movl	$0x3C8,%edx			// edx = port index
	outb	%al,%dx				// output palette index
	cld
	incl	%edx

set_pal_loopb:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jz	skip_colb
ttb:
	movl	%ebx,(%edi)
	shll	$2,%ebx // Convert to 8bpp
	movl	%ebx,(%esi)
	outsb					// output r
	outsb					// output g
	outsb					// output b
	incl	%esi				// skip filler byte
	shrl	$2,%ebx // Convert back to 6bpp
	movl	%ebx,-4(%esi)

	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loopb
	jmp	pal_done

new_colb:
	decl	%edx
	outb	%al,%dx				// output palette index
	incl	%edx
	jmp	ttb

set_pal_loop2b:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jnz	new_colb

skip_colb:
	addl	$4,%esi
	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop2b
	jmp pal_done	

FUNC(fast_palette_update_vsync_check)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx

	xorl	%eax,%eax			// eax = start position
	movl	0+20(%esp),%esi			// esi is start of palette
	movl	4+20(%esp),%edi			// edi is start of palette
	movl	$256,%ebp			// ecx = end position

set_pal_loop_2a:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jz	skip_col_2a

	pushl	%eax
	movl	$0x3DA,%edx			// vsync port

vs_loop1_b:					// wait for retrace to end
	inb	%dx,%al
	testb	$8,%al
	jnz	vs_loop1_b

vs_loop2_b:					// wait for retrace to start again
	inb	%dx,%al
	testb	$8,%al
	jz	vs_loop2_b

	popl	%eax

	movl	$0x3C9,%edx			// edx = port index+1
	jmp	new_col_3a

skip_col_2a:
	addl	$4,%esi
	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop_2a

	jmp	pal_done_3a

set_pal_loop_3a:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jz	skip_col_3a
tt_3a:
	movl	%ebx,(%edi)
	outsb					// output r
	outsb					// output g
	outsb					// output b
	incl	%esi				// skip filler byte

	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop_3a
	jmp	pal_done_3a

new_col_3a:
	decl	%edx
	outb	%al,%dx				// output palette index
	incl	%edx
	jmp	tt_3a

set_pal_loop2_3a:
	movl	(%esi),%ebx
	cmpl	(%edi),%ebx
	jnz	new_col_3a

skip_col_3a:
	addl	$4,%esi
	addl	$4,%edi
	incl	%eax
	decl	%ebp				// next pallete entry
	jnz	set_pal_loop2_3a

pal_done_3a:

	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret

