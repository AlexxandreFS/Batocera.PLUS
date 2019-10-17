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

FUNC(raine_blit_x2_y2_32)
#define BASE 36
	pusha
	movl BASE(%esp),%ebx
	movl BASE+4(%esp),%edi
	movl BASE+24(%esp),%ecx // width
	movl BASE+28(%esp),%ebp // height
	addl %ebp,%ebp
	movl (%ebx),%eax
	sall $2,%eax
	movl %eax,GLOBL(src_add)
	movl 64(%edi),%eax // array of lines
	movl 68(%edi),%edx
	subl %eax,%edx // get length of line in bytes
	sall  $3,%ecx
	subl %ecx,%edx
	sarl $3,%ecx
	movl %edx,GLOBL(dest_add)
	movl BASE+12(%esp),%eax // y1
	sall $2,%eax
	movl 64(%eax,%ebx),%esi
	movl BASE+20(%esp),%eax // y2
	sall $2,%eax
	movl BASE+8(%esp),%edx // x1
	sall $2,%edx
	addl %edx,%esi
	movl 64(%eax,%edi),%edi
	movl BASE+16(%esp),%edx // x2
	sall $2,%edx
	addl %edx,%edi
	
#ifdef RAINE_DOS
	pushw	%es

	movw	%dx,%es
#endif

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
#ifdef RAINE_DOS
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
#else
	lodsl
	stosl
	stosl
#endif

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

FUNC(raine_blit_x2_y1_32)

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
	movl BASE+4*3(%esp),%eax
	sall $2,%eax
	movl 64(%eax,%ebx),%esi
	movl BASE+4*5(%esp),%eax // dy
	sall $2,%eax
	movl BASE+4*2(%esp),%edx
	sall $2,%edx
	addl %edx,%esi
	movl 60(%edi),%edx
	movl 64(%eax,%edi),%edi
	movl BASE+4*4(%esp),%eax // dx
	sall $2,%eax
	addl %eax,%edi
	movl BASE+7*4(%esp),%ebp
	
#ifdef RAINE_DOS
	pushw	%es

	movw	%dx,%es
#endif

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
#ifdef RAINE_DOS 
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
#else
	lodsl
	stosl
	stosl
	decl  %ecx
	jnz   0b
#endif

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
