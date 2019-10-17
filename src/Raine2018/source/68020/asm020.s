

FUNC(op_30)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,28-16(%esp)
	addl	$8,%eax
	movb	0x2164334A+3(%ecx),%cl
RR3_0000:
	movl	28-16(%esp),%edx
	movl	28-16(%esp),%edi
	movb	%cl,35-16(%esp)
	addl	$4,%edx
	addl	$6,%edi
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0000:
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
	jne	L_0_414
	movswl	16-16(%esp),%ecx
	movl	%ecx,16-16(%esp)
L_0_414:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_0_415
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_416
	movl	%ebp,%ebx
L_0_416:
	testl	$64,%esi
	je	L_0_417
	movl	%ebp,16-16(%esp)
L_0_417:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_418
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_0001:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_418:
	cmpl	$48,%edx
	jne	L_0_421
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_421:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_0_424
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_424:
	cmpl	$3,20-16(%esp)
	jne	L_0_427
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_427:
	andl	$4,%esi
	jne	L_0_430
	addl	16-16(%esp),%ebx
L_0_430:
	cmpl	$0,20-16(%esp)
	je	L_0_431
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_431:
	testl	%esi,%esi
	je	L_0_434
	addl	16-16(%esp),%ebx
L_0_434:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_435
	.align	2,0x90
L_0_415:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	16-16(%esp),%eax
L_0_435:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	%eax,20-16(%esp)
	andl	$1020,%edx
	movl	20-16(%esp),%edi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%edi,%eax),%al
	orb	%al,35-16(%esp)
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
	jl	JJ_0000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0000:
	ret

FUNC(op_70)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0000:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0006:
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
	jne	L_0_534
	movswl	%di,%edi
L_0_534:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_535
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_536
	movl	%ebp,%ebx
L_0_536:
	testl	$64,%esi
	je	L_0_537
	movl	%ebp,%edi
L_0_537:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_538
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0007:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_538:
	cmpl	$48,%edx
	jne	L_0_541
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0008:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_541:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_544
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0009:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_544:
	cmpl	$3,16-16(%esp)
	jne	L_0_547
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0010:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_547:
	andl	$4,%esi
	jne	L_0_550
	addl	%edi,%ebx
L_0_550:
	cmpl	$0,16-16(%esp)
	je	L_0_551
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_551:
	testl	%esi,%esi
	je	L_0_554
	addl	%edi,%ebx
L_0_554:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_555
	.align	2,0x90
L_0_535:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_555:
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
	orw	%ax,30-16(%esp)
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
	jl	JJ_0001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0001:
	ret

FUNC(op_b0)

	subl	$20,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_0001:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,32-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,28-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0012:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_670
	movswl	%di,%edi
L_0_670:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_671
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_672
	movl	20-16(%esp),%ebx
L_0_672:
	testl	$64,%esi
	je	L_0_673
	movl	20-16(%esp),%edi
L_0_673:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_674
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0013:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_0_674:
	cmpl	$48,%edx
	jne	L_0_677
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0014:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_677:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_0_680
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0015:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_0_680:
	cmpl	$3,%ebp
	jne	L_0_683
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0016:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_0_683:
	andl	$4,%esi
	jne	L_0_686
	addl	%edi,%ebx
L_0_686:
	testl	%ebp,%ebp
	je	L_0_687
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_687:
	testl	%esi,%esi
	je	L_0_690
	addl	%edi,%ebx
L_0_690:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_0_691
	.align	2,0x90
L_0_671:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	28-16(%esp),%eax
	addl	%edi,%eax
L_0_691:
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
	orl	%eax,32-16(%esp)
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
	jl	JJ_0002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0002:
	ret

FUNC(op_d0)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0002:
	rolw	$8,%ax
	movl	%eax,%edi
	shrw	$12,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	addl	$8,%edx
	movl	(%ecx,%eax,4),%ebx
	movl	(%ecx,%edx,4),%eax
	movb	2(%ecx,%edx,4),%dl
	movl	%eax,%ecx
	andl	$255,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(,%edx,4),%edx
	incl	%eax
	movsbl	(%ecx,%edx),%esi
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movsbl	(%eax,%edx),%ecx
	testw	%di,%di
	jl	L_0_735
	movsbl	%bl,%ebx
L_0_735:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_737
	cmpl	%ebx,%esi
	jne	L_0_736
L_0_737:
	movl	$1,%eax
L_0_736:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_738
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_743
	cmpl	%ecx,%ebx
	jle	L_0_739
	jmp	L_0_743
	.align	2,0x90
L_0_738:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_743
	cmpl	%esi,%ebx
	jge	L_0_739
L_0_743:
	movl	$1,%eax
L_0_739:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_744
	testb	$1,regflags
	je	L_0_744
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_745
	.align	2,0x90
L_0_744:
	addl	$4,GLOBL(regs)+88
L_0_745:
	popl	%eax
	decl	%eax
	jl	JJ_0003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0003:
	ret

FUNC(op_e8)

	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0003:
	rolw	$8,%ax
	movl	%eax,%edi
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebp),%dx
RR4_0000:
	rolw	$8,%dx
	movl	$GLOBL(regs),%ebx
	shrw	$12,%ax
	movswl	%dx,%edx
	cwtl
	addl	(%ebx,%ecx,4),%edx
	movl	(%ebx,%eax,4),%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	incl	%edx
	movsbl	(%ecx,%eax),%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ecx
	testw	%di,%di
	jl	L_0_752
	movsbl	%bl,%ebx
L_0_752:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_754
	cmpl	%ebx,%esi
	jne	L_0_753
L_0_754:
	movl	$1,%eax
L_0_753:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_755
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_760
	cmpl	%ecx,%ebx
	jle	L_0_756
	jmp	L_0_760
	.align	2,0x90
L_0_755:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_760
	cmpl	%esi,%ebx
	jge	L_0_756
L_0_760:
	movl	$1,%eax
L_0_756:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_761
	testb	$1,regflags
	je	L_0_761
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_762
	.align	2,0x90
L_0_761:
	addl	$6,GLOBL(regs)+88
L_0_762:
	popl	%eax
	decl	%eax
	jl	JJ_0004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0004:
	ret

FUNC(op_f0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0004:
	rolw	$8,%ax
	movw	%ax,24-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0020:
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
	jne	L_0_768
	movswl	%di,%edi
L_0_768:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_769
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_770
	movl	%ebp,%ebx
L_0_770:
	testl	$64,%esi
	je	L_0_771
	movl	%ebp,%edi
L_0_771:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_772
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0021:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_772:
	cmpl	$48,%edx
	jne	L_0_775
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0022:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_775:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_778
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0023:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_778:
	cmpl	$3,16-16(%esp)
	jne	L_0_781
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0024:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_781:
	andl	$4,%esi
	jne	L_0_784
	addl	%edi,%ebx
L_0_784:
	cmpl	$0,16-16(%esp)
	je	L_0_785
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_785:
	testl	%esi,%esi
	je	L_0_788
	addl	%edi,%ebx
L_0_788:
	addl	%ebp,%ebx
	jmp	L_0_789
	.align	2,0x90
L_0_769:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_0_789:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%edi
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%esi
	leal	1(%ebx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ebx
	cmpw	$0,24-16(%esp)
	jl	L_0_793
	movl	%edi,%ecx
	movsbl	%cl,%edi
L_0_793:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	je	L_0_795
	cmpl	%edi,%esi
	jne	L_0_794
L_0_795:
	movl	$1,%eax
L_0_794:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ebx,%esi
	jg	L_0_796
	xorl	%eax,%eax
	cmpl	%esi,%edi
	jl	L_0_801
	cmpl	%ebx,%edi
	jle	L_0_797
	jmp	L_0_801
	.align	2,0x90
L_0_796:
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	jg	L_0_801
	cmpl	%esi,%edi
	jge	L_0_797
L_0_801:
	movl	$1,%eax
L_0_797:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_0_803
	testb	$1,regflags
	je	L_0_803
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_0_803:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0005:
	ret

FUNC(op_f8)

	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0005:
	rolw	$8,%ax
	movl	%eax,%edi
	shrw	$12,%ax
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebp),%dx
RR4_0001:
	rolw	$8,%dx
	cwtl
	movswl	%dx,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	incl	%edx
	movsbl	(%ecx,%eax),%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ecx
	testw	%di,%di
	jl	L_0_810
	movsbl	%bl,%ebx
L_0_810:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_812
	cmpl	%ebx,%esi
	jne	L_0_811
L_0_812:
	movl	$1,%eax
L_0_811:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_813
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_818
	cmpl	%ecx,%ebx
	jle	L_0_814
	jmp	L_0_818
	.align	2,0x90
L_0_813:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_818
	cmpl	%esi,%ebx
	jge	L_0_814
L_0_818:
	movl	$1,%eax
L_0_814:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_819
	testb	$1,regflags
	je	L_0_819
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_820
	.align	2,0x90
L_0_819:
	addl	$6,GLOBL(regs)+88
L_0_820:
	popl	%eax
	decl	%eax
	jl	JJ_0006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0026:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0006:
	ret

FUNC(op_f9)

	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0006:
	rolw	$8,%ax
	movl	%eax,%edi
	shrw	$12,%ax
	movl	0x2164334A+4(%ebp),%edx
RR4_0002:
	cwtl
	bswapl	%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	incl	%edx
	movsbl	(%ecx,%eax),%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ecx
	testw	%di,%di
	jl	L_0_827
	movsbl	%bl,%ebx
L_0_827:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_829
	cmpl	%ebx,%esi
	jne	L_0_828
L_0_829:
	movl	$1,%eax
L_0_828:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_830
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_835
	cmpl	%ecx,%ebx
	jle	L_0_831
	jmp	L_0_835
	.align	2,0x90
L_0_830:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_835
	cmpl	%esi,%ebx
	jge	L_0_831
L_0_835:
	movl	$1,%eax
L_0_831:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_836
	testb	$1,regflags
	je	L_0_836
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_837
	.align	2,0x90
L_0_836:
	addl	$8,GLOBL(regs)+88
L_0_837:
	popl	%eax
	decl	%eax
	jl	JJ_0007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0027:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0007:
	ret

FUNC(op_fa)

	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_0007:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%edi),%ax
RR4_0003:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edi),%edx
	movl	%ebp,%eax
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	incl	%edx
	movsbl	(%ecx,%eax),%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ecx
	testw	%bp,%bp
	jl	L_0_845
	movsbl	%bl,%ebx
L_0_845:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_847
	cmpl	%ebx,%esi
	jne	L_0_846
L_0_847:
	movl	$1,%eax
L_0_846:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_848
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_853
	cmpl	%ecx,%ebx
	jle	L_0_849
	jmp	L_0_853
	.align	2,0x90
L_0_848:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_853
	cmpl	%esi,%ebx
	jge	L_0_849
L_0_853:
	movl	$1,%eax
L_0_849:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_0_854
	testb	$1,regflags
	je	L_0_854
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_855
	.align	2,0x90
L_0_854:
	addl	$6,GLOBL(regs)+88
L_0_855:
	popl	%eax
	decl	%eax
	jl	JJ_0008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0028:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0008:
	ret

FUNC(op_fb)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0008:
	rolw	$8,%ax
	movl	%ecx,%edx
	movw	%ax,24-16(%esp)
	addl	$4,%edx
	addl	$6,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0029:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_862
	movswl	%di,%edi
L_0_862:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_863
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_864
	movl	%ebp,%ebx
L_0_864:
	testl	$64,%esi
	je	L_0_865
	movl	%ebp,%edi
L_0_865:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_866
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0030:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_866:
	cmpl	$48,%edx
	jne	L_0_869
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0031:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_869:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_872
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0032:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_872:
	cmpl	$3,16-16(%esp)
	jne	L_0_875
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0033:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_875:
	andl	$4,%esi
	jne	L_0_878
	addl	%edi,%ebx
L_0_878:
	cmpl	$0,16-16(%esp)
	je	L_0_879
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_879:
	testl	%esi,%esi
	je	L_0_882
	addl	%edi,%ebx
L_0_882:
	addl	%ebp,%ebx
	jmp	L_0_883
	.align	2,0x90
L_0_863:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_0_883:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	cwtl
	movl	GLOBL(regs)(,%eax,4),%edi
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%esi
	leal	1(%ebx),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movsbl	(%edx,%eax),%ebx
	cmpw	$0,24-16(%esp)
	jl	L_0_887
	movl	%edi,%ecx
	movsbl	%cl,%edi
L_0_887:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	je	L_0_889
	cmpl	%edi,%esi
	jne	L_0_888
L_0_889:
	movl	$1,%eax
L_0_888:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ebx,%esi
	jg	L_0_890
	xorl	%eax,%eax
	cmpl	%esi,%edi
	jl	L_0_895
	cmpl	%ebx,%edi
	jle	L_0_891
	jmp	L_0_895
	.align	2,0x90
L_0_890:
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	jg	L_0_895
	cmpl	%esi,%edi
	jge	L_0_891
L_0_895:
	movl	$1,%eax
L_0_891:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_0_897
	testb	$1,regflags
	je	L_0_897
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_0_897:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0034:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0009:
	ret

FUNC(op_130)

	subl	$16,%esp
	movl	%eax,%edx
	pushl	%ebp
	pushl	%edi
	shrl	$7,%eax
	pushl	%esi
	andl	$28,%eax
	pushl	%ebx
	andl	$7,%edx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0035:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,20(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_941
	movswl	%di,%edi
L_0_941:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_942
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_943
	movl	%ebp,%ebx
L_0_943:
	testl	$64,%esi
	je	L_0_944
	movl	%ebp,%edi
L_0_944:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_945
	movl	20(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0036:
	rolw	$8,%ax
	movl	24(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_945:
	cmpl	$48,%edx
	jne	L_0_948
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0037:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_948:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16(%esp)
	cmpl	$2,%ecx
	jne	L_0_951
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0038:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_951:
	cmpl	$3,16(%esp)
	jne	L_0_954
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0039:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_954:
	andl	$4,%esi
	jne	L_0_957
	addl	%edi,%ebx
L_0_957:
	cmpl	$0,16(%esp)
	je	L_0_958
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_958:
	testl	%esi,%esi
	je	L_0_961
	addl	%edi,%ebx
L_0_961:
	leal	(%ebp,%ebx),%edx
	jmp	L_0_962
	.align	2,0x90
L_0_942:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_0_962:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movb	28(%esp),%cl
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	popl	%ebx
	xorb	$1,%al
	popl	%esi
	movb	%al,%dl
	popl	%edi
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	popl	%ebp
	orb	%dl,%al
	addl	$16,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0040:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0010:
	ret

FUNC(op_13b)

	subl	$16,%esp
	shrl	$7,%eax
	pushl	%esi
	andl	$28,%eax
	pushl	%ebx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-8(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-8(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0041:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-8(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_996
	movswl	%di,%edi
L_0_996:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_997
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_998
	movl	%ebp,%ebx
L_0_998:
	testl	$64,%esi
	je	L_0_999
	movl	%ebp,%edi
L_0_999:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1000
	movl	20-8(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0042:
	rolw	$8,%ax
	movl	24-8(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1000:
	cmpl	$48,%edx
	jne	L_0_1003
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0043:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1003:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-8(%esp)
	cmpl	$2,%ecx
	jne	L_0_1006
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0044:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1006:
	cmpl	$3,16-8(%esp)
	jne	L_0_1009
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0045:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1009:
	andl	$4,%esi
	jne	L_0_1012
	addl	%edi,%ebx
L_0_1012:
	cmpl	$0,16-8(%esp)
	je	L_0_1013
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1013:
	testl	%esi,%esi
	je	L_0_1016
	addl	%edi,%ebx
L_0_1016:
	leal	(%ebp,%ebx),%edx
	jmp	L_0_1017
	.align	2,0x90
L_0_997:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_0_1017:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movb	28-8(%esp),%cl
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movsbl	(%edx,%eax),%eax
	sarl	%cl,%eax
	popl	%ebx
	xorb	$1,%al
	popl	%esi
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
	jl	JJ_0011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0046:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0011:
	ret

FUNC(op_170)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0047:
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
	jne	L_0_1080
	movswl	%di,%edi
L_0_1080:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1081
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1082
	movl	%ebp,%ebx
L_0_1082:
	testl	$64,%esi
	je	L_0_1083
	movl	%ebp,%edi
L_0_1083:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1084
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0048:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1084:
	cmpl	$48,%edx
	jne	L_0_1087
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0049:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1087:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1090
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0050:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1090:
	cmpl	$3,16-16(%esp)
	jne	L_0_1093
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0051:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1093:
	andl	$4,%esi
	jne	L_0_1096
	addl	%edi,%ebx
L_0_1096:
	cmpl	$0,16-16(%esp)
	je	L_0_1097
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1097:
	testl	%esi,%esi
	je	L_0_1100
	addl	%edi,%ebx
L_0_1100:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1101
	.align	2,0x90
L_0_1081:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1101:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0012:
	ret

FUNC(op_17b)

	subl	$16,%esp
	shrl	$7,%eax
	andl	$28,%eax
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0053:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_1142
	movswl	%di,%edi
L_0_1142:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1143
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1144
	movl	%ebp,%ebx
L_0_1144:
	testl	$64,%esi
	je	L_0_1145
	movl	%ebp,%edi
L_0_1145:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1146
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0054:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1146:
	cmpl	$48,%edx
	jne	L_0_1149
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0055:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1149:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1152
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0056:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1152:
	cmpl	$3,16-16(%esp)
	jne	L_0_1155
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0057:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1155:
	andl	$4,%esi
	jne	L_0_1158
	addl	%edi,%ebx
L_0_1158:
	cmpl	$0,16-16(%esp)
	je	L_0_1159
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1159:
	testl	%esi,%esi
	je	L_0_1162
	addl	%edi,%ebx
L_0_1162:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1163
	.align	2,0x90
L_0_1143:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1163:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0013:
	ret

FUNC(op_1b0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0059:
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
	jne	L_0_1219
	movswl	%di,%edi
L_0_1219:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1220
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1221
	movl	%ebp,%ebx
L_0_1221:
	testl	$64,%esi
	je	L_0_1222
	movl	%ebp,%edi
L_0_1222:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1223
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0060:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1223:
	cmpl	$48,%edx
	jne	L_0_1226
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0061:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1226:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1229
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0062:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1229:
	cmpl	$3,16-16(%esp)
	jne	L_0_1232
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0063:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1232:
	andl	$4,%esi
	jne	L_0_1235
	addl	%edi,%ebx
L_0_1235:
	cmpl	$0,16-16(%esp)
	je	L_0_1236
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1236:
	testl	%esi,%esi
	je	L_0_1239
	addl	%edi,%ebx
L_0_1239:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1240
	.align	2,0x90
L_0_1220:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1240:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	16-16(%esp),%dl
	movb	%dl,(%esi,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0014:
	ret

FUNC(op_1bb)

	subl	$16,%esp
	shrl	$7,%eax
	andl	$28,%eax
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0065:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_1281
	movswl	%di,%edi
L_0_1281:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1282
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1283
	movl	%ebp,%ebx
L_0_1283:
	testl	$64,%esi
	je	L_0_1284
	movl	%ebp,%edi
L_0_1284:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1285
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0066:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1285:
	cmpl	$48,%edx
	jne	L_0_1288
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0067:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1288:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1291
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0068:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1291:
	cmpl	$3,16-16(%esp)
	jne	L_0_1294
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0069:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1294:
	andl	$4,%esi
	jne	L_0_1297
	addl	%edi,%ebx
L_0_1297:
	cmpl	$0,16-16(%esp)
	je	L_0_1298
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1298:
	testl	%esi,%esi
	je	L_0_1301
	addl	%edi,%ebx
L_0_1301:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1302
	.align	2,0x90
L_0_1282:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1302:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	16-16(%esp),%dl
	movb	%dl,(%esi,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0070:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0015:
	ret

FUNC(op_1f0)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0071:
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
	jne	L_0_1362
	movswl	%di,%edi
L_0_1362:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1363
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1364
	movl	%ebp,%ebx
L_0_1364:
	testl	$64,%esi
	je	L_0_1365
	movl	%ebp,%edi
L_0_1365:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1366
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0072:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1366:
	cmpl	$48,%edx
	jne	L_0_1369
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0073:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1369:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1372
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0074:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1372:
	cmpl	$3,16-16(%esp)
	jne	L_0_1375
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0075:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1375:
	andl	$4,%esi
	jne	L_0_1378
	addl	%edi,%ebx
L_0_1378:
	cmpl	$0,16-16(%esp)
	je	L_0_1379
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1379:
	testl	%esi,%esi
	je	L_0_1382
	addl	%edi,%ebx
L_0_1382:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1383
	.align	2,0x90
L_0_1363:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1383:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0016:
	ret

FUNC(op_1fb)

	subl	$16,%esp
	shrl	$7,%eax
	andl	$28,%eax
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,28-16(%esp)
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0077:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_1424
	movswl	%di,%edi
L_0_1424:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1425
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1426
	movl	%ebp,%ebx
L_0_1426:
	testl	$64,%esi
	je	L_0_1427
	movl	%ebp,%edi
L_0_1427:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1428
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0078:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1428:
	cmpl	$48,%edx
	jne	L_0_1431
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0079:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1431:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1434
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0080:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1434:
	cmpl	$3,16-16(%esp)
	jne	L_0_1437
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0081:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1437:
	andl	$4,%esi
	jne	L_0_1440
	addl	%edi,%ebx
L_0_1440:
	cmpl	$0,16-16(%esp)
	je	L_0_1441
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1441:
	testl	%esi,%esi
	je	L_0_1444
	addl	%edi,%ebx
L_0_1444:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1445
	.align	2,0x90
L_0_1425:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1445:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	movb	(%esi,%eax),%al
	movb	28-16(%esp),%cl
	movb	%al,16-16(%esp)
	andl	$7,%ecx
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
	movl	%ecx,%edi
	sall	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%esi,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0017:
	ret

FUNC(op_230)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%eax
	movl	%ecx,28-16(%esp)
	addl	$8,%eax
	movb	0x2164334A+3(%ecx),%cl
RR3_0001:
	movl	28-16(%esp),%edx
	movl	28-16(%esp),%edi
	movb	%cl,35-16(%esp)
	addl	$4,%edx
	addl	$6,%edi
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0083:
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
	jne	L_0_1491
	movswl	16-16(%esp),%ecx
	movl	%ecx,16-16(%esp)
L_0_1491:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_0_1492
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1493
	movl	%ebp,%ebx
L_0_1493:
	testl	$64,%esi
	je	L_0_1494
	movl	%ebp,16-16(%esp)
L_0_1494:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1495
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_0084:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1495:
	cmpl	$48,%edx
	jne	L_0_1498
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0085:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1498:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_0_1501
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0086:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1501:
	cmpl	$3,20-16(%esp)
	jne	L_0_1504
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0087:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1504:
	andl	$4,%esi
	jne	L_0_1507
	addl	16-16(%esp),%ebx
L_0_1507:
	cmpl	$0,20-16(%esp)
	je	L_0_1508
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1508:
	testl	%esi,%esi
	je	L_0_1511
	addl	16-16(%esp),%ebx
L_0_1511:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1512
	.align	2,0x90
L_0_1492:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	16-16(%esp),%eax
L_0_1512:
	movl	%eax,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	%eax,20-16(%esp)
	andl	$1020,%edx
	movl	20-16(%esp),%edi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%edi,%eax),%al
	andb	%al,35-16(%esp)
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
	jl	JJ_0018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0018:
	ret

FUNC(op_270)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0009:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0089:
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
	jne	L_0_1611
	movswl	%di,%edi
L_0_1611:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1612
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1613
	movl	%ebp,%ebx
L_0_1613:
	testl	$64,%esi
	je	L_0_1614
	movl	%ebp,%edi
L_0_1614:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1615
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0090:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1615:
	cmpl	$48,%edx
	jne	L_0_1618
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0091:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1618:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1621
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0092:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1621:
	cmpl	$3,16-16(%esp)
	jne	L_0_1624
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0093:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1624:
	andl	$4,%esi
	jne	L_0_1627
	addl	%edi,%ebx
L_0_1627:
	cmpl	$0,16-16(%esp)
	je	L_0_1628
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1628:
	testl	%esi,%esi
	je	L_0_1631
	addl	%edi,%ebx
L_0_1631:
	leal	(%ebp,%ebx),%eax
	jmp	L_0_1632
	.align	2,0x90
L_0_1612:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_0_1632:
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
	andw	%ax,30-16(%esp)
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
	jl	JJ_0019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0019:
	ret

FUNC(op_2b0)

	subl	$20,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebp
	addl	$8,%eax
	movl	0x2164334A+2(%ebp),%ecx
RR2_0010:
	bswapl	%ecx
	leal	6(%ebp),%edx
	movl	%ecx,32-16(%esp)
	movl	%edx,GLOBL(regs)+88
	movl	GLOBL(regs)(,%eax,4),%eax
	leal	8(%ebp),%ecx
	movl	%eax,28-16(%esp)
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0095:
	rolw	$8,%si
	movl	%eax,%ebx
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_1747
	movswl	%di,%edi
L_0_1747:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1748
	movl	$0,20-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1749
	movl	20-16(%esp),%ebx
L_0_1749:
	testl	$64,%esi
	je	L_0_1750
	movl	20-16(%esp),%edi
L_0_1750:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1751
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0096:
	rolw	$8,%ax
	addl	$10,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_0_1751:
	cmpl	$48,%edx
	jne	L_0_1754
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0097:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1754:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_0_1757
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0098:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_0_1757:
	cmpl	$3,%ebp
	jne	L_0_1760
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0099:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_0_1760:
	andl	$4,%esi
	jne	L_0_1763
	addl	%edi,%ebx
L_0_1763:
	testl	%ebp,%ebp
	je	L_0_1764
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1764:
	testl	%esi,%esi
	je	L_0_1767
	addl	%edi,%ebx
L_0_1767:
	movl	20-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_0_1768
	.align	2,0x90
L_0_1748:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	28-16(%esp),%eax
	addl	%edi,%eax
L_0_1768:
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
	andl	%eax,32-16(%esp)
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
	jl	JJ_0020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0020:
	ret

FUNC(op_2d0)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0011:
	rolw	$8,%ax
	movw	%ax,16-16(%esp)
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
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$2,%edx
	movswl	%ax,%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movswl	%ax,%ecx
	cmpw	$0,16-16(%esp)
	jl	L_0_1814
	movswl	%si,%esi
L_0_1814:
	xorl	%eax,%eax
	cmpl	%esi,%ecx
	je	L_0_1816
	cmpl	%esi,%ebx
	jne	L_0_1815
L_0_1816:
	movl	$1,%eax
L_0_1815:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%ebx
	jg	L_0_1817
	xorl	%eax,%eax
	cmpl	%ebx,%esi
	jl	L_0_1822
	cmpl	%ecx,%esi
	jle	L_0_1818
	jmp	L_0_1822
	.align	2,0x90
L_0_1817:
	xorl	%eax,%eax
	cmpl	%ecx,%esi
	jg	L_0_1822
	cmpl	%ebx,%esi
	jge	L_0_1818
L_0_1822:
	movl	$1,%eax
L_0_1818:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	16-16(%esp),%edi
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_1823
	testb	$1,regflags
	je	L_0_1823
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_1824
	.align	2,0x90
L_0_1823:
	addl	$4,GLOBL(regs)+88
L_0_1824:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0021:
	ret

FUNC(op_2e8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0012:
	rolw	$8,%ax
	movw	%ax,16-16(%esp)
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%ebp),%cx
RR4_0004:
	rolw	$8,%cx
	movl	$GLOBL(regs),%ebx
	movswl	%cx,%ecx
	shrw	$12,%ax
	addl	(%ebx,%edx,4),%ecx
	cwtl
	movl	%ecx,%edx
	movl	(%ebx,%eax,4),%ebx
	shrl	$14,%edx
	movl	%ecx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$2,%ecx
	movswl	%ax,%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movw	(%ecx),%ax
	rolw	$8,%ax
	movswl	%ax,%ecx
	cmpw	$0,16-16(%esp)
	jl	L_0_1833
	movswl	%bx,%ebx
L_0_1833:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_1835
	cmpl	%ebx,%esi
	jne	L_0_1834
L_0_1835:
	movl	$1,%eax
L_0_1834:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_1836
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_1841
	cmpl	%ecx,%ebx
	jle	L_0_1837
	jmp	L_0_1841
	.align	2,0x90
L_0_1836:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_1841
	cmpl	%esi,%ebx
	jge	L_0_1837
L_0_1841:
	movl	$1,%eax
L_0_1837:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	16-16(%esp),%edi
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_1842
	testb	$1,regflags
	je	L_0_1842
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_1843
	.align	2,0x90
L_0_1842:
	addl	$6,GLOBL(regs)+88
L_0_1843:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0022:
	ret

FUNC(op_2f0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0013:
	rolw	$8,%ax
	movw	%ax,24-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_0103:
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
	jne	L_0_1849
	movswl	%di,%edi
L_0_1849:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1850
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1851
	movl	%ebp,%ebx
L_0_1851:
	testl	$64,%esi
	je	L_0_1852
	movl	%ebp,%edi
L_0_1852:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1853
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0104:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1853:
	cmpl	$48,%edx
	jne	L_0_1856
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0105:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1856:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1859
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0106:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1859:
	cmpl	$3,16-16(%esp)
	jne	L_0_1862
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0107:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1862:
	andl	$4,%esi
	jne	L_0_1865
	addl	%edi,%ebx
L_0_1865:
	cmpl	$0,16-16(%esp)
	je	L_0_1866
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1866:
	testl	%esi,%esi
	je	L_0_1869
	addl	%edi,%ebx
L_0_1869:
	addl	%ebp,%ebx
	jmp	L_0_1870
	.align	2,0x90
L_0_1850:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_0_1870:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	movl	%ebx,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%edi
	movl	%ebx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%esi
	leal	2(%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%ebx
	cmpw	$0,24-16(%esp)
	jl	L_0_1876
	movswl	%di,%edi
L_0_1876:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	je	L_0_1878
	cmpl	%edi,%esi
	jne	L_0_1877
L_0_1878:
	movl	$1,%eax
L_0_1877:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ebx,%esi
	jg	L_0_1879
	xorl	%eax,%eax
	cmpl	%esi,%edi
	jl	L_0_1884
	cmpl	%ebx,%edi
	jle	L_0_1880
	jmp	L_0_1884
	.align	2,0x90
L_0_1879:
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	jg	L_0_1884
	cmpl	%esi,%edi
	jge	L_0_1880
L_0_1884:
	movl	$1,%eax
L_0_1880:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_0_1886
	testb	$1,regflags
	je	L_0_1886
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_0_1886:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0023:
	ret

FUNC(op_2f8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0014:
	rolw	$8,%ax
	movw	%ax,16-16(%esp)
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%ebp),%cx
RR4_0005:
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
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$2,%ecx
	movswl	%ax,%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movw	(%ecx),%ax
	rolw	$8,%ax
	movswl	%ax,%ecx
	cmpw	$0,16-16(%esp)
	jl	L_0_1895
	movswl	%bx,%ebx
L_0_1895:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_1897
	cmpl	%ebx,%esi
	jne	L_0_1896
L_0_1897:
	movl	$1,%eax
L_0_1896:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_1898
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_1903
	cmpl	%ecx,%ebx
	jle	L_0_1899
	jmp	L_0_1903
	.align	2,0x90
L_0_1898:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_1903
	cmpl	%esi,%ebx
	jge	L_0_1899
L_0_1903:
	movl	$1,%eax
L_0_1899:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	16-16(%esp),%edi
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_1904
	testb	$1,regflags
	je	L_0_1904
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_1905
	.align	2,0x90
L_0_1904:
	addl	$6,GLOBL(regs)+88
L_0_1905:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0024:
	ret

FUNC(op_2f9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_0015:
	rolw	$8,%ax
	movw	%ax,16-16(%esp)
	movl	0x2164334A+4(%ebp),%ecx
RR4_0006:
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
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	addl	$2,%ecx
	movswl	%ax,%esi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movw	(%ecx),%ax
	rolw	$8,%ax
	movswl	%ax,%ecx
	cmpw	$0,16-16(%esp)
	jl	L_0_1914
	movswl	%bx,%ebx
L_0_1914:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_1916
	cmpl	%ebx,%esi
	jne	L_0_1915
L_0_1916:
	movl	$1,%eax
L_0_1915:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,%esi
	jg	L_0_1917
	xorl	%eax,%eax
	cmpl	%esi,%ebx
	jl	L_0_1922
	cmpl	%ecx,%ebx
	jle	L_0_1918
	jmp	L_0_1922
	.align	2,0x90
L_0_1917:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_1922
	cmpl	%esi,%ebx
	jge	L_0_1918
L_0_1922:
	movl	$1,%eax
L_0_1918:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	16-16(%esp),%edi
	movb	%al,regflags
	testl	$2048,%edi
	je	L_0_1923
	testb	$1,regflags
	je	L_0_1923
	pushl	%ebp
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_1924
	.align	2,0x90
L_0_1923:
	addl	$8,GLOBL(regs)+88
L_0_1924:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0025:
	ret

FUNC(op_2fa)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%edi
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_0016:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%edi),%ax
RR4_0007:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edi),%ecx
	movl	%ebp,%eax
	shrw	$12,%ax
	movl	%ecx,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	%ecx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	addl	$2,%ecx
	movl	%eax,16-16(%esp)
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$65535,%ecx
	andl	$1020,%eax
	addl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movw	(%ecx),%ax
	rolw	$8,%ax
	movswl	%ax,%ecx
	testw	%bp,%bp
	jl	L_0_1934
	movswl	%bx,%ebx
L_0_1934:
	xorl	%eax,%eax
	cmpl	%ebx,%ecx
	je	L_0_1936
	cmpl	%ebx,16-16(%esp)
	jne	L_0_1935
L_0_1936:
	movl	$1,%eax
L_0_1935:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ecx,16-16(%esp)
	jg	L_0_1937
	xorl	%eax,%eax
	cmpl	%ebx,16-16(%esp)
	jg	L_0_1942
	cmpl	%ecx,%ebx
	jle	L_0_1938
	jmp	L_0_1942
	.align	2,0x90
L_0_1937:
	xorl	%eax,%eax
	cmpl	%ecx,%ebx
	jg	L_0_1942
	cmpl	%ebx,16-16(%esp)
	jle	L_0_1938
L_0_1942:
	movl	$1,%eax
L_0_1938:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	testl	$2048,%ebp
	je	L_0_1943
	testb	$1,regflags
	je	L_0_1943
	pushl	%edi
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_0_1944
	.align	2,0x90
L_0_1943:
	addl	$6,GLOBL(regs)+88
L_0_1944:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0026:
	ret

FUNC(op_2fb)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0017:
	rolw	$8,%ax
	movl	%ecx,%edx
	movw	%ax,24-16(%esp)
	addl	$4,%edx
	addl	$6,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_0112:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_0_1951
	movswl	%di,%edi
L_0_1951:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_0_1952
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_0_1953
	movl	%ebp,%ebx
L_0_1953:
	testl	$64,%esi
	je	L_0_1954
	movl	%ebp,%edi
L_0_1954:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_0_1955
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_0113:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_0_1955:
	cmpl	$48,%edx
	jne	L_0_1958
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0114:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_0_1958:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_0_1961
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_0115:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1961:
	cmpl	$3,16-16(%esp)
	jne	L_0_1964
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_0116:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_0_1964:
	andl	$4,%esi
	jne	L_0_1967
	addl	%edi,%ebx
L_0_1967:
	cmpl	$0,16-16(%esp)
	je	L_0_1968
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_0_1968:
	testl	%esi,%esi
	je	L_0_1971
	addl	%edi,%ebx
L_0_1971:
	addl	%ebp,%ebx
	jmp	L_0_1972
	.align	2,0x90
L_0_1952:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_0_1972:
	movl	24-16(%esp),%eax
	shrw	$12,%ax
	movl	%ebx,%edx
	cwtl
	shrl	$14,%edx
	movl	GLOBL(regs)(,%eax,4),%edi
	movl	%ebx,%eax
	andl	$1020,%edx
	andl	$65535,%eax
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%esi
	leal	2(%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%ebx
	cmpw	$0,24-16(%esp)
	jl	L_0_1978
	movswl	%di,%edi
L_0_1978:
	xorl	%eax,%eax
	cmpl	%edi,%ebx
	je	L_0_1980
	cmpl	%edi,%esi
	jne	L_0_1979
L_0_1980:
	movl	$1,%eax
L_0_1979:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	movb	%al,regflags
	cmpl	%ebx,%esi
	jg	L_0_1981
	xorl	%eax,%eax
	cmpl	%esi,%edi
	jl	L_0_1986
	cmpl	%ebx,%edi
	jle	L_0_1982
	jmp	L_0_1986
	.align	2,0x90
L_0_1981:
	xorl	%eax,%eax
	cmpl	%ebx,%edi
	jg	L_0_1986
	cmpl	%esi,%edi
	jge	L_0_1982
L_0_1986:
	movl	$1,%eax
L_0_1982:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	testb	$8,%ch
	je	L_0_1988
	testb	$1,regflags
	je	L_0_1988
	movl	28-16(%esp),%ecx
	pushl	%ecx
	pushl	$6
	call	GLOBL(Exception)
	addl	$8,%esp
L_0_1988:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0027:
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


FUNC(op_illegal_jedi)

	pushl	%eax
	call	GLOBL(op_illg)
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0028:
	ret

FUNC(op_0)

	movl	%eax,%ecx
	movl	$GLOBL(regs),%edx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	sall	$2,%ecx
	movb	0x2164334A+3(%eax),%al
RR3_0002:
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0029:
	ret

FUNC(op_10)

	andl	$7,%eax
	xorl	%edx,%edx
	xorl	%ecx,%ecx
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_0003:
	movl	GLOBL(R24)(%edx),%eax
	orb	(%ecx,%eax),%bl
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
	jl	JJ_0030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0030:
	ret

FUNC(op_18)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	leal	8(%ebp),%ebx
	movb	0x2164334A+3(%eax),%al
RR3_0004:
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
	orb	%al,19-16(%esp)
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
	jl	JJ_0031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0031:
	ret

FUNC(op_20)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%edi
	movb	0x2164334A+3(%eax),%al
RR3_0005:
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
	orb	%al,19-12(%esp)
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
	jl	JJ_0032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0032:
	ret

FUNC(op_28)

	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_0008:
	rolw	$8,%dx
	addl	$8,%eax
	movswl	%dx,%edx
	addl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_0006:
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	orb	(%edx,%eax),%bl
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
	jl	JJ_0033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0033:
	ret

FUNC(op_38)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_0009:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_0007:
	movl	GLOBL(R24)(%ecx),%eax
	orb	(%edx,%eax),%bl
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
	jl	JJ_0034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0034:
	ret

FUNC(op_39)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+4(%ebx),%ecx
RR4_0010:
	bswapl	%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_0008:
	movl	GLOBL(R24)(%edx),%eax
	orb	(%ecx,%eax),%bl
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
	jl	JJ_0035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0035:
	ret

FUNC(op_3c)

	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0018:
	rolw	$8,%dx
	movl	%edx,%eax
	movb	$0,%ah
	orw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0036:
	ret

FUNC(op_40)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_0019:
	rolw	$8,%si
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%eax,%edx
	movl	$GLOBL(regs),%eax
	orw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0037:
	ret

FUNC(op_50)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_0020:
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
	orl	%eax,%ebx
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
	jl	JJ_0038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0038:
	ret

FUNC(op_58)

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
RR2_0021:
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
	orl	%eax,%edi
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
	jl	JJ_0039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0039:
	ret

FUNC(op_60)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	$GLOBL(regs),%ebp
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0022:
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
	orl	%eax,%edi
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
	jl	JJ_0040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0040:
	ret

FUNC(op_68)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0023:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_0011:
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
	orl	%edx,%ebx
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
	jl	JJ_0041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0041:
	ret

FUNC(op_78)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_0024:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_0012:
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
	orl	%edx,%ebx
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
	jl	JJ_0042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0042:
	ret

FUNC(op_79)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_0025:
	rolw	$8,%ax
	movl	%eax,%ebx
	movl	0x2164334A+4(%edx),%eax
RR4_0013:
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
	orl	%edx,%ebx
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
	jl	JJ_0043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0043:
	ret

FUNC(op_7c)

	cmpb	$0,GLOBL(regs)+80
	jne	L_0_595
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0044:
	ret
	.align	2,0x90
L_0_595:
	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0026:
	rolw	$8,%dx
	movl	%edx,%eax
	orw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0045:
	ret

FUNC(op_80)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_0027:
	sall	$2,%edx
	bswapl	%eax
	orl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0046:
	ret

FUNC(op_90)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_0028:
	movb	GLOBL(regs)+2(,%edx,4),%cl
	bswapl	%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	orl	%eax,%ebx
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
	jl	JJ_0047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0047:
	ret

FUNC(op_98)

	movl	$GLOBL(regs),%ebp
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	addl	$8,%esi
	movl	0x2164334A+2(%eax),%edi
RR2_0029:
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
	orl	%eax,%edi
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
	jl	JJ_0048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0048:
	ret

FUNC(op_a0)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%ebp
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%ebp),%ecx
	movl	GLOBL(regs)+88,%eax
	addl	$-4,%ecx
	movl	0x2164334A+2(%eax),%edi
RR2_0030:
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
	orl	%eax,%edi
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
	jl	JJ_0049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0049:
	ret

FUNC(op_a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_0000:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_0031:
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
	orl	%edx,%ebx
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
	jl	JJ_0050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0050:
	ret

FUNC(op_b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_0001:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_0032:
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
	orl	%edx,%ebx
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
	jl	JJ_0051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0051:
	ret

FUNC(op_b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_0033:
	movl	0x2164334A+6(%eax),%eax
RR6_0002:
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
	orl	%edx,%ebx
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
	jl	JJ_0052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0052:
	ret

FUNC(op_100)

	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	GLOBL(regs)(%eax),%ecx
	andl	$7,%edx
	andl	$31,%ecx
	movl	GLOBL(regs)(,%edx,4),%eax
	sarl	%cl,%eax
	xorb	$1,%al
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	orb	%dl,%al
	addl	$2,GLOBL(regs)+88
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0053:
	ret

FUNC(op_108)

	movl	%eax,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	movl	%eax,%esi
	pushl	%ebx
	shrl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ebx
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0034:
	rolw	$8,%dx
	addl	(%ebx,%ecx,4),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ebp
	andl	$1020,%eax
	addl	$2,%edx
	movl	GLOBL(R24)(%eax),%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%ebp
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%ecx
	xorl	%eax,%eax
	movb	(%ebp,%edi),%al
	movb	(%edx,%ecx),%dl
	salw	$8,%ax
	movb	$0,%dh
	andl	$28,%esi
	orl	%edx,%eax
	movw	%ax,(%esi,%ebx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0054:
	ret

FUNC(op_110)

	movl	%eax,%edx
	andl	$7,%eax
	xorl	%ecx,%ecx
	pushl	%ebx
	shrl	$7,%edx
	movl	$GLOBL(regs),%esi
	addl	$8,%eax
	andl	$28,%edx
	movb	2(%esi,%eax,4),%cl
	xorl	%ebx,%ebx
	movw	(%esi,%eax,4),%bx
	movb	(%edx,%esi),%al
	movl	GLOBL(R24)(,%ecx,4),%ecx
	andb	$7,%al
	movsbl	(%ebx,%ecx),%edx
	movsbl	%al,%ecx
	sarl	%cl,%edx
	addl	$2,GLOBL(regs)+88
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	popl	%ebx
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0055:
	ret

FUNC(op_118)

	subl	$4,%esp
	movl	%eax,%edx
	pushl	%edi
	pushl	%esi
	shrl	$7,%eax
	movl	%edx,%edi
	pushl	%ebx
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edi
	movb	(%eax,%esi),%al
	leal	8(%edi),%ecx
	movb	%al,12(%esp)
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%eax,%eax
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	movb	12(%esp),%cl
	movsbl	%al,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	addl	$2,GLOBL(regs)+88
	xorb	$1,%al
	popl	%ebx
	movb	%al,%dl
	popl	%esi
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	popl	%edi
	orb	%dl,%al
	addl	$4,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0056:
	ret

FUNC(op_120)

	subl	$4,%esp
	movl	%eax,%edx
	pushl	%esi
	pushl	%ebx
	shrl	$7,%eax
	movl	$GLOBL(regs),%esi
	andl	$28,%eax
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ecx
	movb	%al,8(%esp)
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
	movb	8(%esp),%cl
	movsbl	%al,%eax
	andl	$7,%ecx
	sarl	%cl,%eax
	xorb	$1,%al
	addl	$2,GLOBL(regs)+88
	movb	%al,%dl
	popl	%ebx
	andb	$1,%dl
	movb	regflags,%al
	salb	$6,%dl
	andb	$191,%al
	popl	%esi
	orb	%dl,%al
	addl	$4,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0057:
	ret

FUNC(op_128)

	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edi
	xorl	%edx,%edx
	movw	0x2164334A+2(%edi),%dx
RR2_0035:
	rolw	$8,%dx
	movswl	%dx,%edx
	addl	$8,%eax
	addl	(%esi,%eax,4),%edx
	movl	%edx,%eax
	shrl	$7,%ebx
	shrl	$14,%eax
	addl	$4,%edi
	andl	$1020,%eax
	andl	$28,%ebx
	movl	GLOBL(R24)(%eax),%ecx
	movb	(%ebx,%esi),%al
	andl	$65535,%edx
	andb	$7,%al
	movsbl	(%edx,%ecx),%edx
	movsbl	%al,%ecx
	movl	%edi,GLOBL(regs)+88
	sarl	%cl,%edx
	movb	regflags,%al
	xorl	$1,%edx
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0058:
	ret

FUNC(op_138)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%esi
	xorl	%edx,%edx
	movw	0x2164334A+2(%esi),%dx
RR2_0036:
	rolw	$8,%dx
	movswl	%dx,%edx
	shrl	$7,%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$28,%ebx
	movl	GLOBL(R24)(%eax),%ecx
	movb	GLOBL(regs)(%ebx),%al
	andl	$65535,%edx
	andb	$7,%al
	movsbl	(%edx,%ecx),%edx
	movsbl	%al,%ecx
	addl	$4,%esi
	sarl	%cl,%edx
	movl	%esi,GLOBL(regs)+88
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0059:
	ret

FUNC(op_139)

	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%esi
	shrl	$7,%ecx
	movl	0x2164334A+2(%esi),%edx
RR2_0037:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$28,%ecx
	movl	GLOBL(R24)(%eax),%ebx
	movb	GLOBL(regs)(%ecx),%al
	andl	$65535,%edx
	andb	$7,%al
	movsbl	(%edx,%ebx),%edx
	movsbl	%al,%ecx
	addl	$6,%esi
	sarl	%cl,%edx
	movl	%esi,GLOBL(regs)+88
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0060:
	ret

FUNC(op_13a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%esi
	shrl	$7,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_0038:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%esi),%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$28,%ebx
	movl	GLOBL(R24)(%eax),%ecx
	movb	GLOBL(regs)(%ebx),%al
	andl	$65535,%edx
	andb	$7,%al
	movsbl	(%edx,%ecx),%edx
	movsbl	%al,%ecx
	addl	$4,%esi
	sarl	%cl,%edx
	movl	%esi,GLOBL(regs)+88
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0061:
	ret

FUNC(op_13c)

	shrl	$7,%eax
	pushl	%ebx
	andl	$28,%eax
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ebx
	andb	$7,%al
	movsbl	0x2164334A+3(%ebx),%edx
RR3_0009:
	movsbl	%al,%ecx
	sarl	%cl,%edx
	addl	$4,%ebx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	movl	%ebx,GLOBL(regs)+88
	orb	%dl,%al
	popl	%ebx
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_0062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0062:
	ret

FUNC(op_140)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebx
	andl	$7,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	shrl	$7,%eax
	movl	(%ebx,%esi),%ecx
	andl	$28,%eax
	movl	%ecx,12-12(%esp)
	movl	(%eax,%esi),%edi
	andl	$31,%edi
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
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0063:
	ret

FUNC(op_148)

	subl	$32,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$7,%edx
	movl	%eax,44-16(%esp)
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0039:
	rolw	$8,%cx
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%ecx,%eax
	movl	%ecx,%ebx
	shrl	$14,%eax
	andl	$65535,%ebx
	andl	$1020,%eax
	movl	%ebx,20-16(%esp)
	leal	2(%ecx),%esi
	movl	GLOBL(R24)(%eax),%edx
	movl	%esi,%eax
	andl	$65535,%esi
	shrl	$14,%eax
	movl	%esi,36-16(%esp)
	andl	$1020,%eax
	leal	4(%ecx),%ebx
	movl	GLOBL(R24)(%eax),%ebp
	movl	%ebx,%eax
	andl	$65535,%ebx
	shrl	$14,%eax
	movl	%ebx,28-16(%esp)
	andl	$1020,%eax
	addl	$6,%ecx
	movl	GLOBL(R24)(%eax),%edi
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	movl	20-16(%esp),%esi
	movl	GLOBL(R24)(%eax),%eax
	movl	36-16(%esp),%ebx
	movl	%eax,16-16(%esp)
	andl	$65535,%ecx
	movb	(%esi,%edx),%dl
	xorl	%eax,%eax
	movb	(%ebx,%ebp),%al
	andl	$255,%edx
	sall	$16,%eax
	sall	$24,%edx
	movl	28-16(%esp),%esi
	addl	%eax,%edx
	xorl	%eax,%eax
	movb	(%esi,%edi),%al
	movl	16-16(%esp),%ebx
	sall	$8,%eax
	movl	44-16(%esp),%esi
	addl	%eax,%edx
	xorl	%eax,%eax
	movb	(%ecx,%ebx),%al
	andl	$28,%esi
	addl	%eax,%edx
	movl	$GLOBL(regs),%ebx
	movl	%edx,(%esi,%ebx)
	addl	$4,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0064:
	ret

FUNC(op_150)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edi,%edi
	movl	$GLOBL(regs),%esi
	xorl	%ebx,%ebx
	movb	2(%esi,%eax,4),%bl
	movw	(%esi,%eax,4),%di
	sall	$2,%ebx
	movl	GLOBL(R24)(%ebx),%eax
	shrl	$7,%edx
	movb	(%edi,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	(%edx,%esi),%al
	andb	$7,%al
	movsbl	%al,%esi
	movsbl	15-12(%esp),%edx
	movl	%esi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	xorb	%al,%cl
	movb	%cl,(%edi,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0065:
	ret

FUNC(op_158)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%edi
	andl	$28,%eax
	andl	$7,%edi
	movb	GLOBL(regs)(%eax),%al
	leal	8(%edi),%ecx
	movb	%al,16-16(%esp)
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%edx
	movzbl	GLOBL(regs)+2(%ecx),%esi
	movl	%edx,%ebp
	sall	$2,%esi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%esi),%eax
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebp,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	movb	16-16(%esp),%cl
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
	movb	%bl,(%ebp,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0066:
	ret

FUNC(op_160)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ecx
	movb	%al,16-16(%esp)
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%edi
	shrl	$14,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%edx,(%ecx,%esi)
	movb	16-16(%esp),%cl
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
	movl	GLOBL(W24)(%edi),%edx
	xorb	%al,%bl
	movb	%bl,(%ebp,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0067:
	ret

FUNC(op_168)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ebp
	movl	%eax,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0040:
	rolw	$8,%cx
	movl	%ecx,16-16(%esp)
	addl	$8,%edx
	movswl	16-16(%esp),%ecx
	addl	(%ebp,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,16-16(%esp)
	andl	$1020,%esi
	shrl	$7,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edi
	movb	(%ecx,%eax),%bl
	movb	(%edi,%ebp),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	16-16(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0068:
	ret

FUNC(op_178)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0041:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0069:
	ret

FUNC(op_179)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_0042:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movb	(%ebx,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	15-12(%esp),%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%cl
	movb	%cl,(%ebx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0070:
	ret

FUNC(op_17a)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0043:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	xorb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0071:
	ret

FUNC(op_180)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebx
	andl	$28,%eax
	andl	$7,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%eax,%esi),%ecx
	movl	(%ebx,%esi),%edi
	andl	$31,%ecx
	movl	%edi,%eax
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
	andl	%edi,%eax
	movl	%eax,(%ebx,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0072:
	ret

FUNC(op_188)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$7,%eax
	andl	$7,%ecx
	andl	$28,%eax
	addl	$8,%ecx
	movw	GLOBL(regs)(%eax),%si
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0044:
	rolw	$8,%dx
	addl	GLOBL(regs)(,%ecx,4),%edx
	movl	%esi,%ebx
	movl	%edx,%eax
	movl	%edx,%ecx
	addl	$2,%edx
	sarw	$8,%bx
	shrl	$14,%eax
	movw	%bx,10-8(%esp)
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(W24)(%eax),%eax
	movb	10-8(%esp),%bl
	movb	%bl,(%ecx,%eax)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movl	%esi,%ebx
	movb	%bl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0073:
	ret

FUNC(op_190)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edi,%edi
	movl	$GLOBL(regs),%esi
	xorl	%ebx,%ebx
	movb	2(%esi,%eax,4),%bl
	movw	(%esi,%eax,4),%di
	sall	$2,%ebx
	movl	GLOBL(R24)(%ebx),%eax
	shrl	$7,%edx
	movb	(%edi,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	(%edx,%esi),%al
	andb	$7,%al
	movsbl	%al,%esi
	movsbl	15-12(%esp),%edx
	movl	%esi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%ebx),%eax
	andb	15-12(%esp),%dl
	movb	%dl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0074:
	ret

FUNC(op_198)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%edi
	andl	$7,%edi
	andl	$28,%eax
	leal	8(%edi),%ecx
	sall	$2,%ecx
	movb	GLOBL(regs)(%eax),%bl
	movl	GLOBL(regs)(%ecx),%edx
	movzbl	GLOBL(regs)+2(%ecx),%esi
	movl	%edx,%ebp
	sall	$2,%esi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%esi),%eax
	movb	(%ebp,%eax),%al
	movb	%al,19-16(%esp)
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movl	%edx,GLOBL(regs)(%ecx)
	movl	%ebx,%ecx
	movsbl	19-16(%esp),%eax
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
	andb	19-16(%esp),%dl
	movb	%dl,(%ebp,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0075:
	ret

FUNC(op_1a0)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ecx
	movb	%al,16-16(%esp)
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%edi
	shrl	$14,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%edx,(%ecx,%esi)
	movb	16-16(%esp),%cl
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
	movl	GLOBL(W24)(%edi),%eax
	andb	%dl,%bl
	movb	%bl,(%ebp,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0076:
	ret

FUNC(op_1a8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ebp
	movl	%eax,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0045:
	rolw	$8,%cx
	movl	%ecx,16-16(%esp)
	addl	$8,%edx
	movswl	16-16(%esp),%ecx
	addl	(%ebp,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,16-16(%esp)
	andl	$1020,%esi
	shrl	$7,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edi
	movb	(%ecx,%eax),%bl
	movb	(%edi,%ebp),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	16-16(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0077:
	ret

FUNC(op_1b8)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0046:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0078:
	ret

FUNC(op_1b9)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_0047:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movb	(%ebx,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	15-12(%esp),%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	15-12(%esp),%dl
	movb	%dl,(%ebx,%eax)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0079:
	ret

FUNC(op_1ba)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0048:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$-2,%eax
	movl	%eax,%edx
	roll	%cl,%edx
	movl	GLOBL(W24)(%esi),%eax
	andb	%dl,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0080:
	ret

FUNC(op_1c0)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebx
	andl	$7,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	shrl	$7,%eax
	movl	(%ebx,%esi),%ecx
	andl	$28,%eax
	movl	%ecx,12-12(%esp)
	movl	(%eax,%esi),%edi
	andl	$31,%edi
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
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0081:
	ret

FUNC(op_1c8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	addl	$8,%edx
	movl	GLOBL(regs)(%eax),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0049:
	rolw	$8,%cx
	addl	GLOBL(regs)(,%edx,4),%ecx
	movl	%esi,%ebx
	movl	%ecx,%eax
	movl	%ecx,%edx
	sarl	$24,%ebx
	shrl	$14,%eax
	movl	%ebx,8-8(%esp)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	8-8(%esp),%bl
	movb	%bl,(%edx,%eax)
	leal	2(%ecx),%edx
	movl	%esi,%ebx
	movl	%edx,%eax
	sarl	$16,%ebx
	shrl	$14,%eax
	movl	%ebx,8-8(%esp)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	8-8(%esp),%bl
	movb	%bl,(%edx,%eax)
	movl	%esi,%ebx
	leal	4(%ecx),%edx
	addl	$6,%ecx
	movl	%edx,%eax
	sarl	$8,%ebx
	shrl	$14,%eax
	movl	%ebx,8-8(%esp)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	8-8(%esp),%bl
	movb	%bl,(%edx,%eax)
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(W24)(%eax),%eax
	movl	%esi,%ebx
	movb	%bl,(%ecx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0082:
	ret

FUNC(op_1d0)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edi,%edi
	movl	$GLOBL(regs),%esi
	xorl	%ebx,%ebx
	movb	2(%esi,%eax,4),%bl
	movw	(%esi,%eax,4),%di
	sall	$2,%ebx
	movl	GLOBL(R24)(%ebx),%eax
	shrl	$7,%edx
	movb	(%edi,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	(%edx,%esi),%al
	andb	$7,%al
	movsbl	%al,%esi
	movsbl	15-12(%esp),%edx
	movl	%esi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%ebx),%edx
	orb	%al,%cl
	movb	%cl,(%edi,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0083:
	ret

FUNC(op_1d8)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%edi
	andl	$28,%eax
	andl	$7,%edi
	movb	GLOBL(regs)(%eax),%al
	leal	8(%edi),%ecx
	movb	%al,16-16(%esp)
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%edx
	movzbl	GLOBL(regs)+2(%ecx),%esi
	movl	%edx,%ebp
	sall	$2,%esi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%esi),%eax
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebp,%eax),%bl
	movl	%edx,GLOBL(regs)(%ecx)
	movb	16-16(%esp),%cl
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
	movb	%bl,(%ebp,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0084:
	ret

FUNC(op_1e0)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ecx
	movb	%al,16-16(%esp)
	sall	$2,%ecx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%edi
	shrl	$14,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	movb	(%ebp,%eax),%bl
	movl	%edx,(%ecx,%esi)
	movb	16-16(%esp),%cl
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
	movl	GLOBL(W24)(%edi),%edx
	orb	%al,%bl
	movb	%bl,(%ebp,%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0085:
	ret

FUNC(op_1e8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ebp
	movl	%eax,%edi
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0050:
	rolw	$8,%cx
	movl	%ecx,16-16(%esp)
	addl	$8,%edx
	movswl	16-16(%esp),%ecx
	addl	(%ebp,%edx,4),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,16-16(%esp)
	andl	$1020,%esi
	shrl	$7,%edi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edi
	movb	(%ecx,%eax),%bl
	movb	(%edi,%ebp),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	16-16(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0086:
	ret

FUNC(op_1f8)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_0051:
	rolw	$8,%cx
	movl	%ecx,12-12(%esp)
	movswl	12-12(%esp),%ecx
	movl	%ecx,%esi
	andl	$65535,%ecx
	shrl	$14,%esi
	movl	%ecx,12-12(%esp)
	andl	$1020,%esi
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0087:
	ret

FUNC(op_1f9)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_0052:
	bswapl	%ebx
	movl	%ebx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%esi),%eax
	movb	(%ebx,%eax),%al
	andl	$28,%edx
	movb	%al,15-12(%esp)
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	15-12(%esp),%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movb	15-12(%esp),%cl
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%cl
	movb	%cl,(%ebx,%edx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0088:
	ret

FUNC(op_1fa)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0053:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,12-12(%esp)
	movl	%eax,%esi
	movl	%eax,%ecx
	shrl	$14,%esi
	andl	$65535,%ecx
	andl	$1020,%esi
	movl	%ecx,12-12(%esp)
	movl	GLOBL(R24)(%esi),%eax
	andl	$28,%edx
	movb	(%ecx,%eax),%bl
	movb	GLOBL(regs)(%edx),%al
	andb	$7,%al
	movsbl	%al,%edi
	movsbl	%bl,%edx
	movl	%edi,%ecx
	sarl	%cl,%edx
	xorl	$1,%edx
	movb	regflags,%al
	andb	$1,%dl
	andb	$191,%al
	salb	$6,%dl
	orb	%dl,%al
	movb	%al,regflags
	movl	$1,%eax
	sall	%cl,%eax
	movl	GLOBL(W24)(%esi),%edx
	orb	%al,%bl
	movl	12-12(%esp),%ecx
	movb	%bl,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0089:
	ret

FUNC(op_200)

	movl	%eax,%ecx
	movl	$GLOBL(regs),%edx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	sall	$2,%ecx
	movb	0x2164334A+3(%eax),%al
RR3_0010:
	andb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0090:
	ret

FUNC(op_210)

	andl	$7,%eax
	xorl	%edx,%edx
	xorl	%ecx,%ecx
	addl	$8,%eax
	movl	GLOBL(regs)+88,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_0011:
	movl	GLOBL(R24)(%edx),%eax
	andb	(%ecx,%eax),%bl
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
	jl	JJ_0091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0091:
	ret

FUNC(op_218)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	leal	8(%ebp),%ebx
	movb	0x2164334A+3(%eax),%al
RR3_0012:
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
	andb	%al,19-16(%esp)
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
	jl	JJ_0092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0092:
	ret

FUNC(op_220)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%edi
	movb	0x2164334A+3(%eax),%al
RR3_0013:
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
	andb	%al,19-12(%esp)
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
	jl	JJ_0093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0093:
	ret

FUNC(op_228)

	andl	$7,%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_0014:
	rolw	$8,%dx
	addl	$8,%eax
	movswl	%dx,%edx
	addl	GLOBL(regs)(,%eax,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_0014:
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	andb	(%edx,%eax),%bl
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
	jl	JJ_0094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0094:
	ret

FUNC(op_238)

	movl	GLOBL(regs)+88,%ebx
	xorl	%edx,%edx
	movw	0x2164334A+4(%ebx),%dx
RR4_0015:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	0x2164334A+3(%ebx),%bl
RR3_0015:
	movl	GLOBL(R24)(%ecx),%eax
	andb	(%edx,%eax),%bl
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
	jl	JJ_0095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0095:
	ret

FUNC(op_239)

	movl	GLOBL(regs)+88,%ebx
	movl	0x2164334A+4(%ebx),%ecx
RR4_0016:
	bswapl	%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	0x2164334A+3(%ebx),%bl
RR3_0016:
	movl	GLOBL(R24)(%edx),%eax
	andb	(%ecx,%eax),%bl
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
	jl	JJ_0096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0096:
	ret

FUNC(op_23c)

	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0054:
	rolw	$8,%dx
	movl	%edx,%eax
	movb	$255,%ah
	andw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0097:
	ret

FUNC(op_240)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_0055:
	rolw	$8,%si
	movl	%esi,%eax
	sall	$2,%ecx
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
	jl	JJ_0098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0098:
	ret

FUNC(op_250)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_0056:
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
	andl	%eax,%ebx
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
	jl	JJ_0099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0099:
	ret

FUNC(op_258)

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
RR2_0057:
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
	andl	%eax,%edi
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
	jl	JJ_0100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0100:
	ret

FUNC(op_260)

	subl	$4,%esp
	movl	%eax,%ecx
	andl	$7,%ecx
	addl	$8,%ecx
	movl	$GLOBL(regs),%ebp
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0058:
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
	andl	%eax,%edi
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
	jl	JJ_0101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0101:
	ret

FUNC(op_268)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_0059:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_0017:
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
	andl	%edx,%ebx
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
	jl	JJ_0102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0102:
	ret

FUNC(op_278)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_0060:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_0018:
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
	andl	%edx,%ebx
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
	jl	JJ_0103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0103:
	ret

FUNC(op_279)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_0061:
	rolw	$8,%ax
	movl	%eax,%ebx
	movl	0x2164334A+4(%edx),%eax
RR4_0019:
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
	andl	%edx,%ebx
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
	jl	JJ_0104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0104:
	ret

FUNC(op_27c)

	cmpb	$0,GLOBL(regs)+80
	jne	L_0_1672
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_0105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0105:
	ret
	.align	2,0x90
L_0_1672:
	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_0062:
	rolw	$8,%dx
	movl	%edx,%eax
	andw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_0106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0106:
	ret

FUNC(op_280)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_0063:
	sall	$2,%edx
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
	jl	JJ_0107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0107:
	ret

FUNC(op_290)

	movl	%eax,%edx
	xorl	%ecx,%ecx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_0064:
	movb	GLOBL(regs)+2(,%edx,4),%cl
	bswapl	%ebx
	movw	GLOBL(regs)(,%edx,4),%dx
	sall	$2,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	andl	%eax,%ebx
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
	jl	JJ_0108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0108:
	ret

FUNC(op_298)

	movl	$GLOBL(regs),%ebp
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	addl	$8,%esi
	movl	0x2164334A+2(%eax),%edi
RR2_0065:
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
	andl	%eax,%edi
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
	jl	JJ_0109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0109:
	ret

FUNC(op_2a0)

	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%ebp
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%ebp),%ecx
	movl	GLOBL(regs)+88,%eax
	addl	$-4,%ecx
	movl	0x2164334A+2(%eax),%edi
RR2_0066:
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
	andl	%eax,%edi
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
	jl	JJ_0110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0110:
	ret

FUNC(op_2a8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_0003:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_0067:
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
	andl	%edx,%ebx
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
	jl	JJ_0111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0111:
	ret

FUNC(op_2b8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+6(%eax),%si
RR6_0004:
	rolw	$8,%si
	movl	0x2164334A+2(%eax),%ebx
RR2_0068:
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
	andl	%edx,%ebx
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
	jl	JJ_0112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0112:
	ret

FUNC(op_2b9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_0069:
	movl	0x2164334A+6(%eax),%eax
RR6_0005:
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
	andl	%edx,%ebx
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
	jl	JJ_0113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0113:
	ret

FUNC(op_400)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%eax
	sall	$2,%edx
	movl	GLOBL(regs)+88,%ecx
	movb	(%edx,%eax),%bl
	subb	0x2164334A+3(%ecx),%bl
RR3_0017:
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
	jl	JJ_0114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0114:
	ret

FUNC(op_410)

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
	subb	0x2164334A+3(%ecx),%bl
RR3_0018:
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
	jl	JJ_0115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0115:
	ret

FUNC(op_418)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%eax
	leal	8(%ebp),%ebx
	movb	0x2164334A+3(%eax),%al
RR3_0019:
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
	subb	19-16(%esp),%cl
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
	jl	JJ_0116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_0206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_0116:
	ret

FUNC(Init020_00)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_0000-4
	movl	%eax,RR0_0001-4
	movl	%eax,RR0_0002-4
	movl	%eax,RR0_0003-4
	movl	%eax,RR0_0004-4
	movl	%eax,RR0_0005-4
	movl	%eax,RR0_0006-4
	movl	%eax,RR0_0007-4
	movl	%eax,RR0_0008-4
	movl	%eax,RR0_0009-4
	movl	%eax,RR0_0010-4
	movl	%eax,RR0_0011-4
	movl	%eax,RR0_0012-4
	movl	%eax,RR0_0013-4
	movl	%eax,RR0_0014-4
	movl	%eax,RR0_0015-4
	movl	%eax,RR0_0016-4
	movl	%eax,RR0_0017-4
	movl	%eax,RR0_0018-4
	movl	%eax,RR0_0019-4
	movl	%eax,RR0_0020-4
	movl	%eax,RR0_0021-4
	movl	%eax,RR0_0022-4
	movl	%eax,RR0_0023-4
	movl	%eax,RR0_0024-4
	movl	%eax,RR0_0025-4
	movl	%eax,RR0_0026-4
	movl	%eax,RR0_0027-4
	movl	%eax,RR0_0028-4
	movl	%eax,RR0_0029-4
	movl	%eax,RR0_0030-4
	movl	%eax,RR0_0031-4
	movl	%eax,RR0_0032-4
	movl	%eax,RR0_0033-4
	movl	%eax,RR0_0034-4
	movl	%eax,RR0_0035-4
	movl	%eax,RR0_0036-4
	movl	%eax,RR0_0037-4
	movl	%eax,RR0_0038-4
	movl	%eax,RR0_0039-4
	movl	%eax,RR0_0040-4
	movl	%eax,RR0_0041-4
	movl	%eax,RR0_0042-4
	movl	%eax,RR0_0043-4
	movl	%eax,RR0_0044-4
	movl	%eax,RR0_0045-4
	movl	%eax,RR0_0046-4
	movl	%eax,RR0_0047-4
	movl	%eax,RR0_0048-4
	movl	%eax,RR0_0049-4
	movl	%eax,RR0_0050-4
	movl	%eax,RR0_0051-4
	movl	%eax,RR0_0052-4
	movl	%eax,RR0_0053-4
	movl	%eax,RR0_0054-4
	movl	%eax,RR0_0055-4
	movl	%eax,RR0_0056-4
	movl	%eax,RR0_0057-4
	movl	%eax,RR0_0058-4
	movl	%eax,RR0_0059-4
	movl	%eax,RR0_0060-4
	movl	%eax,RR0_0061-4
	movl	%eax,RR0_0062-4
	movl	%eax,RR0_0063-4
	movl	%eax,RR0_0064-4
	movl	%eax,RR0_0065-4
	movl	%eax,RR0_0066-4
	movl	%eax,RR0_0067-4
	movl	%eax,RR0_0068-4
	movl	%eax,RR0_0069-4
	movl	%eax,RR0_0070-4
	movl	%eax,RR0_0071-4
	movl	%eax,RR0_0072-4
	movl	%eax,RR0_0073-4
	movl	%eax,RR0_0074-4
	movl	%eax,RR0_0075-4
	movl	%eax,RR0_0076-4
	movl	%eax,RR0_0077-4
	movl	%eax,RR0_0078-4
	movl	%eax,RR0_0079-4
	movl	%eax,RR0_0080-4
	movl	%eax,RR0_0081-4
	movl	%eax,RR0_0082-4
	movl	%eax,RR0_0083-4
	movl	%eax,RR0_0084-4
	movl	%eax,RR0_0085-4
	movl	%eax,RR0_0086-4
	movl	%eax,RR0_0087-4
	movl	%eax,RR0_0088-4
	movl	%eax,RR0_0089-4
	movl	%eax,RR0_0090-4
	movl	%eax,RR0_0091-4
	movl	%eax,RR0_0092-4
	movl	%eax,RR0_0093-4
	movl	%eax,RR0_0094-4
	movl	%eax,RR0_0095-4
	movl	%eax,RR0_0096-4
	movl	%eax,RR0_0097-4
	movl	%eax,RR0_0098-4
	movl	%eax,RR0_0099-4
	movl	%eax,RR0_0100-4
	movl	%eax,RR0_0101-4
	movl	%eax,RR0_0102-4
	movl	%eax,RR0_0103-4
	movl	%eax,RR0_0104-4
	movl	%eax,RR0_0105-4
	movl	%eax,RR0_0106-4
	movl	%eax,RR0_0107-4
	movl	%eax,RR0_0108-4
	movl	%eax,RR0_0109-4
	movl	%eax,RR0_0110-4
	movl	%eax,RR0_0111-4
	movl	%eax,RR0_0112-4
	movl	%eax,RR0_0113-4
	movl	%eax,RR0_0114-4
	movl	%eax,RR0_0115-4
	movl	%eax,RR0_0116-4
	movl	%eax,RR0_0117-4
	movl	%eax,RR0_0118-4
	movl	%eax,RR0_0119-4
	movl	%eax,RR0_0120-4
	movl	%eax,RR0_0121-4
	movl	%eax,RR0_0122-4
	movl	%eax,RR0_0123-4
	movl	%eax,RR0_0124-4
	movl	%eax,RR0_0125-4
	movl	%eax,RR0_0126-4
	movl	%eax,RR0_0127-4
	movl	%eax,RR0_0128-4
	movl	%eax,RR0_0129-4
	movl	%eax,RR0_0130-4
	movl	%eax,RR0_0131-4
	movl	%eax,RR0_0132-4
	movl	%eax,RR0_0133-4
	movl	%eax,RR0_0134-4
	movl	%eax,RR0_0135-4
	movl	%eax,RR0_0136-4
	movl	%eax,RR0_0137-4
	movl	%eax,RR0_0138-4
	movl	%eax,RR0_0139-4
	movl	%eax,RR0_0140-4
	movl	%eax,RR0_0141-4
	movl	%eax,RR0_0142-4
	movl	%eax,RR0_0143-4
	movl	%eax,RR0_0144-4
	movl	%eax,RR0_0145-4
	movl	%eax,RR0_0146-4
	movl	%eax,RR0_0147-4
	movl	%eax,RR0_0148-4
	movl	%eax,RR0_0149-4
	movl	%eax,RR0_0150-4
	movl	%eax,RR0_0151-4
	movl	%eax,RR0_0152-4
	movl	%eax,RR0_0153-4
	movl	%eax,RR0_0154-4
	movl	%eax,RR0_0155-4
	movl	%eax,RR0_0156-4
	movl	%eax,RR0_0157-4
	movl	%eax,RR0_0158-4
	movl	%eax,RR0_0159-4
	movl	%eax,RR0_0160-4
	movl	%eax,RR0_0161-4
	movl	%eax,RR0_0162-4
	movl	%eax,RR0_0163-4
	movl	%eax,RR0_0164-4
	movl	%eax,RR0_0165-4
	movl	%eax,RR0_0166-4
	movl	%eax,RR0_0167-4
	movl	%eax,RR0_0168-4
	movl	%eax,RR0_0169-4
	movl	%eax,RR0_0170-4
	movl	%eax,RR0_0171-4
	movl	%eax,RR0_0172-4
	movl	%eax,RR0_0173-4
	movl	%eax,RR0_0174-4
	movl	%eax,RR0_0175-4
	movl	%eax,RR0_0176-4
	movl	%eax,RR0_0177-4
	movl	%eax,RR0_0178-4
	movl	%eax,RR0_0179-4
	movl	%eax,RR0_0180-4
	movl	%eax,RR0_0181-4
	movl	%eax,RR0_0182-4
	movl	%eax,RR0_0183-4
	movl	%eax,RR0_0184-4
	movl	%eax,RR0_0185-4
	movl	%eax,RR0_0186-4
	movl	%eax,RR0_0187-4
	movl	%eax,RR0_0188-4
	movl	%eax,RR0_0189-4
	movl	%eax,RR0_0190-4
	movl	%eax,RR0_0191-4
	movl	%eax,RR0_0192-4
	movl	%eax,RR0_0193-4
	movl	%eax,RR0_0194-4
	movl	%eax,RR0_0195-4
	movl	%eax,RR0_0196-4
	movl	%eax,RR0_0197-4
	movl	%eax,RR0_0198-4
	movl	%eax,RR0_0199-4
	movl	%eax,RR0_0200-4
	movl	%eax,RR0_0201-4
	movl	%eax,RR0_0202-4
	movl	%eax,RR0_0203-4
	movl	%eax,RR0_0204-4
	movl	%eax,RR0_0205-4
	movl	%eax,RR0_0206-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_0000-4
	movl	%eax,RR2_0001-4
	movl	%eax,RR2_0002-4
	movl	%eax,RR2_0003-4
	movl	%eax,RR2_0004-4
	movl	%eax,RR2_0005-4
	movl	%eax,RR2_0006-4
	movl	%eax,RR2_0007-4
	movl	%eax,RR2_0008-4
	movl	%eax,RR2_0009-4
	movl	%eax,RR2_0010-4
	movl	%eax,RR2_0011-4
	movl	%eax,RR2_0012-4
	movl	%eax,RR2_0013-4
	movl	%eax,RR2_0014-4
	movl	%eax,RR2_0015-4
	movl	%eax,RR2_0016-4
	movl	%eax,RR2_0017-4
	movl	%eax,RR2_0018-4
	movl	%eax,RR2_0019-4
	movl	%eax,RR2_0020-4
	movl	%eax,RR2_0021-4
	movl	%eax,RR2_0022-4
	movl	%eax,RR2_0023-4
	movl	%eax,RR2_0024-4
	movl	%eax,RR2_0025-4
	movl	%eax,RR2_0026-4
	movl	%eax,RR2_0027-4
	movl	%eax,RR2_0028-4
	movl	%eax,RR2_0029-4
	movl	%eax,RR2_0030-4
	movl	%eax,RR2_0031-4
	movl	%eax,RR2_0032-4
	movl	%eax,RR2_0033-4
	movl	%eax,RR2_0034-4
	movl	%eax,RR2_0035-4
	movl	%eax,RR2_0036-4
	movl	%eax,RR2_0037-4
	movl	%eax,RR2_0038-4
	movl	%eax,RR2_0039-4
	movl	%eax,RR2_0040-4
	movl	%eax,RR2_0041-4
	movl	%eax,RR2_0042-4
	movl	%eax,RR2_0043-4
	movl	%eax,RR2_0044-4
	movl	%eax,RR2_0045-4
	movl	%eax,RR2_0046-4
	movl	%eax,RR2_0047-4
	movl	%eax,RR2_0048-4
	movl	%eax,RR2_0049-4
	movl	%eax,RR2_0050-4
	movl	%eax,RR2_0051-4
	movl	%eax,RR2_0052-4
	movl	%eax,RR2_0053-4
	movl	%eax,RR2_0054-4
	movl	%eax,RR2_0055-4
	movl	%eax,RR2_0056-4
	movl	%eax,RR2_0057-4
	movl	%eax,RR2_0058-4
	movl	%eax,RR2_0059-4
	movl	%eax,RR2_0060-4
	movl	%eax,RR2_0061-4
	movl	%eax,RR2_0062-4
	movl	%eax,RR2_0063-4
	movl	%eax,RR2_0064-4
	movl	%eax,RR2_0065-4
	movl	%eax,RR2_0066-4
	movl	%eax,RR2_0067-4
	movl	%eax,RR2_0068-4
	movl	%eax,RR2_0069-4
	incl	%eax
	movl	%eax,RR3_0000-4
	movl	%eax,RR3_0001-4
	movl	%eax,RR3_0002-4
	movl	%eax,RR3_0003-4
	movl	%eax,RR3_0004-4
	movl	%eax,RR3_0005-4
	movl	%eax,RR3_0006-4
	movl	%eax,RR3_0007-4
	movl	%eax,RR3_0008-4
	movl	%eax,RR3_0009-4
	movl	%eax,RR3_0010-4
	movl	%eax,RR3_0011-4
	movl	%eax,RR3_0012-4
	movl	%eax,RR3_0013-4
	movl	%eax,RR3_0014-4
	movl	%eax,RR3_0015-4
	movl	%eax,RR3_0016-4
	movl	%eax,RR3_0017-4
	movl	%eax,RR3_0018-4
	movl	%eax,RR3_0019-4
	incl	%eax
	movl	%eax,RR4_0000-4
	movl	%eax,RR4_0001-4
	movl	%eax,RR4_0002-4
	movl	%eax,RR4_0003-4
	movl	%eax,RR4_0004-4
	movl	%eax,RR4_0005-4
	movl	%eax,RR4_0006-4
	movl	%eax,RR4_0007-4
	movl	%eax,RR4_0008-4
	movl	%eax,RR4_0009-4
	movl	%eax,RR4_0010-4
	movl	%eax,RR4_0011-4
	movl	%eax,RR4_0012-4
	movl	%eax,RR4_0013-4
	movl	%eax,RR4_0014-4
	movl	%eax,RR4_0015-4
	movl	%eax,RR4_0016-4
	movl	%eax,RR4_0017-4
	movl	%eax,RR4_0018-4
	movl	%eax,RR4_0019-4
	incl	%eax
	incl	%eax
	movl	%eax,RR6_0000-4
	movl	%eax,RR6_0001-4
	movl	%eax,RR6_0002-4
	movl	%eax,RR6_0003-4
	movl	%eax,RR6_0004-4
	movl	%eax,RR6_0005-4
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
