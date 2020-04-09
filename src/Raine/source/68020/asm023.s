

FUNC(op_10f0)

	subl	$20,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%edx
	movl	%eax,32-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,28-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3000:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_3_384
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_3_384:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_3_385
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_386
	movl	%ebp,%ebx
L_3_386:
	testl	$64,%esi
	je	L_3_387
	movl	%ebp,16-16(%esp)
L_3_387:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_388
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_3001:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_388:
	cmpl	$48,%edx
	jne	L_3_391
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_391:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_3_394
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_394:
	cmpl	$3,20-16(%esp)
	jne	L_3_397
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_397:
	andl	$4,%esi
	jne	L_3_400
	addl	16-16(%esp),%ebx
L_3_400:
	cmpl	$0,20-16(%esp)
	je	L_3_401
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_401:
	testl	%esi,%esi
	je	L_3_404
	addl	16-16(%esp),%ebx
L_3_404:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_405
	.align	2,0x90
L_3_385:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_405:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	movl	32-16(%esp),%eax
	addl	$8,%eax
	movl	32-16(%esp),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%edi
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%edi
	movl	%edi,GLOBL(regs)(%eax)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3000:
	ret

FUNC(op_10fb)

	subl	$20,%esp
	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,32-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,28-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_3006:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_3_446
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_3_446:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_3_447
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_448
	movl	%ebp,%ebx
L_3_448:
	testl	$64,%esi
	je	L_3_449
	movl	%ebp,16-16(%esp)
L_3_449:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_450
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_3007:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_450:
	cmpl	$48,%edx
	jne	L_3_453
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_453:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_3_456
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_456:
	cmpl	$3,20-16(%esp)
	jne	L_3_459
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_459:
	andl	$4,%esi
	jne	L_3_462
	addl	16-16(%esp),%ebx
L_3_462:
	cmpl	$0,20-16(%esp)
	je	L_3_463
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_463:
	testl	%esi,%esi
	je	L_3_466
	addl	16-16(%esp),%ebx
L_3_466:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_467
	.align	2,0x90
L_3_447:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_467:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	movl	32-16(%esp),%eax
	addl	$8,%eax
	movl	32-16(%esp),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%edi
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%edi
	movl	%edi,GLOBL(regs)(%eax)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3001:
	ret

FUNC(op_1130)

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
RR0_3012:
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
	jne	L_3_521
	movswl	%di,%edi
L_3_521:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_522
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_523
	movl	%ebp,%ebx
L_3_523:
	testl	$64,%esi
	je	L_3_524
	movl	%ebp,%edi
L_3_524:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_525
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_525:
	cmpl	$48,%edx
	jne	L_3_528
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_528:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_531
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_531:
	cmpl	$3,16-16(%esp)
	jne	L_3_534
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_534:
	andl	$4,%esi
	jne	L_3_537
	addl	%edi,%ebx
L_3_537:
	cmpl	$0,16-16(%esp)
	je	L_3_538
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_538:
	testl	%esi,%esi
	je	L_3_541
	addl	%edi,%ebx
L_3_541:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_542
	.align	2,0x90
L_3_522:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_542:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	28-16(%esp),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3002:
	ret

FUNC(op_113b)

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
RR0_3018:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_583
	movswl	%di,%edi
L_3_583:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_584
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_585
	movl	%ebp,%ebx
L_3_585:
	testl	$64,%esi
	je	L_3_586
	movl	%ebp,%edi
L_3_586:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_587
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3019:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_587:
	cmpl	$48,%edx
	jne	L_3_590
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_590:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_593
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_593:
	cmpl	$3,16-16(%esp)
	jne	L_3_596
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_596:
	andl	$4,%esi
	jne	L_3_599
	addl	%edi,%ebx
L_3_599:
	cmpl	$0,16-16(%esp)
	je	L_3_600
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_600:
	testl	%esi,%esi
	je	L_3_603
	addl	%edi,%ebx
L_3_603:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_604
	.align	2,0x90
L_3_584:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_604:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	28-16(%esp),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3003:
	ret

FUNC(op_1170)

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
RR0_3024:
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
	jne	L_3_668
	movswl	%di,%edi
L_3_668:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_669
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_670
	movl	%ebp,%ebx
L_3_670:
	testl	$64,%esi
	je	L_3_671
	movl	%ebp,%edi
L_3_671:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_672
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3025:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_672:
	cmpl	$48,%edx
	jne	L_3_675
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_675:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_678
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_678:
	cmpl	$3,16-16(%esp)
	jne	L_3_681
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_681:
	andl	$4,%esi
	jne	L_3_684
	addl	%edi,%ebx
L_3_684:
	cmpl	$0,16-16(%esp)
	je	L_3_685
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_685:
	testl	%esi,%esi
	je	L_3_688
	addl	%edi,%ebx
L_3_688:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_689
	.align	2,0x90
L_3_669:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_689:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%ecx,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_3029:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%edx
	addl	$8,%edx
	cwtl
	movb	16-16(%esp),%cl
	addl	GLOBL(regs)(,%edx,4),%eax
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3030:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3004:
	ret

FUNC(op_117b)

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
RR0_3031:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_737
	movswl	%di,%edi
L_3_737:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_738
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_739
	movl	%ebp,%ebx
L_3_739:
	testl	$64,%esi
	je	L_3_740
	movl	%ebp,%edi
L_3_740:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_741
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3032:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_741:
	cmpl	$48,%edx
	jne	L_3_744
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3033:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_744:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_747
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3034:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_747:
	cmpl	$3,16-16(%esp)
	jne	L_3_750
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3035:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_750:
	andl	$4,%esi
	jne	L_3_753
	addl	%edi,%ebx
L_3_753:
	cmpl	$0,16-16(%esp)
	je	L_3_754
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_754:
	testl	%esi,%esi
	je	L_3_757
	addl	%edi,%ebx
L_3_757:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_758
	.align	2,0x90
L_3_738:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_758:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%ecx,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A(%eax),%cx
RR0_3036:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%edx
	addl	$8,%edx
	cwtl
	movb	16-16(%esp),%cl
	addl	GLOBL(regs)(,%edx,4),%eax
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3005:
	ret

FUNC(op_1180)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%edx
	andl	$7,%eax
	movb	GLOBL(regs)(,%edx,4),%dl
	movl	GLOBL(regs)+88,%ecx
	movb	%dl,31-16(%esp)
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_3038:
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
	jne	L_3_775
	movswl	%di,%edi
L_3_775:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_776
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_777
	movl	%ebp,%ebx
L_3_777:
	testl	$64,%esi
	je	L_3_778
	movl	%ebp,%edi
L_3_778:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_779
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3039:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_779:
	cmpl	$48,%edx
	jne	L_3_782
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3040:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_782:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_785
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3041:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_785:
	cmpl	$3,16-16(%esp)
	jne	L_3_788
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3042:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_788:
	andl	$4,%esi
	jne	L_3_791
	addl	%edi,%ebx
L_3_791:
	cmpl	$0,16-16(%esp)
	je	L_3_792
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_792:
	testl	%esi,%esi
	je	L_3_795
	addl	%edi,%ebx
L_3_795:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_796
	.align	2,0x90
L_3_776:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_3_796:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3006:
	ret

FUNC(op_1190)

	subl	$16,%esp
	movl	%eax,%edx
	xorl	%ecx,%ecx
	shrl	$9,%edx
	andl	$7,%eax
	addl	$8,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	2(%esi,%eax,4),%cl
	xorl	%ebx,%ebx
	movw	(%esi,%eax,4),%bx
	addl	$8,%edx
	movl	GLOBL(R24)(,%ecx,4),%eax
	movl	GLOBL(regs)+88,%ecx
	movb	(%ebx,%eax),%bl
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	movb	%bl,31-16(%esp)
	movl	%eax,GLOBL(regs)+88
	addl	$4,%ecx
	movl	(%esi,%edx,4),%edx
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3044:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_804
	movswl	%di,%edi
L_3_804:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_805
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_806
	movl	%ebp,%ebx
L_3_806:
	testl	$64,%esi
	je	L_3_807
	movl	%ebp,%edi
L_3_807:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_808
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3045:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_808:
	cmpl	$48,%edx
	jne	L_3_811
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3046:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_811:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_814
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3047:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_814:
	cmpl	$3,16-16(%esp)
	jne	L_3_817
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3048:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_817:
	andl	$4,%esi
	jne	L_3_820
	addl	%edi,%ebx
L_3_820:
	cmpl	$0,16-16(%esp)
	je	L_3_821
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_821:
	testl	%esi,%esi
	je	L_3_824
	addl	%edi,%ebx
L_3_824:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_825
	.align	2,0x90
L_3_805:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_825:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3007:
	ret

FUNC(op_1198)

	subl	$16,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edi
	leal	8(%ebp),%ecx
	movl	%eax,%esi
	sall	$2,%ecx
	shrl	$9,%esi
	movl	%ecx,16-16(%esp)
	xorl	%eax,%eax
	movl	(%ecx,%edi),%edx
	movb	2(%ecx,%edi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	movb	(%ebx,%eax),%bl
	movb	%bl,31-16(%esp)
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movl	%edx,(%ecx,%edi)
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
RR0_3050:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_833
	movswl	%di,%edi
L_3_833:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_834
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_835
	movl	%ebp,%ebx
L_3_835:
	testl	$64,%esi
	je	L_3_836
	movl	%ebp,%edi
L_3_836:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_837
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3051:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_837:
	cmpl	$48,%edx
	jne	L_3_840
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3052:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_840:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_843
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3053:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_843:
	cmpl	$3,16-16(%esp)
	jne	L_3_846
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3054:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_846:
	andl	$4,%esi
	jne	L_3_849
	addl	%edi,%ebx
L_3_849:
	cmpl	$0,16-16(%esp)
	je	L_3_850
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_850:
	testl	%esi,%esi
	je	L_3_853
	addl	%edi,%ebx
L_3_853:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_854
	.align	2,0x90
L_3_834:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_854:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3008:
	ret

FUNC(op_11a0)

	subl	$16,%esp
	movl	%eax,%edx
	andl	$7,%eax
	leal	8(%eax),%ecx
	movl	$GLOBL(regs),%edi
	sall	$2,%ecx
	movl	%edx,%esi
	movl	%ecx,16-16(%esp)
	shrl	$9,%esi
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ecx,%edi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%bl
	movb	%bl,31-16(%esp)
	movl	%edx,(%ecx,%edi)
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
RR0_3056:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_862
	movswl	%di,%edi
L_3_862:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_863
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_864
	movl	%ebp,%ebx
L_3_864:
	testl	$64,%esi
	je	L_3_865
	movl	%ebp,%edi
L_3_865:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_866
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3057:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_866:
	cmpl	$48,%edx
	jne	L_3_869
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3058:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_869:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_872
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3059:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_872:
	cmpl	$3,16-16(%esp)
	jne	L_3_875
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3060:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_875:
	andl	$4,%esi
	jne	L_3_878
	addl	%edi,%ebx
L_3_878:
	cmpl	$0,16-16(%esp)
	je	L_3_879
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_879:
	testl	%esi,%esi
	je	L_3_882
	addl	%edi,%ebx
L_3_882:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_883
	.align	2,0x90
L_3_863:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_883:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3009:
	ret

FUNC(op_11a8)

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
RR2_3000:
	rolw	$8,%ax
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%al
	movb	%al,27-16(%esp)
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	addl	$4,%eax
	addl	$8,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3062:
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
	jne	L_3_892
	movswl	%di,%edi
L_3_892:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_893
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_894
	movl	%ebp,%ebx
L_3_894:
	testl	$64,%esi
	je	L_3_895
	movl	%ebp,%edi
L_3_895:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_896
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3063:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_896:
	cmpl	$48,%edx
	jne	L_3_899
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3064:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_899:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_902
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3065:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_902:
	cmpl	$3,16-16(%esp)
	jne	L_3_905
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3066:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_905:
	andl	$4,%esi
	jne	L_3_908
	addl	%edi,%ebx
L_3_908:
	cmpl	$0,16-16(%esp)
	je	L_3_909
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_909:
	testl	%esi,%esi
	je	L_3_912
	addl	%edi,%ebx
L_3_912:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_913
	.align	2,0x90
L_3_893:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_913:
	movb	27-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3067:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3010:
	ret

FUNC(op_11b0)

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
RR0_3068:
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
	jne	L_3_920
	movswl	%di,%edi
L_3_920:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_921
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_922
	movl	%ebp,%ebx
L_3_922:
	testl	$64,%esi
	je	L_3_923
	movl	%ebp,%edi
L_3_923:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_924
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3069:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_924:
	cmpl	$48,%edx
	jne	L_3_927
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3070:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_927:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_930
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3071:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_930:
	cmpl	$3,16-16(%esp)
	jne	L_3_933
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3072:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_933:
	andl	$4,%esi
	jne	L_3_936
	addl	%edi,%ebx
L_3_936:
	cmpl	$0,16-16(%esp)
	je	L_3_937
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_937:
	testl	%esi,%esi
	je	L_3_940
	addl	%edi,%ebx
L_3_940:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_941
	.align	2,0x90
L_3_921:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_941:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%dl
	movl	40-16(%esp),%eax
	movb	%dl,31-16(%esp)
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_3073:
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
	jne	L_3_946
	movswl	%di,%edi
L_3_946:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_947
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_948
	movl	%ebp,%ebx
L_3_948:
	testl	$64,%esi
	je	L_3_949
	movl	%ebp,%edi
L_3_949:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_950
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3074:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_950:
	cmpl	$48,%edx
	jne	L_3_953
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3075:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_953:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_956
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3076:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_956:
	cmpl	$3,16-16(%esp)
	jne	L_3_959
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3077:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_959:
	andl	$4,%esi
	jne	L_3_962
	addl	%edi,%ebx
L_3_962:
	cmpl	$0,16-16(%esp)
	je	L_3_963
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_963:
	testl	%esi,%esi
	je	L_3_966
	addl	%edi,%ebx
L_3_966:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_967
	.align	2,0x90
L_3_947:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_967:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3011:
	ret

FUNC(op_11b8)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebx
	movl	%eax,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_3001:
	rolw	$8,%dx
	movswl	%dx,%edx
	shrl	$9,%ecx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movb	(%edx,%eax),%dl
	movl	%ebx,%eax
	addl	$6,%ebx
	addl	$4,%eax
	movb	%dl,27-16(%esp)
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3079:
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
	jne	L_3_976
	movswl	%di,%edi
L_3_976:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_977
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_3_978
	movl	%ebp,16-16(%esp)
L_3_978:
	testl	$64,%esi
	je	L_3_979
	movl	%ebp,%edi
L_3_979:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_980
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3080:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_3_980:
	cmpl	$48,%edx
	jne	L_3_983
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3081:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_3_983:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_3_986
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3082:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_986:
	cmpl	$3,%ecx
	jne	L_3_989
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3083:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_989:
	andl	$4,%esi
	jne	L_3_992
	addl	%edi,16-16(%esp)
L_3_992:
	testl	%ecx,%ecx
	je	L_3_993
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_3_993:
	testl	%esi,%esi
	je	L_3_996
	addl	%edi,16-16(%esp)
L_3_996:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_3_997
	.align	2,0x90
L_3_977:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_997:
	movb	27-16(%esp),%bl
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3012:
	ret

FUNC(op_11b9)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ebx
	movl	%eax,%ecx
	movl	%ebx,28-16(%esp)
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%edx
RR2_3002:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movb	(%edx,%eax),%dl
	movl	%ebx,%eax
	addl	$8,%ebx
	addl	$6,%eax
	movb	%dl,27-16(%esp)
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3085:
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
	jne	L_3_1006
	movswl	%di,%edi
L_3_1006:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1007
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_3_1008
	movl	%ebp,16-16(%esp)
L_3_1008:
	testl	$64,%esi
	je	L_3_1009
	movl	%ebp,%edi
L_3_1009:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1010
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3086:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$10,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_3_1010:
	cmpl	$48,%edx
	jne	L_3_1013
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3087:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_3_1013:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_3_1016
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3088:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1016:
	cmpl	$3,%ecx
	jne	L_3_1019
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3089:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1019:
	andl	$4,%esi
	jne	L_3_1022
	addl	%edi,16-16(%esp)
L_3_1022:
	testl	%ecx,%ecx
	je	L_3_1023
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_3_1023:
	testl	%esi,%esi
	je	L_3_1026
	addl	%edi,16-16(%esp)
L_3_1026:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_3_1027
	.align	2,0x90
L_3_1007:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1027:
	movb	27-16(%esp),%bl
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3013:
	ret

FUNC(op_11ba)

	subl	$16,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	%ebx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_3003:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%al
	movb	%al,27-16(%esp)
	andl	$7,%ecx
	movl	%ebx,%eax
	addl	$8,%ecx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_3091:
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
	jne	L_3_1037
	movswl	%di,%edi
L_3_1037:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1038
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_3_1039
	movl	%ebp,16-16(%esp)
L_3_1039:
	testl	$64,%esi
	je	L_3_1040
	movl	%ebp,%edi
L_3_1040:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1041
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3092:
	rolw	$8,%ax
	movl	28-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_3_1041:
	cmpl	$48,%edx
	jne	L_3_1044
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3093:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_3_1044:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_3_1047
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3094:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1047:
	cmpl	$3,%ecx
	jne	L_3_1050
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3095:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1050:
	andl	$4,%esi
	jne	L_3_1053
	addl	%edi,16-16(%esp)
L_3_1053:
	testl	%ecx,%ecx
	je	L_3_1054
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_3_1054:
	testl	%esi,%esi
	je	L_3_1057
	addl	%edi,16-16(%esp)
L_3_1057:
	movl	16-16(%esp),%edx
	addl	%ebp,%edx
	jmp	L_3_1058
	.align	2,0x90
L_3_1038:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1058:
	movb	27-16(%esp),%bl
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3014:
	ret

FUNC(op_11bb)

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
RR0_3097:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,32-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1066
	movswl	%di,%edi
L_3_1066:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1067
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1068
	movl	%ebp,%ebx
L_3_1068:
	testl	$64,%esi
	je	L_3_1069
	movl	%ebp,%edi
L_3_1069:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1070
	movl	32-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3098:
	rolw	$8,%ax
	movl	36-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1070:
	cmpl	$48,%edx
	jne	L_3_1073
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3099:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1073:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1076
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3100:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1076:
	cmpl	$3,16-16(%esp)
	jne	L_3_1079
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3101:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1079:
	andl	$4,%esi
	jne	L_3_1082
	addl	%edi,%ebx
L_3_1082:
	cmpl	$0,16-16(%esp)
	je	L_3_1083
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1083:
	testl	%esi,%esi
	je	L_3_1086
	addl	%edi,%ebx
L_3_1086:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1087
	.align	2,0x90
L_3_1067:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1087:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%dl
	movl	40-16(%esp),%eax
	movb	%dl,31-16(%esp)
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%ecx,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%ecx),%si
RR0_3102:
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
	jne	L_3_1092
	movswl	%di,%edi
L_3_1092:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1093
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1094
	movl	%ebp,%ebx
L_3_1094:
	testl	$64,%esi
	je	L_3_1095
	movl	%ebp,%edi
L_3_1095:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1096
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3103:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$4,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1096:
	cmpl	$48,%edx
	jne	L_3_1099
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3104:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1099:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1102
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3105:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1102:
	cmpl	$3,16-16(%esp)
	jne	L_3_1105
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3106:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1105:
	andl	$4,%esi
	jne	L_3_1108
	addl	%edi,%ebx
L_3_1108:
	cmpl	$0,16-16(%esp)
	je	L_3_1109
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1109:
	testl	%esi,%esi
	je	L_3_1112
	addl	%edi,%ebx
L_3_1112:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1113
	.align	2,0x90
L_3_1093:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1113:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3015:
	ret

FUNC(op_11bc)

	subl	$16,%esp
	shrl	$9,%eax
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,24-16(%esp)
	addl	$8,%eax
	movl	24-16(%esp),%edx
	movb	0x2164334A+3(%ecx),%cl
RR3_3000:
	addl	$4,%edx
	movb	%cl,31-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_3108:
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
	jne	L_3_1120
	movswl	%di,%edi
L_3_1120:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1121
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1122
	movl	%ebp,%ebx
L_3_1122:
	testl	$64,%esi
	je	L_3_1123
	movl	%ebp,%edi
L_3_1123:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1124
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3109:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1124:
	cmpl	$48,%edx
	jne	L_3_1127
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3110:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1127:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1130
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3111:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1130:
	cmpl	$3,16-16(%esp)
	jne	L_3_1133
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3112:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1133:
	andl	$4,%esi
	jne	L_3_1136
	addl	%edi,%ebx
L_3_1136:
	cmpl	$0,16-16(%esp)
	je	L_3_1137
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1137:
	testl	%esi,%esi
	je	L_3_1140
	addl	%edi,%ebx
L_3_1140:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1141
	.align	2,0x90
L_3_1121:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_3_1141:
	movb	31-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3016:
	ret

FUNC(op_11f0)

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
RR0_3114:
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
	jne	L_3_1198
	movswl	%di,%edi
L_3_1198:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1199
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1200
	movl	%ebp,%ebx
L_3_1200:
	testl	$64,%esi
	je	L_3_1201
	movl	%ebp,%edi
L_3_1201:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1202
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3115:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1202:
	cmpl	$48,%edx
	jne	L_3_1205
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3116:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1205:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1208
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3117:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1208:
	cmpl	$3,16-16(%esp)
	jne	L_3_1211
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3118:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1211:
	andl	$4,%esi
	jne	L_3_1214
	addl	%edi,%ebx
L_3_1214:
	cmpl	$0,16-16(%esp)
	je	L_3_1215
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1215:
	testl	%esi,%esi
	je	L_3_1218
	addl	%edi,%ebx
L_3_1218:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1219
	.align	2,0x90
L_3_1199:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_3_1219:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3119:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3017:
	ret

FUNC(op_11fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_3121:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1267
	movswl	%di,%edi
L_3_1267:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1268
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1269
	movl	%ebp,%ebx
L_3_1269:
	testl	$64,%esi
	je	L_3_1270
	movl	%ebp,%edi
L_3_1270:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1271
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3122:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1271:
	cmpl	$48,%edx
	jne	L_3_1274
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3123:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1274:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1277
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3124:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1277:
	cmpl	$3,16-16(%esp)
	jne	L_3_1280
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3125:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1280:
	andl	$4,%esi
	jne	L_3_1283
	addl	%edi,%ebx
L_3_1283:
	cmpl	$0,16-16(%esp)
	je	L_3_1284
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1284:
	testl	%esi,%esi
	je	L_3_1287
	addl	%edi,%ebx
L_3_1287:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1288
	.align	2,0x90
L_3_1268:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1288:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3126:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3018:
	ret

FUNC(op_13f0)

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
RR0_3128:
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
	jne	L_3_1355
	movswl	%di,%edi
L_3_1355:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1356
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1357
	movl	%ebp,%ebx
L_3_1357:
	testl	$64,%esi
	je	L_3_1358
	movl	%ebp,%edi
L_3_1358:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1359
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3129:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1359:
	cmpl	$48,%edx
	jne	L_3_1362
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3130:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1362:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1365
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3131:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1365:
	cmpl	$3,16-16(%esp)
	jne	L_3_1368
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3132:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1368:
	andl	$4,%esi
	jne	L_3_1371
	addl	%edi,%ebx
L_3_1371:
	cmpl	$0,16-16(%esp)
	je	L_3_1372
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1372:
	testl	%esi,%esi
	je	L_3_1375
	addl	%edi,%ebx
L_3_1375:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1376
	.align	2,0x90
L_3_1356:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_3_1376:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3133:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3019:
	ret

FUNC(op_13fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_3135:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1424
	movswl	%di,%edi
L_3_1424:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1425
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1426
	movl	%ebp,%ebx
L_3_1426:
	testl	$64,%esi
	je	L_3_1427
	movl	%ebp,%edi
L_3_1427:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1428
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3136:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1428:
	cmpl	$48,%edx
	jne	L_3_1431
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3137:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1431:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1434
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3138:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1434:
	cmpl	$3,16-16(%esp)
	jne	L_3_1437
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3139:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1437:
	andl	$4,%esi
	jne	L_3_1440
	addl	%edi,%ebx
L_3_1440:
	cmpl	$0,16-16(%esp)
	je	L_3_1441
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1441:
	testl	%esi,%esi
	je	L_3_1444
	addl	%edi,%ebx
L_3_1444:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1445
	.align	2,0x90
L_3_1425:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1445:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3140:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3020:
	ret

FUNC(op_2030)

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
RR0_3142:
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
	jne	L_3_1504
	movswl	%di,%edi
L_3_1504:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1505
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1506
	movl	%ebp,%ebx
L_3_1506:
	testl	$64,%esi
	je	L_3_1507
	movl	%ebp,%edi
L_3_1507:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1508
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3143:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1508:
	cmpl	$48,%edx
	jne	L_3_1511
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3144:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1511:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1514
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3145:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1514:
	cmpl	$3,16-16(%esp)
	jne	L_3_1517
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3146:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1517:
	andl	$4,%esi
	jne	L_3_1520
	addl	%edi,%ebx
L_3_1520:
	cmpl	$0,16-16(%esp)
	je	L_3_1521
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1521:
	testl	%esi,%esi
	je	L_3_1524
	addl	%edi,%ebx
L_3_1524:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_1525
	.align	2,0x90
L_3_1505:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_1525:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3021:
	ret

FUNC(op_203b)

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
RR0_3148:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1566
	movswl	%di,%edi
L_3_1566:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1567
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1568
	movl	%ebp,%ebx
L_3_1568:
	testl	$64,%esi
	je	L_3_1569
	movl	%ebp,%edi
L_3_1569:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1570
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3149:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1570:
	cmpl	$48,%edx
	jne	L_3_1573
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3150:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1573:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1576
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3151:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1576:
	cmpl	$3,16-16(%esp)
	jne	L_3_1579
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3152:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1579:
	andl	$4,%esi
	jne	L_3_1582
	addl	%edi,%ebx
L_3_1582:
	cmpl	$0,16-16(%esp)
	je	L_3_1583
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1583:
	testl	%esi,%esi
	je	L_3_1586
	addl	%edi,%ebx
L_3_1586:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_1587
	.align	2,0x90
L_3_1567:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_1587:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3022:
	ret

FUNC(op_2070)

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
RR0_3154:
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
	jne	L_3_1643
	movswl	%di,%edi
L_3_1643:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1644
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1645
	movl	%ebp,%ebx
L_3_1645:
	testl	$64,%esi
	je	L_3_1646
	movl	%ebp,%edi
L_3_1646:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1647
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3155:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1647:
	cmpl	$48,%edx
	jne	L_3_1650
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3156:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1650:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1653
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3157:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1653:
	cmpl	$3,16-16(%esp)
	jne	L_3_1656
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3158:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1656:
	andl	$4,%esi
	jne	L_3_1659
	addl	%edi,%ebx
L_3_1659:
	cmpl	$0,16-16(%esp)
	je	L_3_1660
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1660:
	testl	%esi,%esi
	je	L_3_1663
	addl	%edi,%ebx
L_3_1663:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1664
	.align	2,0x90
L_3_1644:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1664:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3023:
	ret

FUNC(op_207b)

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
RR0_3160:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1705
	movswl	%di,%edi
L_3_1705:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1706
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1707
	movl	%ebp,%ebx
L_3_1707:
	testl	$64,%esi
	je	L_3_1708
	movl	%ebp,%edi
L_3_1708:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1709
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3161:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1709:
	cmpl	$48,%edx
	jne	L_3_1712
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3162:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1712:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1715
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3163:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1715:
	cmpl	$3,16-16(%esp)
	jne	L_3_1718
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3164:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1718:
	andl	$4,%esi
	jne	L_3_1721
	addl	%edi,%ebx
L_3_1721:
	cmpl	$0,16-16(%esp)
	je	L_3_1722
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1722:
	testl	%esi,%esi
	je	L_3_1725
	addl	%edi,%ebx
L_3_1725:
	leal	(%ebp,%ebx),%edx
	jmp	L_3_1726
	.align	2,0x90
L_3_1706:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_3_1726:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3024:
	ret

FUNC(op_20b0)

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
RR0_3166:
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
	jne	L_3_1806
	movswl	%di,%edi
L_3_1806:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1807
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1808
	movl	%ebp,%ebx
L_3_1808:
	testl	$64,%esi
	je	L_3_1809
	movl	%ebp,%edi
L_3_1809:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1810
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3167:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1810:
	cmpl	$48,%edx
	jne	L_3_1813
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3168:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1813:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1816
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3169:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1816:
	cmpl	$3,16-16(%esp)
	jne	L_3_1819
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3170:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1819:
	andl	$4,%esi
	jne	L_3_1822
	addl	%edi,%ebx
L_3_1822:
	cmpl	$0,16-16(%esp)
	je	L_3_1823
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1823:
	testl	%esi,%esi
	je	L_3_1826
	addl	%edi,%ebx
L_3_1826:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_1827
	.align	2,0x90
L_3_1807:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_1827:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3025:
	ret

FUNC(op_20bb)

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
RR0_3172:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_1882
	movswl	%di,%edi
L_3_1882:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1883
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1884
	movl	%ebp,%ebx
L_3_1884:
	testl	$64,%esi
	je	L_3_1885
	movl	%ebp,%edi
L_3_1885:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1886
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3173:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1886:
	cmpl	$48,%edx
	jne	L_3_1889
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3174:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1889:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1892
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3175:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1892:
	cmpl	$3,16-16(%esp)
	jne	L_3_1895
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3176:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1895:
	andl	$4,%esi
	jne	L_3_1898
	addl	%edi,%ebx
L_3_1898:
	cmpl	$0,16-16(%esp)
	je	L_3_1899
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_1899:
	testl	%esi,%esi
	je	L_3_1902
	addl	%edi,%ebx
L_3_1902:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_1903
	.align	2,0x90
L_3_1883:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_1903:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
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
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3026:
	ret

FUNC(op_20f0)

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
RR0_3178:
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
	jne	L_3_1989
	movswl	%di,%edi
L_3_1989:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_1990
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_1991
	movl	%ebp,%ebx
L_3_1991:
	testl	$64,%esi
	je	L_3_1992
	movl	%ebp,%edi
L_3_1992:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_1993
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3179:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_1993:
	cmpl	$48,%edx
	jne	L_3_1996
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3180:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_1996:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_1999
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3181:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_1999:
	cmpl	$3,16-16(%esp)
	jne	L_3_2002
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3182:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_2002:
	andl	$4,%esi
	jne	L_3_2005
	addl	%edi,%ebx
L_3_2005:
	cmpl	$0,16-16(%esp)
	je	L_3_2006
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_2006:
	testl	%esi,%esi
	je	L_3_2009
	addl	%edi,%ebx
L_3_2009:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_2010
	.align	2,0x90
L_3_1990:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_2010:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	addl	$8,%edx
	movl	(%eax),%ebx
	sall	$2,%edx
	bswapl	%ebx
	movl	GLOBL(regs)(%edx),%eax
	leal	4(%eax),%ecx
	movl	%ecx,GLOBL(regs)(%edx)
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
	jl	JJ_3027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3027:
	ret

FUNC(op_20fb)

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
RR0_3184:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_3_2065
	movswl	%di,%edi
L_3_2065:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_3_2066
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_3_2067
	movl	%ebp,%ebx
L_3_2067:
	testl	$64,%esi
	je	L_3_2068
	movl	%ebp,%edi
L_3_2068:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_3_2069
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_3185:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_3_2069:
	cmpl	$48,%edx
	jne	L_3_2072
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3186:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_3_2072:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_3_2075
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_3187:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_2075:
	cmpl	$3,16-16(%esp)
	jne	L_3_2078
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_3188:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_3_2078:
	andl	$4,%esi
	jne	L_3_2081
	addl	%edi,%ebx
L_3_2081:
	cmpl	$0,16-16(%esp)
	je	L_3_2082
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_3_2082:
	testl	%esi,%esi
	je	L_3_2085
	addl	%edi,%ebx
L_3_2085:
	leal	(%ebp,%ebx),%eax
	jmp	L_3_2086
	.align	2,0x90
L_3_2066:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_3_2086:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%edx
	addl	$8,%edx
	movl	(%eax),%ebx
	sall	$2,%edx
	bswapl	%ebx
	movl	GLOBL(regs)(%edx),%eax
	leal	4(%eax),%ecx
	movl	%ecx,GLOBL(regs)(%edx)
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
	jl	JJ_3028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3028:
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


FUNC(op_10e8)

	movl	%eax,%edx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_3004:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	andl	$7,%ebx
	movzbl	(%eax,%edx),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%ebx
	movl	%esi,%ecx
	movl	%ebx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3029:
	ret

FUNC(op_10f8)

	movl	%eax,%ebx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3005:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%ebx
	movl	%esi,%ecx
	movl	%ebx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3030:
	ret

FUNC(op_10f9)

	movl	%eax,%ebx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_3006:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%ebx
	movl	%esi,%ecx
	movl	%ebx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3031:
	ret

FUNC(op_10fa)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%edx
	shrl	$9,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_3007:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%ebx
	movl	%esi,%ecx
	movl	%ebx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3032:
	ret

FUNC(op_10fc)

	subl	$4,%esp
	movl	%eax,%ebx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	movb	0x2164334A+3(%eax),%al
RR3_3001:
	andl	$7,%ebx
	movb	%al,7-4(%esp)
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%ebx
	movl	GLOBL(regs)(%eax),%edx
	addl	%edx,%ebx
	movl	%ebx,GLOBL(regs)(%eax)
	movb	7-4(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3033:
	ret

FUNC(op_1100)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	movb	(%ecx,%eax,4),%bl
	leal	8(%edx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%esi
	subl	%edx,%esi
	movl	%esi,%edx
	movl	%edx,(%eax,%ecx)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3034:
	ret

FUNC(op_1110)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%esi
	shrl	$9,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%esi,%eax,4),%cl
	movw	(%esi,%eax,4),%bx
	andl	$7,%edx
	movl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%ecx,%ecx
	movb	(%ebx,%eax),%cl
	leal	8(%edx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%esi),%edi
	subl	%edx,%edi
	movl	%edi,%edx
	movl	%edx,(%eax,%esi)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3035:
	ret

FUNC(op_1118)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%edi
	leal	8(%ebp),%ecx
	sall	$2,%ecx
	shrl	$9,%edi
	movl	%ecx,16-16(%esp)
	xorl	%eax,%eax
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	movzbl	(%ebx,%eax),%esi
	movl	$GLOBL(areg_byteinc),%ebx
	andl	$7,%edi
	addl	(%ebx,%ebp,4),%edx
	leal	8(%edi),%eax
	movl	%edx,GLOBL(regs)(%ecx)
	sall	$2,%eax
	movl	(%ebx,%edi,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%esi,%ecx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3036:
	ret

FUNC(op_1120)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(areg_byteinc),%ebp
	leal	8(%eax),%ecx
	movl	%edx,%edi
	leal	0(,%ecx,4),%ebx
	shrl	$9,%edi
	movl	%ebx,16-16(%esp)
	movl	$GLOBL(regs),%esi
	movl	(%ebp,%eax,4),%eax
	movl	(%ebx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%ecx,%eax),%bl
	andl	$7,%edi
	movl	%ebx,20-16(%esp)
	movl	16-16(%esp),%ecx
	leal	8(%edi),%eax
	movl	%edx,(%ecx,%esi)
	sall	$2,%eax
	movl	(%ebp,%edi,4),%edx
	movl	(%eax,%esi),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%edx,(%eax,%esi)
	movb	20-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,%bl
	movb	%bl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3037:
	ret

FUNC(op_1128)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_3008:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	andl	$7,%ecx
	movzbl	(%eax,%edx),%esi
	leal	8(%ecx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ecx,4),%edx
	movl	GLOBL(regs)(%eax),%ebx
	subl	%edx,%ebx
	movl	%ebx,%edx
	movl	%esi,%ebx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3038:
	ret

FUNC(op_1138)

	movl	%eax,%ebx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3009:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%esi,%ecx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3039:
	ret

FUNC(op_1139)

	movl	%eax,%ebx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_3010:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%esi,%ecx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3040:
	ret

FUNC(op_113a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%edx
	shrl	$9,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_3011:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ebx
	movzbl	(%edx,%eax),%esi
	leal	8(%ebx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%ebx,4),%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	movl	%ecx,%edx
	movl	%esi,%ecx
	movl	%edx,GLOBL(regs)(%eax)
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3041:
	ret

FUNC(op_113c)

	movl	%eax,%edx
	pushl	%ebx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%edx
	movb	0x2164334A+3(%eax),%bl
RR3_3002:
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%esi
	subl	%edx,%esi
	movl	%esi,%edx
	movl	%edx,(%eax,%ecx)
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3042:
	ret

FUNC(op_1140)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	movb	(%ecx,%eax,4),%bl
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_3012:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3043:
	ret

FUNC(op_1150)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%esi
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%esi,%eax,4),%cl
	movw	(%esi,%eax,4),%bx
	shrl	$9,%edx
	movl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%ecx,%ecx
	movb	(%ebx,%eax),%cl
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_3013:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%edx
	cwtl
	addl	(%esi,%edx,4),%eax
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3044:
	ret

FUNC(op_1158)

	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%esi
	leal	8(%ebp),%ecx
	shrl	$9,%esi
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%ebx,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_3014:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%esi
	cwtl
	andl	$255,%ebx
	addl	GLOBL(regs)(,%esi,4),%eax
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3045:
	ret

FUNC(op_1160)

	movl	%eax,%edx
	pushl	%esi
	pushl	%ebx
	andl	$7,%eax
	movl	%edx,%esi
	leal	8(%eax),%ecx
	shrl	$9,%esi
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_3015:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%esi
	cwtl
	andl	$255,%ebx
	addl	GLOBL(regs)(,%esi,4),%eax
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3207:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3046:
	ret

FUNC(op_1168)

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
RR2_3016:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	xorl	%ebx,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	addl	$8,%ecx
	movb	(%eax,%edx),%bl
	xorl	%eax,%eax
	movw	0x2164334A+4(%esi),%ax
RR4_3000:
	rolw	$8,%ax
	cwtl
	addl	(%edi,%ecx,4),%eax
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3208:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3047:
	ret

FUNC(op_1178)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_3017:
	rolw	$8,%dx
	movswl	%dx,%edx
	shrl	$9,%ecx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movzbl	(%edx,%eax),%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ebx),%ax
RR4_3001:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
	movl	%esi,%ebx
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3209:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3048:
	ret

FUNC(op_1179)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%edx
RR2_3018:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movzbl	(%edx,%eax),%esi
	xorl	%eax,%eax
	movw	0x2164334A+6(%ebx),%ax
RR6_3000:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ecx,4),%eax
	movl	%esi,%ebx
	testb	%bl,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3210:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3049:
	ret

FUNC(op_117a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%ecx
	shrl	$9,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_3019:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$7,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	addl	$8,%ebx
	movzbl	(%eax,%edx),%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_3002:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%ebx,4),%eax
	movl	%esi,%ecx
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3211:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3050:
	ret

FUNC(op_117c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+4(%eax),%bx
RR4_3003:
	rolw	$8,%bx
	andl	$7,%edx
	movb	0x2164334A+3(%eax),%cl
RR3_3003:
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3212:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3051:
	ret

FUNC(op_11c0)

	andl	$7,%eax
	movb	GLOBL(regs)(,%eax,4),%cl
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3020:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3213:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3052:
	ret

FUNC(op_11d0)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(R24)(,%edx,4),%eax
	movb	(%ecx,%eax),%cl
	andl	$255,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3021:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3214:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3053:
	ret

FUNC(op_11d8)

	movl	%eax,%edi
	pushl	%esi
	andl	$7,%edi
	pushl	%ebx
	leal	8(%edi),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%esi)
	andl	$255,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3022:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3215:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3054:
	ret

FUNC(op_11e0)

	andl	$7,%eax
	pushl	%ebx
	leal	8(%eax),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%esi)
	andl	$255,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3023:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3216:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3055:
	ret

FUNC(op_11e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_3024:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	xorl	%ecx,%ecx
	movb	(%eax,%edx),%cl
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_3004:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3217:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3056:
	ret

FUNC(op_11f8)

	movl	GLOBL(regs)+88,%ecx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_3025:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	xorl	%edx,%edx
	movw	0x2164334A+4(%ecx),%dx
RR4_3005:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3218:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3057:
	ret

FUNC(op_11f9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%edx
RR2_3026:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	xorl	%edx,%edx
	movw	0x2164334A+6(%ecx),%dx
RR6_3001:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3219:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3058:
	ret

FUNC(op_11fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_3027:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	xorl	%ebx,%ebx
	movb	(%eax,%edx),%bl
	xorl	%edx,%edx
	movw	0x2164334A+4(%ecx),%dx
RR4_3006:
	rolw	$8,%dx
	movswl	%dx,%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3220:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3059:
	ret

FUNC(op_11fc)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+4(%eax),%dx
RR4_3007:
	rolw	$8,%dx
	movswl	%dx,%edx
	movb	0x2164334A+3(%eax),%cl
RR3_3004:
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3221:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3060:
	ret

FUNC(op_13c0)

	andl	$7,%eax
	movb	GLOBL(regs)(,%eax,4),%cl
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_3028:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3222:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3061:
	ret

FUNC(op_13d0)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(R24)(,%edx,4),%eax
	movb	(%ecx,%eax),%cl
	movl	GLOBL(regs)+88,%eax
	andl	$255,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_3029:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3223:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3062:
	ret

FUNC(op_13d8)

	movl	%eax,%edi
	pushl	%esi
	andl	$7,%edi
	pushl	%ebx
	leal	8(%edi),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%esi)
	movl	GLOBL(regs)+88,%eax
	andl	$255,%ebx
	movl	0x2164334A+2(%eax),%edx
RR2_3030:
	bswapl	%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3224:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3063:
	ret

FUNC(op_13e0)

	andl	$7,%eax
	pushl	%ebx
	leal	8(%eax),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%esi)
	movl	GLOBL(regs)+88,%eax
	andl	$255,%ebx
	movl	0x2164334A+2(%eax),%edx
RR2_3031:
	bswapl	%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3225:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3064:
	ret

FUNC(op_13e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_3032:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	xorl	%ecx,%ecx
	movb	(%eax,%edx),%cl
	movl	0x2164334A+4(%ebx),%edx
RR4_3008:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3226:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3065:
	ret

FUNC(op_13f8)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_3033:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	0x2164334A+4(%ebx),%edx
RR4_3009:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3227:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3066:
	ret

FUNC(op_13f9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%edx
RR2_3034:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ebx,%ebx
	movb	(%edx,%eax),%bl
	movl	0x2164334A+6(%ecx),%edx
RR6_3002:
	bswapl	%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3228:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3067:
	ret

FUNC(op_13fa)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_3035:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	xorl	%ebx,%ebx
	movb	(%eax,%edx),%bl
	movl	0x2164334A+4(%ecx),%edx
RR4_3010:
	bswapl	%edx
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3229:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3068:
	ret

FUNC(op_13fc)

	movl	GLOBL(regs)+88,%eax
	movb	0x2164334A+3(%eax),%cl
RR3_3005:
	movl	0x2164334A+4(%eax),%edx
RR4_3011:
	bswapl	%edx
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3230:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3069:
	ret

FUNC(op_2000)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	movl	(%ecx,%edx,4),%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%edx,(%ecx,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3231:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3070:
	ret

FUNC(op_2008)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	shrl	$9,%edx
	addl	$8,%eax
	andl	$7,%edx
	movl	(%ecx,%eax,4),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3232:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3071:
	ret

FUNC(op_2010)

	movl	%eax,%edx
	movl	%edx,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$7,%eax
	shrl	$9,%ecx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	andl	$7,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3233:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3072:
	ret

FUNC(op_2018)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edi
	movl	(%ecx,%ebx),%edx
	shrl	$9,%edi
	movl	%edx,%eax
	movzbl	2(%ecx,%ebx),%esi
	andl	$65535,%eax
	andl	$7,%edi
	addl	GLOBL(R24)(,%esi,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%edx,(%ecx,%ebx)
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3234:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3073:
	ret

FUNC(op_2020)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%eax,%edi
	addl	$-4,%ecx
	shrl	$9,%edi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$7,%edi
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%ebx,%esi)
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3235:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3074:
	ret

FUNC(op_2028)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_3036:
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
	andl	$7,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3236:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3075:
	ret

FUNC(op_2038)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_3037:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$7,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3237:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3076:
	ret

FUNC(op_2039)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_3038:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$7,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3238:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3077:
	ret

FUNC(op_203a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3039:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$7,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3239:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3078:
	ret

FUNC(op_203c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%edx
	movl	0x2164334A+2(%eax),%eax
RR2_3040:
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movl	%eax,GLOBL(regs)(,%edx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3240:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3079:
	ret

FUNC(op_2040)

	movl	%eax,%ecx
	shrl	$9,%eax
	movl	$GLOBL(regs),%edx
	andl	$7,%ecx
	andl	$7,%eax
	movl	(%edx,%ecx,4),%ecx
	addl	$8,%eax
	movl	%ecx,(%edx,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3241:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3080:
	ret

FUNC(op_2048)

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
	jl	JJ_3081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3242:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3081:
	ret

FUNC(op_2050)

	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	movw	(%ebx,%eax,4),%ax
	shrl	$9,%edx
	andl	$65535,%eax
	andl	$7,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	addl	$8,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,(%ebx,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3243:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3082:
	ret

FUNC(op_2058)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	sall	$2,%ecx
	shrl	$9,%ebx
	movl	(%ecx,%esi),%edx
	movzbl	2(%ecx,%esi),%edi
	movl	%edx,%eax
	andl	$7,%ebx
	andl	$65535,%eax
	addl	$4,%edx
	addl	GLOBL(R24)(,%edi,4),%eax
	addl	$8,%ebx
	movl	(%eax),%eax
	movl	%edx,(%ecx,%esi)
	bswapl	%eax
	movl	%eax,(%esi,%ebx,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3244:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3083:
	ret

FUNC(op_2060)

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
	andl	$7,%esi
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%esi
	movl	(%eax),%eax
	movl	%ecx,(%ebx,%edi)
	bswapl	%eax
	movl	%eax,(%edi,%esi,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3245:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3084:
	ret

FUNC(op_2068)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_3041:
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
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,(%ebx,%ecx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3246:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3085:
	ret

FUNC(op_2078)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_3042:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3247:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3086:
	ret

FUNC(op_2079)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_3043:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$7,%ecx
	addl	GLOBL(R24)(%eax),%edx
	addl	$8,%ecx
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3248:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3087:
	ret

FUNC(op_207a)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3044:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3249:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3088:
	ret

FUNC(op_207c)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_3045:
	addl	$8,%eax
	bswapl	%edx
	movl	%edx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3250:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3089:
	ret

FUNC(op_2080)

	movl	%eax,%ecx
	shrl	$9,%eax
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	andl	$7,%ecx
	addl	$8,%eax
	movl	(%edx,%ecx,4),%ecx
	movl	(%edx,%eax,4),%edx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3251:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3090:
	ret

FUNC(op_2088)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movl	(%ecx,%edx,4),%ebx
	movl	(%ecx,%eax,4),%edx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3252:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3091:
	ret

FUNC(op_2090)

	movl	%eax,%edx
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
	movl	(%ebx,%edx,4),%edx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3253:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3092:
	ret

FUNC(op_2098)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	sall	$2,%ecx
	shrl	$9,%ebx
	movl	(%ecx,%esi),%edx
	movzbl	2(%ecx,%esi),%edi
	movl	%edx,%eax
	andl	$7,%ebx
	andl	$65535,%eax
	addl	$4,%edx
	addl	GLOBL(R24)(,%edi,4),%eax
	addl	$8,%ebx
	movl	(%eax),%edi
	movl	%edx,(%ecx,%esi)
	bswapl	%edi
	movl	(%esi,%ebx,4),%edx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3254:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3093:
	ret

FUNC(op_20a0)

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
	andl	$7,%esi
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%esi
	movl	(%eax),%ebp
	movl	%ecx,(%ebx,%edi)
	bswapl	%ebp
	movl	(%edi,%esi,4),%edx
	testl	%ebp,%ebp
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ebp
	movl	%ebp,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3255:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3094:
	ret

FUNC(op_20a8)

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
RR2_3046:
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
	movl	(%esi,%ecx,4),%edx
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
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3256:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3095:
	ret

FUNC(op_20b8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_3047:
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
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3257:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3096:
	ret

FUNC(op_20b9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_3048:
	bswapl	%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3258:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3097:
	ret

FUNC(op_20ba)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3049:
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
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3259:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3098:
	ret

FUNC(op_20bc)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$7,%eax
	movl	0x2164334A+2(%edx),%ecx
RR2_3050:
	addl	$8,%eax
	bswapl	%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
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
	jl	JJ_3099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3260:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3099:
	ret

FUNC(op_20c0)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	andl	$7,%edx
	sall	$2,%eax
	movl	(%ecx,%edx,4),%ebx
	movl	(%eax,%ecx),%edx
	leal	4(%edx),%esi
	movl	%esi,(%eax,%ecx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3261:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3100:
	ret

FUNC(op_20c8)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$9,%edx
	pushl	%ebx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	sall	$2,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	(%edx,%ecx),%eax
	leal	4(%eax),%esi
	movl	%esi,(%edx,%ecx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3262:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3101:
	ret

FUNC(op_20d0)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%bl
	shrl	$9,%edx
	movw	(%ecx,%eax,4),%ax
	andl	$7,%edx
	andl	$65535,%eax
	addl	$8,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	sall	$2,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	(%edx,%ecx),%eax
	leal	4(%eax),%esi
	movl	%esi,(%edx,%ecx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3263:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3102:
	ret

FUNC(op_20d8)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	%eax,%ebx
	andl	$7,%edx
	andl	$7,%ebx
	movl	$GLOBL(regs),%esi
	addl	$8,%ebx
	addl	$8,%edx
	sall	$2,%ebx
	sall	$2,%edx
	movl	(%ebx,%esi),%eax
	movzbl	2(%ebx,%esi),%edi
	andl	$65535,%eax
	movl	(%ebx,%esi),%ecx
	addl	GLOBL(R24)(,%edi,4),%eax
	addl	$4,%ecx
	movl	(%eax),%edi
	movl	%ecx,(%ebx,%esi)
	bswapl	%edi
	movl	(%edx,%esi),%eax
	leal	4(%eax),%ecx
	movl	%ecx,(%edx,%esi)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3264:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3103:
	ret

FUNC(op_20e0)

	subl	$4,%esp
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
	leal	4(%eax),%ebx
	movl	%ebx,(%ecx,%edi)
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
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_3104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3265:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3104:
	ret

FUNC(op_20e8)

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
RR2_3051:
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
	leal	4(%eax),%edi
	movl	%edi,(%ecx,%ebx)
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
	jl	JJ_3105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3266:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3105:
	ret

FUNC(op_20f8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_3052:
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
	leal	4(%eax),%esi
	movl	%esi,(%ecx,%edx)
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
	jl	JJ_3106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3267:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3106:
	ret

FUNC(op_20f9)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_3053:
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
	leal	4(%eax),%esi
	movl	%esi,(%ecx,%edx)
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3268:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3107:
	ret

FUNC(op_20fa)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_3054:
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
	movl	$GLOBL(regs),%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	(%ecx,%edx),%eax
	leal	4(%eax),%esi
	movl	%esi,(%ecx,%edx)
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
	jl	JJ_3108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3269:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3108:
	ret

FUNC(op_20fc)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$9,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_3055:
	sall	$2,%edx
	bswapl	%ebx
	movl	(%edx,%ecx),%eax
	leal	4(%eax),%esi
	movl	%esi,(%edx,%ecx)
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3270:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3109:
	ret

FUNC(op_2100)

	movl	%eax,%edx
	shrl	$9,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	andl	$7,%edx
	sall	$2,%eax
	movl	(%ecx,%edx,4),%ebx
	movl	(%eax,%ecx),%edx
	addl	$-4,%edx
	movl	%edx,(%eax,%ecx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3271:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3110:
	ret

FUNC(op_2108)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	sall	$2,%edx
	movl	(%ecx,%eax,4),%ebx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3272:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3111:
	ret

FUNC(op_2110)

	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%bl
	shrl	$9,%edx
	movw	(%ecx,%eax,4),%ax
	andl	$7,%edx
	andl	$65535,%eax
	addl	$8,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	sall	$2,%edx
	movl	(%eax),%ebx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3273:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3112:
	ret

FUNC(op_2118)

	movl	%eax,%ebx
	movl	%eax,%edx
	andl	$7,%ebx
	shrl	$9,%edx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	andl	$7,%edx
	movl	(%ebx,%esi),%ecx
	addl	$8,%edx
	movl	%ecx,%eax
	movzbl	2(%ebx,%esi),%edi
	andl	$65535,%eax
	sall	$2,%edx
	addl	GLOBL(R24)(,%edi,4),%eax
	addl	$4,%ecx
	movl	(%eax),%edi
	movl	%ecx,(%ebx,%esi)
	bswapl	%edi
	movl	(%edx,%esi),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%esi)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_3113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_3274:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_3113:
	ret

FUNC(Init020_03)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_3000-4
	movl	%eax,RR0_3001-4
	movl	%eax,RR0_3002-4
	movl	%eax,RR0_3003-4
	movl	%eax,RR0_3004-4
	movl	%eax,RR0_3005-4
	movl	%eax,RR0_3006-4
	movl	%eax,RR0_3007-4
	movl	%eax,RR0_3008-4
	movl	%eax,RR0_3009-4
	movl	%eax,RR0_3010-4
	movl	%eax,RR0_3011-4
	movl	%eax,RR0_3012-4
	movl	%eax,RR0_3013-4
	movl	%eax,RR0_3014-4
	movl	%eax,RR0_3015-4
	movl	%eax,RR0_3016-4
	movl	%eax,RR0_3017-4
	movl	%eax,RR0_3018-4
	movl	%eax,RR0_3019-4
	movl	%eax,RR0_3020-4
	movl	%eax,RR0_3021-4
	movl	%eax,RR0_3022-4
	movl	%eax,RR0_3023-4
	movl	%eax,RR0_3024-4
	movl	%eax,RR0_3025-4
	movl	%eax,RR0_3026-4
	movl	%eax,RR0_3027-4
	movl	%eax,RR0_3028-4
	movl	%eax,RR0_3029-4
	movl	%eax,RR0_3030-4
	movl	%eax,RR0_3031-4
	movl	%eax,RR0_3032-4
	movl	%eax,RR0_3033-4
	movl	%eax,RR0_3034-4
	movl	%eax,RR0_3035-4
	movl	%eax,RR0_3036-4
	movl	%eax,RR0_3037-4
	movl	%eax,RR0_3038-4
	movl	%eax,RR0_3039-4
	movl	%eax,RR0_3040-4
	movl	%eax,RR0_3041-4
	movl	%eax,RR0_3042-4
	movl	%eax,RR0_3043-4
	movl	%eax,RR0_3044-4
	movl	%eax,RR0_3045-4
	movl	%eax,RR0_3046-4
	movl	%eax,RR0_3047-4
	movl	%eax,RR0_3048-4
	movl	%eax,RR0_3049-4
	movl	%eax,RR0_3050-4
	movl	%eax,RR0_3051-4
	movl	%eax,RR0_3052-4
	movl	%eax,RR0_3053-4
	movl	%eax,RR0_3054-4
	movl	%eax,RR0_3055-4
	movl	%eax,RR0_3056-4
	movl	%eax,RR0_3057-4
	movl	%eax,RR0_3058-4
	movl	%eax,RR0_3059-4
	movl	%eax,RR0_3060-4
	movl	%eax,RR0_3061-4
	movl	%eax,RR0_3062-4
	movl	%eax,RR0_3063-4
	movl	%eax,RR0_3064-4
	movl	%eax,RR0_3065-4
	movl	%eax,RR0_3066-4
	movl	%eax,RR0_3067-4
	movl	%eax,RR0_3068-4
	movl	%eax,RR0_3069-4
	movl	%eax,RR0_3070-4
	movl	%eax,RR0_3071-4
	movl	%eax,RR0_3072-4
	movl	%eax,RR0_3073-4
	movl	%eax,RR0_3074-4
	movl	%eax,RR0_3075-4
	movl	%eax,RR0_3076-4
	movl	%eax,RR0_3077-4
	movl	%eax,RR0_3078-4
	movl	%eax,RR0_3079-4
	movl	%eax,RR0_3080-4
	movl	%eax,RR0_3081-4
	movl	%eax,RR0_3082-4
	movl	%eax,RR0_3083-4
	movl	%eax,RR0_3084-4
	movl	%eax,RR0_3085-4
	movl	%eax,RR0_3086-4
	movl	%eax,RR0_3087-4
	movl	%eax,RR0_3088-4
	movl	%eax,RR0_3089-4
	movl	%eax,RR0_3090-4
	movl	%eax,RR0_3091-4
	movl	%eax,RR0_3092-4
	movl	%eax,RR0_3093-4
	movl	%eax,RR0_3094-4
	movl	%eax,RR0_3095-4
	movl	%eax,RR0_3096-4
	movl	%eax,RR0_3097-4
	movl	%eax,RR0_3098-4
	movl	%eax,RR0_3099-4
	movl	%eax,RR0_3100-4
	movl	%eax,RR0_3101-4
	movl	%eax,RR0_3102-4
	movl	%eax,RR0_3103-4
	movl	%eax,RR0_3104-4
	movl	%eax,RR0_3105-4
	movl	%eax,RR0_3106-4
	movl	%eax,RR0_3107-4
	movl	%eax,RR0_3108-4
	movl	%eax,RR0_3109-4
	movl	%eax,RR0_3110-4
	movl	%eax,RR0_3111-4
	movl	%eax,RR0_3112-4
	movl	%eax,RR0_3113-4
	movl	%eax,RR0_3114-4
	movl	%eax,RR0_3115-4
	movl	%eax,RR0_3116-4
	movl	%eax,RR0_3117-4
	movl	%eax,RR0_3118-4
	movl	%eax,RR0_3119-4
	movl	%eax,RR0_3120-4
	movl	%eax,RR0_3121-4
	movl	%eax,RR0_3122-4
	movl	%eax,RR0_3123-4
	movl	%eax,RR0_3124-4
	movl	%eax,RR0_3125-4
	movl	%eax,RR0_3126-4
	movl	%eax,RR0_3127-4
	movl	%eax,RR0_3128-4
	movl	%eax,RR0_3129-4
	movl	%eax,RR0_3130-4
	movl	%eax,RR0_3131-4
	movl	%eax,RR0_3132-4
	movl	%eax,RR0_3133-4
	movl	%eax,RR0_3134-4
	movl	%eax,RR0_3135-4
	movl	%eax,RR0_3136-4
	movl	%eax,RR0_3137-4
	movl	%eax,RR0_3138-4
	movl	%eax,RR0_3139-4
	movl	%eax,RR0_3140-4
	movl	%eax,RR0_3141-4
	movl	%eax,RR0_3142-4
	movl	%eax,RR0_3143-4
	movl	%eax,RR0_3144-4
	movl	%eax,RR0_3145-4
	movl	%eax,RR0_3146-4
	movl	%eax,RR0_3147-4
	movl	%eax,RR0_3148-4
	movl	%eax,RR0_3149-4
	movl	%eax,RR0_3150-4
	movl	%eax,RR0_3151-4
	movl	%eax,RR0_3152-4
	movl	%eax,RR0_3153-4
	movl	%eax,RR0_3154-4
	movl	%eax,RR0_3155-4
	movl	%eax,RR0_3156-4
	movl	%eax,RR0_3157-4
	movl	%eax,RR0_3158-4
	movl	%eax,RR0_3159-4
	movl	%eax,RR0_3160-4
	movl	%eax,RR0_3161-4
	movl	%eax,RR0_3162-4
	movl	%eax,RR0_3163-4
	movl	%eax,RR0_3164-4
	movl	%eax,RR0_3165-4
	movl	%eax,RR0_3166-4
	movl	%eax,RR0_3167-4
	movl	%eax,RR0_3168-4
	movl	%eax,RR0_3169-4
	movl	%eax,RR0_3170-4
	movl	%eax,RR0_3171-4
	movl	%eax,RR0_3172-4
	movl	%eax,RR0_3173-4
	movl	%eax,RR0_3174-4
	movl	%eax,RR0_3175-4
	movl	%eax,RR0_3176-4
	movl	%eax,RR0_3177-4
	movl	%eax,RR0_3178-4
	movl	%eax,RR0_3179-4
	movl	%eax,RR0_3180-4
	movl	%eax,RR0_3181-4
	movl	%eax,RR0_3182-4
	movl	%eax,RR0_3183-4
	movl	%eax,RR0_3184-4
	movl	%eax,RR0_3185-4
	movl	%eax,RR0_3186-4
	movl	%eax,RR0_3187-4
	movl	%eax,RR0_3188-4
	movl	%eax,RR0_3189-4
	movl	%eax,RR0_3190-4
	movl	%eax,RR0_3191-4
	movl	%eax,RR0_3192-4
	movl	%eax,RR0_3193-4
	movl	%eax,RR0_3194-4
	movl	%eax,RR0_3195-4
	movl	%eax,RR0_3196-4
	movl	%eax,RR0_3197-4
	movl	%eax,RR0_3198-4
	movl	%eax,RR0_3199-4
	movl	%eax,RR0_3200-4
	movl	%eax,RR0_3201-4
	movl	%eax,RR0_3202-4
	movl	%eax,RR0_3203-4
	movl	%eax,RR0_3204-4
	movl	%eax,RR0_3205-4
	movl	%eax,RR0_3206-4
	movl	%eax,RR0_3207-4
	movl	%eax,RR0_3208-4
	movl	%eax,RR0_3209-4
	movl	%eax,RR0_3210-4
	movl	%eax,RR0_3211-4
	movl	%eax,RR0_3212-4
	movl	%eax,RR0_3213-4
	movl	%eax,RR0_3214-4
	movl	%eax,RR0_3215-4
	movl	%eax,RR0_3216-4
	movl	%eax,RR0_3217-4
	movl	%eax,RR0_3218-4
	movl	%eax,RR0_3219-4
	movl	%eax,RR0_3220-4
	movl	%eax,RR0_3221-4
	movl	%eax,RR0_3222-4
	movl	%eax,RR0_3223-4
	movl	%eax,RR0_3224-4
	movl	%eax,RR0_3225-4
	movl	%eax,RR0_3226-4
	movl	%eax,RR0_3227-4
	movl	%eax,RR0_3228-4
	movl	%eax,RR0_3229-4
	movl	%eax,RR0_3230-4
	movl	%eax,RR0_3231-4
	movl	%eax,RR0_3232-4
	movl	%eax,RR0_3233-4
	movl	%eax,RR0_3234-4
	movl	%eax,RR0_3235-4
	movl	%eax,RR0_3236-4
	movl	%eax,RR0_3237-4
	movl	%eax,RR0_3238-4
	movl	%eax,RR0_3239-4
	movl	%eax,RR0_3240-4
	movl	%eax,RR0_3241-4
	movl	%eax,RR0_3242-4
	movl	%eax,RR0_3243-4
	movl	%eax,RR0_3244-4
	movl	%eax,RR0_3245-4
	movl	%eax,RR0_3246-4
	movl	%eax,RR0_3247-4
	movl	%eax,RR0_3248-4
	movl	%eax,RR0_3249-4
	movl	%eax,RR0_3250-4
	movl	%eax,RR0_3251-4
	movl	%eax,RR0_3252-4
	movl	%eax,RR0_3253-4
	movl	%eax,RR0_3254-4
	movl	%eax,RR0_3255-4
	movl	%eax,RR0_3256-4
	movl	%eax,RR0_3257-4
	movl	%eax,RR0_3258-4
	movl	%eax,RR0_3259-4
	movl	%eax,RR0_3260-4
	movl	%eax,RR0_3261-4
	movl	%eax,RR0_3262-4
	movl	%eax,RR0_3263-4
	movl	%eax,RR0_3264-4
	movl	%eax,RR0_3265-4
	movl	%eax,RR0_3266-4
	movl	%eax,RR0_3267-4
	movl	%eax,RR0_3268-4
	movl	%eax,RR0_3269-4
	movl	%eax,RR0_3270-4
	movl	%eax,RR0_3271-4
	movl	%eax,RR0_3272-4
	movl	%eax,RR0_3273-4
	movl	%eax,RR0_3274-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_3000-4
	movl	%eax,RR2_3001-4
	movl	%eax,RR2_3002-4
	movl	%eax,RR2_3003-4
	movl	%eax,RR2_3004-4
	movl	%eax,RR2_3005-4
	movl	%eax,RR2_3006-4
	movl	%eax,RR2_3007-4
	movl	%eax,RR2_3008-4
	movl	%eax,RR2_3009-4
	movl	%eax,RR2_3010-4
	movl	%eax,RR2_3011-4
	movl	%eax,RR2_3012-4
	movl	%eax,RR2_3013-4
	movl	%eax,RR2_3014-4
	movl	%eax,RR2_3015-4
	movl	%eax,RR2_3016-4
	movl	%eax,RR2_3017-4
	movl	%eax,RR2_3018-4
	movl	%eax,RR2_3019-4
	movl	%eax,RR2_3020-4
	movl	%eax,RR2_3021-4
	movl	%eax,RR2_3022-4
	movl	%eax,RR2_3023-4
	movl	%eax,RR2_3024-4
	movl	%eax,RR2_3025-4
	movl	%eax,RR2_3026-4
	movl	%eax,RR2_3027-4
	movl	%eax,RR2_3028-4
	movl	%eax,RR2_3029-4
	movl	%eax,RR2_3030-4
	movl	%eax,RR2_3031-4
	movl	%eax,RR2_3032-4
	movl	%eax,RR2_3033-4
	movl	%eax,RR2_3034-4
	movl	%eax,RR2_3035-4
	movl	%eax,RR2_3036-4
	movl	%eax,RR2_3037-4
	movl	%eax,RR2_3038-4
	movl	%eax,RR2_3039-4
	movl	%eax,RR2_3040-4
	movl	%eax,RR2_3041-4
	movl	%eax,RR2_3042-4
	movl	%eax,RR2_3043-4
	movl	%eax,RR2_3044-4
	movl	%eax,RR2_3045-4
	movl	%eax,RR2_3046-4
	movl	%eax,RR2_3047-4
	movl	%eax,RR2_3048-4
	movl	%eax,RR2_3049-4
	movl	%eax,RR2_3050-4
	movl	%eax,RR2_3051-4
	movl	%eax,RR2_3052-4
	movl	%eax,RR2_3053-4
	movl	%eax,RR2_3054-4
	movl	%eax,RR2_3055-4
	incl	%eax
	movl	%eax,RR3_3000-4
	movl	%eax,RR3_3001-4
	movl	%eax,RR3_3002-4
	movl	%eax,RR3_3003-4
	movl	%eax,RR3_3004-4
	movl	%eax,RR3_3005-4
	incl	%eax
	movl	%eax,RR4_3000-4
	movl	%eax,RR4_3001-4
	movl	%eax,RR4_3002-4
	movl	%eax,RR4_3003-4
	movl	%eax,RR4_3004-4
	movl	%eax,RR4_3005-4
	movl	%eax,RR4_3006-4
	movl	%eax,RR4_3007-4
	movl	%eax,RR4_3008-4
	movl	%eax,RR4_3009-4
	movl	%eax,RR4_3010-4
	movl	%eax,RR4_3011-4
	incl	%eax
	incl	%eax
	movl	%eax,RR6_3000-4
	movl	%eax,RR6_3001-4
	movl	%eax,RR6_3002-4
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
