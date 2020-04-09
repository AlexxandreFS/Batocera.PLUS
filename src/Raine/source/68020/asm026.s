

FUNC(op_4230)

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
RR0_6000:
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
	jne	L_6_388
	movswl	%di,%edi
L_6_388:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_389
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_390
	movl	%ebp,%ebx
L_6_390:
	testl	$64,%esi
	je	L_6_391
	movl	%ebp,%edi
L_6_391:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_392
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_392:
	cmpl	$48,%edx
	jne	L_6_395
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_395:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_398
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_398:
	cmpl	$3,16-16(%esp)
	jne	L_6_401
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_401:
	andl	$4,%esi
	jne	L_6_404
	addl	%edi,%ebx
L_6_404:
	cmpl	$0,16-16(%esp)
	je	L_6_405
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_405:
	testl	%esi,%esi
	je	L_6_408
	addl	%edi,%ebx
L_6_408:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_409
	.align	2,0x90
L_6_389:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_6_409:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6000:
	ret

FUNC(op_4270)

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
RR0_6006:
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
	jne	L_6_470
	movswl	%di,%edi
L_6_470:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_471
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_472
	movl	%ebp,%ebx
L_6_472:
	testl	$64,%esi
	je	L_6_473
	movl	%ebp,%edi
L_6_473:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_474
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_474:
	cmpl	$48,%edx
	jne	L_6_477
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_477:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_480
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_480:
	cmpl	$3,16-16(%esp)
	jne	L_6_483
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_483:
	andl	$4,%esi
	jne	L_6_486
	addl	%edi,%ebx
L_6_486:
	cmpl	$0,16-16(%esp)
	je	L_6_487
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_487:
	testl	%esi,%esi
	je	L_6_490
	addl	%edi,%ebx
L_6_490:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_491
	.align	2,0x90
L_6_471:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_6_491:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	$64,regflags
	addl	GLOBL(W24)(%eax),%edx
	xorl	%eax,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6001:
	ret

FUNC(op_42b0)

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
RR0_6012:
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
	jne	L_6_557
	movswl	%di,%edi
L_6_557:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_558
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_559
	movl	%ebp,%ebx
L_6_559:
	testl	$64,%esi
	je	L_6_560
	movl	%ebp,%edi
L_6_560:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_561
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_561:
	cmpl	$48,%edx
	jne	L_6_564
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_564:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_567
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_567:
	cmpl	$3,16-16(%esp)
	jne	L_6_570
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_570:
	andl	$4,%esi
	jne	L_6_573
	addl	%edi,%ebx
L_6_573:
	cmpl	$0,16-16(%esp)
	je	L_6_574
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_574:
	testl	%esi,%esi
	je	L_6_577
	addl	%edi,%ebx
L_6_577:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_578
	.align	2,0x90
L_6_558:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_578:
	movl	%eax,%edx
	movl	$64,regflags
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ecx,%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6002:
	ret

FUNC(op_42f0)

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
RR0_6018:
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
	jne	L_6_644
	movswl	%di,%edi
L_6_644:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_645
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_646
	movl	%ebp,%ebx
L_6_646:
	testl	$64,%esi
	je	L_6_647
	movl	%ebp,%edi
L_6_647:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_648
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6019:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_648:
	cmpl	$48,%edx
	jne	L_6_651
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_651:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_654
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_654:
	cmpl	$3,16-16(%esp)
	jne	L_6_657
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_657:
	andl	$4,%esi
	jne	L_6_660
	addl	%edi,%ebx
L_6_660:
	cmpl	$0,16-16(%esp)
	je	L_6_661
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_661:
	testl	%esi,%esi
	je	L_6_664
	addl	%edi,%ebx
L_6_664:
	addl	%ebp,%ebx
	jmp	L_6_665
	.align	2,0x90
L_6_645:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ebx
L_6_665:
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	movl	%ebx,%edx
	xorl	%ecx,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)+76,%cl
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6003:
	ret

FUNC(op_4430)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,28-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_6024:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%ebp,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_6_731
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_6_731:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_6_732
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_733
	movl	%ebp,%ebx
L_6_733:
	testl	$64,%esi
	je	L_6_734
	movl	%ebp,16-16(%esp)
L_6_734:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_735
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_6025:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_735:
	cmpl	$48,%edx
	jne	L_6_738
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_738:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_6_741
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_741:
	cmpl	$3,20-16(%esp)
	jne	L_6_744
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_744:
	andl	$4,%esi
	jne	L_6_747
	addl	16-16(%esp),%ebx
L_6_747:
	cmpl	$0,20-16(%esp)
	je	L_6_748
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_748:
	testl	%esi,%esi
	je	L_6_751
	addl	16-16(%esp),%ebx
L_6_751:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_752
	.align	2,0x90
L_6_732:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_6_752:
	movl	%edx,%eax
	andl	$65535,%edx
	xorl	%ecx,%ecx
	shrl	$14,%eax
	movl	%edx,20-16(%esp)
	andl	$1020,%eax
	movl	20-16(%esp),%edi
	movl	GLOBL(R24)(%eax),%edx
	subb	(%edi,%edx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%edi,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6004:
	ret

FUNC(op_4470)

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
RR0_6030:
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
	jne	L_6_834
	movswl	%di,%edi
L_6_834:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_835
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_836
	movl	%ebp,%ebx
L_6_836:
	testl	$64,%esi
	je	L_6_837
	movl	%ebp,%edi
L_6_837:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_838
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_838:
	cmpl	$48,%edx
	jne	L_6_841
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_841:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_844
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_844:
	cmpl	$3,16-16(%esp)
	jne	L_6_847
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_847:
	andl	$4,%esi
	jne	L_6_850
	addl	%edi,%ebx
L_6_850:
	cmpl	$0,16-16(%esp)
	je	L_6_851
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_851:
	testl	%esi,%esi
	je	L_6_854
	addl	%edi,%ebx
L_6_854:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_855
	.align	2,0x90
L_6_835:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_855:
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
	xorl	%ecx,%ecx
	subw	%ax,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6005:
	ret

FUNC(op_44b0)

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
RR0_6036:
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
	jne	L_6_947
	movswl	%di,%edi
L_6_947:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_948
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_949
	movl	%ebp,%ebx
L_6_949:
	testl	$64,%esi
	je	L_6_950
	movl	%ebp,%edi
L_6_950:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_951
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6037:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_951:
	cmpl	$48,%edx
	jne	L_6_954
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_954:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_957
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_957:
	cmpl	$3,16-16(%esp)
	jne	L_6_960
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_960:
	andl	$4,%esi
	jne	L_6_963
	addl	%edi,%ebx
L_6_963:
	cmpl	$0,16-16(%esp)
	je	L_6_964
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_964:
	testl	%esi,%esi
	je	L_6_967
	addl	%edi,%ebx
L_6_967:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_968
	.align	2,0x90
L_6_948:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_968:
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	movl	%eax,%edx
	movl	%ecx,16-16(%esp)
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%ecx,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,%ecx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6006:
	ret

FUNC(op_44f0)

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
RR0_6042:
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
	jne	L_6_1044
	movswl	%di,%edi
L_6_1044:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1045
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1046
	movl	%ebp,%ebx
L_6_1046:
	testl	$64,%esi
	je	L_6_1047
	movl	%ebp,%edi
L_6_1047:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1048
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6043:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1048:
	cmpl	$48,%edx
	jne	L_6_1051
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6044:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1051:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1054
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6045:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1054:
	cmpl	$3,16-16(%esp)
	jne	L_6_1057
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6046:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1057:
	andl	$4,%esi
	jne	L_6_1060
	addl	%edi,%ebx
L_6_1060:
	cmpl	$0,16-16(%esp)
	je	L_6_1061
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1061:
	testl	%esi,%esi
	je	L_6_1064
	addl	%edi,%ebx
L_6_1064:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_1065
	.align	2,0x90
L_6_1045:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_1065:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6007:
	ret

FUNC(op_44fb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_6048:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_6_1106
	movswl	%di,%edi
L_6_1106:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1107
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1108
	movl	%ebp,%ebx
L_6_1108:
	testl	$64,%esi
	je	L_6_1109
	movl	%ebp,%edi
L_6_1109:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1110
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6049:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1110:
	cmpl	$48,%edx
	jne	L_6_1113
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6050:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1113:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1116
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6051:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1116:
	cmpl	$3,16-16(%esp)
	jne	L_6_1119
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6052:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1119:
	andl	$4,%esi
	jne	L_6_1122
	addl	%edi,%ebx
L_6_1122:
	cmpl	$0,16-16(%esp)
	je	L_6_1123
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1123:
	testl	%esi,%esi
	je	L_6_1126
	addl	%edi,%ebx
L_6_1126:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_1127
	.align	2,0x90
L_6_1107:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_6_1127:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6008:
	ret

FUNC(op_4630)

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
RR0_6054:
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
	jne	L_6_1179
	movswl	%di,%edi
L_6_1179:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1180
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1181
	movl	%ebp,%ebx
L_6_1181:
	testl	$64,%esi
	je	L_6_1182
	movl	%ebp,%edi
L_6_1182:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1183
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6055:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1183:
	cmpl	$48,%edx
	jne	L_6_1186
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6056:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1186:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1189
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6057:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1189:
	cmpl	$3,16-16(%esp)
	jne	L_6_1192
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6058:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1192:
	andl	$4,%esi
	jne	L_6_1195
	addl	%edi,%ebx
L_6_1195:
	cmpl	$0,16-16(%esp)
	je	L_6_1196
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1196:
	testl	%esi,%esi
	je	L_6_1199
	addl	%edi,%ebx
L_6_1199:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_1200
	.align	2,0x90
L_6_1180:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_1200:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movsbl	(%ecx,%eax),%eax
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6009:
	ret

FUNC(op_4670)

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
RR0_6060:
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
	jne	L_6_1282
	movswl	%di,%edi
L_6_1282:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1283
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1284
	movl	%ebp,%ebx
L_6_1284:
	testl	$64,%esi
	je	L_6_1285
	movl	%ebp,%edi
L_6_1285:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1286
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6061:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1286:
	cmpl	$48,%edx
	jne	L_6_1289
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6062:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1289:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1292
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6063:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1292:
	cmpl	$3,16-16(%esp)
	jne	L_6_1295
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6064:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1295:
	andl	$4,%esi
	jne	L_6_1298
	addl	%edi,%ebx
L_6_1298:
	cmpl	$0,16-16(%esp)
	je	L_6_1299
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1299:
	testl	%esi,%esi
	je	L_6_1302
	addl	%edi,%ebx
L_6_1302:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_1303
	.align	2,0x90
L_6_1283:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_1303:
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
	cwtl
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	movl	16-16(%esp),%ecx
	rolw	$8,%ax
	addl	GLOBL(W24)(%edx),%ecx
	movw	%ax,(%ecx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6010:
	ret

FUNC(op_46b0)

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
RR0_6066:
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
	jne	L_6_1395
	movswl	%di,%edi
L_6_1395:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1396
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1397
	movl	%ebp,%ebx
L_6_1397:
	testl	$64,%esi
	je	L_6_1398
	movl	%ebp,%edi
L_6_1398:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1399
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6067:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1399:
	cmpl	$48,%edx
	jne	L_6_1402
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6068:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1402:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1405
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6069:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1405:
	cmpl	$3,16-16(%esp)
	jne	L_6_1408
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6070:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1408:
	andl	$4,%esi
	jne	L_6_1411
	addl	%edi,%ebx
L_6_1411:
	cmpl	$0,16-16(%esp)
	je	L_6_1412
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1412:
	testl	%esi,%esi
	je	L_6_1415
	addl	%edi,%ebx
L_6_1415:
	leal	(%ebp,%ebx),%eax
	jmp	L_6_1416
	.align	2,0x90
L_6_1396:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_6_1416:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	notl	%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6071:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6011:
	ret

FUNC(op_46f0)

	subl	$12,%esp
	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1500
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_6_1501
	.align	2,0x90
L_6_1500:
	movl	GLOBL(regs)+88,%ecx
	addl	$8,%eax
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_6072:
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
	jne	L_6_1504
	movswl	%di,%edi
L_6_1504:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1505
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1506
	movl	%ebp,%ebx
L_6_1506:
	testl	$64,%esi
	je	L_6_1507
	movl	%ebp,%edi
L_6_1507:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1508
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6073:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1508:
	cmpl	$48,%edx
	jne	L_6_1511
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6074:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1511:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1514
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6075:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1514:
	cmpl	$3,16-16(%esp)
	jne	L_6_1517
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6076:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1517:
	andl	$4,%esi
	jne	L_6_1520
	addl	%edi,%ebx
L_6_1520:
	cmpl	$0,16-16(%esp)
	je	L_6_1521
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1521:
	testl	%esi,%esi
	je	L_6_1524
	addl	%edi,%ebx
L_6_1524:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_1525
	.align	2,0x90
L_6_1505:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_6_1525:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
L_6_1501:
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6012:
	ret

FUNC(op_46fb)

	subl	$12,%esp
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1568
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_6_1569
	.align	2,0x90
L_6_1568:
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_6078:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_6_1573
	movswl	%di,%edi
L_6_1573:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1574
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1575
	movl	%ebp,%ebx
L_6_1575:
	testl	$64,%esi
	je	L_6_1576
	movl	%ebp,%edi
L_6_1576:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1577
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6079:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1577:
	cmpl	$48,%edx
	jne	L_6_1580
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6080:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1580:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1583
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6081:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1583:
	cmpl	$3,16-16(%esp)
	jne	L_6_1586
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6082:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1586:
	andl	$4,%esi
	jne	L_6_1589
	addl	%edi,%ebx
L_6_1589:
	cmpl	$0,16-16(%esp)
	je	L_6_1590
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1590:
	testl	%esi,%esi
	je	L_6_1593
	addl	%edi,%ebx
L_6_1593:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_1594
	.align	2,0x90
L_6_1574:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_6_1594:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
L_6_1569:
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6013:
	ret

FUNC(op_4800)

	andl	$7,%eax
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	leal	0(,%eax,4),%ebx
	movb	(%ebx,%esi),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1607
	decl	%eax
L_6_1607:
	movl	%eax,%ecx
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1608
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1608:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1609
	addl	$-96,%ecx
L_6_1609:
	testb	%cl,%cl
	je	L_6_1610
	andb	$191,%al
	movb	%al,regflags
L_6_1610:
	movb	%cl,%dl
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movb	%cl,(%ebx,%esi)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6014:
	ret

FUNC(op_4810)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%ebx
	addl	$8,%eax
	xorl	%esi,%esi
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%si
	leal	0(,%edx,4),%ebx
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1624
	decl	%eax
L_6_1624:
	movl	%eax,%ecx
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1625
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1625:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1626
	addl	$-96,%ecx
L_6_1626:
	testb	%cl,%cl
	je	L_6_1627
	andb	$191,%al
	movb	%al,regflags
L_6_1627:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%ebx),%eax
	movb	%cl,(%esi,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6085:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6015:
	ret

FUNC(op_4818)

	movl	%eax,%esi
	andl	$7,%esi
	leal	8(%esi),%ecx
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%al
	movl	%edx,%ebp
	leal	0(,%eax,4),%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%ebx,%eax
	addl	GLOBL(areg_byteinc)(,%esi,4),%edx
	andl	$15,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1632
	decl	%eax
L_6_1632:
	movl	%eax,%ecx
	movl	%ebx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1633
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1633:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1634
	addl	$-96,%ecx
L_6_1634:
	testb	%cl,%cl
	je	L_6_1635
	andb	$191,%al
	movb	%al,regflags
L_6_1635:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%edi),%eax
	movb	%cl,(%ebp,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6086:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6016:
	ret

FUNC(op_4820)

	andl	$7,%eax
	pushl	%esi
	leal	8(%eax),%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	GLOBL(regs)(%ecx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	movb	(%edi,%eax),%bl
	movl	%ebx,%eax
	andl	$15,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1640
	decl	%eax
L_6_1640:
	movl	%eax,%ecx
	movl	%ebx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1641
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1641:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1642
	addl	$-96,%ecx
L_6_1642:
	testb	%cl,%cl
	je	L_6_1643
	andb	$191,%al
	movb	%al,regflags
L_6_1643:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%esi),%eax
	movb	%cl,(%edi,%eax)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6087:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6017:
	ret

FUNC(op_4828)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_6000:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1649
	decl	%eax
L_6_1649:
	movl	%eax,%ecx
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1650
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1650:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1651
	addl	$-96,%ecx
L_6_1651:
	testb	%cl,%cl
	je	L_6_1652
	andb	$191,%al
	movb	%al,regflags
L_6_1652:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%ebx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6018:
	ret

FUNC(op_4830)

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
RR0_6089:
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
	jne	L_6_1658
	movswl	%di,%edi
L_6_1658:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1659
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1660
	movl	%ebp,%ebx
L_6_1660:
	testl	$64,%esi
	je	L_6_1661
	movl	%ebp,%edi
L_6_1661:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1662
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6090:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1662:
	cmpl	$48,%edx
	jne	L_6_1665
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6091:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1665:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1668
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6092:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1668:
	cmpl	$3,16-16(%esp)
	jne	L_6_1671
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6093:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1671:
	andl	$4,%esi
	jne	L_6_1674
	addl	%edi,%ebx
L_6_1674:
	cmpl	$0,16-16(%esp)
	je	L_6_1675
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1675:
	testl	%esi,%esi
	je	L_6_1678
	addl	%edi,%ebx
L_6_1678:
	leal	(%ebp,%ebx),%edx
	jmp	L_6_1679
	.align	2,0x90
L_6_1659:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_6_1679:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1682
	decl	%eax
L_6_1682:
	movl	%eax,%edi
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%di
	jbe	L_6_1683
	addl	$-6,%edi
	addl	$-16,%edx
L_6_1683:
	movl	%edi,%eax
	andl	$15,%eax
	movl	%edx,%edi
	addl	%eax,%edi
	movl	%edx,%eax
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
	je	L_6_1684
	addl	$-96,%edi
L_6_1684:
	movl	%edi,%ecx
	testb	%cl,%cl
	je	L_6_1685
	andb	$191,%al
	movb	%al,regflags
L_6_1685:
	movl	%edi,%eax
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%ebx),%eax
	movl	%edi,%ecx
	movb	%cl,(%esi,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6019:
	ret

FUNC(op_4838)

	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_6001:
	rolw	$8,%di
	movl	%edi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1691
	decl	%eax
L_6_1691:
	movl	%eax,%ecx
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1692
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1692:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1693
	addl	$-96,%ecx
L_6_1693:
	testb	%cl,%cl
	je	L_6_1694
	andb	$191,%al
	movb	%al,regflags
L_6_1694:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%ebx),%eax
	movb	%cl,(%esi,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6020:
	ret

FUNC(op_4839)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_6002:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%dl
	movl	%edx,%eax
	andl	$15,%eax
	negl	%eax
	testb	$1,regflags+4
	je	L_6_1700
	decl	%eax
L_6_1700:
	movl	%eax,%ecx
	movl	%edx,%eax
	andl	$240,%eax
	movl	%eax,%edx
	negw	%dx
	cmpw	$9,%cx
	jbe	L_6_1701
	addl	$-6,%ecx
	addl	$-16,%edx
L_6_1701:
	movl	%ecx,%eax
	andl	$15,%eax
	movl	%edx,%ecx
	addl	%eax,%ecx
	movl	%edx,%eax
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
	je	L_6_1702
	addl	$-96,%ecx
L_6_1702:
	testb	%cl,%cl
	je	L_6_1703
	andb	$191,%al
	movb	%al,regflags
L_6_1703:
	movb	%cl,%al
	movb	regflags,%dl
	andb	$128,%al
	andb	$127,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	GLOBL(W24)(%ebx),%eax
	movb	%cl,(%esi,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6021:
	ret

FUNC(op_4870)

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
RR0_6097:
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
	jne	L_6_1735
	movswl	%di,%edi
L_6_1735:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_6_1736
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_6_1737
	movl	%ebp,%ebx
L_6_1737:
	testl	$64,%esi
	je	L_6_1738
	movl	%ebp,%edi
L_6_1738:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_6_1739
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_6098:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_6_1739:
	cmpl	$48,%edx
	jne	L_6_1742
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6099:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_6_1742:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_6_1745
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_6100:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1745:
	cmpl	$3,16-16(%esp)
	jne	L_6_1748
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_6101:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_6_1748:
	andl	$4,%esi
	jne	L_6_1751
	addl	%edi,%ebx
L_6_1751:
	cmpl	$0,16-16(%esp)
	je	L_6_1752
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_6_1752:
	testl	%esi,%esi
	je	L_6_1755
	addl	%edi,%ebx
L_6_1755:
	addl	%ebp,%ebx
	jmp	L_6_1756
	.align	2,0x90
L_6_1736:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ebx
L_6_1756:
	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6022:
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


FUNC(op_4220)

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
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6103:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6023:
	ret

FUNC(op_4228)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6003:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	movl	$64,regflags
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	$0,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6024:
	ret

FUNC(op_4238)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6004:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6025:
	ret

FUNC(op_4239)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_6005:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$64,regflags
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	$0,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6026:
	ret

FUNC(op_4240)

	andl	$7,%eax
	movw	$0,GLOBL(regs)(,%eax,4)
	movl	$64,regflags
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6027:
	ret

FUNC(op_4250)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	$64,regflags
	addl	GLOBL(W24)(%eax),%edx
	xorl	%eax,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6028:
	ret

FUNC(op_4258)

	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	(%edx,%ecx),%eax
	leal	2(%eax),%ebx
	movl	%ebx,(%edx,%ecx)
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$64,regflags
	addl	GLOBL(W24)(%edx),%eax
	xorl	%edx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6029:
	ret

FUNC(op_4260)

	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	(%edx,%ecx),%eax
	addl	$-2,%eax
	movl	%eax,(%edx,%ecx)
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$64,regflags
	addl	GLOBL(W24)(%edx),%eax
	xorl	%edx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6030:
	ret

FUNC(op_4268)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6006:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$64,regflags
	addl	GLOBL(W24)(%edx),%eax
	xorl	%edx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6031:
	ret

FUNC(op_4278)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6007:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	$64,regflags
	addl	GLOBL(W24)(%edx),%eax
	xorl	%edx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6032:
	ret

FUNC(op_4279)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_6008:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	$64,regflags
	addl	GLOBL(W24)(%eax),%edx
	xorl	%eax,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6033:
	ret

FUNC(op_4280)

	andl	$7,%eax
	movl	$0,GLOBL(regs)(,%eax,4)
	movl	$64,regflags
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6034:
	ret

FUNC(op_4290)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%eax
	movl	$64,regflags
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	xorl	%ecx,%ecx
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6035:
	ret

FUNC(op_4298)

	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	(%edx,%ecx),%eax
	leal	4(%eax),%ebx
	movl	%ebx,(%edx,%ecx)
	movl	%eax,%edx
	movl	$64,regflags
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6036:
	ret

FUNC(op_42a0)

	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	(%edx,%ecx),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%ecx)
	movl	%eax,%edx
	movl	$64,regflags
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6037:
	ret

FUNC(op_42a8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6009:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	movl	$64,regflags
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ecx,%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6038:
	ret

FUNC(op_42b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6010:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,%edx
	movl	$64,regflags
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ecx,%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6039:
	ret

FUNC(op_42b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_6011:
	bswapl	%edx
	movl	%edx,%eax
	xorl	%ecx,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	$64,regflags
	addl	GLOBL(W24)(%eax),%edx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6040:
	ret

FUNC(op_42c0)

	movl	%eax,%ebx
	andl	$7,%ebx
	call	GLOBL(MakeSR)
	xorl	%eax,%eax
	movb	GLOBL(regs)+76,%al
	movw	%ax,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6041:
	ret

FUNC(op_42d0)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6042:
	ret

FUNC(op_42d8)

	andl	$7,%eax
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
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
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6043:
	ret

FUNC(op_42e0)

	andl	$7,%eax
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
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
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6044:
	ret

FUNC(op_42e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_6012:
	rolw	$8,%bx
	movswl	%bx,%ebx
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6045:
	ret

FUNC(op_42f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_6013:
	rolw	$8,%bx
	movswl	%bx,%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6046:
	ret

FUNC(op_42f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_6014:
	bswapl	%ebx
	call	GLOBL(MakeSR)
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	xorl	%edx,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)+76,%dl
	addl	GLOBL(W24)(%eax),%ebx
	movl	%edx,%eax
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6047:
	ret

FUNC(op_4400)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	subb	(%edx,%eax),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movb	%cl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6048:
	ret

FUNC(op_4410)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%bx
	sall	$2,%edx
	xorl	%ecx,%ecx
	movl	GLOBL(R24)(%edx),%eax
	subb	(%ebx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%ebx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6049:
	ret

FUNC(op_4418)

	movl	%eax,%ebp
	andl	$7,%ebp
	leal	8(%ebp),%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
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
	xorl	%ecx,%ecx
	subb	%al,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6050:
	ret

FUNC(op_4420)

	andl	$7,%eax
	leal	8(%eax),%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
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
	xorl	%ecx,%ecx
	subb	%al,%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%esi,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6051:
	ret

FUNC(op_4428)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_6015:
	rolw	$8,%bx
	movl	%ebx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	xorl	%ebx,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	subb	(%eax,%ecx),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%ecx
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6052:
	ret

FUNC(op_4438)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_6016:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	xorl	%ebx,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	subb	(%eax,%ecx),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%ecx
	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6053:
	ret

FUNC(op_4439)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_6017:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	xorl	%ebx,%ebx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	subb	(%ecx,%edx),%bl
	pushfl
	popl	%esi
	movl	%esi,regflags
	movl	%esi,regflags+4

	movl	%ebx,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6054:
	ret

FUNC(op_4440)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	subw	(%edx,%eax),%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movw	%cx,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6055:
	ret

FUNC(op_4450)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movl	GLOBL(R24)(%edx),%eax
	addl	%ecx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	xorl	%esi,%esi
	subw	%ax,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%eax
	addl	GLOBL(W24)(%edx),%ecx
	andl	$65535,%eax
	rolw	$8,%ax
	movw	%ax,(%ecx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6056:
	ret

FUNC(op_4458)

	movl	%eax,%edx
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	xorl	%ebx,%ebx
	movl	GLOBL(regs)(%edx),%ecx
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
	xorl	%edi,%edi
	subw	%ax,%di
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%edi,%eax
	addl	GLOBL(W24)(%ebx),%esi
	andl	$65535,%eax
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6057:
	ret

FUNC(op_4460)

	movl	%eax,%edx
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	GLOBL(regs)(%edx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%ebx
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
	xorl	%edi,%edi
	subw	%ax,%di
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%edi,%eax
	addl	GLOBL(W24)(%ebx),%esi
	andl	$65535,%eax
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6058:
	ret

FUNC(op_4468)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6018:
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
	xorl	%esi,%esi
	subw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	andl	$65535,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6059:
	ret

FUNC(op_4478)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6019:
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
	xorl	%esi,%esi
	subw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	andl	$65535,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6060:
	ret

FUNC(op_4479)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_6020:
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
	xorl	%esi,%esi
	subw	%dx,%si
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	andl	$65535,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6061:
	ret

FUNC(op_4480)

	andl	$7,%eax
	xorl	%ecx,%ecx
	subl	GLOBL(regs)(,%eax,4),%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,GLOBL(regs)(,%eax,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6062:
	ret

FUNC(op_4490)

	andl	$7,%eax
	xorl	%ecx,%ecx
	pushl	%ebx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%cl
	movw	GLOBL(regs)(,%eax,4),%dx
	sall	$2,%ecx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,%esi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%eax
	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6063:
	ret

FUNC(op_4498)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	sall	$2,%ebx
	xorl	%ecx,%ecx
	movl	GLOBL(regs)(%ebx),%esi
	movb	GLOBL(regs)+2(%ebx),%cl
	movl	%esi,%edx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	xorl	%edi,%edi
	addl	%edx,%eax
	addl	$4,%esi
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,GLOBL(regs)(%ebx)
	subl	%eax,%edi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%edi,%eax
	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6064:
	ret

FUNC(op_44a0)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	sall	$2,%ebx
	movl	GLOBL(regs)(%ebx),%esi
	addl	$-4,%esi
	movl	%esi,%ecx
	shrl	$14,%ecx
	movl	%esi,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%edi,%edi
	movl	(%eax),%eax
	bswapl	%eax
	movl	%esi,GLOBL(regs)(%ebx)
	subl	%eax,%edi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%edi,%eax
	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6065:
	ret

FUNC(op_44a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6021:
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
	movl	(%edx),%edx
	bswapl	%edx
	subl	%edx,%esi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6066:
	ret

FUNC(op_44b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6022:
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
	movl	(%edx),%edx
	bswapl	%edx
	subl	%edx,%esi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6067:
	ret

FUNC(op_44b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_6023:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	xorl	%esi,%esi
	movl	(%edx),%edx
	bswapl	%edx
	subl	%edx,%esi
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	%esi,%edx
	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6068:
	ret

FUNC(op_44c0)

	andl	$7,%eax
	movw	GLOBL(regs)(,%eax,4),%bx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6069:
	ret

FUNC(op_44d0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6070:
	ret

FUNC(op_44d8)

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
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6071:
	ret

FUNC(op_44e0)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	$GLOBL(regs),%edi
	sall	$2,%ecx
	movl	(%ecx,%edi),%ebx
	addl	$-2,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	%ebx,(%ecx,%edi)
	movl	%eax,%esi
	call	GLOBL(MakeSR)
	movl	%esi,%edx
	movb	%dl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6072:
	ret

FUNC(op_44e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6024:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6073:
	ret

FUNC(op_44f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6025:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6074:
	ret

FUNC(op_44f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_6026:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6075:
	ret

FUNC(op_44fa)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6027:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6076:
	ret

FUNC(op_44fc)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6028:
	rolw	$8,%dx
	movl	%edx,%eax
	movl	%eax,%ebx
	call	GLOBL(MakeSR)
	movb	%bl,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6077:
	ret

FUNC(op_4600)

	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movsbl	(%edx,%ecx),%eax
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6078:
	ret

FUNC(op_4610)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movl	GLOBL(R24)(%edx),%eax
	movsbl	(%ecx,%eax),%eax
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6079:
	ret

FUNC(op_4618)

	movl	%eax,%ebp
	andl	$7,%ebp
	leal	8(%ebp),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%bl
	movl	%edx,%edi
	sall	$2,%ebx
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%edi,%eax),%al
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movsbl	%al,%eax
	movl	%edx,(%ecx,%esi)
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	GLOBL(W24)(%ebx),%edx
	movb	%al,(%edi,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6080:
	ret

FUNC(op_4620)

	andl	$7,%eax
	leal	8(%eax),%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ebx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	movl	%edx,%edi
	andl	$1020,%ecx
	andl	$65535,%edi
	movl	GLOBL(R24)(%ecx),%eax
	movb	(%edi,%eax),%al
	movsbl	%al,%eax
	movl	%edx,(%ebx,%esi)
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	GLOBL(W24)(%ecx),%edx
	movb	%al,(%edi,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6081:
	ret

FUNC(op_4628)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6029:
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
	movsbl	(%eax,%edx),%edx
	notl	%edx
	testb	%dl,%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%dl,(%eax,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6082:
	ret

FUNC(op_4638)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6030:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	movsbl	(%edx,%eax),%eax
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	movb	%al,(%edx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6083:
	ret

FUNC(op_4639)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_6031:
	bswapl	%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movsbl	(%ecx,%eax),%eax
	notl	%eax
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	movb	%al,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6084:
	ret

FUNC(op_4640)

	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movswl	(%edx,%ecx),%eax
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6085:
	ret

FUNC(op_4650)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movl	GLOBL(R24)(%edx),%eax
	addl	%ecx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6086:
	ret

FUNC(op_4658)

	movl	%eax,%edx
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	xorl	%ebx,%ebx
	movl	GLOBL(regs)(%edx),%ecx
	movb	GLOBL(regs)+2(%edx),%bl
	movl	%ecx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$2,%ecx
	cwtl
	movl	%ecx,GLOBL(regs)(%edx)
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6087:
	ret

FUNC(op_4660)

	movl	%eax,%edx
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	GLOBL(regs)(%edx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%ebx
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
	cwtl
	movl	%ecx,GLOBL(regs)(%edx)
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6088:
	ret

FUNC(op_4668)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6032:
	rolw	$8,%dx
	addl	$8,%ecx
	movswl	%dx,%edx
	addl	GLOBL(regs)(,%ecx,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	notl	%eax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	andl	$65535,%eax
	addl	GLOBL(W24)(%ecx),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6089:
	ret

FUNC(op_4678)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6033:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	notl	%eax
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
	jl	JJ_6090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6090:
	ret

FUNC(op_4679)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_6034:
	bswapl	%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	notl	%eax
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
	jl	JJ_6091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6091:
	ret

FUNC(op_4680)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	(%eax,%ecx),%edx
	notl	%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%edx,(%eax,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6092:
	ret

FUNC(op_4690)

	andl	$7,%eax
	xorl	%ecx,%ecx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%cl
	movw	GLOBL(regs)(,%eax,4),%dx
	sall	$2,%ecx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	notl	%eax
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
	jl	JJ_6093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6093:
	ret

FUNC(op_4698)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	movl	$GLOBL(regs),%edi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	(%ecx,%edi),%ebx
	movzbl	2(%ecx,%edi),%esi
	movl	%ebx,%edx
	sall	$2,%esi
	andl	$65535,%edx
	movl	GLOBL(R24)(%esi),%eax
	addl	%edx,%eax
	addl	$4,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%ecx,%edi)
	notl	%eax
	testl	%eax,%eax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	addl	GLOBL(W24)(%esi),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6094:
	ret

FUNC(op_46a0)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	movl	$GLOBL(regs),%edi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	(%ecx,%edi),%ebx
	addl	$-4,%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	movl	%ebx,%edx
	andl	$1020,%esi
	andl	$65535,%edx
	movl	GLOBL(R24)(%esi),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%ecx,%edi)
	notl	%eax
	testl	%eax,%eax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	addl	GLOBL(W24)(%esi),%edx
	bswapl	%eax
	movl	%eax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6095:
	ret

FUNC(op_46a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6035:
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
	movl	(%edx),%edx
	bswapl	%edx
	notl	%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6096:
	ret

FUNC(op_46b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_6036:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	movl	(%edx),%edx
	bswapl	%edx
	notl	%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6097:
	ret

FUNC(op_46b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_6037:
	bswapl	%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	addl	%eax,%edx
	movl	(%edx),%edx
	bswapl	%edx
	notl	%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6098:
	ret

FUNC(op_46c0)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1452
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6099:
	ret
	.align	2,0x90
L_6_1452:
	movw	GLOBL(regs)(,%eax,4),%ax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6100:
	ret

FUNC(op_46d0)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1458
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6101:
	ret
	.align	2,0x90
L_6_1458:
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6102:
	ret

FUNC(op_46d8)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1468
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_6_1469
	.align	2,0x90
L_6_1468:
	leal	8(%eax),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,(%ecx,%esi)
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
L_6_1469:
	popl	%eax
	decl	%eax
	jl	JJ_6103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6103:
	ret

FUNC(op_46e0)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1478
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_6_1479
	.align	2,0x90
L_6_1478:
	leal	8(%eax),%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	addl	$-2,%ecx
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ecx,(%ebx,%esi)
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$2,GLOBL(regs)+88
L_6_1479:
	popl	%eax
	decl	%eax
	jl	JJ_6104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6104:
	ret

FUNC(op_46e8)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1488
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6105:
	ret
	.align	2,0x90
L_6_1488:
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6038:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6106:
	ret

FUNC(op_46f8)

	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1530
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6107:
	ret
	.align	2,0x90
L_6_1530:
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6039:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6108:
	ret

FUNC(op_46f9)

	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1542
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6109:
	ret
	.align	2,0x90
L_6_1542:
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_6040:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6110:
	ret

FUNC(op_46fa)

	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1554
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6111:
	ret
	.align	2,0x90
L_6_1554:
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6041:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6112:
	ret

FUNC(op_46fc)

	cmpb	$0,GLOBL(regs)+80
	jne	L_6_1599
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6113:
	ret
	.align	2,0x90
L_6_1599:
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_6042:
	rolw	$8,%dx
	movl	%edx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6114:
	ret

FUNC(op_4808)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	GLOBL(regs)+60,%eax
	addl	$8,%ecx
	movl	$GLOBL(regs),%ebx
	addl	$-4,%eax
	sall	$2,%ecx
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	(%ecx,%ebx),%esi
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%esi
	movl	%esi,(%eax)
	movl	GLOBL(regs)+60,%eax
	movl	%eax,(%ecx,%ebx)
	movl	GLOBL(regs)+88,%edx
	popl	%ebx
	movl	0x2164334A+2(%edx),%eax
RR2_6043:
	bswapl	%eax
	addl	$6,%edx
	addl	%eax,GLOBL(regs)+60
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6115:
	ret

FUNC(op_4840)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	(%eax,%ecx),%edx
	roll	$16,%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%edx,(%eax,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6116:
	ret

FUNC(op_4848)

	addl	$2,GLOBL(regs)+88
	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_6117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6117:
	ret

FUNC(op_4850)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6118
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6118:
	ret

FUNC(op_4868)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6044:
	rolw	$8,%cx
	movswl	%cx,%ecx
	movl	GLOBL(regs)+60,%eax
	addl	$8,%edx
	addl	$-4,%eax
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6119
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6119:
	ret

FUNC(op_4878)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_6045:
	rolw	$8,%cx
	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movswl	%cx,%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_6120
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_6200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_6120:
	ret

FUNC(Init020_06)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_6000-4
	movl	%eax,RR0_6001-4
	movl	%eax,RR0_6002-4
	movl	%eax,RR0_6003-4
	movl	%eax,RR0_6004-4
	movl	%eax,RR0_6005-4
	movl	%eax,RR0_6006-4
	movl	%eax,RR0_6007-4
	movl	%eax,RR0_6008-4
	movl	%eax,RR0_6009-4
	movl	%eax,RR0_6010-4
	movl	%eax,RR0_6011-4
	movl	%eax,RR0_6012-4
	movl	%eax,RR0_6013-4
	movl	%eax,RR0_6014-4
	movl	%eax,RR0_6015-4
	movl	%eax,RR0_6016-4
	movl	%eax,RR0_6017-4
	movl	%eax,RR0_6018-4
	movl	%eax,RR0_6019-4
	movl	%eax,RR0_6020-4
	movl	%eax,RR0_6021-4
	movl	%eax,RR0_6022-4
	movl	%eax,RR0_6023-4
	movl	%eax,RR0_6024-4
	movl	%eax,RR0_6025-4
	movl	%eax,RR0_6026-4
	movl	%eax,RR0_6027-4
	movl	%eax,RR0_6028-4
	movl	%eax,RR0_6029-4
	movl	%eax,RR0_6030-4
	movl	%eax,RR0_6031-4
	movl	%eax,RR0_6032-4
	movl	%eax,RR0_6033-4
	movl	%eax,RR0_6034-4
	movl	%eax,RR0_6035-4
	movl	%eax,RR0_6036-4
	movl	%eax,RR0_6037-4
	movl	%eax,RR0_6038-4
	movl	%eax,RR0_6039-4
	movl	%eax,RR0_6040-4
	movl	%eax,RR0_6041-4
	movl	%eax,RR0_6042-4
	movl	%eax,RR0_6043-4
	movl	%eax,RR0_6044-4
	movl	%eax,RR0_6045-4
	movl	%eax,RR0_6046-4
	movl	%eax,RR0_6047-4
	movl	%eax,RR0_6048-4
	movl	%eax,RR0_6049-4
	movl	%eax,RR0_6050-4
	movl	%eax,RR0_6051-4
	movl	%eax,RR0_6052-4
	movl	%eax,RR0_6053-4
	movl	%eax,RR0_6054-4
	movl	%eax,RR0_6055-4
	movl	%eax,RR0_6056-4
	movl	%eax,RR0_6057-4
	movl	%eax,RR0_6058-4
	movl	%eax,RR0_6059-4
	movl	%eax,RR0_6060-4
	movl	%eax,RR0_6061-4
	movl	%eax,RR0_6062-4
	movl	%eax,RR0_6063-4
	movl	%eax,RR0_6064-4
	movl	%eax,RR0_6065-4
	movl	%eax,RR0_6066-4
	movl	%eax,RR0_6067-4
	movl	%eax,RR0_6068-4
	movl	%eax,RR0_6069-4
	movl	%eax,RR0_6070-4
	movl	%eax,RR0_6071-4
	movl	%eax,RR0_6072-4
	movl	%eax,RR0_6073-4
	movl	%eax,RR0_6074-4
	movl	%eax,RR0_6075-4
	movl	%eax,RR0_6076-4
	movl	%eax,RR0_6077-4
	movl	%eax,RR0_6078-4
	movl	%eax,RR0_6079-4
	movl	%eax,RR0_6080-4
	movl	%eax,RR0_6081-4
	movl	%eax,RR0_6082-4
	movl	%eax,RR0_6083-4
	movl	%eax,RR0_6084-4
	movl	%eax,RR0_6085-4
	movl	%eax,RR0_6086-4
	movl	%eax,RR0_6087-4
	movl	%eax,RR0_6088-4
	movl	%eax,RR0_6089-4
	movl	%eax,RR0_6090-4
	movl	%eax,RR0_6091-4
	movl	%eax,RR0_6092-4
	movl	%eax,RR0_6093-4
	movl	%eax,RR0_6094-4
	movl	%eax,RR0_6095-4
	movl	%eax,RR0_6096-4
	movl	%eax,RR0_6097-4
	movl	%eax,RR0_6098-4
	movl	%eax,RR0_6099-4
	movl	%eax,RR0_6100-4
	movl	%eax,RR0_6101-4
	movl	%eax,RR0_6102-4
	movl	%eax,RR0_6103-4
	movl	%eax,RR0_6104-4
	movl	%eax,RR0_6105-4
	movl	%eax,RR0_6106-4
	movl	%eax,RR0_6107-4
	movl	%eax,RR0_6108-4
	movl	%eax,RR0_6109-4
	movl	%eax,RR0_6110-4
	movl	%eax,RR0_6111-4
	movl	%eax,RR0_6112-4
	movl	%eax,RR0_6113-4
	movl	%eax,RR0_6114-4
	movl	%eax,RR0_6115-4
	movl	%eax,RR0_6116-4
	movl	%eax,RR0_6117-4
	movl	%eax,RR0_6118-4
	movl	%eax,RR0_6119-4
	movl	%eax,RR0_6120-4
	movl	%eax,RR0_6121-4
	movl	%eax,RR0_6122-4
	movl	%eax,RR0_6123-4
	movl	%eax,RR0_6124-4
	movl	%eax,RR0_6125-4
	movl	%eax,RR0_6126-4
	movl	%eax,RR0_6127-4
	movl	%eax,RR0_6128-4
	movl	%eax,RR0_6129-4
	movl	%eax,RR0_6130-4
	movl	%eax,RR0_6131-4
	movl	%eax,RR0_6132-4
	movl	%eax,RR0_6133-4
	movl	%eax,RR0_6134-4
	movl	%eax,RR0_6135-4
	movl	%eax,RR0_6136-4
	movl	%eax,RR0_6137-4
	movl	%eax,RR0_6138-4
	movl	%eax,RR0_6139-4
	movl	%eax,RR0_6140-4
	movl	%eax,RR0_6141-4
	movl	%eax,RR0_6142-4
	movl	%eax,RR0_6143-4
	movl	%eax,RR0_6144-4
	movl	%eax,RR0_6145-4
	movl	%eax,RR0_6146-4
	movl	%eax,RR0_6147-4
	movl	%eax,RR0_6148-4
	movl	%eax,RR0_6149-4
	movl	%eax,RR0_6150-4
	movl	%eax,RR0_6151-4
	movl	%eax,RR0_6152-4
	movl	%eax,RR0_6153-4
	movl	%eax,RR0_6154-4
	movl	%eax,RR0_6155-4
	movl	%eax,RR0_6156-4
	movl	%eax,RR0_6157-4
	movl	%eax,RR0_6158-4
	movl	%eax,RR0_6159-4
	movl	%eax,RR0_6160-4
	movl	%eax,RR0_6161-4
	movl	%eax,RR0_6162-4
	movl	%eax,RR0_6163-4
	movl	%eax,RR0_6164-4
	movl	%eax,RR0_6165-4
	movl	%eax,RR0_6166-4
	movl	%eax,RR0_6167-4
	movl	%eax,RR0_6168-4
	movl	%eax,RR0_6169-4
	movl	%eax,RR0_6170-4
	movl	%eax,RR0_6171-4
	movl	%eax,RR0_6172-4
	movl	%eax,RR0_6173-4
	movl	%eax,RR0_6174-4
	movl	%eax,RR0_6175-4
	movl	%eax,RR0_6176-4
	movl	%eax,RR0_6177-4
	movl	%eax,RR0_6178-4
	movl	%eax,RR0_6179-4
	movl	%eax,RR0_6180-4
	movl	%eax,RR0_6181-4
	movl	%eax,RR0_6182-4
	movl	%eax,RR0_6183-4
	movl	%eax,RR0_6184-4
	movl	%eax,RR0_6185-4
	movl	%eax,RR0_6186-4
	movl	%eax,RR0_6187-4
	movl	%eax,RR0_6188-4
	movl	%eax,RR0_6189-4
	movl	%eax,RR0_6190-4
	movl	%eax,RR0_6191-4
	movl	%eax,RR0_6192-4
	movl	%eax,RR0_6193-4
	movl	%eax,RR0_6194-4
	movl	%eax,RR0_6195-4
	movl	%eax,RR0_6196-4
	movl	%eax,RR0_6197-4
	movl	%eax,RR0_6198-4
	movl	%eax,RR0_6199-4
	movl	%eax,RR0_6200-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_6000-4
	movl	%eax,RR2_6001-4
	movl	%eax,RR2_6002-4
	movl	%eax,RR2_6003-4
	movl	%eax,RR2_6004-4
	movl	%eax,RR2_6005-4
	movl	%eax,RR2_6006-4
	movl	%eax,RR2_6007-4
	movl	%eax,RR2_6008-4
	movl	%eax,RR2_6009-4
	movl	%eax,RR2_6010-4
	movl	%eax,RR2_6011-4
	movl	%eax,RR2_6012-4
	movl	%eax,RR2_6013-4
	movl	%eax,RR2_6014-4
	movl	%eax,RR2_6015-4
	movl	%eax,RR2_6016-4
	movl	%eax,RR2_6017-4
	movl	%eax,RR2_6018-4
	movl	%eax,RR2_6019-4
	movl	%eax,RR2_6020-4
	movl	%eax,RR2_6021-4
	movl	%eax,RR2_6022-4
	movl	%eax,RR2_6023-4
	movl	%eax,RR2_6024-4
	movl	%eax,RR2_6025-4
	movl	%eax,RR2_6026-4
	movl	%eax,RR2_6027-4
	movl	%eax,RR2_6028-4
	movl	%eax,RR2_6029-4
	movl	%eax,RR2_6030-4
	movl	%eax,RR2_6031-4
	movl	%eax,RR2_6032-4
	movl	%eax,RR2_6033-4
	movl	%eax,RR2_6034-4
	movl	%eax,RR2_6035-4
	movl	%eax,RR2_6036-4
	movl	%eax,RR2_6037-4
	movl	%eax,RR2_6038-4
	movl	%eax,RR2_6039-4
	movl	%eax,RR2_6040-4
	movl	%eax,RR2_6041-4
	movl	%eax,RR2_6042-4
	movl	%eax,RR2_6043-4
	movl	%eax,RR2_6044-4
	movl	%eax,RR2_6045-4
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
