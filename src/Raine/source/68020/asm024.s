

FUNC(op_2130)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4000:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_400
	movswl	%di,%edi
L_4_400:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_401
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_402
	movl	%ebp,%ebx
L_4_402:
	testl	$64,%esi
	je	L_4_403
	movl	%ebp,%edi
L_4_403:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_404
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_404:
	cmpl	$48,%edx
	jne	L_4_407
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_407:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_410
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_410:
	cmpl	$3,16-16(%esp)
	jne	L_4_413
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_413:
	andl	$4,%esi
	jne	L_4_416
	addl	%edi,%ebx
L_4_416:
	cmpl	$0,16-16(%esp)
	je	L_4_417
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_417:
	testl	%esi,%esi
	je	L_4_420
	addl	%edi,%ebx
L_4_420:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_421
	.align	2,0x90
L_4_401:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_421:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	movl	$GLOBL(regs),%ecx
	addl	$8,%edx
	movl	(%eax),%ebx
	sall	$2,%edx
	bswapl	%ebx
	movl	(%edx,%ecx),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%ecx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4000:
	ret

FUNC(op_213b)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4006:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_476
	movswl	%di,%edi
L_4_476:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_477
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_478
	movl	%ebp,%ebx
L_4_478:
	testl	$64,%esi
	je	L_4_479
	movl	%ebp,%edi
L_4_479:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_480
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_480:
	cmpl	$48,%edx
	jne	L_4_483
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_483:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_486
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_486:
	cmpl	$3,16-16(%esp)
	jne	L_4_489
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_489:
	andl	$4,%esi
	jne	L_4_492
	addl	%edi,%ebx
L_4_492:
	cmpl	$0,16-16(%esp)
	je	L_4_493
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_493:
	testl	%esi,%esi
	je	L_4_496
	addl	%edi,%ebx
L_4_496:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_497
	.align	2,0x90
L_4_477:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_497:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	movl	$GLOBL(regs),%ecx
	addl	$8,%edx
	movl	(%eax),%ebx
	sall	$2,%edx
	bswapl	%ebx
	movl	(%edx,%ecx),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%ecx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4001:
	ret

FUNC(op_2170)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4012:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_595
	movswl	%di,%edi
L_4_595:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_596
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_597
	movl	%ebp,%ebx
L_4_597:
	testl	$64,%esi
	je	L_4_598
	movl	%ebp,%edi
L_4_598:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_599
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_599:
	cmpl	$48,%edx
	jne	L_4_602
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_602:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_605
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_605:
	cmpl	$3,16-16(%esp)
	jne	L_4_608
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_608:
	andl	$4,%esi
	jne	L_4_611
	addl	%edi,%ebx
L_4_611:
	cmpl	$0,16-16(%esp)
	je	L_4_612
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_612:
	testl	%esi,%esi
	je	L_4_615
	addl	%edi,%ebx
L_4_615:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_616
	.align	2,0x90
L_4_596:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_616:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	28-16(%esp),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_4017:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	movl	16-16(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%eax
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4002:
	ret

FUNC(op_217b)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4019:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_678
	movswl	%di,%edi
L_4_678:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_679
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_680
	movl	%ebp,%ebx
L_4_680:
	testl	$64,%esi
	je	L_4_681
	movl	%ebp,%edi
L_4_681:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_682
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4020:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_682:
	cmpl	$48,%edx
	jne	L_4_685
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4021:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_685:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_688
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4022:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_688:
	cmpl	$3,16-16(%esp)
	jne	L_4_691
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4023:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_691:
	andl	$4,%esi
	jne	L_4_694
	addl	%edi,%ebx
L_4_694:
	cmpl	$0,16-16(%esp)
	je	L_4_695
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_695:
	testl	%esi,%esi
	je	L_4_698
	addl	%edi,%ebx
L_4_698:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_699
	.align	2,0x90
L_4_679:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_699:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	28-16(%esp),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_4024:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	movl	16-16(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%eax
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4003:
	ret

FUNC(op_2180)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	movl	(%ecx,%edx,4),%edx
	movl	GLOBL(regs)+88,%ebx
	movl	%edx,28-16(%esp)
	addl	$8,%eax
	movl	%ebx,%edx
	movl	%ebx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ebx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4026:
	rolw	$8,%si
	movl	(%ecx,%eax,4),%ebp
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%ebp,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_722
	movswl	%di,%edi
L_4_722:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_723
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_724
	movl	%ebp,16-16(%esp)
L_4_724:
	testl	$64,%esi
	je	L_4_725
	movl	%ebp,%edi
L_4_725:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_726
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4027:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_726:
	cmpl	$48,%edx
	jne	L_4_729
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4028:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_729:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_732
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4029:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_732:
	cmpl	$3,%ecx
	jne	L_4_735
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4030:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_735:
	andl	$4,%esi
	jne	L_4_738
	addl	%edi,16-16(%esp)
L_4_738:
	testl	%ecx,%ecx
	je	L_4_739
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_739:
	testl	%esi,%esi
	je	L_4_742
	addl	%edi,16-16(%esp)
L_4_742:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_743
	.align	2,0x90
L_4_723:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ecx
L_4_743:
	movl	28-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4031:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4004:
	ret

FUNC(op_2188)

	subl	$16,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$9,%edx
	andl	$7,%eax
	addl	$8,%eax
	andl	$7,%edx
	movl	(%ecx,%eax,4),%eax
	movl	GLOBL(regs)+88,%ebx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ebx,%eax
	movl	%ebx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4032:
	rolw	$8,%si
	movl	(%ecx,%edx,4),%edx
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_751
	movswl	%di,%edi
L_4_751:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_752
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_753
	movl	%ebp,16-16(%esp)
L_4_753:
	testl	$64,%esi
	je	L_4_754
	movl	%ebp,%edi
L_4_754:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_755
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4033:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_755:
	cmpl	$48,%edx
	jne	L_4_758
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4034:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_758:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_761
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4035:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_761:
	cmpl	$3,%ecx
	jne	L_4_764
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4036:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_764:
	andl	$4,%esi
	jne	L_4_767
	addl	%edi,16-16(%esp)
L_4_767:
	testl	%ecx,%ecx
	je	L_4_768
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_768:
	testl	%esi,%esi
	je	L_4_771
	addl	%edi,16-16(%esp)
L_4_771:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_772
	.align	2,0x90
L_4_752:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ecx
L_4_772:
	movl	28-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4005:
	ret

FUNC(op_2190)

	subl	$16,%esp
	movl	%eax,%edx
	andl	$7,%eax
	addl	$8,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	movw	(%ebx,%eax,4),%ax
	shrl	$9,%edx
	andl	$65535,%eax
	andl	$7,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4038:
	rolw	$8,%si
	movl	(%ebx,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_782
	movswl	%di,%edi
L_4_782:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_783
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_784
	movl	%ebp,%ebx
L_4_784:
	testl	$64,%esi
	je	L_4_785
	movl	%ebp,%edi
L_4_785:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_786
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4039:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_786:
	cmpl	$48,%edx
	jne	L_4_789
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4040:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_789:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_792
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4041:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_792:
	cmpl	$3,16-16(%esp)
	jne	L_4_795
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4042:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_795:
	andl	$4,%esi
	jne	L_4_798
	addl	%edi,%ebx
L_4_798:
	cmpl	$0,16-16(%esp)
	je	L_4_799
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_799:
	testl	%esi,%esi
	je	L_4_802
	addl	%edi,%ebx
L_4_802:
	addl	%ebp,%ebx
	jmp	L_4_803
	.align	2,0x90
L_4_783:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_4_803:
	movl	28-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4006:
	ret

FUNC(op_2198)

	subl	$16,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%edi
	movl	%eax,%esi
	shrl	$9,%esi
	movl	(%ecx,%edi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,(%ecx,%edi)
	movl	GLOBL(regs)+88,%ebx
	andl	$7,%esi
	movl	%ebx,%eax
	addl	$8,%esi
	addl	$2,%eax
	movl	%ebx,24-16(%esp)
	movl	%eax,GLOBL(regs)+88
	addl	$4,%ebx
	movl	(%edi,%esi,4),%edx
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4044:
	rolw	$8,%si
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_813
	movswl	%di,%edi
L_4_813:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_814
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_815
	movl	%ebp,16-16(%esp)
L_4_815:
	testl	$64,%esi
	je	L_4_816
	movl	%ebp,%edi
L_4_816:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_817
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4045:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_817:
	cmpl	$48,%edx
	jne	L_4_820
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4046:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_820:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_823
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4047:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_823:
	cmpl	$3,%ecx
	jne	L_4_826
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4048:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_826:
	andl	$4,%esi
	jne	L_4_829
	addl	%edi,16-16(%esp)
L_4_829:
	testl	%ecx,%ecx
	je	L_4_830
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_830:
	testl	%esi,%esi
	je	L_4_833
	addl	%edi,16-16(%esp)
L_4_833:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_834
	.align	2,0x90
L_4_814:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ecx
L_4_834:
	movl	28-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4007:
	ret

FUNC(op_21a0)

	subl	$16,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	movl	%eax,%esi
	addl	$-4,%ecx
	shrl	$9,%esi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%ecx,(%ebx,%edi)
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%esi
	movl	%ecx,%eax
	addl	$8,%esi
	addl	$2,%eax
	movl	%ecx,24-16(%esp)
	movl	%eax,GLOBL(regs)+88
	addl	$4,%ecx
	movl	(%edi,%esi,4),%edx
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4050:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_844
	movswl	%di,%edi
L_4_844:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_845
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_846
	movl	%ebp,%ebx
L_4_846:
	testl	$64,%esi
	je	L_4_847
	movl	%ebp,%edi
L_4_847:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_848
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4051:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_848:
	cmpl	$48,%edx
	jne	L_4_851
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4052:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_851:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_854
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4053:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_854:
	cmpl	$3,16-16(%esp)
	jne	L_4_857
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4054:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_857:
	andl	$4,%esi
	jne	L_4_860
	addl	%edi,%ebx
L_4_860:
	cmpl	$0,16-16(%esp)
	je	L_4_861
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_861:
	testl	%esi,%esi
	je	L_4_864
	addl	%edi,%ebx
L_4_864:
	addl	%ebp,%ebx
	jmp	L_4_865
	.align	2,0x90
L_4_845:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_4_865:
	movl	28-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4008:
	ret

FUNC(op_21a8)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$7,%ecx
	andl	$7,%edx
	movl	%ecx,16-16(%esp)
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_4000:
	rolw	$8,%ax
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	addl	$4,%eax
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4056:
	rolw	$8,%si
	movl	(%ebx,%ecx,4),%edx
	movl	28-16(%esp),%ecx
	movl	%esi,%eax
	addl	$6,%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_876
	movswl	%di,%edi
L_4_876:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_877
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_878
	movl	%ebp,%ebx
L_4_878:
	testl	$64,%esi
	je	L_4_879
	movl	%ebp,%edi
L_4_879:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_880
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4057:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_880:
	cmpl	$48,%edx
	jne	L_4_883
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4058:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_883:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_886
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4059:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_886:
	cmpl	$3,16-16(%esp)
	jne	L_4_889
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4060:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_889:
	andl	$4,%esi
	jne	L_4_892
	addl	%edi,%ebx
L_4_892:
	cmpl	$0,16-16(%esp)
	je	L_4_893
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_893:
	testl	%esi,%esi
	je	L_4_896
	addl	%edi,%ebx
L_4_896:
	addl	%ebp,%ebx
	jmp	L_4_897
	.align	2,0x90
L_4_877:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_4_897:
	movl	24-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4009:
	ret

FUNC(op_21b0)

	subl	$28,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,40-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,36-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4062:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,32-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_905
	movswl	%di,%edi
L_4_905:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_906
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_907
	movl	%ebp,%ebx
L_4_907:
	testl	$64,%esi
	je	L_4_908
	movl	%ebp,%edi
L_4_908:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_909
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4063:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_909:
	cmpl	$48,%edx
	jne	L_4_912
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4064:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_912:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_915
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4065:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_915:
	cmpl	$3,16-16(%esp)
	jne	L_4_918
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4066:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_918:
	andl	$4,%esi
	jne	L_4_921
	addl	%edi,%ebx
L_4_921:
	cmpl	$0,16-16(%esp)
	je	L_4_922
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_922:
	testl	%esi,%esi
	je	L_4_925
	addl	%edi,%ebx
L_4_925:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_926
	.align	2,0x90
L_4_906:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_926:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	40-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_4067:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$2,%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_932
	movswl	%di,%edi
L_4_932:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_933
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_934
	movl	%ebp,%ebx
L_4_934:
	testl	$64,%esi
	je	L_4_935
	movl	%ebp,%edi
L_4_935:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_936
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4068:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_936:
	cmpl	$48,%edx
	jne	L_4_939
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4069:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_939:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_942
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4070:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_942:
	cmpl	$3,16-16(%esp)
	jne	L_4_945
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4071:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_945:
	andl	$4,%esi
	jne	L_4_948
	addl	%edi,%ebx
L_4_948:
	cmpl	$0,16-16(%esp)
	je	L_4_949
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_949:
	testl	%esi,%esi
	je	L_4_952
	addl	%edi,%ebx
L_4_952:
	addl	%ebp,%ebx
	jmp	L_4_953
	.align	2,0x90
L_4_933:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_4_953:
	movl	28-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4072:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4010:
	ret

FUNC(op_21b8)

	subl	$16,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4001:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	andl	$7,%ecx
	movl	%ebx,%eax
	addl	$8,%ecx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4073:
	rolw	$8,%si
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_964
	movswl	%di,%edi
L_4_964:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_965
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_966
	movl	%ebp,16-16(%esp)
L_4_966:
	testl	$64,%esi
	je	L_4_967
	movl	%ebp,%edi
L_4_967:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_968
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4074:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_968:
	cmpl	$48,%edx
	jne	L_4_971
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4075:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_971:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_974
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4076:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_974:
	cmpl	$3,%ecx
	jne	L_4_977
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4077:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_977:
	andl	$4,%esi
	jne	L_4_980
	addl	%edi,16-16(%esp)
L_4_980:
	testl	%ecx,%ecx
	je	L_4_981
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_981:
	testl	%esi,%esi
	je	L_4_984
	addl	%edi,16-16(%esp)
L_4_984:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_985
	.align	2,0x90
L_4_965:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ecx
L_4_985:
	movl	24-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4011:
	ret

FUNC(op_21b9)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebx
	movl	%eax,%ecx
	movl	%ebx,28-16(%esp)
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_4002:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	andl	$7,%ecx
	movl	%ebx,%eax
	addl	$8,%ecx
	addl	$6,%eax
	addl	$8,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4079:
	rolw	$8,%si
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_996
	movswl	%di,%edi
L_4_996:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_997
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_998
	movl	%ebp,16-16(%esp)
L_4_998:
	testl	$64,%esi
	je	L_4_999
	movl	%ebp,%edi
L_4_999:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1000
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4080:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$10,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_1000:
	cmpl	$48,%edx
	jne	L_4_1003
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4081:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_1003:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_1006
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4082:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1006:
	cmpl	$3,%ecx
	jne	L_4_1009
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4083:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1009:
	andl	$4,%esi
	jne	L_4_1012
	addl	%edi,16-16(%esp)
L_4_1012:
	testl	%ecx,%ecx
	je	L_4_1013
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_1013:
	testl	%esi,%esi
	je	L_4_1016
	addl	%edi,16-16(%esp)
L_4_1016:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_1017
	.align	2,0x90
L_4_997:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ecx
L_4_1017:
	movl	24-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4012:
	ret

FUNC(op_21ba)

	subl	$16,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4003:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	andl	$7,%ecx
	movl	%ebx,%eax
	addl	$8,%ecx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4085:
	rolw	$8,%si
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1029
	movswl	%di,%edi
L_4_1029:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1030
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_4_1031
	movl	%ebp,16-16(%esp)
L_4_1031:
	testl	$64,%esi
	je	L_4_1032
	movl	%ebp,%edi
L_4_1032:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1033
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4086:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_4_1033:
	cmpl	$48,%edx
	jne	L_4_1036
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4087:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_4_1036:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_4_1039
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4088:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1039:
	cmpl	$3,%ecx
	jne	L_4_1042
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4089:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1042:
	andl	$4,%esi
	jne	L_4_1045
	addl	%edi,16-16(%esp)
L_4_1045:
	testl	%ecx,%ecx
	je	L_4_1046
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_4_1046:
	testl	%esi,%esi
	je	L_4_1049
	addl	%edi,16-16(%esp)
L_4_1049:
	movl	16-16(%esp),%ecx
	addl	%ebp,%ecx
	jmp	L_4_1050
	.align	2,0x90
L_4_1030:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ecx
L_4_1050:
	movl	24-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4013:
	ret

FUNC(op_21bb)

	subl	$28,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,36-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4091:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,32-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1059
	movswl	%di,%edi
L_4_1059:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1060
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1061
	movl	%ebp,%ebx
L_4_1061:
	testl	$64,%esi
	je	L_4_1062
	movl	%ebp,%edi
L_4_1062:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1063
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4092:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1063:
	cmpl	$48,%edx
	jne	L_4_1066
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4093:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1066:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1069
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4094:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1069:
	cmpl	$3,16-16(%esp)
	jne	L_4_1072
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4095:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1072:
	andl	$4,%esi
	jne	L_4_1075
	addl	%edi,%ebx
L_4_1075:
	cmpl	$0,16-16(%esp)
	je	L_4_1076
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1076:
	testl	%esi,%esi
	je	L_4_1079
	addl	%edi,%ebx
L_4_1079:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1080
	.align	2,0x90
L_4_1060:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1080:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	40-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_4096:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$2,%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1086
	movswl	%di,%edi
L_4_1086:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1087
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1088
	movl	%ebp,%ebx
L_4_1088:
	testl	$64,%esi
	je	L_4_1089
	movl	%ebp,%edi
L_4_1089:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1090
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4097:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1090:
	cmpl	$48,%edx
	jne	L_4_1093
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4098:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1093:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1096
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4099:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1096:
	cmpl	$3,16-16(%esp)
	jne	L_4_1099
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4100:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1099:
	andl	$4,%esi
	jne	L_4_1102
	addl	%edi,%ebx
L_4_1102:
	cmpl	$0,16-16(%esp)
	je	L_4_1103
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1103:
	testl	%esi,%esi
	je	L_4_1106
	addl	%edi,%ebx
L_4_1106:
	addl	%ebp,%ebx
	jmp	L_4_1107
	.align	2,0x90
L_4_1087:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_4_1107:
	movl	28-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4014:
	ret

FUNC(op_21bc)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_4004:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,28-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4102:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1116
	movswl	%di,%edi
L_4_1116:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1117
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1118
	movl	16-16(%esp),%ebx
L_4_1118:
	testl	$64,%esi
	je	L_4_1119
	movl	16-16(%esp),%edi
L_4_1119:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1120
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4103:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_4_1120:
	cmpl	$48,%edx
	jne	L_4_1123
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4104:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1123:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_4_1126
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4105:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_4_1126:
	cmpl	$3,%ebp
	jne	L_4_1129
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4106:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_4_1129:
	andl	$4,%esi
	jne	L_4_1132
	addl	%edi,%ebx
L_4_1132:
	testl	%ebp,%ebp
	je	L_4_1133
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1133:
	testl	%esi,%esi
	je	L_4_1136
	addl	%edi,%ebx
L_4_1136:
	addl	16-16(%esp),%ebx
	jmp	L_4_1137
	.align	2,0x90
L_4_1117:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	24-16(%esp),%eax
	leal	(%edi,%eax),%ebx
L_4_1137:
	movl	28-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4015:
	ret

FUNC(op_21f0)

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
RR0_4108:
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
	jne	L_4_1223
	movswl	%di,%edi
L_4_1223:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1224
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1225
	movl	%ebp,%ebx
L_4_1225:
	testl	$64,%esi
	je	L_4_1226
	movl	%ebp,%edi
L_4_1226:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1227
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4109:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1227:
	cmpl	$48,%edx
	jne	L_4_1230
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4110:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1230:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1233
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4111:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1233:
	cmpl	$3,16-16(%esp)
	jne	L_4_1236
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4112:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1236:
	andl	$4,%esi
	jne	L_4_1239
	addl	%edi,%ebx
L_4_1239:
	cmpl	$0,16-16(%esp)
	je	L_4_1240
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1240:
	testl	%esi,%esi
	je	L_4_1243
	addl	%edi,%ebx
L_4_1243:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1244
	.align	2,0x90
L_4_1224:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_4_1244:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_4113:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4016:
	ret

FUNC(op_21fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4115:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1306
	movswl	%di,%edi
L_4_1306:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1307
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1308
	movl	%ebp,%ebx
L_4_1308:
	testl	$64,%esi
	je	L_4_1309
	movl	%ebp,%edi
L_4_1309:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1310
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4116:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1310:
	cmpl	$48,%edx
	jne	L_4_1313
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4117:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1313:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1316
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4118:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1316:
	cmpl	$3,16-16(%esp)
	jne	L_4_1319
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4119:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1319:
	andl	$4,%esi
	jne	L_4_1322
	addl	%edi,%ebx
L_4_1322:
	cmpl	$0,16-16(%esp)
	je	L_4_1323
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1323:
	testl	%esi,%esi
	je	L_4_1326
	addl	%edi,%ebx
L_4_1326:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1327
	.align	2,0x90
L_4_1307:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1327:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_4120:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4017:
	ret

FUNC(op_23f0)

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
RR0_4122:
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
	jne	L_4_1428
	movswl	%di,%edi
L_4_1428:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1429
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1430
	movl	%ebp,%ebx
L_4_1430:
	testl	$64,%esi
	je	L_4_1431
	movl	%ebp,%edi
L_4_1431:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1432
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4123:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1432:
	cmpl	$48,%edx
	jne	L_4_1435
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4124:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1435:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1438
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4125:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1438:
	cmpl	$3,16-16(%esp)
	jne	L_4_1441
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4126:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1441:
	andl	$4,%esi
	jne	L_4_1444
	addl	%edi,%ebx
L_4_1444:
	cmpl	$0,16-16(%esp)
	je	L_4_1445
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1445:
	testl	%esi,%esi
	je	L_4_1448
	addl	%edi,%ebx
L_4_1448:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1449
	.align	2,0x90
L_4_1429:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_4_1449:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4127:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4018:
	ret

FUNC(op_23fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4129:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1511
	movswl	%di,%edi
L_4_1511:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1512
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1513
	movl	%ebp,%ebx
L_4_1513:
	testl	$64,%esi
	je	L_4_1514
	movl	%ebp,%edi
L_4_1514:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1515
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4130:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1515:
	cmpl	$48,%edx
	jne	L_4_1518
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4131:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1518:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1521
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4132:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1521:
	cmpl	$3,16-16(%esp)
	jne	L_4_1524
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4133:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1524:
	andl	$4,%esi
	jne	L_4_1527
	addl	%edi,%ebx
L_4_1527:
	cmpl	$0,16-16(%esp)
	je	L_4_1528
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1528:
	testl	%esi,%esi
	je	L_4_1531
	addl	%edi,%ebx
L_4_1531:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1532
	.align	2,0x90
L_4_1512:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1532:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4134:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4019:
	ret

FUNC(op_3030)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4136:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1597
	movswl	%di,%edi
L_4_1597:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1598
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1599
	movl	%ebp,%ebx
L_4_1599:
	testl	$64,%esi
	je	L_4_1600
	movl	%ebp,%edi
L_4_1600:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1601
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4137:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1601:
	cmpl	$48,%edx
	jne	L_4_1604
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4138:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1604:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1607
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4139:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1607:
	cmpl	$3,16-16(%esp)
	jne	L_4_1610
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4140:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1610:
	andl	$4,%esi
	jne	L_4_1613
	addl	%edi,%ebx
L_4_1613:
	cmpl	$0,16-16(%esp)
	je	L_4_1614
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1614:
	testl	%esi,%esi
	je	L_4_1617
	addl	%edi,%ebx
L_4_1617:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1618
	.align	2,0x90
L_4_1598:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1618:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movw	%ax,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4020:
	ret

FUNC(op_303b)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4142:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1659
	movswl	%di,%edi
L_4_1659:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1660
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1661
	movl	%ebp,%ebx
L_4_1661:
	testl	$64,%esi
	je	L_4_1662
	movl	%ebp,%edi
L_4_1662:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1663
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4143:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1663:
	cmpl	$48,%edx
	jne	L_4_1666
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4144:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1666:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1669
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4145:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1669:
	cmpl	$3,16-16(%esp)
	jne	L_4_1672
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4146:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1672:
	andl	$4,%esi
	jne	L_4_1675
	addl	%edi,%ebx
L_4_1675:
	cmpl	$0,16-16(%esp)
	je	L_4_1676
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1676:
	testl	%esi,%esi
	je	L_4_1679
	addl	%edi,%ebx
L_4_1679:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1680
	.align	2,0x90
L_4_1660:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1680:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movw	%ax,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4021:
	ret

FUNC(op_3070)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4148:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1736
	movswl	%di,%edi
L_4_1736:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1737
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1738
	movl	%ebp,%ebx
L_4_1738:
	testl	$64,%esi
	je	L_4_1739
	movl	%ebp,%edi
L_4_1739:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1740
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4149:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1740:
	cmpl	$48,%edx
	jne	L_4_1743
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4150:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1743:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1746
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4151:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1746:
	cmpl	$3,16-16(%esp)
	jne	L_4_1749
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4152:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1749:
	andl	$4,%esi
	jne	L_4_1752
	addl	%edi,%ebx
L_4_1752:
	cmpl	$0,16-16(%esp)
	je	L_4_1753
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1753:
	testl	%esi,%esi
	je	L_4_1756
	addl	%edi,%ebx
L_4_1756:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1757
	.align	2,0x90
L_4_1737:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1757:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4022:
	ret

FUNC(op_307b)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4154:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1798
	movswl	%di,%edi
L_4_1798:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1799
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1800
	movl	%ebp,%ebx
L_4_1800:
	testl	$64,%esi
	je	L_4_1801
	movl	%ebp,%edi
L_4_1801:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1802
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4155:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1802:
	cmpl	$48,%edx
	jne	L_4_1805
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4156:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1805:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1808
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4157:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1808:
	cmpl	$3,16-16(%esp)
	jne	L_4_1811
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4158:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1811:
	andl	$4,%esi
	jne	L_4_1814
	addl	%edi,%ebx
L_4_1814:
	cmpl	$0,16-16(%esp)
	je	L_4_1815
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1815:
	testl	%esi,%esi
	je	L_4_1818
	addl	%edi,%ebx
L_4_1818:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1819
	.align	2,0x90
L_4_1799:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1819:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4023:
	ret

FUNC(op_30b0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4160:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1899
	movswl	%di,%edi
L_4_1899:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1900
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1901
	movl	%ebp,%ebx
L_4_1901:
	testl	$64,%esi
	je	L_4_1902
	movl	%ebp,%edi
L_4_1902:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1903
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4161:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1903:
	cmpl	$48,%edx
	jne	L_4_1906
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4162:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1906:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1909
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4163:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1909:
	cmpl	$3,16-16(%esp)
	jne	L_4_1912
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4164:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1912:
	andl	$4,%esi
	jne	L_4_1915
	addl	%edi,%ebx
L_4_1915:
	cmpl	$0,16-16(%esp)
	je	L_4_1916
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1916:
	testl	%esi,%esi
	je	L_4_1919
	addl	%edi,%ebx
L_4_1919:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1920
	.align	2,0x90
L_4_1900:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1920:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,16-16(%esp)
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	16-16(%esp),%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4024:
	ret

FUNC(op_30bb)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4166:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_1975
	movswl	%di,%edi
L_4_1975:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_1976
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_1977
	movl	%ebp,%ebx
L_4_1977:
	testl	$64,%esi
	je	L_4_1978
	movl	%ebp,%edi
L_4_1978:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_1979
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4167:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_1979:
	cmpl	$48,%edx
	jne	L_4_1982
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4168:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_1982:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_1985
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4169:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1985:
	cmpl	$3,16-16(%esp)
	jne	L_4_1988
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4170:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_1988:
	andl	$4,%esi
	jne	L_4_1991
	addl	%edi,%ebx
L_4_1991:
	cmpl	$0,16-16(%esp)
	je	L_4_1992
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_1992:
	testl	%esi,%esi
	je	L_4_1995
	addl	%edi,%ebx
L_4_1995:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_1996
	.align	2,0x90
L_4_1976:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_1996:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,16-16(%esp)
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	16-16(%esp),%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4025:
	ret

FUNC(op_30f0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4172:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_2082
	movswl	%di,%edi
L_4_2082:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_2083
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_2084
	movl	%ebp,%ebx
L_4_2084:
	testl	$64,%esi
	je	L_4_2085
	movl	%ebp,%edi
L_4_2085:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_2086
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4173:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_2086:
	cmpl	$48,%edx
	jne	L_4_2089
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4174:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_2089:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_2092
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4175:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2092:
	cmpl	$3,16-16(%esp)
	jne	L_4_2095
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4176:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2095:
	andl	$4,%esi
	jne	L_4_2098
	addl	%edi,%ebx
L_4_2098:
	cmpl	$0,16-16(%esp)
	je	L_4_2099
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_2099:
	testl	%esi,%esi
	je	L_4_2102
	addl	%edi,%ebx
L_4_2102:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_2103
	.align	2,0x90
L_4_2083:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_2103:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	addl	$8,%edx
	movl	%ecx,%eax
	sall	$2,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)(%edx),%eax
	leal	2(%eax),%ecx
	movl	%ecx,GLOBL(regs)(%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4026:
	ret

FUNC(op_30fb)

	subl	$16,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_4178:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_2158
	movswl	%di,%edi
L_4_2158:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_2159
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_2160
	movl	%ebp,%ebx
L_4_2160:
	testl	$64,%esi
	je	L_4_2161
	movl	%ebp,%edi
L_4_2161:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_2162
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4179:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_2162:
	cmpl	$48,%edx
	jne	L_4_2165
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4180:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_2165:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_2168
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4181:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2168:
	cmpl	$3,16-16(%esp)
	jne	L_4_2171
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4182:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2171:
	andl	$4,%esi
	jne	L_4_2174
	addl	%edi,%ebx
L_4_2174:
	cmpl	$0,16-16(%esp)
	je	L_4_2175
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_2175:
	testl	%esi,%esi
	je	L_4_2178
	addl	%edi,%ebx
L_4_2178:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_2179
	.align	2,0x90
L_4_2159:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_2179:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	addl	$8,%edx
	movl	%ecx,%eax
	sall	$2,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)(%edx),%eax
	leal	2(%eax),%ecx
	movl	%ecx,GLOBL(regs)(%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4027:
	ret

FUNC(op_3130)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_4184:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_4_2265
	movswl	%di,%edi
L_4_2265:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_4_2266
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_4_2267
	movl	%ebp,%ebx
L_4_2267:
	testl	$64,%esi
	je	L_4_2268
	movl	%ebp,%edi
L_4_2268:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_4_2269
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_4185:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_4_2269:
	cmpl	$48,%edx
	jne	L_4_2272
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4186:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_4_2272:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_4_2275
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_4187:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2275:
	cmpl	$3,16-16(%esp)
	jne	L_4_2278
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_4188:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_4_2278:
	andl	$4,%esi
	jne	L_4_2281
	addl	%edi,%ebx
L_4_2281:
	cmpl	$0,16-16(%esp)
	je	L_4_2282
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_4_2282:
	testl	%esi,%esi
	je	L_4_2285
	addl	%edi,%ebx
L_4_2285:
	leal	(%ebp,%ebx),%eax
	jmp	L_4_2286
	.align	2,0x90
L_4_2266:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_4_2286:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	addl	$8,%edx
	movl	%ecx,%eax
	sall	$2,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)(%edx),%eax
	addl	$-2,%eax
	movl	%eax,GLOBL(regs)(%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4028:
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


FUNC(op_2120)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	%eax,%ecx
	movl	(%esi,%edi),%ebx
	shrl	$9,%ecx
	addl	$-4,%ebx
	andl	$7,%ecx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	sall	$2,%ecx
	movl	(%eax),%ebp
	movl	%ebx,(%esi,%edi)
	bswapl	%ebp
	movl	(%ecx,%edi),%eax
	addl	$-4,%eax
	movl	%eax,(%ecx,%edi)
	testl	%ebp,%ebp
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebp
	movl	%ebp,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4029:
	ret

FUNC(op_2128)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%edx
	shrl	$9,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4005:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	sall	$2,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	movl	(%ecx,%ebx),%eax
	addl	$-4,%eax
	movl	%eax,(%ecx,%ebx)
	testl	%esi,%esi
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%esi
	movl	%esi,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4030:
	ret

FUNC(op_2138)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4006:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	andl	$7,%ecx
	movl	%eax,%edx
	addl	$8,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	(%ecx,%edx),%eax
	addl	$-4,%eax
	movl	%eax,(%ecx,%edx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4031:
	ret

FUNC(op_2139)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_4007:
	bswapl	%eax
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	addl	$8,%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	(%ecx,%edx),%eax
	addl	$-4,%eax
	movl	%eax,(%ecx,%edx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4032:
	ret

FUNC(op_213a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4008:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	andl	$7,%ecx
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	addl	$8,%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	(%ecx,%edx),%eax
	addl	$-4,%eax
	movl	%eax,(%ecx,%edx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4033:
	ret

FUNC(op_213c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_4009:
	sall	$2,%edx
	bswapl	%ebx
	movl	(%edx,%ecx),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%ecx)
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4034:
	ret

FUNC(op_2140)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4010:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4035:
	ret

FUNC(op_2148)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%eax
	shrl	$9,%edx
	addl	$8,%eax
	andl	$7,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4011:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4036:
	ret

FUNC(op_2150)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	shrl	$9,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	andl	$7,%edx
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4012:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ebx,%edx,4),%eax
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4037:
	ret

FUNC(op_2158)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	%eax,%esi
	sall	$2,%ecx
	shrl	$9,%esi
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	GLOBL(regs)+2(%ecx),%bl
	andl	$65535,%eax
	andl	$7,%esi
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	movl	%edx,GLOBL(regs)(%ecx)
	bswapl	%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4013:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%esi
	cwtl
	addl	GLOBL(regs)(,%esi,4),%eax
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4038:
	ret

FUNC(op_2160)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	movl	%eax,%esi
	addl	$-4,%ecx
	shrl	$9,%esi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$7,%esi
	movl	(%eax),%ebp
	movl	%ecx,(%ebx,%edi)
	bswapl	%ebp
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_4014:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%esi
	cwtl
	addl	(%edi,%esi,4),%eax
	testl	%ebp,%ebp
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebp
	movl	%ebp,(%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4039:
	ret

FUNC(op_2168)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%edx
	shrl	$9,%ecx
	movl	$GLOBL(regs),%edi
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_4015:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%ebx
	bswapl	%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%esi),%ax
RR4_4000:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%ecx,4),%eax
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4040:
	ret

FUNC(op_2178)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4016:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_4001:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
	testl	%esi,%esi
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%esi
	movl	%esi,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4041:
	ret

FUNC(op_2179)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_4017:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	xorl	%eax,%eax
	movw	0x2164334A+6(%ebx),%ax
RR6_4000:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
	testl	%esi,%esi
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%esi
	movl	%esi,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4042:
	ret

FUNC(op_217a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%ecx
	shrl	$9,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_4018:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ebx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ebx
	movl	(%eax),%esi
	bswapl	%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_4002:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ebx,4),%eax
	testl	%esi,%esi
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%esi
	movl	%esi,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4043:
	ret

FUNC(op_217c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+6(%eax),%bx
RR6_4001:
	rolw	$8,%bx
	andl	$7,%edx
	movl	0x2164334A+2(%eax),%ecx
RR2_4019:
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	bswapl	%ecx
	addl	GLOBL(regs)(,%edx,4),%eax
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4044:
	ret

FUNC(op_21c0)

	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4020:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4045:
	ret

FUNC(op_21c8)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4021:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4207:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4046:
	ret

FUNC(op_21d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4022:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4208:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4047:
	ret

FUNC(op_21d8)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	movl	%edx,(%ecx,%esi)
	bswapl	%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4023:
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4209:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4048:
	ret

FUNC(op_21e0)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%ebx
	addl	$-4,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edi
	movl	%ebx,GLOBL(regs)(%ecx)
	bswapl	%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4024:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	testl	%edi,%edi
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%edi
	movl	%edi,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4210:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4049:
	ret

FUNC(op_21e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4025:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_4003:
	rolw	$8,%ax
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4211:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4050:
	ret

FUNC(op_21f8)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_4026:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_4004:
	rolw	$8,%ax
	cwtl
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4212:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4051:
	ret

FUNC(op_21f9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%eax
RR2_4027:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
	xorl	%eax,%eax
	movw	0x2164334A+6(%ecx),%ax
RR6_4002:
	rolw	$8,%ax
	cwtl
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4213:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4052:
	ret

FUNC(op_21fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_4028:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_4005:
	rolw	$8,%ax
	cwtl
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4214:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4053:
	ret

FUNC(op_21fc)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+6(%eax),%bx
RR6_4003:
	rolw	$8,%bx
	movl	0x2164334A+2(%eax),%ecx
RR2_4029:
	movl	%ebx,%eax
	bswapl	%ecx
	cwtl
	testl	%ecx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4215:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4054:
	ret

FUNC(op_23c0)

	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_4030:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4216:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4055:
	ret

FUNC(op_23c8)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_4031:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4217:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4056:
	ret

FUNC(op_23d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_4032:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4218:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4057:
	ret

FUNC(op_23d8)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	movl	%edx,(%ecx,%esi)
	bswapl	%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_4033:
	bswapl	%edx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ebx
	movl	%ebx,(%edx)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4219:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4058:
	ret

FUNC(op_23e0)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	pushl	%ebx
	sall	$2,%ecx
	movl	(%ecx,%esi),%ebx
	addl	$-4,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edi
	movl	%ebx,(%ecx,%esi)
	bswapl	%edi
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_4034:
	bswapl	%edx
	testl	%edi,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%edi
	movl	%edi,(%edx)
	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4220:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4059:
	ret

FUNC(op_23e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4035:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	0x2164334A+4(%ebx),%edx
RR4_4006:
	bswapl	%edx
	movl	(%eax),%ecx
	bswapl	%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4221:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4060:
	ret

FUNC(op_23f8)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_4036:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	0x2164334A+4(%ebx),%edx
RR4_4007:
	bswapl	%edx
	movl	(%eax),%ecx
	bswapl	%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4222:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4061:
	ret

FUNC(op_23f9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%eax
RR2_4037:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	0x2164334A+6(%ecx),%edx
RR6_4004:
	bswapl	%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ebx
	movl	%ebx,(%edx)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4223:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4062:
	ret

FUNC(op_23fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_4038:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	0x2164334A+4(%ecx),%edx
RR4_4008:
	bswapl	%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ebx
	movl	%ebx,(%edx)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4224:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4063:
	ret

FUNC(op_23fc)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_4039:
	bswapl	%ecx
	movl	0x2164334A+6(%eax),%edx
RR6_4005:
	bswapl	%edx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4225:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4064:
	ret

FUNC(op_3000)

	movl	%eax,%ecx
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$9,%edx
	movl	$GLOBL(regs),%eax
	andl	$7,%edx
	movw	(%eax,%ecx,4),%cx
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%cx,(%eax,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4226:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4065:
	ret

FUNC(op_3008)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	$GLOBL(regs),%eax
	addl	$8,%edx
	andl	$7,%ecx
	movw	(%eax,%edx,4),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%eax,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4227:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4066:
	ret

FUNC(op_3010)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ebx
	andl	$7,%eax
	shrl	$9,%ebx
	addl	$8,%eax
	movl	$GLOBL(regs),%edx
	xorl	%ecx,%ecx
	movb	2(%edx,%eax,4),%cl
	movw	(%edx,%eax,4),%ax
	andl	$65535,%eax
	andl	$7,%ebx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	testw	%ax,%ax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movw	%ax,(%edx,%ebx,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4228:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4067:
	ret

FUNC(op_3018)

	subl	$8,%esp
	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	movl	%eax,%edi
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	shrl	$9,%edi
	movl	(%ecx,%ebx),%eax
	movb	2(%ecx,%ebx),%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%ebx),%edx
	addl	$2,%edx
	andl	$7,%edi
	movl	%edx,(%ecx,%ebx)
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%ebx,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4229:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4068:
	ret

FUNC(op_3020)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%eax,%edi
	addl	$-2,%ecx
	shrl	$9,%edi
	movl	%ecx,12-12(%esp)
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	12-12(%esp),%ecx
	andl	$7,%edi
	movl	%ecx,(%ebx,%esi)
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4230:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4069:
	ret

FUNC(op_3028)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4040:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ebx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%ecx,%ebx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4231:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4070:
	ret

FUNC(op_3038)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4041:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4232:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4071:
	ret

FUNC(op_3039)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_4042:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4233:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4072:
	ret

FUNC(op_303a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4043:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4234:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4073:
	ret

FUNC(op_303c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4044:
	rolw	$8,%bx
	movl	%ebx,%eax
	andl	$7,%edx
	testw	%ax,%ax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movw	%ax,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4235:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4074:
	ret

FUNC(op_3040)

	movl	%eax,%ecx
	shrl	$9,%eax
	movl	$GLOBL(regs),%edx
	andl	$7,%ecx
	andl	$7,%eax
	movswl	(%edx,%ecx,4),%ecx
	addl	$8,%eax
	movl	%ecx,(%edx,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4236:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4075:
	ret

FUNC(op_3048)

	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	addl	$8,%edx
	andl	$7,%eax
	movswl	(%ecx,%edx,4),%edx
	addl	$8,%eax
	movl	%edx,(%ecx,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4237:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4076:
	ret

FUNC(op_3050)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	shrl	$9,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebx,%edx,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4238:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4077:
	ret

FUNC(op_3058)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	$GLOBL(regs),%edi
	movl	%eax,%esi
	sall	$2,%ecx
	shrl	$9,%esi
	movl	(%ecx,%edi),%edx
	xorl	%ebx,%ebx
	movb	2(%ecx,%edi),%bl
	movl	%edx,%eax
	andl	$7,%esi
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%edi)
	cwtl
	addl	$8,%esi
	movl	%eax,(%edi,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4239:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4078:
	ret

FUNC(op_3060)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	movl	%eax,%esi
	addl	$-2,%ecx
	shrl	$9,%esi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	%ecx,(%ebx,%edi)
	cwtl
	addl	$8,%esi
	movl	%eax,(%edi,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4240:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4079:
	ret

FUNC(op_3068)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4045:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$7,%ecx
	cwtl
	addl	$8,%ecx
	movl	%eax,(%ebx,%ecx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4241:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4080:
	ret

FUNC(op_3078)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_4046:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	andl	$7,%ecx
	cwtl
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4242:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4081:
	ret

FUNC(op_3079)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_4047:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	andl	$7,%ecx
	cwtl
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4243:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4082:
	ret

FUNC(op_307a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4048:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	andl	$7,%ecx
	cwtl
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4244:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4083:
	ret

FUNC(op_307c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_4049:
	rolw	$8,%cx
	movl	%ecx,%eax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	movl	%eax,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4245:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4084:
	ret

FUNC(op_3080)

	movl	%eax,%ecx
	shrl	$9,%eax
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	andl	$7,%ecx
	addl	$8,%eax
	movw	(%edx,%ecx,4),%cx
	movl	(%edx,%eax,4),%edx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4246:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4085:
	ret

FUNC(op_3088)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movw	(%ecx,%edx,4),%bx
	movl	(%ecx,%eax,4),%edx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4247:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4086:
	ret

FUNC(op_3090)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	shrl	$9,%edx
	movw	(%ebx,%eax,4),%ax
	andl	$7,%edx
	andl	$65535,%eax
	addl	$8,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	(%ebx,%edx,4),%edx
	movl	%eax,%ecx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4248:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4087:
	ret

FUNC(op_3098)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	movl	%eax,%esi
	addl	$8,%ecx
	shrl	$9,%esi
	sall	$2,%ecx
	xorl	%ebx,%ebx
	andl	$7,%esi
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%bl
	movl	%edx,%eax
	addl	$2,%edx
	andl	$65535,%eax
	addl	$8,%esi
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%eax,%ebx
	movl	GLOBL(regs)(,%esi,4),%edx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4249:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4088:
	ret

FUNC(op_30a0)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	sall	$2,%ebx
	movl	%eax,%esi
	movl	GLOBL(regs)(%ebx),%ecx
	shrl	$9,%esi
	addl	$-2,%ecx
	andl	$7,%esi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%ebx)
	movl	%eax,%ebp
	movl	GLOBL(regs)(,%esi,4),%edx
	testw	%bp,%bp
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bp,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4250:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4089:
	ret

FUNC(op_30a8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%edx
	shrl	$9,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4050:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%esi
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	(%esi,%ecx,4),%edx
	movl	%eax,%ebx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4251:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4090:
	ret

FUNC(op_30b8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4051:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%eax,%ebx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4252:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4091:
	ret

FUNC(op_30b9)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_4052:
	bswapl	%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%eax,%ebx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4253:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4092:
	ret

FUNC(op_30ba)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4053:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	GLOBL(regs)(,%ecx,4),%edx
	movl	%eax,%ebx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4254:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4093:
	ret

FUNC(op_30bc)

	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%edx),%bx
RR2_4054:
	rolw	$8,%bx
	movl	%ebx,%edx
	addl	$8,%eax
	movl	%edx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4255:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4094:
	ret

FUNC(op_30c0)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	andl	$7,%edx
	sall	$2,%eax
	movw	(%ecx,%edx,4),%bx
	movl	(%eax,%ecx),%edx
	leal	2(%edx),%esi
	movl	%esi,(%eax,%ecx)
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4256:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4095:
	ret

FUNC(op_30c8)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%eax
	andl	$7,%edx
	addl	$8,%eax
	addl	$8,%edx
	sall	$2,%eax
	movw	(%ecx,%edx,4),%bx
	movl	(%eax,%ecx),%edx
	leal	2(%edx),%esi
	movl	%esi,(%eax,%ecx)
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4257:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4096:
	ret

FUNC(op_30d0)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	shrl	$9,%edx
	movw	(%ebx,%eax,4),%ax
	andl	$7,%edx
	andl	$65535,%eax
	addl	$8,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	sall	$2,%edx
	movl	%eax,%ecx
	movl	(%edx,%ebx),%eax
	leal	2(%eax),%esi
	movl	%esi,(%edx,%ebx)
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4258:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4097:
	ret

FUNC(op_30d8)

	subl	$12,%esp
	movl	%eax,%ebx
	movl	%eax,%edx
	andl	$7,%ebx
	xorl	%ecx,%ecx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	shrl	$9,%edx
	movl	(%ebx,%edi),%eax
	movb	2(%ebx,%edi),%cl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,22-12(%esp)
	andl	$7,%edx
	movl	(%ebx,%edi),%ecx
	addl	$8,%edx
	addl	$2,%ecx
	sall	$2,%edx
	movl	%ecx,(%ebx,%edi)
	movl	(%edx,%edi),%eax
	leal	2(%eax),%ecx
	movl	%ecx,(%edx,%edi)
	movw	22-12(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	22-12(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4259:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4098:
	ret

FUNC(op_30e0)

	subl	$4,%esp
	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	%eax,%ecx
	movl	(%esi,%edi),%ebx
	shrl	$9,%ecx
	addl	$-2,%ebx
	andl	$7,%ecx
	movl	%ebx,16-16(%esp)
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	16-16(%esp),%ebx
	sall	$2,%ecx
	movl	%ebx,(%esi,%edi)
	movl	%eax,%ebp
	movl	(%ecx,%edi),%eax
	leal	2(%eax),%ebx
	movl	%ebx,(%ecx,%edi)
	testw	%bp,%bp
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bp,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4260:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4099:
	ret

FUNC(op_30e8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%edx
	shrl	$9,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4055:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	sall	$2,%ecx
	movl	%eax,%esi
	movl	(%ecx,%ebx),%eax
	leal	2(%eax),%edi
	movl	%edi,(%ecx,%ebx)
	testw	%si,%si
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%si,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4261:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4100:
	ret

FUNC(op_30f8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4056:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	andl	$7,%ecx
	movl	%eax,%edx
	addl	$8,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	leal	2(%eax),%esi
	movl	%esi,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4262:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4101:
	ret

FUNC(op_30f9)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_4057:
	bswapl	%eax
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	addl	$8,%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	leal	2(%eax),%esi
	movl	%esi,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4263:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4102:
	ret

FUNC(op_30fa)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4058:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	andl	$7,%ecx
	movl	%eax,%edx
	addl	$8,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	leal	2(%eax),%esi
	movl	%esi,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4264:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4103:
	ret

FUNC(op_30fc)

	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%esi,%esi
	movw	0x2164334A+2(%edx),%si
RR2_4059:
	rolw	$8,%si
	addl	$8,%eax
	movl	%esi,%edx
	sall	$2,%eax
	movl	%edx,%ebx
	movl	(%eax,%ecx),%edx
	leal	2(%edx),%esi
	movl	%esi,(%eax,%ecx)
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4265:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4104:
	ret

FUNC(op_3100)

	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	andl	$7,%edx
	sall	$2,%eax
	movw	(%ecx,%edx,4),%bx
	movl	(%eax,%ecx),%edx
	addl	$-2,%edx
	movl	%edx,(%eax,%ecx)
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4266:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4105:
	ret

FUNC(op_3108)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	andl	$7,%edx
	addl	$8,%eax
	addl	$8,%edx
	sall	$2,%eax
	movw	(%ecx,%edx,4),%bx
	movl	(%eax,%ecx),%edx
	addl	$-2,%edx
	movl	%edx,(%eax,%ecx)
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%bx,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4267:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4106:
	ret

FUNC(op_3110)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	shrl	$9,%edx
	movw	(%ebx,%eax,4),%ax
	andl	$7,%edx
	andl	$65535,%eax
	addl	$8,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	sall	$2,%edx
	movl	%eax,%ecx
	movl	(%edx,%ebx),%eax
	addl	$-2,%eax
	movl	%eax,(%edx,%ebx)
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4268:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4107:
	ret

FUNC(op_3118)

	subl	$12,%esp
	movl	%eax,%ebx
	movl	%eax,%edx
	andl	$7,%ebx
	xorl	%ecx,%ecx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	shrl	$9,%edx
	movl	(%ebx,%edi),%eax
	movb	2(%ebx,%edi),%cl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,22-12(%esp)
	andl	$7,%edx
	movl	(%ebx,%edi),%ecx
	addl	$8,%edx
	addl	$2,%ecx
	sall	$2,%edx
	movl	%ecx,(%ebx,%edi)
	movl	(%edx,%edi),%eax
	addl	$-2,%eax
	movl	%eax,(%edx,%edi)
	movw	22-12(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	22-12(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4269:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4108:
	ret

FUNC(op_3120)

	subl	$4,%esp
	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	%eax,%ecx
	movl	(%esi,%edi),%ebx
	shrl	$9,%ecx
	addl	$-2,%ebx
	andl	$7,%ecx
	movl	%ebx,16-16(%esp)
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	16-16(%esp),%ebx
	sall	$2,%ecx
	movl	%ebx,(%esi,%edi)
	movl	%eax,%ebp
	movl	(%ecx,%edi),%eax
	addl	$-2,%eax
	movl	%eax,(%ecx,%edi)
	testw	%bp,%bp
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bp,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_4109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4270:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4109:
	ret

FUNC(op_3128)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%edx
	shrl	$9,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_4060:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	sall	$2,%ecx
	movl	%eax,%esi
	movl	(%ecx,%ebx),%eax
	addl	$-2,%eax
	movl	%eax,(%ecx,%ebx)
	testw	%si,%si
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%si,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4271:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4110:
	ret

FUNC(op_3138)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_4061:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	andl	$7,%ecx
	movl	%eax,%edx
	addl	$8,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	addl	$-2,%eax
	movl	%eax,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4272:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4111:
	ret

FUNC(op_3139)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_4062:
	bswapl	%eax
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	addl	$8,%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	addl	$-2,%eax
	movl	%eax,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4273:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4112:
	ret

FUNC(op_313a)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_4063:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	andl	$7,%ecx
	movl	%eax,%edx
	addl	$8,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,%ebx
	movl	(%ecx,%edx),%eax
	addl	$-2,%eax
	movl	%eax,(%ecx,%edx)
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%bx,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_4113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_4274:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_4113:
	ret

FUNC(Init020_04)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_4000-4
	movl	%eax,RR0_4001-4
	movl	%eax,RR0_4002-4
	movl	%eax,RR0_4003-4
	movl	%eax,RR0_4004-4
	movl	%eax,RR0_4005-4
	movl	%eax,RR0_4006-4
	movl	%eax,RR0_4007-4
	movl	%eax,RR0_4008-4
	movl	%eax,RR0_4009-4
	movl	%eax,RR0_4010-4
	movl	%eax,RR0_4011-4
	movl	%eax,RR0_4012-4
	movl	%eax,RR0_4013-4
	movl	%eax,RR0_4014-4
	movl	%eax,RR0_4015-4
	movl	%eax,RR0_4016-4
	movl	%eax,RR0_4017-4
	movl	%eax,RR0_4018-4
	movl	%eax,RR0_4019-4
	movl	%eax,RR0_4020-4
	movl	%eax,RR0_4021-4
	movl	%eax,RR0_4022-4
	movl	%eax,RR0_4023-4
	movl	%eax,RR0_4024-4
	movl	%eax,RR0_4025-4
	movl	%eax,RR0_4026-4
	movl	%eax,RR0_4027-4
	movl	%eax,RR0_4028-4
	movl	%eax,RR0_4029-4
	movl	%eax,RR0_4030-4
	movl	%eax,RR0_4031-4
	movl	%eax,RR0_4032-4
	movl	%eax,RR0_4033-4
	movl	%eax,RR0_4034-4
	movl	%eax,RR0_4035-4
	movl	%eax,RR0_4036-4
	movl	%eax,RR0_4037-4
	movl	%eax,RR0_4038-4
	movl	%eax,RR0_4039-4
	movl	%eax,RR0_4040-4
	movl	%eax,RR0_4041-4
	movl	%eax,RR0_4042-4
	movl	%eax,RR0_4043-4
	movl	%eax,RR0_4044-4
	movl	%eax,RR0_4045-4
	movl	%eax,RR0_4046-4
	movl	%eax,RR0_4047-4
	movl	%eax,RR0_4048-4
	movl	%eax,RR0_4049-4
	movl	%eax,RR0_4050-4
	movl	%eax,RR0_4051-4
	movl	%eax,RR0_4052-4
	movl	%eax,RR0_4053-4
	movl	%eax,RR0_4054-4
	movl	%eax,RR0_4055-4
	movl	%eax,RR0_4056-4
	movl	%eax,RR0_4057-4
	movl	%eax,RR0_4058-4
	movl	%eax,RR0_4059-4
	movl	%eax,RR0_4060-4
	movl	%eax,RR0_4061-4
	movl	%eax,RR0_4062-4
	movl	%eax,RR0_4063-4
	movl	%eax,RR0_4064-4
	movl	%eax,RR0_4065-4
	movl	%eax,RR0_4066-4
	movl	%eax,RR0_4067-4
	movl	%eax,RR0_4068-4
	movl	%eax,RR0_4069-4
	movl	%eax,RR0_4070-4
	movl	%eax,RR0_4071-4
	movl	%eax,RR0_4072-4
	movl	%eax,RR0_4073-4
	movl	%eax,RR0_4074-4
	movl	%eax,RR0_4075-4
	movl	%eax,RR0_4076-4
	movl	%eax,RR0_4077-4
	movl	%eax,RR0_4078-4
	movl	%eax,RR0_4079-4
	movl	%eax,RR0_4080-4
	movl	%eax,RR0_4081-4
	movl	%eax,RR0_4082-4
	movl	%eax,RR0_4083-4
	movl	%eax,RR0_4084-4
	movl	%eax,RR0_4085-4
	movl	%eax,RR0_4086-4
	movl	%eax,RR0_4087-4
	movl	%eax,RR0_4088-4
	movl	%eax,RR0_4089-4
	movl	%eax,RR0_4090-4
	movl	%eax,RR0_4091-4
	movl	%eax,RR0_4092-4
	movl	%eax,RR0_4093-4
	movl	%eax,RR0_4094-4
	movl	%eax,RR0_4095-4
	movl	%eax,RR0_4096-4
	movl	%eax,RR0_4097-4
	movl	%eax,RR0_4098-4
	movl	%eax,RR0_4099-4
	movl	%eax,RR0_4100-4
	movl	%eax,RR0_4101-4
	movl	%eax,RR0_4102-4
	movl	%eax,RR0_4103-4
	movl	%eax,RR0_4104-4
	movl	%eax,RR0_4105-4
	movl	%eax,RR0_4106-4
	movl	%eax,RR0_4107-4
	movl	%eax,RR0_4108-4
	movl	%eax,RR0_4109-4
	movl	%eax,RR0_4110-4
	movl	%eax,RR0_4111-4
	movl	%eax,RR0_4112-4
	movl	%eax,RR0_4113-4
	movl	%eax,RR0_4114-4
	movl	%eax,RR0_4115-4
	movl	%eax,RR0_4116-4
	movl	%eax,RR0_4117-4
	movl	%eax,RR0_4118-4
	movl	%eax,RR0_4119-4
	movl	%eax,RR0_4120-4
	movl	%eax,RR0_4121-4
	movl	%eax,RR0_4122-4
	movl	%eax,RR0_4123-4
	movl	%eax,RR0_4124-4
	movl	%eax,RR0_4125-4
	movl	%eax,RR0_4126-4
	movl	%eax,RR0_4127-4
	movl	%eax,RR0_4128-4
	movl	%eax,RR0_4129-4
	movl	%eax,RR0_4130-4
	movl	%eax,RR0_4131-4
	movl	%eax,RR0_4132-4
	movl	%eax,RR0_4133-4
	movl	%eax,RR0_4134-4
	movl	%eax,RR0_4135-4
	movl	%eax,RR0_4136-4
	movl	%eax,RR0_4137-4
	movl	%eax,RR0_4138-4
	movl	%eax,RR0_4139-4
	movl	%eax,RR0_4140-4
	movl	%eax,RR0_4141-4
	movl	%eax,RR0_4142-4
	movl	%eax,RR0_4143-4
	movl	%eax,RR0_4144-4
	movl	%eax,RR0_4145-4
	movl	%eax,RR0_4146-4
	movl	%eax,RR0_4147-4
	movl	%eax,RR0_4148-4
	movl	%eax,RR0_4149-4
	movl	%eax,RR0_4150-4
	movl	%eax,RR0_4151-4
	movl	%eax,RR0_4152-4
	movl	%eax,RR0_4153-4
	movl	%eax,RR0_4154-4
	movl	%eax,RR0_4155-4
	movl	%eax,RR0_4156-4
	movl	%eax,RR0_4157-4
	movl	%eax,RR0_4158-4
	movl	%eax,RR0_4159-4
	movl	%eax,RR0_4160-4
	movl	%eax,RR0_4161-4
	movl	%eax,RR0_4162-4
	movl	%eax,RR0_4163-4
	movl	%eax,RR0_4164-4
	movl	%eax,RR0_4165-4
	movl	%eax,RR0_4166-4
	movl	%eax,RR0_4167-4
	movl	%eax,RR0_4168-4
	movl	%eax,RR0_4169-4
	movl	%eax,RR0_4170-4
	movl	%eax,RR0_4171-4
	movl	%eax,RR0_4172-4
	movl	%eax,RR0_4173-4
	movl	%eax,RR0_4174-4
	movl	%eax,RR0_4175-4
	movl	%eax,RR0_4176-4
	movl	%eax,RR0_4177-4
	movl	%eax,RR0_4178-4
	movl	%eax,RR0_4179-4
	movl	%eax,RR0_4180-4
	movl	%eax,RR0_4181-4
	movl	%eax,RR0_4182-4
	movl	%eax,RR0_4183-4
	movl	%eax,RR0_4184-4
	movl	%eax,RR0_4185-4
	movl	%eax,RR0_4186-4
	movl	%eax,RR0_4187-4
	movl	%eax,RR0_4188-4
	movl	%eax,RR0_4189-4
	movl	%eax,RR0_4190-4
	movl	%eax,RR0_4191-4
	movl	%eax,RR0_4192-4
	movl	%eax,RR0_4193-4
	movl	%eax,RR0_4194-4
	movl	%eax,RR0_4195-4
	movl	%eax,RR0_4196-4
	movl	%eax,RR0_4197-4
	movl	%eax,RR0_4198-4
	movl	%eax,RR0_4199-4
	movl	%eax,RR0_4200-4
	movl	%eax,RR0_4201-4
	movl	%eax,RR0_4202-4
	movl	%eax,RR0_4203-4
	movl	%eax,RR0_4204-4
	movl	%eax,RR0_4205-4
	movl	%eax,RR0_4206-4
	movl	%eax,RR0_4207-4
	movl	%eax,RR0_4208-4
	movl	%eax,RR0_4209-4
	movl	%eax,RR0_4210-4
	movl	%eax,RR0_4211-4
	movl	%eax,RR0_4212-4
	movl	%eax,RR0_4213-4
	movl	%eax,RR0_4214-4
	movl	%eax,RR0_4215-4
	movl	%eax,RR0_4216-4
	movl	%eax,RR0_4217-4
	movl	%eax,RR0_4218-4
	movl	%eax,RR0_4219-4
	movl	%eax,RR0_4220-4
	movl	%eax,RR0_4221-4
	movl	%eax,RR0_4222-4
	movl	%eax,RR0_4223-4
	movl	%eax,RR0_4224-4
	movl	%eax,RR0_4225-4
	movl	%eax,RR0_4226-4
	movl	%eax,RR0_4227-4
	movl	%eax,RR0_4228-4
	movl	%eax,RR0_4229-4
	movl	%eax,RR0_4230-4
	movl	%eax,RR0_4231-4
	movl	%eax,RR0_4232-4
	movl	%eax,RR0_4233-4
	movl	%eax,RR0_4234-4
	movl	%eax,RR0_4235-4
	movl	%eax,RR0_4236-4
	movl	%eax,RR0_4237-4
	movl	%eax,RR0_4238-4
	movl	%eax,RR0_4239-4
	movl	%eax,RR0_4240-4
	movl	%eax,RR0_4241-4
	movl	%eax,RR0_4242-4
	movl	%eax,RR0_4243-4
	movl	%eax,RR0_4244-4
	movl	%eax,RR0_4245-4
	movl	%eax,RR0_4246-4
	movl	%eax,RR0_4247-4
	movl	%eax,RR0_4248-4
	movl	%eax,RR0_4249-4
	movl	%eax,RR0_4250-4
	movl	%eax,RR0_4251-4
	movl	%eax,RR0_4252-4
	movl	%eax,RR0_4253-4
	movl	%eax,RR0_4254-4
	movl	%eax,RR0_4255-4
	movl	%eax,RR0_4256-4
	movl	%eax,RR0_4257-4
	movl	%eax,RR0_4258-4
	movl	%eax,RR0_4259-4
	movl	%eax,RR0_4260-4
	movl	%eax,RR0_4261-4
	movl	%eax,RR0_4262-4
	movl	%eax,RR0_4263-4
	movl	%eax,RR0_4264-4
	movl	%eax,RR0_4265-4
	movl	%eax,RR0_4266-4
	movl	%eax,RR0_4267-4
	movl	%eax,RR0_4268-4
	movl	%eax,RR0_4269-4
	movl	%eax,RR0_4270-4
	movl	%eax,RR0_4271-4
	movl	%eax,RR0_4272-4
	movl	%eax,RR0_4273-4
	movl	%eax,RR0_4274-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_4000-4
	movl	%eax,RR2_4001-4
	movl	%eax,RR2_4002-4
	movl	%eax,RR2_4003-4
	movl	%eax,RR2_4004-4
	movl	%eax,RR2_4005-4
	movl	%eax,RR2_4006-4
	movl	%eax,RR2_4007-4
	movl	%eax,RR2_4008-4
	movl	%eax,RR2_4009-4
	movl	%eax,RR2_4010-4
	movl	%eax,RR2_4011-4
	movl	%eax,RR2_4012-4
	movl	%eax,RR2_4013-4
	movl	%eax,RR2_4014-4
	movl	%eax,RR2_4015-4
	movl	%eax,RR2_4016-4
	movl	%eax,RR2_4017-4
	movl	%eax,RR2_4018-4
	movl	%eax,RR2_4019-4
	movl	%eax,RR2_4020-4
	movl	%eax,RR2_4021-4
	movl	%eax,RR2_4022-4
	movl	%eax,RR2_4023-4
	movl	%eax,RR2_4024-4
	movl	%eax,RR2_4025-4
	movl	%eax,RR2_4026-4
	movl	%eax,RR2_4027-4
	movl	%eax,RR2_4028-4
	movl	%eax,RR2_4029-4
	movl	%eax,RR2_4030-4
	movl	%eax,RR2_4031-4
	movl	%eax,RR2_4032-4
	movl	%eax,RR2_4033-4
	movl	%eax,RR2_4034-4
	movl	%eax,RR2_4035-4
	movl	%eax,RR2_4036-4
	movl	%eax,RR2_4037-4
	movl	%eax,RR2_4038-4
	movl	%eax,RR2_4039-4
	movl	%eax,RR2_4040-4
	movl	%eax,RR2_4041-4
	movl	%eax,RR2_4042-4
	movl	%eax,RR2_4043-4
	movl	%eax,RR2_4044-4
	movl	%eax,RR2_4045-4
	movl	%eax,RR2_4046-4
	movl	%eax,RR2_4047-4
	movl	%eax,RR2_4048-4
	movl	%eax,RR2_4049-4
	movl	%eax,RR2_4050-4
	movl	%eax,RR2_4051-4
	movl	%eax,RR2_4052-4
	movl	%eax,RR2_4053-4
	movl	%eax,RR2_4054-4
	movl	%eax,RR2_4055-4
	movl	%eax,RR2_4056-4
	movl	%eax,RR2_4057-4
	movl	%eax,RR2_4058-4
	movl	%eax,RR2_4059-4
	movl	%eax,RR2_4060-4
	movl	%eax,RR2_4061-4
	movl	%eax,RR2_4062-4
	movl	%eax,RR2_4063-4
	incl	%eax
	incl	%eax
	movl	%eax,RR4_4000-4
	movl	%eax,RR4_4001-4
	movl	%eax,RR4_4002-4
	movl	%eax,RR4_4003-4
	movl	%eax,RR4_4004-4
	movl	%eax,RR4_4005-4
	movl	%eax,RR4_4006-4
	movl	%eax,RR4_4007-4
	movl	%eax,RR4_4008-4
	incl	%eax
	incl	%eax
	movl	%eax,RR6_4000-4
	movl	%eax,RR6_4001-4
	movl	%eax,RR6_4002-4
	movl	%eax,RR6_4003-4
	movl	%eax,RR6_4004-4
	movl	%eax,RR6_4005-4
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
