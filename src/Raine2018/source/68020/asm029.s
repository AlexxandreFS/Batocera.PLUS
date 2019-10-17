

FUNC(op_54c0)

	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_372
	movl	$255,%edx
L_9_372:
	movb	%dl,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9000:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9000:
	ret

FUNC(op_54c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9000:
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%edx,%ecx),%bx
	movl	%eax,%esi
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	jne	L_9_401
	movl	%ebx,%edi
	decl	%edi
	movw	%di,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_401
	movl	GLOBL(regs)+88,%edx
	movswl	%si,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_426
	.align	2,0x90
L_9_401:
	addl	$4,GLOBL(regs)+88
L_9_426:
	popl	%eax
	decl	%eax
	jl	JJ_9001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9001:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9001:
	ret

FUNC(op_54d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_429
	movl	$255,%ecx
L_9_429:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9002:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9002:
	ret

FUNC(op_54d8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	testb	$1,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_458
	movl	$255,%ecx
L_9_458:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9003:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9003:
	ret

FUNC(op_54e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	testb	$1,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_487
	movl	$255,%ecx
L_9_487:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9004:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9004:
	ret

FUNC(op_54e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9001:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_517
	movl	$255,%ecx
L_9_517:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9005:
	ret

FUNC(op_54f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9006:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_548
	movswl	%di,%edi
L_9_548:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_549
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_550
	movl	%ebp,%ebx
L_9_550:
	testl	$64,%esi
	je	L_9_551
	movl	%ebp,%edi
L_9_551:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_552
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_552:
	cmpl	$48,%edx
	jne	L_9_555
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_555:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_558
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_558:
	cmpl	$3,16-16(%esp)
	jne	L_9_561
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_561:
	andl	$4,%esi
	jne	L_9_564
	addl	%edi,%ebx
L_9_564:
	cmpl	$0,16-16(%esp)
	je	L_9_565
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_565:
	testl	%esi,%esi
	je	L_9_568
	addl	%edi,%ebx
L_9_568:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_579
	.align	2,0x90
L_9_549:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_579:
	testb	$1,regflags
	sete	%al
	xorl	%ebx,%ebx
	testb	$1,%al
	je	L_9_571
	movl	$255,%ebx
L_9_571:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9006:
	ret

FUNC(op_54f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9002:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_601
	movl	$255,%ecx
L_9_601:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9012:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9007:
	ret

FUNC(op_54f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9003:
	bswapl	%edx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_631
	movl	$255,%ecx
L_9_631:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9013:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9008:
	ret

FUNC(op_54fa)

	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_661
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9014:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9009:
	ret
	.align	2,0x90
L_9_661:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9010:
	ret

FUNC(op_54fb)

	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_690
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9016:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9011:
	ret
	.align	2,0x90
L_9_690:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9012:
	ret

FUNC(op_54fc)

	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_9_718
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9013:
	ret
	.align	2,0x90
L_9_718:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9014:
	ret

FUNC(op_55c0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$1,regflags
	je	L_9_746
	movl	$255,%edx
L_9_746:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9020:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9015:
	ret

FUNC(op_55c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9004:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$1,regflags
	jne	L_9_775
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_775
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_800
	.align	2,0x90
L_9_775:
	addl	$4,GLOBL(regs)+88
L_9_800:
	popl	%eax
	decl	%eax
	jl	JJ_9016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9021:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9016:
	ret

FUNC(op_55d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$1,regflags
	je	L_9_803
	movl	$255,%ecx
L_9_803:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9022:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9017:
	ret

FUNC(op_55d8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$1,regflags
	je	L_9_832
	movl	$255,%ecx
L_9_832:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9018:
	ret

FUNC(op_55e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	xorl	%ecx,%ecx
	testb	$1,regflags
	je	L_9_861
	movl	$255,%ecx
L_9_861:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9024:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9019:
	ret

FUNC(op_55e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9005:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$1,regflags
	je	L_9_891
	movl	$255,%ecx
L_9_891:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9020:
	ret

FUNC(op_55f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9026:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_922
	movswl	%di,%edi
L_9_922:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_923
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_924
	movl	%ebp,%ebx
L_9_924:
	testl	$64,%esi
	je	L_9_925
	movl	%ebp,%edi
L_9_925:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_926
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9027:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_926:
	cmpl	$48,%edx
	jne	L_9_929
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9028:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_929:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_932
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9029:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_932:
	cmpl	$3,16-16(%esp)
	jne	L_9_935
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9030:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_935:
	andl	$4,%esi
	jne	L_9_938
	addl	%edi,%ebx
L_9_938:
	cmpl	$0,16-16(%esp)
	je	L_9_939
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_939:
	testl	%esi,%esi
	je	L_9_942
	addl	%edi,%ebx
L_9_942:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_954
	.align	2,0x90
L_9_923:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_954:
	xorl	%ebx,%ebx
	testb	$1,regflags
	je	L_9_945
	movl	$255,%ebx
L_9_945:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9031:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9021:
	ret

FUNC(op_55f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9006:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$1,regflags
	je	L_9_975
	movl	$255,%ecx
L_9_975:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9032:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9022:
	ret

FUNC(op_55f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9007:
	bswapl	%edx
	testb	$1,regflags
	je	L_9_1005
	movl	$255,%ecx
L_9_1005:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9033:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9023:
	ret

FUNC(op_55fa)

	testb	$1,regflags
	je	L_9_1035
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9034:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9024:
	ret
	.align	2,0x90
L_9_1035:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9025:
	ret

FUNC(op_55fb)

	testb	$1,regflags
	je	L_9_1064
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9036:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9026:
	ret
	.align	2,0x90
L_9_1064:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9027:
	ret

FUNC(op_55fc)

	testb	$1,regflags
	je	L_9_1092
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9038:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9028:
	ret
	.align	2,0x90
L_9_1092:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9039:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9029:
	ret

FUNC(op_56c0)

	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1120
	movl	$255,%edx
L_9_1120:
	movb	%dl,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9040:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9030:
	ret

FUNC(op_56c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9008:
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%edx,%ecx),%bx
	movl	%eax,%esi
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	jne	L_9_1149
	movl	%ebx,%edi
	decl	%edi
	movw	%di,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_1149
	movl	GLOBL(regs)+88,%edx
	movswl	%si,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_1174
	.align	2,0x90
L_9_1149:
	addl	$4,GLOBL(regs)+88
L_9_1174:
	popl	%eax
	decl	%eax
	jl	JJ_9031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9031:
	ret

FUNC(op_56d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1177
	movl	$255,%ecx
L_9_1177:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9042:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9032:
	ret

FUNC(op_56d8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	testb	$64,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_1206
	movl	$255,%ecx
L_9_1206:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9033:
	ret

FUNC(op_56e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	testb	$64,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_1235
	movl	$255,%ecx
L_9_1235:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9044:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9034:
	ret

FUNC(op_56e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9009:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1265
	movl	$255,%ecx
L_9_1265:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9045:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9035:
	ret

FUNC(op_56f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9046:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_1296
	movswl	%di,%edi
L_9_1296:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_1297
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_1298
	movl	%ebp,%ebx
L_9_1298:
	testl	$64,%esi
	je	L_9_1299
	movl	%ebp,%edi
L_9_1299:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_1300
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9047:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_1300:
	cmpl	$48,%edx
	jne	L_9_1303
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9048:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_1303:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_1306
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9049:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_1306:
	cmpl	$3,16-16(%esp)
	jne	L_9_1309
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9050:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_1309:
	andl	$4,%esi
	jne	L_9_1312
	addl	%edi,%ebx
L_9_1312:
	cmpl	$0,16-16(%esp)
	je	L_9_1313
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_1313:
	testl	%esi,%esi
	je	L_9_1316
	addl	%edi,%ebx
L_9_1316:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_1329
	.align	2,0x90
L_9_1297:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_1329:
	testb	$64,regflags
	sete	%al
	xorl	%ebx,%ebx
	testb	$1,%al
	je	L_9_1319
	movl	$255,%ebx
L_9_1319:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9051:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9036:
	ret

FUNC(op_56f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9010:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1349
	movl	$255,%ecx
L_9_1349:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9037:
	ret

FUNC(op_56f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9011:
	bswapl	%edx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1379
	movl	$255,%ecx
L_9_1379:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9038:
	ret

FUNC(op_56fa)

	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1409
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9054:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9039:
	ret
	.align	2,0x90
L_9_1409:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9040:
	ret

FUNC(op_56fb)

	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1438
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9056:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9041:
	ret
	.align	2,0x90
L_9_1438:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9057:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9042:
	ret

FUNC(op_56fc)

	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_9_1466
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9043:
	ret
	.align	2,0x90
L_9_1466:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9044:
	ret

FUNC(op_57c0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$64,regflags
	je	L_9_1494
	movl	$255,%edx
L_9_1494:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9060:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9045:
	ret

FUNC(op_57c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9012:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$64,regflags
	jne	L_9_1523
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_1523
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_1548
	.align	2,0x90
L_9_1523:
	addl	$4,GLOBL(regs)+88
L_9_1548:
	popl	%eax
	decl	%eax
	jl	JJ_9046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9046:
	ret

FUNC(op_57d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$64,regflags
	je	L_9_1551
	movl	$255,%ecx
L_9_1551:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9047:
	ret

FUNC(op_57d8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$64,regflags
	je	L_9_1580
	movl	$255,%ecx
L_9_1580:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9063:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9048:
	ret

FUNC(op_57e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	xorl	%ecx,%ecx
	testb	$64,regflags
	je	L_9_1609
	movl	$255,%ecx
L_9_1609:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9049:
	ret

FUNC(op_57e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9013:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$64,regflags
	je	L_9_1639
	movl	$255,%ecx
L_9_1639:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9050:
	ret

FUNC(op_57f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9066:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_1670
	movswl	%di,%edi
L_9_1670:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_1671
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_1672
	movl	%ebp,%ebx
L_9_1672:
	testl	$64,%esi
	je	L_9_1673
	movl	%ebp,%edi
L_9_1673:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_1674
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9067:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_1674:
	cmpl	$48,%edx
	jne	L_9_1677
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9068:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_1677:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_1680
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9069:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_1680:
	cmpl	$3,16-16(%esp)
	jne	L_9_1683
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9070:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_1683:
	andl	$4,%esi
	jne	L_9_1686
	addl	%edi,%ebx
L_9_1686:
	cmpl	$0,16-16(%esp)
	je	L_9_1687
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_1687:
	testl	%esi,%esi
	je	L_9_1690
	addl	%edi,%ebx
L_9_1690:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_1704
	.align	2,0x90
L_9_1671:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_1704:
	xorl	%ebx,%ebx
	testb	$64,regflags
	je	L_9_1693
	movl	$255,%ebx
L_9_1693:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9071:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9051:
	ret

FUNC(op_57f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9014:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$64,regflags
	je	L_9_1723
	movl	$255,%ecx
L_9_1723:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9072:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9052:
	ret

FUNC(op_57f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9015:
	bswapl	%edx
	testb	$64,regflags
	je	L_9_1753
	movl	$255,%ecx
L_9_1753:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9073:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9053:
	ret

FUNC(op_57fa)

	testb	$64,regflags
	je	L_9_1783
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9074:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9054:
	ret
	.align	2,0x90
L_9_1783:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9075:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9055:
	ret

FUNC(op_57fb)

	testb	$64,regflags
	je	L_9_1812
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9056:
	ret
	.align	2,0x90
L_9_1812:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9057:
	ret

FUNC(op_57fc)

	testb	$64,regflags
	je	L_9_1840
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9058:
	ret
	.align	2,0x90
L_9_1840:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9059:
	ret

FUNC(op_58c0)

	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_1868
	movl	$255,%edx
L_9_1868:
	movb	%dl,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9060:
	ret

FUNC(op_58c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9016:
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%edx,%ecx),%bx
	movl	%eax,%esi
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	jne	L_9_1897
	movl	%ebx,%edi
	decl	%edi
	movw	%di,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_1897
	movl	GLOBL(regs)+88,%edx
	movswl	%si,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_1922
	.align	2,0x90
L_9_1897:
	addl	$4,GLOBL(regs)+88
L_9_1922:
	popl	%eax
	decl	%eax
	jl	JJ_9061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9061:
	ret

FUNC(op_58d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_1925
	movl	$255,%ecx
L_9_1925:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9062:
	ret

FUNC(op_58d8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	testb	$8,regflags+1
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_1954
	movl	$255,%ecx
L_9_1954:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9063:
	ret

FUNC(op_58e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	testb	$8,regflags+1
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_1983
	movl	$255,%ecx
L_9_1983:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9064:
	ret

FUNC(op_58e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9017:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2013
	movl	$255,%ecx
L_9_2013:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9085:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9065:
	ret

FUNC(op_58f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9086:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_2044
	movswl	%di,%edi
L_9_2044:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_2045
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_2046
	movl	%ebp,%ebx
L_9_2046:
	testl	$64,%esi
	je	L_9_2047
	movl	%ebp,%edi
L_9_2047:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_2048
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9087:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_2048:
	cmpl	$48,%edx
	jne	L_9_2051
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9088:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_2051:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_2054
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9089:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2054:
	cmpl	$3,16-16(%esp)
	jne	L_9_2057
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9090:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2057:
	andl	$4,%esi
	jne	L_9_2060
	addl	%edi,%ebx
L_9_2060:
	cmpl	$0,16-16(%esp)
	je	L_9_2061
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_2061:
	testl	%esi,%esi
	je	L_9_2064
	addl	%edi,%ebx
L_9_2064:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_2079
	.align	2,0x90
L_9_2045:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_2079:
	testb	$8,regflags+1
	sete	%al
	xorl	%ebx,%ebx
	testb	$1,%al
	je	L_9_2067
	movl	$255,%ebx
L_9_2067:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9066:
	ret

FUNC(op_58f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9018:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2097
	movl	$255,%ecx
L_9_2097:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9092:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9067:
	ret

FUNC(op_58f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9019:
	bswapl	%edx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2127
	movl	$255,%ecx
L_9_2127:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9093:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9068:
	ret

FUNC(op_58fa)

	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2157
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9069:
	ret
	.align	2,0x90
L_9_2157:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9070:
	ret

FUNC(op_58fb)

	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2186
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9071:
	ret
	.align	2,0x90
L_9_2186:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9072:
	ret

FUNC(op_58fc)

	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_9_2214
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9073:
	ret
	.align	2,0x90
L_9_2214:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9074:
	ret

FUNC(op_59c0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$8,regflags+1
	je	L_9_2242
	movl	$255,%edx
L_9_2242:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9075:
	ret

FUNC(op_59c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9020:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$8,regflags+1
	jne	L_9_2271
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_2271
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_2296
	.align	2,0x90
L_9_2271:
	addl	$4,GLOBL(regs)+88
L_9_2296:
	popl	%eax
	decl	%eax
	jl	JJ_9076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9076:
	ret

FUNC(op_59d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$8,regflags+1
	je	L_9_2299
	movl	$255,%ecx
L_9_2299:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9077:
	ret

FUNC(op_59d8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$8,regflags+1
	je	L_9_2328
	movl	$255,%ecx
L_9_2328:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9103:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9078:
	ret

FUNC(op_59e0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	xorl	%ecx,%ecx
	testb	$8,regflags+1
	je	L_9_2357
	movl	$255,%ecx
L_9_2357:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9079:
	ret

FUNC(op_59e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9021:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$8,regflags+1
	je	L_9_2387
	movl	$255,%ecx
L_9_2387:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9080:
	ret

FUNC(op_59f0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9106:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_2418
	movswl	%di,%edi
L_9_2418:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_2419
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_2420
	movl	%ebp,%ebx
L_9_2420:
	testl	$64,%esi
	je	L_9_2421
	movl	%ebp,%edi
L_9_2421:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_2422
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9107:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_2422:
	cmpl	$48,%edx
	jne	L_9_2425
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9108:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_2425:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_2428
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9109:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2428:
	cmpl	$3,16-16(%esp)
	jne	L_9_2431
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9110:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2431:
	andl	$4,%esi
	jne	L_9_2434
	addl	%edi,%ebx
L_9_2434:
	cmpl	$0,16-16(%esp)
	je	L_9_2435
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_2435:
	testl	%esi,%esi
	je	L_9_2438
	addl	%edi,%ebx
L_9_2438:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_2454
	.align	2,0x90
L_9_2419:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_2454:
	xorl	%ebx,%ebx
	testb	$8,regflags+1
	je	L_9_2441
	movl	$255,%ebx
L_9_2441:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9081:
	ret

FUNC(op_59f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9022:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$8,regflags+1
	je	L_9_2471
	movl	$255,%ecx
L_9_2471:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9082:
	ret

FUNC(op_59f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9023:
	bswapl	%edx
	testb	$8,regflags+1
	je	L_9_2501
	movl	$255,%ecx
L_9_2501:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9083:
	ret

FUNC(op_59fa)

	testb	$8,regflags+1
	je	L_9_2531
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9084:
	ret
	.align	2,0x90
L_9_2531:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9085:
	ret

FUNC(op_59fb)

	testb	$8,regflags+1
	je	L_9_2560
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9086:
	ret
	.align	2,0x90
L_9_2560:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9087:
	ret

FUNC(op_59fc)

	testb	$8,regflags+1
	je	L_9_2588
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9088:
	ret
	.align	2,0x90
L_9_2588:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9089:
	ret

FUNC(op_5ac0)

	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2616
	movl	$255,%edx
L_9_2616:
	movb	%dl,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9090:
	ret

FUNC(op_5ac8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9024:
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%edx,%ecx),%bx
	movl	%eax,%esi
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	jne	L_9_2645
	movl	%ebx,%edi
	decl	%edi
	movw	%di,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_2645
	movl	GLOBL(regs)+88,%edx
	movswl	%si,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_2670
	.align	2,0x90
L_9_2645:
	addl	$4,GLOBL(regs)+88
L_9_2670:
	popl	%eax
	decl	%eax
	jl	JJ_9091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9091:
	ret

FUNC(op_5ad0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2673
	movl	$255,%ecx
L_9_2673:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9092:
	ret

FUNC(op_5ad8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	testb	$128,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_2702
	movl	$255,%ecx
L_9_2702:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9093:
	ret

FUNC(op_5ae0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	testb	$128,regflags
	sete	%al
	xorl	%ecx,%ecx
	testb	$1,%al
	je	L_9_2731
	movl	$255,%ecx
L_9_2731:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9094:
	ret

FUNC(op_5ae8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9025:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2761
	movl	$255,%ecx
L_9_2761:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9095:
	ret

FUNC(op_5af0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9126:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_2792
	movswl	%di,%edi
L_9_2792:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_2793
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_2794
	movl	%ebp,%ebx
L_9_2794:
	testl	$64,%esi
	je	L_9_2795
	movl	%ebp,%edi
L_9_2795:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_2796
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9127:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_2796:
	cmpl	$48,%edx
	jne	L_9_2799
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9128:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_2799:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_2802
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9129:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2802:
	cmpl	$3,16-16(%esp)
	jne	L_9_2805
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9130:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_2805:
	andl	$4,%esi
	jne	L_9_2808
	addl	%edi,%ebx
L_9_2808:
	cmpl	$0,16-16(%esp)
	je	L_9_2809
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_2809:
	testl	%esi,%esi
	je	L_9_2812
	addl	%edi,%ebx
L_9_2812:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_2829
	.align	2,0x90
L_9_2793:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_2829:
	testb	$128,regflags
	sete	%al
	xorl	%ebx,%ebx
	testb	$1,%al
	je	L_9_2815
	movl	$255,%ebx
L_9_2815:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9096:
	ret

FUNC(op_5af8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9026:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2845
	movl	$255,%ecx
L_9_2845:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9097:
	ret

FUNC(op_5af9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9027:
	bswapl	%edx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2875
	movl	$255,%ecx
L_9_2875:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9098:
	ret

FUNC(op_5afa)

	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2905
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9099:
	ret
	.align	2,0x90
L_9_2905:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9100:
	ret

FUNC(op_5afb)

	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2934
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9101:
	ret
	.align	2,0x90
L_9_2934:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9102:
	ret

FUNC(op_5afc)

	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_9_2962
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9103:
	ret
	.align	2,0x90
L_9_2962:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9104:
	ret

FUNC(op_5bc0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$128,regflags
	je	L_9_2990
	movl	$255,%edx
L_9_2990:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9105:
	ret

FUNC(op_5bc8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9028:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$128,regflags
	jne	L_9_3019
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_9_3019
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_3044
	.align	2,0x90
L_9_3019:
	addl	$4,GLOBL(regs)+88
L_9_3044:
	popl	%eax
	decl	%eax
	jl	JJ_9106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9106:
	ret

FUNC(op_5bd0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$128,regflags
	je	L_9_3047
	movl	$255,%ecx
L_9_3047:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9107:
	ret

FUNC(op_5bd8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$128,regflags
	je	L_9_3076
	movl	$255,%ecx
L_9_3076:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9108:
	ret

FUNC(op_5be0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%ecx)
	xorl	%ecx,%ecx
	testb	$128,regflags
	je	L_9_3105
	movl	$255,%ecx
L_9_3105:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9109:
	ret

FUNC(op_5be8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9029:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$128,regflags
	je	L_9_3135
	movl	$255,%ecx
L_9_3135:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9110:
	ret

FUNC(op_5bf0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9146:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_3166
	movswl	%di,%edi
L_9_3166:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_3167
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_3168
	movl	%ebp,%ebx
L_9_3168:
	testl	$64,%esi
	je	L_9_3169
	movl	%ebp,%edi
L_9_3169:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_3170
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9147:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_3170:
	cmpl	$48,%edx
	jne	L_9_3173
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9148:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_3173:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_3176
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9149:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_3176:
	cmpl	$3,16-16(%esp)
	jne	L_9_3179
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9150:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_3179:
	andl	$4,%esi
	jne	L_9_3182
	addl	%edi,%ebx
L_9_3182:
	cmpl	$0,16-16(%esp)
	je	L_9_3183
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_3183:
	testl	%esi,%esi
	je	L_9_3186
	addl	%edi,%ebx
L_9_3186:
	leal	(%ebp,%ebx),%edx
	jmp	L_9_3204
	.align	2,0x90
L_9_3167:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_9_3204:
	xorl	%ebx,%ebx
	testb	$128,regflags
	je	L_9_3189
	movl	$255,%ebx
L_9_3189:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9111:
	ret

FUNC(op_5bf8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_9030:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$128,regflags
	je	L_9_3219
	movl	$255,%ecx
L_9_3219:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9112:
	ret

FUNC(op_5bf9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_9031:
	bswapl	%edx
	testb	$128,regflags
	je	L_9_3249
	movl	$255,%ecx
L_9_3249:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9113:
	ret

FUNC(op_5bfa)

	testb	$128,regflags
	je	L_9_3279
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9114:
	ret
	.align	2,0x90
L_9_3279:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9115:
	ret

FUNC(op_5bfb)

	testb	$128,regflags
	je	L_9_3308
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9116:
	ret
	.align	2,0x90
L_9_3308:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9117:
	ret

FUNC(op_5bfc)

	testb	$128,regflags
	je	L_9_3336
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9118
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9118:
	ret
	.align	2,0x90
L_9_3336:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9119
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9119:
	ret

FUNC(op_5cc0)

	movl	%eax,%ebx
	andl	$7,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3364
	movl	$255,%ecx
L_9_3364:
	movb	%cl,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9120
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9120:
	ret

FUNC(op_5cc8)

	andl	$7,%eax
	leal	0(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9032:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ebp
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	movl	$GLOBL(regs),%ebx
	shrb	$3,%al
	movw	(%ecx,%ebx),%si
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3393
	movl	%esi,%edi
	decl	%edi
	movw	%di,(%ecx,%ebx)
	testw	%si,%si
	je	L_9_3393
	movl	GLOBL(regs)+88,%edx
	movswl	%bp,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_3418
	.align	2,0x90
L_9_3393:
	addl	$4,GLOBL(regs)+88
L_9_3418:
	popl	%eax
	decl	%eax
	jl	JJ_9121
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9121:
	ret

FUNC(op_5cd0)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3421
	movl	$255,%ecx
L_9_3421:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9122
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9122:
	ret

FUNC(op_5cd8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3450
	movl	$255,%ecx
L_9_3450:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9123
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9123:
	ret

FUNC(op_5ce0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,(%eax,%ecx)
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3479
	movl	$255,%ecx
L_9_3479:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9124
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9124:
	ret

FUNC(op_5ce8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9033:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%ebx
	addl	%eax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3509
	movl	$255,%ecx
L_9_3509:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9125
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9125:
	ret

FUNC(op_5cf0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_9166:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_9_3540
	movswl	%di,%edi
L_9_3540:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_9_3541
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_9_3542
	movl	%ebp,%ebx
L_9_3542:
	testl	$64,%esi
	je	L_9_3543
	movl	%ebp,%edi
L_9_3543:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_9_3544
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_9167:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_9_3544:
	cmpl	$48,%edx
	jne	L_9_3547
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9168:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_9_3547:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_9_3550
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_9169:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_3550:
	cmpl	$3,16-16(%esp)
	jne	L_9_3553
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_9170:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_9_3553:
	andl	$4,%esi
	jne	L_9_3556
	addl	%edi,%ebx
L_9_3556:
	cmpl	$0,16-16(%esp)
	je	L_9_3557
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_9_3557:
	testl	%esi,%esi
	je	L_9_3560
	addl	%edi,%ebx
L_9_3560:
	leal	(%ebp,%ebx),%esi
	jmp	L_9_3579
	.align	2,0x90
L_9_3541:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%esi
L_9_3579:
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ebx,%ebx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3563
	movl	$255,%ebx
L_9_3563:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9126
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9126:
	ret

FUNC(op_5cf8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9034:
	rolw	$8,%si
	movl	%esi,%eax
	movswl	%ax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3593
	movl	$255,%ecx
L_9_3593:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9127
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9127:
	ret

FUNC(op_5cf9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_9035:
	bswapl	%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3623
	movl	$255,%ecx
L_9_3623:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9128
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9128:
	ret

FUNC(op_5cfa)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3653
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9129
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9129:
	ret
	.align	2,0x90
L_9_3653:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9130
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9130:
	ret

FUNC(op_5cfb)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3682
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9131
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9131:
	ret
	.align	2,0x90
L_9_3682:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9132
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9132:
	ret

FUNC(op_5cfc)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3710
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_9133
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9133:
	ret
	.align	2,0x90
L_9_3710:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9134
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9134:
	ret

FUNC(op_5dc0)

	movl	%eax,%ebx
	andl	$7,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3738
	movl	$255,%ecx
L_9_3738:
	movb	%cl,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9135
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9135:
	ret

FUNC(op_5dc8)

	andl	$7,%eax
	leal	0(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_9036:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ebp
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	movl	$GLOBL(regs),%ebx
	shrb	$3,%al
	movw	(%ecx,%ebx),%si
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_9_3767
	movl	%esi,%edi
	decl	%edi
	movw	%di,(%ecx,%ebx)
	testw	%si,%si
	je	L_9_3767
	movl	GLOBL(regs)+88,%edx
	movswl	%bp,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_9_3792
	.align	2,0x90
L_9_3767:
	addl	$4,GLOBL(regs)+88
L_9_3792:
	popl	%eax
	decl	%eax
	jl	JJ_9136
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9136:
	ret

FUNC(op_5dd0)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3795
	movl	$255,%ecx
L_9_3795:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9137
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9137:
	ret

FUNC(op_5dd8)

	movl	%eax,%ecx
	andl	$7,%ecx
	leal	8(%ecx),%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%ecx
	movl	(%eax,%edx),%ebx
	addl	%ebx,%ecx
	movl	%ecx,(%eax,%edx)
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3824
	movl	$255,%ecx
L_9_3824:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9138
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9138:
	ret

FUNC(op_5de0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,(%eax,%ecx)
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3853
	movl	$255,%ecx
L_9_3853:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9139
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9139:
	ret

FUNC(op_5de8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_9037:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%ebx
	addl	%eax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_9_3883
	movl	$255,%ecx
L_9_3883:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_9140
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_9185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_9140:
	ret
.comm	GLOBL(R24),1024
.comm	GLOBL(W24),1024
.comm	GLOBL(ROM),4
.comm	_RAM,4
.comm	_GFX,4
.comm	_SMP,4
.comm	_EEPROM,4
.comm	_Z80ROM,4
.comm	_ByteRead,4
.comm	_WordRead,4
.comm	_LongRead,4
.comm	_ByteWrite,4
.comm	_WordWrite,4
.comm	_LongWrite,4
.comm	regflags,8
.comm	GLOBL(regs),180


FUNC(Init020_09)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_9000-4
	movl	%eax,RR0_9001-4
	movl	%eax,RR0_9002-4
	movl	%eax,RR0_9003-4
	movl	%eax,RR0_9004-4
	movl	%eax,RR0_9005-4
	movl	%eax,RR0_9006-4
	movl	%eax,RR0_9007-4
	movl	%eax,RR0_9008-4
	movl	%eax,RR0_9009-4
	movl	%eax,RR0_9010-4
	movl	%eax,RR0_9011-4
	movl	%eax,RR0_9012-4
	movl	%eax,RR0_9013-4
	movl	%eax,RR0_9014-4
	movl	%eax,RR0_9015-4
	movl	%eax,RR0_9016-4
	movl	%eax,RR0_9017-4
	movl	%eax,RR0_9018-4
	movl	%eax,RR0_9019-4
	movl	%eax,RR0_9020-4
	movl	%eax,RR0_9021-4
	movl	%eax,RR0_9022-4
	movl	%eax,RR0_9023-4
	movl	%eax,RR0_9024-4
	movl	%eax,RR0_9025-4
	movl	%eax,RR0_9026-4
	movl	%eax,RR0_9027-4
	movl	%eax,RR0_9028-4
	movl	%eax,RR0_9029-4
	movl	%eax,RR0_9030-4
	movl	%eax,RR0_9031-4
	movl	%eax,RR0_9032-4
	movl	%eax,RR0_9033-4
	movl	%eax,RR0_9034-4
	movl	%eax,RR0_9035-4
	movl	%eax,RR0_9036-4
	movl	%eax,RR0_9037-4
	movl	%eax,RR0_9038-4
	movl	%eax,RR0_9039-4
	movl	%eax,RR0_9040-4
	movl	%eax,RR0_9041-4
	movl	%eax,RR0_9042-4
	movl	%eax,RR0_9043-4
	movl	%eax,RR0_9044-4
	movl	%eax,RR0_9045-4
	movl	%eax,RR0_9046-4
	movl	%eax,RR0_9047-4
	movl	%eax,RR0_9048-4
	movl	%eax,RR0_9049-4
	movl	%eax,RR0_9050-4
	movl	%eax,RR0_9051-4
	movl	%eax,RR0_9052-4
	movl	%eax,RR0_9053-4
	movl	%eax,RR0_9054-4
	movl	%eax,RR0_9055-4
	movl	%eax,RR0_9056-4
	movl	%eax,RR0_9057-4
	movl	%eax,RR0_9058-4
	movl	%eax,RR0_9059-4
	movl	%eax,RR0_9060-4
	movl	%eax,RR0_9061-4
	movl	%eax,RR0_9062-4
	movl	%eax,RR0_9063-4
	movl	%eax,RR0_9064-4
	movl	%eax,RR0_9065-4
	movl	%eax,RR0_9066-4
	movl	%eax,RR0_9067-4
	movl	%eax,RR0_9068-4
	movl	%eax,RR0_9069-4
	movl	%eax,RR0_9070-4
	movl	%eax,RR0_9071-4
	movl	%eax,RR0_9072-4
	movl	%eax,RR0_9073-4
	movl	%eax,RR0_9074-4
	movl	%eax,RR0_9075-4
	movl	%eax,RR0_9076-4
	movl	%eax,RR0_9077-4
	movl	%eax,RR0_9078-4
	movl	%eax,RR0_9079-4
	movl	%eax,RR0_9080-4
	movl	%eax,RR0_9081-4
	movl	%eax,RR0_9082-4
	movl	%eax,RR0_9083-4
	movl	%eax,RR0_9084-4
	movl	%eax,RR0_9085-4
	movl	%eax,RR0_9086-4
	movl	%eax,RR0_9087-4
	movl	%eax,RR0_9088-4
	movl	%eax,RR0_9089-4
	movl	%eax,RR0_9090-4
	movl	%eax,RR0_9091-4
	movl	%eax,RR0_9092-4
	movl	%eax,RR0_9093-4
	movl	%eax,RR0_9094-4
	movl	%eax,RR0_9095-4
	movl	%eax,RR0_9096-4
	movl	%eax,RR0_9097-4
	movl	%eax,RR0_9098-4
	movl	%eax,RR0_9099-4
	movl	%eax,RR0_9100-4
	movl	%eax,RR0_9101-4
	movl	%eax,RR0_9102-4
	movl	%eax,RR0_9103-4
	movl	%eax,RR0_9104-4
	movl	%eax,RR0_9105-4
	movl	%eax,RR0_9106-4
	movl	%eax,RR0_9107-4
	movl	%eax,RR0_9108-4
	movl	%eax,RR0_9109-4
	movl	%eax,RR0_9110-4
	movl	%eax,RR0_9111-4
	movl	%eax,RR0_9112-4
	movl	%eax,RR0_9113-4
	movl	%eax,RR0_9114-4
	movl	%eax,RR0_9115-4
	movl	%eax,RR0_9116-4
	movl	%eax,RR0_9117-4
	movl	%eax,RR0_9118-4
	movl	%eax,RR0_9119-4
	movl	%eax,RR0_9120-4
	movl	%eax,RR0_9121-4
	movl	%eax,RR0_9122-4
	movl	%eax,RR0_9123-4
	movl	%eax,RR0_9124-4
	movl	%eax,RR0_9125-4
	movl	%eax,RR0_9126-4
	movl	%eax,RR0_9127-4
	movl	%eax,RR0_9128-4
	movl	%eax,RR0_9129-4
	movl	%eax,RR0_9130-4
	movl	%eax,RR0_9131-4
	movl	%eax,RR0_9132-4
	movl	%eax,RR0_9133-4
	movl	%eax,RR0_9134-4
	movl	%eax,RR0_9135-4
	movl	%eax,RR0_9136-4
	movl	%eax,RR0_9137-4
	movl	%eax,RR0_9138-4
	movl	%eax,RR0_9139-4
	movl	%eax,RR0_9140-4
	movl	%eax,RR0_9141-4
	movl	%eax,RR0_9142-4
	movl	%eax,RR0_9143-4
	movl	%eax,RR0_9144-4
	movl	%eax,RR0_9145-4
	movl	%eax,RR0_9146-4
	movl	%eax,RR0_9147-4
	movl	%eax,RR0_9148-4
	movl	%eax,RR0_9149-4
	movl	%eax,RR0_9150-4
	movl	%eax,RR0_9151-4
	movl	%eax,RR0_9152-4
	movl	%eax,RR0_9153-4
	movl	%eax,RR0_9154-4
	movl	%eax,RR0_9155-4
	movl	%eax,RR0_9156-4
	movl	%eax,RR0_9157-4
	movl	%eax,RR0_9158-4
	movl	%eax,RR0_9159-4
	movl	%eax,RR0_9160-4
	movl	%eax,RR0_9161-4
	movl	%eax,RR0_9162-4
	movl	%eax,RR0_9163-4
	movl	%eax,RR0_9164-4
	movl	%eax,RR0_9165-4
	movl	%eax,RR0_9166-4
	movl	%eax,RR0_9167-4
	movl	%eax,RR0_9168-4
	movl	%eax,RR0_9169-4
	movl	%eax,RR0_9170-4
	movl	%eax,RR0_9171-4
	movl	%eax,RR0_9172-4
	movl	%eax,RR0_9173-4
	movl	%eax,RR0_9174-4
	movl	%eax,RR0_9175-4
	movl	%eax,RR0_9176-4
	movl	%eax,RR0_9177-4
	movl	%eax,RR0_9178-4
	movl	%eax,RR0_9179-4
	movl	%eax,RR0_9180-4
	movl	%eax,RR0_9181-4
	movl	%eax,RR0_9182-4
	movl	%eax,RR0_9183-4
	movl	%eax,RR0_9184-4
	movl	%eax,RR0_9185-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_9000-4
	movl	%eax,RR2_9001-4
	movl	%eax,RR2_9002-4
	movl	%eax,RR2_9003-4
	movl	%eax,RR2_9004-4
	movl	%eax,RR2_9005-4
	movl	%eax,RR2_9006-4
	movl	%eax,RR2_9007-4
	movl	%eax,RR2_9008-4
	movl	%eax,RR2_9009-4
	movl	%eax,RR2_9010-4
	movl	%eax,RR2_9011-4
	movl	%eax,RR2_9012-4
	movl	%eax,RR2_9013-4
	movl	%eax,RR2_9014-4
	movl	%eax,RR2_9015-4
	movl	%eax,RR2_9016-4
	movl	%eax,RR2_9017-4
	movl	%eax,RR2_9018-4
	movl	%eax,RR2_9019-4
	movl	%eax,RR2_9020-4
	movl	%eax,RR2_9021-4
	movl	%eax,RR2_9022-4
	movl	%eax,RR2_9023-4
	movl	%eax,RR2_9024-4
	movl	%eax,RR2_9025-4
	movl	%eax,RR2_9026-4
	movl	%eax,RR2_9027-4
	movl	%eax,RR2_9028-4
	movl	%eax,RR2_9029-4
	movl	%eax,RR2_9030-4
	movl	%eax,RR2_9031-4
	movl	%eax,RR2_9032-4
	movl	%eax,RR2_9033-4
	movl	%eax,RR2_9034-4
	movl	%eax,RR2_9035-4
	movl	%eax,RR2_9036-4
	movl	%eax,RR2_9037-4
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	incl	%eax
	popl	%eax
	ret
