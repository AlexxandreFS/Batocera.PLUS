#include "asmdefs.inc"

CODE_SEG

//code for programming the VGA card
//reads in array vgaregs320x240 and setups the registers

//MACROS for the different register types

//CRTC registers
#define MCRTC ; \
	movb %bl,%ah; \
	lodsb; \
	xchgb	%ah,%al; \
	outw %ax,%dx; \
	incb	%bl;

//'general' registers
#define MGEN ; \
	movb	%bl,%ah; \
	lodsb; \
	xchg	%ah,%al; \
	outw	%ax,%dx;

//Attribute registers
#define MATTR ; \
	movw	$0x3da,%dx; \
	inb		%dx,%al; \
	movw	$0x3c0,%dx; \
	movb	%bl,%al; \
	orb		$32,%al; \
	outb	%al,%dx; \
	lodsb; \
	outb	%al,%dx;

FUNC(setarcademode)

	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%edi
	pushl	%esi

	cld
//get our array
	leal	GLOBL(vgaregs320x240),%ecx

//first things first
//clear the protection on the VGA regs
	movw	$0x3d4,%dx
	movb	$0x11,%al
	outb	%al,%dx
	incw	%dx
	inb		%dx,%al
	andb	$127,%al
	movb	%al,%ah
	decw	%dx
	movb	$0x11,%al
	outw	%ax,%dx

//load up the array of values
	movl	%ecx,%esi

//then set the registers

//3c2 misc. output registers
	lodsb
	movw	$0x3c2,%dx
	outb 	%al,%dx

//3d4 the CRTC registers
	movw	$0x3d4,%dx
	movl	$10,%ecx

	xorw 	%bx,%bx
1:
	MCRTC
	loop	1b

	movl	$8,%ecx
	movb	$0x10,%bl
2:
	MCRTC
	loop	2b

//3c4 the sequencer registers
	movw	$0x3c4,%dx
	movb	$1,%bl
	MGEN
	movb	$4,%bl
	MGEN

//3ce - graphics controller registers
	movw	$0x3ce,%dx
	movb	$5,%bl
	MGEN
	movb	$6,%bl
	MGEN

//3c0 - attribute address registers
	movb	$0x10,%bl
	MATTR
	movb	$0x13,%bl
	MATTR


	popl	%esi
	popl	%edi
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax

	ret

