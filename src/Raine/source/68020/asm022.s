

FUNC(op_a70)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2000:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_2000:
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
	jne	L_2_405
	movswl	%di,%edi
L_2_405:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_406
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_407
	movl	%ebp,%ebx
L_2_407:
	testl	$64,%esi
	je	L_2_408
	movl	%ebp,%edi
L_2_408:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_409
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_409:
	cmpl	$48,%edx
	jne	L_2_412
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_412:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_415
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_415:
	cmpl	$3,16-16(%esp)
	jne	L_2_418
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_418:
	andl	$4,%esi
	jne	L_2_421
	addl	%edi,%ebx
L_2_421:
	cmpl	$0,16-16(%esp)
	je	L_2_422
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_422:
	testl	%esi,%esi
	je	L_2_425
	addl	%edi,%ebx
L_2_425:
	leal	(%ebp,%ebx),%eax
	jmp	L_2_426
	.align	2,0x90
L_2_406:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_2_426:
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
	xorw	%ax,30-16(%esp)
	movw	30-16(%esp),%cx
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%cx,%ax
	movl	16-16(%esp),%ecx
	rolw	$8,%ax
	addl	GLOBL(W24)(%edx),%ecx
	movw	%ax,(%ecx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2000:
	ret

FUNC(op_ab0)

	subl	$20,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_2001:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,32-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,28-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2006:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_541
	movswl	%di,%edi
L_2_541:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_542
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_543
	movl	20-16(%esp),%ebx
L_2_543:
	testl	$64,%esi
	je	L_2_544
	movl	20-16(%esp),%edi
L_2_544:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_545
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2007:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_545:
	cmpl	$48,%edx
	jne	L_2_548
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_548:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_551
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_2_551:
	cmpl	$3,%ebp
	jne	L_2_554
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2010:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_2_554:
	andl	$4,%esi
	jne	L_2_557
	addl	%edi,%ebx
L_2_557:
	testl	%ebp,%ebp
	je	L_2_558
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_558:
	testl	%esi,%esi
	je	L_2_561
	addl	%edi,%ebx
L_2_561:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_562
	.align	2,0x90
L_2_542:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	28-16(%esp),%eax
	addl	%edi,%eax
L_2_562:
	movl	%eax,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	movl	%eax,%edx
	movl	%ecx,16-16(%esp)
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	xorl	%eax,32-16(%esp)
	movl	32-16(%esp),%ecx
	testl	%ecx,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	16-16(%esp),%ecx
	addl	GLOBL(W24)(%ecx),%edx
	movl	32-16(%esp),%ecx
	bswapl	%ecx
	movl	%ecx,(%edx)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2001:
	ret

FUNC(op_af0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2002:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_2012:
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
	jne	L_2_663
	movswl	%di,%edi
L_2_663:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_664
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_665
	movl	%ebp,%ebx
L_2_665:
	testl	$64,%esi
	je	L_2_666
	movl	%ebp,%edi
L_2_666:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_667
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2013:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_667:
	cmpl	$48,%edx
	jne	L_2_670
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_670:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_673
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_673:
	cmpl	$3,16-16(%esp)
	jne	L_2_676
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2016:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_676:
	andl	$4,%esi
	jne	L_2_679
	addl	%edi,%ebx
L_2_679:
	cmpl	$0,16-16(%esp)
	je	L_2_680
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_680:
	testl	%esi,%esi
	je	L_2_683
	addl	%edi,%ebx
L_2_683:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_684
	.align	2,0x90
L_2_664:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_684:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	28-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	28-16(%esp),%eax
	andl	$7,%eax
	sall	$2,%eax
	movl	$GLOBL(regs),%edx
	movl	%eax,16-16(%esp)
	cmpb	(%eax,%edx),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_687
	movb	(%edx,%esi,4),%dl
	movl	GLOBL(W24)(%edi),%eax
	movb	%dl,(%ebp,%eax)
	jmp	L_2_690
	.align	2,0x90
L_2_687:
	movsbl	%bl,%eax
	movl	16-16(%esp),%ecx
	movl	%eax,(%ecx,%edx)
L_2_690:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2002:
	ret

FUNC(op_c30)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,24-16(%esp)
	addl	$8,%eax
	movl	24-16(%esp),%edx
	movb	0x2164334A+3(%ecx),%cl
RR3_2000:
	addl	$4,%edx
	movb	%cl,31-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2018:
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
	jne	L_2_756
	movswl	%di,%edi
L_2_756:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_757
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_758
	movl	%ebp,%ebx
L_2_758:
	testl	$64,%esi
	je	L_2_759
	movl	%ebp,%edi
L_2_759:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_760
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2019:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_760:
	cmpl	$48,%edx
	jne	L_2_763
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2020:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_763:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_766
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_766:
	cmpl	$3,16-16(%esp)
	jne	L_2_769
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_769:
	andl	$4,%esi
	jne	L_2_772
	addl	%edi,%ebx
L_2_772:
	cmpl	$0,16-16(%esp)
	je	L_2_773
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_773:
	testl	%esi,%esi
	je	L_2_776
	addl	%edi,%ebx
L_2_776:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_777
	.align	2,0x90
L_2_757:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_2_777:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	cmpb	31-16(%esp),%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2003:
	ret

FUNC(op_c3b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ebp
	movb	0x2164334A+3(%ebp),%cl
RR3_2001:
	leal	4(%ebp),%edx
	movb	%cl,27-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2024:
	rolw	$8,%si
	movl	%esi,%eax
	leal	6(%ebp),%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_811
	movswl	%di,%edi
L_2_811:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_812
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_813
	movl	16-16(%esp),%ebx
L_2_813:
	testl	$64,%esi
	je	L_2_814
	movl	16-16(%esp),%edi
L_2_814:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_815
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2025:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_815:
	cmpl	$48,%edx
	jne	L_2_818
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2026:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_818:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_821
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_821:
	cmpl	$3,%ebp
	jne	L_2_824
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2028:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_824:
	andl	$4,%esi
	jne	L_2_827
	addl	%edi,%ebx
L_2_827:
	testl	%ebp,%ebp
	je	L_2_828
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_828:
	testl	%esi,%esi
	je	L_2_831
	addl	%edi,%ebx
L_2_831:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_2_832
	.align	2,0x90
L_2_812:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_832:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	cmpb	27-16(%esp),%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2004:
	ret

FUNC(op_c70)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2003:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_2030:
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
	jne	L_2_888
	movswl	%di,%edi
L_2_888:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_889
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_890
	movl	%ebp,%ebx
L_2_890:
	testl	$64,%esi
	je	L_2_891
	movl	%ebp,%edi
L_2_891:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_892
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_892:
	cmpl	$48,%edx
	jne	L_2_895
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_895:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_898
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_898:
	cmpl	$3,16-16(%esp)
	jne	L_2_901
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_901:
	andl	$4,%esi
	jne	L_2_904
	addl	%edi,%ebx
L_2_904:
	cmpl	$0,16-16(%esp)
	je	L_2_905
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_905:
	testl	%esi,%esi
	je	L_2_908
	addl	%edi,%ebx
L_2_908:
	leal	(%ebp,%ebx),%eax
	jmp	L_2_909
	.align	2,0x90
L_2_889:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_2_909:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	cmpw	30-16(%esp),%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2005:
	ret

FUNC(op_c7b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_2004:
	rolw	$8,%ax
	movw	%ax,26-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2036:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_957
	movswl	%di,%edi
L_2_957:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_958
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_959
	movl	16-16(%esp),%ebx
L_2_959:
	testl	$64,%esi
	je	L_2_960
	movl	16-16(%esp),%edi
L_2_960:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_961
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2037:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_961:
	cmpl	$48,%edx
	jne	L_2_964
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_964:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_967
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_967:
	cmpl	$3,%ebp
	jne	L_2_970
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2040:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_970:
	andl	$4,%esi
	jne	L_2_973
	addl	%edi,%ebx
L_2_973:
	testl	%ebp,%ebp
	je	L_2_974
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_974:
	testl	%esi,%esi
	je	L_2_977
	addl	%edi,%ebx
L_2_977:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_978
	.align	2,0x90
L_2_958:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_2_978:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	cmpw	26-16(%esp),%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2006:
	ret

FUNC(op_cb0)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_2005:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,28-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,24-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2042:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1035
	movswl	%di,%edi
L_2_1035:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1036
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1037
	movl	16-16(%esp),%ebx
L_2_1037:
	testl	$64,%esi
	je	L_2_1038
	movl	16-16(%esp),%edi
L_2_1038:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1039
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2043:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1039:
	cmpl	$48,%edx
	jne	L_2_1042
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2044:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1042:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1045
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2045:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1045:
	cmpl	$3,%ebp
	jne	L_2_1048
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2046:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1048:
	andl	$4,%esi
	jne	L_2_1051
	addl	%edi,%ebx
L_2_1051:
	testl	%ebp,%ebp
	je	L_2_1052
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1052:
	testl	%esi,%esi
	je	L_2_1055
	addl	%edi,%ebx
L_2_1055:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_1056
	.align	2,0x90
L_2_1036:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	24-16(%esp),%eax
	addl	%edi,%eax
L_2_1056:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	28-16(%esp),%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2007:
	ret

FUNC(op_cbb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ebp
	movl	0x2164334A+2(%ebp),%ecx
RR2_2006:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,24-16(%esp)
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2048:
	rolw	$8,%si
	movl	%esi,%eax
	leal	8(%ebp),%ecx
	shrl	$10,%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1104
	movswl	%di,%edi
L_2_1104:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1105
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1106
	movl	16-16(%esp),%ebx
L_2_1106:
	testl	$64,%esi
	je	L_2_1107
	movl	16-16(%esp),%edi
L_2_1107:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1108
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2049:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1108:
	cmpl	$48,%edx
	jne	L_2_1111
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2050:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1111:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1114
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2051:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1114:
	cmpl	$3,%ebp
	jne	L_2_1117
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2052:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1117:
	andl	$4,%esi
	jne	L_2_1120
	addl	%edi,%ebx
L_2_1120:
	testl	%ebp,%ebp
	je	L_2_1121
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1121:
	testl	%esi,%esi
	je	L_2_1124
	addl	%edi,%ebx
L_2_1124:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_1125
	.align	2,0x90
L_2_1105:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_2_1125:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	24-16(%esp),%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2008:
	ret

FUNC(op_cd8)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2007:
	rolw	$8,%di
	movl	%edi,%eax
	movl	(%ecx,%esi),%edx
	movl	%eax,%ebx
	xorl	%eax,%eax
	movl	%edx,%edi
	movb	2(%ecx,%esi),%al
	andl	$65535,%edi
	leal	0(,%eax,4),%ebp
	movl	%edi,20-16(%esp)
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	%ax,18-16(%esp)
	addl	$2,%edx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%esi)
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%ebx,%eax
	andl	$7,%eax
	movw	18-16(%esp),%di
	leal	0(,%eax,4),%edx
	cmpw	(%edx,%esi),%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1152
	xorl	%eax,%eax
	movw	(%esi,%ecx,4),%ax
	movl	20-16(%esp),%edx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebp),%edx
	movw	%ax,(%edx)
	jmp	L_2_1155
	.align	2,0x90
L_2_1152:
	movswl	18-16(%esp),%eax
	movl	%eax,(%edx,%esi)
L_2_1155:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2054:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2009:
	ret

FUNC(op_cf0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2008:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_2055:
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
	jne	L_2_1199
	movswl	%di,%edi
L_2_1199:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1200
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1201
	movl	%ebp,%ebx
L_2_1201:
	testl	$64,%esi
	je	L_2_1202
	movl	%ebp,%edi
L_2_1202:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1203
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2056:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_1203:
	cmpl	$48,%edx
	jne	L_2_1206
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2057:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1206:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_1209
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2058:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1209:
	cmpl	$3,16-16(%esp)
	jne	L_2_1212
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2059:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1212:
	andl	$4,%esi
	jne	L_2_1215
	addl	%edi,%ebx
L_2_1215:
	cmpl	$0,16-16(%esp)
	je	L_2_1216
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1216:
	testl	%esi,%esi
	je	L_2_1219
	addl	%edi,%ebx
L_2_1219:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_1220
	.align	2,0x90
L_2_1200:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1220:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	andl	$1020,%ebp
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edx,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%esi
	movl	28-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	28-16(%esp),%eax
	andl	$7,%eax
	leal	0(,%eax,4),%ebx
	cmpw	GLOBL(regs)(%ebx),%si
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1224
	xorl	%eax,%eax
	movw	GLOBL(regs)(,%edi,4),%ax
	addl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	jmp	L_2_1228
	.align	2,0x90
L_2_1224:
	movswl	%si,%eax
	movl	%eax,GLOBL(regs)(%ebx)
L_2_1228:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2060:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2010:
	ret

FUNC(op_cfc)

	subl	$8,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_2009:
	bswapl	%ebx
	movl	%ebx,%edx
	sarl	$26,%edx
	movl	$GLOBL(regs),%esi
	andl	$28,%edx
	xorl	%eax,%eax
	movb	2(%edx,%esi),%al
	xorl	%ebp,%ebp
	sall	$2,%eax
	movl	%ebx,%ecx
	movl	%eax,16-16(%esp)
	movl	%eax,%edi
	movw	(%edx,%esi),%bp
	movl	GLOBL(R24)(%edi),%eax
	sarl	$10,%ecx
	addl	%ebp,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	andl	$28,%ecx
	movw	%ax,22-16(%esp)
	xorl	%edx,%edx
	movb	2(%ecx,%esi),%dl
	xorl	%eax,%eax
	movw	(%ecx,%esi),%ax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ebx,%eax
	sarl	$14,%eax
	movw	22-16(%esp),%di
	andl	$28,%eax
	cmpw	(%eax,%esi),%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1283
	movl	%ebx,%eax
	andl	$7,%eax
	cmpw	(%esi,%eax,4),%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%eax
	sarl	$20,%eax
	movl	16-16(%esp),%edi
	andl	$28,%eax
	movl	GLOBL(W24)(%edi),%edx
	movw	(%eax,%esi),%ax
	addl	%ebp,%edx
	andl	$65535,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movl	%ebx,%eax
	sarl	$4,%eax
	andl	$28,%eax
	movl	GLOBL(W24)(%edi),%edx
	movw	(%eax,%esi),%ax
	addl	%ebp,%edx
	andl	$65535,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	testb	$64,regflags
	jne	L_2_1281
L_2_1283:
	movl	%ebx,%eax
	sarl	$20,%eax
	movw	22-16(%esp),%di
	andl	$28,%eax
	movw	%di,(%eax,%esi)
	movl	%ebx,%eax
	sarl	$4,%eax
	andl	$28,%eax
	movw	%cx,(%eax,%esi)
L_2_1281:
	addl	$6,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2011:
	ret

FUNC(op_e10)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1285
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1286
	.align	2,0x90
L_2_1285:
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2010:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ebx
	testb	$8,%bh
	je	L_2_1288
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	leal	8(%edx),%eax
	xorl	%edx,%edx
	movb	2(%ecx,%eax,4),%dl
	movw	(%ecx,%eax,4),%cx
	andl	$65535,%ecx
	movl	GLOBL(W24)(,%edx,4),%eax
	movb	%bl,(%ecx,%eax)
	jmp	L_2_1290
	.align	2,0x90
L_2_1288:
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%esi
	xorl	%edx,%edx
	xorl	%ecx,%ecx
	movb	2(%esi,%eax,4),%dl
	movw	(%esi,%eax,4),%cx
	movl	GLOBL(R24)(,%edx,4),%eax
	movb	(%ecx,%eax),%dl
	testw	%bx,%bx
	jge	L_2_1292
	movl	%ebx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%dl,%edx
	addl	$8,%eax
	movl	%edx,(%esi,%eax,4)
	jmp	L_2_1290
	.align	2,0x90
L_2_1292:
	movl	%ebx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%dl,(%esi,%eax,4)
L_2_1290:
	addl	$4,GLOBL(regs)+88
L_2_1286:
	popl	%eax
	decl	%eax
	jl	JJ_2012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2012:
	ret

FUNC(op_e18)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,20-16(%esp)
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1295
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1296
	.align	2,0x90
L_2_1295:
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2011:
	rolw	$8,%si
	movl	%esi,%eax
	movw	%ax,16-16(%esp)
	testb	$8,%ah
	je	L_2_1298
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	movl	20-16(%esp),%eax
	addl	$8,%eax
	movl	20-16(%esp),%edi
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edi,4),%esi
	movl	(%eax,%ecx),%edx
	addl	%edx,%esi
	movl	%esi,(%eax,%ecx)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	jmp	L_2_1300
	.align	2,0x90
L_2_1298:
	movl	20-16(%esp),%ecx
	movl	$GLOBL(regs),%ebp
	addl	$8,%ecx
	xorl	%eax,%eax
	sall	$2,%ecx
	movl	20-16(%esp),%edi
	movl	(%ecx,%ebp),%edx
	movb	2(%ecx,%ebp),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%ebp)
	cmpw	$0,16-16(%esp)
	jge	L_2_1302
	movl	16-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%bl,%edx
	addl	$8,%eax
	movl	%edx,(%ebp,%eax,4)
	jmp	L_2_1300
	.align	2,0x90
L_2_1302:
	movl	16-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%bl,(%ebp,%eax,4)
L_2_1300:
	addl	$4,GLOBL(regs)+88
L_2_1296:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2063:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2013:
	ret

FUNC(op_e20)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1305
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1306
	.align	2,0x90
L_2_1305:
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2012:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebp
	testl	$2048,%ebp
	je	L_2_1308
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	leal	8(%edx),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%esi
	subl	%edx,%esi
	movl	%esi,%edx
	movl	%edx,(%eax,%ecx)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	jmp	L_2_1310
	.align	2,0x90
L_2_1308:
	leal	8(%edx),%ecx
	movl	$GLOBL(regs),%edi
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%edi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ebx,%eax),%bl
	movl	%edx,(%ecx,%edi)
	testw	%bp,%bp
	jge	L_2_1312
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%bl,%edx
	addl	$8,%eax
	movl	%edx,(%edi,%eax,4)
	jmp	L_2_1310
	.align	2,0x90
L_2_1312:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%bl,(%edi,%eax,4)
L_2_1310:
	addl	$4,GLOBL(regs)+88
L_2_1306:
	popl	%eax
	decl	%eax
	jl	JJ_2014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2014:
	ret

FUNC(op_e28)

	movl	%eax,%esi
	andl	$7,%esi
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1315
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1316
	.align	2,0x90
L_2_1315:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2013:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1318
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2000:
	rolw	$8,%ax
	leal	8(%esi),%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(W24)(%edx),%edx
	movb	%bl,(%eax,%edx)
	jmp	L_2_1321
	.align	2,0x90
L_2_1318:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2000:
	rolw	$8,%ax
	leal	8(%esi),%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	testw	%cx,%cx
	jge	L_2_1324
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%dl,%edx
	addl	$8,%eax
	movl	%edx,(%ebx,%eax,4)
	jmp	L_2_1321
	.align	2,0x90
L_2_1324:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%dl,(%ebx,%eax,4)
L_2_1321:
	addl	$8,GLOBL(regs)+88
L_2_1316:
	popl	%eax
	decl	%eax
	jl	JJ_2015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2015:
	ret

FUNC(op_e30)

	subl	$28,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1327
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1328
	.align	2,0x90
L_2_1327:
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_2014:
	rolw	$8,%ax
	movw	%ax,40-16(%esp)
	testb	$8,%ah
	je	L_2_1330
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	4(%ebp),%edx
	movl	%eax,36-16(%esp)
	movl	%edx,GLOBL(regs)+88
	leal	8(%ebx),%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	6(%ebp),%ecx
	movl	%eax,32-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2066:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1333
	movswl	%di,%edi
L_2_1333:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1334
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1335
	movl	24-16(%esp),%ebx
L_2_1335:
	testl	$64,%esi
	je	L_2_1336
	movl	24-16(%esp),%edi
L_2_1336:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1337
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2067:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1337:
	cmpl	$48,%edx
	jne	L_2_1340
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2068:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1340:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1343
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2069:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1343:
	cmpl	$3,%ebp
	jne	L_2_1346
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2070:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1346:
	andl	$4,%esi
	jne	L_2_1349
	addl	%edi,%ebx
L_2_1349:
	testl	%ebp,%ebp
	je	L_2_1350
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1350:
	testl	%esi,%esi
	je	L_2_1353
	addl	%edi,%ebx
L_2_1353:
	movl	24-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_2_1354
	.align	2,0x90
L_2_1334:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	32-16(%esp),%eax
	leal	(%edi,%eax),%edx
L_2_1354:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	36-16(%esp),%cl
	movb	%cl,(%edx,%eax)
	jmp	L_2_1328
	.align	2,0x90
L_2_1330:
	leal	8(%ebx),%eax
	xorl	%esi,%esi
	movw	0x2164334A(%ebp),%si
RR0_2071:
	rolw	$8,%si
	leal	2(%ebp),%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1360
	movswl	%di,%edi
L_2_1360:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1361
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1362
	movl	16-16(%esp),%ebx
L_2_1362:
	testl	$64,%esi
	je	L_2_1363
	movl	16-16(%esp),%edi
L_2_1363:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1364
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2072:
	rolw	$8,%ax
	addl	$4,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1364:
	cmpl	$48,%edx
	jne	L_2_1367
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2073:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1367:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1370
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2074:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1370:
	cmpl	$3,%ebp
	jne	L_2_1373
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2075:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1373:
	andl	$4,%esi
	jne	L_2_1376
	addl	%edi,%ebx
L_2_1376:
	testl	%ebp,%ebp
	je	L_2_1377
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1377:
	testl	%esi,%esi
	je	L_2_1380
	addl	%edi,%ebx
L_2_1380:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_2_1381
	.align	2,0x90
L_2_1361:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1381:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%dl
	cmpw	$0,40-16(%esp)
	jge	L_2_1384
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%dl,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1328
	.align	2,0x90
L_2_1384:
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%dl,GLOBL(regs)(,%eax,4)
L_2_1328:
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2016:
	ret

FUNC(op_e38)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1387
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1388
	.align	2,0x90
L_2_1387:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2015:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1390
	xorl	%ebx,%ebx
	movw	0x2164334A+4(%edx),%bx
RR4_2001:
	rolw	$8,%bx
	shrw	$12,%ax
	movl	%ebx,%edx
	cwtl
	movswl	%dx,%edx
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	jmp	L_2_1393
	.align	2,0x90
L_2_1390:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2001:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	testw	%cx,%cx
	jge	L_2_1396
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%dl,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1393
	.align	2,0x90
L_2_1396:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%dl,GLOBL(regs)(,%eax,4)
L_2_1393:
	addl	$8,GLOBL(regs)+88
L_2_1388:
	popl	%eax
	decl	%eax
	jl	JJ_2017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2017:
	ret

FUNC(op_e39)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1399
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2018:
	ret
	.align	2,0x90
L_2_1399:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2016:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1402
	shrw	$12,%ax
	movl	0x2164334A+4(%edx),%edx
RR4_2002:
	cwtl
	bswapl	%edx
	movl	GLOBL(regs)(,%eax,4),%ecx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	jmp	L_2_1405
	.align	2,0x90
L_2_1402:
	movl	0x2164334A+8(%edx),%eax
RR8_2000:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	testw	%cx,%cx
	jge	L_2_1408
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movsbl	%dl,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1405
	.align	2,0x90
L_2_1408:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movb	%dl,GLOBL(regs)(,%eax,4)
L_2_1405:
	addl	$12,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2019:
	ret

FUNC(op_e50)

	movl	%eax,%esi
	andl	$7,%esi
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1411
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1412
	.align	2,0x90
L_2_1411:
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2017:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1414
	shrw	$12,%ax
	movl	$GLOBL(regs),%edx
	movswl	%ax,%ebx
	leal	8(%esi),%eax
	xorl	%ecx,%ecx
	movb	2(%edx,%eax,4),%cl
	movw	(%edx,%eax,4),%ax
	movw	(%edx,%ebx,4),%dx
	andl	$65535,%eax
	andl	$65535,%edx
	addl	GLOBL(W24)(,%ecx,4),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	jmp	L_2_1417
	.align	2,0x90
L_2_1414:
	leal	8(%esi),%eax
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
	movl	%eax,%edx
	testw	%cx,%cx
	jge	L_2_1420
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,(%ebx,%eax,4)
	jmp	L_2_1417
	.align	2,0x90
L_2_1420:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,(%ebx,%eax,4)
L_2_1417:
	addl	$4,GLOBL(regs)+88
L_2_1412:
	popl	%eax
	decl	%eax
	jl	JJ_2020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2020:
	ret

FUNC(op_e58)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1423
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1424
	.align	2,0x90
L_2_1423:
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2018:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebp
	testl	$2048,%ebp
	je	L_2_1426
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	leal	8(%edx),%eax
	sall	$2,%eax
	movl	(%eax,%ecx),%edx
	leal	2(%edx),%esi
	movl	%esi,(%eax,%ecx)
	movl	%edx,%eax
	movl	%ebx,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	jmp	L_2_1429
	.align	2,0x90
L_2_1426:
	leal	8(%edx),%ecx
	movl	$GLOBL(regs),%edi
	sall	$2,%ecx
	movl	(%ecx,%edi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%edx,(%ecx,%edi)
	movl	%eax,%ebx
	testw	%bp,%bp
	jge	L_2_1432
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%bx,%edx
	addl	$8,%eax
	movl	%edx,(%edi,%eax,4)
	jmp	L_2_1429
	.align	2,0x90
L_2_1432:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%bx,(%edi,%eax,4)
L_2_1429:
	addl	$4,GLOBL(regs)+88
L_2_1424:
	popl	%eax
	decl	%eax
	jl	JJ_2021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2021:
	ret

FUNC(op_e60)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1435
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1436
	.align	2,0x90
L_2_1435:
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2019:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebp
	testl	$2048,%ebp
	je	L_2_1438
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%eax,4),%ebx
	leal	8(%edx),%eax
	sall	$2,%eax
	movl	(%eax,%ecx),%edx
	addl	$-2,%edx
	movl	%edx,(%eax,%ecx)
	movl	%edx,%eax
	movl	%ebx,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	jmp	L_2_1441
	.align	2,0x90
L_2_1438:
	leal	8(%edx),%ebx
	movl	$GLOBL(regs),%edi
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	addl	$-2,%ecx
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%ebx,%edi)
	movl	%eax,%edx
	testw	%bp,%bp
	jge	L_2_1444
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,(%edi,%eax,4)
	jmp	L_2_1441
	.align	2,0x90
L_2_1444:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,(%edi,%eax,4)
L_2_1441:
	addl	$4,GLOBL(regs)+88
L_2_1436:
	popl	%eax
	decl	%eax
	jl	JJ_2022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2022:
	ret

FUNC(op_e68)

	movl	%eax,%esi
	andl	$7,%esi
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1447
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1448
	.align	2,0x90
L_2_1447:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2020:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1450
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	movswl	%ax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2003:
	rolw	$8,%ax
	leal	8(%esi),%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	movw	(%ecx,%ebx,4),%cx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	jmp	L_2_1454
	.align	2,0x90
L_2_1450:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2002:
	rolw	$8,%ax
	leal	8(%esi),%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%edx
	testw	%cx,%cx
	jge	L_2_1458
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,(%ebx,%eax,4)
	jmp	L_2_1454
	.align	2,0x90
L_2_1458:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,(%ebx,%eax,4)
L_2_1454:
	addl	$8,GLOBL(regs)+88
L_2_1448:
	popl	%eax
	decl	%eax
	jl	JJ_2023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2023:
	ret

FUNC(op_e70)

	subl	$28,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1461
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1462
	.align	2,0x90
L_2_1461:
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_2021:
	rolw	$8,%ax
	movw	%ax,40-16(%esp)
	testb	$8,%ah
	je	L_2_1464
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	4(%ebp),%edx
	movl	%eax,36-16(%esp)
	movl	%edx,GLOBL(regs)+88
	leal	8(%ebx),%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	6(%ebp),%ecx
	movl	%eax,32-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2084:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1467
	movswl	%di,%edi
L_2_1467:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1468
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1469
	movl	24-16(%esp),%ebx
L_2_1469:
	testl	$64,%esi
	je	L_2_1470
	movl	24-16(%esp),%edi
L_2_1470:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1471
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2085:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1471:
	cmpl	$48,%edx
	jne	L_2_1474
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2086:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1474:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1477
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2087:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1477:
	cmpl	$3,%ebp
	jne	L_2_1480
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2088:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1480:
	andl	$4,%esi
	jne	L_2_1483
	addl	%edi,%ebx
L_2_1483:
	testl	%ebp,%ebp
	je	L_2_1484
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1484:
	testl	%esi,%esi
	je	L_2_1487
	addl	%edi,%ebx
L_2_1487:
	movl	24-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_2_1488
	.align	2,0x90
L_2_1468:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	32-16(%esp),%eax
	leal	(%edi,%eax),%edx
L_2_1488:
	movl	%edx,%eax
	movl	36-16(%esp),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	jmp	L_2_1462
	.align	2,0x90
L_2_1464:
	leal	8(%ebx),%eax
	xorl	%esi,%esi
	movw	0x2164334A(%ebp),%si
RR0_2089:
	rolw	$8,%si
	leal	2(%ebp),%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1495
	movswl	%di,%edi
L_2_1495:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1496
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1497
	movl	16-16(%esp),%ebx
L_2_1497:
	testl	$64,%esi
	je	L_2_1498
	movl	16-16(%esp),%edi
L_2_1498:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1499
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2090:
	rolw	$8,%ax
	addl	$4,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1499:
	cmpl	$48,%edx
	jne	L_2_1502
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2091:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1502:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1505
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2092:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1505:
	cmpl	$3,%ebp
	jne	L_2_1508
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2093:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1508:
	andl	$4,%esi
	jne	L_2_1511
	addl	%edi,%ebx
L_2_1511:
	testl	%ebp,%ebp
	je	L_2_1512
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1512:
	testl	%esi,%esi
	je	L_2_1515
	addl	%edi,%ebx
L_2_1515:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%edx
	jmp	L_2_1516
	.align	2,0x90
L_2_1496:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1516:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,%edx
	cmpw	$0,40-16(%esp)
	jge	L_2_1520
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1462
	.align	2,0x90
L_2_1520:
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,GLOBL(regs)(,%eax,4)
L_2_1462:
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2024:
	ret

FUNC(op_e78)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1523
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1524
	.align	2,0x90
L_2_1523:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2022:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1526
	shrw	$12,%ax
	movswl	%ax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2004:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	jmp	L_2_1530
	.align	2,0x90
L_2_1526:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2003:
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
	movl	%eax,%edx
	testw	%cx,%cx
	jge	L_2_1534
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1530
	.align	2,0x90
L_2_1534:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,GLOBL(regs)(,%eax,4)
L_2_1530:
	addl	$8,GLOBL(regs)+88
L_2_1524:
	popl	%eax
	decl	%eax
	jl	JJ_2025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2025:
	ret

FUNC(op_e79)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1537
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1538
	.align	2,0x90
L_2_1537:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2023:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1540
	shrw	$12,%ax
	movswl	%ax,%ecx
	movl	0x2164334A+4(%edx),%eax
RR4_2005:
	bswapl	%eax
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%edx),%eax
	movl	%ecx,%edx
	rolw	$8,%dx
	movw	%dx,(%eax)
	jmp	L_2_1544
	.align	2,0x90
L_2_1540:
	movl	0x2164334A+8(%edx),%eax
RR8_2001:
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
	movl	%eax,%edx
	testw	%cx,%cx
	jge	L_2_1548
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movswl	%dx,%edx
	addl	$8,%eax
	movl	%edx,GLOBL(regs)(,%eax,4)
	jmp	L_2_1544
	.align	2,0x90
L_2_1548:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movw	%dx,GLOBL(regs)(,%eax,4)
L_2_1544:
	addl	$12,GLOBL(regs)+88
L_2_1538:
	popl	%eax
	decl	%eax
	jl	JJ_2026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2026:
	ret

FUNC(op_e90)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1551
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1552
	.align	2,0x90
L_2_1551:
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2024:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1554
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	movswl	%ax,%ebx
	leal	8(%edx),%eax
	xorl	%edx,%edx
	movb	2(%ecx,%eax,4),%dl
	movw	(%ecx,%eax,4),%ax
	andl	$65535,%eax
	movl	(%ecx,%ebx,4),%ebx
	addl	GLOBL(W24)(,%edx,4),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	jmp	L_2_1557
	.align	2,0x90
L_2_1554:
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movb	2(%ebx,%eax,4),%dl
	movw	(%ebx,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%edx
	bswapl	%edx
	testw	%cx,%cx
	jge	L_2_1560
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1562
	.align	2,0x90
L_2_1560:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1562:
	movl	%edx,(%ebx,%eax,4)
L_2_1557:
	addl	$4,GLOBL(regs)+88
L_2_1552:
	popl	%eax
	decl	%eax
	jl	JJ_2027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2027:
	ret

FUNC(op_e98)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1564
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1565
	.align	2,0x90
L_2_1564:
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2025:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%esi
	testl	$2048,%esi
	je	L_2_1567
	movl	$GLOBL(regs),%ecx
	shrw	$12,%ax
	addl	$8,%edx
	cwtl
	sall	$2,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	(%edx,%ecx),%eax
	leal	4(%eax),%edi
	movl	%edi,(%edx,%ecx)
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	jmp	L_2_1570
	.align	2,0x90
L_2_1567:
	leal	8(%edx),%ecx
	movl	$GLOBL(regs),%ebp
	sall	$2,%ecx
	movl	(%ecx,%ebp),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%ebp),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%edx,(%ecx,%ebp)
	testw	%si,%si
	jge	L_2_1573
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1575
	.align	2,0x90
L_2_1573:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1575:
	movl	%ebx,(%ebp,%eax,4)
L_2_1570:
	addl	$4,GLOBL(regs)+88
L_2_1565:
	popl	%eax
	decl	%eax
	jl	JJ_2028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2028:
	ret

FUNC(op_ea0)

	movl	%eax,%edx
	andl	$7,%edx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1577
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1578
	.align	2,0x90
L_2_1577:
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2026:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%esi
	testl	$2048,%esi
	je	L_2_1580
	movl	$GLOBL(regs),%ecx
	shrw	$12,%ax
	addl	$8,%edx
	cwtl
	sall	$2,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	(%edx,%ecx),%eax
	addl	$-4,%eax
	movl	%eax,(%edx,%ecx)
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	jmp	L_2_1583
	.align	2,0x90
L_2_1580:
	leal	8(%edx),%ebx
	movl	$GLOBL(regs),%ebp
	sall	$2,%ebx
	movl	(%ebx,%ebp),%ecx
	addl	$-4,%ecx
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ecx,(%ebx,%ebp)
	testw	%si,%si
	jge	L_2_1586
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1588
	.align	2,0x90
L_2_1586:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1588:
	movl	%edx,(%ebp,%eax,4)
L_2_1583:
	addl	$4,GLOBL(regs)+88
L_2_1578:
	popl	%eax
	decl	%eax
	jl	JJ_2029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2029:
	ret

FUNC(op_ea8)

	movl	%eax,%esi
	andl	$7,%esi
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1590
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1591
	.align	2,0x90
L_2_1590:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2027:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1593
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	movswl	%ax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2006:
	rolw	$8,%ax
	leal	8(%esi),%edx
	cwtl
	addl	(%ecx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	(%ecx,%ebx,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	jmp	L_2_1597
	.align	2,0x90
L_2_1593:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2004:
	rolw	$8,%ax
	leal	8(%esi),%edx
	movl	$GLOBL(regs),%ebx
	cwtl
	addl	(%ebx,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	testw	%cx,%cx
	jge	L_2_1601
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1603
	.align	2,0x90
L_2_1601:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1603:
	movl	%edx,(%ebx,%eax,4)
L_2_1597:
	addl	$8,GLOBL(regs)+88
L_2_1591:
	popl	%eax
	decl	%eax
	jl	JJ_2030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2030:
	ret

FUNC(op_eb0)

	subl	$28,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1605
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_2_1606
	.align	2,0x90
L_2_1605:
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_2028:
	rolw	$8,%ax
	movw	%ax,40-16(%esp)
	testb	$8,%ah
	je	L_2_1608
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	4(%ebp),%edx
	movl	%eax,36-16(%esp)
	movl	%edx,GLOBL(regs)+88
	leal	8(%ebx),%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	6(%ebp),%ecx
	movl	%eax,32-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_2101:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1611
	movswl	%di,%edi
L_2_1611:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1612
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1613
	movl	24-16(%esp),%ebx
L_2_1613:
	testl	$64,%esi
	je	L_2_1614
	movl	24-16(%esp),%edi
L_2_1614:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1615
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2102:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1615:
	cmpl	$48,%edx
	jne	L_2_1618
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2103:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1618:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1621
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2104:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1621:
	cmpl	$3,%ebp
	jne	L_2_1624
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2105:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_2_1624:
	andl	$4,%esi
	jne	L_2_1627
	addl	%edi,%ebx
L_2_1627:
	testl	%ebp,%ebp
	je	L_2_1628
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1628:
	testl	%esi,%esi
	je	L_2_1631
	addl	%edi,%ebx
L_2_1631:
	movl	24-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_1632
	.align	2,0x90
L_2_1612:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	32-16(%esp),%eax
	addl	%edi,%eax
L_2_1632:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	36-16(%esp),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	jmp	L_2_1606
	.align	2,0x90
L_2_1608:
	leal	8(%ebx),%eax
	xorl	%esi,%esi
	movw	0x2164334A(%ebp),%si
RR0_2106:
	rolw	$8,%si
	leal	2(%ebp),%ecx
	movl	GLOBL(regs)(,%eax,4),%edx
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1639
	movswl	%di,%edi
L_2_1639:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1640
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1641
	movl	16-16(%esp),%ebx
L_2_1641:
	testl	$64,%esi
	je	L_2_1642
	movl	16-16(%esp),%edi
L_2_1642:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1643
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2107:
	rolw	$8,%ax
	addl	$4,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_2_1643:
	cmpl	$48,%edx
	jne	L_2_1646
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2108:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1646:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_2_1649
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2109:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1649:
	cmpl	$3,%ebp
	jne	L_2_1652
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2110:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_2_1652:
	andl	$4,%esi
	jne	L_2_1655
	addl	%edi,%ebx
L_2_1655:
	testl	%ebp,%ebp
	je	L_2_1656
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1656:
	testl	%esi,%esi
	je	L_2_1659
	addl	%edi,%ebx
L_2_1659:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_2_1660
	.align	2,0x90
L_2_1640:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_2_1660:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	cmpw	$0,40-16(%esp)
	jge	L_2_1664
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1666
	.align	2,0x90
L_2_1664:
	movl	40-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1666:
	movl	%edx,GLOBL(regs)(,%eax,4)
L_2_1606:
	addl	$28,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2031:
	ret

FUNC(op_eb8)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1668
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2032:
	ret
	.align	2,0x90
L_2_1668:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2029:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1671
	shrw	$12,%ax
	movswl	%ax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2007:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	GLOBL(regs)(,%ecx,4),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	jmp	L_2_1675
	.align	2,0x90
L_2_1671:
	xorl	%eax,%eax
	movw	0x2164334A+6(%edx),%ax
RR6_2005:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	testw	%cx,%cx
	jge	L_2_1679
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1681
	.align	2,0x90
L_2_1679:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1681:
	movl	%edx,GLOBL(regs)(,%eax,4)
L_2_1675:
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2033:
	ret

FUNC(op_eb9)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_1683
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2034:
	ret
	.align	2,0x90
L_2_1683:
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2030:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,%ch
	je	L_2_1686
	shrw	$12,%ax
	movswl	%ax,%ecx
	movl	0x2164334A+4(%edx),%eax
RR4_2008:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	GLOBL(regs)(,%ecx,4),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	jmp	L_2_1690
	.align	2,0x90
L_2_1686:
	movl	0x2164334A+8(%edx),%eax
RR8_2002:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	testw	%cx,%cx
	jge	L_2_1694
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
	addl	$8,%eax
	jmp	L_2_1696
	.align	2,0x90
L_2_1694:
	movl	%ecx,%eax
	sarw	$12,%ax
	andl	$7,%eax
L_2_1696:
	movl	%edx,GLOBL(regs)(,%eax,4)
L_2_1690:
	addl	$12,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2035:
	ret

FUNC(op_ef0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2031:
	rolw	$8,%ax
	movw	%ax,28-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_2116:
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
	jne	L_2_1775
	movswl	%di,%edi
L_2_1775:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1776
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1777
	movl	%ebp,%ebx
L_2_1777:
	testl	$64,%esi
	je	L_2_1778
	movl	%ebp,%edi
L_2_1778:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1779
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2117:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_1779:
	cmpl	$48,%edx
	jne	L_2_1782
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2118:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1782:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_1785
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2119:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1785:
	cmpl	$3,16-16(%esp)
	jne	L_2_1788
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2120:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1788:
	andl	$4,%esi
	jne	L_2_1791
	addl	%edi,%ebx
L_2_1791:
	cmpl	$0,16-16(%esp)
	je	L_2_1792
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1792:
	testl	%esi,%esi
	je	L_2_1795
	addl	%edi,%ebx
L_2_1795:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_1796
	.align	2,0x90
L_2_1776:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1796:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	andl	$1020,%ebp
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edx,%eax
	movl	(%eax),%esi
	bswapl	%esi
	movl	28-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	28-16(%esp),%eax
	andl	$7,%eax
	leal	0(,%eax,4),%ebx
	cmpl	GLOBL(regs)(%ebx),%esi
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1800
	movl	GLOBL(W24)(%ebp),%eax
	movl	GLOBL(regs)(,%edi,4),%edi
	addl	%edx,%eax
	bswapl	%edi
	movl	%edi,(%eax)
	jmp	L_2_1804
	.align	2,0x90
L_2_1800:
	movl	%esi,GLOBL(regs)(%ebx)
L_2_1804:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2036:
	ret

FUNC(op_efc)

	subl	$8,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_2032:
	bswapl	%ebx
	movl	%ebx,%edx
	sarl	$26,%edx
	movl	$GLOBL(regs),%esi
	andl	$28,%edx
	xorl	%eax,%eax
	movb	2(%edx,%esi),%al
	xorl	%ebp,%ebp
	sall	$2,%eax
	movl	%ebx,%ecx
	movl	%eax,16-16(%esp)
	movl	%eax,%edi
	movw	(%edx,%esi),%bp
	movl	GLOBL(R24)(%edi),%eax
	sarl	$10,%ecx
	addl	%ebp,%eax
	andl	$28,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	xorl	%edx,%edx
	movb	2(%ecx,%esi),%dl
	xorl	%eax,%eax
	movw	(%ecx,%esi),%ax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	%ebx,%eax
	sarl	$14,%eax
	movl	20-16(%esp),%edi
	andl	$28,%eax
	cmpl	(%eax,%esi),%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1859
	movl	%ebx,%eax
	andl	$7,%eax
	cmpl	(%esi,%eax,4),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%eax
	movl	16-16(%esp),%edi
	sarl	$20,%eax
	movl	GLOBL(W24)(%edi),%edx
	andl	$28,%eax
	addl	%ebp,%edx
	movl	(%eax,%esi),%eax
	bswapl	%eax
	movl	%eax,(%edx)
	movl	%ebx,%eax
	sarl	$4,%eax
	movl	GLOBL(W24)(%edi),%edx
	andl	$28,%eax
	addl	%ebp,%edx
	movl	(%eax,%esi),%eax
	bswapl	%eax
	movl	%eax,(%edx)
	testb	$64,regflags
	jne	L_2_1857
L_2_1859:
	movl	%ebx,%eax
	sarl	$20,%eax
	movl	20-16(%esp),%edi
	andl	$28,%eax
	movl	%edi,(%eax,%esi)
	movl	%ebx,%eax
	sarl	$4,%eax
	andl	$28,%eax
	movl	%ecx,(%eax,%esi)
L_2_1857:
	addl	$6,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2037:
	ret

FUNC(op_1030)

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
RR0_2123:
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
	jne	L_2_1893
	movswl	%di,%edi
L_2_1893:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1894
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1895
	movl	%ebp,%ebx
L_2_1895:
	testl	$64,%esi
	je	L_2_1896
	movl	%ebp,%edi
L_2_1896:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1897
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2124:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_1897:
	cmpl	$48,%edx
	jne	L_2_1900
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2125:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1900:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_1903
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2126:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1903:
	cmpl	$3,16-16(%esp)
	jne	L_2_1906
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2127:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1906:
	andl	$4,%esi
	jne	L_2_1909
	addl	%edi,%ebx
L_2_1909:
	cmpl	$0,16-16(%esp)
	je	L_2_1910
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1910:
	testl	%esi,%esi
	je	L_2_1913
	addl	%edi,%ebx
L_2_1913:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_1914
	.align	2,0x90
L_2_1894:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1914:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movb	%al,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2038:
	ret

FUNC(op_103b)

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
RR0_2129:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_1948
	movswl	%di,%edi
L_2_1948:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_1949
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_1950
	movl	%ebp,%ebx
L_2_1950:
	testl	$64,%esi
	je	L_2_1951
	movl	%ebp,%edi
L_2_1951:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_1952
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2130:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_1952:
	cmpl	$48,%edx
	jne	L_2_1955
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2131:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_1955:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_1958
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2132:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1958:
	cmpl	$3,16-16(%esp)
	jne	L_2_1961
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2133:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_1961:
	andl	$4,%esi
	jne	L_2_1964
	addl	%edi,%ebx
L_2_1964:
	cmpl	$0,16-16(%esp)
	je	L_2_1965
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_1965:
	testl	%esi,%esi
	je	L_2_1968
	addl	%edi,%ebx
L_2_1968:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_1969
	.align	2,0x90
L_2_1949:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_1969:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	28-16(%esp),%ecx
	movb	%al,GLOBL(regs)(,%ecx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2039:
	ret

FUNC(op_10b0)

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
RR0_2135:
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
	jne	L_2_2020
	movswl	%di,%edi
L_2_2020:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_2021
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_2022
	movl	%ebp,%ebx
L_2_2022:
	testl	$64,%esi
	je	L_2_2023
	movl	%ebp,%edi
L_2_2023:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_2024
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2136:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_2024:
	cmpl	$48,%edx
	jne	L_2_2027
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2137:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_2027:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_2030
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2138:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_2030:
	cmpl	$3,16-16(%esp)
	jne	L_2_2033
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2139:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_2033:
	andl	$4,%esi
	jne	L_2_2036
	addl	%edi,%ebx
L_2_2036:
	cmpl	$0,16-16(%esp)
	je	L_2_2037
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_2037:
	testl	%esi,%esi
	je	L_2_2040
	addl	%edi,%ebx
L_2_2040:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_2041
	.align	2,0x90
L_2_2021:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_2041:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
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
	jl	JJ_2040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2040:
	ret

FUNC(op_10bb)

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
RR0_2141:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_2_2082
	movswl	%di,%edi
L_2_2082:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_2_2083
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_2_2084
	movl	%ebp,%ebx
L_2_2084:
	testl	$64,%esi
	je	L_2_2085
	movl	%ebp,%edi
L_2_2085:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_2_2086
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_2142:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_2_2086:
	cmpl	$48,%edx
	jne	L_2_2089
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2143:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_2_2089:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_2_2092
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_2144:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_2092:
	cmpl	$3,16-16(%esp)
	jne	L_2_2095
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_2145:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_2_2095:
	andl	$4,%esi
	jne	L_2_2098
	addl	%edi,%ebx
L_2_2098:
	cmpl	$0,16-16(%esp)
	je	L_2_2099
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_2_2099:
	testl	%esi,%esi
	je	L_2_2102
	addl	%edi,%ebx
L_2_2102:
	leal	(%ebp,%ebx),%edx
	jmp	L_2_2103
	.align	2,0x90
L_2_2083:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_2_2103:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	28-16(%esp),%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
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
	jl	JJ_2041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2041:
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


FUNC(op_a60)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	$GLOBL(regs),%ebp
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_2033:
	rolw	$8,%dx
	movl	%edx,%eax
	movl	(%ecx,%ebp),%edx
	addl	$-2,%edx
	movl	%eax,%edi
	movl	%edx,%ebx
	movl	%edx,16-16(%esp)
	shrl	$14,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,%eax
	movl	16-16(%esp),%edx
	movl	%edx,(%ecx,%ebp)
	xorl	%eax,%edi
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	xorl	%eax,%eax
	movw	%di,%ax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2042:
	ret

FUNC(op_a68)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2034:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2009:
	rolw	$8,%ax
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
	xorl	%edx,%ebx
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	xorl	%edx,%edx
	movw	%bx,%dx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2043:
	ret

FUNC(op_a78)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2035:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2010:
	rolw	$8,%ax
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
	xorl	%edx,%ebx
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	xorl	%edx,%edx
	movw	%bx,%dx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2044:
	ret

FUNC(op_a79)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2036:
	rolw	$8,%ax
	movl	%eax,%ebx
	movl	0x2164334A+4(%edx),%eax
RR4_2011:
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
	xorl	%edx,%ebx
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	xorl	%edx,%edx
	movw	%bx,%dx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2045:
	ret

FUNC(op_a7c)

	cmpb	$0,GLOBL(regs)+80
	jne	L_2_466
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2046:
	ret
	.align	2,0x90
L_2_466:
	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_2037:
	rolw	$8,%dx
	movl	%edx,%eax
	xorw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2047:
	ret

FUNC(op_a80)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_2038:
	sall	$2,%edx
	bswapl	%eax
	xorl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2048:
	ret

FUNC(op_a90)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_2039:
	movb	GLOBL(regs)+2(,%edx,4),%cl
	bswapl	%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	xorl	%eax,%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ecx),%edx
	bswapl	%ebx
	movl	%ebx,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2049:
	ret

FUNC(op_a98)

	movl	$GLOBL(regs),%ebp
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	addl	$8,%esi
	movl	0x2164334A+2(%eax),%edi
RR2_2040:
	sall	$2,%esi
	bswapl	%edi
	movl	(%esi,%ebp),%ecx
	movb	2(%esi,%ebp),%bl
	movl	%ecx,%edx
	sall	$2,%ebx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%edx,%eax
	addl	$4,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%esi,%ebp)
	xorl	%eax,%edi
	testl	%edi,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ebx),%edx
	bswapl	%edi
	movl	%edi,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2050:
	ret

FUNC(op_aa0)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%ebp
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%ebp),%ecx
	movl	GLOBL(regs)+88,%eax
	addl	$-4,%ecx
	movl	0x2164334A+2(%eax),%edi
RR2_2041:
	movl	%ecx,%ebx
	bswapl	%edi
	shrl	$14,%ebx
	movl	%ecx,%edx
	andl	$1020,%ebx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%esi,%ebp)
	xorl	%eax,%edi
	testl	%edi,%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	GLOBL(W24)(%ebx),%edx
	bswapl	%edi
	movl	%edi,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2051:
	ret

FUNC(op_aa8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_2006:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_2042:
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
	xorl	%edx,%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	popl	%ebx
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2052:
	ret

FUNC(op_ab8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_2007:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_2043:
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
	xorl	%edx,%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2053:
	ret

FUNC(op_ab9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_2044:
	movl	0x2164334A+6(%eax),%eax
RR6_2008:
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
	xorl	%edx,%ebx
	testl	%ebx,%ebx
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	GLOBL(W24)(%ecx),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$10,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2054:
	ret

FUNC(op_ad0)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2045:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%edi,%edi
	movl	%eax,%ecx
	xorl	%eax,%eax
	movb	2(%esi,%edx,4),%al
	movw	(%esi,%edx,4),%di
	leal	0(,%eax,4),%ebp
	movl	%edi,20-16(%esp)
	movl	GLOBL(R24)(%ebp),%eax
	movb	(%edi,%eax),%bl
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	%edi,16-16(%esp)
	leal	0(,%eax,4),%edx
	cmpb	(%edx,%esi),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_604
	movb	(%esi,%edi,4),%dl
	movl	GLOBL(W24)(%ebp),%eax
	movl	20-16(%esp),%edi
	movb	%dl,(%edi,%eax)
	jmp	L_2_606
	.align	2,0x90
L_2_604:
	movsbl	%bl,%eax
	movl	%eax,(%edx,%esi)
L_2_606:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2055:
	ret

FUNC(op_ad8)

	subl	$12,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%eax
	movl	16-16(%esp),%ecx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_2046:
	rolw	$8,%bx
	addl	$8,%ecx
	movl	%ebx,%eax
	sall	$2,%ecx
	movl	%eax,%esi
	movl	(%ecx,%edi),%edx
	xorl	%eax,%eax
	movl	%edx,%ebx
	movb	2(%ecx,%edi),%al
	andl	$65535,%ebx
	leal	0(,%eax,4),%ebp
	movl	%ebx,20-16(%esp)
	movl	GLOBL(R24)(%ebp),%eax
	movb	(%ebx,%eax),%al
	movb	%al,27-16(%esp)
	movl	16-16(%esp),%ebx
	movl	%esi,%eax
	addl	GLOBL(areg_byteinc)(,%ebx,4),%edx
	sarw	$6,%ax
	movl	%edx,(%ecx,%edi)
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%esi,%eax
	andl	$7,%eax
	movb	27-16(%esp),%bl
	leal	0(,%eax,4),%edx
	cmpb	(%edx,%edi),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_618
	movb	(%edi,%ecx,4),%dl
	movl	GLOBL(W24)(%ebp),%eax
	movl	20-16(%esp),%ebx
	movb	%dl,(%ebx,%eax)
	jmp	L_2_620
	.align	2,0x90
L_2_618:
	movsbl	27-16(%esp),%eax
	movl	%eax,(%edx,%edi)
L_2_620:
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2056:
	ret

FUNC(op_ae0)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_2047:
	rolw	$8,%bx
	movl	%ebx,%eax
	sall	$2,%ecx
	movw	%ax,20-16(%esp)
	movl	$GLOBL(regs),%esi
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%al
	movb	%al,19-16(%esp)
	movl	%edx,(%ecx,%esi)
	movl	20-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	20-16(%esp),%eax
	andl	$7,%eax
	movb	19-16(%esp),%bl
	leal	0(,%eax,4),%edx
	cmpb	(%edx,%esi),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_632
	movb	(%esi,%ecx,4),%dl
	movl	GLOBL(W24)(%edi),%eax
	movb	%dl,(%ebp,%eax)
	jmp	L_2_634
	.align	2,0x90
L_2_632:
	movsbl	19-16(%esp),%eax
	movl	%eax,(%edx,%esi)
L_2_634:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2057:
	ret

FUNC(op_ae8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2048:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2012:
	rolw	$8,%ax
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	%edx,%ebp
	movl	%eax,20-16(%esp)
	andl	$1020,%ebp
	movl	20-16(%esp),%edi
	movl	GLOBL(R24)(%ebp),%eax
	movb	(%edi,%eax),%cl
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ebx,%eax
	andl	$7,%eax
	movl	%edi,16-16(%esp)
	leal	0(,%eax,4),%edx
	cmpb	(%edx,%esi),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_647
	movb	(%esi,%edi,4),%dl
	movl	GLOBL(W24)(%ebp),%eax
	movl	20-16(%esp),%edi
	movb	%dl,(%edi,%eax)
	jmp	L_2_649
	.align	2,0x90
L_2_647:
	movsbl	%cl,%eax
	movl	%eax,(%edx,%esi)
L_2_649:
	addl	$6,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2058:
	ret

FUNC(op_af8)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2049:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2013:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%edi
	movl	%eax,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%edx
	leal	0(,%eax,4),%ecx
	cmpb	(%ecx,%edx),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_695
	movb	(%edx,%esi,4),%dl
	movl	GLOBL(W24)(%edi),%eax
	movb	%dl,(%ebp,%eax)
	jmp	L_2_697
	.align	2,0x90
L_2_695:
	movsbl	%bl,%eax
	movl	%eax,(%ecx,%edx)
L_2_697:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2059:
	ret

FUNC(op_af9)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2050:
	rolw	$8,%ax
	movl	%eax,%ecx
	movl	0x2164334A+4(%edx),%edx
RR4_2014:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%edx
	leal	0(,%eax,4),%ecx
	cmpb	(%ecx,%edx),%bl
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_711
	movb	(%edx,%esi,4),%dl
	movl	GLOBL(W24)(%edi),%eax
	movb	%dl,(%ebp,%eax)
	jmp	L_2_713
	.align	2,0x90
L_2_711:
	movsbl	%bl,%eax
	movl	%eax,(%ecx,%edx)
L_2_713:
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2060:
	ret

FUNC(op_c00)

	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	movb	GLOBL(regs)(,%eax,4),%al
	cmpb	0x2164334A+3(%edx),%al
RR3_2002:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2061:
	ret

FUNC(op_c10)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(R24)(,%edx,4),%eax
	movl	GLOBL(regs)+88,%ebx
	movb	(%ecx,%eax),%al
	cmpb	0x2164334A+3(%ebx),%al
RR3_2003:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ebx
	movl	%ebx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2062:
	ret

FUNC(op_c18)

	subl	$4,%esp
	movl	%eax,%edi
	andl	$7,%edi
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	leal	8(%edi),%ecx
	movb	0x2164334A+3(%eax),%al
RR3_2004:
	sall	$2,%ecx
	movb	%al,15-12(%esp)
	movl	(%ecx,%esi),%edx
	xorl	%eax,%eax
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	cmpb	15-12(%esp),%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2063:
	ret

FUNC(op_c20)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	leal	8(%edx),%ecx
	movb	0x2164334A+3(%eax),%al
RR3_2005:
	movl	$GLOBL(regs),%esi
	movb	%al,11-8(%esp)
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
	cmpb	11-8(%esp),%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2064:
	ret

FUNC(op_c28)

	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2015:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	cmpb	0x2164334A+3(%ecx),%dl
RR3_2006:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2065:
	ret

FUNC(op_c38)

	movl	GLOBL(regs)+88,%ecx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ecx),%dx
RR4_2016:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	cmpb	0x2164334A+3(%ecx),%al
RR3_2007:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2066:
	ret

FUNC(op_c39)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+4(%ecx),%edx
RR4_2017:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	cmpb	0x2164334A+3(%ecx),%al
RR3_2008:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$8,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2067:
	ret

FUNC(op_c3a)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2018:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	cmpb	0x2164334A+3(%ecx),%dl
RR3_2009:
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2068:
	ret

FUNC(op_c40)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%edx
	andl	$7,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2051:
	rolw	$8,%ax
	movw	GLOBL(regs)(,%ecx,4),%cx
	cmpw	%ax,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2069:
	ret

FUNC(op_c50)

	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	movl	GLOBL(regs)+88,%ecx
	andl	$65535,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%ecx),%bx
RR2_2052:
	rolw	$8,%bx
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%bx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	popl	%ebx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2070:
	ret

FUNC(op_c58)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2053:
	rolw	$8,%di
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	$2,%edx
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%esi)
	cmpw	%di,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2071:
	ret

FUNC(op_c60)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2054:
	rolw	$8,%di
	addl	$8,%ebx
	movl	%edi,12-12(%esp)
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
	cmpw	12-12(%esp),%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2072:
	ret

FUNC(op_c68)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2019:
	rolw	$8,%ax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%ecx),%bx
RR2_2055:
	rolw	$8,%bx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%bx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	popl	%ebx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2073:
	ret

FUNC(op_c78)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2020:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%ecx),%bx
RR2_2056:
	rolw	$8,%bx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%bx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2074:
	ret

FUNC(op_c79)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+4(%ecx),%eax
RR4_2021:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%ecx),%bx
RR2_2057:
	rolw	$8,%bx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%bx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$8,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2075:
	ret

FUNC(op_c7a)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2022:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%ecx),%bx
RR2_2058:
	rolw	$8,%bx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cmpw	%bx,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2076:
	ret

FUNC(op_c80)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%edx
	andl	$7,%ecx
	movl	0x2164334A+2(%edx),%eax
RR2_2059:
	bswapl	%eax
	movl	GLOBL(regs)(,%ecx,4),%ecx
	cmpl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2077:
	ret

FUNC(op_c90)

	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	movl	GLOBL(regs)+88,%ecx
	andl	$65535,%eax
	movl	0x2164334A+2(%ecx),%ebx
RR2_2060:
	addl	GLOBL(R24)(,%edx,4),%eax
	bswapl	%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%ebx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	popl	%ebx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2078:
	ret

FUNC(op_c98)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	0x2164334A+2(%eax),%edi
RR2_2061:
	movl	(%ecx,%esi),%edx
	bswapl	%edi
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%edx,(%ecx,%esi)
	cmpl	%edi,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2079:
	ret

FUNC(op_ca0)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	(%ebx,%esi),%ecx
	movl	0x2164334A+2(%eax),%edi
RR2_2062:
	addl	$-4,%ecx
	bswapl	%edi
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ecx,(%ebx,%esi)
	cmpl	%edi,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2080:
	ret

FUNC(op_ca8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+6(%ecx),%ax
RR6_2009:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0x2164334A+2(%ecx),%ebx
RR2_2063:
	addl	GLOBL(R24)(%edx),%eax
	bswapl	%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%ebx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$8,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2081:
	ret

FUNC(op_cb8)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+6(%ecx),%ax
RR6_2010:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0x2164334A+2(%ecx),%ebx
RR2_2064:
	addl	GLOBL(R24)(%edx),%eax
	bswapl	%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%ebx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$8,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2082:
	ret

FUNC(op_cb9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+6(%ecx),%eax
RR6_2011:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0x2164334A+2(%ecx),%ebx
RR2_2065:
	addl	GLOBL(R24)(%edx),%eax
	bswapl	%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%ebx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$10,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2083:
	ret

FUNC(op_cba)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+6(%ecx),%ax
RR6_2012:
	rolw	$8,%ax
	cwtl
	leal	6(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0x2164334A+2(%ecx),%ebx
RR2_2066:
	addl	GLOBL(R24)(%edx),%eax
	bswapl	%ebx
	movl	(%eax),%eax
	bswapl	%eax
	cmpl	%ebx,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$8,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2084:
	ret

FUNC(op_cd0)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2067:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%edi,%edi
	movl	%eax,%ecx
	xorl	%eax,%eax
	movb	2(%esi,%edx,4),%al
	movw	(%esi,%edx,4),%di
	leal	0(,%eax,4),%ebp
	movl	%edi,20-16(%esp)
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ebx
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	%edi,16-16(%esp)
	leal	0(,%eax,4),%edx
	cmpw	(%edx,%esi),%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1134
	xorl	%eax,%eax
	movw	(%esi,%edi,4),%ax
	movl	20-16(%esp),%edx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebp),%edx
	movw	%ax,(%edx)
	jmp	L_2_1137
	.align	2,0x90
L_2_1134:
	movswl	%bx,%eax
	movl	%eax,(%edx,%esi)
L_2_1137:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2085:
	ret

FUNC(op_ce0)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2068:
	rolw	$8,%di
	movl	(%ecx,%esi),%edx
	movl	%edi,%eax
	addl	$-2,%edx
	movl	%eax,%ebx
	movl	%edx,%eax
	movl	%edx,%edi
	shrl	$14,%eax
	andl	$65535,%edi
	movl	%eax,%ebp
	movl	%edi,20-16(%esp)
	andl	$1020,%ebp
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movw	%ax,18-16(%esp)
	movl	%ebx,%eax
	movl	%edx,(%ecx,%esi)
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%ebx,%eax
	andl	$7,%eax
	movw	18-16(%esp),%di
	leal	0(,%eax,4),%edx
	cmpw	(%edx,%esi),%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1161
	xorl	%eax,%eax
	movw	(%esi,%ecx,4),%ax
	movl	20-16(%esp),%edx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebp),%edx
	movw	%ax,(%edx)
	jmp	L_2_1164
	.align	2,0x90
L_2_1161:
	movswl	18-16(%esp),%eax
	movl	%eax,(%edx,%esi)
L_2_1164:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2086:
	ret

FUNC(op_ce8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2069:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2023:
	rolw	$8,%ax
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	%edx,%ebp
	movl	%eax,20-16(%esp)
	andl	$1020,%ebp
	addl	GLOBL(R24)(%ebp),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%edx
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ebx,%eax
	andl	$7,%eax
	movl	%edi,16-16(%esp)
	leal	0(,%eax,4),%ecx
	cmpw	(%ecx,%esi),%dx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1180
	xorl	%eax,%eax
	movw	(%esi,%edi,4),%ax
	movl	20-16(%esp),%edx
	rolw	$8,%ax
	addl	GLOBL(W24)(%ebp),%edx
	movw	%ax,(%edx)
	jmp	L_2_1183
	.align	2,0x90
L_2_1180:
	movswl	%dx,%eax
	movl	%eax,(%ecx,%esi)
L_2_1183:
	addl	$6,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2087:
	ret

FUNC(op_cf8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2070:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2024:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%edi
	movl	%eax,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	movl	%esi,16-16(%esp)
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	cmpw	(%edx,%ecx),%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1234
	xorl	%eax,%eax
	movw	(%ecx,%esi,4),%ax
	movl	GLOBL(W24)(%edi),%edx
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	jmp	L_2_1237
	.align	2,0x90
L_2_1234:
	movswl	%bx,%eax
	movl	%eax,(%edx,%ecx)
L_2_1237:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2088:
	ret

FUNC(op_cf9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2071:
	rolw	$8,%ax
	movl	%eax,%ecx
	movl	0x2164334A+4(%edx),%edx
RR4_2025:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	movl	%esi,16-16(%esp)
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	cmpw	(%edx,%ecx),%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1254
	xorl	%eax,%eax
	movw	(%ecx,%esi,4),%ax
	movl	GLOBL(W24)(%edi),%edx
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	jmp	L_2_1257
	.align	2,0x90
L_2_1254:
	movswl	%bx,%eax
	movl	%eax,(%edx,%ecx)
L_2_1257:
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2089:
	ret

FUNC(op_ed0)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2072:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edi,%edi
	movl	%eax,%ecx
	xorl	%eax,%eax
	movb	2(%ebx,%edx,4),%al
	movw	(%ebx,%edx,4),%di
	leal	0(,%eax,4),%ebp
	movl	%edi,20-16(%esp)
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	movl	(%eax),%esi
	bswapl	%esi
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	%edi,16-16(%esp)
	leal	0(,%eax,4),%edx
	cmpl	(%edx,%ebx),%esi
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1701
	movl	20-16(%esp),%eax
	movl	(%ebx,%edi,4),%ebx
	addl	GLOBL(W24)(%ebp),%eax
	bswapl	%ebx
	movl	%ebx,(%eax)
	jmp	L_2_1704
	.align	2,0x90
L_2_1701:
	movl	%esi,(%edx,%ebx)
L_2_1704:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2090:
	ret

FUNC(op_ed8)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2073:
	rolw	$8,%di
	movl	%edi,%eax
	movl	(%ecx,%esi),%edx
	movl	%eax,%ebx
	xorl	%eax,%eax
	movl	%edx,%edi
	movb	2(%ecx,%esi),%al
	andl	$65535,%edi
	leal	0(,%eax,4),%ebp
	movl	%edi,20-16(%esp)
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	addl	$4,%edx
	movl	%ebx,%eax
	movl	%edx,(%ecx,%esi)
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%ebx,%eax
	andl	$7,%eax
	movl	16-16(%esp),%edi
	leal	0(,%eax,4),%edx
	cmpl	(%edx,%esi),%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1719
	movl	20-16(%esp),%eax
	movl	(%esi,%ecx,4),%ecx
	addl	GLOBL(W24)(%ebp),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	jmp	L_2_1722
	.align	2,0x90
L_2_1719:
	movl	16-16(%esp),%edi
	movl	%edi,(%edx,%esi)
L_2_1722:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2091:
	ret

FUNC(op_ee0)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_2074:
	rolw	$8,%di
	movl	(%ecx,%esi),%edx
	movl	%edi,%eax
	addl	$-4,%edx
	movl	%eax,%ebx
	movl	%edx,%eax
	movl	%edx,%edi
	shrl	$14,%eax
	andl	$65535,%edi
	movl	%eax,%ebp
	movl	%edi,20-16(%esp)
	andl	$1020,%ebp
	movl	%edi,%eax
	addl	GLOBL(R24)(%ebp),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	movl	%edx,(%ecx,%esi)
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$7,%ecx
	movl	%ebx,%eax
	andl	$7,%eax
	movl	16-16(%esp),%edi
	leal	0(,%eax,4),%edx
	cmpl	(%edx,%esi),%edi
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1737
	movl	20-16(%esp),%eax
	movl	(%esi,%ecx,4),%ecx
	addl	GLOBL(W24)(%ebp),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	jmp	L_2_1740
	.align	2,0x90
L_2_1737:
	movl	16-16(%esp),%edi
	movl	%edi,(%edx,%esi)
L_2_1740:
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2092:
	ret

FUNC(op_ee8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_2075:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_2026:
	rolw	$8,%ax
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	%edx,%ebp
	movl	%eax,16-16(%esp)
	andl	$1020,%ebp
	addl	GLOBL(R24)(%ebp),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$7,%edi
	movl	%ebx,%eax
	andl	$7,%eax
	leal	0(,%eax,4),%ecx
	cmpl	(%ecx,%esi),%edx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1756
	movl	16-16(%esp),%eax
	movl	(%esi,%edi,4),%edi
	addl	GLOBL(W24)(%ebp),%eax
	bswapl	%edi
	movl	%edi,(%eax)
	jmp	L_2_1759
	.align	2,0x90
L_2_1756:
	movl	%edx,(%ecx,%esi)
L_2_1759:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2093:
	ret

FUNC(op_ef8)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2076:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_2027:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%edi
	movl	%eax,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	cmpl	(%edx,%ecx),%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1810
	movl	GLOBL(W24)(%edi),%eax
	movl	(%ecx,%esi,4),%esi
	addl	%ebp,%eax
	bswapl	%esi
	movl	%esi,(%eax)
	jmp	L_2_1813
	.align	2,0x90
L_2_1810:
	movl	%ebx,(%edx,%ecx)
L_2_1813:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2094:
	ret

FUNC(op_ef9)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2077:
	rolw	$8,%ax
	movl	%eax,%ecx
	movl	0x2164334A+4(%edx),%edx
RR4_2028:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%ecx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$7,%esi
	movl	%ecx,%eax
	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	0(,%eax,4),%edx
	cmpl	(%edx,%ecx),%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags

	testb	$64,regflags
	je	L_2_1830
	movl	GLOBL(W24)(%edi),%eax
	movl	(%ecx,%esi,4),%esi
	addl	%ebp,%eax
	bswapl	%esi
	movl	%esi,(%eax)
	jmp	L_2_1833
	.align	2,0x90
L_2_1830:
	movl	%ebx,(%edx,%ecx)
L_2_1833:
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2095:
	ret

FUNC(op_1000)

	movl	%eax,%ecx
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$9,%edx
	movl	$GLOBL(regs),%eax
	andl	$7,%edx
	movb	(%eax,%ecx,4),%cl
	testb	%cl,%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%cl,(%eax,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2096:
	ret

FUNC(op_1010)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	movl	%edx,%esi
	andl	$7,%eax
	shrl	$9,%esi
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%edx,%eax,4),%cl
	movw	(%edx,%eax,4),%bx
	movl	GLOBL(R24)(,%ecx,4),%eax
	andl	$7,%esi
	movb	(%ebx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,(%edx,%esi,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2097:
	ret

FUNC(op_1018)

	movl	%eax,%ebp
	andl	$7,%ebp
	movl	%eax,%edi
	shrl	$9,%edi
	leal	8(%ebp),%ecx
	xorl	%eax,%eax
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$7,%edi
	movl	(%ecx,%ebx),%edx
	movb	2(%ecx,%ebx),%al
	movl	%edx,%esi
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%esi
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	movb	(%esi,%eax),%al
	movl	%edx,(%ecx,%ebx)
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%edi,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2098:
	ret

FUNC(op_1020)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	andl	$7,%eax
	shrl	$9,%edi
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
	andl	$7,%edi
	movb	(%esi,%eax),%al
	movl	%edx,(%ecx,%ebx)
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2099:
	ret

FUNC(op_1028)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_2078:
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
	andl	$7,%ebx
	movb	(%eax,%edx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ecx,%ebx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2100:
	ret

FUNC(op_1038)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_2079:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2101:
	ret

FUNC(op_1039)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_2080:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2207:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2102:
	ret

FUNC(op_103a)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%edx
	shrl	$9,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2081:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2208:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2103:
	ret

FUNC(op_103c)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%edx
	movb	0x2164334A+3(%eax),%al
RR3_2010:
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2209:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2104:
	ret

FUNC(op_1080)

	movl	%eax,%ecx
	shrl	$9,%eax
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	andl	$7,%ecx
	addl	$8,%eax
	movb	(%edx,%ecx,4),%cl
	movl	(%edx,%eax,4),%edx
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
	popl	%eax
	decl	%eax
	jl	JJ_2105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2210:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2105:
	ret

FUNC(op_1090)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	shrl	$9,%edx
	movl	$GLOBL(regs),%esi
	andl	$7,%eax
	andl	$7,%edx
	xorl	%ebx,%ebx
	addl	$8,%eax
	addl	$8,%edx
	movb	2(%esi,%eax,4),%cl
	movw	(%esi,%eax,4),%bx
	movl	(%esi,%edx,4),%edx
	movl	GLOBL(R24)(,%ecx,4),%eax
	xorl	%ecx,%ecx
	movb	(%ebx,%eax),%cl
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2211:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2106:
	ret

FUNC(op_1098)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	leal	8(%ebp),%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	sall	$2,%ecx
	shrl	$9,%ebx
	movl	%ecx,16-16(%esp)
	xorl	%eax,%eax
	andl	$7,%ebx
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%al
	movl	%edx,%edi
	movl	GLOBL(R24)(,%eax,4),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%edx
	andl	$65535,%edi
	addl	$8,%ebx
	movzbl	(%edi,%eax),%edi
	movl	%edx,(%ecx,%esi)
	movl	(%esi,%ebx,4),%edx
	movl	%edi,%ecx
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
	jl	JJ_2107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2212:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2107:
	ret

FUNC(op_10a0)

	movl	%eax,%edx
	pushl	%esi
	movl	$GLOBL(regs),%edi
	pushl	%ebx
	andl	$7,%eax
	movl	%edx,%esi
	leal	8(%eax),%ecx
	shrl	$9,%esi
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%ecx,%edi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebx
	andl	$1020,%eax
	andl	$65535,%ebx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%esi
	movb	(%ebx,%eax),%bl
	addl	$8,%esi
	movl	%edx,(%ecx,%edi)
	andl	$255,%ebx
	movl	(%edi,%esi,4),%edx
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
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2213:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2108:
	ret

FUNC(op_10a8)

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
RR2_2082:
	rolw	$8,%di
	movl	%edi,%eax
	movl	$GLOBL(regs),%esi
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	andl	$7,%ecx
	shrl	$14,%edx
	xorl	%ebx,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	addl	$8,%ecx
	movb	(%eax,%edx),%bl
	movl	(%esi,%ecx,4),%edx
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
	jl	JJ_2109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2214:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2109:
	ret

FUNC(op_10b8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_2083:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movb	(%edx,%eax),%bl
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2215:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2110:
	ret

FUNC(op_10b9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_2084:
	bswapl	%edx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movb	(%edx,%eax),%bl
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	jl	JJ_2111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2216:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2111:
	ret

FUNC(op_10ba)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_2085:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%edx),%edx
	movl	%edx,%eax
	xorl	%ebx,%ebx
	shrl	$14,%eax
	andl	$7,%ecx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	addl	$8,%ecx
	movb	(%edx,%eax),%bl
	movl	GLOBL(regs)(,%ecx,4),%edx
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2217:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2112:
	ret

FUNC(op_10bc)

	shrl	$9,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	addl	$8,%eax
	movb	0x2164334A+3(%edx),%cl
RR3_2011:
	movl	GLOBL(regs)(,%eax,4),%edx
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
	jl	JJ_2113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2218:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2113:
	ret

FUNC(op_10c0)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebx
	andl	$7,%eax
	shrl	$9,%ebx
	movb	GLOBL(regs)(,%eax,4),%al
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
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_2114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2219:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2114:
	ret

FUNC(op_10d0)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	pushl	%ebx
	movl	%edx,%esi
	andl	$7,%eax
	shrl	$9,%esi
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ebx,%ebx
	movb	2(%ecx,%eax,4),%dl
	movw	(%ecx,%eax,4),%bx
	movl	GLOBL(R24)(,%edx,4),%eax
	andl	$7,%esi
	movb	(%ebx,%eax),%bl
	leal	8(%esi),%eax
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%esi,4),%esi
	movl	(%eax,%ecx),%edx
	addl	%edx,%esi
	andl	$255,%ebx
	movl	%esi,(%eax,%ecx)
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
	jl	JJ_2115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2220:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2115:
	ret

FUNC(op_10d8)

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
	andl	$7,%edi
	movzbl	(%ebx,%eax),%esi
	movl	$GLOBL(areg_byteinc),%ebx
	leal	8(%edi),%eax
	addl	(%ebx,%ebp,4),%edx
	sall	$2,%eax
	movl	%edx,GLOBL(regs)(%ecx)
	movl	GLOBL(regs)(%eax),%edx
	movl	(%ebx,%edi,4),%edi
	addl	%edx,%edi
	movl	%esi,%ecx
	movl	%edi,GLOBL(regs)(%eax)
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
	jl	JJ_2116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2221:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2116:
	ret

FUNC(op_10e0)

	movl	%eax,%edx
	pushl	%edi
	movl	$GLOBL(areg_byteinc),%ebp
	pushl	%esi
	andl	$7,%eax
	movl	%edx,%edi
	pushl	%ebx
	shrl	$9,%edi
	leal	8(%eax),%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebp,%eax,4),%eax
	movl	(%ebx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%edi
	movb	(%ecx,%eax),%cl
	leal	8(%edi),%eax
	movl	%edx,(%ebx,%esi)
	sall	$2,%eax
	movl	(%ebp,%edi,4),%edi
	movl	(%eax,%esi),%edx
	addl	%edx,%edi
	andl	$255,%ecx
	movl	%edi,(%eax,%esi)
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
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_2117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_2222:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_2117:
	ret

FUNC(Init020_02)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_2000-4
	movl	%eax,RR0_2001-4
	movl	%eax,RR0_2002-4
	movl	%eax,RR0_2003-4
	movl	%eax,RR0_2004-4
	movl	%eax,RR0_2005-4
	movl	%eax,RR0_2006-4
	movl	%eax,RR0_2007-4
	movl	%eax,RR0_2008-4
	movl	%eax,RR0_2009-4
	movl	%eax,RR0_2010-4
	movl	%eax,RR0_2011-4
	movl	%eax,RR0_2012-4
	movl	%eax,RR0_2013-4
	movl	%eax,RR0_2014-4
	movl	%eax,RR0_2015-4
	movl	%eax,RR0_2016-4
	movl	%eax,RR0_2017-4
	movl	%eax,RR0_2018-4
	movl	%eax,RR0_2019-4
	movl	%eax,RR0_2020-4
	movl	%eax,RR0_2021-4
	movl	%eax,RR0_2022-4
	movl	%eax,RR0_2023-4
	movl	%eax,RR0_2024-4
	movl	%eax,RR0_2025-4
	movl	%eax,RR0_2026-4
	movl	%eax,RR0_2027-4
	movl	%eax,RR0_2028-4
	movl	%eax,RR0_2029-4
	movl	%eax,RR0_2030-4
	movl	%eax,RR0_2031-4
	movl	%eax,RR0_2032-4
	movl	%eax,RR0_2033-4
	movl	%eax,RR0_2034-4
	movl	%eax,RR0_2035-4
	movl	%eax,RR0_2036-4
	movl	%eax,RR0_2037-4
	movl	%eax,RR0_2038-4
	movl	%eax,RR0_2039-4
	movl	%eax,RR0_2040-4
	movl	%eax,RR0_2041-4
	movl	%eax,RR0_2042-4
	movl	%eax,RR0_2043-4
	movl	%eax,RR0_2044-4
	movl	%eax,RR0_2045-4
	movl	%eax,RR0_2046-4
	movl	%eax,RR0_2047-4
	movl	%eax,RR0_2048-4
	movl	%eax,RR0_2049-4
	movl	%eax,RR0_2050-4
	movl	%eax,RR0_2051-4
	movl	%eax,RR0_2052-4
	movl	%eax,RR0_2053-4
	movl	%eax,RR0_2054-4
	movl	%eax,RR0_2055-4
	movl	%eax,RR0_2056-4
	movl	%eax,RR0_2057-4
	movl	%eax,RR0_2058-4
	movl	%eax,RR0_2059-4
	movl	%eax,RR0_2060-4
	movl	%eax,RR0_2061-4
	movl	%eax,RR0_2062-4
	movl	%eax,RR0_2063-4
	movl	%eax,RR0_2064-4
	movl	%eax,RR0_2065-4
	movl	%eax,RR0_2066-4
	movl	%eax,RR0_2067-4
	movl	%eax,RR0_2068-4
	movl	%eax,RR0_2069-4
	movl	%eax,RR0_2070-4
	movl	%eax,RR0_2071-4
	movl	%eax,RR0_2072-4
	movl	%eax,RR0_2073-4
	movl	%eax,RR0_2074-4
	movl	%eax,RR0_2075-4
	movl	%eax,RR0_2076-4
	movl	%eax,RR0_2077-4
	movl	%eax,RR0_2078-4
	movl	%eax,RR0_2079-4
	movl	%eax,RR0_2080-4
	movl	%eax,RR0_2081-4
	movl	%eax,RR0_2082-4
	movl	%eax,RR0_2083-4
	movl	%eax,RR0_2084-4
	movl	%eax,RR0_2085-4
	movl	%eax,RR0_2086-4
	movl	%eax,RR0_2087-4
	movl	%eax,RR0_2088-4
	movl	%eax,RR0_2089-4
	movl	%eax,RR0_2090-4
	movl	%eax,RR0_2091-4
	movl	%eax,RR0_2092-4
	movl	%eax,RR0_2093-4
	movl	%eax,RR0_2094-4
	movl	%eax,RR0_2095-4
	movl	%eax,RR0_2096-4
	movl	%eax,RR0_2097-4
	movl	%eax,RR0_2098-4
	movl	%eax,RR0_2099-4
	movl	%eax,RR0_2100-4
	movl	%eax,RR0_2101-4
	movl	%eax,RR0_2102-4
	movl	%eax,RR0_2103-4
	movl	%eax,RR0_2104-4
	movl	%eax,RR0_2105-4
	movl	%eax,RR0_2106-4
	movl	%eax,RR0_2107-4
	movl	%eax,RR0_2108-4
	movl	%eax,RR0_2109-4
	movl	%eax,RR0_2110-4
	movl	%eax,RR0_2111-4
	movl	%eax,RR0_2112-4
	movl	%eax,RR0_2113-4
	movl	%eax,RR0_2114-4
	movl	%eax,RR0_2115-4
	movl	%eax,RR0_2116-4
	movl	%eax,RR0_2117-4
	movl	%eax,RR0_2118-4
	movl	%eax,RR0_2119-4
	movl	%eax,RR0_2120-4
	movl	%eax,RR0_2121-4
	movl	%eax,RR0_2122-4
	movl	%eax,RR0_2123-4
	movl	%eax,RR0_2124-4
	movl	%eax,RR0_2125-4
	movl	%eax,RR0_2126-4
	movl	%eax,RR0_2127-4
	movl	%eax,RR0_2128-4
	movl	%eax,RR0_2129-4
	movl	%eax,RR0_2130-4
	movl	%eax,RR0_2131-4
	movl	%eax,RR0_2132-4
	movl	%eax,RR0_2133-4
	movl	%eax,RR0_2134-4
	movl	%eax,RR0_2135-4
	movl	%eax,RR0_2136-4
	movl	%eax,RR0_2137-4
	movl	%eax,RR0_2138-4
	movl	%eax,RR0_2139-4
	movl	%eax,RR0_2140-4
	movl	%eax,RR0_2141-4
	movl	%eax,RR0_2142-4
	movl	%eax,RR0_2143-4
	movl	%eax,RR0_2144-4
	movl	%eax,RR0_2145-4
	movl	%eax,RR0_2146-4
	movl	%eax,RR0_2147-4
	movl	%eax,RR0_2148-4
	movl	%eax,RR0_2149-4
	movl	%eax,RR0_2150-4
	movl	%eax,RR0_2151-4
	movl	%eax,RR0_2152-4
	movl	%eax,RR0_2153-4
	movl	%eax,RR0_2154-4
	movl	%eax,RR0_2155-4
	movl	%eax,RR0_2156-4
	movl	%eax,RR0_2157-4
	movl	%eax,RR0_2158-4
	movl	%eax,RR0_2159-4
	movl	%eax,RR0_2160-4
	movl	%eax,RR0_2161-4
	movl	%eax,RR0_2162-4
	movl	%eax,RR0_2163-4
	movl	%eax,RR0_2164-4
	movl	%eax,RR0_2165-4
	movl	%eax,RR0_2166-4
	movl	%eax,RR0_2167-4
	movl	%eax,RR0_2168-4
	movl	%eax,RR0_2169-4
	movl	%eax,RR0_2170-4
	movl	%eax,RR0_2171-4
	movl	%eax,RR0_2172-4
	movl	%eax,RR0_2173-4
	movl	%eax,RR0_2174-4
	movl	%eax,RR0_2175-4
	movl	%eax,RR0_2176-4
	movl	%eax,RR0_2177-4
	movl	%eax,RR0_2178-4
	movl	%eax,RR0_2179-4
	movl	%eax,RR0_2180-4
	movl	%eax,RR0_2181-4
	movl	%eax,RR0_2182-4
	movl	%eax,RR0_2183-4
	movl	%eax,RR0_2184-4
	movl	%eax,RR0_2185-4
	movl	%eax,RR0_2186-4
	movl	%eax,RR0_2187-4
	movl	%eax,RR0_2188-4
	movl	%eax,RR0_2189-4
	movl	%eax,RR0_2190-4
	movl	%eax,RR0_2191-4
	movl	%eax,RR0_2192-4
	movl	%eax,RR0_2193-4
	movl	%eax,RR0_2194-4
	movl	%eax,RR0_2195-4
	movl	%eax,RR0_2196-4
	movl	%eax,RR0_2197-4
	movl	%eax,RR0_2198-4
	movl	%eax,RR0_2199-4
	movl	%eax,RR0_2200-4
	movl	%eax,RR0_2201-4
	movl	%eax,RR0_2202-4
	movl	%eax,RR0_2203-4
	movl	%eax,RR0_2204-4
	movl	%eax,RR0_2205-4
	movl	%eax,RR0_2206-4
	movl	%eax,RR0_2207-4
	movl	%eax,RR0_2208-4
	movl	%eax,RR0_2209-4
	movl	%eax,RR0_2210-4
	movl	%eax,RR0_2211-4
	movl	%eax,RR0_2212-4
	movl	%eax,RR0_2213-4
	movl	%eax,RR0_2214-4
	movl	%eax,RR0_2215-4
	movl	%eax,RR0_2216-4
	movl	%eax,RR0_2217-4
	movl	%eax,RR0_2218-4
	movl	%eax,RR0_2219-4
	movl	%eax,RR0_2220-4
	movl	%eax,RR0_2221-4
	movl	%eax,RR0_2222-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_2000-4
	movl	%eax,RR2_2001-4
	movl	%eax,RR2_2002-4
	movl	%eax,RR2_2003-4
	movl	%eax,RR2_2004-4
	movl	%eax,RR2_2005-4
	movl	%eax,RR2_2006-4
	movl	%eax,RR2_2007-4
	movl	%eax,RR2_2008-4
	movl	%eax,RR2_2009-4
	movl	%eax,RR2_2010-4
	movl	%eax,RR2_2011-4
	movl	%eax,RR2_2012-4
	movl	%eax,RR2_2013-4
	movl	%eax,RR2_2014-4
	movl	%eax,RR2_2015-4
	movl	%eax,RR2_2016-4
	movl	%eax,RR2_2017-4
	movl	%eax,RR2_2018-4
	movl	%eax,RR2_2019-4
	movl	%eax,RR2_2020-4
	movl	%eax,RR2_2021-4
	movl	%eax,RR2_2022-4
	movl	%eax,RR2_2023-4
	movl	%eax,RR2_2024-4
	movl	%eax,RR2_2025-4
	movl	%eax,RR2_2026-4
	movl	%eax,RR2_2027-4
	movl	%eax,RR2_2028-4
	movl	%eax,RR2_2029-4
	movl	%eax,RR2_2030-4
	movl	%eax,RR2_2031-4
	movl	%eax,RR2_2032-4
	movl	%eax,RR2_2033-4
	movl	%eax,RR2_2034-4
	movl	%eax,RR2_2035-4
	movl	%eax,RR2_2036-4
	movl	%eax,RR2_2037-4
	movl	%eax,RR2_2038-4
	movl	%eax,RR2_2039-4
	movl	%eax,RR2_2040-4
	movl	%eax,RR2_2041-4
	movl	%eax,RR2_2042-4
	movl	%eax,RR2_2043-4
	movl	%eax,RR2_2044-4
	movl	%eax,RR2_2045-4
	movl	%eax,RR2_2046-4
	movl	%eax,RR2_2047-4
	movl	%eax,RR2_2048-4
	movl	%eax,RR2_2049-4
	movl	%eax,RR2_2050-4
	movl	%eax,RR2_2051-4
	movl	%eax,RR2_2052-4
	movl	%eax,RR2_2053-4
	movl	%eax,RR2_2054-4
	movl	%eax,RR2_2055-4
	movl	%eax,RR2_2056-4
	movl	%eax,RR2_2057-4
	movl	%eax,RR2_2058-4
	movl	%eax,RR2_2059-4
	movl	%eax,RR2_2060-4
	movl	%eax,RR2_2061-4
	movl	%eax,RR2_2062-4
	movl	%eax,RR2_2063-4
	movl	%eax,RR2_2064-4
	movl	%eax,RR2_2065-4
	movl	%eax,RR2_2066-4
	movl	%eax,RR2_2067-4
	movl	%eax,RR2_2068-4
	movl	%eax,RR2_2069-4
	movl	%eax,RR2_2070-4
	movl	%eax,RR2_2071-4
	movl	%eax,RR2_2072-4
	movl	%eax,RR2_2073-4
	movl	%eax,RR2_2074-4
	movl	%eax,RR2_2075-4
	movl	%eax,RR2_2076-4
	movl	%eax,RR2_2077-4
	movl	%eax,RR2_2078-4
	movl	%eax,RR2_2079-4
	movl	%eax,RR2_2080-4
	movl	%eax,RR2_2081-4
	movl	%eax,RR2_2082-4
	movl	%eax,RR2_2083-4
	movl	%eax,RR2_2084-4
	movl	%eax,RR2_2085-4
	incl	%eax
	movl	%eax,RR3_2000-4
	movl	%eax,RR3_2001-4
	movl	%eax,RR3_2002-4
	movl	%eax,RR3_2003-4
	movl	%eax,RR3_2004-4
	movl	%eax,RR3_2005-4
	movl	%eax,RR3_2006-4
	movl	%eax,RR3_2007-4
	movl	%eax,RR3_2008-4
	movl	%eax,RR3_2009-4
	movl	%eax,RR3_2010-4
	movl	%eax,RR3_2011-4
	incl	%eax
	movl	%eax,RR4_2000-4
	movl	%eax,RR4_2001-4
	movl	%eax,RR4_2002-4
	movl	%eax,RR4_2003-4
	movl	%eax,RR4_2004-4
	movl	%eax,RR4_2005-4
	movl	%eax,RR4_2006-4
	movl	%eax,RR4_2007-4
	movl	%eax,RR4_2008-4
	movl	%eax,RR4_2009-4
	movl	%eax,RR4_2010-4
	movl	%eax,RR4_2011-4
	movl	%eax,RR4_2012-4
	movl	%eax,RR4_2013-4
	movl	%eax,RR4_2014-4
	movl	%eax,RR4_2015-4
	movl	%eax,RR4_2016-4
	movl	%eax,RR4_2017-4
	movl	%eax,RR4_2018-4
	movl	%eax,RR4_2019-4
	movl	%eax,RR4_2020-4
	movl	%eax,RR4_2021-4
	movl	%eax,RR4_2022-4
	movl	%eax,RR4_2023-4
	movl	%eax,RR4_2024-4
	movl	%eax,RR4_2025-4
	movl	%eax,RR4_2026-4
	movl	%eax,RR4_2027-4
	movl	%eax,RR4_2028-4
	incl	%eax
	incl	%eax
	movl	%eax,RR6_2000-4
	movl	%eax,RR6_2001-4
	movl	%eax,RR6_2002-4
	movl	%eax,RR6_2003-4
	movl	%eax,RR6_2004-4
	movl	%eax,RR6_2005-4
	movl	%eax,RR6_2006-4
	movl	%eax,RR6_2007-4
	movl	%eax,RR6_2008-4
	movl	%eax,RR6_2009-4
	movl	%eax,RR6_2010-4
	movl	%eax,RR6_2011-4
	movl	%eax,RR6_2012-4
	incl	%eax
	incl	%eax
	movl	%eax,RR8_2000-4
	movl	%eax,RR8_2001-4
	movl	%eax,RR8_2002-4
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
