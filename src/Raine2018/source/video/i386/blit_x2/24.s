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

FUNC(raine_blit_x2_y2_24)

	pushl %ebp
	pushl %edi
	pushl %esi
	pushl %ebx
	movl 20(%esp),%ebx
	movl 24(%esp),%edi
	movl 44(%esp),%ecx
	movl 48(%esp),%ebp
	addl %ebp,%ebp
	movl (%ebx),%eax
	movl %eax,GLOBL(src_add)
	movl 64(%edi),%eax
	movl 68(%edi),%edx
	subl %eax,%edx
	leal (%ecx,%ecx),%eax
	subl %eax,%edx
	movl %edx,GLOBL(dest_add)
	movl 60(%edi),%edx
	movl 32(%esp),%eax
	sall $2,%eax
	sarl $2,%ecx
	movl 64(%eax,%ebx),%esi
	movl 40(%esp),%eax
	sall $2,%eax
	addl 28(%esp),%esi
	movl 64(%eax,%edi),%edi
	addl 36(%esp),%edi
	movl %ebp,%eax
	
	pushal
	pushw	%es

	movw	%dx,%es

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
	movl	%eax,%es:(%edi)
	addl	$4,%esi
	movl	%ebx,%es:4(%edi)
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

	popw	%es
	popal
	
	popl %ebx
	popl %esi
	popl %edi
	popl %ebp
	ret

/*

double width only

*/

FUNC(raine_blit_x2_y1_24)

	pushl %edi
	pushl %esi
	pushl %ebx
	movl 16(%esp),%ebx
	movl 20(%esp),%edi
	movl 40(%esp),%ecx
	movl (%ebx),%eax
	movl %eax,GLOBL(src_add)
	movl 64(%edi),%eax
	movl 68(%edi),%edx
	subl %eax,%edx
	leal (%ecx,%ecx),%eax
	subl %eax,%edx
	movl %edx,GLOBL(dest_add)
	movl 60(%edi),%edx
	movl 28(%esp),%eax
	sall $2,%eax
	sarl $2,%ecx
	movl 64(%eax,%ebx),%esi
	movl 36(%esp),%eax
	sall $2,%eax
	addl 24(%esp),%esi
	movl 64(%eax,%edi),%edi
	movl 44(%esp),%eax
	addl 32(%esp),%edi
	
	pushal
	pushw	%es

	movw	%dx,%es

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
	movl	%eax,%es:(%edi)
	addl	$4,%esi
	movl	%ebx,%es:4(%edi)
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

	popw	%es
	popal
	
	popl %ebx
	popl %esi
	popl %edi
	ret
