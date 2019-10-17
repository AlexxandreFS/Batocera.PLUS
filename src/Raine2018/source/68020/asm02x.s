#include "asmdefs.inc"

FUNC(DoCycles)

	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax

	subl	$8,%esp

	movl	GLOBL(ROM),%eax
	movl	%eax,SMC1-4

	movl	%esp,GLOBL(cyclepos)

	movl	GLOBL(cycles),%eax
	movl	%eax,(%esp)

	movl	$SMC2,%eax
	movl	%eax,4(%esp)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
SMC1:
	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
SMC2:

	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popl	%ebp

	ret
