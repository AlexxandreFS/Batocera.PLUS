

FUNC(op_430)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,24-16(%esp)
	addl	$8,%eax
	movl	24-16(%esp),%edx
	movb	0x2164334A+3(%ecx),%cl
RR3_1000:
	addl	$4,%edx
	movb	%cl,31-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1000:
	rolw	$8,%si
	movl	24-16(%esp),%ecx
	movl	GLOBL(regs)(,%eax,4),%ebp
	addl	$6,%ecx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_392
	movswl	%di,%edi
L_1_392:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_393
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_394
	movl	%ebp,%ebx
L_1_394:
	testl	$64,%esi
	je	L_1_395
	movl	%ebp,%edi
L_1_395:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_396
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_396:
	cmpl	$48,%edx
	jne	L_1_399
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_399:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_402
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_402:
	cmpl	$3,16-16(%esp)
	jne	L_1_405
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_405:
	andl	$4,%esi
	jne	L_1_408
	addl	%edi,%ebx
L_1_408:
	cmpl	$0,16-16(%esp)
	je	L_1_409
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_409:
	testl	%esi,%esi
	je	L_1_412
	addl	%edi,%ebx
L_1_412:
	leal	(%ebp,%ebx),%edx
	jmp	L_1_413
	.align	2,0x90
L_1_393:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_1_413:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	subb	31-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1000:
	ret

FUNC(op_470)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1000:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1006:
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
	jne	L_1_506
	movswl	%di,%edi
L_1_506:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_507
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_508
	movl	%ebp,%ebx
L_1_508:
	testl	$64,%esi
	je	L_1_509
	movl	%ebp,%edi
L_1_509:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_510
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_510:
	cmpl	$48,%edx
	jne	L_1_513
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_513:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_516
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_516:
	cmpl	$3,16-16(%esp)
	jne	L_1_519
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_519:
	andl	$4,%esi
	jne	L_1_522
	addl	%edi,%ebx
L_1_522:
	cmpl	$0,16-16(%esp)
	je	L_1_523
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_523:
	testl	%esi,%esi
	je	L_1_526
	addl	%edi,%ebx
L_1_526:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_527
	.align	2,0x90
L_1_507:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_527:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	%eax,16-16(%esp)
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	subw	30-16(%esp),%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	movl	16-16(%esp),%ecx
	rolw	$8,%ax
	addl	GLOBL(W24)(%edx),%ecx
	movw	%ax,(%ecx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1001:
	ret

FUNC(op_4b0)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_1001:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,28-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1012:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_634
	movswl	%di,%edi
L_1_634:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_635
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_636
	movl	16-16(%esp),%ebx
L_1_636:
	testl	$64,%esi
	je	L_1_637
	movl	16-16(%esp),%edi
L_1_637:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_638
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1013:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_638:
	cmpl	$48,%edx
	jne	L_1_641
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_641:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_644
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_644:
	cmpl	$3,%ebp
	jne	L_1_647
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1016:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_647:
	andl	$4,%esi
	jne	L_1_650
	addl	%edi,%ebx
L_1_650:
	testl	%ebp,%ebp
	je	L_1_651
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_651:
	testl	%esi,%esi
	je	L_1_654
	addl	%edi,%ebx
L_1_654:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_1_655
	.align	2,0x90
L_1_635:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	24-16(%esp),%eax
	addl	%edi,%eax
L_1_655:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	subl	28-16(%esp),%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1002:
	ret

FUNC(op_4d0)

	movl	%eax,%ecx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_1002:
	rolw	$8,%ax
	movl	%eax,%edi
	addl	$8,%ecx
	movl	$GLOBL(regs),%ebx
	shrw	$12,%ax
	movl	(%ebx,%ecx,4),%edx
	cwtl
	movb	2(%ebx,%ecx,4),%cl
	movl	(%ebx,%eax,4),%esi
	movl	%edx,%eax
	andl	$255,%ecx
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movl	(%edx),%ecx
	bswapl	%ecx
	cmpl	%esi,%ecx
	je	L_1_702
	cmpl	%esi,%ebx
	jne	L_1_701
L_1_702:
	movl	$1,%eax
L_1_701:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%ebx
	jg	L_1_703
	xorl	%eax,%eax
	cmpl	%ebx,%esi
	jl	L_1_708
	cmpl	%ecx,%esi
	jle	L_1_704
	jmp	L_1_708
	.align	2,0x90
L_1_703:
	xorl	%eax,%eax
	cmpl	%ecx,%esi
	jg	L_1_708
	cmpl	%ebx,%esi
	jge	L_1_704
L_1_708:
	movl	$1,%eax
L_1_704:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%edi
	je	L_1_709
	testb	$1,regflags
	je	L_1_709
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_1_710
	.align	2,0x90
L_1_709:
	addl	$4,GLOBL(regs)+88
L_1_710:
	popl	%eax
	decl	%eax
	jl	JJ_1003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1003:
	ret

FUNC(op_4e8)

	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_1003:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%edi),%cx
RR4_1000:
	rolw	$8,%cx
	movl	$GLOBL(regs),%ebx
	movswl	%cx,%ecx
	addl	(%ebx,%edx,4),%ecx
	shrw	$12,%ax
	movl	%ecx,%edx
	cwtl
	shrl	$14,%edx
	movl	(%ebx,%eax,4),%ebx
	movl	%ecx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	addl	$4,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movl	(%ecx),%ecx
	bswapl	%ecx
	cmpl	%ebx,%ecx
	je	L_1_720
	cmpl	%ebx,%esi
	jne	L_1_719
L_1_720:
	movl	$1,%eax
L_1_719:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_1_721
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_726
	cmpl	%ecx,%ebx
	jle	L_1_722
	jmp	L_1_726
	.align	2,0x90
L_1_721:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_1_726
	cmpl	%esi,%ebx
	jge	L_1_722
L_1_726:
	movl	$1,%eax
L_1_722:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_1_727
	testb	$1,regflags
	je	L_1_727
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_1_728
	.align	2,0x90
L_1_727:
	addl	$6,GLOBL(regs)+88
L_1_728:
	popl	%eax
	decl	%eax
	jl	JJ_1004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1004:
	ret

FUNC(op_4f0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1004:
	rolw	$8,%ax
	movw	%ax,24-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1020:
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
	jne	L_1_734
	movswl	%di,%edi
L_1_734:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_735
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_736
	movl	%ebp,%ebx
L_1_736:
	testl	$64,%esi
	je	L_1_737
	movl	%ebp,%edi
L_1_737:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_738
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1021:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_738:
	cmpl	$48,%edx
	jne	L_1_741
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1022:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_741:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_744
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1023:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_744:
	cmpl	$3,16-16(%esp)
	jne	L_1_747
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1024:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_747:
	andl	$4,%esi
	jne	L_1_750
	addl	%edi,%ebx
L_1_750:
	cmpl	$0,16-16(%esp)
	je	L_1_751
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_751:
	testl	%esi,%esi
	je	L_1_754
	addl	%edi,%ebx
L_1_754:
	leal	(%ebp,%ebx),%edi
	jmp	L_1_755
	.align	2,0x90
L_1_735:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%eax,%edi
L_1_755:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	movl	%edi,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edi,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%esi
	bswapl	%esi
	leal	4(%edi),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edi
	bswapl	%edi
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	je	L_1_762
	cmpl	%ebx,%esi
	jne	L_1_761
L_1_762:
	movl	$1,%eax
L_1_761:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%edi,%esi
	jg	L_1_763
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_768
	cmpl	%edi,%ebx
	jle	L_1_764
	jmp	L_1_768
	.align	2,0x90
L_1_763:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	jg	L_1_768
	cmpl	%esi,%ebx
	jge	L_1_764
L_1_768:
	movl	$1,%eax
L_1_764:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_1_770
	testb	$1,regflags
	je	L_1_770
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_1_770:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1005:
	ret

FUNC(op_4f8)

	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_1005:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%edi),%cx
RR4_1001:
	rolw	$8,%cx
	movswl	%cx,%ecx
	shrw	$12,%ax
	movl	%ecx,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%ecx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	addl	$4,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movl	(%ecx),%ecx
	bswapl	%ecx
	cmpl	%ebx,%ecx
	je	L_1_780
	cmpl	%ebx,%esi
	jne	L_1_779
L_1_780:
	movl	$1,%eax
L_1_779:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_1_781
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_786
	cmpl	%ecx,%ebx
	jle	L_1_782
	jmp	L_1_786
	.align	2,0x90
L_1_781:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_1_786
	cmpl	%esi,%ebx
	jge	L_1_782
L_1_786:
	movl	$1,%eax
L_1_782:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_1_787
	testb	$1,regflags
	je	L_1_787
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_1_788
	.align	2,0x90
L_1_787:
	addl	$6,GLOBL(regs)+88
L_1_788:
	popl	%eax
	decl	%eax
	jl	JJ_1006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1026:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1006:
	ret

FUNC(op_4f9)

	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_1006:
	rolw	$8,%ax
	movl	%eax,%ebp
	movl	0x2164334A+4(%edi),%ecx
RR4_1002:
	bswapl	%ecx
	shrw	$12,%ax
	movl	%ecx,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%ecx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	addl	$4,%ecx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movl	(%ecx),%ecx
	bswapl	%ecx
	cmpl	%ebx,%ecx
	je	L_1_798
	cmpl	%ebx,%esi
	jne	L_1_797
L_1_798:
	movl	$1,%eax
L_1_797:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_1_799
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_804
	cmpl	%ecx,%ebx
	jle	L_1_800
	jmp	L_1_804
	.align	2,0x90
L_1_799:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_1_804
	cmpl	%esi,%ebx
	jge	L_1_800
L_1_804:
	movl	$1,%eax
L_1_800:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_1_805
	testb	$1,regflags
	je	L_1_805
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_1_806
	.align	2,0x90
L_1_805:
	addl	$8,GLOBL(regs)+88
L_1_806:
	popl	%eax
	decl	%eax
	jl	JJ_1007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1027:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1007:
	ret

FUNC(op_4fa)

	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_1007:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%edi),%ax
RR4_1003:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edi),%edx
	movl	%ebp,%eax
	shrw	$12,%ax
	movl	%edx,%ecx
	cwtl
	shrl	$14,%ecx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edx,%eax
	andl	$1020,%ecx
	andl	$65535,%eax
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movl	(%edx),%ecx
	bswapl	%ecx
	cmpl	%ebx,%ecx
	je	L_1_817
	cmpl	%ebx,%esi
	jne	L_1_816
L_1_817:
	movl	$1,%eax
L_1_816:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_1_818
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_823
	cmpl	%ecx,%ebx
	jle	L_1_819
	jmp	L_1_823
	.align	2,0x90
L_1_818:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_1_823
	cmpl	%esi,%ebx
	jge	L_1_819
L_1_823:
	movl	$1,%eax
L_1_819:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_1_824
	testb	$1,regflags
	je	L_1_824
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_1_825
	.align	2,0x90
L_1_824:
	addl	$6,GLOBL(regs)+88
L_1_825:
	popl	%eax
	decl	%eax
	jl	JJ_1008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1028:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1008:
	ret

FUNC(op_4fb)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1008:
	rolw	$8,%ax
	movl	%ecx,%edx
	movw	%ax,24-16(%esp)
	addl	$4,%edx
	addl	$6,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1029:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_832
	movswl	%di,%edi
L_1_832:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_833
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_834
	movl	%ebp,%ebx
L_1_834:
	testl	$64,%esi
	je	L_1_835
	movl	%ebp,%edi
L_1_835:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_836
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1030:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_836:
	cmpl	$48,%edx
	jne	L_1_839
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1031:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_839:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_842
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1032:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_842:
	cmpl	$3,16-16(%esp)
	jne	L_1_845
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1033:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_845:
	andl	$4,%esi
	jne	L_1_848
	addl	%edi,%ebx
L_1_848:
	cmpl	$0,16-16(%esp)
	je	L_1_849
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_849:
	testl	%esi,%esi
	je	L_1_852
	addl	%edi,%ebx
L_1_852:
	leal	(%ebp,%ebx),%edi
	jmp	L_1_853
	.align	2,0x90
L_1_833:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%eax,%edi
L_1_853:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	movl	%edi,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edi,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%esi
	bswapl	%esi
	leal	4(%edi),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edi
	bswapl	%edi
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	je	L_1_860
	cmpl	%ebx,%esi
	jne	L_1_859
L_1_860:
	movl	$1,%eax
L_1_859:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%edi,%esi
	jg	L_1_861
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_1_866
	cmpl	%edi,%ebx
	jle	L_1_862
	jmp	L_1_866
	.align	2,0x90
L_1_861:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	jg	L_1_866
	cmpl	%esi,%ebx
	jge	L_1_862
L_1_866:
	movl	$1,%eax
L_1_862:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_1_868
	testb	$1,regflags
	je	L_1_868
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_1_868:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1034:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1009:
	ret

FUNC(op_630)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,24-16(%esp)
	addl	$8,%eax
	movl	24-16(%esp),%edx
	movb	0x2164334A+3(%ecx),%cl
RR3_1001:
	addl	$4,%edx
	movb	%cl,31-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1035:
	rolw	$8,%si
	movl	24-16(%esp),%ecx
	movl	GLOBL(regs)(,%eax,4),%ebp
	addl	$6,%ecx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_910
	movswl	%di,%edi
L_1_910:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_911
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_912
	movl	%ebp,%ebx
L_1_912:
	testl	$64,%esi
	je	L_1_913
	movl	%ebp,%edi
L_1_913:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_914
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1036:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_914:
	cmpl	$48,%edx
	jne	L_1_917
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1037:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_917:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_920
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1038:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_920:
	cmpl	$3,16-16(%esp)
	jne	L_1_923
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1039:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_923:
	andl	$4,%esi
	jne	L_1_926
	addl	%edi,%ebx
L_1_926:
	cmpl	$0,16-16(%esp)
	je	L_1_927
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_927:
	testl	%esi,%esi
	je	L_1_930
	addl	%edi,%ebx
L_1_930:
	leal	(%ebp,%ebx),%edx
	jmp	L_1_931
	.align	2,0x90
L_1_911:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_1_931:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	addb	31-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1040:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1010:
	ret

FUNC(op_670)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1009:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1041:
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
	jne	L_1_1024
	movswl	%di,%edi
L_1_1024:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1025
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1026
	movl	%ebp,%ebx
L_1_1026:
	testl	$64,%esi
	je	L_1_1027
	movl	%ebp,%edi
L_1_1027:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1028
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1042:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1028:
	cmpl	$48,%edx
	jne	L_1_1031
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1043:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1031:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_1034
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1044:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1034:
	cmpl	$3,16-16(%esp)
	jne	L_1_1037
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1045:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1037:
	andl	$4,%esi
	jne	L_1_1040
	addl	%edi,%ebx
L_1_1040:
	cmpl	$0,16-16(%esp)
	je	L_1_1041
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1041:
	testl	%esi,%esi
	je	L_1_1044
	addl	%edi,%ebx
L_1_1044:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_1045
	.align	2,0x90
L_1_1025:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1045:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	%eax,16-16(%esp)
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	addw	30-16(%esp),%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	movl	16-16(%esp),%ecx
	rolw	$8,%ax
	addl	GLOBL(W24)(%edx),%ecx
	movw	%ax,(%ecx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1046:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1011:
	ret

FUNC(op_6b0)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_1010:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,28-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1047:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_1152
	movswl	%di,%edi
L_1_1152:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1153
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1154
	movl	16-16(%esp),%ebx
L_1_1154:
	testl	$64,%esi
	je	L_1_1155
	movl	16-16(%esp),%edi
L_1_1155:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1156
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1048:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_1156:
	cmpl	$48,%edx
	jne	L_1_1159
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1049:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1159:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_1162
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1050:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_1162:
	cmpl	$3,%ebp
	jne	L_1_1165
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1051:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_1165:
	andl	$4,%esi
	jne	L_1_1168
	addl	%edi,%ebx
L_1_1168:
	testl	%ebp,%ebp
	je	L_1_1169
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1169:
	testl	%esi,%esi
	je	L_1_1172
	addl	%edi,%ebx
L_1_1172:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_1_1173
	.align	2,0x90
L_1_1153:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	24-16(%esp),%eax
	addl	%edi,%eax
L_1_1173:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	addl	28-16(%esp),%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1012:
	ret

FUNC(op_830)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1011:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1053:
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
	jne	L_1_1292
	movswl	%di,%edi
L_1_1292:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1293
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1294
	movl	%ebp,%ebx
L_1_1294:
	testl	$64,%esi
	je	L_1_1295
	movl	%ebp,%edi
L_1_1295:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1296
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1054:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1296:
	cmpl	$48,%edx
	jne	L_1_1299
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1055:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1299:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_1302
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1056:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1302:
	cmpl	$3,16-16(%esp)
	jne	L_1_1305
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1057:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1305:
	andl	$4,%esi
	jne	L_1_1308
	addl	%edi,%ebx
L_1_1308:
	cmpl	$0,16-16(%esp)
	je	L_1_1309
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1309:
	testl	%esi,%esi
	je	L_1_1312
	addl	%edi,%ebx
L_1_1312:
	leal	(%ebp,%ebx),%edx
	jmp	L_1_1313
	.align	2,0x90
L_1_1293:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_1_1313:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	28-16(%esp),%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	addl	$16,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1013:
	ret

FUNC(op_83b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_1012:
	rolw	$8,%ax
	movw	%ax,24-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1059:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_1354
	movswl	%di,%edi
L_1_1354:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1355
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1356
	movl	16-16(%esp),%ebx
L_1_1356:
	testl	$64,%esi
	je	L_1_1357
	movl	16-16(%esp),%edi
L_1_1357:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1358
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1060:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_1358:
	cmpl	$48,%edx
	jne	L_1_1361
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1061:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1361:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_1364
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1062:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_1364:
	cmpl	$3,%ebp
	jne	L_1_1367
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1063:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_1_1367:
	andl	$4,%esi
	jne	L_1_1370
	addl	%edi,%ebx
L_1_1370:
	testl	%ebp,%ebp
	je	L_1_1371
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1371:
	testl	%esi,%esi
	je	L_1_1374
	addl	%edi,%ebx
L_1_1374:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_1_1375
	.align	2,0x90
L_1_1355:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_1_1375:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	24-16(%esp),%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	addl	$12,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1014:
	ret

FUNC(op_870)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1013:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1065:
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
	jne	L_1_1437
	movswl	%di,%edi
L_1_1437:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1438
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1439
	movl	%ebp,%ebx
L_1_1439:
	testl	$64,%esi
	je	L_1_1440
	movl	%ebp,%edi
L_1_1440:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1441
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1066:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1441:
	cmpl	$48,%edx
	jne	L_1_1444
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1067:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1444:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_1447
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1068:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1447:
	cmpl	$3,16-16(%esp)
	jne	L_1_1450
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1069:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1450:
	andl	$4,%esi
	jne	L_1_1453
	addl	%edi,%ebx
L_1_1453:
	cmpl	$0,16-16(%esp)
	je	L_1_1454
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1454:
	testl	%esi,%esi
	je	L_1_1457
	addl	%edi,%ebx
L_1_1457:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_1458
	.align	2,0x90
L_1_1438:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1458:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,16-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1070:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1015:
	ret

FUNC(op_87b)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_1014:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1071:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_1506
	movswl	%di,%edi
L_1_1506:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1507
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1508
	movl	20-16(%esp),%ebx
L_1_1508:
	testl	$64,%esi
	je	L_1_1509
	movl	20-16(%esp),%edi
L_1_1509:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1510
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1072:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_1510:
	cmpl	$48,%edx
	jne	L_1_1513
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1073:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1513:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_1516
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1074:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1516:
	cmpl	$3,%ebp
	jne	L_1_1519
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1075:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1519:
	andl	$4,%esi
	jne	L_1_1522
	addl	%edi,%ebx
L_1_1522:
	testl	%ebp,%ebp
	je	L_1_1523
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1523:
	testl	%esi,%esi
	je	L_1_1526
	addl	%edi,%ebx
L_1_1526:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_1_1527
	.align	2,0x90
L_1_1507:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1527:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,19-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	19-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1016:
	ret

FUNC(op_8b0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1015:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1077:
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
	jne	L_1_1584
	movswl	%di,%edi
L_1_1584:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1585
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1586
	movl	%ebp,%ebx
L_1_1586:
	testl	$64,%esi
	je	L_1_1587
	movl	%ebp,%edi
L_1_1587:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1588
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1078:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1588:
	cmpl	$48,%edx
	jne	L_1_1591
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1079:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1591:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_1594
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1080:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1594:
	cmpl	$3,16-16(%esp)
	jne	L_1_1597
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1081:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1597:
	andl	$4,%esi
	jne	L_1_1600
	addl	%edi,%ebx
L_1_1600:
	cmpl	$0,16-16(%esp)
	je	L_1_1601
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1601:
	testl	%esi,%esi
	je	L_1_1604
	addl	%edi,%ebx
L_1_1604:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_1605
	.align	2,0x90
L_1_1585:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1605:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,16-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	16-16(%esp),%dl
	movb	%dl,(%esi,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1017:
	ret

FUNC(op_8bb)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_1016:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1083:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_1653
	movswl	%di,%edi
L_1_1653:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1654
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1655
	movl	20-16(%esp),%ebx
L_1_1655:
	testl	$64,%esi
	je	L_1_1656
	movl	20-16(%esp),%edi
L_1_1656:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1657
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1084:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_1657:
	cmpl	$48,%edx
	jne	L_1_1660
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1085:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1660:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_1663
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1086:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1663:
	cmpl	$3,%ebp
	jne	L_1_1666
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1087:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1666:
	andl	$4,%esi
	jne	L_1_1669
	addl	%edi,%ebx
L_1_1669:
	testl	%ebp,%ebp
	je	L_1_1670
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1670:
	testl	%esi,%esi
	je	L_1_1673
	addl	%edi,%ebx
L_1_1673:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_1_1674
	.align	2,0x90
L_1_1654:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1674:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,19-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	19-16(%esp),%dl
	movb	%dl,(%esi,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1018:
	ret

FUNC(op_8f0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_1017:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_1089:
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
	jne	L_1_1731
	movswl	%di,%edi
L_1_1731:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1732
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1733
	movl	%ebp,%ebx
L_1_1733:
	testl	$64,%esi
	je	L_1_1734
	movl	%ebp,%edi
L_1_1734:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1735
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1090:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1735:
	cmpl	$48,%edx
	jne	L_1_1738
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1091:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1738:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_1_1741
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1092:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1741:
	cmpl	$3,16-16(%esp)
	jne	L_1_1744
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1093:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1744:
	andl	$4,%esi
	jne	L_1_1747
	addl	%edi,%ebx
L_1_1747:
	cmpl	$0,16-16(%esp)
	je	L_1_1748
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1748:
	testl	%esi,%esi
	je	L_1_1751
	addl	%edi,%ebx
L_1_1751:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_1752
	.align	2,0x90
L_1_1732:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1752:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,16-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1019:
	ret

FUNC(op_8fb)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_1018:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1095:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_1_1800
	movswl	%di,%edi
L_1_1800:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_1_1801
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1802
	movl	20-16(%esp),%ebx
L_1_1802:
	testl	$64,%esi
	je	L_1_1803
	movl	20-16(%esp),%edi
L_1_1803:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1804
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_1096:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_1_1804:
	cmpl	$48,%edx
	jne	L_1_1807
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1097:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1807:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_1_1810
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1098:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1810:
	cmpl	$3,%ebp
	jne	L_1_1813
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1099:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_1_1813:
	andl	$4,%esi
	jne	L_1_1816
	addl	%edi,%ebx
L_1_1816:
	testl	%ebp,%ebp
	je	L_1_1817
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1817:
	testl	%esi,%esi
	je	L_1_1820
	addl	%edi,%ebx
L_1_1820:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_1_1821
	.align	2,0x90
L_1_1801:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_1_1821:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movl	28-16(%esp),%edi
	movb	(%esi,%eax),%al
	andl	$7,%edi
	movb	%al,19-16(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	19-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1020:
	ret

FUNC(op_a30)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,28-16(%esp)
	addl	$8,%eax
	movb	0x2164334A+3(%ecx),%cl
RR3_1002:
	movl	28-16(%esp),%edx
	movl	28-16(%esp),%edi
	movb	%cl,35-16(%esp)
	addl	$4,%edx
	addl	$6,%edi
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_1101:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%edi,24-16(%esp)
	shrl	$10,%eax
	movl	%edi,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%ebp,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_1_1867
	movswl	16-16(%esp),%ecx
	movl	%ecx,16-16(%esp)
L_1_1867:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_1_1868
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_1_1869
	movl	%ebp,%ebx
L_1_1869:
	testl	$64,%esi
	je	L_1_1870
	movl	%ebp,16-16(%esp)
L_1_1870:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_1_1871
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_1102:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_1_1871:
	cmpl	$48,%edx
	jne	L_1_1874
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1103:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_1_1874:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_1_1877
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_1104:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1877:
	cmpl	$3,20-16(%esp)
	jne	L_1_1880
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_1105:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_1_1880:
	andl	$4,%esi
	jne	L_1_1883
	addl	16-16(%esp),%ebx
L_1_1883:
	cmpl	$0,20-16(%esp)
	je	L_1_1884
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_1_1884:
	testl	%esi,%esi
	je	L_1_1887
	addl	16-16(%esp),%ebx
L_1_1887:
	leal	(%ebp,%ebx),%eax
	jmp	L_1_1888
	.align	2,0x90
L_1_1868:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	16-16(%esp),%eax
L_1_1888:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	%eax,20-16(%esp)
	andl	$1020,%edx
	movl	20-16(%esp),%edi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%edi,%eax),%al
	xorb	%al,35-16(%esp)
	movb	35-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%edi,%eax)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1021:
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


FUNC(op_420)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%edi
	movb	0x2164334A+3(%eax),%al
RR3_1003:
	leal	8(%edx),%ebx
	movb	%al,15-12(%esp)
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ebx,%edi),%ecx
	subl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	movl	%ecx,%esi
	andl	$1020,%edx
	andl	$65535,%esi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%esi,%eax),%al
	movl	%ecx,(%ebx,%edi)
	movb	%al,%cl
	subb	15-12(%esp),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1022:
	ret

FUNC(op_428)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_1004:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	movb	(%eax,%ecx),%cl
	subb	0x2164334A+3(%ebx),%cl
RR3_1004:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1023:
	ret

FUNC(op_438)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_1005:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	movb	(%eax,%ecx),%cl
	subb	0x2164334A+3(%ebx),%cl
RR3_1005:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1024:
	ret

FUNC(op_439)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+4(%ebx),%ecx
RR4_1006:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	subb	0x2164334A+3(%ebx),%dl
RR3_1006:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1025:
	ret

FUNC(op_440)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_1019:
	rolw	$8,%cx
	sall	$2,%edx
	movl	$GLOBL(regs),%eax
	movw	(%edx,%eax),%si
	subw	%cx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%ecx
	movw	%cx,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1026:
	ret

FUNC(op_450)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	movb	GLOBL(regs)+2(,%edx,4),%cl
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1020:
	rolw	$8,%bx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	subw	%bx,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1027:
	ret

FUNC(op_458)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1021:
	rolw	$8,%bp
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(%ecx),%bl
	movl	%edx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%edx
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	subw	%bp,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1028:
	ret

FUNC(op_460)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%edx
	addl	$-2,%edx
	movl	GLOBL(regs)+88,%eax
	movl	%edx,%ebx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1022:
	rolw	$8,%bp
	shrl	$14,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	subw	%bp,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1029:
	ret

FUNC(op_468)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1023:
	rolw	$8,%bx
	xorl	%esi,%esi
	movw	0x2164334A+4(%eax),%si
RR4_1007:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1030:
	ret

FUNC(op_478)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1024:
	rolw	$8,%bx
	xorl	%esi,%esi
	movw	0x2164334A+4(%eax),%si
RR4_1008:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1031:
	ret

FUNC(op_479)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1025:
	rolw	$8,%bx
	movl	0x2164334A+4(%eax),%eax
RR4_1009:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1032:
	ret

FUNC(op_480)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_1026:
	bswapl	%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	subl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1033:
	ret

FUNC(op_490)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_1027:
	movb	GLOBL(regs)+2(,%edx,4),%cl
	bswapl	%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	subl	%ebx,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1034:
	ret

FUNC(op_498)

	xorl	%ecx,%ecx
	movl	$GLOBL(regs),%edi
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	addl	$8,%esi
	movl	0x2164334A+2(%eax),%ebp
RR2_1028:
	sall	$2,%esi
	bswapl	%ebp
	movl	(%esi,%edi),%ebx
	movb	2(%esi,%edi),%cl
	movl	%ebx,%edx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	addl	$4,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%esi,%edi)
	subl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1035:
	ret

FUNC(op_4a0)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%edi),%ebx
	movl	GLOBL(regs)+88,%eax
	addl	$-4,%ebx
	movl	0x2164334A+2(%eax),%ebp
RR2_1029:
	movl	%ebx,%ecx
	bswapl	%ebp
	shrl	$14,%ecx
	movl	%ebx,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%esi,%edi)
	subl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1036:
	ret

FUNC(op_4a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_1000:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_1030:
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1037:
	ret

FUNC(op_4b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_1001:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_1031:
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1038:
	ret

FUNC(op_4b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_1032:
	movl	0x2164334A+6(%eax),%eax
RR6_1002:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1039:
	ret

FUNC(op_600)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	movl	GLOBL(regs)+88,%ecx
	movb	(%edx,%eax),%bl
	addb	0x2164334A+3(%ecx),%bl
RR3_1007:
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%ecx
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1040:
	ret

FUNC(op_610)

	subl	$4,%esp
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	xorl	%ebx,%ebx
	movw	GLOBL(regs)(,%eax,4),%bx
	sall	$2,%edx
	movl	%ebx,8-8(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)+88,%ecx
	movb	(%esi,%eax),%bl
	addb	0x2164334A+3(%ecx),%bl
RR3_1008:
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,%ecx
	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1041:
	ret

FUNC(op_618)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%eax
	leal	8(%ebp),%ebx
	movb	0x2164334A+3(%eax),%al
RR3_1009:
	sall	$2,%ebx
	movb	%al,19-16(%esp)
	xorl	%edx,%edx
	movl	(%ebx,%edi),%ecx
	movb	2(%ebx,%edi),%dl
	movl	%ecx,%esi
	sall	$2,%edx
	andl	$65535,%esi
	movl	GLOBL(R24)(%edx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%ecx
	movb	(%esi,%eax),%al
	movl	%ecx,(%ebx,%edi)
	movb	%al,%cl
	addb	19-16(%esp),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1042:
	ret

FUNC(op_620)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%edi
	movb	0x2164334A+3(%eax),%al
RR3_1010:
	leal	8(%edx),%ebx
	movb	%al,15-12(%esp)
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ebx,%edi),%ecx
	subl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	movl	%ecx,%esi
	andl	$1020,%edx
	andl	$65535,%esi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%esi,%eax),%al
	movl	%ecx,(%ebx,%edi)
	movb	%al,%cl
	addb	15-12(%esp),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1043:
	ret

FUNC(op_628)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_1010:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	movb	(%eax,%ecx),%cl
	addb	0x2164334A+3(%ebx),%cl
RR3_1011:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1044:
	ret

FUNC(op_638)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_1011:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	movb	(%eax,%ecx),%cl
	addb	0x2164334A+3(%ebx),%cl
RR3_1012:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1045:
	ret

FUNC(op_639)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+4(%ebx),%ecx
RR4_1012:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	addb	0x2164334A+3(%ebx),%dl
RR3_1013:
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1046:
	ret

FUNC(op_640)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_1033:
	rolw	$8,%cx
	sall	$2,%edx
	movl	$GLOBL(regs),%eax
	movw	(%edx,%eax),%si
	addw	%cx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%ecx
	movw	%cx,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1047:
	ret

FUNC(op_650)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	movb	GLOBL(regs)+2(,%edx,4),%cl
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1034:
	rolw	$8,%bx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	addw	%bx,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1048:
	ret

FUNC(op_658)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1035:
	rolw	$8,%bp
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(%ecx),%bl
	movl	%edx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%edx
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	addw	%bp,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1049:
	ret

FUNC(op_660)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%edx
	addl	$-2,%edx
	movl	GLOBL(regs)+88,%eax
	movl	%edx,%ebx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1036:
	rolw	$8,%bp
	shrl	$14,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	addw	%bp,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1050:
	ret

FUNC(op_668)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1037:
	rolw	$8,%bx
	xorl	%esi,%esi
	movw	0x2164334A+4(%eax),%si
RR4_1013:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1051:
	ret

FUNC(op_678)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1038:
	rolw	$8,%bx
	xorl	%esi,%esi
	movw	0x2164334A+4(%eax),%si
RR4_1014:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1052:
	ret

FUNC(op_679)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_1039:
	rolw	$8,%bx
	movl	0x2164334A+4(%eax),%eax
RR4_1015:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	%bx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1053:
	ret

FUNC(op_680)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_1040:
	bswapl	%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	addl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1054:
	ret

FUNC(op_690)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_1041:
	movb	GLOBL(regs)+2(,%edx,4),%cl
	bswapl	%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	addl	%ebx,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1055:
	ret

FUNC(op_698)

	xorl	%ecx,%ecx
	movl	$GLOBL(regs),%edi
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	addl	$8,%esi
	movl	0x2164334A+2(%eax),%ebp
RR2_1042:
	sall	$2,%esi
	bswapl	%ebp
	movl	(%esi,%edi),%ebx
	movb	2(%esi,%edi),%cl
	movl	%ebx,%edx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	addl	$4,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%esi,%edi)
	addl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1056:
	ret

FUNC(op_6a0)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%edi),%ebx
	movl	GLOBL(regs)+88,%eax
	addl	$-4,%ebx
	movl	0x2164334A+2(%eax),%ebp
RR2_1043:
	movl	%ebx,%ecx
	bswapl	%ebp
	shrl	$14,%ecx
	movl	%ebx,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%esi,%edi)
	addl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1057:
	ret

FUNC(op_6a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_1003:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_1044:
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1058:
	ret

FUNC(op_6b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_1004:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_1045:
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1059:
	ret

FUNC(op_6b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_1046:
	movl	0x2164334A+6(%eax),%eax
RR6_1005:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	bswapl	%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	%ebx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1060:
	ret

FUNC(op_6c0)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1061:
	ret

FUNC(op_6c8)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1062:
	ret

FUNC(op_6d0)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1063:
	ret

FUNC(op_6e8)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1064:
	ret

FUNC(op_6f0)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1065:
	ret

FUNC(op_6f8)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1066:
	ret

FUNC(op_6f9)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1067:
	ret

FUNC(op_6fa)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1068:
	ret

FUNC(op_6fb)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1069:
	ret

FUNC(op_800)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_1047:
	rolw	$8,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	GLOBL(regs)(,%edx,4),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	addl	$4,%ebx
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%ebx,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1070:
	ret

FUNC(op_810)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(regs)+88,%esi
	movl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%esi),%bx
RR2_1048:
	rolw	$8,%bx
	movsbl	(%ecx,%eax),%eax
	movl	%ebx,%ecx
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$4,%esi
	movb	%al,%dl
	movl	%esi,GLOBL(regs)+88
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	popl	%ebx
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1071:
	ret

FUNC(op_818)

	movl	%eax,%edi
	pushl	%ebx
	andl	$7,%edi
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	leal	8(%edi),%ecx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1049:
	rolw	$8,%bp
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	movl	%ebp,%ecx
	movsbl	%al,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	addl	$4,GLOBL(regs)+88
	xorb	$1,%al
	popl	%ebx
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1072:
	ret

FUNC(op_820)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	leal	8(%edx),%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_1050:
	rolw	$8,%di
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	movl	%edi,%ecx
	movsbl	%al,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$4,GLOBL(regs)+88
	movb	%al,%dl
	popl	%ebx
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	popl	%esi
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1073:
	ret

FUNC(op_828)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%esi),%ax
RR4_1016:
	rolw	$8,%ax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%esi),%bx
RR2_1051:
	rolw	$8,%bx
	shrl	$14,%edx
	movl	%ebx,%ecx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	andl	$7,%ecx
	movsbl	(%eax,%edx),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$6,%esi
	movb	%al,%dl
	popl	%ebx
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%esi,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1074:
	ret

FUNC(op_838)

	movl	GLOBL(regs)+88,%esi
	xorl	%edx,%edx
	movw	0x2164334A+4(%esi),%dx
RR4_1017:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%esi),%bx
RR2_1052:
	rolw	$8,%bx
	shrl	$14,%eax
	movl	%ebx,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$6,%esi
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%esi,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1075:
	ret

FUNC(op_839)

	movl	GLOBL(regs)+88,%esi
	movl	0x2164334A+4(%esi),%edx
RR4_1018:
	bswapl	%edx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%esi),%bx
RR2_1053:
	rolw	$8,%bx
	shrl	$14,%eax
	movl	%ebx,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$8,%esi
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%esi,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1076:
	ret

FUNC(op_83a)

	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%esi),%ax
RR4_1019:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%esi),%eax
	movl	%eax,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%esi),%bx
RR2_1054:
	rolw	$8,%bx
	shrl	$14,%edx
	movl	%ebx,%ecx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	andl	$7,%ecx
	movsbl	(%eax,%edx),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$6,%esi
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%esi,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1077:
	ret

FUNC(op_83c)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_1055:
	rolw	$8,%dx
	movl	%edx,%ecx
	movsbl	0x2164334A+5(%ebx),%eax
RR5_1000:
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	addl	$6,%ebx
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	movl	%ebx,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_1078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1078:
	ret

FUNC(op_840)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_1056:
	rolw	$8,%cx
	movl	%ecx,%eax
	sall	$2,%ebx
	movl	%eax,%edi
	movl	(%ebx,%esi),%ecx
	andl	$31,%edi
	movl	%ecx,12-12(%esp)
	movl	%ecx,%eax
	movl	%edi,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	xorl	12-12(%esp),%eax
	movl	%eax,(%ebx,%esi)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1079:
	ret

FUNC(op_850)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	xorl	%edi,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%edx,4),%bl
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_1057:
	rolw	$8,%si
	sall	$2,%ebx
	movw	GLOBL(regs)(,%edx,4),%di
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%edi,%eax),%al
	andl	$7,%esi
	movb	%al,15-12(%esp)
	movl	%esi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%edi,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1080:
	ret

FUNC(op_858)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	16-16(%esp),%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1058:
	rolw	$8,%bp
	movl	%edx,%edi
	movzbl	GLOBL(regs)+2(%ecx),%esi
	andl	$65535,%edi
	sall	$2,%esi
	movl	%edi,20-16(%esp)
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	16-16(%esp),%edi
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	20-16(%esp),%edi
	movb	%bl,(%edi,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1081:
	ret

FUNC(op_860)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	leal	8(%edx),%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1059:
	rolw	$8,%bp
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%esi
	shrl	$14,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movb	%bl,(%edi,%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1082:
	ret

FUNC(op_868)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_1060:
	rolw	$8,%di
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1020:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	addl	$8,%edx
	movswl	12-12(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1083:
	ret

FUNC(op_878)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1061:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1021:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1084:
	ret

FUNC(op_879)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+4(%eax),%ebx
RR4_1022:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1062:
	rolw	$8,%dx
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movl	%edx,%edi
	movb	(%ebx,%eax),%al
	andl	$7,%edi
	movb	%al,15-12(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%cl
	movb	%cl,(%ebx,%edx)
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1085:
	ret

FUNC(op_87a)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_1023:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_1063:
	rolw	$8,%dx
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1086:
	ret

FUNC(op_880)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_1064:
	rolw	$8,%cx
	movl	%ecx,%eax
	sall	$2,%ebx
	movl	%eax,%edi
	movl	(%ebx,%esi),%ecx
	andl	$31,%edi
	movl	%ecx,12-12(%esp)
	movl	%ecx,%eax
	movl	%edi,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	roll	%cl,%eax
	andl	12-12(%esp),%eax
	movl	%eax,(%ebx,%esi)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1087:
	ret

FUNC(op_890)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	xorl	%edi,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%edx,4),%bl
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_1065:
	rolw	$8,%si
	sall	$2,%ebx
	movw	GLOBL(regs)(,%edx,4),%di
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%edi,%eax),%al
	andl	$7,%esi
	movb	%al,15-12(%esp)
	movl	%esi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	15-12(%esp),%dl
	movb	%dl,(%edi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1088:
	ret

FUNC(op_898)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	16-16(%esp),%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1066:
	rolw	$8,%bp
	movl	%edx,%edi
	movzbl	GLOBL(regs)+2(%ecx),%esi
	andl	$65535,%edi
	sall	$2,%esi
	movl	%edi,20-16(%esp)
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	16-16(%esp),%edi
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	20-16(%esp),%edi
	movb	%bl,(%edi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1089:
	ret

FUNC(op_8a0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	leal	8(%edx),%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1067:
	rolw	$8,%bp
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%esi
	shrl	$14,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movb	%bl,(%edi,%eax)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1090:
	ret

FUNC(op_8a8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_1068:
	rolw	$8,%di
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1024:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	addl	$8,%edx
	movswl	12-12(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1091:
	ret

FUNC(op_8b8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1069:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1025:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1092:
	ret

FUNC(op_8b9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+4(%eax),%ebx
RR4_1026:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1070:
	rolw	$8,%dx
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movl	%edx,%edi
	movb	(%ebx,%eax),%al
	andl	$7,%edi
	movb	%al,15-12(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	15-12(%esp),%dl
	movb	%dl,(%ebx,%eax)
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1093:
	ret

FUNC(op_8ba)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_1027:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_1071:
	rolw	$8,%dx
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1094:
	ret

FUNC(op_8c0)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_1072:
	rolw	$8,%cx
	movl	%ecx,%eax
	sall	$2,%ebx
	movl	%eax,%edi
	movl	(%ebx,%esi),%ecx
	andl	$31,%edi
	movl	%ecx,12-12(%esp)
	movl	%ecx,%eax
	movl	%edi,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	orl	12-12(%esp),%eax
	movl	%eax,(%ebx,%esi)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1095:
	ret

FUNC(op_8d0)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	xorl	%edi,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%edx,4),%bl
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_1073:
	rolw	$8,%si
	sall	$2,%ebx
	movw	GLOBL(regs)(,%edx,4),%di
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%edi,%eax),%al
	andl	$7,%esi
	movb	%al,15-12(%esp)
	movl	%esi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%edi,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1096:
	ret

FUNC(op_8d8)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	16-16(%esp),%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	GLOBL(regs)(%ecx),%edx
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1074:
	rolw	$8,%bp
	movl	%edx,%edi
	movzbl	GLOBL(regs)+2(%ecx),%esi
	andl	$65535,%edi
	sall	$2,%esi
	movl	%edi,20-16(%esp)
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	16-16(%esp),%edi
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	20-16(%esp),%edi
	movb	%bl,(%edi,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1097:
	ret

FUNC(op_8e0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	leal	8(%edx),%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebp,%ebp
	movw	0x2164334A+2(%eax),%bp
RR2_1075:
	rolw	$8,%bp
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%esi
	shrl	$14,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebp,%ecx
	movsbl	%bl,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movb	%bl,(%edi,%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1098:
	ret

FUNC(op_8e8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_1076:
	rolw	$8,%di
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1028:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	addl	$8,%edx
	movswl	12-12(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1099:
	ret

FUNC(op_8f8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1077:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_1029:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1100:
	ret

FUNC(op_8f9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+4(%eax),%ebx
RR4_1030:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1078:
	rolw	$8,%dx
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movl	%edx,%edi
	movb	(%ebx,%eax),%al
	andl	$7,%edi
	movb	%al,15-12(%esp)
	movl	%edi,%ecx
	movsbl	%al,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%cl
	movb	%cl,(%ebx,%edx)
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1101:
	ret

FUNC(op_8fa)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_1031:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_1079:
	rolw	$8,%dx
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	%edx,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%bl
	movl	%edi,%ecx
	movsbl	%bl,%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1102:
	ret

FUNC(op_a00)

	movl	%eax,%ecx
	movl	$GLOBL(regs),%edx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	sall	$2,%ecx
	movb	0x2164334A+3(%eax),%al
RR3_1014:
	xorb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1103:
	ret

FUNC(op_a10)

	andl	$7,%eax
	xorl	%edx,%edx
	xorl	%ecx,%ecx
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_1015:
	movl	GLOBL(R24)(%edx),%eax
	xorb	(%ecx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1104:
	ret

FUNC(op_a18)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	leal	8(%ebp),%ebx
	movb	0x2164334A+3(%eax),%al
RR3_1016:
	sall	$2,%ebx
	movb	%al,19-16(%esp)
	xorl	%ecx,%ecx
	movb	2(%ebx,%esi),%cl
	movl	(%ebx,%esi),%edi
	movl	(%ebx,%esi),%edx
	sall	$2,%ecx
	andl	$65535,%edi
	movl	GLOBL(R24)(%ecx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%edi,%eax),%al
	movl	%edx,(%ebx,%esi)
	xorb	%al,19-16(%esp)
	movb	19-16(%esp),%dl
	testb	%dl,%dl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	GLOBL(W24)(%ecx),%eax
	movb	%dl,(%edi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1105:
	ret

FUNC(op_a20)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%edi
	movb	0x2164334A+3(%eax),%al
RR3_1017:
	leal	8(%edx),%ebx
	movb	%al,19-12(%esp)
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ebx,%edi),%edx
	subl	%eax,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	movl	%edx,%esi
	movl	%ecx,12-12(%esp)
	andl	$65535,%esi
	movl	GLOBL(R24)(%ecx),%eax
	movb	(%esi,%eax),%al
	movl	%edx,(%ebx,%edi)
	xorb	%al,19-12(%esp)
	movb	19-12(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	12-12(%esp),%ecx
	movl	GLOBL(W24)(%ecx),%eax
	movb	19-12(%esp),%cl
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_1106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1106:
	ret

FUNC(op_a28)

	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_1032:
	rolw	$8,%dx
	addl	$8,%eax
	movswl	%dx,%edx
	addl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_1018:
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	xorb	(%edx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%al,(%edx,%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1107:
	ret

FUNC(op_a38)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_1033:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_1019:
	movl	GLOBL(R24)(%ecx),%eax
	xorb	(%edx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%al,(%edx,%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1108:
	ret

FUNC(op_a39)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+4(%ebx),%ecx
RR4_1034:
	bswapl	%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_1020:
	movl	GLOBL(R24)(%edx),%eax
	xorb	(%ecx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1109:
	ret

FUNC(op_a3c)

	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1080:
	rolw	$8,%dx
	movl	%edx,%eax
	movb	$0,%ah
	xorw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1110:
	ret

FUNC(op_a40)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_1081:
	rolw	$8,%si
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	xorw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1111:
	ret

FUNC(op_a50)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_1082:
	rolw	$8,%si
	addl	$8,%edx
	movl	%esi,%eax
	movb	GLOBL(regs)+2(,%edx,4),%cl
	movl	%eax,%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	xorl	%eax,%ebx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%bx,%ax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1112:
	ret

FUNC(op_a58)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	movl	$GLOBL(regs),%ebp
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_1083:
	rolw	$8,%dx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%ebp),%bl
	movl	(%ecx,%ebp),%esi
	movl	%eax,%edi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%ebp),%edx
	addl	$2,%edx
	xorl	%eax,%edi
	movl	%edx,(%ecx,%ebp)
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%di,%ax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_1113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_1198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_1113:
	ret

FUNC(Init020_01)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_1000-4
	movl	%eax,RR0_1001-4
	movl	%eax,RR0_1002-4
	movl	%eax,RR0_1003-4
	movl	%eax,RR0_1004-4
	movl	%eax,RR0_1005-4
	movl	%eax,RR0_1006-4
	movl	%eax,RR0_1007-4
	movl	%eax,RR0_1008-4
	movl	%eax,RR0_1009-4
	movl	%eax,RR0_1010-4
	movl	%eax,RR0_1011-4
	movl	%eax,RR0_1012-4
	movl	%eax,RR0_1013-4
	movl	%eax,RR0_1014-4
	movl	%eax,RR0_1015-4
	movl	%eax,RR0_1016-4
	movl	%eax,RR0_1017-4
	movl	%eax,RR0_1018-4
	movl	%eax,RR0_1019-4
	movl	%eax,RR0_1020-4
	movl	%eax,RR0_1021-4
	movl	%eax,RR0_1022-4
	movl	%eax,RR0_1023-4
	movl	%eax,RR0_1024-4
	movl	%eax,RR0_1025-4
	movl	%eax,RR0_1026-4
	movl	%eax,RR0_1027-4
	movl	%eax,RR0_1028-4
	movl	%eax,RR0_1029-4
	movl	%eax,RR0_1030-4
	movl	%eax,RR0_1031-4
	movl	%eax,RR0_1032-4
	movl	%eax,RR0_1033-4
	movl	%eax,RR0_1034-4
	movl	%eax,RR0_1035-4
	movl	%eax,RR0_1036-4
	movl	%eax,RR0_1037-4
	movl	%eax,RR0_1038-4
	movl	%eax,RR0_1039-4
	movl	%eax,RR0_1040-4
	movl	%eax,RR0_1041-4
	movl	%eax,RR0_1042-4
	movl	%eax,RR0_1043-4
	movl	%eax,RR0_1044-4
	movl	%eax,RR0_1045-4
	movl	%eax,RR0_1046-4
	movl	%eax,RR0_1047-4
	movl	%eax,RR0_1048-4
	movl	%eax,RR0_1049-4
	movl	%eax,RR0_1050-4
	movl	%eax,RR0_1051-4
	movl	%eax,RR0_1052-4
	movl	%eax,RR0_1053-4
	movl	%eax,RR0_1054-4
	movl	%eax,RR0_1055-4
	movl	%eax,RR0_1056-4
	movl	%eax,RR0_1057-4
	movl	%eax,RR0_1058-4
	movl	%eax,RR0_1059-4
	movl	%eax,RR0_1060-4
	movl	%eax,RR0_1061-4
	movl	%eax,RR0_1062-4
	movl	%eax,RR0_1063-4
	movl	%eax,RR0_1064-4
	movl	%eax,RR0_1065-4
	movl	%eax,RR0_1066-4
	movl	%eax,RR0_1067-4
	movl	%eax,RR0_1068-4
	movl	%eax,RR0_1069-4
	movl	%eax,RR0_1070-4
	movl	%eax,RR0_1071-4
	movl	%eax,RR0_1072-4
	movl	%eax,RR0_1073-4
	movl	%eax,RR0_1074-4
	movl	%eax,RR0_1075-4
	movl	%eax,RR0_1076-4
	movl	%eax,RR0_1077-4
	movl	%eax,RR0_1078-4
	movl	%eax,RR0_1079-4
	movl	%eax,RR0_1080-4
	movl	%eax,RR0_1081-4
	movl	%eax,RR0_1082-4
	movl	%eax,RR0_1083-4
	movl	%eax,RR0_1084-4
	movl	%eax,RR0_1085-4
	movl	%eax,RR0_1086-4
	movl	%eax,RR0_1087-4
	movl	%eax,RR0_1088-4
	movl	%eax,RR0_1089-4
	movl	%eax,RR0_1090-4
	movl	%eax,RR0_1091-4
	movl	%eax,RR0_1092-4
	movl	%eax,RR0_1093-4
	movl	%eax,RR0_1094-4
	movl	%eax,RR0_1095-4
	movl	%eax,RR0_1096-4
	movl	%eax,RR0_1097-4
	movl	%eax,RR0_1098-4
	movl	%eax,RR0_1099-4
	movl	%eax,RR0_1100-4
	movl	%eax,RR0_1101-4
	movl	%eax,RR0_1102-4
	movl	%eax,RR0_1103-4
	movl	%eax,RR0_1104-4
	movl	%eax,RR0_1105-4
	movl	%eax,RR0_1106-4
	movl	%eax,RR0_1107-4
	movl	%eax,RR0_1108-4
	movl	%eax,RR0_1109-4
	movl	%eax,RR0_1110-4
	movl	%eax,RR0_1111-4
	movl	%eax,RR0_1112-4
	movl	%eax,RR0_1113-4
	movl	%eax,RR0_1114-4
	movl	%eax,RR0_1115-4
	movl	%eax,RR0_1116-4
	movl	%eax,RR0_1117-4
	movl	%eax,RR0_1118-4
	movl	%eax,RR0_1119-4
	movl	%eax,RR0_1120-4
	movl	%eax,RR0_1121-4
	movl	%eax,RR0_1122-4
	movl	%eax,RR0_1123-4
	movl	%eax,RR0_1124-4
	movl	%eax,RR0_1125-4
	movl	%eax,RR0_1126-4
	movl	%eax,RR0_1127-4
	movl	%eax,RR0_1128-4
	movl	%eax,RR0_1129-4
	movl	%eax,RR0_1130-4
	movl	%eax,RR0_1131-4
	movl	%eax,RR0_1132-4
	movl	%eax,RR0_1133-4
	movl	%eax,RR0_1134-4
	movl	%eax,RR0_1135-4
	movl	%eax,RR0_1136-4
	movl	%eax,RR0_1137-4
	movl	%eax,RR0_1138-4
	movl	%eax,RR0_1139-4
	movl	%eax,RR0_1140-4
	movl	%eax,RR0_1141-4
	movl	%eax,RR0_1142-4
	movl	%eax,RR0_1143-4
	movl	%eax,RR0_1144-4
	movl	%eax,RR0_1145-4
	movl	%eax,RR0_1146-4
	movl	%eax,RR0_1147-4
	movl	%eax,RR0_1148-4
	movl	%eax,RR0_1149-4
	movl	%eax,RR0_1150-4
	movl	%eax,RR0_1151-4
	movl	%eax,RR0_1152-4
	movl	%eax,RR0_1153-4
	movl	%eax,RR0_1154-4
	movl	%eax,RR0_1155-4
	movl	%eax,RR0_1156-4
	movl	%eax,RR0_1157-4
	movl	%eax,RR0_1158-4
	movl	%eax,RR0_1159-4
	movl	%eax,RR0_1160-4
	movl	%eax,RR0_1161-4
	movl	%eax,RR0_1162-4
	movl	%eax,RR0_1163-4
	movl	%eax,RR0_1164-4
	movl	%eax,RR0_1165-4
	movl	%eax,RR0_1166-4
	movl	%eax,RR0_1167-4
	movl	%eax,RR0_1168-4
	movl	%eax,RR0_1169-4
	movl	%eax,RR0_1170-4
	movl	%eax,RR0_1171-4
	movl	%eax,RR0_1172-4
	movl	%eax,RR0_1173-4
	movl	%eax,RR0_1174-4
	movl	%eax,RR0_1175-4
	movl	%eax,RR0_1176-4
	movl	%eax,RR0_1177-4
	movl	%eax,RR0_1178-4
	movl	%eax,RR0_1179-4
	movl	%eax,RR0_1180-4
	movl	%eax,RR0_1181-4
	movl	%eax,RR0_1182-4
	movl	%eax,RR0_1183-4
	movl	%eax,RR0_1184-4
	movl	%eax,RR0_1185-4
	movl	%eax,RR0_1186-4
	movl	%eax,RR0_1187-4
	movl	%eax,RR0_1188-4
	movl	%eax,RR0_1189-4
	movl	%eax,RR0_1190-4
	movl	%eax,RR0_1191-4
	movl	%eax,RR0_1192-4
	movl	%eax,RR0_1193-4
	movl	%eax,RR0_1194-4
	movl	%eax,RR0_1195-4
	movl	%eax,RR0_1196-4
	movl	%eax,RR0_1197-4
	movl	%eax,RR0_1198-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_1000-4
	movl	%eax,RR2_1001-4
	movl	%eax,RR2_1002-4
	movl	%eax,RR2_1003-4
	movl	%eax,RR2_1004-4
	movl	%eax,RR2_1005-4
	movl	%eax,RR2_1006-4
	movl	%eax,RR2_1007-4
	movl	%eax,RR2_1008-4
	movl	%eax,RR2_1009-4
	movl	%eax,RR2_1010-4
	movl	%eax,RR2_1011-4
	movl	%eax,RR2_1012-4
	movl	%eax,RR2_1013-4
	movl	%eax,RR2_1014-4
	movl	%eax,RR2_1015-4
	movl	%eax,RR2_1016-4
	movl	%eax,RR2_1017-4
	movl	%eax,RR2_1018-4
	movl	%eax,RR2_1019-4
	movl	%eax,RR2_1020-4
	movl	%eax,RR2_1021-4
	movl	%eax,RR2_1022-4
	movl	%eax,RR2_1023-4
	movl	%eax,RR2_1024-4
	movl	%eax,RR2_1025-4
	movl	%eax,RR2_1026-4
	movl	%eax,RR2_1027-4
	movl	%eax,RR2_1028-4
	movl	%eax,RR2_1029-4
	movl	%eax,RR2_1030-4
	movl	%eax,RR2_1031-4
	movl	%eax,RR2_1032-4
	movl	%eax,RR2_1033-4
	movl	%eax,RR2_1034-4
	movl	%eax,RR2_1035-4
	movl	%eax,RR2_1036-4
	movl	%eax,RR2_1037-4
	movl	%eax,RR2_1038-4
	movl	%eax,RR2_1039-4
	movl	%eax,RR2_1040-4
	movl	%eax,RR2_1041-4
	movl	%eax,RR2_1042-4
	movl	%eax,RR2_1043-4
	movl	%eax,RR2_1044-4
	movl	%eax,RR2_1045-4
	movl	%eax,RR2_1046-4
	movl	%eax,RR2_1047-4
	movl	%eax,RR2_1048-4
	movl	%eax,RR2_1049-4
	movl	%eax,RR2_1050-4
	movl	%eax,RR2_1051-4
	movl	%eax,RR2_1052-4
	movl	%eax,RR2_1053-4
	movl	%eax,RR2_1054-4
	movl	%eax,RR2_1055-4
	movl	%eax,RR2_1056-4
	movl	%eax,RR2_1057-4
	movl	%eax,RR2_1058-4
	movl	%eax,RR2_1059-4
	movl	%eax,RR2_1060-4
	movl	%eax,RR2_1061-4
	movl	%eax,RR2_1062-4
	movl	%eax,RR2_1063-4
	movl	%eax,RR2_1064-4
	movl	%eax,RR2_1065-4
	movl	%eax,RR2_1066-4
	movl	%eax,RR2_1067-4
	movl	%eax,RR2_1068-4
	movl	%eax,RR2_1069-4
	movl	%eax,RR2_1070-4
	movl	%eax,RR2_1071-4
	movl	%eax,RR2_1072-4
	movl	%eax,RR2_1073-4
	movl	%eax,RR2_1074-4
	movl	%eax,RR2_1075-4
	movl	%eax,RR2_1076-4
	movl	%eax,RR2_1077-4
	movl	%eax,RR2_1078-4
	movl	%eax,RR2_1079-4
	movl	%eax,RR2_1080-4
	movl	%eax,RR2_1081-4
	movl	%eax,RR2_1082-4
	movl	%eax,RR2_1083-4
	incl	%eax
	movl	%eax,RR3_1000-4
	movl	%eax,RR3_1001-4
	movl	%eax,RR3_1002-4
	movl	%eax,RR3_1003-4
	movl	%eax,RR3_1004-4
	movl	%eax,RR3_1005-4
	movl	%eax,RR3_1006-4
	movl	%eax,RR3_1007-4
	movl	%eax,RR3_1008-4
	movl	%eax,RR3_1009-4
	movl	%eax,RR3_1010-4
	movl	%eax,RR3_1011-4
	movl	%eax,RR3_1012-4
	movl	%eax,RR3_1013-4
	movl	%eax,RR3_1014-4
	movl	%eax,RR3_1015-4
	movl	%eax,RR3_1016-4
	movl	%eax,RR3_1017-4
	movl	%eax,RR3_1018-4
	movl	%eax,RR3_1019-4
	movl	%eax,RR3_1020-4
	incl	%eax
	movl	%eax,RR4_1000-4
	movl	%eax,RR4_1001-4
	movl	%eax,RR4_1002-4
	movl	%eax,RR4_1003-4
	movl	%eax,RR4_1004-4
	movl	%eax,RR4_1005-4
	movl	%eax,RR4_1006-4
	movl	%eax,RR4_1007-4
	movl	%eax,RR4_1008-4
	movl	%eax,RR4_1009-4
	movl	%eax,RR4_1010-4
	movl	%eax,RR4_1011-4
	movl	%eax,RR4_1012-4
	movl	%eax,RR4_1013-4
	movl	%eax,RR4_1014-4
	movl	%eax,RR4_1015-4
	movl	%eax,RR4_1016-4
	movl	%eax,RR4_1017-4
	movl	%eax,RR4_1018-4
	movl	%eax,RR4_1019-4
	movl	%eax,RR4_1020-4
	movl	%eax,RR4_1021-4
	movl	%eax,RR4_1022-4
	movl	%eax,RR4_1023-4
	movl	%eax,RR4_1024-4
	movl	%eax,RR4_1025-4
	movl	%eax,RR4_1026-4
	movl	%eax,RR4_1027-4
	movl	%eax,RR4_1028-4
	movl	%eax,RR4_1029-4
	movl	%eax,RR4_1030-4
	movl	%eax,RR4_1031-4
	movl	%eax,RR4_1032-4
	movl	%eax,RR4_1033-4
	movl	%eax,RR4_1034-4
	incl	%eax
	movl	%eax,RR5_1000-4
	incl	%eax
	movl	%eax,RR6_1000-4
	movl	%eax,RR6_1001-4
	movl	%eax,RR6_1002-4
	movl	%eax,RR6_1003-4
	movl	%eax,RR6_1004-4
	movl	%eax,RR6_1005-4
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
