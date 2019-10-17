

FUNC(op_313b)

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
RR0_5000:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_375
	movswl	%di,%edi
L_5_375:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_376
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_377
	movl	%ebp,%ebx
L_5_377:
	testl	$64,%esi
	je	L_5_378
	movl	%ebp,%edi
L_5_378:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_379
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_379:
	cmpl	$48,%edx
	jne	L_5_382
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_382:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_385
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_385:
	cmpl	$3,16-16(%esp)
	jne	L_5_388
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_388:
	andl	$4,%esi
	jne	L_5_391
	addl	%edi,%ebx
L_5_391:
	cmpl	$0,16-16(%esp)
	je	L_5_392
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_392:
	testl	%esi,%esi
	je	L_5_395
	addl	%edi,%ebx
L_5_395:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_396
	.align	2,0x90
L_5_376:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_396:
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
	jl	JJ_5000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5000:
	ret

FUNC(op_3170)

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
RR0_5006:
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
	jne	L_5_494
	movswl	%di,%edi
L_5_494:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_495
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_496
	movl	%ebp,%ebx
L_5_496:
	testl	$64,%esi
	je	L_5_497
	movl	%ebp,%edi
L_5_497:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_498
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_498:
	cmpl	$48,%edx
	jne	L_5_501
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_501:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_504
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_504:
	cmpl	$3,16-16(%esp)
	jne	L_5_507
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_507:
	andl	$4,%esi
	jne	L_5_510
	addl	%edi,%ebx
L_5_510:
	cmpl	$0,16-16(%esp)
	je	L_5_511
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_511:
	testl	%esi,%esi
	je	L_5_514
	addl	%edi,%ebx
L_5_514:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_515
	.align	2,0x90
L_5_495:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_515:
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
	movl	28-16(%esp),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_5011:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	movl	16-16(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%eax
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5012:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5001:
	ret

FUNC(op_317b)

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
RR0_5013:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_577
	movswl	%di,%edi
L_5_577:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_578
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_579
	movl	%ebp,%ebx
L_5_579:
	testl	$64,%esi
	je	L_5_580
	movl	%ebp,%edi
L_5_580:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_581
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5014:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_581:
	cmpl	$48,%edx
	jne	L_5_584
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5015:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_584:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_587
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5016:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_587:
	cmpl	$3,16-16(%esp)
	jne	L_5_590
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5017:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_590:
	andl	$4,%esi
	jne	L_5_593
	addl	%edi,%ebx
L_5_593:
	cmpl	$0,16-16(%esp)
	je	L_5_594
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_594:
	testl	%esi,%esi
	je	L_5_597
	addl	%edi,%ebx
L_5_597:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_598
	.align	2,0x90
L_5_578:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_598:
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
	movl	28-16(%esp),%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_5018:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	movl	16-16(%esp),%ecx
	addl	GLOBL(regs)(,%edx,4),%eax
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5002:
	ret

FUNC(op_3180)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%edx
	andl	$7,%eax
	movw	GLOBL(regs)(,%edx,4),%dx
	movl	GLOBL(regs)+88,%ecx
	movw	%dx,30-16(%esp)
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_5020:
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
	jne	L_5_621
	movswl	%di,%edi
L_5_621:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_622
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_623
	movl	%ebp,%ebx
L_5_623:
	testl	$64,%esi
	je	L_5_624
	movl	%ebp,%edi
L_5_624:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_625
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5021:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_625:
	cmpl	$48,%edx
	jne	L_5_628
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5022:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_628:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_631
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5023:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_631:
	cmpl	$3,16-16(%esp)
	jne	L_5_634
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5024:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_634:
	andl	$4,%esi
	jne	L_5_637
	addl	%edi,%ebx
L_5_637:
	cmpl	$0,16-16(%esp)
	je	L_5_638
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_638:
	testl	%esi,%esi
	je	L_5_641
	addl	%edi,%ebx
L_5_641:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_642
	.align	2,0x90
L_5_622:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_5_642:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5003:
	ret

FUNC(op_3188)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	addl	$8,%eax
	andl	$7,%edx
	movw	GLOBL(regs)(,%eax,4),%ax
	movl	GLOBL(regs)+88,%ecx
	movw	%ax,30-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5026:
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
	jne	L_5_650
	movswl	%di,%edi
L_5_650:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_651
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_652
	movl	%ebp,%ebx
L_5_652:
	testl	$64,%esi
	je	L_5_653
	movl	%ebp,%edi
L_5_653:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_654
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5027:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_654:
	cmpl	$48,%edx
	jne	L_5_657
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5028:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_657:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_660
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5029:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_660:
	cmpl	$3,16-16(%esp)
	jne	L_5_663
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5030:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_663:
	andl	$4,%esi
	jne	L_5_666
	addl	%edi,%ebx
L_5_666:
	cmpl	$0,16-16(%esp)
	je	L_5_667
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_667:
	testl	%esi,%esi
	je	L_5_670
	addl	%edi,%ebx
L_5_670:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_671
	.align	2,0x90
L_5_651:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_671:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5031:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5004:
	ret

FUNC(op_3190)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	movl	%edx,%ecx
	andl	$7,%ecx
	addl	$8,%eax
	movl	%ecx,16-16(%esp)
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	GLOBL(regs)+88,%ecx
	movw	%ax,30-16(%esp)
	movl	%ecx,24-16(%esp)
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	addl	$2,%eax
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5032:
	rolw	$8,%si
	movl	(%ebx,%ecx,4),%edx
	movl	24-16(%esp),%ecx
	movl	%esi,%eax
	addl	$4,%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_681
	movswl	%di,%edi
L_5_681:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_682
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_683
	movl	%ebp,%ebx
L_5_683:
	testl	$64,%esi
	je	L_5_684
	movl	%ebp,%edi
L_5_684:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_685
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5033:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_685:
	cmpl	$48,%edx
	jne	L_5_688
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5034:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_688:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_691
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5035:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_691:
	cmpl	$3,16-16(%esp)
	jne	L_5_694
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5036:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_694:
	andl	$4,%esi
	jne	L_5_697
	addl	%edi,%ebx
L_5_697:
	cmpl	$0,16-16(%esp)
	je	L_5_698
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_698:
	testl	%esi,%esi
	je	L_5_701
	addl	%edi,%ebx
L_5_701:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_702
	.align	2,0x90
L_5_682:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_702:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5005:
	ret

FUNC(op_3198)

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
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$2,%edx
	movw	%ax,30-16(%esp)
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
RR0_5038:
	rolw	$8,%si
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_712
	movswl	%di,%edi
L_5_712:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_713
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_5_714
	movl	%ebp,16-16(%esp)
L_5_714:
	testl	$64,%esi
	je	L_5_715
	movl	%ebp,%edi
L_5_715:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_716
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5039:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_5_716:
	cmpl	$48,%edx
	jne	L_5_719
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5040:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_5_719:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_5_722
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5041:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_722:
	cmpl	$3,%ecx
	jne	L_5_725
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5042:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_725:
	andl	$4,%esi
	jne	L_5_728
	addl	%edi,16-16(%esp)
L_5_728:
	testl	%ecx,%ecx
	je	L_5_729
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_5_729:
	testl	%esi,%esi
	je	L_5_732
	addl	%edi,16-16(%esp)
L_5_732:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_5_733
	.align	2,0x90
L_5_713:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_733:
	movw	30-16(%esp),%bx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5006:
	ret

FUNC(op_31a0)

	subl	$16,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	movl	%eax,%esi
	addl	$-2,%ecx
	shrl	$9,%esi
	movl	%ecx,16-16(%esp)
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
	movl	16-16(%esp),%ecx
	movw	%ax,30-16(%esp)
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
RR0_5044:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_743
	movswl	%di,%edi
L_5_743:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_744
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_745
	movl	%ebp,%ebx
L_5_745:
	testl	$64,%esi
	je	L_5_746
	movl	%ebp,%edi
L_5_746:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_747
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5045:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_747:
	cmpl	$48,%edx
	jne	L_5_750
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5046:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_750:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_753
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5047:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_753:
	cmpl	$3,16-16(%esp)
	jne	L_5_756
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5048:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_756:
	andl	$4,%esi
	jne	L_5_759
	addl	%edi,%ebx
L_5_759:
	cmpl	$0,16-16(%esp)
	je	L_5_760
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_760:
	testl	%esi,%esi
	je	L_5_763
	addl	%edi,%ebx
L_5_763:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_764
	.align	2,0x90
L_5_744:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_764:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5007:
	ret

FUNC(op_31a8)

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
RR2_5000:
	rolw	$8,%ax
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,26-16(%esp)
	movl	28-16(%esp),%eax
	movl	16-16(%esp),%ecx
	addl	$4,%eax
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5050:
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
	jne	L_5_775
	movswl	%di,%edi
L_5_775:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_776
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_777
	movl	%ebp,%ebx
L_5_777:
	testl	$64,%esi
	je	L_5_778
	movl	%ebp,%edi
L_5_778:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_779
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5051:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_779:
	cmpl	$48,%edx
	jne	L_5_782
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5052:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_782:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_785
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5053:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_785:
	cmpl	$3,16-16(%esp)
	jne	L_5_788
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5054:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_788:
	andl	$4,%esi
	jne	L_5_791
	addl	%edi,%ebx
L_5_791:
	cmpl	$0,16-16(%esp)
	je	L_5_792
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_792:
	testl	%esi,%esi
	je	L_5_795
	addl	%edi,%ebx
L_5_795:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_796
	.align	2,0x90
L_5_776:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_796:
	movw	26-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	26-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5008:
	ret

FUNC(op_31b0)

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
RR0_5056:
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
	jne	L_5_804
	movswl	%di,%edi
L_5_804:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_805
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_806
	movl	%ebp,%ebx
L_5_806:
	testl	$64,%esi
	je	L_5_807
	movl	%ebp,%edi
L_5_807:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_808
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5057:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_808:
	cmpl	$48,%edx
	jne	L_5_811
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5058:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_811:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_814
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5059:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_814:
	cmpl	$3,16-16(%esp)
	jne	L_5_817
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5060:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_817:
	andl	$4,%esi
	jne	L_5_820
	addl	%edi,%ebx
L_5_820:
	cmpl	$0,16-16(%esp)
	je	L_5_821
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_821:
	testl	%esi,%esi
	je	L_5_824
	addl	%edi,%ebx
L_5_824:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_825
	.align	2,0x90
L_5_805:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_825:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,30-16(%esp)
	movl	40-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_5061:
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
	jne	L_5_831
	movswl	%di,%edi
L_5_831:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_832
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_833
	movl	%ebp,%ebx
L_5_833:
	testl	$64,%esi
	je	L_5_834
	movl	%ebp,%edi
L_5_834:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_835
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5062:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_835:
	cmpl	$48,%edx
	jne	L_5_838
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5063:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_838:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_841
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5064:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_841:
	cmpl	$3,16-16(%esp)
	jne	L_5_844
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5065:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_844:
	andl	$4,%esi
	jne	L_5_847
	addl	%edi,%ebx
L_5_847:
	cmpl	$0,16-16(%esp)
	je	L_5_848
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_848:
	testl	%esi,%esi
	je	L_5_851
	addl	%edi,%ebx
L_5_851:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_852
	.align	2,0x90
L_5_832:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_852:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5066:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5009:
	ret

FUNC(op_31b8)

	subl	$16,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5001:
	rolw	$8,%ax
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
	movw	%ax,26-16(%esp)
	addl	$8,%ecx
	movl	28-16(%esp),%eax
	movl	28-16(%esp),%ebx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5067:
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
	jne	L_5_863
	movswl	%di,%edi
L_5_863:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_864
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_5_865
	movl	%ebp,16-16(%esp)
L_5_865:
	testl	$64,%esi
	je	L_5_866
	movl	%ebp,%edi
L_5_866:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_867
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5068:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_5_867:
	cmpl	$48,%edx
	jne	L_5_870
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5069:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_5_870:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_5_873
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5070:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_873:
	cmpl	$3,%ecx
	jne	L_5_876
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5071:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_876:
	andl	$4,%esi
	jne	L_5_879
	addl	%edi,16-16(%esp)
L_5_879:
	testl	%ecx,%ecx
	je	L_5_880
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_5_880:
	testl	%esi,%esi
	je	L_5_883
	addl	%edi,16-16(%esp)
L_5_883:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_5_884
	.align	2,0x90
L_5_864:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_884:
	movw	26-16(%esp),%bx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5072:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5010:
	ret

FUNC(op_31b9)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebx
	movl	%eax,%ecx
	movl	%ebx,28-16(%esp)
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_5002:
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
	movw	%ax,26-16(%esp)
	addl	$8,%ecx
	movl	28-16(%esp),%eax
	movl	28-16(%esp),%ebx
	addl	$6,%eax
	addl	$8,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5073:
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
	jne	L_5_895
	movswl	%di,%edi
L_5_895:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_896
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_5_897
	movl	%ebp,16-16(%esp)
L_5_897:
	testl	$64,%esi
	je	L_5_898
	movl	%ebp,%edi
L_5_898:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_899
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5074:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$10,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_5_899:
	cmpl	$48,%edx
	jne	L_5_902
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5075:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_5_902:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_5_905
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5076:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_905:
	cmpl	$3,%ecx
	jne	L_5_908
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5077:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_908:
	andl	$4,%esi
	jne	L_5_911
	addl	%edi,16-16(%esp)
L_5_911:
	testl	%ecx,%ecx
	je	L_5_912
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_5_912:
	testl	%esi,%esi
	je	L_5_915
	addl	%edi,16-16(%esp)
L_5_915:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_5_916
	.align	2,0x90
L_5_896:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_916:
	movw	26-16(%esp),%bx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5011:
	ret

FUNC(op_31ba)

	subl	$16,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5003:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
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
	movw	%ax,26-16(%esp)
	addl	$8,%ecx
	movl	28-16(%esp),%eax
	movl	28-16(%esp),%ebx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5079:
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
	jne	L_5_928
	movswl	%di,%edi
L_5_928:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_929
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_5_930
	movl	%ebp,16-16(%esp)
L_5_930:
	testl	$64,%esi
	je	L_5_931
	movl	%ebp,%edi
L_5_931:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_932
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5080:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_5_932:
	cmpl	$48,%edx
	jne	L_5_935
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5081:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_5_935:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_5_938
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5082:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_938:
	cmpl	$3,%ecx
	jne	L_5_941
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5083:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_941:
	andl	$4,%esi
	jne	L_5_944
	addl	%edi,16-16(%esp)
L_5_944:
	testl	%ecx,%ecx
	je	L_5_945
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_5_945:
	testl	%esi,%esi
	je	L_5_948
	addl	%edi,16-16(%esp)
L_5_948:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_5_949
	.align	2,0x90
L_5_929:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_949:
	movw	26-16(%esp),%bx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5012:
	ret

FUNC(op_31bb)

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
RR0_5085:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,32-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_958
	movswl	%di,%edi
L_5_958:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_959
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_960
	movl	%ebp,%ebx
L_5_960:
	testl	$64,%esi
	je	L_5_961
	movl	%ebp,%edi
L_5_961:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_962
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5086:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_962:
	cmpl	$48,%edx
	jne	L_5_965
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5087:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_965:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_968
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5088:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_968:
	cmpl	$3,16-16(%esp)
	jne	L_5_971
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5089:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_971:
	andl	$4,%esi
	jne	L_5_974
	addl	%edi,%ebx
L_5_974:
	cmpl	$0,16-16(%esp)
	je	L_5_975
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_975:
	testl	%esi,%esi
	je	L_5_978
	addl	%edi,%ebx
L_5_978:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_979
	.align	2,0x90
L_5_959:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_979:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,30-16(%esp)
	movl	40-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_5090:
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
	jne	L_5_985
	movswl	%di,%edi
L_5_985:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_986
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_987
	movl	%ebp,%ebx
L_5_987:
	testl	$64,%esi
	je	L_5_988
	movl	%ebp,%edi
L_5_988:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_989
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5091:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_989:
	cmpl	$48,%edx
	jne	L_5_992
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5092:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_992:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_995
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5093:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_995:
	cmpl	$3,16-16(%esp)
	jne	L_5_998
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5094:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_998:
	andl	$4,%esi
	jne	L_5_1001
	addl	%edi,%ebx
L_5_1001:
	cmpl	$0,16-16(%esp)
	je	L_5_1002
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1002:
	testl	%esi,%esi
	je	L_5_1005
	addl	%edi,%ebx
L_5_1005:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_1006
	.align	2,0x90
L_5_986:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_1006:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5013:
	ret

FUNC(op_31bc)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	shrl	$9,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_5004:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	andl	$7,%edx
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_5096:
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
	jne	L_5_1015
	movswl	%di,%edi
L_5_1015:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1016
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1017
	movl	%ebp,%ebx
L_5_1017:
	testl	$64,%esi
	je	L_5_1018
	movl	%ebp,%edi
L_5_1018:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1019
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5097:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1019:
	cmpl	$48,%edx
	jne	L_5_1022
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5098:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1022:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1025
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5099:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1025:
	cmpl	$3,16-16(%esp)
	jne	L_5_1028
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5100:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1028:
	andl	$4,%esi
	jne	L_5_1031
	addl	%edi,%ebx
L_5_1031:
	cmpl	$0,16-16(%esp)
	je	L_5_1032
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1032:
	testl	%esi,%esi
	je	L_5_1035
	addl	%edi,%ebx
L_5_1035:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_1036
	.align	2,0x90
L_5_1016:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_1036:
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	30-16(%esp),%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5014:
	ret

FUNC(op_31f0)

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
RR0_5102:
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
	jne	L_5_1122
	movswl	%di,%edi
L_5_1122:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1123
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1124
	movl	%ebp,%ebx
L_5_1124:
	testl	$64,%esi
	je	L_5_1125
	movl	%ebp,%edi
L_5_1125:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1126
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5103:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1126:
	cmpl	$48,%edx
	jne	L_5_1129
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5104:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1129:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1132
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5105:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1132:
	cmpl	$3,16-16(%esp)
	jne	L_5_1135
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5106:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1135:
	andl	$4,%esi
	jne	L_5_1138
	addl	%edi,%ebx
L_5_1138:
	cmpl	$0,16-16(%esp)
	je	L_5_1139
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1139:
	testl	%esi,%esi
	je	L_5_1142
	addl	%edi,%ebx
L_5_1142:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_1143
	.align	2,0x90
L_5_1123:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_5_1143:
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
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_5107:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	cwtl
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5015:
	ret

FUNC(op_31fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_5109:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_1205
	movswl	%di,%edi
L_5_1205:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1206
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1207
	movl	%ebp,%ebx
L_5_1207:
	testl	$64,%esi
	je	L_5_1208
	movl	%ebp,%edi
L_5_1208:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1209
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5110:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1209:
	cmpl	$48,%edx
	jne	L_5_1212
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5111:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1212:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1215
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5112:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1215:
	cmpl	$3,16-16(%esp)
	jne	L_5_1218
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5113:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1218:
	andl	$4,%esi
	jne	L_5_1221
	addl	%edi,%ebx
L_5_1221:
	cmpl	$0,16-16(%esp)
	je	L_5_1222
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1222:
	testl	%esi,%esi
	je	L_5_1225
	addl	%edi,%ebx
L_5_1225:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_1226
	.align	2,0x90
L_5_1206:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_1226:
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
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_5114:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	cwtl
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	16-16(%esp),%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5016:
	ret

FUNC(op_33f0)

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
RR0_5116:
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
	jne	L_5_1327
	movswl	%di,%edi
L_5_1327:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1328
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1329
	movl	%ebp,%ebx
L_5_1329:
	testl	$64,%esi
	je	L_5_1330
	movl	%ebp,%edi
L_5_1330:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1331
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5117:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1331:
	cmpl	$48,%edx
	jne	L_5_1334
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5118:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1334:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1337
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5119:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1337:
	cmpl	$3,16-16(%esp)
	jne	L_5_1340
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5120:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1340:
	andl	$4,%esi
	jne	L_5_1343
	addl	%edi,%ebx
L_5_1343:
	cmpl	$0,16-16(%esp)
	je	L_5_1344
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1344:
	testl	%esi,%esi
	je	L_5_1347
	addl	%edi,%ebx
L_5_1347:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_1348
	.align	2,0x90
L_5_1328:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_5_1348:
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
	movl	GLOBL(regs)+88,%eax
	movl	16-16(%esp),%ecx
	movl	0x2164334A(%eax),%edx
RR0_5121:
	bswapl	%edx
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
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5017:
	ret

FUNC(op_33fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_5123:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_1410
	movswl	%di,%edi
L_5_1410:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1411
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1412
	movl	%ebp,%ebx
L_5_1412:
	testl	$64,%esi
	je	L_5_1413
	movl	%ebp,%edi
L_5_1413:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1414
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5124:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1414:
	cmpl	$48,%edx
	jne	L_5_1417
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5125:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1417:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1420
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5126:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1420:
	cmpl	$3,16-16(%esp)
	jne	L_5_1423
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5127:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1423:
	andl	$4,%esi
	jne	L_5_1426
	addl	%edi,%ebx
L_5_1426:
	cmpl	$0,16-16(%esp)
	je	L_5_1427
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1427:
	testl	%esi,%esi
	je	L_5_1430
	addl	%edi,%ebx
L_5_1430:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_1431
	.align	2,0x90
L_5_1411:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_1431:
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
	movl	GLOBL(regs)+88,%eax
	movl	16-16(%esp),%ecx
	movl	0x2164334A(%eax),%edx
RR0_5128:
	bswapl	%edx
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
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5018:
	ret

FUNC(op_4000)

	movl	%eax,%ebp
	andl	$7,%ebp
	movsbl	GLOBL(regs)(,%ebp,4),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1452
	decl	%ebx
L_5_1452:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	movl	%eax,%edi
	xorl	%esi,%esi
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1453
	testl	%edi,%edi
	je	L_5_1453
	incl	%eax
L_5_1453:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1458
	testl	%esi,%esi
	je	L_5_1457
L_5_1458:
	testl	%edi,%edi
	je	L_5_1456
	testl	%esi,%esi
	je	L_5_1457
	testl	%ecx,%ecx
	je	L_5_1456
L_5_1457:
	movl	$1,%edx
L_5_1456:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1459
	andb	$191,%cl
	movb	%cl,regflags
L_5_1459:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movb	%bl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5019:
	ret

FUNC(op_4010)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ebp
	movb	GLOBL(regs)+2(,%eax,4),%al
	movl	%ebp,%edx
	andl	$255,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(,%eax,4),%eax
	movsbl	(%edx,%eax),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1464
	decl	%ebx
L_5_1464:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	movl	%eax,%edi
	xorl	%esi,%esi
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1465
	testl	%edi,%edi
	je	L_5_1465
	incl	%eax
L_5_1465:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1470
	testl	%esi,%esi
	je	L_5_1469
L_5_1470:
	testl	%edi,%edi
	je	L_5_1468
	testl	%esi,%esi
	je	L_5_1469
	testl	%ecx,%ecx
	je	L_5_1468
L_5_1469:
	movl	$1,%edx
L_5_1468:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1471
	andb	$191,%cl
	movb	%cl,regflags
L_5_1471:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5020:
	ret

FUNC(op_4018)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%ebx
	leal	8(%esi),%edx
	xorl	%eax,%eax
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%esi,4),%esi
	movl	(%edx,%ebx),%edi
	movb	2(%edx,%ebx),%al
	movl	%edi,%ecx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ecx
	addl	%edi,%esi
	movb	(%ecx,%eax),%al
	movl	%esi,(%edx,%ebx)
	movsbl	%al,%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1477
	decl	%ebx
L_5_1477:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	movl	%eax,%ebp
	xorl	%esi,%esi
	shrl	$31,%ebp
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1478
	testl	%ebp,%ebp
	je	L_5_1478
	incl	%eax
L_5_1478:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1483
	testl	%esi,%esi
	je	L_5_1482
L_5_1483:
	testl	%ebp,%ebp
	je	L_5_1481
	testl	%esi,%esi
	je	L_5_1482
	testl	%ecx,%ecx
	je	L_5_1481
L_5_1482:
	movl	$1,%edx
L_5_1481:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1484
	andb	$191,%cl
	movb	%cl,regflags
L_5_1484:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,%eax
	shrl	$14,%eax
	movl	%edi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5021:
	ret

FUNC(op_4020)

	andl	$7,%eax
	leal	8(%eax),%edx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ebx),%edi
	subl	%eax,%edi
	movl	%edi,%eax
	shrl	$14,%eax
	movl	%edi,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ecx,%eax),%al
	movl	%edi,(%edx,%ebx)
	movsbl	%al,%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1490
	decl	%ebx
L_5_1490:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	movl	%eax,%ebp
	xorl	%esi,%esi
	shrl	$31,%ebp
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1491
	testl	%ebp,%ebp
	je	L_5_1491
	incl	%eax
L_5_1491:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1496
	testl	%esi,%esi
	je	L_5_1495
L_5_1496:
	testl	%ebp,%ebp
	je	L_5_1494
	testl	%esi,%esi
	je	L_5_1495
	testl	%ecx,%ecx
	je	L_5_1494
L_5_1495:
	movl	$1,%edx
L_5_1494:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1497
	andb	$191,%cl
	movb	%cl,regflags
L_5_1497:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,%eax
	shrl	$14,%eax
	movl	%edi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5022:
	ret

FUNC(op_4028)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5005:
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(regs)(,%edx,4),%ebp
	cwtl
	addl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1504
	decl	%ebx
L_5_1504:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1505
	cmpl	$0,16-16(%esp)
	je	L_5_1505
	incl	%eax
L_5_1505:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1510
	testl	%esi,%esi
	je	L_5_1509
L_5_1510:
	cmpl	$0,16-16(%esp)
	je	L_5_1508
	testl	%esi,%esi
	je	L_5_1509
	testl	%ecx,%ecx
	je	L_5_1508
L_5_1509:
	movl	$1,%edx
L_5_1508:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1511
	andb	$191,%cl
	movb	%cl,regflags
L_5_1511:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5023:
	ret

FUNC(op_4030)

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
RR0_5135:
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
	jne	L_5_1518
	movswl	%di,%edi
L_5_1518:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1519
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1520
	movl	%ebp,%ebx
L_5_1520:
	testl	$64,%esi
	je	L_5_1521
	movl	%ebp,%edi
L_5_1521:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1522
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5136:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1522:
	cmpl	$48,%edx
	jne	L_5_1525
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5137:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1525:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1528
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5138:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1528:
	cmpl	$3,16-16(%esp)
	jne	L_5_1531
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5139:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1531:
	andl	$4,%esi
	jne	L_5_1534
	addl	%edi,%ebx
L_5_1534:
	cmpl	$0,16-16(%esp)
	je	L_5_1535
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1535:
	testl	%esi,%esi
	je	L_5_1538
	addl	%edi,%ebx
L_5_1538:
	leal	(%ebp,%ebx),%edi
	jmp	L_5_1539
	.align	2,0x90
L_5_1519:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%eax,%edi
L_5_1539:
	movl	%edi,%eax
	shrl	$14,%eax
	movl	%edi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1542
	decl	%ebx
L_5_1542:
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	movsbl	%bl,%eax
	movl	%eax,%ebp
	xorl	%esi,%esi
	shrl	$31,%ebp
	movl	%esi,%eax
	cmpl	$0,16-16(%esp)
	je	L_5_1543
	testl	%ebp,%ebp
	je	L_5_1543
	incl	%eax
L_5_1543:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	cmpl	$0,16-16(%esp)
	je	L_5_1548
	testl	%esi,%esi
	je	L_5_1547
L_5_1548:
	testl	%ebp,%ebp
	je	L_5_1546
	testl	%esi,%esi
	je	L_5_1547
	cmpl	$0,16-16(%esp)
	je	L_5_1546
L_5_1547:
	movl	$1,%edx
L_5_1546:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	movl	%ecx,%esi
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1549
	andb	$191,%cl
	movb	%cl,regflags
L_5_1549:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,%eax
	shrl	$14,%eax
	movl	%edi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5024:
	ret

FUNC(op_4038)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5006:
	rolw	$8,%di
	movl	%edi,%eax
	movswl	%ax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1556
	decl	%ebx
L_5_1556:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1557
	cmpl	$0,16-16(%esp)
	je	L_5_1557
	incl	%eax
L_5_1557:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1562
	testl	%esi,%esi
	je	L_5_1561
L_5_1562:
	cmpl	$0,16-16(%esp)
	je	L_5_1560
	testl	%esi,%esi
	je	L_5_1561
	testl	%ecx,%ecx
	je	L_5_1560
L_5_1561:
	movl	$1,%edx
L_5_1560:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1563
	andb	$191,%cl
	movb	%cl,regflags
L_5_1563:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5025:
	ret

FUNC(op_4039)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebp
RR2_5007:
	bswapl	%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1570
	decl	%ebx
L_5_1570:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	movl	%eax,%edi
	xorl	%esi,%esi
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1571
	testl	%edi,%edi
	je	L_5_1571
	incl	%eax
L_5_1571:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1576
	testl	%esi,%esi
	je	L_5_1575
L_5_1576:
	testl	%edi,%edi
	je	L_5_1574
	testl	%esi,%esi
	je	L_5_1575
	testl	%ecx,%ecx
	je	L_5_1574
L_5_1575:
	movl	$1,%edx
L_5_1574:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_5_1577
	andb	$191,%cl
	movb	%cl,regflags
L_5_1577:
	movb	%bl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5026:
	ret

FUNC(op_4040)

	movl	%eax,%ebp
	andl	$7,%ebp
	movswl	GLOBL(regs)(,%ebp,4),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1582
	decl	%ebx
L_5_1582:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movswl	%bx,%eax
	movl	%eax,%edi
	xorl	%esi,%esi
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1583
	testl	%edi,%edi
	je	L_5_1583
	incl	%eax
L_5_1583:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1588
	testl	%esi,%esi
	je	L_5_1587
L_5_1588:
	testl	%edi,%edi
	je	L_5_1586
	testl	%esi,%esi
	je	L_5_1587
	testl	%ecx,%ecx
	je	L_5_1586
L_5_1587:
	movl	$1,%edx
L_5_1586:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%bx,%bx
	je	L_5_1589
	andb	$191,%cl
	movb	%cl,regflags
L_5_1589:
	movl	%ebx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movw	%bx,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5027:
	ret

FUNC(op_4050)

	subl	$4,%esp
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movl	GLOBL(regs)(,%eax,4),%ebp
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movl	%ebp,%eax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1595
	decl	%ebx
L_5_1595:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movswl	%bx,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1596
	cmpl	$0,16-16(%esp)
	je	L_5_1596
	incl	%eax
L_5_1596:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1601
	testl	%esi,%esi
	je	L_5_1600
L_5_1601:
	cmpl	$0,16-16(%esp)
	je	L_5_1599
	testl	%esi,%esi
	je	L_5_1600
	testl	%ecx,%ecx
	je	L_5_1599
L_5_1600:
	movl	$1,%edx
L_5_1599:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%bx,%bx
	je	L_5_1602
	andb	$191,%cl
	movb	%cl,regflags
L_5_1602:
	movl	%ebx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebx,%ecx
	movl	%ebp,%eax
	movl	%ebp,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5028:
	ret

FUNC(op_4058)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%edi
	xorl	%ecx,%ecx
	movl	%edi,%eax
	movb	2(%edx,%ebx),%cl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	leal	2(%edi),%esi
	movl	%eax,%ecx
	movl	%esi,(%edx,%ebx)
	negl	%ecx
	testb	$1,regflags+4
	je	L_5_1610
	decl	%ecx
L_5_1610:
	movl	%eax,%ebx
	shrl	$31,%ebx
	movswl	%cx,%eax
	movl	%eax,%ebp
	shrl	$31,%ebp
	xorl	%eax,%eax
	testl	%ebx,%ebx
	je	L_5_1611
	testl	%ebp,%ebp
	je	L_5_1611
	incl	%eax
L_5_1611:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ebx,%ebx
	je	L_5_1616
	testl	%edx,%edx
	je	L_5_1615
L_5_1616:
	testl	%ebp,%ebp
	je	L_5_1614
	xorl	%esi,%esi
	testl	%esi,%esi
	je	L_5_1615
	testl	%ebx,%ebx
	je	L_5_1614
L_5_1615:
	movl	$1,%edx
L_5_1614:
	movb	%dl,%al
	movb	regflags,%bl
	andb	$1,%al
	andb	$254,%bl
	orb	%al,%bl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%bl,regflags
	movb	%al,regflags+4
	testw	%cx,%cx
	je	L_5_1617
	andb	$191,%bl
	movb	%bl,regflags
L_5_1617:
	movl	%ecx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,%eax
	movl	%edi,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5029:
	ret

FUNC(op_4060)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	movl	(%ecx,%ebx),%edi
	addl	$-2,%edi
	movl	%edi,%edx
	movl	%edi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%edi,(%ecx,%ebx)
	cwtl
	movl	%eax,%ecx
	negl	%ecx
	testb	$1,regflags+4
	je	L_5_1625
	decl	%ecx
L_5_1625:
	movl	%eax,%ebx
	shrl	$31,%ebx
	movswl	%cx,%eax
	movl	%eax,%ebp
	shrl	$31,%ebp
	xorl	%eax,%eax
	testl	%ebx,%ebx
	je	L_5_1626
	testl	%ebp,%ebp
	je	L_5_1626
	incl	%eax
L_5_1626:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ebx,%ebx
	je	L_5_1631
	testl	%edx,%edx
	je	L_5_1630
L_5_1631:
	testl	%ebp,%ebp
	je	L_5_1629
	xorl	%esi,%esi
	testl	%esi,%esi
	je	L_5_1630
	testl	%ebx,%ebx
	je	L_5_1629
L_5_1630:
	movl	$1,%edx
L_5_1629:
	movb	%dl,%al
	movb	regflags,%bl
	andb	$1,%al
	andb	$254,%bl
	orb	%al,%bl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%bl,regflags
	movb	%al,regflags+4
	testw	%cx,%cx
	je	L_5_1632
	andb	$191,%bl
	movb	%bl,regflags
L_5_1632:
	movl	%ecx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,%eax
	movl	%edi,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5030:
	ret

FUNC(op_4068)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5008:
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(regs)(,%edx,4),%ebp
	cwtl
	addl	%eax,%ebp
	movl	%ebp,%edx
	movl	%ebp,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1641
	decl	%ebx
L_5_1641:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movswl	%bx,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1642
	cmpl	$0,16-16(%esp)
	je	L_5_1642
	incl	%eax
L_5_1642:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1647
	testl	%esi,%esi
	je	L_5_1646
L_5_1647:
	cmpl	$0,16-16(%esp)
	je	L_5_1645
	testl	%esi,%esi
	je	L_5_1646
	testl	%ecx,%ecx
	je	L_5_1645
L_5_1646:
	movl	$1,%edx
L_5_1645:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%bx,%bx
	je	L_5_1648
	andb	$191,%cl
	movb	%cl,regflags
L_5_1648:
	movl	%ebx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebx,%ecx
	movl	%ebp,%eax
	movl	%ebp,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5031:
	ret

FUNC(op_4070)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebx
	addl	$8,%eax
	movl	%ebx,%edx
	movl	%ebx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ebx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_5148:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%ebx,20-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%ebp,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_1656
	movswl	%di,%edi
L_5_1656:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1657
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_5_1658
	movl	%ebp,16-16(%esp)
L_5_1658:
	testl	$64,%esi
	je	L_5_1659
	movl	%ebp,%edi
L_5_1659:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1660
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5149:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_5_1660:
	cmpl	$48,%edx
	jne	L_5_1663
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5150:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_5_1663:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_5_1666
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5151:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1666:
	cmpl	$3,%ecx
	jne	L_5_1669
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5152:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1669:
	andl	$4,%esi
	jne	L_5_1672
	addl	%edi,16-16(%esp)
L_5_1672:
	testl	%ecx,%ecx
	je	L_5_1673
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_5_1673:
	testl	%esi,%esi
	je	L_5_1676
	addl	%edi,16-16(%esp)
L_5_1676:
	movl	16-16(%esp),%edi
	addl	%ebp,%edi
	jmp	L_5_1677
	.align	2,0x90
L_5_1657:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%ebp,%eax
	addl	%eax,%edi
L_5_1677:
	movl	%edi,%edx
	movl	%edi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%esi
	negl	%esi
	testb	$1,regflags+4
	je	L_5_1681
	decl	%esi
L_5_1681:
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	movswl	%si,%eax
	movl	%eax,%ebp
	xorl	%ecx,%ecx
	shrl	$31,%ebp
	movl	%ecx,%eax
	cmpl	$0,16-16(%esp)
	je	L_5_1682
	testl	%ebp,%ebp
	je	L_5_1682
	incl	%eax
L_5_1682:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	cmpl	$0,16-16(%esp)
	je	L_5_1687
	testl	%ecx,%ecx
	je	L_5_1686
L_5_1687:
	testl	%ebp,%ebp
	je	L_5_1685
	testl	%ecx,%ecx
	je	L_5_1686
	cmpl	$0,16-16(%esp)
	je	L_5_1685
L_5_1686:
	movl	$1,%edx
L_5_1685:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%si,%si
	je	L_5_1688
	andb	$191,%cl
	movb	%cl,regflags
L_5_1688:
	movl	%esi,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%esi,%ecx
	movl	%edi,%eax
	movl	%edi,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5032:
	ret

FUNC(op_4078)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5009:
	rolw	$8,%di
	movl	%edi,%eax
	movswl	%ax,%ebp
	movl	%ebp,%edx
	movl	%ebp,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1697
	decl	%ebx
L_5_1697:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movswl	%bx,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1698
	cmpl	$0,16-16(%esp)
	je	L_5_1698
	incl	%eax
L_5_1698:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1703
	testl	%esi,%esi
	je	L_5_1702
L_5_1703:
	cmpl	$0,16-16(%esp)
	je	L_5_1701
	testl	%esi,%esi
	je	L_5_1702
	testl	%ecx,%ecx
	je	L_5_1701
L_5_1702:
	movl	$1,%edx
L_5_1701:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%bx,%bx
	je	L_5_1704
	andb	$191,%cl
	movb	%cl,regflags
L_5_1704:
	movl	%ebx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebx,%ecx
	movl	%ebp,%eax
	movl	%ebp,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5033:
	ret

FUNC(op_4079)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebp
RR2_5010:
	bswapl	%ebp
	movl	%ebp,%edx
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1713
	decl	%ebx
L_5_1713:
	movl	%eax,%ecx
	shrl	$31,%ecx
	movswl	%bx,%eax
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%eax,16-16(%esp)
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1714
	cmpl	$0,16-16(%esp)
	je	L_5_1714
	incl	%eax
L_5_1714:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1719
	testl	%esi,%esi
	je	L_5_1718
L_5_1719:
	cmpl	$0,16-16(%esp)
	je	L_5_1717
	testl	%esi,%esi
	je	L_5_1718
	testl	%ecx,%ecx
	je	L_5_1717
L_5_1718:
	movl	$1,%edx
L_5_1717:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testw	%bx,%bx
	je	L_5_1720
	andb	$191,%cl
	movb	%cl,regflags
L_5_1720:
	movl	%ebx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebx,%ecx
	movl	%ebp,%eax
	movl	%ebp,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5034:
	ret

FUNC(op_4080)

	movl	%eax,%ebp
	andl	$7,%ebp
	movl	GLOBL(regs)(,%ebp,4),%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1726
	decl	%ebx
L_5_1726:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%edi
	shrl	$31,%ecx
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1727
	testl	%edi,%edi
	je	L_5_1727
	incl	%eax
L_5_1727:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1732
	testl	%esi,%esi
	je	L_5_1731
L_5_1732:
	testl	%edi,%edi
	je	L_5_1730
	testl	%esi,%esi
	je	L_5_1731
	testl	%ecx,%ecx
	je	L_5_1730
L_5_1731:
	movl	$1,%edx
L_5_1730:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1733
	andb	$191,%cl
	movb	%cl,regflags
L_5_1733:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%ebx,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5035:
	ret

FUNC(op_4090)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movl	GLOBL(regs)(,%eax,4),%ebp
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movl	%ebp,%eax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1739
	decl	%ebx
L_5_1739:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%edi
	shrl	$31,%ecx
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1740
	testl	%edi,%edi
	je	L_5_1740
	incl	%eax
L_5_1740:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1745
	testl	%esi,%esi
	je	L_5_1744
L_5_1745:
	testl	%edi,%edi
	je	L_5_1743
	testl	%esi,%esi
	je	L_5_1744
	testl	%ecx,%ecx
	je	L_5_1743
L_5_1744:
	movl	$1,%edx
L_5_1743:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1746
	andb	$191,%cl
	movb	%cl,regflags
L_5_1746:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%ebp,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5036:
	ret

FUNC(op_4098)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%edi
	xorl	%ecx,%ecx
	movl	%edi,%eax
	movb	2(%edx,%ebx),%cl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	leal	4(%edi),%esi
	movl	(%eax),%eax
	movl	%esi,(%edx,%ebx)
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1754
	decl	%ebx
L_5_1754:
	movl	%eax,%ecx
	movl	%ebx,%ebp
	shrl	$31,%ecx
	shrl	$31,%ebp
	xorl	%eax,%eax
	testl	%ecx,%ecx
	je	L_5_1755
	testl	%ebp,%ebp
	je	L_5_1755
	incl	%eax
L_5_1755:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1760
	testl	%edx,%edx
	je	L_5_1759
L_5_1760:
	testl	%ebp,%ebp
	je	L_5_1758
	xorl	%esi,%esi
	testl	%esi,%esi
	je	L_5_1759
	testl	%ecx,%ecx
	je	L_5_1758
L_5_1759:
	movl	$1,%edx
L_5_1758:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1761
	andb	$191,%cl
	movb	%cl,regflags
L_5_1761:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%edi,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%edi,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5037:
	ret

FUNC(op_40a0)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	movl	(%ecx,%ebx),%edi
	addl	$-4,%edi
	movl	%edi,%edx
	movl	%edi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	movl	%edi,(%ecx,%ebx)
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1769
	decl	%ebx
L_5_1769:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%ebp
	shrl	$31,%ecx
	shrl	$31,%ebp
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1770
	testl	%ebp,%ebp
	je	L_5_1770
	incl	%eax
L_5_1770:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1775
	testl	%esi,%esi
	je	L_5_1774
L_5_1775:
	testl	%ebp,%ebp
	je	L_5_1773
	testl	%esi,%esi
	je	L_5_1774
	testl	%ecx,%ecx
	je	L_5_1773
L_5_1774:
	movl	$1,%edx
L_5_1773:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1776
	andb	$191,%cl
	movb	%cl,regflags
L_5_1776:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%edi,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%edi,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5038:
	ret

FUNC(op_40a8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5011:
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(regs)(,%edx,4),%ebp
	cwtl
	addl	%eax,%ebp
	movl	%ebp,%edx
	movl	%ebp,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1785
	decl	%ebx
L_5_1785:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%edi
	shrl	$31,%ecx
	shrl	$31,%edi
	movl	%esi,%eax
	movl	%edi,16-16(%esp)
	testl	%ecx,%ecx
	je	L_5_1786
	testl	%edi,%edi
	je	L_5_1786
	incl	%eax
L_5_1786:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1791
	testl	%esi,%esi
	je	L_5_1790
L_5_1791:
	cmpl	$0,16-16(%esp)
	je	L_5_1789
	testl	%esi,%esi
	je	L_5_1790
	testl	%ecx,%ecx
	je	L_5_1789
L_5_1790:
	movl	$1,%edx
L_5_1789:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1792
	andb	$191,%cl
	movb	%cl,regflags
L_5_1792:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%ebp,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5039:
	ret

FUNC(op_40b0)

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
RR0_5161:
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
	jne	L_5_1800
	movswl	%di,%edi
L_5_1800:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1801
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1802
	movl	%ebp,%ebx
L_5_1802:
	testl	$64,%esi
	je	L_5_1803
	movl	%ebp,%edi
L_5_1803:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1804
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5162:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1804:
	cmpl	$48,%edx
	jne	L_5_1807
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5163:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1807:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1810
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5164:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1810:
	cmpl	$3,16-16(%esp)
	jne	L_5_1813
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5165:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1813:
	andl	$4,%esi
	jne	L_5_1816
	addl	%edi,%ebx
L_5_1816:
	cmpl	$0,16-16(%esp)
	je	L_5_1817
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1817:
	testl	%esi,%esi
	je	L_5_1820
	addl	%edi,%ebx
L_5_1820:
	leal	(%ebp,%ebx),%edi
	jmp	L_5_1821
	.align	2,0x90
L_5_1801:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%eax,%edi
L_5_1821:
	movl	%edi,%edx
	movl	%edi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1825
	decl	%ebx
L_5_1825:
	shrl	$31,%eax
	xorl	%esi,%esi
	movl	%ebx,%ebp
	movl	%eax,16-16(%esp)
	shrl	$31,%ebp
	movl	%esi,%eax
	cmpl	$0,16-16(%esp)
	je	L_5_1826
	testl	%ebp,%ebp
	je	L_5_1826
	incl	%eax
L_5_1826:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	cmpl	$0,16-16(%esp)
	je	L_5_1831
	testl	%esi,%esi
	je	L_5_1830
L_5_1831:
	testl	%ebp,%ebp
	je	L_5_1829
	testl	%esi,%esi
	je	L_5_1830
	cmpl	$0,16-16(%esp)
	je	L_5_1829
L_5_1830:
	movl	$1,%edx
L_5_1829:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	movl	%ecx,%esi
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1832
	andb	$191,%cl
	movb	%cl,regflags
L_5_1832:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%edi,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%edi,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5040:
	ret

FUNC(op_40b8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5012:
	rolw	$8,%di
	movl	%edi,%eax
	movswl	%ax,%ebp
	movl	%ebp,%edx
	movl	%ebp,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1841
	decl	%ebx
L_5_1841:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%edi
	shrl	$31,%ecx
	shrl	$31,%edi
	movl	%esi,%eax
	movl	%edi,16-16(%esp)
	testl	%ecx,%ecx
	je	L_5_1842
	testl	%edi,%edi
	je	L_5_1842
	incl	%eax
L_5_1842:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1847
	testl	%esi,%esi
	je	L_5_1846
L_5_1847:
	cmpl	$0,16-16(%esp)
	je	L_5_1845
	testl	%esi,%esi
	je	L_5_1846
	testl	%ecx,%ecx
	je	L_5_1845
L_5_1846:
	movl	$1,%edx
L_5_1845:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1848
	andb	$191,%cl
	movb	%cl,regflags
L_5_1848:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%ebp,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5041:
	ret

FUNC(op_40b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebp
RR2_5013:
	bswapl	%ebp
	movl	%ebp,%edx
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,%ebx
	negl	%ebx
	testb	$1,regflags+4
	je	L_5_1857
	decl	%ebx
L_5_1857:
	movl	%eax,%ecx
	xorl	%esi,%esi
	movl	%ebx,%edi
	shrl	$31,%ecx
	shrl	$31,%edi
	movl	%esi,%eax
	testl	%ecx,%ecx
	je	L_5_1858
	testl	%edi,%edi
	je	L_5_1858
	incl	%eax
L_5_1858:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%ecx,%ecx
	je	L_5_1863
	testl	%esi,%esi
	je	L_5_1862
L_5_1863:
	testl	%edi,%edi
	je	L_5_1861
	testl	%esi,%esi
	je	L_5_1862
	testl	%ecx,%ecx
	je	L_5_1861
L_5_1862:
	movl	$1,%edx
L_5_1861:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testl	%ebx,%ebx
	je	L_5_1864
	andb	$191,%cl
	movb	%cl,regflags
L_5_1864:
	movl	%ebx,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movl	%ebp,%edx
	movb	%al,regflags
	shrl	$14,%edx
	movl	%ebp,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5042:
	ret

FUNC(op_40f0)

	subl	$12,%esp
	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1918
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1919
	.align	2,0x90
L_5_1918:
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_5169:
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
	jne	L_5_1922
	movswl	%di,%edi
L_5_1922:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_1923
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_1924
	movl	%ebp,%ebx
L_5_1924:
	testl	$64,%esi
	je	L_5_1925
	movl	%ebp,%edi
L_5_1925:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_1926
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5170:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_1926:
	cmpl	$48,%edx
	jne	L_5_1929
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5171:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_1929:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_1932
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5172:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1932:
	cmpl	$3,16-16(%esp)
	jne	L_5_1935
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5173:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_1935:
	andl	$4,%esi
	jne	L_5_1938
	addl	%edi,%ebx
L_5_1938:
	cmpl	$0,16-16(%esp)
	je	L_5_1939
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_1939:
	testl	%esi,%esi
	je	L_5_1942
	addl	%edi,%ebx
L_5_1942:
	addl	%ebp,%ebx
	jmp	L_5_1943
	.align	2,0x90
L_5_1923:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ebx
L_5_1943:
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	movl	%ebx,%edx
	xorl	%ecx,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
L_5_1919:
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5043:
	ret

FUNC(op_4130)

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
RR0_5175:
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
	jne	L_5_2053
	movswl	%di,%edi
L_5_2053:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2054
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2055
	movl	%ebp,%ebx
L_5_2055:
	testl	$64,%esi
	je	L_5_2056
	movl	%ebp,%edi
L_5_2056:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2057
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5176:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2057:
	cmpl	$48,%edx
	jne	L_5_2060
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5177:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2060:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2063
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5178:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2063:
	cmpl	$3,16-16(%esp)
	jne	L_5_2066
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5179:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2066:
	andl	$4,%esi
	jne	L_5_2069
	addl	%edi,%ebx
L_5_2069:
	cmpl	$0,16-16(%esp)
	je	L_5_2070
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2070:
	testl	%esi,%esi
	je	L_5_2073
	addl	%edi,%ebx
L_5_2073:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_2074
	.align	2,0x90
L_5_2054:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_2074:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%ecx
	movl	(%eax),%edx
	bswapl	%edx
	movl	GLOBL(regs)(,%ecx,4),%eax
	testl	%eax,%eax
	jge	L_5_2078
	movl	24-16(%esp),%ecx
	orb	$128,regflags
	jmp	L_5_2082
	.align	2,0x90
L_5_2078:
	cmpl	%edx,%eax
	jle	L_5_2079
	movl	24-16(%esp),%ecx
	andb	$127,regflags
L_5_2082:
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_5_2079:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5044:
	ret

FUNC(op_413b)

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
RR0_5181:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_2144
	movswl	%di,%edi
L_5_2144:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2145
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2146
	movl	%ebp,%ebx
L_5_2146:
	testl	$64,%esi
	je	L_5_2147
	movl	%ebp,%edi
L_5_2147:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2148
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5182:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2148:
	cmpl	$48,%edx
	jne	L_5_2151
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5183:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2151:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2154
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5184:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2154:
	cmpl	$3,16-16(%esp)
	jne	L_5_2157
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5185:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2157:
	andl	$4,%esi
	jne	L_5_2160
	addl	%edi,%ebx
L_5_2160:
	cmpl	$0,16-16(%esp)
	je	L_5_2161
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2161:
	testl	%esi,%esi
	je	L_5_2164
	addl	%edi,%ebx
L_5_2164:
	leal	(%ebp,%ebx),%eax
	jmp	L_5_2165
	.align	2,0x90
L_5_2145:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_5_2165:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%ecx
	movl	(%eax),%edx
	bswapl	%edx
	movl	GLOBL(regs)(,%ecx,4),%eax
	testl	%eax,%eax
	jge	L_5_2169
	movl	24-16(%esp),%ecx
	orb	$128,regflags
	jmp	L_5_2173
	.align	2,0x90
L_5_2169:
	cmpl	%edx,%eax
	jle	L_5_2170
	movl	24-16(%esp),%ecx
	andb	$127,regflags
L_5_2173:
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_5_2170:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5045:
	ret

FUNC(op_41b0)

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
RR0_5187:
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
	jne	L_5_2270
	movswl	%di,%edi
L_5_2270:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2271
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2272
	movl	%ebp,%ebx
L_5_2272:
	testl	$64,%esi
	je	L_5_2273
	movl	%ebp,%edi
L_5_2273:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2274
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5188:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2274:
	cmpl	$48,%edx
	jne	L_5_2277
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5189:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2277:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2280
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5190:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2280:
	cmpl	$3,16-16(%esp)
	jne	L_5_2283
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5191:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2283:
	andl	$4,%esi
	jne	L_5_2286
	addl	%edi,%ebx
L_5_2286:
	cmpl	$0,16-16(%esp)
	je	L_5_2287
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2287:
	testl	%esi,%esi
	je	L_5_2290
	addl	%edi,%ebx
L_5_2290:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_2291
	.align	2,0x90
L_5_2271:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_2291:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	28-16(%esp),%ecx
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,%edx
	movw	GLOBL(regs)(,%ecx,4),%ax
	testw	%ax,%ax
	jge	L_5_2295
	movl	24-16(%esp),%ecx
	orb	$128,regflags
	jmp	L_5_2299
	.align	2,0x90
L_5_2295:
	cmpw	%dx,%ax
	jle	L_5_2296
	movl	24-16(%esp),%ecx
	andb	$127,regflags
L_5_2299:
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_5_2296:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5046:
	ret

FUNC(op_41bb)

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
RR0_5193:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_2361
	movswl	%di,%edi
L_5_2361:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2362
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2363
	movl	%ebp,%ebx
L_5_2363:
	testl	$64,%esi
	je	L_5_2364
	movl	%ebp,%edi
L_5_2364:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2365
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5194:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2365:
	cmpl	$48,%edx
	jne	L_5_2368
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5195:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2368:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2371
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5196:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2371:
	cmpl	$3,16-16(%esp)
	jne	L_5_2374
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5197:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2374:
	andl	$4,%esi
	jne	L_5_2377
	addl	%edi,%ebx
L_5_2377:
	cmpl	$0,16-16(%esp)
	je	L_5_2378
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2378:
	testl	%esi,%esi
	je	L_5_2381
	addl	%edi,%ebx
L_5_2381:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_2382
	.align	2,0x90
L_5_2362:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_2382:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	28-16(%esp),%ecx
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,%edx
	movw	GLOBL(regs)(,%ecx,4),%ax
	testw	%ax,%ax
	jge	L_5_2386
	movl	24-16(%esp),%ecx
	orb	$128,regflags
	jmp	L_5_2390
	.align	2,0x90
L_5_2386:
	cmpw	%dx,%ax
	jle	L_5_2387
	movl	24-16(%esp),%ecx
	andb	$127,regflags
L_5_2390:
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_5_2387:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5047:
	ret

FUNC(op_41f0)

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
RR0_5199:
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
	jne	L_5_2418
	movswl	%di,%edi
L_5_2418:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2419
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2420
	movl	%ebp,%ebx
L_5_2420:
	testl	$64,%esi
	je	L_5_2421
	movl	%ebp,%edi
L_5_2421:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2422
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5200:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2422:
	cmpl	$48,%edx
	jne	L_5_2425
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5201:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2425:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2428
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5202:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2428:
	cmpl	$3,16-16(%esp)
	jne	L_5_2431
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5203:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2431:
	andl	$4,%esi
	jne	L_5_2434
	addl	%edi,%ebx
L_5_2434:
	cmpl	$0,16-16(%esp)
	je	L_5_2435
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2435:
	testl	%esi,%esi
	je	L_5_2438
	addl	%edi,%ebx
L_5_2438:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_2439
	.align	2,0x90
L_5_2419:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_2439:
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5048:
	ret

FUNC(op_41fb)

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
RR0_5205:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_5_2466
	movswl	%di,%edi
L_5_2466:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_5_2467
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_5_2468
	movl	%ebp,%ebx
L_5_2468:
	testl	$64,%esi
	je	L_5_2469
	movl	%ebp,%edi
L_5_2469:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_5_2470
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_5206:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_5_2470:
	cmpl	$48,%edx
	jne	L_5_2473
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5207:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_5_2473:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_5_2476
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_5208:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2476:
	cmpl	$3,16-16(%esp)
	jne	L_5_2479
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_5209:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_5_2479:
	andl	$4,%esi
	jne	L_5_2482
	addl	%edi,%ebx
L_5_2482:
	cmpl	$0,16-16(%esp)
	je	L_5_2483
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_5_2483:
	testl	%esi,%esi
	je	L_5_2486
	addl	%edi,%ebx
L_5_2486:
	leal	(%ebp,%ebx),%edx
	jmp	L_5_2487
	.align	2,0x90
L_5_2467:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_5_2487:
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5210:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5049:
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


FUNC(op_313c)

	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%esi,%esi
	movw	0x2164334A+2(%edx),%si
RR2_5014:
	rolw	$8,%si
	addl	$8,%eax
	movl	%esi,%edx
	sall	$2,%eax
	movl	%edx,%ebx
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
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5211:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5050:
	ret

FUNC(op_3140)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	movw	(%ecx,%eax,4),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_5015:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
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
	jl	JJ_5051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5212:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5051:
	ret

FUNC(op_3148)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%eax
	shrl	$9,%edx
	addl	$8,%eax
	andl	$7,%edx
	movw	(%ecx,%eax,4),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_5016:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
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
	jl	JJ_5052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5213:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5052:
	ret

FUNC(op_3150)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%ecx
	pushl	%ebx
	andl	$7,%eax
	shrl	$9,%ecx
	addl	$8,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	andl	$7,%ecx
	movl	%eax,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5017:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%ecx
	cwtl
	addl	(%ebx,%ecx,4),%eax
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
	jl	JJ_5053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5214:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5053:
	ret

FUNC(op_3158)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	movl	%eax,%esi
	addl	$8,%ecx
	shrl	$9,%esi
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	GLOBL(regs)(%ecx),%edx
	andl	$7,%esi
	movl	%edx,%eax
	movb	GLOBL(regs)+2(%ecx),%bl
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5018:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%esi
	cwtl
	addl	GLOBL(regs)(,%esi,4),%eax
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
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5215:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5054:
	ret

FUNC(op_3160)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	sall	$2,%ebx
	movl	GLOBL(regs)(%ebx),%ecx
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
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%ebx)
	movl	%eax,%ebp
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5019:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%esi
	cwtl
	addl	GLOBL(regs)(,%esi,4),%eax
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5216:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5055:
	ret

FUNC(op_3168)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$9,%ecx
	addl	$8,%edx
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_5020:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%edx,4),%eax
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
	addl	$8,%ecx
	movw	%ax,14-12(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+4(%esi),%ax
RR4_5000:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%ecx,4),%eax
	movw	14-12(%esp),%bx
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
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5217:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5056:
	ret

FUNC(op_3178)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5021:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%ecx
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_5001:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5218:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5057:
	ret

FUNC(op_3179)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_5022:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%ecx
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+6(%ebx),%ax
RR6_5000:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5219:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5058:
	ret

FUNC(op_317a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5023:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%ecx
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_5002:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5220:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5059:
	ret

FUNC(op_317c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_5024:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_5003:
	rolw	$8,%ax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5221:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5060:
	ret

FUNC(op_31c0)

	andl	$7,%eax
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5025:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5222:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5061:
	ret

FUNC(op_31c8)

	andl	$7,%eax
	addl	$8,%eax
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5026:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5223:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5062:
	ret

FUNC(op_31d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5027:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5224:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5063:
	ret

FUNC(op_31d8)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	sall	$2,%edx
	movl	(%edx,%esi),%ecx
	xorl	%ebx,%ebx
	movl	%ecx,%eax
	movb	2(%edx,%esi),%bl
	andl	$65535,%eax
	addl	$2,%ecx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,(%edx,%esi)
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_5028:
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
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
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5225:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5064:
	ret

FUNC(op_31e0)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%ebx
	addl	$-2,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)(%ecx)
	movl	%eax,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_5029:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	testw	%di,%di
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	xorl	%ecx,%ecx
	andl	$1020,%edx
	movw	%di,%cx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5226:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5065:
	ret

FUNC(op_31e8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5030:
	rolw	$8,%ax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_5004:
	rolw	$8,%ax
	cwtl
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5227:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5066:
	ret

FUNC(op_31f8)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5031:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_5005:
	rolw	$8,%ax
	cwtl
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5228:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5067:
	ret

FUNC(op_31f9)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+2(%ebx),%eax
RR2_5032:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+6(%ebx),%ax
RR6_5001:
	rolw	$8,%ax
	cwtl
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5229:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5068:
	ret

FUNC(op_31fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_5033:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_5006:
	rolw	$8,%ax
	cwtl
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5230:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5069:
	ret

FUNC(op_31fc)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_5034:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_5007:
	rolw	$8,%ax
	cwtl
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5231:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5070:
	ret

FUNC(op_33c0)

	andl	$7,%eax
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_5035:
	bswapl	%edx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5232:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5071:
	ret

FUNC(op_33c8)

	andl	$7,%eax
	addl	$8,%eax
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_5036:
	bswapl	%edx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5233:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5072:
	ret

FUNC(op_33d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_5037:
	bswapl	%edx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5234:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5073:
	ret

FUNC(op_33d8)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	sall	$2,%edx
	movl	(%edx,%esi),%ecx
	xorl	%ebx,%ebx
	movl	%ecx,%eax
	movb	2(%edx,%esi),%bl
	andl	$65535,%eax
	addl	$2,%ecx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,(%edx,%esi)
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_5038:
	bswapl	%edx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5235:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5074:
	ret

FUNC(op_33e0)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%ebx
	addl	$-2,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)(%ecx)
	movl	%eax,%edi
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_5039:
	bswapl	%edx
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	xorl	%ecx,%ecx
	andl	$1020,%eax
	movw	%di,%cx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5236:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5075:
	ret

FUNC(op_33e8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5040:
	rolw	$8,%ax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	0x2164334A+4(%ebx),%edx
RR4_5008:
	bswapl	%edx
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5237:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5076:
	ret

FUNC(op_33f8)

	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5041:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	0x2164334A+4(%ebx),%edx
RR4_5009:
	bswapl	%edx
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5238:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5077:
	ret

FUNC(op_33f9)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+2(%ebx),%eax
RR2_5042:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	0x2164334A+6(%ebx),%edx
RR6_5002:
	bswapl	%edx
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
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5239:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5078:
	ret

FUNC(op_33fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_5043:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	0x2164334A+4(%ecx),%edx
RR4_5010:
	bswapl	%edx
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5240:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5079:
	ret

FUNC(op_33fc)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_5044:
	rolw	$8,%ax
	movl	%eax,%ecx
	movl	0x2164334A+4(%edx),%edx
RR4_5011:
	bswapl	%edx
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
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5241:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5080:
	ret

FUNC(op_40c0)

	movl	%eax,%ebx
	andl	$7,%ebx
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1870
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1871
	.align	2,0x90
L_5_1870:
	call	GLOBL(MakeSR)
	xorl	%eax,%eax
	movw	GLOBL(regs)+76,%ax
	movw	%ax,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
L_5_1871:
	popl	%eax
	decl	%eax
	jl	JJ_5081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5242:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5081:
	ret

FUNC(op_40d0)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1876
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1877
	.align	2,0x90
L_5_1876:
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
L_5_1877:
	popl	%eax
	decl	%eax
	jl	JJ_5082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5243:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5082:
	ret

FUNC(op_40d8)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1886
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1887
	.align	2,0x90
L_5_1886:
	addl	$8,%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	(%eax,%edx),%ebx
	leal	2(%ebx),%ecx
	movl	%ecx,(%eax,%edx)
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
L_5_1887:
	popl	%eax
	decl	%eax
	jl	JJ_5083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5244:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5083:
	ret

FUNC(op_40e0)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1896
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1897
	.align	2,0x90
L_5_1896:
	addl	$8,%eax
	movl	$GLOBL(regs),%edx
	sall	$2,%eax
	movl	(%eax,%edx),%ebx
	addl	$-2,%ebx
	movl	%ebx,(%eax,%edx)
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
L_5_1897:
	popl	%eax
	decl	%eax
	jl	JJ_5084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5245:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5084:
	ret

FUNC(op_40e8)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1906
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1907
	.align	2,0x90
L_5_1906:
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5045:
	rolw	$8,%bx
	leal	8(%edx),%eax
	movswl	%bx,%ebx
	addl	GLOBL(regs)(,%eax,4),%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
L_5_1907:
	popl	%eax
	decl	%eax
	jl	JJ_5085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5246:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5085:
	ret

FUNC(op_40f8)

	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1948
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1949
	.align	2,0x90
L_5_1948:
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5046:
	rolw	$8,%bx
	movswl	%bx,%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
L_5_1949:
	popl	%eax
	decl	%eax
	jl	JJ_5086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5247:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5086:
	ret

FUNC(op_40f9)

	cmpb	$0,GLOBL(regs)+80
	jne	L_5_1960
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1961
	.align	2,0x90
L_5_1960:
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_5047:
	bswapl	%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movw	GLOBL(regs)+76,%dx
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$6,GLOBL(regs)+88
L_5_1961:
	popl	%eax
	decl	%eax
	jl	JJ_5087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5248:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5087:
	ret

FUNC(op_4100)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	movl	GLOBL(regs)+88,%ebx
	movl	(%ecx,%eax,4),%esi
	movl	(%edx,%ecx),%eax
	movl	%ebx,%edi
	testl	%eax,%eax
	jge	L_5_1973
	orb	$128,regflags
	jmp	L_5_2506
	.align	2,0x90
L_5_1973:
	cmpl	%esi,%eax
	jle	L_5_1975
	andb	$127,regflags
L_5_2506:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1974
	.align	2,0x90
L_5_1975:
	addl	$2,%edi
	movl	%edi,GLOBL(regs)+88
L_5_1974:
	popl	%eax
	decl	%eax
	jl	JJ_5088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5249:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5088:
	ret

FUNC(op_4110)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	addl	$8,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	movl	GLOBL(regs)+88,%esi
	andl	$65535,%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	%esi,%edi
	movl	(%eax),%edx
	bswapl	%edx
	movl	(%ecx,%ebx),%eax
	testl	%eax,%eax
	jge	L_5_1987
	orb	$128,regflags
	jmp	L_5_2507
	.align	2,0x90
L_5_1987:
	cmpl	%edx,%eax
	jle	L_5_1989
	andb	$127,regflags
L_5_2507:
	pushl	%esi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_1988
	.align	2,0x90
L_5_1989:
	addl	$2,%edi
	movl	%edi,GLOBL(regs)+88
L_5_1988:
	popl	%eax
	decl	%eax
	jl	JJ_5089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5250:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5089:
	ret

FUNC(op_4118)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%ebp
	movl	$GLOBL(regs),%ebx
	movl	%ebp,20-16(%esp)
	movl	%eax,%edi
	movl	(%ecx,%ebx),%edx
	shrl	$7,%edi
	movl	%edx,%eax
	movzbl	2(%ecx,%ebx),%esi
	andl	$65535,%eax
	addl	GLOBL(R24)(,%esi,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	andl	$28,%edi
	movl	%edx,(%ecx,%ebx)
	movl	(%edi,%ebx),%eax
	testl	%eax,%eax
	jge	L_5_2003
	orb	$128,regflags
	pushl	%ebp
	jmp	L_5_2508
	.align	2,0x90
L_5_2003:
	cmpl	%eax,16-16(%esp)
	jge	L_5_2005
	movl	20-16(%esp),%esi
	andb	$127,regflags
	pushl	%esi
L_5_2508:
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2004
	.align	2,0x90
L_5_2005:
	addl	$2,GLOBL(regs)+88
L_5_2004:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5251:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5090:
	ret

FUNC(op_4120)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%ebx
	movl	%ebp,16-16(%esp)
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%eax,%edi
	addl	$-4,%ecx
	shrl	$7,%edi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$28,%edi
	movl	(%eax),%edx
	movl	%ecx,(%ebx,%esi)
	bswapl	%edx
	movl	(%edi,%esi),%eax
	testl	%eax,%eax
	jge	L_5_2019
	orb	$128,regflags
	pushl	%ebp
	jmp	L_5_2509
	.align	2,0x90
L_5_2019:
	cmpl	%edx,%eax
	jle	L_5_2021
	movl	16-16(%esp),%ecx
	andb	$127,regflags
	pushl	%ecx
L_5_2509:
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2020
	.align	2,0x90
L_5_2021:
	addl	$2,GLOBL(regs)+88
L_5_2020:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5252:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5091:
	ret

FUNC(op_4128)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$7,%ecx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_5048:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	%esi,%edi
	movl	(%eax),%edx
	bswapl	%edx
	movl	(%ecx,%ebx),%eax
	testl	%eax,%eax
	jge	L_5_2036
	orb	$128,regflags
	jmp	L_5_2510
	.align	2,0x90
L_5_2036:
	cmpl	%edx,%eax
	jle	L_5_2038
	andb	$127,regflags
L_5_2510:
	pushl	%esi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2037
	.align	2,0x90
L_5_2038:
	addl	$4,%edi
	movl	%edi,GLOBL(regs)+88
L_5_2037:
	popl	%eax
	decl	%eax
	jl	JJ_5092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5253:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5092:
	ret

FUNC(op_4138)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_5049:
	rolw	$8,%dx
	movswl	%dx,%edx
	shrl	$7,%eax
	movl	%edx,%ecx
	andl	$28,%eax
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movl	GLOBL(regs)(%eax),%eax
	addl	GLOBL(R24)(%ecx),%edx
	movl	%ebx,%esi
	movl	(%edx),%edx
	bswapl	%edx
	testl	%eax,%eax
	jge	L_5_2088
	orb	$128,regflags
	jmp	L_5_2511
	.align	2,0x90
L_5_2088:
	cmpl	%edx,%eax
	jle	L_5_2090
	andb	$127,regflags
L_5_2511:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2089
	.align	2,0x90
L_5_2090:
	addl	$4,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2089:
	popl	%eax
	decl	%eax
	jl	JJ_5093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5254:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5093:
	ret

FUNC(op_4139)

	movl	GLOBL(regs)+88,%ebx
	shrl	$7,%eax
	movl	0x2164334A+2(%ebx),%edx
RR2_5050:
	bswapl	%edx
	movl	%edx,%ecx
	andl	$28,%eax
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movl	GLOBL(regs)(%eax),%eax
	addl	GLOBL(R24)(%ecx),%edx
	movl	%ebx,%esi
	movl	(%edx),%edx
	bswapl	%edx
	testl	%eax,%eax
	jge	L_5_2106
	orb	$128,regflags
	jmp	L_5_2512
	.align	2,0x90
L_5_2106:
	cmpl	%edx,%eax
	jle	L_5_2108
	andb	$127,regflags
L_5_2512:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2107
	.align	2,0x90
L_5_2108:
	addl	$6,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2107:
	popl	%eax
	decl	%eax
	jl	JJ_5094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5255:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5094:
	ret

FUNC(op_413a)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5051:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	%ebx,%esi
	movl	(%eax),%edx
	bswapl	%edx
	movl	GLOBL(regs)(%ecx),%eax
	testl	%eax,%eax
	jge	L_5_2125
	orb	$128,regflags
	jmp	L_5_2513
	.align	2,0x90
L_5_2125:
	cmpl	%edx,%eax
	jle	L_5_2127
	andb	$127,regflags
L_5_2513:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2126
	.align	2,0x90
L_5_2127:
	addl	$4,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2126:
	popl	%eax
	decl	%eax
	jl	JJ_5095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5256:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5095:
	ret

FUNC(op_413c)

	shrl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$28,%eax
	movl	%edx,%ebx
	movl	0x2164334A+2(%edx),%ecx
RR2_5052:
	bswapl	%ecx
	movl	GLOBL(regs)(%eax),%eax
	testl	%eax,%eax
	jge	L_5_2177
	orb	$128,regflags
	jmp	L_5_2514
	.align	2,0x90
L_5_2177:
	cmpl	%ecx,%eax
	jle	L_5_2179
	andb	$127,regflags
L_5_2514:
	pushl	%edx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2178
	.align	2,0x90
L_5_2179:
	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
L_5_2178:
	popl	%eax
	decl	%eax
	jl	JJ_5096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5257:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5096:
	ret

FUNC(op_4180)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	movl	GLOBL(regs)+88,%ebx
	movw	(%ecx,%eax,4),%si
	movw	(%edx,%ecx),%ax
	movl	%ebx,%edi
	testw	%ax,%ax
	jge	L_5_2190
	orb	$128,regflags
	jmp	L_5_2515
	.align	2,0x90
L_5_2190:
	cmpw	%si,%ax
	jle	L_5_2192
	andb	$127,regflags
L_5_2515:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2191
	.align	2,0x90
L_5_2192:
	addl	$2,%edi
	movl	%edi,GLOBL(regs)+88
L_5_2191:
	popl	%eax
	decl	%eax
	jl	JJ_5097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5258:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5097:
	ret

FUNC(op_4190)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	addl	$8,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	andl	$28,%ecx
	movw	(%ebx,%eax,4),%ax
	movl	GLOBL(regs)+88,%esi
	andl	$65535,%eax
	movl	%esi,%ebp
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%ecx,%ebx),%dx
	testw	%dx,%dx
	jge	L_5_2204
	orb	$128,regflags
	jmp	L_5_2516
	.align	2,0x90
L_5_2204:
	cmpw	%ax,%dx
	jle	L_5_2206
	andb	$127,regflags
L_5_2516:
	pushl	%esi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2205
	.align	2,0x90
L_5_2206:
	addl	$2,%ebp
	movl	%ebp,GLOBL(regs)+88
L_5_2205:
	popl	%eax
	decl	%eax
	jl	JJ_5098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5259:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5098:
	ret

FUNC(op_4198)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	%eax,%edi
	sall	$2,%ecx
	shrl	$7,%edi
	movl	GLOBL(regs)+88,%ebp
	movl	$GLOBL(regs),%esi
	movl	%ebp,20-16(%esp)
	xorl	%ebx,%ebx
	movl	(%ecx,%esi),%edx
	andl	$28,%edi
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%edx,(%ecx,%esi)
	movl	%ebx,%eax
	movw	(%edi,%esi),%dx
	testw	%dx,%dx
	jge	L_5_2220
	orb	$128,regflags
	pushl	%ebp
	jmp	L_5_2517
	.align	2,0x90
L_5_2220:
	cmpw	%ax,%dx
	jle	L_5_2222
	movl	20-16(%esp),%ebx
	andb	$127,regflags
	pushl	%ebx
L_5_2517:
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2221
	.align	2,0x90
L_5_2222:
	addl	$2,GLOBL(regs)+88
L_5_2221:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5260:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5099:
	ret

FUNC(op_41a0)

	subl	$8,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%ebx
	movl	%ebp,20-16(%esp)
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%eax,%edi
	addl	$-2,%ecx
	shrl	$7,%edi
	movl	%ecx,16-16(%esp)
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
	movl	16-16(%esp),%ecx
	andl	$28,%edi
	movl	%ecx,(%ebx,%esi)
	movw	(%edi,%esi),%dx
	testw	%dx,%dx
	jge	L_5_2236
	orb	$128,regflags
	pushl	%ebp
	jmp	L_5_2518
	.align	2,0x90
L_5_2236:
	cmpw	%ax,%dx
	jle	L_5_2238
	movl	20-16(%esp),%ecx
	andb	$127,regflags
	pushl	%ecx
L_5_2518:
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2237
	.align	2,0x90
L_5_2238:
	addl	$2,GLOBL(regs)+88
L_5_2237:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_5100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5261:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5100:
	ret

FUNC(op_41a8)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$7,%ecx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_5053:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	%esi,%ebp
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%ecx,%ebx),%dx
	testw	%dx,%dx
	jge	L_5_2253
	orb	$128,regflags
	jmp	L_5_2519
	.align	2,0x90
L_5_2253:
	cmpw	%ax,%dx
	jle	L_5_2255
	andb	$127,regflags
L_5_2519:
	pushl	%esi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2254
	.align	2,0x90
L_5_2255:
	addl	$4,%ebp
	movl	%ebp,GLOBL(regs)+88
L_5_2254:
	popl	%eax
	decl	%eax
	jl	JJ_5101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5262:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5101:
	ret

FUNC(op_41b8)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5054:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	%ebx,%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	GLOBL(regs)(%ecx),%dx
	testw	%dx,%dx
	jge	L_5_2305
	orb	$128,regflags
	jmp	L_5_2520
	.align	2,0x90
L_5_2305:
	cmpw	%ax,%dx
	jle	L_5_2307
	andb	$127,regflags
L_5_2520:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2306
	.align	2,0x90
L_5_2307:
	addl	$4,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2306:
	popl	%eax
	decl	%eax
	jl	JJ_5102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5263:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5102:
	ret

FUNC(op_41b9)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$7,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_5055:
	bswapl	%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	%ebx,%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	GLOBL(regs)(%ecx),%dx
	testw	%dx,%dx
	jge	L_5_2323
	orb	$128,regflags
	jmp	L_5_2521
	.align	2,0x90
L_5_2323:
	cmpw	%ax,%dx
	jle	L_5_2325
	andb	$127,regflags
L_5_2521:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2324
	.align	2,0x90
L_5_2325:
	addl	$6,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2324:
	popl	%eax
	decl	%eax
	jl	JJ_5103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5264:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5103:
	ret

FUNC(op_41ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_5056:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	%ebx,%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	GLOBL(regs)(%ecx),%dx
	testw	%dx,%dx
	jge	L_5_2342
	orb	$128,regflags
	jmp	L_5_2522
	.align	2,0x90
L_5_2342:
	cmpw	%ax,%dx
	jle	L_5_2344
	andb	$127,regflags
L_5_2522:
	pushl	%ebx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2343
	.align	2,0x90
L_5_2344:
	addl	$4,%esi
	movl	%esi,GLOBL(regs)+88
L_5_2343:
	popl	%eax
	decl	%eax
	jl	JJ_5104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5265:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5104:
	ret

FUNC(op_41bc)

	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_5057:
	rolw	$8,%ax
	andl	$28,%edx
	movl	%ecx,%ebx
	movw	GLOBL(regs)(%edx),%dx
	testw	%dx,%dx
	jge	L_5_2394
	orb	$128,regflags
	jmp	L_5_2523
	.align	2,0x90
L_5_2394:
	cmpw	%ax,%dx
	jle	L_5_2396
	andb	$127,regflags
L_5_2523:
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_5_2395
	.align	2,0x90
L_5_2396:
	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
L_5_2395:
	popl	%eax
	decl	%eax
	jl	JJ_5105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5266:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5105:
	ret

FUNC(op_41d0)

	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	addl	$8,%edx
	andl	$7,%eax
	movl	(%ecx,%edx,4),%edx
	addl	$8,%eax
	movl	%edx,(%ecx,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5267:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5106:
	ret

FUNC(op_41e8)

	movl	%eax,%ecx
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_5058:
	rolw	$8,%bx
	movl	%ebx,%eax
	andl	$7,%edx
	addl	$8,%ecx
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%ecx,4),%eax
	movl	%eax,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5268:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5107:
	ret

FUNC(op_41f8)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_5059:
	rolw	$8,%cx
	movl	%ecx,%edx
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5269:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5108:
	ret

FUNC(op_41f9)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_5060:
	addl	$8,%eax
	bswapl	%edx
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5270:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5109:
	ret

FUNC(op_41fa)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%edx
	shrl	$9,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_5061:
	rolw	$8,%ax
	cwtl
	andl	$7,%ecx
	leal	2(%eax,%edx),%edx
	addl	$8,%ecx
	movl	%edx,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5271:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5110:
	ret

FUNC(op_4200)

	andl	$7,%eax
	movb	$0,GLOBL(regs)(,%eax,4)
	movl	$64,regflags
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5272:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5111:
	ret

FUNC(op_4210)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5273:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5112:
	ret

FUNC(op_4218)

	movl	%eax,%ebx
	andl	$7,%ebx
	leal	8(%ebx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	(%eax,%ecx),%edx
	addl	%edx,%ebx
	movl	%ebx,(%eax,%ecx)
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_5113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_5274:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_5113:
	ret

FUNC(Init020_05)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_5000-4
	movl	%eax,RR0_5001-4
	movl	%eax,RR0_5002-4
	movl	%eax,RR0_5003-4
	movl	%eax,RR0_5004-4
	movl	%eax,RR0_5005-4
	movl	%eax,RR0_5006-4
	movl	%eax,RR0_5007-4
	movl	%eax,RR0_5008-4
	movl	%eax,RR0_5009-4
	movl	%eax,RR0_5010-4
	movl	%eax,RR0_5011-4
	movl	%eax,RR0_5012-4
	movl	%eax,RR0_5013-4
	movl	%eax,RR0_5014-4
	movl	%eax,RR0_5015-4
	movl	%eax,RR0_5016-4
	movl	%eax,RR0_5017-4
	movl	%eax,RR0_5018-4
	movl	%eax,RR0_5019-4
	movl	%eax,RR0_5020-4
	movl	%eax,RR0_5021-4
	movl	%eax,RR0_5022-4
	movl	%eax,RR0_5023-4
	movl	%eax,RR0_5024-4
	movl	%eax,RR0_5025-4
	movl	%eax,RR0_5026-4
	movl	%eax,RR0_5027-4
	movl	%eax,RR0_5028-4
	movl	%eax,RR0_5029-4
	movl	%eax,RR0_5030-4
	movl	%eax,RR0_5031-4
	movl	%eax,RR0_5032-4
	movl	%eax,RR0_5033-4
	movl	%eax,RR0_5034-4
	movl	%eax,RR0_5035-4
	movl	%eax,RR0_5036-4
	movl	%eax,RR0_5037-4
	movl	%eax,RR0_5038-4
	movl	%eax,RR0_5039-4
	movl	%eax,RR0_5040-4
	movl	%eax,RR0_5041-4
	movl	%eax,RR0_5042-4
	movl	%eax,RR0_5043-4
	movl	%eax,RR0_5044-4
	movl	%eax,RR0_5045-4
	movl	%eax,RR0_5046-4
	movl	%eax,RR0_5047-4
	movl	%eax,RR0_5048-4
	movl	%eax,RR0_5049-4
	movl	%eax,RR0_5050-4
	movl	%eax,RR0_5051-4
	movl	%eax,RR0_5052-4
	movl	%eax,RR0_5053-4
	movl	%eax,RR0_5054-4
	movl	%eax,RR0_5055-4
	movl	%eax,RR0_5056-4
	movl	%eax,RR0_5057-4
	movl	%eax,RR0_5058-4
	movl	%eax,RR0_5059-4
	movl	%eax,RR0_5060-4
	movl	%eax,RR0_5061-4
	movl	%eax,RR0_5062-4
	movl	%eax,RR0_5063-4
	movl	%eax,RR0_5064-4
	movl	%eax,RR0_5065-4
	movl	%eax,RR0_5066-4
	movl	%eax,RR0_5067-4
	movl	%eax,RR0_5068-4
	movl	%eax,RR0_5069-4
	movl	%eax,RR0_5070-4
	movl	%eax,RR0_5071-4
	movl	%eax,RR0_5072-4
	movl	%eax,RR0_5073-4
	movl	%eax,RR0_5074-4
	movl	%eax,RR0_5075-4
	movl	%eax,RR0_5076-4
	movl	%eax,RR0_5077-4
	movl	%eax,RR0_5078-4
	movl	%eax,RR0_5079-4
	movl	%eax,RR0_5080-4
	movl	%eax,RR0_5081-4
	movl	%eax,RR0_5082-4
	movl	%eax,RR0_5083-4
	movl	%eax,RR0_5084-4
	movl	%eax,RR0_5085-4
	movl	%eax,RR0_5086-4
	movl	%eax,RR0_5087-4
	movl	%eax,RR0_5088-4
	movl	%eax,RR0_5089-4
	movl	%eax,RR0_5090-4
	movl	%eax,RR0_5091-4
	movl	%eax,RR0_5092-4
	movl	%eax,RR0_5093-4
	movl	%eax,RR0_5094-4
	movl	%eax,RR0_5095-4
	movl	%eax,RR0_5096-4
	movl	%eax,RR0_5097-4
	movl	%eax,RR0_5098-4
	movl	%eax,RR0_5099-4
	movl	%eax,RR0_5100-4
	movl	%eax,RR0_5101-4
	movl	%eax,RR0_5102-4
	movl	%eax,RR0_5103-4
	movl	%eax,RR0_5104-4
	movl	%eax,RR0_5105-4
	movl	%eax,RR0_5106-4
	movl	%eax,RR0_5107-4
	movl	%eax,RR0_5108-4
	movl	%eax,RR0_5109-4
	movl	%eax,RR0_5110-4
	movl	%eax,RR0_5111-4
	movl	%eax,RR0_5112-4
	movl	%eax,RR0_5113-4
	movl	%eax,RR0_5114-4
	movl	%eax,RR0_5115-4
	movl	%eax,RR0_5116-4
	movl	%eax,RR0_5117-4
	movl	%eax,RR0_5118-4
	movl	%eax,RR0_5119-4
	movl	%eax,RR0_5120-4
	movl	%eax,RR0_5121-4
	movl	%eax,RR0_5122-4
	movl	%eax,RR0_5123-4
	movl	%eax,RR0_5124-4
	movl	%eax,RR0_5125-4
	movl	%eax,RR0_5126-4
	movl	%eax,RR0_5127-4
	movl	%eax,RR0_5128-4
	movl	%eax,RR0_5129-4
	movl	%eax,RR0_5130-4
	movl	%eax,RR0_5131-4
	movl	%eax,RR0_5132-4
	movl	%eax,RR0_5133-4
	movl	%eax,RR0_5134-4
	movl	%eax,RR0_5135-4
	movl	%eax,RR0_5136-4
	movl	%eax,RR0_5137-4
	movl	%eax,RR0_5138-4
	movl	%eax,RR0_5139-4
	movl	%eax,RR0_5140-4
	movl	%eax,RR0_5141-4
	movl	%eax,RR0_5142-4
	movl	%eax,RR0_5143-4
	movl	%eax,RR0_5144-4
	movl	%eax,RR0_5145-4
	movl	%eax,RR0_5146-4
	movl	%eax,RR0_5147-4
	movl	%eax,RR0_5148-4
	movl	%eax,RR0_5149-4
	movl	%eax,RR0_5150-4
	movl	%eax,RR0_5151-4
	movl	%eax,RR0_5152-4
	movl	%eax,RR0_5153-4
	movl	%eax,RR0_5154-4
	movl	%eax,RR0_5155-4
	movl	%eax,RR0_5156-4
	movl	%eax,RR0_5157-4
	movl	%eax,RR0_5158-4
	movl	%eax,RR0_5159-4
	movl	%eax,RR0_5160-4
	movl	%eax,RR0_5161-4
	movl	%eax,RR0_5162-4
	movl	%eax,RR0_5163-4
	movl	%eax,RR0_5164-4
	movl	%eax,RR0_5165-4
	movl	%eax,RR0_5166-4
	movl	%eax,RR0_5167-4
	movl	%eax,RR0_5168-4
	movl	%eax,RR0_5169-4
	movl	%eax,RR0_5170-4
	movl	%eax,RR0_5171-4
	movl	%eax,RR0_5172-4
	movl	%eax,RR0_5173-4
	movl	%eax,RR0_5174-4
	movl	%eax,RR0_5175-4
	movl	%eax,RR0_5176-4
	movl	%eax,RR0_5177-4
	movl	%eax,RR0_5178-4
	movl	%eax,RR0_5179-4
	movl	%eax,RR0_5180-4
	movl	%eax,RR0_5181-4
	movl	%eax,RR0_5182-4
	movl	%eax,RR0_5183-4
	movl	%eax,RR0_5184-4
	movl	%eax,RR0_5185-4
	movl	%eax,RR0_5186-4
	movl	%eax,RR0_5187-4
	movl	%eax,RR0_5188-4
	movl	%eax,RR0_5189-4
	movl	%eax,RR0_5190-4
	movl	%eax,RR0_5191-4
	movl	%eax,RR0_5192-4
	movl	%eax,RR0_5193-4
	movl	%eax,RR0_5194-4
	movl	%eax,RR0_5195-4
	movl	%eax,RR0_5196-4
	movl	%eax,RR0_5197-4
	movl	%eax,RR0_5198-4
	movl	%eax,RR0_5199-4
	movl	%eax,RR0_5200-4
	movl	%eax,RR0_5201-4
	movl	%eax,RR0_5202-4
	movl	%eax,RR0_5203-4
	movl	%eax,RR0_5204-4
	movl	%eax,RR0_5205-4
	movl	%eax,RR0_5206-4
	movl	%eax,RR0_5207-4
	movl	%eax,RR0_5208-4
	movl	%eax,RR0_5209-4
	movl	%eax,RR0_5210-4
	movl	%eax,RR0_5211-4
	movl	%eax,RR0_5212-4
	movl	%eax,RR0_5213-4
	movl	%eax,RR0_5214-4
	movl	%eax,RR0_5215-4
	movl	%eax,RR0_5216-4
	movl	%eax,RR0_5217-4
	movl	%eax,RR0_5218-4
	movl	%eax,RR0_5219-4
	movl	%eax,RR0_5220-4
	movl	%eax,RR0_5221-4
	movl	%eax,RR0_5222-4
	movl	%eax,RR0_5223-4
	movl	%eax,RR0_5224-4
	movl	%eax,RR0_5225-4
	movl	%eax,RR0_5226-4
	movl	%eax,RR0_5227-4
	movl	%eax,RR0_5228-4
	movl	%eax,RR0_5229-4
	movl	%eax,RR0_5230-4
	movl	%eax,RR0_5231-4
	movl	%eax,RR0_5232-4
	movl	%eax,RR0_5233-4
	movl	%eax,RR0_5234-4
	movl	%eax,RR0_5235-4
	movl	%eax,RR0_5236-4
	movl	%eax,RR0_5237-4
	movl	%eax,RR0_5238-4
	movl	%eax,RR0_5239-4
	movl	%eax,RR0_5240-4
	movl	%eax,RR0_5241-4
	movl	%eax,RR0_5242-4
	movl	%eax,RR0_5243-4
	movl	%eax,RR0_5244-4
	movl	%eax,RR0_5245-4
	movl	%eax,RR0_5246-4
	movl	%eax,RR0_5247-4
	movl	%eax,RR0_5248-4
	movl	%eax,RR0_5249-4
	movl	%eax,RR0_5250-4
	movl	%eax,RR0_5251-4
	movl	%eax,RR0_5252-4
	movl	%eax,RR0_5253-4
	movl	%eax,RR0_5254-4
	movl	%eax,RR0_5255-4
	movl	%eax,RR0_5256-4
	movl	%eax,RR0_5257-4
	movl	%eax,RR0_5258-4
	movl	%eax,RR0_5259-4
	movl	%eax,RR0_5260-4
	movl	%eax,RR0_5261-4
	movl	%eax,RR0_5262-4
	movl	%eax,RR0_5263-4
	movl	%eax,RR0_5264-4
	movl	%eax,RR0_5265-4
	movl	%eax,RR0_5266-4
	movl	%eax,RR0_5267-4
	movl	%eax,RR0_5268-4
	movl	%eax,RR0_5269-4
	movl	%eax,RR0_5270-4
	movl	%eax,RR0_5271-4
	movl	%eax,RR0_5272-4
	movl	%eax,RR0_5273-4
	movl	%eax,RR0_5274-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_5000-4
	movl	%eax,RR2_5001-4
	movl	%eax,RR2_5002-4
	movl	%eax,RR2_5003-4
	movl	%eax,RR2_5004-4
	movl	%eax,RR2_5005-4
	movl	%eax,RR2_5006-4
	movl	%eax,RR2_5007-4
	movl	%eax,RR2_5008-4
	movl	%eax,RR2_5009-4
	movl	%eax,RR2_5010-4
	movl	%eax,RR2_5011-4
	movl	%eax,RR2_5012-4
	movl	%eax,RR2_5013-4
	movl	%eax,RR2_5014-4
	movl	%eax,RR2_5015-4
	movl	%eax,RR2_5016-4
	movl	%eax,RR2_5017-4
	movl	%eax,RR2_5018-4
	movl	%eax,RR2_5019-4
	movl	%eax,RR2_5020-4
	movl	%eax,RR2_5021-4
	movl	%eax,RR2_5022-4
	movl	%eax,RR2_5023-4
	movl	%eax,RR2_5024-4
	movl	%eax,RR2_5025-4
	movl	%eax,RR2_5026-4
	movl	%eax,RR2_5027-4
	movl	%eax,RR2_5028-4
	movl	%eax,RR2_5029-4
	movl	%eax,RR2_5030-4
	movl	%eax,RR2_5031-4
	movl	%eax,RR2_5032-4
	movl	%eax,RR2_5033-4
	movl	%eax,RR2_5034-4
	movl	%eax,RR2_5035-4
	movl	%eax,RR2_5036-4
	movl	%eax,RR2_5037-4
	movl	%eax,RR2_5038-4
	movl	%eax,RR2_5039-4
	movl	%eax,RR2_5040-4
	movl	%eax,RR2_5041-4
	movl	%eax,RR2_5042-4
	movl	%eax,RR2_5043-4
	movl	%eax,RR2_5044-4
	movl	%eax,RR2_5045-4
	movl	%eax,RR2_5046-4
	movl	%eax,RR2_5047-4
	movl	%eax,RR2_5048-4
	movl	%eax,RR2_5049-4
	movl	%eax,RR2_5050-4
	movl	%eax,RR2_5051-4
	movl	%eax,RR2_5052-4
	movl	%eax,RR2_5053-4
	movl	%eax,RR2_5054-4
	movl	%eax,RR2_5055-4
	movl	%eax,RR2_5056-4
	movl	%eax,RR2_5057-4
	movl	%eax,RR2_5058-4
	movl	%eax,RR2_5059-4
	movl	%eax,RR2_5060-4
	movl	%eax,RR2_5061-4
	incl	%eax
	incl	%eax
	movl	%eax,RR4_5000-4
	movl	%eax,RR4_5001-4
	movl	%eax,RR4_5002-4
	movl	%eax,RR4_5003-4
	movl	%eax,RR4_5004-4
	movl	%eax,RR4_5005-4
	movl	%eax,RR4_5006-4
	movl	%eax,RR4_5007-4
	movl	%eax,RR4_5008-4
	movl	%eax,RR4_5009-4
	movl	%eax,RR4_5010-4
	movl	%eax,RR4_5011-4
	incl	%eax
	incl	%eax
	movl	%eax,RR6_5000-4
	movl	%eax,RR6_5001-4
	movl	%eax,RR6_5002-4
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
