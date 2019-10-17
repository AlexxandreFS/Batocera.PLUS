

FUNC(op_4eb0)

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
RR0_8000:
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
	jne	L_8_388
	movswl	%di,%edi
L_8_388:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_389
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_390
	movl	%ebp,%ebx
L_8_390:
	testl	$64,%esi
	je	L_8_391
	movl	%ebp,%edi
L_8_391:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_392
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_392:
	cmpl	$48,%edx
	jne	L_8_395
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_395:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_398
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_398:
	cmpl	$3,16-16(%esp)
	jne	L_8_401
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_401:
	andl	$4,%esi
	jne	L_8_404
	addl	%edi,%ebx
L_8_404:
	cmpl	$0,16-16(%esp)
	je	L_8_405
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_405:
	testl	%esi,%esi
	je	L_8_408
	addl	%edi,%ebx
L_8_408:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_409
	.align	2,0x90
L_8_389:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_8_409:
	pushl	%eax
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8000:
	ret

FUNC(op_4ebb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_8006:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_8_443
	movswl	%di,%edi
L_8_443:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_444
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_445
	movl	%ebp,%ebx
L_8_445:
	testl	$64,%esi
	je	L_8_446
	movl	%ebp,%edi
L_8_446:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_447
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_447:
	cmpl	$48,%edx
	jne	L_8_450
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_450:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_453
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_453:
	cmpl	$3,16-16(%esp)
	jne	L_8_456
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_456:
	andl	$4,%esi
	jne	L_8_459
	addl	%edi,%ebx
L_8_459:
	cmpl	$0,16-16(%esp)
	je	L_8_460
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_460:
	testl	%esi,%esi
	je	L_8_463
	addl	%edi,%ebx
L_8_463:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_464
	.align	2,0x90
L_8_444:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_464:
	pushl	%eax
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8001:
	ret

FUNC(op_4ef0)

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
RR0_8012:
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
	jne	L_8_485
	movswl	%di,%edi
L_8_485:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_486
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_487
	movl	%ebp,%ebx
L_8_487:
	testl	$64,%esi
	je	L_8_488
	movl	%ebp,%edi
L_8_488:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_489
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_489:
	cmpl	$48,%edx
	jne	L_8_492
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_492:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_495
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_495:
	cmpl	$3,16-16(%esp)
	jne	L_8_498
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_498:
	andl	$4,%esi
	jne	L_8_501
	addl	%edi,%ebx
L_8_501:
	cmpl	$0,16-16(%esp)
	je	L_8_502
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_502:
	testl	%esi,%esi
	je	L_8_505
	addl	%edi,%ebx
L_8_505:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_506
	.align	2,0x90
L_8_486:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_8_506:
	movl	%eax,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8002:
	ret

FUNC(op_4efb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_8018:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_8_540
	movswl	%di,%edi
L_8_540:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_541
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_542
	movl	%ebp,%ebx
L_8_542:
	testl	$64,%esi
	je	L_8_543
	movl	%ebp,%edi
L_8_543:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_544
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8019:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_544:
	cmpl	$48,%edx
	jne	L_8_547
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_547:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_550
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_550:
	cmpl	$3,16-16(%esp)
	jne	L_8_553
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_553:
	andl	$4,%esi
	jne	L_8_556
	addl	%edi,%ebx
L_8_556:
	cmpl	$0,16-16(%esp)
	je	L_8_557
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_557:
	testl	%esi,%esi
	je	L_8_560
	addl	%edi,%ebx
L_8_560:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_561
	.align	2,0x90
L_8_541:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_561:
	movl	%eax,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8003:
	ret

FUNC(op_5030)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8024:
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
	jne	L_8_606
	movswl	%di,%edi
L_8_606:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_607
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_608
	movl	%ebp,%ebx
L_8_608:
	testl	$64,%esi
	je	L_8_609
	movl	%ebp,%edi
L_8_609:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_610
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8025:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_610:
	cmpl	$48,%edx
	jne	L_8_613
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_613:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_616
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_616:
	cmpl	$3,16-16(%esp)
	jne	L_8_619
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_619:
	andl	$4,%esi
	jne	L_8_622
	addl	%edi,%ebx
L_8_622:
	cmpl	$0,16-16(%esp)
	je	L_8_623
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_623:
	testl	%esi,%esi
	je	L_8_626
	addl	%edi,%ebx
L_8_626:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_627
	.align	2,0x90
L_8_607:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_8_627:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	addb	28-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8004:
	ret

FUNC(op_5070)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8030:
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
	jne	L_8_713
	movswl	%di,%edi
L_8_713:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_714
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_715
	movl	%ebp,%ebx
L_8_715:
	testl	$64,%esi
	je	L_8_716
	movl	%ebp,%edi
L_8_716:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_717
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_717:
	cmpl	$48,%edx
	jne	L_8_720
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_720:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_723
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_723:
	cmpl	$3,16-16(%esp)
	jne	L_8_726
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_726:
	andl	$4,%esi
	jne	L_8_729
	addl	%edi,%ebx
L_8_729:
	cmpl	$0,16-16(%esp)
	je	L_8_730
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_730:
	testl	%esi,%esi
	je	L_8_733
	addl	%edi,%ebx
L_8_733:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_734
	.align	2,0x90
L_8_714:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_734:
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
	addw	28-16(%esp),%ax
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
	jl	JJ_8005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8005:
	ret

FUNC(op_50b0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8036:
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
	jne	L_8_830
	movswl	%di,%edi
L_8_830:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_831
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_832
	movl	%ebp,%ebx
L_8_832:
	testl	$64,%esi
	je	L_8_833
	movl	%ebp,%edi
L_8_833:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_834
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8037:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_834:
	cmpl	$48,%edx
	jne	L_8_837
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_837:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_840
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_840:
	cmpl	$3,16-16(%esp)
	jne	L_8_843
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_843:
	andl	$4,%esi
	jne	L_8_846
	addl	%edi,%ebx
L_8_846:
	cmpl	$0,16-16(%esp)
	je	L_8_847
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_847:
	testl	%esi,%esi
	je	L_8_850
	addl	%edi,%ebx
L_8_850:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_851
	.align	2,0x90
L_8_831:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_851:
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
	jl	JJ_8006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8006:
	ret

FUNC(op_50c0)

	andl	$7,%eax
	movb	$255,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8042:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8007:
	ret

FUNC(op_50c8)

	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8008:
	ret

FUNC(op_50d0)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(W24)(,%edx,4),%eax
	movb	$-1,(%ecx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8044:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8009:
	ret

FUNC(op_50d8)

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
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$-1,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8045:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8010:
	ret

FUNC(op_50e0)

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
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$-1,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8046:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8011:
	ret

FUNC(op_50e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_8000:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	$-1,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8012:
	ret

FUNC(op_50f0)

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
RR0_8048:
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
	jne	L_8_1063
	movswl	%di,%edi
L_8_1063:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_1064
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_1065
	movl	%ebp,%ebx
L_8_1065:
	testl	$64,%esi
	je	L_8_1066
	movl	%ebp,%edi
L_8_1066:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_1067
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8049:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_1067:
	cmpl	$48,%edx
	jne	L_8_1070
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8050:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_1070:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_1073
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8051:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1073:
	cmpl	$3,16-16(%esp)
	jne	L_8_1076
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8052:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1076:
	andl	$4,%esi
	jne	L_8_1079
	addl	%edi,%ebx
L_8_1079:
	cmpl	$0,16-16(%esp)
	je	L_8_1080
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_1080:
	testl	%esi,%esi
	je	L_8_1083
	addl	%edi,%ebx
L_8_1083:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_1090
	.align	2,0x90
L_8_1064:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_8_1090:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$-1,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8013:
	ret

FUNC(op_50f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_8001:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$-1,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8054:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8014:
	ret

FUNC(op_50f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_8002:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$-1,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8015:
	ret

FUNC(op_50fa)

	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8056:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8016:
	ret

FUNC(op_50fb)

	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8057:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8017:
	ret

FUNC(op_50fc)

	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8018:
	ret

FUNC(op_5130)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8059:
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
	jne	L_8_1301
	movswl	%di,%edi
L_8_1301:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_1302
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_1303
	movl	%ebp,%ebx
L_8_1303:
	testl	$64,%esi
	je	L_8_1304
	movl	%ebp,%edi
L_8_1304:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_1305
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8060:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_1305:
	cmpl	$48,%edx
	jne	L_8_1308
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8061:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_1308:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_1311
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8062:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1311:
	cmpl	$3,16-16(%esp)
	jne	L_8_1314
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8063:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1314:
	andl	$4,%esi
	jne	L_8_1317
	addl	%edi,%ebx
L_8_1317:
	cmpl	$0,16-16(%esp)
	je	L_8_1318
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_1318:
	testl	%esi,%esi
	je	L_8_1321
	addl	%edi,%ebx
L_8_1321:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_1322
	.align	2,0x90
L_8_1302:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_8_1322:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	subb	28-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8019:
	ret

FUNC(op_5170)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8065:
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
	jne	L_8_1408
	movswl	%di,%edi
L_8_1408:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_1409
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_1410
	movl	%ebp,%ebx
L_8_1410:
	testl	$64,%esi
	je	L_8_1411
	movl	%ebp,%edi
L_8_1411:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_1412
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8066:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_1412:
	cmpl	$48,%edx
	jne	L_8_1415
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8067:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_1415:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_1418
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8068:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1418:
	cmpl	$3,16-16(%esp)
	jne	L_8_1421
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8069:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1421:
	andl	$4,%esi
	jne	L_8_1424
	addl	%edi,%ebx
L_8_1424:
	cmpl	$0,16-16(%esp)
	je	L_8_1425
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_1425:
	testl	%esi,%esi
	je	L_8_1428
	addl	%edi,%ebx
L_8_1428:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_1429
	.align	2,0x90
L_8_1409:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_1429:
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
	subw	28-16(%esp),%ax
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
	jl	JJ_8020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8070:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8020:
	ret

FUNC(op_51b0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	GLOBL(imm8_table)(%eax),%eax
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_8071:
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
	jne	L_8_1525
	movswl	%di,%edi
L_8_1525:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_1526
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_1527
	movl	%ebp,%ebx
L_8_1527:
	testl	$64,%esi
	je	L_8_1528
	movl	%ebp,%edi
L_8_1528:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_1529
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8072:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_1529:
	cmpl	$48,%edx
	jne	L_8_1532
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8073:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_1532:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_1535
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8074:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1535:
	cmpl	$3,16-16(%esp)
	jne	L_8_1538
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8075:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1538:
	andl	$4,%esi
	jne	L_8_1541
	addl	%edi,%ebx
L_8_1541:
	cmpl	$0,16-16(%esp)
	je	L_8_1542
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_1542:
	testl	%esi,%esi
	je	L_8_1545
	addl	%edi,%ebx
L_8_1545:
	leal	(%ebp,%ebx),%eax
	jmp	L_8_1546
	.align	2,0x90
L_8_1526:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_8_1546:
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
	jl	JJ_8021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8021:
	ret

FUNC(op_51c0)

	andl	$7,%eax
	movb	$0,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8022:
	ret

FUNC(op_51c8)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	sall	$2,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8003:
	rolw	$8,%si
	movw	(%edx,%ecx),%bx
	movl	%esi,%eax
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_8_1611
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_8_1636
	.align	2,0x90
L_8_1611:
	addl	$4,GLOBL(regs)+88
L_8_1636:
	popl	%eax
	decl	%eax
	jl	JJ_8023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8023:
	ret

FUNC(op_51d0)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(W24)(,%edx,4),%eax
	movb	$0,(%ecx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8024:
	ret

FUNC(op_51d8)

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
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8025:
	ret

FUNC(op_51e0)

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
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8026:
	ret

FUNC(op_51e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_8004:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	$0,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8027:
	ret

FUNC(op_51f0)

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
RR0_8083:
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
	jne	L_8_1758
	movswl	%di,%edi
L_8_1758:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_1759
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_1760
	movl	%ebp,%ebx
L_8_1760:
	testl	$64,%esi
	je	L_8_1761
	movl	%ebp,%edi
L_8_1761:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_1762
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8084:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_1762:
	cmpl	$48,%edx
	jne	L_8_1765
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8085:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_1765:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_1768
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8086:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1768:
	cmpl	$3,16-16(%esp)
	jne	L_8_1771
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8087:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_1771:
	andl	$4,%esi
	jne	L_8_1774
	addl	%edi,%ebx
L_8_1774:
	cmpl	$0,16-16(%esp)
	je	L_8_1775
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_1775:
	testl	%esi,%esi
	je	L_8_1778
	addl	%edi,%ebx
L_8_1778:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_1786
	.align	2,0x90
L_8_1759:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_8_1786:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8028:
	ret

FUNC(op_51f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_8005:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8089:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8029:
	ret

FUNC(op_51f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_8006:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8030:
	ret

FUNC(op_51fa)

	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8031:
	ret

FUNC(op_51fb)

	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8092:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8032:
	ret

FUNC(op_51fc)

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8093:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8033:
	ret

FUNC(op_52c0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$65,regflags
	jne	L_8_1956
	movl	$255,%edx
L_8_1956:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8034:
	ret

FUNC(op_52c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8007:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$65,regflags
	je	L_8_1985
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_8_1985
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_8_2010
	.align	2,0x90
L_8_1985:
	addl	$4,GLOBL(regs)+88
L_8_2010:
	popl	%eax
	decl	%eax
	jl	JJ_8035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8035:
	ret

FUNC(op_52d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$65,regflags
	jne	L_8_2013
	movl	$255,%ecx
L_8_2013:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8036:
	ret

FUNC(op_52d8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$65,regflags
	jne	L_8_2042
	movl	$255,%ecx
L_8_2042:
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
	jl	JJ_8037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8037:
	ret

FUNC(op_52e0)

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
	testb	$65,regflags
	jne	L_8_2071
	movl	$255,%ecx
L_8_2071:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8038:
	ret

FUNC(op_52e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_8008:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$65,regflags
	jne	L_8_2101
	movl	$255,%ecx
L_8_2101:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8039:
	ret

FUNC(op_52f0)

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
RR0_8100:
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
	jne	L_8_2132
	movswl	%di,%edi
L_8_2132:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_2133
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_2134
	movl	%ebp,%ebx
L_8_2134:
	testl	$64,%esi
	je	L_8_2135
	movl	%ebp,%edi
L_8_2135:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_2136
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8101:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_2136:
	cmpl	$48,%edx
	jne	L_8_2139
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8102:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_2139:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_2142
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8103:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_2142:
	cmpl	$3,16-16(%esp)
	jne	L_8_2145
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8104:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_2145:
	andl	$4,%esi
	jne	L_8_2148
	addl	%edi,%ebx
L_8_2148:
	cmpl	$0,16-16(%esp)
	je	L_8_2149
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_2149:
	testl	%esi,%esi
	je	L_8_2152
	addl	%edi,%ebx
L_8_2152:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_2161
	.align	2,0x90
L_8_2133:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_8_2161:
	xorl	%ebx,%ebx
	testb	$65,regflags
	jne	L_8_2155
	movl	$255,%ebx
L_8_2155:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8040:
	ret

FUNC(op_52f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_8009:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$65,regflags
	jne	L_8_2185
	movl	$255,%ecx
L_8_2185:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8041:
	ret

FUNC(op_52f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_8010:
	bswapl	%edx
	testb	$65,regflags
	jne	L_8_2215
	movl	$255,%ecx
L_8_2215:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8042:
	ret

FUNC(op_52fa)

	testb	$65,regflags
	jne	L_8_2245
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8043:
	ret
	.align	2,0x90
L_8_2245:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8044:
	ret

FUNC(op_52fb)

	testb	$65,regflags
	jne	L_8_2274
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8045:
	ret
	.align	2,0x90
L_8_2274:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8046:
	ret

FUNC(op_52fc)

	testb	$65,regflags
	jne	L_8_2302
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8047:
	ret
	.align	2,0x90
L_8_2302:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8048:
	ret

FUNC(op_53c0)

	andl	$7,%eax
	xorl	%edx,%edx
	testb	$65,regflags
	je	L_8_2330
	movl	$255,%edx
L_8_2330:
	movb	%dl,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8049:
	ret

FUNC(op_53c8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	movw	(%edx,%ecx),%bx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8011:
	rolw	$8,%si
	movl	%esi,%eax
	testb	$65,regflags
	jne	L_8_2359
	movl	%ebx,%esi
	decl	%esi
	movw	%si,(%edx,%ecx)
	testw	%bx,%bx
	je	L_8_2359
	movl	GLOBL(regs)+88,%edx
	cwtl
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_8_2384
	.align	2,0x90
L_8_2359:
	addl	$4,GLOBL(regs)+88
L_8_2384:
	popl	%eax
	decl	%eax
	jl	JJ_8050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8050:
	ret

FUNC(op_53d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	testb	$65,regflags
	je	L_8_2387
	movl	$255,%ecx
L_8_2387:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8051:
	ret

FUNC(op_53d8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%ecx,%ecx
	testb	$65,regflags
	je	L_8_2416
	movl	$255,%ecx
L_8_2416:
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
	jl	JJ_8052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8052:
	ret

FUNC(op_53e0)

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
	testb	$65,regflags
	je	L_8_2445
	movl	$255,%ecx
L_8_2445:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8053:
	ret

FUNC(op_53e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_8012:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	xorl	%ecx,%ecx
	addl	%eax,%edx
	testb	$65,regflags
	je	L_8_2475
	movl	$255,%ecx
L_8_2475:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8054:
	ret

FUNC(op_53f0)

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
RR0_8120:
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
	jne	L_8_2506
	movswl	%di,%edi
L_8_2506:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_8_2507
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_8_2508
	movl	%ebp,%ebx
L_8_2508:
	testl	$64,%esi
	je	L_8_2509
	movl	%ebp,%edi
L_8_2509:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_8_2510
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_8121:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_8_2510:
	cmpl	$48,%edx
	jne	L_8_2513
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8122:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_8_2513:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_8_2516
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_8123:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_2516:
	cmpl	$3,16-16(%esp)
	jne	L_8_2519
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_8124:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_8_2519:
	andl	$4,%esi
	jne	L_8_2522
	addl	%edi,%ebx
L_8_2522:
	cmpl	$0,16-16(%esp)
	je	L_8_2523
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_8_2523:
	testl	%esi,%esi
	je	L_8_2526
	addl	%edi,%ebx
L_8_2526:
	leal	(%ebp,%ebx),%edx
	jmp	L_8_2536
	.align	2,0x90
L_8_2507:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_8_2536:
	xorl	%ebx,%ebx
	testb	$65,regflags
	je	L_8_2529
	movl	$255,%ebx
L_8_2529:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8055:
	ret

FUNC(op_53f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_8013:
	rolw	$8,%bx
	movl	%ebx,%eax
	xorl	%ecx,%ecx
	movswl	%ax,%edx
	testb	$65,regflags
	je	L_8_2559
	movl	$255,%ecx
L_8_2559:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8056:
	ret

FUNC(op_53f9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%edx
RR2_8014:
	bswapl	%edx
	testb	$65,regflags
	je	L_8_2589
	movl	$255,%ecx
L_8_2589:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8057:
	ret

FUNC(op_53fa)

	testb	$65,regflags
	je	L_8_2619
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8058:
	ret
	.align	2,0x90
L_8_2619:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8059:
	ret

FUNC(op_53fb)

	testb	$65,regflags
	je	L_8_2648
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8060:
	ret
	.align	2,0x90
L_8_2648:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8061:
	ret

FUNC(op_53fc)

	testb	$65,regflags
	je	L_8_2676
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8062:
	ret
	.align	2,0x90
L_8_2676:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8063:
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


FUNC(op_4e90)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	pushl	%eax
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	pushl	%eax
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8064:
	ret

FUNC(op_4ea8)

	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_8015:
	rolw	$8,%dx
	movswl	%dx,%edx
	addl	$8,%eax
	addl	GLOBL(regs)(,%eax,4),%edx
	addl	$4,%ecx
	pushl	%edx
	pushl	%ecx
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8065:
	ret

FUNC(op_4eb8)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_8016:
	rolw	$8,%ax
	cwtl
	pushl	%eax
	addl	$4,%edx
	pushl	%edx
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8066:
	ret

FUNC(op_4eb9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_8017:
	bswapl	%edx
	addl	$6,%eax
	pushl	%edx
	pushl	%eax
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8067:
	ret

FUNC(op_4eba)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_8018:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%eax
	addl	$4,%edx
	pushl	%eax
	pushl	%edx
	call	GLOBL(m68k_do_jsr)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8068:
	ret

FUNC(op_4ed0)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8069:
	ret

FUNC(op_4ee8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_8019:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8070:
	ret

FUNC(op_4ef8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_8020:
	rolw	$8,%dx
	movl	%edx,%eax
	cwtl
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8071:
	ret

FUNC(op_4ef9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_8021:
	bswapl	%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8072:
	ret

FUNC(op_4efa)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_8022:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8073:
	ret

FUNC(op_5000)

	subl	$4,%esp
	movl	%eax,%ecx
	movl	%eax,%edx
	shrl	$7,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	andl	$28,%ecx
	movb	(%edx,%eax),%bl
	addb	GLOBL(imm8_table)(%ecx),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%ecx
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8074:
	ret

FUNC(op_5010)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	shrl	$7,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	xorl	%ebx,%ebx
	movw	GLOBL(regs)(,%eax,4),%bx
	sall	$2,%edx
	movl	%ebx,8-8(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%edx),%eax
	andl	$28,%ecx
	movb	(%esi,%eax),%bl
	addb	GLOBL(imm8_table)(%ecx),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,%ecx
	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8075:
	ret

FUNC(op_5018)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	shrl	$7,%eax
	leal	8(%ebp),%ebx
	andl	$28,%eax
	sall	$2,%ebx
	movl	GLOBL(imm8_table)(%eax),%edi
	movl	%ebx,16-16(%esp)
	xorl	%edx,%edx
	movl	GLOBL(regs)(%ebx),%ecx
	movb	GLOBL(regs)+2(%ebx),%dl
	movl	%ecx,%esi
	sall	$2,%edx
	andl	$65535,%esi
	movl	GLOBL(R24)(%edx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%ecx
	movb	(%esi,%eax),%al
	movl	%ecx,GLOBL(regs)(%ebx)
	movb	%al,%cl
	movl	%edi,%ebx
	addb	%bl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8076:
	ret

FUNC(op_5020)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	%edx,%eax
	andl	$7,%eax
	leal	8(%eax),%ebx
	sall	$2,%ebx
	movl	%ebx,16-16(%esp)
	movl	$GLOBL(regs),%edi
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
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
	movl	%ebp,%ebx
	addb	%bl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8077:
	ret

FUNC(op_5028)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8023:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	shrl	$7,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	andl	$28,%ebx
	movb	(%eax,%ecx),%cl
	addb	GLOBL(imm8_table)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8078:
	ret

FUNC(op_5038)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8024:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	andl	$28,%ebx
	movb	(%eax,%ecx),%cl
	addb	GLOBL(imm8_table)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8079:
	ret

FUNC(op_5039)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_8025:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	andl	$28,%ebx
	movb	(%ecx,%edx),%dl
	addb	GLOBL(imm8_table)(%ebx),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8080:
	ret

FUNC(op_5040)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	andl	$28,%ecx
	movw	(%edx,%eax),%si
	addw	GLOBL(imm8_table)(%ecx),%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%ecx
	movw	%cx,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8081:
	ret

FUNC(op_5048)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	addl	$8,%edx
	andl	$28,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	addl	GLOBL(imm8_table)(%eax),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8082:
	ret

FUNC(op_5050)

	movl	%eax,%ebx
	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	shrl	$7,%ebx
	movl	GLOBL(R24)(%edx),%eax
	andl	$28,%ebx
	addl	%ecx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	addw	GLOBL(imm8_table)(%ebx),%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8083:
	ret

FUNC(op_5058)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	shrl	$7,%eax
	addl	$8,%edx
	pushl	%ebx
	andl	$28,%eax
	sall	$2,%edx
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	GLOBL(regs)(%edx),%ecx
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(%edx),%bl
	movl	%ecx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%ecx
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%edx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8084:
	ret

FUNC(op_5060)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	GLOBL(regs)(%edx),%ecx
	shrl	$7,%eax
	addl	$-2,%ecx
	andl	$28,%eax
	movl	%ecx,%ebx
	movl	GLOBL(imm8_table)(%eax),%ebp
	shrl	$14,%ebx
	movl	%ecx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%edx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8085:
	ret

FUNC(op_5068)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8026:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	shrl	$7,%ebx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	GLOBL(imm8_table)(%ebx),%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8086:
	ret

FUNC(op_5078)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8027:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	GLOBL(imm8_table)(%ebx),%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8087:
	ret

FUNC(op_5079)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_8028:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	addw	GLOBL(imm8_table)(%ebx),%dx
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
	jl	JJ_8088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8088:
	ret

FUNC(op_5080)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	andl	$28,%eax
	addl	GLOBL(imm8_table)(%eax),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8089:
	ret

FUNC(op_5088)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	addl	$8,%edx
	andl	$28,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	addl	GLOBL(imm8_table)(%eax),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8090:
	ret

FUNC(op_5090)

	movl	%eax,%ebx
	andl	$7,%eax
	xorl	%ecx,%ecx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%cl
	movw	GLOBL(regs)(,%eax,4),%dx
	sall	$2,%ecx
	movl	GLOBL(R24)(%ecx),%eax
	shrl	$7,%ebx
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	addl	GLOBL(imm8_table)(%ebx),%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8091:
	ret

FUNC(op_5098)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	movl	%edx,%ebx
	shrl	$7,%eax
	andl	$7,%ebx
	movl	$GLOBL(regs),%edi
	addl	$8,%ebx
	andl	$28,%eax
	sall	$2,%ebx
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	(%ebx,%edi),%esi
	movb	2(%ebx,%edi),%cl
	movl	%esi,%edx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	addl	$4,%esi
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,(%ebx,%edi)
	addl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8092:
	ret

FUNC(op_50a0)

	movl	%eax,%edx
	movl	%edx,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%esi
	shrl	$7,%eax
	addl	$-4,%esi
	andl	$28,%eax
	movl	%esi,%ecx
	movl	GLOBL(imm8_table)(%eax),%ebp
	shrl	$14,%ecx
	movl	%esi,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,(%ebx,%edi)
	addl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8093:
	ret

FUNC(op_50a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8029:
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
	shrl	$7,%ebx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8094:
	ret

FUNC(op_50b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8030:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8095:
	ret

FUNC(op_50b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_8031:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	addl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8096:
	ret

FUNC(op_5100)

	subl	$4,%esp
	movl	%eax,%ecx
	movl	%eax,%edx
	shrl	$7,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	andl	$28,%ecx
	movb	(%edx,%eax),%bl
	subb	GLOBL(imm8_table)(%ecx),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%ecx
	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8097:
	ret

FUNC(op_5110)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	shrl	$7,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	xorl	%ebx,%ebx
	movw	GLOBL(regs)(,%eax,4),%bx
	sall	$2,%edx
	movl	%ebx,8-8(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%edx),%eax
	andl	$28,%ecx
	movb	(%esi,%eax),%bl
	subb	GLOBL(imm8_table)(%ecx),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,%ecx
	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8098:
	ret

FUNC(op_5118)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	shrl	$7,%eax
	leal	8(%ebp),%ebx
	andl	$28,%eax
	sall	$2,%ebx
	movl	GLOBL(imm8_table)(%eax),%edi
	movl	%ebx,16-16(%esp)
	xorl	%edx,%edx
	movl	GLOBL(regs)(%ebx),%ecx
	movb	GLOBL(regs)+2(%ebx),%dl
	movl	%ecx,%esi
	sall	$2,%edx
	andl	$65535,%esi
	movl	GLOBL(R24)(%edx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%ecx
	movb	(%esi,%eax),%al
	movl	%ecx,GLOBL(regs)(%ebx)
	movb	%al,%cl
	movl	%edi,%ebx
	subb	%bl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8099:
	ret

FUNC(op_5120)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	%edx,%eax
	andl	$7,%eax
	leal	8(%eax),%ebx
	sall	$2,%ebx
	movl	%ebx,16-16(%esp)
	movl	$GLOBL(regs),%edi
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
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
	movl	%ebp,%ebx
	subb	%bl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_8100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8100:
	ret

FUNC(op_5128)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8032:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	shrl	$7,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	andl	$28,%ebx
	movb	(%eax,%ecx),%cl
	subb	GLOBL(imm8_table)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8101:
	ret

FUNC(op_5138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8033:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	andl	$28,%ebx
	movb	(%eax,%ecx),%cl
	subb	GLOBL(imm8_table)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8102:
	ret

FUNC(op_5139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_8034:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	andl	$28,%ebx
	movb	(%ecx,%edx),%dl
	subb	GLOBL(imm8_table)(%ebx),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8103:
	ret

FUNC(op_5140)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	andl	$28,%ecx
	movw	(%edx,%eax),%si
	subw	GLOBL(imm8_table)(%ecx),%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%ecx
	movw	%cx,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8104:
	ret

FUNC(op_5148)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	addl	$8,%edx
	andl	$28,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	subl	GLOBL(imm8_table)(%eax),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8105:
	ret

FUNC(op_5150)

	movl	%eax,%ebx
	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	shrl	$7,%ebx
	movl	GLOBL(R24)(%edx),%eax
	andl	$28,%ebx
	addl	%ecx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	subw	GLOBL(imm8_table)(%ebx),%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8106:
	ret

FUNC(op_5158)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	shrl	$7,%eax
	addl	$8,%edx
	pushl	%ebx
	andl	$28,%eax
	sall	$2,%edx
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	GLOBL(regs)(%edx),%ecx
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(%edx),%bl
	movl	%ecx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%ecx
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%edx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8107:
	ret

FUNC(op_5160)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	GLOBL(regs)(%edx),%ecx
	shrl	$7,%eax
	addl	$-2,%ecx
	andl	$28,%eax
	movl	%ecx,%ebx
	movl	GLOBL(imm8_table)(%eax),%ebp
	shrl	$14,%ebx
	movl	%ecx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,GLOBL(regs)(%edx)
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8108:
	ret

FUNC(op_5168)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8035:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	shrl	$7,%ebx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	GLOBL(imm8_table)(%ebx),%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8109:
	ret

FUNC(op_5178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8036:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	GLOBL(imm8_table)(%ebx),%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8110:
	ret

FUNC(op_5179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_8037:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%esi,%esi
	movw	(%edx),%si
	rolw	$8,%si
	movl	%esi,%edx
	subw	GLOBL(imm8_table)(%ebx),%dx
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
	jl	JJ_8111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8111:
	ret

FUNC(op_5180)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	andl	$28,%eax
	subl	GLOBL(imm8_table)(%eax),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8112:
	ret

FUNC(op_5188)

	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	addl	$8,%edx
	andl	$28,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	subl	GLOBL(imm8_table)(%eax),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8113:
	ret

FUNC(op_5190)

	movl	%eax,%ebx
	andl	$7,%eax
	xorl	%ecx,%ecx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%cl
	movw	GLOBL(regs)(,%eax,4),%dx
	sall	$2,%ecx
	movl	GLOBL(R24)(%ecx),%eax
	shrl	$7,%ebx
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	subl	GLOBL(imm8_table)(%ebx),%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8114:
	ret

FUNC(op_5198)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	movl	%edx,%ebx
	shrl	$7,%eax
	andl	$7,%ebx
	movl	$GLOBL(regs),%edi
	addl	$8,%ebx
	andl	$28,%eax
	sall	$2,%ebx
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	(%ebx,%edi),%esi
	movb	2(%ebx,%edi),%cl
	movl	%esi,%edx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	addl	$4,%esi
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,(%ebx,%edi)
	subl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8115:
	ret

FUNC(op_51a0)

	movl	%eax,%edx
	movl	%edx,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%esi
	shrl	$7,%eax
	addl	$-4,%esi
	andl	$28,%eax
	movl	%esi,%ecx
	movl	GLOBL(imm8_table)(%eax),%ebp
	shrl	$14,%ecx
	movl	%esi,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,(%ebx,%edi)
	subl	%ebp,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8116:
	ret

FUNC(op_51a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8038:
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
	shrl	$7,%ebx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8117:
	ret

FUNC(op_51b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_8039:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8118
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8118:
	ret

FUNC(op_51b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_8040:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	andl	$28,%ebx
	movl	(%edx),%edx
	bswapl	%edx
	subl	GLOBL(imm8_table)(%ebx),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_8119
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_8189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_8119:
	ret

FUNC(Init020_08)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_8000-4
	movl	%eax,RR0_8001-4
	movl	%eax,RR0_8002-4
	movl	%eax,RR0_8003-4
	movl	%eax,RR0_8004-4
	movl	%eax,RR0_8005-4
	movl	%eax,RR0_8006-4
	movl	%eax,RR0_8007-4
	movl	%eax,RR0_8008-4
	movl	%eax,RR0_8009-4
	movl	%eax,RR0_8010-4
	movl	%eax,RR0_8011-4
	movl	%eax,RR0_8012-4
	movl	%eax,RR0_8013-4
	movl	%eax,RR0_8014-4
	movl	%eax,RR0_8015-4
	movl	%eax,RR0_8016-4
	movl	%eax,RR0_8017-4
	movl	%eax,RR0_8018-4
	movl	%eax,RR0_8019-4
	movl	%eax,RR0_8020-4
	movl	%eax,RR0_8021-4
	movl	%eax,RR0_8022-4
	movl	%eax,RR0_8023-4
	movl	%eax,RR0_8024-4
	movl	%eax,RR0_8025-4
	movl	%eax,RR0_8026-4
	movl	%eax,RR0_8027-4
	movl	%eax,RR0_8028-4
	movl	%eax,RR0_8029-4
	movl	%eax,RR0_8030-4
	movl	%eax,RR0_8031-4
	movl	%eax,RR0_8032-4
	movl	%eax,RR0_8033-4
	movl	%eax,RR0_8034-4
	movl	%eax,RR0_8035-4
	movl	%eax,RR0_8036-4
	movl	%eax,RR0_8037-4
	movl	%eax,RR0_8038-4
	movl	%eax,RR0_8039-4
	movl	%eax,RR0_8040-4
	movl	%eax,RR0_8041-4
	movl	%eax,RR0_8042-4
	movl	%eax,RR0_8043-4
	movl	%eax,RR0_8044-4
	movl	%eax,RR0_8045-4
	movl	%eax,RR0_8046-4
	movl	%eax,RR0_8047-4
	movl	%eax,RR0_8048-4
	movl	%eax,RR0_8049-4
	movl	%eax,RR0_8050-4
	movl	%eax,RR0_8051-4
	movl	%eax,RR0_8052-4
	movl	%eax,RR0_8053-4
	movl	%eax,RR0_8054-4
	movl	%eax,RR0_8055-4
	movl	%eax,RR0_8056-4
	movl	%eax,RR0_8057-4
	movl	%eax,RR0_8058-4
	movl	%eax,RR0_8059-4
	movl	%eax,RR0_8060-4
	movl	%eax,RR0_8061-4
	movl	%eax,RR0_8062-4
	movl	%eax,RR0_8063-4
	movl	%eax,RR0_8064-4
	movl	%eax,RR0_8065-4
	movl	%eax,RR0_8066-4
	movl	%eax,RR0_8067-4
	movl	%eax,RR0_8068-4
	movl	%eax,RR0_8069-4
	movl	%eax,RR0_8070-4
	movl	%eax,RR0_8071-4
	movl	%eax,RR0_8072-4
	movl	%eax,RR0_8073-4
	movl	%eax,RR0_8074-4
	movl	%eax,RR0_8075-4
	movl	%eax,RR0_8076-4
	movl	%eax,RR0_8077-4
	movl	%eax,RR0_8078-4
	movl	%eax,RR0_8079-4
	movl	%eax,RR0_8080-4
	movl	%eax,RR0_8081-4
	movl	%eax,RR0_8082-4
	movl	%eax,RR0_8083-4
	movl	%eax,RR0_8084-4
	movl	%eax,RR0_8085-4
	movl	%eax,RR0_8086-4
	movl	%eax,RR0_8087-4
	movl	%eax,RR0_8088-4
	movl	%eax,RR0_8089-4
	movl	%eax,RR0_8090-4
	movl	%eax,RR0_8091-4
	movl	%eax,RR0_8092-4
	movl	%eax,RR0_8093-4
	movl	%eax,RR0_8094-4
	movl	%eax,RR0_8095-4
	movl	%eax,RR0_8096-4
	movl	%eax,RR0_8097-4
	movl	%eax,RR0_8098-4
	movl	%eax,RR0_8099-4
	movl	%eax,RR0_8100-4
	movl	%eax,RR0_8101-4
	movl	%eax,RR0_8102-4
	movl	%eax,RR0_8103-4
	movl	%eax,RR0_8104-4
	movl	%eax,RR0_8105-4
	movl	%eax,RR0_8106-4
	movl	%eax,RR0_8107-4
	movl	%eax,RR0_8108-4
	movl	%eax,RR0_8109-4
	movl	%eax,RR0_8110-4
	movl	%eax,RR0_8111-4
	movl	%eax,RR0_8112-4
	movl	%eax,RR0_8113-4
	movl	%eax,RR0_8114-4
	movl	%eax,RR0_8115-4
	movl	%eax,RR0_8116-4
	movl	%eax,RR0_8117-4
	movl	%eax,RR0_8118-4
	movl	%eax,RR0_8119-4
	movl	%eax,RR0_8120-4
	movl	%eax,RR0_8121-4
	movl	%eax,RR0_8122-4
	movl	%eax,RR0_8123-4
	movl	%eax,RR0_8124-4
	movl	%eax,RR0_8125-4
	movl	%eax,RR0_8126-4
	movl	%eax,RR0_8127-4
	movl	%eax,RR0_8128-4
	movl	%eax,RR0_8129-4
	movl	%eax,RR0_8130-4
	movl	%eax,RR0_8131-4
	movl	%eax,RR0_8132-4
	movl	%eax,RR0_8133-4
	movl	%eax,RR0_8134-4
	movl	%eax,RR0_8135-4
	movl	%eax,RR0_8136-4
	movl	%eax,RR0_8137-4
	movl	%eax,RR0_8138-4
	movl	%eax,RR0_8139-4
	movl	%eax,RR0_8140-4
	movl	%eax,RR0_8141-4
	movl	%eax,RR0_8142-4
	movl	%eax,RR0_8143-4
	movl	%eax,RR0_8144-4
	movl	%eax,RR0_8145-4
	movl	%eax,RR0_8146-4
	movl	%eax,RR0_8147-4
	movl	%eax,RR0_8148-4
	movl	%eax,RR0_8149-4
	movl	%eax,RR0_8150-4
	movl	%eax,RR0_8151-4
	movl	%eax,RR0_8152-4
	movl	%eax,RR0_8153-4
	movl	%eax,RR0_8154-4
	movl	%eax,RR0_8155-4
	movl	%eax,RR0_8156-4
	movl	%eax,RR0_8157-4
	movl	%eax,RR0_8158-4
	movl	%eax,RR0_8159-4
	movl	%eax,RR0_8160-4
	movl	%eax,RR0_8161-4
	movl	%eax,RR0_8162-4
	movl	%eax,RR0_8163-4
	movl	%eax,RR0_8164-4
	movl	%eax,RR0_8165-4
	movl	%eax,RR0_8166-4
	movl	%eax,RR0_8167-4
	movl	%eax,RR0_8168-4
	movl	%eax,RR0_8169-4
	movl	%eax,RR0_8170-4
	movl	%eax,RR0_8171-4
	movl	%eax,RR0_8172-4
	movl	%eax,RR0_8173-4
	movl	%eax,RR0_8174-4
	movl	%eax,RR0_8175-4
	movl	%eax,RR0_8176-4
	movl	%eax,RR0_8177-4
	movl	%eax,RR0_8178-4
	movl	%eax,RR0_8179-4
	movl	%eax,RR0_8180-4
	movl	%eax,RR0_8181-4
	movl	%eax,RR0_8182-4
	movl	%eax,RR0_8183-4
	movl	%eax,RR0_8184-4
	movl	%eax,RR0_8185-4
	movl	%eax,RR0_8186-4
	movl	%eax,RR0_8187-4
	movl	%eax,RR0_8188-4
	movl	%eax,RR0_8189-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_8000-4
	movl	%eax,RR2_8001-4
	movl	%eax,RR2_8002-4
	movl	%eax,RR2_8003-4
	movl	%eax,RR2_8004-4
	movl	%eax,RR2_8005-4
	movl	%eax,RR2_8006-4
	movl	%eax,RR2_8007-4
	movl	%eax,RR2_8008-4
	movl	%eax,RR2_8009-4
	movl	%eax,RR2_8010-4
	movl	%eax,RR2_8011-4
	movl	%eax,RR2_8012-4
	movl	%eax,RR2_8013-4
	movl	%eax,RR2_8014-4
	movl	%eax,RR2_8015-4
	movl	%eax,RR2_8016-4
	movl	%eax,RR2_8017-4
	movl	%eax,RR2_8018-4
	movl	%eax,RR2_8019-4
	movl	%eax,RR2_8020-4
	movl	%eax,RR2_8021-4
	movl	%eax,RR2_8022-4
	movl	%eax,RR2_8023-4
	movl	%eax,RR2_8024-4
	movl	%eax,RR2_8025-4
	movl	%eax,RR2_8026-4
	movl	%eax,RR2_8027-4
	movl	%eax,RR2_8028-4
	movl	%eax,RR2_8029-4
	movl	%eax,RR2_8030-4
	movl	%eax,RR2_8031-4
	movl	%eax,RR2_8032-4
	movl	%eax,RR2_8033-4
	movl	%eax,RR2_8034-4
	movl	%eax,RR2_8035-4
	movl	%eax,RR2_8036-4
	movl	%eax,RR2_8037-4
	movl	%eax,RR2_8038-4
	movl	%eax,RR2_8039-4
	movl	%eax,RR2_8040-4
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
