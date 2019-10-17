

FUNC(op_c03b)

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
RR0_d000:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_375
	movswl	%di,%edi
L_d_375:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_376
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_377
	movl	%ebp,%ebx
L_d_377:
	testl	$64,%esi
	je	L_d_378
	movl	%ebp,%edi
L_d_378:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_379
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_379:
	cmpl	$48,%edx
	jne	L_d_382
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_382:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_385
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_385:
	cmpl	$3,16-16(%esp)
	jne	L_d_388
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_388:
	andl	$4,%esi
	jne	L_d_391
	addl	%edi,%ebx
L_d_391:
	cmpl	$0,16-16(%esp)
	je	L_d_392
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_392:
	testl	%esi,%esi
	je	L_d_395
	addl	%edi,%ebx
L_d_395:
	leal	(%ebp,%ebx),%edx
	jmp	L_d_396
	.align	2,0x90
L_d_376:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_d_396:
	movl	%edx,%eax
	movl	%edx,%ebx
	movl	28-16(%esp),%ecx
	shrl	$14,%eax
	andl	$65535,%ebx
	andl	$1020,%eax
	sall	$2,%ecx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ecx,16-16(%esp)
	movl	$GLOBL(regs),%edx
	movb	(%ebx,%eax),%al
	andb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d000:
	ret

FUNC(op_c070)

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
RR0_d006:
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
	jne	L_d_445
	movswl	%di,%edi
L_d_445:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_446
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_447
	movl	%ebp,%ebx
L_d_447:
	testl	$64,%esi
	je	L_d_448
	movl	%ebp,%edi
L_d_448:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_449
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_449:
	cmpl	$48,%edx
	jne	L_d_452
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_452:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_455
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_455:
	cmpl	$3,16-16(%esp)
	jne	L_d_458
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_458:
	andl	$4,%esi
	jne	L_d_461
	addl	%edi,%ebx
L_d_461:
	cmpl	$0,16-16(%esp)
	je	L_d_462
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_462:
	testl	%esi,%esi
	je	L_d_465
	addl	%edi,%ebx
L_d_465:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_466
	.align	2,0x90
L_d_446:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_466:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	movl	%eax,%edx
	sall	$2,%ecx
	movl	$GLOBL(regs),%eax
	movl	%ecx,16-16(%esp)
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d001:
	ret

FUNC(op_c07b)

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
RR0_d012:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_507
	movswl	%di,%edi
L_d_507:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_508
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_509
	movl	%ebp,%ebx
L_d_509:
	testl	$64,%esi
	je	L_d_510
	movl	%ebp,%edi
L_d_510:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_511
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_511:
	cmpl	$48,%edx
	jne	L_d_514
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_514:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_517
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_517:
	cmpl	$3,16-16(%esp)
	jne	L_d_520
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_520:
	andl	$4,%esi
	jne	L_d_523
	addl	%edi,%ebx
L_d_523:
	cmpl	$0,16-16(%esp)
	je	L_d_524
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_524:
	testl	%esi,%esi
	je	L_d_527
	addl	%edi,%ebx
L_d_527:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_528
	.align	2,0x90
L_d_508:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_528:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	movl	%eax,%edx
	sall	$2,%ecx
	movl	$GLOBL(regs),%eax
	movl	%ecx,16-16(%esp)
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d002:
	ret

FUNC(op_c0b0)

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
RR0_d018:
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
	jne	L_d_580
	movswl	%di,%edi
L_d_580:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_581
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_582
	movl	%ebp,%ebx
L_d_582:
	testl	$64,%esi
	je	L_d_583
	movl	%ebp,%edi
L_d_583:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_584
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d019:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_584:
	cmpl	$48,%edx
	jne	L_d_587
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_587:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_590
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_590:
	cmpl	$3,16-16(%esp)
	jne	L_d_593
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_593:
	andl	$4,%esi
	jne	L_d_596
	addl	%edi,%ebx
L_d_596:
	cmpl	$0,16-16(%esp)
	je	L_d_597
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_597:
	testl	%esi,%esi
	je	L_d_600
	addl	%edi,%ebx
L_d_600:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_601
	.align	2,0x90
L_d_581:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_601:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	28-16(%esp),%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%eax
	movl	%ecx,16-16(%esp)
	bswapl	%eax
	andl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d003:
	ret

FUNC(op_c0bb)

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
RR0_d024:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_642
	movswl	%di,%edi
L_d_642:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_643
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_644
	movl	%ebp,%ebx
L_d_644:
	testl	$64,%esi
	je	L_d_645
	movl	%ebp,%edi
L_d_645:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_646
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d025:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_646:
	cmpl	$48,%edx
	jne	L_d_649
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_649:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_652
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_652:
	cmpl	$3,16-16(%esp)
	jne	L_d_655
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_655:
	andl	$4,%esi
	jne	L_d_658
	addl	%edi,%ebx
L_d_658:
	cmpl	$0,16-16(%esp)
	je	L_d_659
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_659:
	testl	%esi,%esi
	je	L_d_662
	addl	%edi,%ebx
L_d_662:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_663
	.align	2,0x90
L_d_643:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_663:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	28-16(%esp),%ecx
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%eax
	movl	%ecx,16-16(%esp)
	bswapl	%eax
	andl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d004:
	ret

FUNC(op_c0f0)

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
RR0_d030:
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
	jne	L_d_715
	movswl	%di,%edi
L_d_715:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_716
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_717
	movl	%ebp,%ebx
L_d_717:
	testl	$64,%esi
	je	L_d_718
	movl	%ebp,%edi
L_d_718:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_719
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_719:
	cmpl	$48,%edx
	jne	L_d_722
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_722:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_725
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_725:
	cmpl	$3,16-16(%esp)
	jne	L_d_728
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_728:
	andl	$4,%esi
	jne	L_d_731
	addl	%edi,%ebx
L_d_731:
	cmpl	$0,16-16(%esp)
	je	L_d_732
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_732:
	testl	%esi,%esi
	je	L_d_735
	addl	%edi,%ebx
L_d_735:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_736
	.align	2,0x90
L_d_716:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_736:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	movl	%eax,%edx
	leal	0(,%ecx,4),%ebx
	xorl	%eax,%eax
	movw	GLOBL(regs)(%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(%ebx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d005:
	ret

FUNC(op_c0fb)

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
RR0_d036:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_777
	movswl	%di,%edi
L_d_777:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_778
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_779
	movl	%ebp,%ebx
L_d_779:
	testl	$64,%esi
	je	L_d_780
	movl	%ebp,%edi
L_d_780:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_781
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d037:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_781:
	cmpl	$48,%edx
	jne	L_d_784
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_784:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_787
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_787:
	cmpl	$3,16-16(%esp)
	jne	L_d_790
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_790:
	andl	$4,%esi
	jne	L_d_793
	addl	%edi,%ebx
L_d_793:
	cmpl	$0,16-16(%esp)
	je	L_d_794
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_794:
	testl	%esi,%esi
	je	L_d_797
	addl	%edi,%ebx
L_d_797:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_798
	.align	2,0x90
L_d_778:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_798:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	movl	%eax,%edx
	leal	0(,%ecx,4),%ebx
	xorl	%eax,%eax
	movw	GLOBL(regs)(%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(%ebx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d006:
	ret

FUNC(op_c100)

	subl	$12,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebp
	movl	%edx,%edi
	movb	(%ebp,%eax,4),%al
	andl	$28,%edi
	movb	%al,24-16(%esp)
	movb	(%edi,%ebp),%bl
	movb	%al,%dl
	movb	%bl,%al
	andl	$15,%edx
	andl	$15,%eax
	movb	%bl,20-16(%esp)
	addl	%edx,%eax
	testb	$1,regflags+4
	je	L_d_810
	incl	%eax
L_d_810:
	movl	%eax,%ecx
	movb	24-16(%esp),%dl
	movb	20-16(%esp),%al
	andl	$240,%edx
	andl	$240,%eax
	addw	%dx,%ax
	cmpw	$9,%cx
	jbe	L_d_811
	addl	$6,%ecx
L_d_811:
	addl	%ecx,%eax
	movw	%ax,18-16(%esp)
	andl	$496,%eax
	cmpw	$144,%ax
	seta	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testb	$1,regflags
	je	L_d_812
	addw	$96,18-16(%esp)
L_d_812:
	cmpb	$0,18-16(%esp)
	je	L_d_813
	andb	$191,%al
	movb	%al,regflags
L_d_813:
	movsbl	18-16(%esp),%eax
	movl	%eax,%esi
	shrl	$31,%esi
	movb	regflags,%al
	movl	%esi,%edx
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	xorl	%ecx,%ecx
	movb	%al,regflags
	movsbl	24-16(%esp),%edx
	movsbl	20-16(%esp),%eax
	shrl	$31,%edx
	shrl	$31,%eax
	cmpl	%eax,%edx
	je	L_d_814
	cmpl	%eax,%esi
	setne	%al
	movb	%al,%cl
L_d_814:
	movb	%cl,%dl
	movb	regflags+1,%al
	andb	$1,%dl
	andb	$247,%al
	salb	$3,%dl
	orb	%dl,%al
	movb	18-16(%esp),%bl
	movb	%al,regflags+1
	movb	%bl,(%edi,%ebp)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d042:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d007:
	ret

FUNC(op_c108)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(areg_byteinc),%ebp
	movl	%edx,%esi
	leal	8(%eax),%ebx
	shrl	$9,%esi
	sall	$2,%ebx
	movl	(%ebp,%eax,4),%eax
	movl	GLOBL(regs)(%ebx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ecx,%eax),%cl
	andl	$7,%esi
	movb	%cl,24-16(%esp)
	leal	8(%esi),%ecx
	movl	%edx,GLOBL(regs)(%ebx)
	sall	$2,%ecx
	movl	(%ebp,%esi,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	movl	%edx,%edi
	shrl	$14,%eax
	andl	$65535,%edi
	movl	%eax,%ebp
	movl	%edi,16-16(%esp)
	andl	$1020,%ebp
	movl	GLOBL(R24)(%ebp),%eax
	movb	(%edi,%eax),%al
	movb	%al,20-16(%esp)
	movl	%edx,GLOBL(regs)(%ecx)
	movb	24-16(%esp),%dl
	movb	20-16(%esp),%al
	andl	$15,%edx
	andl	$15,%eax
	addl	%edx,%eax
	testb	$1,regflags+4
	je	L_d_819
	incl	%eax
L_d_819:
	movl	%eax,%ecx
	movb	24-16(%esp),%dl
	movb	20-16(%esp),%al
	andl	$240,%edx
	andl	$240,%eax
	addw	%dx,%ax
	cmpw	$9,%cx
	jbe	L_d_820
	addl	$6,%ecx
L_d_820:
	movl	%eax,%ebx
	addl	%ecx,%ebx
	movl	%ebx,%eax
	andl	$496,%eax
	cmpw	$144,%ax
	seta	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testb	$1,regflags
	je	L_d_821
	addl	$96,%ebx
L_d_821:
	testb	%bl,%bl
	je	L_d_822
	andb	$191,%al
	movb	%al,regflags
L_d_822:
	movsbl	%bl,%eax
	movl	%eax,%esi
	shrl	$31,%esi
	movb	regflags,%al
	movl	%esi,%edx
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	xorl	%ecx,%ecx
	movb	%al,regflags
	movsbl	24-16(%esp),%edx
	movsbl	20-16(%esp),%eax
	shrl	$31,%edx
	shrl	$31,%eax
	cmpl	%eax,%edx
	je	L_d_823
	cmpl	%eax,%esi
	setne	%al
	movb	%al,%cl
L_d_823:
	movb	%cl,%al
	movb	regflags+1,%dl
	andb	$1,%al
	andb	$247,%dl
	salb	$3,%al
	orb	%al,%dl
	movb	%dl,regflags+1
	movl	16-16(%esp),%edi
	movl	GLOBL(W24)(%ebp),%eax
	movb	%bl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d008:
	ret

FUNC(op_c130)

	subl	$16,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movb	(%eax,%ecx),%al
	movl	GLOBL(regs)+88,%ebx
	movb	%al,31-16(%esp)
	addl	$8,%edx
	movl	%ebx,%eax
	movl	%ebx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_d044:
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
	jne	L_d_863
	movswl	%di,%edi
L_d_863:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_864
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_d_865
	movl	%ebp,16-16(%esp)
L_d_865:
	testl	$64,%esi
	je	L_d_866
	movl	%ebp,%edi
L_d_866:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_867
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d045:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_d_867:
	cmpl	$48,%edx
	jne	L_d_870
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d046:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_d_870:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_d_873
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d047:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_873:
	cmpl	$3,%ecx
	jne	L_d_876
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d048:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_876:
	andl	$4,%esi
	jne	L_d_879
	addl	%edi,16-16(%esp)
L_d_879:
	testl	%ecx,%ecx
	je	L_d_880
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_d_880:
	testl	%esi,%esi
	je	L_d_883
	addl	%edi,16-16(%esp)
L_d_883:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_d_884
	.align	2,0x90
L_d_864:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_884:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	andb	%al,31-16(%esp)
	movb	31-16(%esp),%bl
	testb	%bl,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	GLOBL(W24)(%edx),%eax
	movb	%bl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d009:
	ret

FUNC(op_c170)

	subl	$16,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movw	(%eax,%ecx),%ax
	movl	GLOBL(regs)+88,%ebx
	movw	%ax,30-16(%esp)
	addl	$8,%edx
	movl	%ebx,%eax
	movl	%ebx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_d050:
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
	jne	L_d_970
	movswl	%di,%edi
L_d_970:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_971
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_d_972
	movl	%ebp,16-16(%esp)
L_d_972:
	testl	$64,%esi
	je	L_d_973
	movl	%ebp,%edi
L_d_973:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_974
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d051:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_d_974:
	cmpl	$48,%edx
	jne	L_d_977
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d052:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_d_977:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_d_980
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d053:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_980:
	cmpl	$3,%ecx
	jne	L_d_983
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d054:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_983:
	andl	$4,%esi
	jne	L_d_986
	addl	%edi,16-16(%esp)
L_d_986:
	testl	%ecx,%ecx
	je	L_d_987
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_d_987:
	testl	%esi,%esi
	je	L_d_990
	addl	%edi,16-16(%esp)
L_d_990:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_d_991
	.align	2,0x90
L_d_971:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_991:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	addl	%ecx,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	andw	%ax,30-16(%esp)
	movw	30-16(%esp),%bx
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%bx,%ax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d010:
	ret

FUNC(op_c1b0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movl	(%eax,%ecx),%eax
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
RR0_d056:
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
	jne	L_d_1083
	movswl	%di,%edi
L_d_1083:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1084
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_d_1085
	movl	%ebp,16-16(%esp)
L_d_1085:
	testl	$64,%esi
	je	L_d_1086
	movl	%ebp,%edi
L_d_1086:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1087
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d057:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_d_1087:
	cmpl	$48,%edx
	jne	L_d_1090
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d058:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_d_1090:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_d_1093
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d059:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1093:
	cmpl	$3,%ecx
	jne	L_d_1096
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d060:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1096:
	andl	$4,%esi
	jne	L_d_1099
	addl	%edi,16-16(%esp)
L_d_1099:
	testl	%ecx,%ecx
	je	L_d_1100
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_d_1100:
	testl	%esi,%esi
	je	L_d_1103
	addl	%edi,16-16(%esp)
L_d_1103:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_d_1104
	.align	2,0x90
L_d_1084:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1104:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	andl	%eax,28-16(%esp)
	movl	28-16(%esp),%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%ebx
	movl	%ebx,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d011:
	ret

FUNC(op_c1f0)

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
RR0_d062:
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
	jne	L_d_1180
	movswl	%di,%edi
L_d_1180:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1181
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1182
	movl	%ebp,%ebx
L_d_1182:
	testl	$64,%esi
	je	L_d_1183
	movl	%ebp,%edi
L_d_1183:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1184
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d063:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1184:
	cmpl	$48,%edx
	jne	L_d_1187
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d064:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1187:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_1190
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d065:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1190:
	cmpl	$3,16-16(%esp)
	jne	L_d_1193
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d066:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1193:
	andl	$4,%esi
	jne	L_d_1196
	addl	%edi,%ebx
L_d_1196:
	cmpl	$0,16-16(%esp)
	je	L_d_1197
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1197:
	testl	%esi,%esi
	je	L_d_1200
	addl	%edi,%ebx
L_d_1200:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1201
	.align	2,0x90
L_d_1181:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1201:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	leal	0(,%ecx,4),%ebx
	movl	%eax,%edx
	movswl	GLOBL(regs)(%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(%ebx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d067:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d012:
	ret

FUNC(op_c1fb)

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
RR0_d068:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_1242
	movswl	%di,%edi
L_d_1242:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1243
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1244
	movl	%ebp,%ebx
L_d_1244:
	testl	$64,%esi
	je	L_d_1245
	movl	%ebp,%edi
L_d_1245:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1246
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d069:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1246:
	cmpl	$48,%edx
	jne	L_d_1249
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d070:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1249:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_1252
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d071:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1252:
	cmpl	$3,16-16(%esp)
	jne	L_d_1255
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d072:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1255:
	andl	$4,%esi
	jne	L_d_1258
	addl	%edi,%ebx
L_d_1258:
	cmpl	$0,16-16(%esp)
	je	L_d_1259
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1259:
	testl	%esi,%esi
	je	L_d_1262
	addl	%edi,%ebx
L_d_1262:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1263
	.align	2,0x90
L_d_1243:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1263:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	28-16(%esp),%ecx
	leal	0(,%ecx,4),%ebx
	movl	%eax,%edx
	movswl	GLOBL(regs)(%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,GLOBL(regs)(%ebx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d073:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d013:
	ret

FUNC(op_d030)

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
RR0_d074:
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
	jne	L_d_1307
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_d_1307:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_d_1308
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1309
	movl	%ebp,%ebx
L_d_1309:
	testl	$64,%esi
	je	L_d_1310
	movl	%ebp,16-16(%esp)
L_d_1310:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1311
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_d075:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1311:
	cmpl	$48,%edx
	jne	L_d_1314
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d076:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1314:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_d_1317
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d077:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1317:
	cmpl	$3,20-16(%esp)
	jne	L_d_1320
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d078:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1320:
	andl	$4,%esi
	jne	L_d_1323
	addl	16-16(%esp),%ebx
L_d_1323:
	cmpl	$0,20-16(%esp)
	je	L_d_1324
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1324:
	testl	%esi,%esi
	je	L_d_1327
	addl	16-16(%esp),%ebx
L_d_1327:
	leal	(%ebp,%ebx),%edx
	jmp	L_d_1328
	.align	2,0x90
L_d_1308:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_d_1328:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	movl	32-16(%esp),%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$65535,%ebx
	movl	%eax,20-16(%esp)
	leal	0(,%ecx,4),%edx
	movl	$GLOBL(regs),%eax
	movl	20-16(%esp),%edi
	movb	(%edx,%eax),%cl
	addb	(%ebx,%edi),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,20-16(%esp)
	movb	20-16(%esp),%cl
	movb	%cl,(%edx,%eax)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d014:
	ret

FUNC(op_d03b)

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
RR0_d080:
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
	jne	L_d_1362
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_d_1362:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_d_1363
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1364
	movl	%ebp,%ebx
L_d_1364:
	testl	$64,%esi
	je	L_d_1365
	movl	%ebp,16-16(%esp)
L_d_1365:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1366
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_d081:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1366:
	cmpl	$48,%edx
	jne	L_d_1369
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d082:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1369:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_d_1372
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d083:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1372:
	cmpl	$3,20-16(%esp)
	jne	L_d_1375
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d084:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1375:
	andl	$4,%esi
	jne	L_d_1378
	addl	16-16(%esp),%ebx
L_d_1378:
	cmpl	$0,20-16(%esp)
	je	L_d_1379
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1379:
	testl	%esi,%esi
	je	L_d_1382
	addl	16-16(%esp),%ebx
L_d_1382:
	leal	(%ebp,%ebx),%edx
	jmp	L_d_1383
	.align	2,0x90
L_d_1363:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_d_1383:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	movl	32-16(%esp),%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$65535,%ebx
	movl	%eax,20-16(%esp)
	leal	0(,%ecx,4),%edx
	movl	$GLOBL(regs),%eax
	movl	20-16(%esp),%edi
	movb	(%edx,%eax),%cl
	addb	(%ebx,%edi),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,20-16(%esp)
	movb	20-16(%esp),%cl
	movb	%cl,(%edx,%eax)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d085:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d015:
	ret

FUNC(op_d070)

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
RR0_d086:
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
	jne	L_d_1436
	movswl	%di,%edi
L_d_1436:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1437
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1438
	movl	%ebp,%ebx
L_d_1438:
	testl	$64,%esi
	je	L_d_1439
	movl	%ebp,%edi
L_d_1439:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1440
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d087:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1440:
	cmpl	$48,%edx
	jne	L_d_1443
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d088:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1443:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_1446
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d089:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1446:
	cmpl	$3,16-16(%esp)
	jne	L_d_1449
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d090:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1449:
	andl	$4,%esi
	jne	L_d_1452
	addl	%edi,%ebx
L_d_1452:
	cmpl	$0,16-16(%esp)
	je	L_d_1453
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1453:
	testl	%esi,%esi
	je	L_d_1456
	addl	%edi,%ebx
L_d_1456:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1457
	.align	2,0x90
L_d_1437:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1457:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,16-16(%esp)
	movl	28-16(%esp),%ecx
	movl	$GLOBL(regs),%eax
	leal	0(,%ecx,4),%edx
	movw	(%edx,%eax),%cx
	addw	16-16(%esp),%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,16-16(%esp)
	movl	16-16(%esp),%ecx
	movw	%cx,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d016:
	ret

FUNC(op_d07b)

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
RR0_d092:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_d_1498
	movswl	%di,%edi
L_d_1498:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1499
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1500
	movl	%ebp,%ebx
L_d_1500:
	testl	$64,%esi
	je	L_d_1501
	movl	%ebp,%edi
L_d_1501:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1502
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d093:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1502:
	cmpl	$48,%edx
	jne	L_d_1505
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d094:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1505:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_1508
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d095:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1508:
	cmpl	$3,16-16(%esp)
	jne	L_d_1511
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d096:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1511:
	andl	$4,%esi
	jne	L_d_1514
	addl	%edi,%ebx
L_d_1514:
	cmpl	$0,16-16(%esp)
	je	L_d_1515
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1515:
	testl	%esi,%esi
	je	L_d_1518
	addl	%edi,%ebx
L_d_1518:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1519
	.align	2,0x90
L_d_1499:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1519:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,16-16(%esp)
	movl	28-16(%esp),%ecx
	movl	$GLOBL(regs),%eax
	leal	0(,%ecx,4),%edx
	movw	(%edx,%eax),%cx
	addw	16-16(%esp),%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,16-16(%esp)
	movl	16-16(%esp),%ecx
	movw	%cx,(%edx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d017:
	ret

FUNC(op_d0b0)

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
RR0_d098:
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
	jne	L_d_1575
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_d_1575:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_d_1576
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1577
	movl	%ebp,%ebx
L_d_1577:
	testl	$64,%esi
	je	L_d_1578
	movl	%ebp,16-16(%esp)
L_d_1578:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1579
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_d099:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1579:
	cmpl	$48,%edx
	jne	L_d_1582
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d100:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1582:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_d_1585
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d101:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1585:
	cmpl	$3,20-16(%esp)
	jne	L_d_1588
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d102:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1588:
	andl	$4,%esi
	jne	L_d_1591
	addl	16-16(%esp),%ebx
L_d_1591:
	cmpl	$0,20-16(%esp)
	je	L_d_1592
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1592:
	testl	%esi,%esi
	je	L_d_1595
	addl	16-16(%esp),%ebx
L_d_1595:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1596
	.align	2,0x90
L_d_1576:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_d_1596:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edi,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d103:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d018:
	ret

FUNC(op_d0bb)

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
RR0_d104:
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
	jne	L_d_1637
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_d_1637:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_d_1638
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1639
	movl	%ebp,%ebx
L_d_1639:
	testl	$64,%esi
	je	L_d_1640
	movl	%ebp,16-16(%esp)
L_d_1640:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1641
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_d105:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1641:
	cmpl	$48,%edx
	jne	L_d_1644
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d106:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1644:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_d_1647
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d107:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1647:
	cmpl	$3,20-16(%esp)
	jne	L_d_1650
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d108:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1650:
	andl	$4,%esi
	jne	L_d_1653
	addl	16-16(%esp),%ebx
L_d_1653:
	cmpl	$0,20-16(%esp)
	je	L_d_1654
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1654:
	testl	%esi,%esi
	je	L_d_1657
	addl	16-16(%esp),%ebx
L_d_1657:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1658
	.align	2,0x90
L_d_1638:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_d_1658:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edi,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d019:
	ret

FUNC(op_d0f0)

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
RR0_d110:
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
	jne	L_d_1714
	movswl	%di,%edi
L_d_1714:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_d_1715
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_d_1716
	movl	%ebp,%ebx
L_d_1716:
	testl	$64,%esi
	je	L_d_1717
	movl	%ebp,%edi
L_d_1717:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_d_1718
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_d111:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_d_1718:
	cmpl	$48,%edx
	jne	L_d_1721
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d112:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_d_1721:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_d_1724
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_d113:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1724:
	cmpl	$3,16-16(%esp)
	jne	L_d_1727
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_d114:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_d_1727:
	andl	$4,%esi
	jne	L_d_1730
	addl	%edi,%ebx
L_d_1730:
	cmpl	$0,16-16(%esp)
	je	L_d_1731
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_d_1731:
	testl	%esi,%esi
	je	L_d_1734
	addl	%edi,%ebx
L_d_1734:
	leal	(%ebp,%ebx),%eax
	jmp	L_d_1735
	.align	2,0x90
L_d_1715:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_d_1735:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	28-16(%esp),%edx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	%eax,GLOBL(regs)(,%edx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d020:
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


FUNC(op_c03c)

	movl	%eax,%ecx
	movl	$GLOBL(regs),%edx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$28,%ecx
	movb	0x2164334A+3(%eax),%al
RR3_d000:
	andb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d021:
	ret

FUNC(op_c040)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%ecx
	movw	(%edx,%eax,4),%ax
	andw	(%ecx,%edx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d022:
	ret

FUNC(op_c050)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%bl
	movw	(%edx,%eax,4),%ax
	andl	$65535,%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andw	(%ecx,%edx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d023:
	ret

FUNC(op_c058)

	subl	$8,%esp
	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	movl	%eax,%edi
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	shrl	$7,%edi
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
	andl	$28,%edi
	movl	%edx,(%ecx,%ebx)
	andw	(%edi,%ebx),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d024:
	ret

FUNC(op_c060)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	(%ecx,%esi),%ebx
	movl	%eax,%edi
	addl	$-2,%ebx
	shrl	$7,%edi
	movl	%ebx,12-12(%esp)
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	12-12(%esp),%ebx
	andl	$28,%edi
	movl	%ebx,(%ecx,%esi)
	andw	(%edi,%esi),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d025:
	ret

FUNC(op_c068)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d000:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ebx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andw	(%ebx,%ecx),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d026:
	ret

FUNC(op_c078)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d001:
	rolw	$8,%si
	movl	%esi,%eax
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
	andl	$28,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d027:
	ret

FUNC(op_c079)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d002:
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
	andl	$28,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d028:
	ret

FUNC(op_c07a)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d003:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d029:
	ret

FUNC(op_c07c)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d004:
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	andw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d030:
	ret

FUNC(op_c080)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	movl	(%ecx,%eax,4),%eax
	andl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d031:
	ret

FUNC(op_c090)

	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%bl
	movw	(%ecx,%eax,4),%ax
	andl	$65535,%eax
	shrl	$7,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	andl	$28,%edx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d032:
	ret

FUNC(op_c098)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edi
	movl	(%ecx,%ebx),%edx
	shrl	$7,%edi
	movl	%edx,%eax
	movzbl	2(%ecx,%ebx),%esi
	andl	$65535,%eax
	andl	$28,%edi
	addl	GLOBL(R24)(,%esi,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	movl	%edx,(%ecx,%ebx)
	bswapl	%eax
	andl	(%edi,%ebx),%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%ebx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d033:
	ret

FUNC(op_c0a0)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
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
	movl	(%eax),%eax
	movl	%ecx,(%ebx,%esi)
	bswapl	%eax
	andl	(%edi,%esi),%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d034:
	ret

FUNC(op_c0a8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d005:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ebx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d035:
	ret

FUNC(op_c0b8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d006:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d036:
	ret

FUNC(op_c0b9)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d007:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d037:
	ret

FUNC(op_c0ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d008:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	$GLOBL(regs),%edx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d038:
	ret

FUNC(op_c0bc)

	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_d009:
	andl	$28,%edx
	bswapl	%eax
	andl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d039:
	ret

FUNC(op_c0c0)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$7,%ecx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	andl	$28,%ecx
	movw	(%ebx,%edx,4),%dx
	movw	(%ecx,%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d040:
	ret

FUNC(op_c0d0)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ecx,%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d041:
	ret

FUNC(op_c0d8)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%eax,%edi
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	shrl	$7,%edi
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$2,%edx
	movw	%ax,18-12(%esp)
	andl	$28,%edi
	movl	%edx,(%ecx,%esi)
	xorl	%eax,%eax
	movw	(%edi,%esi),%ax
	xorl	%edx,%edx
	movw	18-12(%esp),%dx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d042:
	ret

FUNC(op_c0e0)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	(%ecx,%esi),%ebx
	movl	%eax,%edi
	addl	$-2,%ebx
	shrl	$7,%edi
	movl	%ebx,12-12(%esp)
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%edi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	12-12(%esp),%ebx
	movl	%eax,%edx
	movl	%ebx,(%ecx,%esi)
	xorl	%eax,%eax
	movw	(%edi,%esi),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d043:
	ret

FUNC(op_c0e8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d010:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ebx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ebx,%ecx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d044:
	ret

FUNC(op_c0f8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d011:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ecx,%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d045:
	ret

FUNC(op_c0f9)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d012:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ecx,%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d046:
	ret

FUNC(op_c0fa)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d013:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$GLOBL(regs),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ebx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ebx,%ecx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d047:
	ret

FUNC(op_c0fc)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d014:
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	xorl	%eax,%eax
	movw	(%ecx,%ebx),%ax
	andl	$65535,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d048:
	ret

FUNC(op_c110)

	movl	%eax,%ecx
	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%ebx
	shrl	$7,%ecx
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	andl	$28,%ecx
	movb	2(%esi,%eax,4),%dl
	xorl	%ebx,%ebx
	movw	(%esi,%eax,4),%bx
	sall	$2,%edx
	movb	(%ecx,%esi),%cl
	movl	GLOBL(R24)(%edx),%eax
	andb	(%ebx,%eax),%cl
	movb	%cl,%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ebx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d049:
	ret

FUNC(op_c118)

	subl	$8,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$7,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	leal	8(%ebp),%ecx
	movb	(%eax,%esi),%al
	sall	$2,%ecx
	movb	%al,23-16(%esp)
	movl	%ecx,16-16(%esp)
	xorl	%ebx,%ebx
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%bl
	movl	%edx,%edi
	sall	$2,%ebx
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%edi,%eax),%al
	movl	%edx,(%ecx,%esi)
	andb	%al,23-16(%esp)
	movb	23-16(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	GLOBL(W24)(%ebx),%eax
	movb	%cl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d050:
	ret

FUNC(op_c120)

	subl	$8,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ebx
	movb	%al,19-12(%esp)
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ebx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	movl	%edx,%edi
	movl	%ecx,12-12(%esp)
	andl	$65535,%edi
	movl	GLOBL(R24)(%ecx),%eax
	movb	(%edi,%eax),%al
	movl	%edx,(%ebx,%esi)
	andb	%al,19-12(%esp)
	movb	19-12(%esp),%cl
	testb	%cl,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	12-12(%esp),%ecx
	movl	GLOBL(W24)(%ecx),%eax
	movb	19-12(%esp),%cl
	movb	%cl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d051:
	ret

FUNC(op_c128)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d015:
	rolw	$8,%dx
	addl	$8,%ecx
	movswl	%dx,%edx
	addl	(%esi,%ecx,4),%edx
	shrl	$7,%ebx
	movl	%edx,%ecx
	andl	$28,%ebx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	(%ebx,%esi),%bl
	movl	GLOBL(R24)(%ecx),%eax
	andb	(%edx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%al,(%edx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d052:
	ret

FUNC(op_c138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d016:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	andl	$28,%ebx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%ecx),%eax
	andb	(%edx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%al,(%edx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d053:
	ret

FUNC(op_c139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_d017:
	bswapl	%ecx
	movl	%ecx,%edx
	andl	$28,%ebx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%edx),%eax
	andb	(%ecx,%eax),%bl
	movb	%bl,%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d054:
	ret

FUNC(op_c140)

	movl	%eax,%ecx
	movl	%eax,%ebx
	shrl	$7,%ecx
	andl	$7,%ebx
	movl	$GLOBL(regs),%eax
	sall	$2,%ebx
	andl	$28,%ecx
	movl	(%ebx,%eax),%edx
	movl	(%ecx,%eax),%esi
	movl	%edx,(%ecx,%eax)
	movl	%esi,(%ebx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d055:
	ret

FUNC(op_c148)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	movl	%edx,%ebx
	shrl	$9,%eax
	andl	$7,%ebx
	andl	$7,%eax
	addl	$8,%ebx
	addl	$8,%eax
	sall	$2,%ebx
	sall	$2,%eax
	movl	(%ebx,%ecx),%edx
	movl	(%eax,%ecx),%esi
	movl	%edx,(%eax,%ecx)
	movl	%esi,(%ebx,%ecx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d056:
	ret

FUNC(op_c150)

	xorl	%edx,%edx
	movl	%eax,%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%esi,%eax,4),%dl
	movw	(%esi,%eax,4),%cx
	sall	$2,%edx
	shrl	$7,%ebx
	movl	GLOBL(R24)(%edx),%eax
	andl	$28,%ebx
	addl	%ecx,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	andw	(%ebx,%esi),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d057:
	ret

FUNC(op_c158)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$7,%eax
	andl	$7,%ecx
	movl	$GLOBL(regs),%ebp
	andl	$28,%eax
	addl	$8,%ecx
	sall	$2,%ecx
	movw	(%eax,%ebp),%di
	xorl	%ebx,%ebx
	movb	2(%ecx,%ebp),%bl
	movl	(%ecx,%ebp),%edx
	sall	$2,%ebx
	movl	%edx,%esi
	movl	%ebx,16-16(%esp)
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%edx
	addl	%esi,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%ebp)
	andl	%eax,%edi
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%di,%ax
	movl	16-16(%esp),%ebx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebx),%esi
	movw	%ax,(%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d058:
	ret

FUNC(op_c160)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%ecx
	movl	$GLOBL(regs),%ebp
	addl	$8,%ecx
	sall	$2,%ecx
	movl	(%ecx,%ebp),%edx
	addl	$-2,%edx
	shrl	$7,%eax
	movl	%edx,%ebx
	andl	$28,%eax
	shrl	$14,%ebx
	movw	(%eax,%ebp),%di
	andl	$1020,%ebx
	movl	%edx,%esi
	movl	%ebx,16-16(%esp)
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%ebp)
	andl	%eax,%edi
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%di,%ax
	movl	16-16(%esp),%ebx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebx),%esi
	movw	%ax,(%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d059:
	ret

FUNC(op_c168)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	addl	$8,%ecx
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d018:
	rolw	$8,%dx
	movswl	%dx,%edx
	addl	(%esi,%ecx,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	shrl	$7,%ebx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	andl	$28,%ebx
	addl	%edx,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	andw	(%ebx,%esi),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d060:
	ret

FUNC(op_c178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d019:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	andl	$28,%ebx
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andw	GLOBL(regs)(%ebx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d061:
	ret

FUNC(op_c179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_d020:
	bswapl	%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	andl	$28,%ebx
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andw	GLOBL(regs)(%ebx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d062:
	ret

FUNC(op_c188)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	andl	$7,%edx
	movl	%eax,%ebx
	addl	$8,%edx
	shrl	$7,%ebx
	sall	$2,%edx
	andl	$28,%ebx
	movl	(%edx,%ecx),%eax
	movl	(%ebx,%ecx),%esi
	movl	%eax,(%ebx,%ecx)
	movl	%esi,(%edx,%ecx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d063:
	ret

FUNC(op_c190)

	xorl	%ecx,%ecx
	movl	%eax,%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	xorl	%edx,%edx
	movb	2(%esi,%eax,4),%cl
	movw	(%esi,%eax,4),%dx
	sall	$2,%ecx
	movl	GLOBL(R24)(%ecx),%eax
	shrl	$7,%ebx
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ebx,%esi),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d064:
	ret

FUNC(op_c198)

	movl	%eax,%edx
	pushl	%edi
	pushl	%esi
	shrl	$7,%eax
	movl	$GLOBL(regs),%edi
	movl	%edx,%esi
	pushl	%ebx
	andl	$7,%esi
	andl	$28,%eax
	addl	$8,%esi
	movl	(%eax,%edi),%ebp
	sall	$2,%esi
	xorl	%ebx,%ebx
	movl	(%esi,%edi),%ecx
	movb	2(%esi,%edi),%bl
	movl	%ecx,%edx
	sall	$2,%ebx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%edx,%eax
	addl	$4,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%esi,%edi)
	andl	%eax,%ebp
	testl	%ebp,%ebp
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ebx),%edx
	bswapl	%ebp
	movl	%ebp,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d065:
	ret

FUNC(op_c1a0)

	movl	%eax,%edx
	movl	%edx,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%edi),%ecx
	shrl	$7,%eax
	addl	$-4,%ecx
	andl	$28,%eax
	movl	%ecx,%ebx
	movl	(%eax,%edi),%ebp
	shrl	$14,%ebx
	movl	%ecx,%edx
	andl	$1020,%ebx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%esi,%edi)
	andl	%eax,%ebp
	testl	%ebp,%ebp
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ebx),%edx
	bswapl	%ebp
	movl	%ebp,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d066:
	ret

FUNC(op_c1a8)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d021:
	rolw	$8,%dx
	addl	$8,%ecx
	movswl	%dx,%edx
	addl	(%esi,%ecx,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	shrl	$7,%ebx
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	andl	(%ebx,%esi),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d067:
	ret

FUNC(op_c1b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d022:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	andl	GLOBL(regs)(%ebx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d068:
	ret

FUNC(op_c1b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_d023:
	bswapl	%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	andl	$28,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	andl	GLOBL(regs)(%ebx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d069:
	ret

FUNC(op_c1c0)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$7,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$28,%ecx
	movswl	(%ebx,%edx,4),%edx
	movswl	(%ecx,%ebx),%eax
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d070:
	ret

FUNC(op_c1d0)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	%eax,%edx
	movswl	(%ecx,%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d071:
	ret

FUNC(op_c1d8)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%eax,%edi
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	shrl	$7,%edi
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$2,%edx
	movw	%ax,18-12(%esp)
	andl	$28,%edi
	movl	%edx,(%ecx,%esi)
	movswl	(%edi,%esi),%eax
	movswl	18-12(%esp),%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d072:
	ret

FUNC(op_c1e0)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	(%ecx,%esi),%ebx
	movl	%eax,%edi
	addl	$-2,%ebx
	shrl	$7,%edi
	movl	%ebx,12-12(%esp)
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	12-12(%esp),%ebx
	andl	$28,%edi
	movl	%ebx,(%ecx,%esi)
	movl	%eax,%edx
	movswl	(%edi,%esi),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d073:
	ret

FUNC(op_c1e8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d024:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ebx
	movl	%eax,%edx
	movswl	(%ebx,%ecx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d074:
	ret

FUNC(op_c1f8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d025:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	movswl	(%ecx,%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d075:
	ret

FUNC(op_c1f9)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d026:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	movswl	(%ecx,%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d076:
	ret

FUNC(op_c1fa)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d027:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$GLOBL(regs),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ebx
	movl	%eax,%edx
	movswl	(%ebx,%ecx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d077:
	ret

FUNC(op_c1fc)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d028:
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%eax,%edx
	movswl	(%ecx,%ebx),%eax
	movswl	%dx,%edx
	imull	%edx,%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ecx,%ebx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d078:
	ret

FUNC(op_d000)

	subl	$4,%esp
	movl	%eax,%ecx
	movl	%eax,%edx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	andl	$7,%ecx
	movb	(%edx,%eax),%bl
	addb	(%eax,%ecx,4),%bl
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
	jl	JJ_d079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d079:
	ret

FUNC(op_d010)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%esi,%esi
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%bl
	movw	(%edx,%eax,4),%si
	andl	$28,%ecx
	movl	GLOBL(R24)(,%ebx,4),%eax
	movb	(%ecx,%edx),%bl
	addb	(%esi,%eax),%bl
	pushfl
	popl	%edi
	movl	%edi,regflags
	movl	%edi,regflags+4

	movl	%ebx,%eax
	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d080:
	ret

FUNC(op_d018)

	subl	$8,%esp
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%esi
	shrl	$7,%esi
	leal	8(%ebp),%ebx
	xorl	%eax,%eax
	sall	$2,%ebx
	andl	$28,%esi
	movb	2(%ebx,%ecx),%al
	movl	(%ebx,%ecx),%edx
	movl	(%ebx,%ecx),%edi
	andl	$65535,%edx
	movl	GLOBL(R24)(,%eax,4),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edi
	movb	(%edx,%eax),%al
	movl	%edi,(%ebx,%ecx)
	movb	(%esi,%ecx),%dl
	addb	%al,%dl
	pushfl
	popl	%edi
	movl	%edi,regflags
	movl	%edi,regflags+4

	movl	%edx,%eax
	movb	%al,(%esi,%ecx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d081:
	ret

FUNC(op_d020)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%eax
	leal	8(%eax),%ebx
	movl	$GLOBL(regs),%ecx
	sall	$2,%ebx
	movl	%edx,%edi
	movl	%ebx,12-12(%esp)
	shrl	$7,%edi
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ebx,%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%edi
	movb	(%esi,%eax),%al
	movl	%edx,(%ebx,%ecx)
	movb	(%edi,%ecx),%bl
	addb	%al,%bl
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ebx,%eax
	movb	%al,(%edi,%ecx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d082:
	ret

FUNC(op_d028)

	movl	%eax,%edx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_d029:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	andl	$28,%ebx
	shrl	$14,%edx
	movb	GLOBL(regs)(%ebx),%cl
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	addb	(%eax,%edx),%cl
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,%eax
	movb	%al,GLOBL(regs)(%ebx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d083:
	ret

FUNC(op_d038)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d030:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ecx
	movl	%eax,8-8(%esp)
	andl	$65535,%edx
	movl	$GLOBL(regs),%eax
	movl	8-8(%esp),%esi
	movb	(%ecx,%eax),%bl
	addb	(%edx,%esi),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%edx
	movb	%dl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d084:
	ret

FUNC(op_d039)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_d031:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ecx
	movl	%eax,8-8(%esp)
	andl	$65535,%edx
	movl	$GLOBL(regs),%eax
	movl	8-8(%esp),%esi
	movb	(%ecx,%eax),%bl
	addb	(%edx,%esi),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%edx
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d085:
	ret

FUNC(op_d03a)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_d032:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ecx
	movl	%eax,8-8(%esp)
	andl	$65535,%edx
	movl	$GLOBL(regs),%eax
	movl	8-8(%esp),%esi
	movb	(%ecx,%eax),%bl
	addb	(%edx,%esi),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%edx
	movb	%dl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d086:
	ret

FUNC(op_d03c)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	movl	GLOBL(regs)+88,%ecx
	movb	(%edx,%eax),%bl
	addb	0x2164334A+3(%ecx),%bl
RR3_d001:
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
	jl	JJ_d087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d087:
	ret

FUNC(op_d040)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	andl	$7,%ecx
	movw	(%edx,%eax),%si
	addw	(%eax,%ecx,4),%si
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
	jl	JJ_d088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d088:
	ret

FUNC(op_d048)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%ecx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	addl	$8,%ecx
	movw	(%edx,%eax),%si
	addw	(%eax,%ecx,4),%si
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
	jl	JJ_d089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d089:
	ret

FUNC(op_d050)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%bl
	movw	(%edx,%eax,4),%ax
	andl	$65535,%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movw	(%ecx,%edx),%si
	addw	%ax,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%eax
	movw	%ax,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d090:
	ret

FUNC(op_d058)

	subl	$8,%esp
	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	%eax,%esi
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	shrl	$7,%esi
	movl	(%ecx,%ebx),%eax
	movb	2(%ecx,%ebx),%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%ecx,%ebx),%edx
	andl	$28,%esi
	addl	$2,%edx
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edx,(%ecx,%ebx)
	movl	%edi,%eax
	movw	(%esi,%ebx),%dx
	addw	%ax,%dx
	pushfl
	popl	%edi
	movl	%edi,regflags
	movl	%edi,regflags+4

	movl	%edx,%eax
	movw	%ax,(%esi,%ebx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d091:
	ret

FUNC(op_d060)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%eax,%edi
	addl	$-2,%ecx
	shrl	$7,%edi
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
	andl	$28,%edi
	movl	%ecx,(%ebx,%esi)
	movw	(%edi,%esi),%cx
	addw	%ax,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,%eax
	movw	%ax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d092:
	ret

FUNC(op_d068)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d033:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ebx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movw	(%ebx,%ecx),%si
	addw	%ax,%si
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%esi,%eax
	movw	%ax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d093:
	ret

FUNC(op_d078)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d034:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	$GLOBL(regs),%eax
	movw	(%ecx,%eax),%si
	addw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d094:
	ret

FUNC(op_d079)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d035:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	$GLOBL(regs),%eax
	movw	(%ecx,%eax),%si
	addw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d095:
	ret

FUNC(op_d07a)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d036:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	$GLOBL(regs),%eax
	movw	(%ecx,%eax),%si
	addw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d096:
	ret

FUNC(op_d07c)

	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_d037:
	rolw	$8,%cx
	andl	$28,%edx
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
	jl	JJ_d097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d097:
	ret

FUNC(op_d080)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$28,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(%edx),%ecx
	addl	GLOBL(regs)(,%eax,4),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d098:
	ret

FUNC(op_d088)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(%edx),%ecx
	addl	GLOBL(regs)(,%eax,4),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d099:
	ret

FUNC(op_d090)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%bl
	movw	(%edx,%eax,4),%ax
	andl	$65535,%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(,%ebx,4),%eax
	movl	(%ecx,%edx),%esi
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%esi
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%esi,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d100:
	ret

FUNC(op_d098)

	subl	$4,%esp
	movl	%eax,%ecx
	xorl	%edx,%edx
	andl	$7,%ecx
	movl	%eax,%edi
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	shrl	$7,%edi
	movl	(%ecx,%ebx),%eax
	movb	2(%ecx,%ebx),%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%ecx,%ebx),%edx
	andl	$28,%edi
	addl	$4,%edx
	movl	(%eax),%eax
	movl	%edx,(%ecx,%ebx)
	bswapl	%eax
	movl	(%edi,%ebx),%edx
	addl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%edx,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d101:
	ret

FUNC(op_d0a0)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
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
	movl	(%eax),%eax
	movl	%ecx,(%ebx,%esi)
	bswapl	%eax
	movl	(%edi,%esi),%edx
	addl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%edx,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d102:
	ret

FUNC(op_d0a8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d038:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ebx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%ebx,%ecx),%esi
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%esi
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%esi,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d103:
	ret

FUNC(op_d0b8)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_d039:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ebx
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d104:
	ret

FUNC(op_d0b9)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_d040:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ebx
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d105:
	ret

FUNC(op_d0ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_d041:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ebx
	movl	(%eax),%eax
	bswapl	%eax
	addl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d106:
	ret

FUNC(op_d0bc)

	movl	GLOBL(regs)+88,%edx
	shrl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_d042:
	andl	$28,%eax
	bswapl	%edx
	movl	GLOBL(regs)(%eax),%ecx
	addl	%edx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,GLOBL(regs)(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d107:
	ret

FUNC(op_d0c0)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	movswl	GLOBL(regs)(,%eax,4),%eax
	addl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d108:
	ret

FUNC(op_d0c8)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	addl	$8,%eax
	addl	$8,%edx
	movswl	GLOBL(regs)(,%eax,4),%eax
	addl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d109:
	ret

FUNC(op_d0d0)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%bl
	movw	(%ecx,%eax,4),%ax
	shrl	$9,%edx
	andl	$65535,%eax
	andl	$7,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	%eax,(%ecx,%edx,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d110:
	ret

FUNC(op_d0d8)

	subl	$4,%esp
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
	andl	$7,%edi
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%ebx),%edx
	addl	$8,%edi
	addl	$2,%edx
	cwtl
	movl	%edx,(%ecx,%ebx)
	addl	%eax,(%ebx,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d111:
	ret

FUNC(op_d0e0)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	%eax,%edi
	movl	(%ebx,%esi),%ecx
	shrl	$9,%edi
	addl	$-2,%ecx
	andl	$7,%edi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%edi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	%ecx,(%ebx,%esi)
	cwtl
	addl	%eax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_d112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d207:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d112:
	ret

FUNC(op_d0e8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_d043:
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
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%ecx
	cwtl
	addl	%eax,(%ebx,%ecx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_d113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_d208:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_d113:
	ret

FUNC(Init020_0d)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_d000-4
	movl	%eax,RR0_d001-4
	movl	%eax,RR0_d002-4
	movl	%eax,RR0_d003-4
	movl	%eax,RR0_d004-4
	movl	%eax,RR0_d005-4
	movl	%eax,RR0_d006-4
	movl	%eax,RR0_d007-4
	movl	%eax,RR0_d008-4
	movl	%eax,RR0_d009-4
	movl	%eax,RR0_d010-4
	movl	%eax,RR0_d011-4
	movl	%eax,RR0_d012-4
	movl	%eax,RR0_d013-4
	movl	%eax,RR0_d014-4
	movl	%eax,RR0_d015-4
	movl	%eax,RR0_d016-4
	movl	%eax,RR0_d017-4
	movl	%eax,RR0_d018-4
	movl	%eax,RR0_d019-4
	movl	%eax,RR0_d020-4
	movl	%eax,RR0_d021-4
	movl	%eax,RR0_d022-4
	movl	%eax,RR0_d023-4
	movl	%eax,RR0_d024-4
	movl	%eax,RR0_d025-4
	movl	%eax,RR0_d026-4
	movl	%eax,RR0_d027-4
	movl	%eax,RR0_d028-4
	movl	%eax,RR0_d029-4
	movl	%eax,RR0_d030-4
	movl	%eax,RR0_d031-4
	movl	%eax,RR0_d032-4
	movl	%eax,RR0_d033-4
	movl	%eax,RR0_d034-4
	movl	%eax,RR0_d035-4
	movl	%eax,RR0_d036-4
	movl	%eax,RR0_d037-4
	movl	%eax,RR0_d038-4
	movl	%eax,RR0_d039-4
	movl	%eax,RR0_d040-4
	movl	%eax,RR0_d041-4
	movl	%eax,RR0_d042-4
	movl	%eax,RR0_d043-4
	movl	%eax,RR0_d044-4
	movl	%eax,RR0_d045-4
	movl	%eax,RR0_d046-4
	movl	%eax,RR0_d047-4
	movl	%eax,RR0_d048-4
	movl	%eax,RR0_d049-4
	movl	%eax,RR0_d050-4
	movl	%eax,RR0_d051-4
	movl	%eax,RR0_d052-4
	movl	%eax,RR0_d053-4
	movl	%eax,RR0_d054-4
	movl	%eax,RR0_d055-4
	movl	%eax,RR0_d056-4
	movl	%eax,RR0_d057-4
	movl	%eax,RR0_d058-4
	movl	%eax,RR0_d059-4
	movl	%eax,RR0_d060-4
	movl	%eax,RR0_d061-4
	movl	%eax,RR0_d062-4
	movl	%eax,RR0_d063-4
	movl	%eax,RR0_d064-4
	movl	%eax,RR0_d065-4
	movl	%eax,RR0_d066-4
	movl	%eax,RR0_d067-4
	movl	%eax,RR0_d068-4
	movl	%eax,RR0_d069-4
	movl	%eax,RR0_d070-4
	movl	%eax,RR0_d071-4
	movl	%eax,RR0_d072-4
	movl	%eax,RR0_d073-4
	movl	%eax,RR0_d074-4
	movl	%eax,RR0_d075-4
	movl	%eax,RR0_d076-4
	movl	%eax,RR0_d077-4
	movl	%eax,RR0_d078-4
	movl	%eax,RR0_d079-4
	movl	%eax,RR0_d080-4
	movl	%eax,RR0_d081-4
	movl	%eax,RR0_d082-4
	movl	%eax,RR0_d083-4
	movl	%eax,RR0_d084-4
	movl	%eax,RR0_d085-4
	movl	%eax,RR0_d086-4
	movl	%eax,RR0_d087-4
	movl	%eax,RR0_d088-4
	movl	%eax,RR0_d089-4
	movl	%eax,RR0_d090-4
	movl	%eax,RR0_d091-4
	movl	%eax,RR0_d092-4
	movl	%eax,RR0_d093-4
	movl	%eax,RR0_d094-4
	movl	%eax,RR0_d095-4
	movl	%eax,RR0_d096-4
	movl	%eax,RR0_d097-4
	movl	%eax,RR0_d098-4
	movl	%eax,RR0_d099-4
	movl	%eax,RR0_d100-4
	movl	%eax,RR0_d101-4
	movl	%eax,RR0_d102-4
	movl	%eax,RR0_d103-4
	movl	%eax,RR0_d104-4
	movl	%eax,RR0_d105-4
	movl	%eax,RR0_d106-4
	movl	%eax,RR0_d107-4
	movl	%eax,RR0_d108-4
	movl	%eax,RR0_d109-4
	movl	%eax,RR0_d110-4
	movl	%eax,RR0_d111-4
	movl	%eax,RR0_d112-4
	movl	%eax,RR0_d113-4
	movl	%eax,RR0_d114-4
	movl	%eax,RR0_d115-4
	movl	%eax,RR0_d116-4
	movl	%eax,RR0_d117-4
	movl	%eax,RR0_d118-4
	movl	%eax,RR0_d119-4
	movl	%eax,RR0_d120-4
	movl	%eax,RR0_d121-4
	movl	%eax,RR0_d122-4
	movl	%eax,RR0_d123-4
	movl	%eax,RR0_d124-4
	movl	%eax,RR0_d125-4
	movl	%eax,RR0_d126-4
	movl	%eax,RR0_d127-4
	movl	%eax,RR0_d128-4
	movl	%eax,RR0_d129-4
	movl	%eax,RR0_d130-4
	movl	%eax,RR0_d131-4
	movl	%eax,RR0_d132-4
	movl	%eax,RR0_d133-4
	movl	%eax,RR0_d134-4
	movl	%eax,RR0_d135-4
	movl	%eax,RR0_d136-4
	movl	%eax,RR0_d137-4
	movl	%eax,RR0_d138-4
	movl	%eax,RR0_d139-4
	movl	%eax,RR0_d140-4
	movl	%eax,RR0_d141-4
	movl	%eax,RR0_d142-4
	movl	%eax,RR0_d143-4
	movl	%eax,RR0_d144-4
	movl	%eax,RR0_d145-4
	movl	%eax,RR0_d146-4
	movl	%eax,RR0_d147-4
	movl	%eax,RR0_d148-4
	movl	%eax,RR0_d149-4
	movl	%eax,RR0_d150-4
	movl	%eax,RR0_d151-4
	movl	%eax,RR0_d152-4
	movl	%eax,RR0_d153-4
	movl	%eax,RR0_d154-4
	movl	%eax,RR0_d155-4
	movl	%eax,RR0_d156-4
	movl	%eax,RR0_d157-4
	movl	%eax,RR0_d158-4
	movl	%eax,RR0_d159-4
	movl	%eax,RR0_d160-4
	movl	%eax,RR0_d161-4
	movl	%eax,RR0_d162-4
	movl	%eax,RR0_d163-4
	movl	%eax,RR0_d164-4
	movl	%eax,RR0_d165-4
	movl	%eax,RR0_d166-4
	movl	%eax,RR0_d167-4
	movl	%eax,RR0_d168-4
	movl	%eax,RR0_d169-4
	movl	%eax,RR0_d170-4
	movl	%eax,RR0_d171-4
	movl	%eax,RR0_d172-4
	movl	%eax,RR0_d173-4
	movl	%eax,RR0_d174-4
	movl	%eax,RR0_d175-4
	movl	%eax,RR0_d176-4
	movl	%eax,RR0_d177-4
	movl	%eax,RR0_d178-4
	movl	%eax,RR0_d179-4
	movl	%eax,RR0_d180-4
	movl	%eax,RR0_d181-4
	movl	%eax,RR0_d182-4
	movl	%eax,RR0_d183-4
	movl	%eax,RR0_d184-4
	movl	%eax,RR0_d185-4
	movl	%eax,RR0_d186-4
	movl	%eax,RR0_d187-4
	movl	%eax,RR0_d188-4
	movl	%eax,RR0_d189-4
	movl	%eax,RR0_d190-4
	movl	%eax,RR0_d191-4
	movl	%eax,RR0_d192-4
	movl	%eax,RR0_d193-4
	movl	%eax,RR0_d194-4
	movl	%eax,RR0_d195-4
	movl	%eax,RR0_d196-4
	movl	%eax,RR0_d197-4
	movl	%eax,RR0_d198-4
	movl	%eax,RR0_d199-4
	movl	%eax,RR0_d200-4
	movl	%eax,RR0_d201-4
	movl	%eax,RR0_d202-4
	movl	%eax,RR0_d203-4
	movl	%eax,RR0_d204-4
	movl	%eax,RR0_d205-4
	movl	%eax,RR0_d206-4
	movl	%eax,RR0_d207-4
	movl	%eax,RR0_d208-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_d000-4
	movl	%eax,RR2_d001-4
	movl	%eax,RR2_d002-4
	movl	%eax,RR2_d003-4
	movl	%eax,RR2_d004-4
	movl	%eax,RR2_d005-4
	movl	%eax,RR2_d006-4
	movl	%eax,RR2_d007-4
	movl	%eax,RR2_d008-4
	movl	%eax,RR2_d009-4
	movl	%eax,RR2_d010-4
	movl	%eax,RR2_d011-4
	movl	%eax,RR2_d012-4
	movl	%eax,RR2_d013-4
	movl	%eax,RR2_d014-4
	movl	%eax,RR2_d015-4
	movl	%eax,RR2_d016-4
	movl	%eax,RR2_d017-4
	movl	%eax,RR2_d018-4
	movl	%eax,RR2_d019-4
	movl	%eax,RR2_d020-4
	movl	%eax,RR2_d021-4
	movl	%eax,RR2_d022-4
	movl	%eax,RR2_d023-4
	movl	%eax,RR2_d024-4
	movl	%eax,RR2_d025-4
	movl	%eax,RR2_d026-4
	movl	%eax,RR2_d027-4
	movl	%eax,RR2_d028-4
	movl	%eax,RR2_d029-4
	movl	%eax,RR2_d030-4
	movl	%eax,RR2_d031-4
	movl	%eax,RR2_d032-4
	movl	%eax,RR2_d033-4
	movl	%eax,RR2_d034-4
	movl	%eax,RR2_d035-4
	movl	%eax,RR2_d036-4
	movl	%eax,RR2_d037-4
	movl	%eax,RR2_d038-4
	movl	%eax,RR2_d039-4
	movl	%eax,RR2_d040-4
	movl	%eax,RR2_d041-4
	movl	%eax,RR2_d042-4
	movl	%eax,RR2_d043-4
	incl	%eax
	movl	%eax,RR3_d000-4
	movl	%eax,RR3_d001-4
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
