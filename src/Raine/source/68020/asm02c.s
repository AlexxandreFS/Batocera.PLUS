

FUNC(op_91b0)

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
RR0_c000:
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
	jne	L_c_424
	movswl	%di,%edi
L_c_424:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_425
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_c_426
	movl	%ebp,16-16(%esp)
L_c_426:
	testl	$64,%esi
	je	L_c_427
	movl	%ebp,%edi
L_c_427:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_428
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c001:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_c_428:
	cmpl	$48,%edx
	jne	L_c_431
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c002:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_c_431:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_c_434
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_434:
	cmpl	$3,%ecx
	jne	L_c_437
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_437:
	andl	$4,%esi
	jne	L_c_440
	addl	%edi,16-16(%esp)
L_c_440:
	testl	%ecx,%ecx
	je	L_c_441
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_c_441:
	testl	%esi,%esi
	je	L_c_444
	addl	%edi,16-16(%esp)
L_c_444:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_c_445
	.align	2,0x90
L_c_425:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_445:
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
	jl	JJ_c000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c000:
	ret

FUNC(op_91f0)

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
RR0_c006:
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
	jne	L_c_525
	movswl	%di,%edi
L_c_525:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_526
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_527
	movl	%ebp,%ebx
L_c_527:
	testl	$64,%esi
	je	L_c_528
	movl	%ebp,%edi
L_c_528:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_529
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_529:
	cmpl	$48,%edx
	jne	L_c_532
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_532:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_535
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_535:
	cmpl	$3,16-16(%esp)
	jne	L_c_538
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_538:
	andl	$4,%esi
	jne	L_c_541
	addl	%edi,%ebx
L_c_541:
	cmpl	$0,16-16(%esp)
	je	L_c_542
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_542:
	testl	%esi,%esi
	je	L_c_545
	addl	%edi,%ebx
L_c_545:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_546
	.align	2,0x90
L_c_526:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_546:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	subl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c001:
	ret

FUNC(op_91fb)

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
RR0_c012:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_c_587
	movswl	%di,%edi
L_c_587:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_588
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_589
	movl	%ebp,%ebx
L_c_589:
	testl	$64,%esi
	je	L_c_590
	movl	%ebp,%edi
L_c_590:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_591
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_591:
	cmpl	$48,%edx
	jne	L_c_594
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_594:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_597
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_597:
	cmpl	$3,16-16(%esp)
	jne	L_c_600
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_600:
	andl	$4,%esi
	jne	L_c_603
	addl	%edi,%ebx
L_c_603:
	cmpl	$0,16-16(%esp)
	je	L_c_604
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_604:
	testl	%esi,%esi
	je	L_c_607
	addl	%edi,%ebx
L_c_607:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_608
	.align	2,0x90
L_c_588:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_608:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	subl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c002:
	ret

FUNC(op_b030)

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
RR0_c018:
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
	jne	L_c_652
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_652:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_653
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_654
	movl	%ebp,%ebx
L_c_654:
	testl	$64,%esi
	je	L_c_655
	movl	%ebp,16-16(%esp)
L_c_655:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_656
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c019:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_656:
	cmpl	$48,%edx
	jne	L_c_659
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_659:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_662
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_662:
	cmpl	$3,20-16(%esp)
	jne	L_c_665
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_665:
	andl	$4,%esi
	jne	L_c_668
	addl	16-16(%esp),%ebx
L_c_668:
	cmpl	$0,20-16(%esp)
	je	L_c_669
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_669:
	testl	%esi,%esi
	je	L_c_672
	addl	16-16(%esp),%ebx
L_c_672:
	leal	(%ebp,%ebx),%edx
	jmp	L_c_673
	.align	2,0x90
L_c_653:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_c_673:
	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	movl	32-16(%esp),%ecx
	andl	$1020,%eax
	movb	GLOBL(regs)(,%ecx,4),%cl
	movl	GLOBL(R24)(%eax),%eax
	cmpb	(%edx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c003:
	ret

FUNC(op_b03b)

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
RR0_c024:
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
	jne	L_c_707
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_707:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_708
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_709
	movl	%ebp,%ebx
L_c_709:
	testl	$64,%esi
	je	L_c_710
	movl	%ebp,16-16(%esp)
L_c_710:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_711
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c025:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_711:
	cmpl	$48,%edx
	jne	L_c_714
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_714:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_717
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_717:
	cmpl	$3,20-16(%esp)
	jne	L_c_720
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_720:
	andl	$4,%esi
	jne	L_c_723
	addl	16-16(%esp),%ebx
L_c_723:
	cmpl	$0,20-16(%esp)
	je	L_c_724
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_724:
	testl	%esi,%esi
	je	L_c_727
	addl	16-16(%esp),%ebx
L_c_727:
	leal	(%ebp,%ebx),%edx
	jmp	L_c_728
	.align	2,0x90
L_c_708:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_c_728:
	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	movl	32-16(%esp),%ecx
	andl	$1020,%eax
	movb	GLOBL(regs)(,%ecx,4),%cl
	movl	GLOBL(R24)(%eax),%eax
	cmpb	(%edx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c004:
	ret

FUNC(op_b070)

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
RR0_c030:
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
	jne	L_c_781
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_781:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_782
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_783
	movl	%ebp,%ebx
L_c_783:
	testl	$64,%esi
	je	L_c_784
	movl	%ebp,16-16(%esp)
L_c_784:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_785
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c031:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_785:
	cmpl	$48,%edx
	jne	L_c_788
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_788:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_791
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_791:
	cmpl	$3,20-16(%esp)
	jne	L_c_794
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_794:
	andl	$4,%esi
	jne	L_c_797
	addl	16-16(%esp),%ebx
L_c_797:
	cmpl	$0,20-16(%esp)
	je	L_c_798
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_798:
	testl	%esi,%esi
	je	L_c_801
	addl	16-16(%esp),%ebx
L_c_801:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_802
	.align	2,0x90
L_c_782:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_c_802:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	32-16(%esp),%ecx
	andl	$1020,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c005:
	ret

FUNC(op_b07b)

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
RR0_c036:
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
	jne	L_c_843
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_843:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_844
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_845
	movl	%ebp,%ebx
L_c_845:
	testl	$64,%esi
	je	L_c_846
	movl	%ebp,16-16(%esp)
L_c_846:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_847
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c037:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_847:
	cmpl	$48,%edx
	jne	L_c_850
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_850:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_853
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_853:
	cmpl	$3,20-16(%esp)
	jne	L_c_856
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_856:
	andl	$4,%esi
	jne	L_c_859
	addl	16-16(%esp),%ebx
L_c_859:
	cmpl	$0,20-16(%esp)
	je	L_c_860
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_860:
	testl	%esi,%esi
	je	L_c_863
	addl	16-16(%esp),%ebx
L_c_863:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_864
	.align	2,0x90
L_c_844:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_c_864:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	32-16(%esp),%ecx
	andl	$1020,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c006:
	ret

FUNC(op_b0b0)

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
RR0_c042:
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
	jne	L_c_920
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_920:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_921
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_922
	movl	%ebp,%ebx
L_c_922:
	testl	$64,%esi
	je	L_c_923
	movl	%ebp,16-16(%esp)
L_c_923:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_924
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c043:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_924:
	cmpl	$48,%edx
	jne	L_c_927
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c044:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_927:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_930
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c045:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_930:
	cmpl	$3,20-16(%esp)
	jne	L_c_933
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c046:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_933:
	andl	$4,%esi
	jne	L_c_936
	addl	16-16(%esp),%ebx
L_c_936:
	cmpl	$0,20-16(%esp)
	je	L_c_937
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_937:
	testl	%esi,%esi
	je	L_c_940
	addl	16-16(%esp),%ebx
L_c_940:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_941
	.align	2,0x90
L_c_921:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_c_941:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%edi
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c007:
	ret

FUNC(op_b0bb)

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
RR0_c048:
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
	jne	L_c_982
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_c_982:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_c_983
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_984
	movl	%ebp,%ebx
L_c_984:
	testl	$64,%esi
	je	L_c_985
	movl	%ebp,16-16(%esp)
L_c_985:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_986
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_c049:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_986:
	cmpl	$48,%edx
	jne	L_c_989
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c050:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_989:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_c_992
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c051:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_992:
	cmpl	$3,20-16(%esp)
	jne	L_c_995
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c052:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_995:
	andl	$4,%esi
	jne	L_c_998
	addl	16-16(%esp),%ebx
L_c_998:
	cmpl	$0,20-16(%esp)
	je	L_c_999
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_999:
	testl	%esi,%esi
	je	L_c_1002
	addl	16-16(%esp),%ebx
L_c_1002:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_1003
	.align	2,0x90
L_c_983:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_c_1003:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%edi
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c008:
	ret

FUNC(op_b0f0)

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
RR0_c054:
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
	jne	L_c_1059
	movswl	%di,%edi
L_c_1059:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1060
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_1061
	movl	%ebp,%ebx
L_c_1061:
	testl	$64,%esi
	je	L_c_1062
	movl	%ebp,%edi
L_c_1062:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1063
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c055:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_1063:
	cmpl	$48,%edx
	jne	L_c_1066
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c056:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_1066:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_1069
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c057:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1069:
	cmpl	$3,16-16(%esp)
	jne	L_c_1072
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c058:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1072:
	andl	$4,%esi
	jne	L_c_1075
	addl	%edi,%ebx
L_c_1075:
	cmpl	$0,16-16(%esp)
	je	L_c_1076
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_1076:
	testl	%esi,%esi
	je	L_c_1079
	addl	%edi,%ebx
L_c_1079:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_1080
	.align	2,0x90
L_c_1060:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1080:
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
	movl	GLOBL(regs)(,%edx,4),%edx
	cmpl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c009:
	ret

FUNC(op_b0fb)

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
RR0_c060:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_c_1121
	movswl	%di,%edi
L_c_1121:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1122
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_1123
	movl	%ebp,%ebx
L_c_1123:
	testl	$64,%esi
	je	L_c_1124
	movl	%ebp,%edi
L_c_1124:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1125
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c061:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_1125:
	cmpl	$48,%edx
	jne	L_c_1128
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c062:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_1128:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_1131
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c063:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1131:
	cmpl	$3,16-16(%esp)
	jne	L_c_1134
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c064:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1134:
	andl	$4,%esi
	jne	L_c_1137
	addl	%edi,%ebx
L_c_1137:
	cmpl	$0,16-16(%esp)
	je	L_c_1138
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_1138:
	testl	%esi,%esi
	je	L_c_1141
	addl	%edi,%ebx
L_c_1141:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_1142
	.align	2,0x90
L_c_1122:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1142:
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
	movl	GLOBL(regs)(,%edx,4),%edx
	cmpl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c010:
	ret

FUNC(op_b130)

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
RR0_c066:
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
	jne	L_c_1202
	movswl	%di,%edi
L_c_1202:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1203
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_c_1204
	movl	%ebp,16-16(%esp)
L_c_1204:
	testl	$64,%esi
	je	L_c_1205
	movl	%ebp,%edi
L_c_1205:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1206
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c067:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_c_1206:
	cmpl	$48,%edx
	jne	L_c_1209
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c068:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_c_1209:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_c_1212
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c069:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1212:
	cmpl	$3,%ecx
	jne	L_c_1215
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c070:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1215:
	andl	$4,%esi
	jne	L_c_1218
	addl	%edi,16-16(%esp)
L_c_1218:
	testl	%ecx,%ecx
	je	L_c_1219
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_c_1219:
	testl	%esi,%esi
	je	L_c_1222
	addl	%edi,16-16(%esp)
L_c_1222:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_c_1223
	.align	2,0x90
L_c_1203:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1223:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	xorb	%al,31-16(%esp)
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
	jl	JJ_c011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c071:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c011:
	ret

FUNC(op_b170)

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
RR0_c072:
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
	jne	L_c_1317
	movswl	%di,%edi
L_c_1317:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1318
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_c_1319
	movl	%ebp,16-16(%esp)
L_c_1319:
	testl	$64,%esi
	je	L_c_1320
	movl	%ebp,%edi
L_c_1320:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1321
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c073:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_c_1321:
	cmpl	$48,%edx
	jne	L_c_1324
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c074:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_c_1324:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_c_1327
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c075:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1327:
	cmpl	$3,%ecx
	jne	L_c_1330
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c076:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1330:
	andl	$4,%esi
	jne	L_c_1333
	addl	%edi,16-16(%esp)
L_c_1333:
	testl	%ecx,%ecx
	je	L_c_1334
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_c_1334:
	testl	%esi,%esi
	je	L_c_1337
	addl	%edi,16-16(%esp)
L_c_1337:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_c_1338
	.align	2,0x90
L_c_1318:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1338:
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
	xorw	%ax,30-16(%esp)
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
	jl	JJ_c012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c012:
	ret

FUNC(op_b1b0)

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
RR0_c078:
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
	jne	L_c_1442
	movswl	%di,%edi
L_c_1442:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1443
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_c_1444
	movl	%ebp,16-16(%esp)
L_c_1444:
	testl	$64,%esi
	je	L_c_1445
	movl	%ebp,%edi
L_c_1445:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1446
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c079:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_c_1446:
	cmpl	$48,%edx
	jne	L_c_1449
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c080:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_c_1449:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_c_1452
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c081:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1452:
	cmpl	$3,%ecx
	jne	L_c_1455
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c082:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1455:
	andl	$4,%esi
	jne	L_c_1458
	addl	%edi,16-16(%esp)
L_c_1458:
	testl	%ecx,%ecx
	je	L_c_1459
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_c_1459:
	testl	%esi,%esi
	je	L_c_1462
	addl	%edi,16-16(%esp)
L_c_1462:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_c_1463
	.align	2,0x90
L_c_1443:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1463:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	xorl	%eax,28-16(%esp)
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
	jl	JJ_c013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c013:
	ret

FUNC(op_b1f0)

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
RR0_c084:
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
	jne	L_c_1543
	movswl	%di,%edi
L_c_1543:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1544
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_1545
	movl	%ebp,%ebx
L_c_1545:
	testl	$64,%esi
	je	L_c_1546
	movl	%ebp,%edi
L_c_1546:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1547
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c085:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_1547:
	cmpl	$48,%edx
	jne	L_c_1550
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c086:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_1550:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_1553
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c087:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1553:
	cmpl	$3,16-16(%esp)
	jne	L_c_1556
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c088:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1556:
	andl	$4,%esi
	jne	L_c_1559
	addl	%edi,%ebx
L_c_1559:
	cmpl	$0,16-16(%esp)
	je	L_c_1560
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_1560:
	testl	%esi,%esi
	je	L_c_1563
	addl	%edi,%ebx
L_c_1563:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_1564
	.align	2,0x90
L_c_1544:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1564:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	cmpl	%edx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c089:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c014:
	ret

FUNC(op_b1fb)

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
RR0_c090:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_c_1605
	movswl	%di,%edi
L_c_1605:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1606
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_1607
	movl	%ebp,%ebx
L_c_1607:
	testl	$64,%esi
	je	L_c_1608
	movl	%ebp,%edi
L_c_1608:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1609
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c091:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_1609:
	cmpl	$48,%edx
	jne	L_c_1612
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c092:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_1612:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_1615
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c093:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1615:
	cmpl	$3,16-16(%esp)
	jne	L_c_1618
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c094:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1618:
	andl	$4,%esi
	jne	L_c_1621
	addl	%edi,%ebx
L_c_1621:
	cmpl	$0,16-16(%esp)
	je	L_c_1622
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_1622:
	testl	%esi,%esi
	je	L_c_1625
	addl	%edi,%ebx
L_c_1625:
	leal	(%ebp,%ebx),%eax
	jmp	L_c_1626
	.align	2,0x90
L_c_1606:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_c_1626:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	cmpl	%edx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c015:
	ret

FUNC(op_c030)

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
RR0_c096:
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
	jne	L_c_1670
	movswl	%di,%edi
L_c_1670:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_c_1671
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_c_1672
	movl	%ebp,%ebx
L_c_1672:
	testl	$64,%esi
	je	L_c_1673
	movl	%ebp,%edi
L_c_1673:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_c_1674
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_c097:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_c_1674:
	cmpl	$48,%edx
	jne	L_c_1677
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c098:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_c_1677:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_c_1680
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_c099:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1680:
	cmpl	$3,16-16(%esp)
	jne	L_c_1683
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_c100:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_c_1683:
	andl	$4,%esi
	jne	L_c_1686
	addl	%edi,%ebx
L_c_1686:
	cmpl	$0,16-16(%esp)
	je	L_c_1687
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_c_1687:
	testl	%esi,%esi
	je	L_c_1690
	addl	%edi,%ebx
L_c_1690:
	leal	(%ebp,%ebx),%edx
	jmp	L_c_1691
	.align	2,0x90
L_c_1671:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_c_1691:
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
	jl	JJ_c016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c016:
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


FUNC(op_9190)

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
	subl	(%ebx,%esi),%eax
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
	jl	JJ_c017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c017:
	ret

FUNC(op_9198)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%edi
	pushl	%esi
	shrl	$7,%eax
	movl	%edx,%esi
	movl	$GLOBL(regs),%edi
	andl	$7,%esi
	pushl	%ebx
	addl	$8,%esi
	andl	$28,%eax
	sall	$2,%esi
	movl	(%eax,%edi),%ebp
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
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c103:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c018:
	ret

FUNC(op_91a0)

	movl	%eax,%edx
	movl	%edx,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%edi),%ebx
	shrl	$7,%eax
	addl	$-4,%ebx
	andl	$28,%eax
	movl	%ebx,%ecx
	movl	(%eax,%edi),%ebp
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c019:
	ret

FUNC(op_91a8)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_c000:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%edx
	cwtl
	addl	(%esi,%edx,4),%eax
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
	subl	(%ebx,%esi),%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c020:
	ret

FUNC(op_91b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_c001:
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
	subl	GLOBL(regs)(%ebx),%edx
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
	jl	JJ_c021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c021:
	ret

FUNC(op_91b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_c002:
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
	subl	GLOBL(regs)(%ebx),%edx
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
	jl	JJ_c022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c022:
	ret

FUNC(op_91c0)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	addl	$8,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	subl	GLOBL(regs)(,%eax,4),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c023:
	ret

FUNC(op_91c8)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	subl	GLOBL(regs)(,%eax,4),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c024:
	ret

FUNC(op_91d0)

	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%bl
	movw	(%ecx,%eax,4),%ax
	shrl	$9,%edx
	andl	$65535,%eax
	andl	$7,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$8,%edx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,(%ecx,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c025:
	ret

FUNC(op_91d8)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	%eax,%esi
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	shrl	$9,%esi
	movl	(%ecx,%ebx),%edx
	andl	$7,%esi
	movl	%edx,%eax
	movzbl	2(%ecx,%ebx),%edi
	andl	$65535,%eax
	addl	$4,%edx
	addl	GLOBL(R24)(,%edi,4),%eax
	addl	$8,%esi
	movl	(%eax),%eax
	movl	%edx,(%ecx,%ebx)
	bswapl	%eax
	subl	%eax,(%ebx,%esi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c026:
	ret

FUNC(op_91e0)

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
	andl	$7,%edi
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%edi
	movl	(%eax),%eax
	movl	%ecx,(%ebx,%esi)
	bswapl	%eax
	subl	%eax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c027:
	ret

FUNC(op_91e8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_c003:
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
	addl	$8,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,(%ecx,%ebx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c028:
	ret

FUNC(op_91f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_c004:
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
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c029:
	ret

FUNC(op_91f9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_c005:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c030:
	ret

FUNC(op_91fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c006:
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
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c031:
	ret

FUNC(op_91fc)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_c007:
	addl	$8,%eax
	bswapl	%edx
	subl	%edx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c032:
	ret

FUNC(op_b000)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$28,%edx
	andl	$7,%eax
	movb	GLOBL(regs)(%edx),%dl
	cmpb	GLOBL(regs)(,%eax,4),%dl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c033:
	ret

FUNC(op_b010)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	shrl	$7,%edx
	movl	$GLOBL(regs),%esi
	andl	$7,%eax
	xorl	%ebx,%ebx
	addl	$8,%eax
	andl	$28,%edx
	movb	2(%esi,%eax,4),%cl
	movw	(%esi,%eax,4),%bx
	movb	(%edx,%esi),%dl
	movl	GLOBL(R24)(,%ecx,4),%eax
	cmpb	(%ebx,%eax),%dl
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c034:
	ret

FUNC(op_b018)

	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%edi
	shrl	$7,%edi
	leal	8(%ebp),%ecx
	xorl	%eax,%eax
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$28,%edi
	movl	(%ecx,%ebx),%edx
	movb	2(%ecx,%ebx),%al
	movl	%edx,%esi
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%esi
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%esi,%eax),%al
	movl	%edx,(%ecx,%ebx)
	movb	(%edi,%ebx),%bl
	cmpb	%al,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c035:
	ret

FUNC(op_b020)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%eax
	movl	%edx,%edi
	shrl	$7,%edi
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
	andl	$28,%edi
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	movb	(%edi,%esi),%bl
	cmpb	%al,%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c036:
	ret

FUNC(op_b028)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_c008:
	rolw	$8,%ax
	addl	$8,%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	movb	(%ecx,%ebx),%cl
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	cmpb	(%eax,%edx),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%esi
	popl	%ebx
	movl	%esi,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c037:
	ret

FUNC(op_b038)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ebx),%dx
RR2_c009:
	rolw	$8,%dx
	movswl	%dx,%edx
	shrl	$7,%ecx
	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	andl	$28,%ecx
	andl	$1020,%eax
	movb	GLOBL(regs)(%ecx),%cl
	movl	GLOBL(R24)(%eax),%eax
	cmpb	(%edx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c038:
	ret

FUNC(op_b039)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$7,%ecx
	movl	0x2164334A+2(%ebx),%edx
RR2_c010:
	bswapl	%edx
	movl	%edx,%eax
	andl	$65535,%edx
	shrl	$14,%eax
	andl	$28,%ecx
	andl	$1020,%eax
	movb	GLOBL(regs)(%ecx),%cl
	movl	GLOBL(R24)(%eax),%eax
	cmpb	(%edx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c039:
	ret

FUNC(op_b03a)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c011:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%edx
	movl	%edx,%eax
	andl	$28,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movb	GLOBL(regs)(%ecx),%cl
	movl	GLOBL(R24)(%eax),%eax
	cmpb	(%edx,%eax),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c040:
	ret

FUNC(op_b03c)

	shrl	$7,%eax
	andl	$28,%eax
	movl	GLOBL(regs)+88,%edx
	movb	GLOBL(regs)(%eax),%al
	cmpb	0x2164334A+3(%edx),%al
RR3_c000:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c041:
	ret

FUNC(op_b040)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$28,%edx
	andl	$7,%eax
	movw	GLOBL(regs)(%edx),%dx
	cmpw	GLOBL(regs)(,%eax,4),%dx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c042:
	ret

FUNC(op_b048)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	addl	$8,%eax
	movw	GLOBL(regs)(%edx),%dx
	cmpw	GLOBL(regs)(,%eax,4),%dx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c043:
	ret

FUNC(op_b050)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	shrl	$7,%edx
	movw	(%ebx,%eax,4),%ax
	andl	$28,%edx
	andl	$65535,%eax
	movw	(%edx,%ebx),%dx
	addl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%ax,%dx
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c044:
	ret

FUNC(op_b058)

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
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%ebx),%edx
	addl	$2,%edx
	andl	$28,%edi
	movl	%edx,(%ecx,%ebx)
	movw	(%edi,%ebx),%di
	cmpw	%ax,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c045:
	ret

FUNC(op_b060)

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
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%edi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%ecx,(%ebx,%esi)
	movl	%edx,%eax
	movw	(%edi,%esi),%di
	cmpw	%ax,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c046:
	ret

FUNC(op_b068)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$7,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_c012:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movw	(%ecx,%ebx),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%esi
	popl	%ebx
	movl	%esi,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c047:
	ret

FUNC(op_b078)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c013:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movw	GLOBL(regs)(%ecx),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c048:
	ret

FUNC(op_b079)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$7,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_c014:
	bswapl	%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movw	GLOBL(regs)(%ecx),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c049:
	ret

FUNC(op_b07a)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c015:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	andl	$28,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movw	GLOBL(regs)(%ecx),%cx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c050:
	ret

FUNC(op_b07c)

	shrl	$7,%eax
	movl	GLOBL(regs)+88,%ecx
	andl	$28,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_c016:
	rolw	$8,%dx
	movw	GLOBL(regs)(%eax),%ax
	cmpw	%dx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c051:
	ret

FUNC(op_b080)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$28,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(%edx),%edx
	cmpl	GLOBL(regs)(,%eax,4),%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c052:
	ret

FUNC(op_b088)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(%edx),%edx
	cmpl	GLOBL(regs)(,%eax,4),%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c053:
	ret

FUNC(op_b090)

	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	2(%ebx,%eax,4),%cl
	movw	(%ebx,%eax,4),%ax
	shrl	$7,%edx
	andl	$65535,%eax
	andl	$28,%edx
	addl	GLOBL(R24)(,%ecx,4),%eax
	movl	(%edx,%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c054:
	ret

FUNC(op_b098)

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
	movl	(%edi,%ebx),%edi
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c055:
	ret

FUNC(op_b0a0)

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
	movl	(%edi,%esi),%edi
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c056:
	ret

FUNC(op_b0a8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_c017:
	rolw	$8,%ax
	addl	$8,%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%ecx,%ebx),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%esi
	popl	%ebx
	movl	%esi,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c057:
	ret

FUNC(op_b0b8)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c018:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c058:
	ret

FUNC(op_b0b9)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$7,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_c019:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c059:
	ret

FUNC(op_b0ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c020:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(%ecx),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c060:
	ret

FUNC(op_b0bc)

	movl	GLOBL(regs)+88,%ecx
	shrl	$7,%eax
	movl	0x2164334A+2(%ecx),%edx
RR2_c021:
	andl	$28,%eax
	bswapl	%edx
	movl	GLOBL(regs)(%eax),%eax
	cmpl	%edx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c061:
	ret

FUNC(op_b0c0)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%eax
	andl	$7,%edx
	addl	$8,%eax
	movswl	(%ecx,%edx,4),%edx
	movl	(%ecx,%eax,4),%ecx
	cmpl	%edx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c062:
	ret

FUNC(op_b0c8)

	movl	%eax,%edx
	shrl	$9,%eax
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movswl	(%ecx,%edx,4),%edx
	movl	(%ecx,%eax,4),%ecx
	cmpl	%edx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c063:
	ret

FUNC(op_b0d0)

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
	movl	(%ebx,%edx,4),%ebx
	cwtl
	cmpl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c064:
	ret

FUNC(op_b0d8)

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
	andl	$7,%esi
	movl	%edx,%eax
	addl	$2,%edx
	andl	$65535,%eax
	addl	$8,%esi
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%edi)
	cwtl
	movl	(%edi,%esi,4),%edi
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c065:
	ret

FUNC(op_b0e0)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	%eax,%esi
	movl	(%ebx,%edi),%ecx
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
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	%ecx,(%ebx,%edi)
	cwtl
	movl	(%edi,%esi,4),%edi
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c066:
	ret

FUNC(op_b0e8)

	movl	%eax,%edx
	movl	%eax,%ecx
	andl	$7,%edx
	shrl	$9,%ecx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_c022:
	rolw	$8,%ax
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
	movl	(%ebx,%ecx,4),%ebx
	cwtl
	cmpl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%esi
	popl	%ebx
	movl	%esi,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c067:
	ret

FUNC(op_b0f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c023:
	rolw	$8,%ax
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
	movl	GLOBL(regs)(,%ecx,4),%ecx
	cwtl
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c068:
	ret

FUNC(op_b0f9)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_c024:
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
	movl	GLOBL(regs)(,%ecx,4),%ecx
	cwtl
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c069:
	ret

FUNC(op_b0fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c025:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
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
	movl	GLOBL(regs)(,%ecx,4),%ecx
	cwtl
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c070:
	ret

FUNC(op_b0fc)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_c026:
	rolw	$8,%ax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%edx
	cmpl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c071:
	ret

FUNC(op_b100)

	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$7,%eax
	andl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	sall	$2,%ecx
	movb	(%eax,%edx),%al
	xorb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c072:
	ret

FUNC(op_b108)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%edi
	leal	8(%ebp),%ecx
	shrl	$9,%edi
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	movb	(%ebx,%eax),%bl
	movl	$GLOBL(areg_byteinc),%esi
	movb	%bl,19-16(%esp)
	addl	(%esi,%ebp,4),%edx
	andl	$7,%edi
	movl	%edx,GLOBL(regs)(%ecx)
	leal	8(%edi),%ecx
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	(%esi,%edi,4),%edx
	movb	(%ebx,%eax),%al
	movl	%edx,GLOBL(regs)(%ecx)
	cmpb	19-16(%esp),%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c073:
	ret

FUNC(op_b110)

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
	xorb	(%ebx,%eax),%cl
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
	jl	JJ_c074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c074:
	ret

FUNC(op_b118)

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
	xorb	%al,23-16(%esp)
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
	jl	JJ_c075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c075:
	ret

FUNC(op_b120)

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
	xorb	%al,19-12(%esp)
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
	jl	JJ_c076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c076:
	ret

FUNC(op_b128)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c027:
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
	xorb	(%edx,%eax),%bl
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
	jl	JJ_c077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c077:
	ret

FUNC(op_b138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c028:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	andl	$28,%ebx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%ecx),%eax
	xorb	(%edx,%eax),%bl
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
	jl	JJ_c078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c078:
	ret

FUNC(op_b139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_c029:
	bswapl	%ecx
	movl	%ecx,%edx
	andl	$28,%ebx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%edx),%eax
	xorb	(%ecx,%eax),%bl
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
	jl	JJ_c079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c079:
	ret

FUNC(op_b140)

	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$7,%eax
	andl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	sall	$2,%ecx
	movw	(%eax,%edx),%ax
	xorw	(%ecx,%edx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c080:
	ret

FUNC(op_b148)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	%eax,%ecx
	andl	$7,%ebx
	xorl	%edx,%edx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	shrl	$9,%ecx
	movl	(%ebx,%edi),%eax
	movb	2(%ebx,%edi),%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,12-12(%esp)
	movl	(%ebx,%edi),%edx
	andl	$7,%ecx
	addl	$2,%edx
	addl	$8,%ecx
	movl	%edx,(%ebx,%edi)
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	(%ecx,%edi),%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%edi),%edx
	addl	$2,%edx
	movl	%edx,(%ecx,%edi)
	cmpw	12-12(%esp),%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_c081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c081:
	ret

FUNC(op_b150)

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
	xorw	(%ebx,%esi),%ax
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
	jl	JJ_c082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c082:
	ret

FUNC(op_b158)

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
	xorl	%eax,%edi
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
	jl	JJ_c083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c083:
	ret

FUNC(op_b160)

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
	xorl	%eax,%edi
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
	jl	JJ_c084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c084:
	ret

FUNC(op_b168)

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
RR2_c030:
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
	xorw	(%ebx,%esi),%ax
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
	jl	JJ_c085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c085:
	ret

FUNC(op_b178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c031:
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
	xorw	GLOBL(regs)(%ebx),%ax
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
	jl	JJ_c086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c086:
	ret

FUNC(op_b179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_c032:
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
	xorw	GLOBL(regs)(%ebx),%ax
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
	jl	JJ_c087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c087:
	ret

FUNC(op_b180)

	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$7,%eax
	andl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	sall	$2,%ecx
	movl	(%eax,%edx),%eax
	xorl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c088:
	ret

FUNC(op_b188)

	movl	%eax,%ebx
	movl	%eax,%ecx
	andl	$7,%ebx
	shrl	$9,%ecx
	addl	$8,%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	andl	$7,%ecx
	movl	(%ebx,%edi),%edx
	addl	$8,%ecx
	movl	%edx,%eax
	movzbl	2(%ebx,%edi),%esi
	andl	$65535,%eax
	sall	$2,%ecx
	addl	GLOBL(R24)(,%esi,4),%eax
	addl	$4,%edx
	movl	(%eax),%esi
	movl	%edx,(%ebx,%edi)
	bswapl	%esi
	movl	(%ecx,%edi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%edx,(%ecx,%edi)
	cmpl	%esi,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c089:
	ret

FUNC(op_b190)

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
	xorl	(%ebx,%esi),%eax
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
	jl	JJ_c090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c090:
	ret

FUNC(op_b198)

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
	xorl	%eax,%ebp
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
	jl	JJ_c091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c091:
	ret

FUNC(op_b1a0)

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
	xorl	%eax,%ebp
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
	jl	JJ_c092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c092:
	ret

FUNC(op_b1a8)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c033:
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
	xorl	(%ebx,%esi),%eax
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
	jl	JJ_c093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c093:
	ret

FUNC(op_b1b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_c034:
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
	xorl	GLOBL(regs)(%ebx),%eax
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
	jl	JJ_c094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c094:
	ret

FUNC(op_b1b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_c035:
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
	xorl	GLOBL(regs)(%ebx),%eax
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
	jl	JJ_c095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c095:
	ret

FUNC(op_b1c0)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	addl	$8,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(,%edx,4),%edx
	cmpl	GLOBL(regs)(,%eax,4),%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c096:
	ret

FUNC(op_b1c8)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(,%edx,4),%edx
	cmpl	GLOBL(regs)(,%eax,4),%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c097:
	ret

FUNC(op_b1d0)

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
	movl	(%ebx,%edx,4),%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c098:
	ret

FUNC(op_b1d8)

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
	movl	(%esi,%ebx,4),%esi
	cmpl	%eax,%esi
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c099:
	ret

FUNC(op_b1e0)

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
	movl	(%edi,%esi,4),%edi
	cmpl	%eax,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c100:
	ret

FUNC(op_b1e8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_c036:
	rolw	$8,%ax
	addl	$8,%edx
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
	movl	(%ebx,%ecx,4),%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%esi
	popl	%ebx
	movl	%esi,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c101:
	ret

FUNC(op_b1f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c037:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%ecx,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c102:
	ret

FUNC(op_b1f9)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	shrl	$9,%ecx
	movl	0x2164334A+2(%ebx),%eax
RR2_c038:
	bswapl	%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%ecx,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c103:
	ret

FUNC(op_b1fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_c039:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ebx),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ecx
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%ecx,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c104:
	ret

FUNC(op_b1fc)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	0x2164334A+2(%ecx),%edx
RR2_c040:
	addl	$8,%eax
	bswapl	%edx
	movl	GLOBL(regs)(,%eax,4),%eax
	cmpl	%edx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c105:
	ret

FUNC(op_c000)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%ecx
	movb	(%edx,%eax,4),%al
	andb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c106:
	ret

FUNC(op_c010)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	xorl	%esi,%esi
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%bl
	movw	(%edx,%eax,4),%si
	movl	GLOBL(R24)(,%ebx,4),%eax
	andl	$28,%ecx
	movb	(%esi,%eax),%al
	andb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c107:
	ret

FUNC(op_c018)

	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%edi
	shrl	$7,%edi
	leal	8(%ebp),%ecx
	xorl	%eax,%eax
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$28,%edi
	movl	(%ecx,%ebx),%edx
	movb	2(%ecx,%ebx),%al
	movl	%edx,%esi
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%esi
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%esi,%eax),%al
	movl	%edx,(%ecx,%ebx)
	andb	(%edi,%ebx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c108:
	ret

FUNC(op_c020)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	andl	$7,%eax
	shrl	$7,%edi
	leal	8(%eax),%ecx
	movl	$GLOBL(regs),%ebx
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ecx,%ebx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%edi
	movb	(%esi,%eax),%al
	movl	%edx,(%ecx,%ebx)
	andb	(%edi,%ebx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%edi,%ebx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c109:
	ret

FUNC(op_c028)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_c041:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	andl	$28,%ebx
	movb	(%eax,%edx),%al
	andb	(%ebx,%ecx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c110:
	ret

FUNC(op_c038)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_c042:
	rolw	$8,%cx
	movswl	%cx,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	$GLOBL(regs),%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ebx
	movb	(%ecx,%eax),%al
	andb	(%ebx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,(%ebx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c111:
	ret

FUNC(op_c039)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_c043:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	$GLOBL(regs),%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ebx
	movb	(%ecx,%eax),%al
	andb	(%ebx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,(%ebx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c112:
	ret

FUNC(op_c03a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%edx
	shrl	$7,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_c044:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	$GLOBL(regs),%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ebx
	movb	(%edx,%eax),%al
	andb	(%ebx,%ecx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_c113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_c198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_c113:
	ret

FUNC(Init020_0c)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_c000-4
	movl	%eax,RR0_c001-4
	movl	%eax,RR0_c002-4
	movl	%eax,RR0_c003-4
	movl	%eax,RR0_c004-4
	movl	%eax,RR0_c005-4
	movl	%eax,RR0_c006-4
	movl	%eax,RR0_c007-4
	movl	%eax,RR0_c008-4
	movl	%eax,RR0_c009-4
	movl	%eax,RR0_c010-4
	movl	%eax,RR0_c011-4
	movl	%eax,RR0_c012-4
	movl	%eax,RR0_c013-4
	movl	%eax,RR0_c014-4
	movl	%eax,RR0_c015-4
	movl	%eax,RR0_c016-4
	movl	%eax,RR0_c017-4
	movl	%eax,RR0_c018-4
	movl	%eax,RR0_c019-4
	movl	%eax,RR0_c020-4
	movl	%eax,RR0_c021-4
	movl	%eax,RR0_c022-4
	movl	%eax,RR0_c023-4
	movl	%eax,RR0_c024-4
	movl	%eax,RR0_c025-4
	movl	%eax,RR0_c026-4
	movl	%eax,RR0_c027-4
	movl	%eax,RR0_c028-4
	movl	%eax,RR0_c029-4
	movl	%eax,RR0_c030-4
	movl	%eax,RR0_c031-4
	movl	%eax,RR0_c032-4
	movl	%eax,RR0_c033-4
	movl	%eax,RR0_c034-4
	movl	%eax,RR0_c035-4
	movl	%eax,RR0_c036-4
	movl	%eax,RR0_c037-4
	movl	%eax,RR0_c038-4
	movl	%eax,RR0_c039-4
	movl	%eax,RR0_c040-4
	movl	%eax,RR0_c041-4
	movl	%eax,RR0_c042-4
	movl	%eax,RR0_c043-4
	movl	%eax,RR0_c044-4
	movl	%eax,RR0_c045-4
	movl	%eax,RR0_c046-4
	movl	%eax,RR0_c047-4
	movl	%eax,RR0_c048-4
	movl	%eax,RR0_c049-4
	movl	%eax,RR0_c050-4
	movl	%eax,RR0_c051-4
	movl	%eax,RR0_c052-4
	movl	%eax,RR0_c053-4
	movl	%eax,RR0_c054-4
	movl	%eax,RR0_c055-4
	movl	%eax,RR0_c056-4
	movl	%eax,RR0_c057-4
	movl	%eax,RR0_c058-4
	movl	%eax,RR0_c059-4
	movl	%eax,RR0_c060-4
	movl	%eax,RR0_c061-4
	movl	%eax,RR0_c062-4
	movl	%eax,RR0_c063-4
	movl	%eax,RR0_c064-4
	movl	%eax,RR0_c065-4
	movl	%eax,RR0_c066-4
	movl	%eax,RR0_c067-4
	movl	%eax,RR0_c068-4
	movl	%eax,RR0_c069-4
	movl	%eax,RR0_c070-4
	movl	%eax,RR0_c071-4
	movl	%eax,RR0_c072-4
	movl	%eax,RR0_c073-4
	movl	%eax,RR0_c074-4
	movl	%eax,RR0_c075-4
	movl	%eax,RR0_c076-4
	movl	%eax,RR0_c077-4
	movl	%eax,RR0_c078-4
	movl	%eax,RR0_c079-4
	movl	%eax,RR0_c080-4
	movl	%eax,RR0_c081-4
	movl	%eax,RR0_c082-4
	movl	%eax,RR0_c083-4
	movl	%eax,RR0_c084-4
	movl	%eax,RR0_c085-4
	movl	%eax,RR0_c086-4
	movl	%eax,RR0_c087-4
	movl	%eax,RR0_c088-4
	movl	%eax,RR0_c089-4
	movl	%eax,RR0_c090-4
	movl	%eax,RR0_c091-4
	movl	%eax,RR0_c092-4
	movl	%eax,RR0_c093-4
	movl	%eax,RR0_c094-4
	movl	%eax,RR0_c095-4
	movl	%eax,RR0_c096-4
	movl	%eax,RR0_c097-4
	movl	%eax,RR0_c098-4
	movl	%eax,RR0_c099-4
	movl	%eax,RR0_c100-4
	movl	%eax,RR0_c101-4
	movl	%eax,RR0_c102-4
	movl	%eax,RR0_c103-4
	movl	%eax,RR0_c104-4
	movl	%eax,RR0_c105-4
	movl	%eax,RR0_c106-4
	movl	%eax,RR0_c107-4
	movl	%eax,RR0_c108-4
	movl	%eax,RR0_c109-4
	movl	%eax,RR0_c110-4
	movl	%eax,RR0_c111-4
	movl	%eax,RR0_c112-4
	movl	%eax,RR0_c113-4
	movl	%eax,RR0_c114-4
	movl	%eax,RR0_c115-4
	movl	%eax,RR0_c116-4
	movl	%eax,RR0_c117-4
	movl	%eax,RR0_c118-4
	movl	%eax,RR0_c119-4
	movl	%eax,RR0_c120-4
	movl	%eax,RR0_c121-4
	movl	%eax,RR0_c122-4
	movl	%eax,RR0_c123-4
	movl	%eax,RR0_c124-4
	movl	%eax,RR0_c125-4
	movl	%eax,RR0_c126-4
	movl	%eax,RR0_c127-4
	movl	%eax,RR0_c128-4
	movl	%eax,RR0_c129-4
	movl	%eax,RR0_c130-4
	movl	%eax,RR0_c131-4
	movl	%eax,RR0_c132-4
	movl	%eax,RR0_c133-4
	movl	%eax,RR0_c134-4
	movl	%eax,RR0_c135-4
	movl	%eax,RR0_c136-4
	movl	%eax,RR0_c137-4
	movl	%eax,RR0_c138-4
	movl	%eax,RR0_c139-4
	movl	%eax,RR0_c140-4
	movl	%eax,RR0_c141-4
	movl	%eax,RR0_c142-4
	movl	%eax,RR0_c143-4
	movl	%eax,RR0_c144-4
	movl	%eax,RR0_c145-4
	movl	%eax,RR0_c146-4
	movl	%eax,RR0_c147-4
	movl	%eax,RR0_c148-4
	movl	%eax,RR0_c149-4
	movl	%eax,RR0_c150-4
	movl	%eax,RR0_c151-4
	movl	%eax,RR0_c152-4
	movl	%eax,RR0_c153-4
	movl	%eax,RR0_c154-4
	movl	%eax,RR0_c155-4
	movl	%eax,RR0_c156-4
	movl	%eax,RR0_c157-4
	movl	%eax,RR0_c158-4
	movl	%eax,RR0_c159-4
	movl	%eax,RR0_c160-4
	movl	%eax,RR0_c161-4
	movl	%eax,RR0_c162-4
	movl	%eax,RR0_c163-4
	movl	%eax,RR0_c164-4
	movl	%eax,RR0_c165-4
	movl	%eax,RR0_c166-4
	movl	%eax,RR0_c167-4
	movl	%eax,RR0_c168-4
	movl	%eax,RR0_c169-4
	movl	%eax,RR0_c170-4
	movl	%eax,RR0_c171-4
	movl	%eax,RR0_c172-4
	movl	%eax,RR0_c173-4
	movl	%eax,RR0_c174-4
	movl	%eax,RR0_c175-4
	movl	%eax,RR0_c176-4
	movl	%eax,RR0_c177-4
	movl	%eax,RR0_c178-4
	movl	%eax,RR0_c179-4
	movl	%eax,RR0_c180-4
	movl	%eax,RR0_c181-4
	movl	%eax,RR0_c182-4
	movl	%eax,RR0_c183-4
	movl	%eax,RR0_c184-4
	movl	%eax,RR0_c185-4
	movl	%eax,RR0_c186-4
	movl	%eax,RR0_c187-4
	movl	%eax,RR0_c188-4
	movl	%eax,RR0_c189-4
	movl	%eax,RR0_c190-4
	movl	%eax,RR0_c191-4
	movl	%eax,RR0_c192-4
	movl	%eax,RR0_c193-4
	movl	%eax,RR0_c194-4
	movl	%eax,RR0_c195-4
	movl	%eax,RR0_c196-4
	movl	%eax,RR0_c197-4
	movl	%eax,RR0_c198-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_c000-4
	movl	%eax,RR2_c001-4
	movl	%eax,RR2_c002-4
	movl	%eax,RR2_c003-4
	movl	%eax,RR2_c004-4
	movl	%eax,RR2_c005-4
	movl	%eax,RR2_c006-4
	movl	%eax,RR2_c007-4
	movl	%eax,RR2_c008-4
	movl	%eax,RR2_c009-4
	movl	%eax,RR2_c010-4
	movl	%eax,RR2_c011-4
	movl	%eax,RR2_c012-4
	movl	%eax,RR2_c013-4
	movl	%eax,RR2_c014-4
	movl	%eax,RR2_c015-4
	movl	%eax,RR2_c016-4
	movl	%eax,RR2_c017-4
	movl	%eax,RR2_c018-4
	movl	%eax,RR2_c019-4
	movl	%eax,RR2_c020-4
	movl	%eax,RR2_c021-4
	movl	%eax,RR2_c022-4
	movl	%eax,RR2_c023-4
	movl	%eax,RR2_c024-4
	movl	%eax,RR2_c025-4
	movl	%eax,RR2_c026-4
	movl	%eax,RR2_c027-4
	movl	%eax,RR2_c028-4
	movl	%eax,RR2_c029-4
	movl	%eax,RR2_c030-4
	movl	%eax,RR2_c031-4
	movl	%eax,RR2_c032-4
	movl	%eax,RR2_c033-4
	movl	%eax,RR2_c034-4
	movl	%eax,RR2_c035-4
	movl	%eax,RR2_c036-4
	movl	%eax,RR2_c037-4
	movl	%eax,RR2_c038-4
	movl	%eax,RR2_c039-4
	movl	%eax,RR2_c040-4
	movl	%eax,RR2_c041-4
	movl	%eax,RR2_c042-4
	movl	%eax,RR2_c043-4
	movl	%eax,RR2_c044-4
	incl	%eax
	movl	%eax,RR3_c000-4
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
