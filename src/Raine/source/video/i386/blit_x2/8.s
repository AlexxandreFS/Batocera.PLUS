/******************************************************************************/
/*                                                                            */
/*                         RAINE DOUBLE SIZE BLITTING                         */
/*                                                                            */
/******************************************************************************/

#include "asmdefs.inc"

CODE_SEG

.lcomm GLOBL(src_add),4
.lcomm GLOBL(dest_add),4

/*

double width and height

*/

FUNC(raine_blit_x2_y2)

#define BASE 36
	pusha
	movl BASE(%esp),%ebx
	movl BASE+4(%esp),%edi
	movl BASE+24(%esp),%ecx
	movl BASE+28(%esp),%ebp
	addl %ebp,%ebp
	movl (%ebx),%eax
	movl %eax,GLOBL(src_add)
	movl 64(%edi),%eax
	movl 68(%edi),%edx
	subl %eax,%edx
	leal (%ecx,%ecx),%eax
	subl %eax,%edx
	movl %edx,GLOBL(dest_add)
#ifdef RAINE_DOS
	movl 60(%edi),%edx
#endif
	movl BASE+12(%esp),%eax
	sall $2,%eax
	sarl $2,%ecx
	movl 64(%eax,%ebx),%esi
	movl BASE+20(%esp),%eax
	sall $2,%eax
	addl BASE+8(%esp),%esi
	movl 64(%eax,%edi),%edi
	addl BASE+16(%esp),%edi
	movl %ebp,%eax
	
#ifdef RAINE_DOS
	pushw	%es

	movw	%dx,%es
#endif

	movl	%eax,%ebp

	movl	%ecx,shit_03 - 4

	movl	GLOBL(src_add),%eax
	movl	GLOBL(dest_add),%ebx
	movl	%eax,shit_00 - 4
	movl	%ebx,shit_01 - 4
	jmp	1f
	.align	4
1:
	movl	$0xDEADBEEF,%ecx
shit_03:
	pushl	%esi
0:
	movl	(%esi),%eax
	movl	%eax,%ebx
	bswap	%eax
	xchgw	%ax,%bx
	roll	$8,%eax
	rorl	$8,%ebx
#ifdef RAINE_DOS
	movl	%eax,%es:(%edi)
	addl	$4,%esi
	movl	%ebx,%es:4(%edi)
#else
	movl	%eax,(%edi)
	addl	$4,%esi
	movl	%ebx,4(%edi)
#endif
	addl	$8,%edi

	decl	%ecx
	jnz	0b

	popl	%esi

	testl	$0x01,%ebp
	jz	3f
	addl	$0xDEADBEEF,%esi
3:
shit_00:
	addl	$0xDEADBEEF,%edi
shit_01:
	decl	%ebp
	jne	1b

#ifdef RAINE_DOS
	popw	%es
#endif
	
	popa
	ret

/*

double width only

*/

FUNC(raine_blit_x2_y1)

	pusha
	movl BASE(%esp),%ebx
	movl BASE+4(%esp),%edi
	movl BASE+6*4(%esp),%ecx
	movl (%ebx),%eax
	movl %eax,GLOBL(src_add)
	movl 64(%edi),%eax
	movl 68(%edi),%edx
	subl %eax,%edx
	leal (%ecx,%ecx),%eax
	subl %eax,%edx
	movl %edx,GLOBL(dest_add)
	movl 60(%edi),%edx
	movl BASE+4*3(%esp),%eax
	sall $2,%eax
	sarl $2,%ecx
	movl 64(%eax,%ebx),%esi
	movl BASE+4*5(%esp),%eax
	sall $2,%eax
	addl BASE+4*2(%esp),%esi
	movl 64(%eax,%edi),%edi
	movl BASE+4*7(%esp),%eax
	addl BASE+4*4(%esp),%edi
	
#ifdef RAINE_DOS
	pushw	%es

	movw	%dx,%es
#endif

	movl	%eax,%ebp

	movl	%ecx,poop_03 - 4

	movl	GLOBL(src_add),%eax
	movl	GLOBL(dest_add),%ebx
	movl	%eax,poop_00 - 4
	movl	%ebx,poop_01 - 4
	jmp	1f
	.align	4
1:
	movl	$0xDEADBEEF,%ecx
poop_03:
	pushl	%esi
0:
	movl	(%esi),%eax
	movl	%eax,%ebx
	bswap	%eax
	xchgw	%ax,%bx
	roll	$8,%eax
	rorl	$8,%ebx
#ifdef RAINE_DOS
	movl	%eax,%es:(%edi)
	addl	$4,%esi
	movl	%ebx,%es:4(%edi)
#else
	movl	%eax,(%edi)
	addl	$4,%esi
	movl	%ebx,4(%edi)
#endif
	addl	$8,%edi

	decl	%ecx
	jnz	0b

	popl	%esi

	addl	$0xDEADBEEF,%esi
poop_00:
	addl	$0xDEADBEEF,%edi
poop_01:
	decl	%ebp
	jne	1b

#ifdef RAINE_DOS
	popw	%es
#endif
	
	popa
	ret
