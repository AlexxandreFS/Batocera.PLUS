

FUNC(op_5df0)

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
RR0_a000:
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
	jne	L_a_374
	movswl	%di,%edi
L_a_374:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_375
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_376
	movl	%ebp,%ebx
L_a_376:
	testl	$64,%esi
	je	L_a_377
	movl	%ebp,%edi
L_a_377:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_378
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_378:
	cmpl	$48,%edx
	jne	L_a_381
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_381:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_384
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_384:
	cmpl	$3,16-16(%esp)
	jne	L_a_387
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_387:
	andl	$4,%esi
	jne	L_a_390
	addl	%edi,%ebx
L_a_390:
	cmpl	$0,16-16(%esp)
	je	L_a_391
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_391:
	testl	%esi,%esi
	je	L_a_394
	addl	%edi,%ebx
L_a_394:
	leal	(%ebp,%ebx),%esi
	jmp	L_a_414
	.align	2,0x90
L_a_375:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%esi
L_a_414:
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ebx,%ebx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_397
	movl	$255,%ebx
L_a_397:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%bl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a000:
	ret

FUNC(op_5df8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a000:
	rolw	$8,%si
	movl	%esi,%eax
	movswl	%ax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_427
	movl	$255,%ecx
L_a_427:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a006:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a001:
	ret

FUNC(op_5df9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_a001:
	bswapl	%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	xorl	%ecx,%ecx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_457
	movl	$255,%ecx
L_a_457:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a007:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a002:
	ret

FUNC(op_5dfa)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_487
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a008:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a003:
	ret
	.align	2,0x90
L_a_487:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a009:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a004:
	ret

FUNC(op_5dfb)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_516
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a010:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a005:
	ret
	.align	2,0x90
L_a_516:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a011:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a006:
	ret

FUNC(op_5dfc)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_544
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a012:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a007:
	ret
	.align	2,0x90
L_a_544:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a013:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a008:
	ret

FUNC(op_5ec0)

	movl	%eax,%ebx
	xorl	%ecx,%ecx
	andl	$7,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_593
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	movb	%al,%cl
L_a_593:
	xorl	%edx,%edx
	testl	%ecx,%ecx
	je	L_a_572
	movl	$255,%edx
L_a_572:
	movb	%dl,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a014:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a009:
	ret

FUNC(op_5ec8)

	andl	$7,%eax
	xorl	%edx,%edx
	leal	0(,%eax,4),%ecx
	movl	$GLOBL(regs),%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_a002:
	rolw	$8,%di
	movl	%edi,%eax
	movw	(%ecx,%ebx),%si
	movl	%eax,%ebp
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_621
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_621:
	testl	%edx,%edx
	jne	L_a_601
	movl	%esi,%edi
	decl	%edi
	movw	%di,(%ecx,%ebx)
	testw	%si,%si
	je	L_a_601
	movl	GLOBL(regs)+88,%edx
	movswl	%bp,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_a_626
	.align	2,0x90
L_a_601:
	addl	$4,GLOBL(regs)+88
L_a_626:
	popl	%eax
	decl	%eax
	jl	JJ_a010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a010:
	ret

FUNC(op_5ed0)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movl	GLOBL(regs)(,%eax,4),%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_650
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_650:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_629
	movl	$255,%ecx
L_a_629:
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
	jl	JJ_a011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a016:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a011:
	ret

FUNC(op_5ed8)

	andl	$7,%eax
	leal	8(%eax),%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_679
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_679:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_658
	movl	$255,%ecx
L_a_658:
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
	jl	JJ_a012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a012:
	ret

FUNC(op_5ee0)

	movl	%eax,%edx
	andl	$7,%edx
	leal	8(%edx),%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,(%eax,%ecx)
	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_708
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_708:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_687
	movl	$255,%ecx
L_a_687:
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
	jl	JJ_a013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a013:
	ret

FUNC(op_5ee8)

	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a003:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	movl	GLOBL(regs)(,%edx,4),%ebx
	addl	%eax,%ebx
	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_738
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_738:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_717
	movl	$255,%ecx
L_a_717:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a014:
	ret

FUNC(op_5ef0)

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
RR0_a020:
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
	jne	L_a_748
	movswl	%di,%edi
L_a_748:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_749
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_750
	movl	%ebp,%ebx
L_a_750:
	testl	$64,%esi
	je	L_a_751
	movl	%ebp,%edi
L_a_751:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_752
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a021:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_752:
	cmpl	$48,%edx
	jne	L_a_755
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a022:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_755:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_758
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a023:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_758:
	cmpl	$3,16-16(%esp)
	jne	L_a_761
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a024:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_761:
	andl	$4,%esi
	jne	L_a_764
	addl	%edi,%ebx
L_a_764:
	cmpl	$0,16-16(%esp)
	je	L_a_765
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_765:
	testl	%esi,%esi
	je	L_a_768
	addl	%edi,%ebx
L_a_768:
	addl	%ebp,%ebx
	jmp	L_a_789
	.align	2,0x90
L_a_749:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ebx
L_a_789:
	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_792
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_792:
	xorl	%esi,%esi
	testl	%edx,%edx
	je	L_a_771
	movl	$255,%esi
L_a_771:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movl	%esi,%ecx
	movb	%cl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a015:
	ret

FUNC(op_5ef8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a004:
	rolw	$8,%si
	movl	%esi,%eax
	xorl	%edx,%edx
	movswl	%ax,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_822
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_822:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_801
	movl	$255,%ecx
L_a_801:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a026:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a016:
	ret

FUNC(op_5ef9)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movl	0x2164334A+2(%eax),%ebx
RR2_a005:
	bswapl	%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_852
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_852:
	xorl	%ecx,%ecx
	testl	%edx,%edx
	je	L_a_831
	movl	$255,%ecx
L_a_831:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a027:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a017:
	ret

FUNC(op_5efa)

	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_881
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_881:
	testl	%edx,%edx
	je	L_a_861
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a028:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a018:
	ret
	.align	2,0x90
L_a_861:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a019:
	ret

FUNC(op_5efb)

	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_910
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_910:
	testl	%edx,%edx
	je	L_a_890
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a030:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a020:
	ret
	.align	2,0x90
L_a_890:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a031:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a021:
	ret

FUNC(op_5efc)

	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_938
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_938:
	testl	%edx,%edx
	je	L_a_918
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a032:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a022:
	ret
	.align	2,0x90
L_a_918:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a033:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a023:
	ret

FUNC(op_5fc0)

	movl	%eax,%ebx
	xorl	%ecx,%ecx
	andl	$7,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_968
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_969
L_a_968:
	movl	$1,%ecx
L_a_969:
	xorl	%eax,%eax
	testl	%ecx,%ecx
	je	L_a_946
	movl	$255,%eax
L_a_946:
	movb	%al,GLOBL(regs)(,%ebx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a034:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a024:
	ret

FUNC(op_5fc8)

	movl	%eax,%ebx
	xorl	%ecx,%ecx
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_a006:
	rolw	$8,%di
	movl	%edi,%eax
	movw	GLOBL(regs)(,%ebx,4),%si
	movl	%eax,%ebp
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_996
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_997
L_a_996:
	movl	$1,%ecx
L_a_997:
	testl	%ecx,%ecx
	jne	L_a_975
	movl	%esi,%edi
	decl	%edi
	movw	%di,GLOBL(regs)(,%ebx,4)
	testw	%si,%si
	je	L_a_975
	movl	GLOBL(regs)+88,%edx
	movswl	%bp,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_a_1000
	.align	2,0x90
L_a_975:
	addl	$4,GLOBL(regs)+88
L_a_1000:
	popl	%eax
	decl	%eax
	jl	JJ_a025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a025:
	ret

FUNC(op_5fd0)

	andl	$7,%eax
	pushl	%ebx
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	xorl	%ebx,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1025
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1026
L_a_1025:
	movl	$1,%ebx
L_a_1026:
	xorl	%ecx,%ecx
	testl	%ebx,%ebx
	je	L_a_1003
	movl	$255,%ecx
L_a_1003:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a036:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a026:
	ret

FUNC(op_5fd8)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	leal	8(%eax),%edx
	pushl	%ebx
	sall	$2,%edx
	movl	GLOBL(areg_byteinc)(,%eax,4),%eax
	movl	(%edx,%ecx),%ebx
	addl	%ebx,%eax
	movl	%eax,(%edx,%ecx)
	xorl	%esi,%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1054
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1055
L_a_1054:
	movl	$1,%esi
L_a_1055:
	xorl	%ecx,%ecx
	testl	%esi,%esi
	je	L_a_1032
	movl	$255,%ecx
L_a_1032:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a027:
	ret

FUNC(op_5fe0)

	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	leal	8(%edx),%eax
	pushl	%ebx
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edx,4),%edx
	movl	(%eax,%ecx),%ebx
	subl	%edx,%ebx
	movl	%ebx,(%eax,%ecx)
	xorl	%esi,%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1083
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1084
L_a_1083:
	movl	$1,%esi
L_a_1084:
	xorl	%ecx,%ecx
	testl	%esi,%esi
	je	L_a_1061
	movl	$255,%ecx
L_a_1061:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a038:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a028:
	ret

FUNC(op_5fe8)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_a007:
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(regs)(,%edx,4),%esi
	cwtl
	xorl	%ebx,%ebx
	addl	%eax,%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1113
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1114
L_a_1113:
	movl	$1,%ebx
L_a_1114:
	xorl	%ecx,%ecx
	testl	%ebx,%ebx
	je	L_a_1091
	movl	$255,%ecx
L_a_1091:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a039:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a029:
	ret

FUNC(op_5ff0)

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
RR0_a040:
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
	jne	L_a_1122
	movswl	%di,%edi
L_a_1122:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_1123
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_1124
	movl	%ebp,%ebx
L_a_1124:
	testl	$64,%esi
	je	L_a_1125
	movl	%ebp,%edi
L_a_1125:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_1126
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a041:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_1126:
	cmpl	$48,%edx
	jne	L_a_1129
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a042:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_1129:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_1132
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a043:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_1132:
	cmpl	$3,16-16(%esp)
	jne	L_a_1135
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a044:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_1135:
	andl	$4,%esi
	jne	L_a_1138
	addl	%edi,%ebx
L_a_1138:
	cmpl	$0,16-16(%esp)
	je	L_a_1139
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_1139:
	testl	%esi,%esi
	je	L_a_1142
	addl	%edi,%ebx
L_a_1142:
	addl	%ebp,%ebx
	jmp	L_a_1164
	.align	2,0x90
L_a_1123:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%ebx
L_a_1164:
	xorl	%esi,%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1167
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1168
L_a_1167:
	movl	$1,%esi
L_a_1168:
	xorl	%edi,%edi
	testl	%esi,%esi
	je	L_a_1145
	movl	$255,%edi
L_a_1145:
	movl	%ebx,%eax
	shrl	$14,%eax
	movl	%ebx,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movl	%edi,%ecx
	movb	%cl,(%edx,%eax)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a045:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a030:
	ret

FUNC(op_5ff8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_a008:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%ebx,%ebx
	movswl	%ax,%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1197
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1198
L_a_1197:
	movl	$1,%ebx
L_a_1198:
	xorl	%ecx,%ecx
	testl	%ebx,%ebx
	je	L_a_1175
	movl	$255,%ecx
L_a_1175:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a046:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a031:
	ret

FUNC(op_5ff9)

	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movl	0x2164334A+2(%eax),%esi
RR2_a009:
	bswapl	%esi
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1227
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1228
L_a_1227:
	movl	$1,%ebx
L_a_1228:
	xorl	%ecx,%ecx
	testl	%ebx,%ebx
	je	L_a_1205
	movl	$255,%ecx
L_a_1205:
	movl	%esi,%eax
	shrl	$14,%eax
	movl	%esi,%edx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a032:
	ret

FUNC(op_5ffa)

	xorl	%ecx,%ecx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1256
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1257
L_a_1256:
	movl	$1,%ecx
L_a_1257:
	testl	%ecx,%ecx
	je	L_a_1235
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a048:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a033:
	ret
	.align	2,0x90
L_a_1235:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a034:
	ret

FUNC(op_5ffb)

	xorl	%ecx,%ecx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1285
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1286
L_a_1285:
	movl	$1,%ecx
L_a_1286:
	testl	%ecx,%ecx
	je	L_a_1264
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a050:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a035:
	ret
	.align	2,0x90
L_a_1264:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a051:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a036:
	ret

FUNC(op_5ffc)

	xorl	%ecx,%ecx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_1313
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_1314
L_a_1313:
	movl	$1,%ecx
L_a_1314:
	testl	%ecx,%ecx
	je	L_a_1292
	movl	GLOBL(regs)+88,%eax
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a037:
	ret
	.align	2,0x90
L_a_1292:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a038:
	ret

FUNC(op_6000)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_a010:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a054:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a039:
	ret

FUNC(op_6001)

	movsbl	%al,%edx
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a040:
	ret

FUNC(op_60ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a011:
	bswapl	%edx
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a056:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a041:
	ret

FUNC(op_6200)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a012:
	rolw	$8,%ax
	testb	$65,regflags
	jne	L_a_1453
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a057:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a042:
	ret
	.align	2,0x90
L_a_1453:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a043:
	ret

FUNC(op_6201)

	movsbl	%al,%edx
	testb	$65,regflags
	jne	L_a_1481
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a044:
	ret
	.align	2,0x90
L_a_1481:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a060:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a045:
	ret

FUNC(op_62ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a013:
	bswapl	%edx
	testb	$65,regflags
	jne	L_a_1510
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a046:
	ret
	.align	2,0x90
L_a_1510:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a047:
	ret

FUNC(op_6300)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a014:
	rolw	$8,%ax
	testb	$65,regflags
	je	L_a_1539
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a063:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a048:
	ret
	.align	2,0x90
L_a_1539:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a049:
	ret

FUNC(op_6301)

	movsbl	%al,%edx
	testb	$65,regflags
	je	L_a_1567
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a050:
	ret
	.align	2,0x90
L_a_1567:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a066:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a051:
	ret

FUNC(op_63ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a015:
	bswapl	%edx
	testb	$65,regflags
	je	L_a_1596
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a067:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a052:
	ret
	.align	2,0x90
L_a_1596:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a068:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a053:
	ret

FUNC(op_6400)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a016:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_a_1625
	movswl	%cx,%eax
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a069:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a054:
	ret
	.align	2,0x90
L_a_1625:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a070:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a055:
	ret

FUNC(op_6401)

	movsbl	%al,%edx
	testb	$1,regflags
	sete	%al
	testb	$1,%al
	je	L_a_1653
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a071:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a056:
	ret
	.align	2,0x90
L_a_1653:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a072:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a057:
	ret

FUNC(op_64ff)

	movl	GLOBL(regs)+88,%edx
	testb	$1,regflags
	sete	%al
	movl	0x2164334A+2(%edx),%ecx
RR2_a017:
	bswapl	%ecx
	testb	$1,%al
	je	L_a_1682
	leal	2(%ecx,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a073:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a058:
	ret
	.align	2,0x90
L_a_1682:
	addl	$6,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a074:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a059:
	ret

FUNC(op_6500)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a018:
	rolw	$8,%ax
	testb	$1,regflags
	je	L_a_1711
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a075:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a060:
	ret
	.align	2,0x90
L_a_1711:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a061:
	ret

FUNC(op_6501)

	movsbl	%al,%edx
	testb	$1,regflags
	je	L_a_1739
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a062:
	ret
	.align	2,0x90
L_a_1739:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a063:
	ret

FUNC(op_65ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a019:
	bswapl	%edx
	testb	$1,regflags
	je	L_a_1768
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a064:
	ret
	.align	2,0x90
L_a_1768:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a065:
	ret

FUNC(op_6600)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a020:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_a_1797
	movswl	%cx,%eax
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a066:
	ret
	.align	2,0x90
L_a_1797:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a067:
	ret

FUNC(op_6601)

	movsbl	%al,%edx
	testb	$64,regflags
	sete	%al
	testb	$1,%al
	je	L_a_1825
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a068:
	ret
	.align	2,0x90
L_a_1825:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a069:
	ret

FUNC(op_66ff)

	movl	GLOBL(regs)+88,%edx
	testb	$64,regflags
	sete	%al
	movl	0x2164334A+2(%edx),%ecx
RR2_a021:
	bswapl	%ecx
	testb	$1,%al
	je	L_a_1854
	leal	2(%ecx,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a085:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a070:
	ret
	.align	2,0x90
L_a_1854:
	addl	$6,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a086:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a071:
	ret

FUNC(op_6700)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a022:
	rolw	$8,%ax
	testb	$64,regflags
	je	L_a_1883
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a087:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a072:
	ret
	.align	2,0x90
L_a_1883:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a073:
	ret

FUNC(op_6701)

	movsbl	%al,%edx
	testb	$64,regflags
	je	L_a_1911
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a089:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a074:
	ret
	.align	2,0x90
L_a_1911:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a075:
	ret

FUNC(op_67ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a023:
	bswapl	%edx
	testb	$64,regflags
	je	L_a_1940
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a076:
	ret
	.align	2,0x90
L_a_1940:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a092:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a077:
	ret

FUNC(op_6800)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a024:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_a_1969
	movswl	%cx,%eax
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a093:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a078:
	ret
	.align	2,0x90
L_a_1969:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a079:
	ret

FUNC(op_6801)

	movsbl	%al,%edx
	testb	$8,regflags+1
	sete	%al
	testb	$1,%al
	je	L_a_1997
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a080:
	ret
	.align	2,0x90
L_a_1997:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a081:
	ret

FUNC(op_68ff)

	movl	GLOBL(regs)+88,%edx
	testb	$8,regflags+1
	sete	%al
	movl	0x2164334A+2(%edx),%ecx
RR2_a025:
	bswapl	%ecx
	testb	$1,%al
	je	L_a_2026
	leal	2(%ecx,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a082:
	ret
	.align	2,0x90
L_a_2026:
	addl	$6,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a083:
	ret

FUNC(op_6900)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a026:
	rolw	$8,%ax
	testb	$8,regflags+1
	je	L_a_2055
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a084:
	ret
	.align	2,0x90
L_a_2055:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a085:
	ret

FUNC(op_6901)

	movsbl	%al,%edx
	testb	$8,regflags+1
	je	L_a_2083
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a086:
	ret
	.align	2,0x90
L_a_2083:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a087:
	ret

FUNC(op_69ff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a027:
	bswapl	%edx
	testb	$8,regflags+1
	je	L_a_2112
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a103:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a088:
	ret
	.align	2,0x90
L_a_2112:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a089:
	ret

FUNC(op_6a00)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a028:
	rolw	$8,%ax
	movl	%eax,%ecx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_a_2141
	movswl	%cx,%eax
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a090:
	ret
	.align	2,0x90
L_a_2141:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a091:
	ret

FUNC(op_6a01)

	movsbl	%al,%edx
	testb	$128,regflags
	sete	%al
	testb	$1,%al
	je	L_a_2169
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a092:
	ret
	.align	2,0x90
L_a_2169:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a093:
	ret

FUNC(op_6aff)

	movl	GLOBL(regs)+88,%edx
	testb	$128,regflags
	sete	%al
	movl	0x2164334A+2(%edx),%ecx
RR2_a029:
	bswapl	%ecx
	testb	$1,%al
	je	L_a_2198
	leal	2(%ecx,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a094:
	ret
	.align	2,0x90
L_a_2198:
	addl	$6,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a095:
	ret

FUNC(op_6b00)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a030:
	rolw	$8,%ax
	testb	$128,regflags
	je	L_a_2227
	cwtl
	leal	2(%eax,%edx),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a111:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a096:
	ret
	.align	2,0x90
L_a_2227:
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a097:
	ret

FUNC(op_6b01)

	movsbl	%al,%edx
	testb	$128,regflags
	je	L_a_2255
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%edx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a098:
	ret
	.align	2,0x90
L_a_2255:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a099:
	ret

FUNC(op_6bff)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_a031:
	bswapl	%edx
	testb	$128,regflags
	je	L_a_2284
	leal	2(%edx,%eax),%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a100:
	ret
	.align	2,0x90
L_a_2284:
	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a101:
	ret

FUNC(op_6c00)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_a032:
	rolw	$8,%ax
	movl	%eax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_a_2313
	movswl	%bx,%eax
	leal	2(%eax,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2314
	.align	2,0x90
L_a_2313:
	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2314:
	popl	%eax
	decl	%eax
	jl	JJ_a102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a102:
	ret

FUNC(op_6c01)

	movsbl	%al,%ecx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_a_2341
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%ecx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a103:
	ret
	.align	2,0x90
L_a_2341:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a104:
	ret

FUNC(op_6cff)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movl	GLOBL(regs)+88,%ecx
	movb	regflags+1,%al
	movl	0x2164334A+2(%ecx),%ebx
RR2_a033:
	shrb	$3,%al
	bswapl	%ebx
	andl	$1,%eax
	cmpl	%eax,%edx
	jne	L_a_2370
	leal	2(%ebx,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2371
	.align	2,0x90
L_a_2370:
	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2371:
	popl	%eax
	decl	%eax
	jl	JJ_a105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a105:
	ret

FUNC(op_6d00)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_a034:
	rolw	$8,%ax
	movl	%eax,%ebx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2399
	movswl	%bx,%eax
	leal	2(%eax,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2400
	.align	2,0x90
L_a_2399:
	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2400:
	popl	%eax
	decl	%eax
	jl	JJ_a106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a106:
	ret

FUNC(op_6d01)

	movsbl	%al,%ecx
	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2427
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%ecx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a107:
	ret
	.align	2,0x90
L_a_2427:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a108:
	ret

FUNC(op_6dff)

	movb	regflags,%al
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movl	GLOBL(regs)+88,%ecx
	movb	regflags+1,%al
	movl	0x2164334A+2(%ecx),%ebx
RR2_a035:
	shrb	$3,%al
	bswapl	%ebx
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2456
	leal	2(%ebx,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2457
	.align	2,0x90
L_a_2456:
	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2457:
	popl	%eax
	decl	%eax
	jl	JJ_a109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a109:
	ret

FUNC(op_6e00)

	xorl	%edx,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_a036:
	rolw	$8,%ax
	movl	%eax,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_2481
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_2481:
	testl	%edx,%edx
	je	L_a_2485
	movswl	%bx,%eax
	leal	2(%eax,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2486
	.align	2,0x90
L_a_2485:
	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2486:
	popl	%eax
	decl	%eax
	jl	JJ_a110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a110:
	ret

FUNC(op_6e01)

	movsbl	%al,%ecx
	xorl	%edx,%edx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_2509
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_2509:
	testl	%edx,%edx
	je	L_a_2513
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%ecx,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a111:
	ret
	.align	2,0x90
L_a_2513:
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a112:
	ret

FUNC(op_6eff)

	xorl	%edx,%edx
	movl	GLOBL(regs)+88,%ecx
	movb	regflags,%al
	movl	0x2164334A+2(%ecx),%ebx
RR2_a037:
	bswapl	%ebx
	testb	$64,%al
	jne	L_a_2538
	shrb	$7,%al
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	sete	%al
	xorl	%edx,%edx
	movb	%al,%dl
L_a_2538:
	testl	%edx,%edx
	je	L_a_2542
	leal	2(%ebx,%ecx),%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2543
	.align	2,0x90
L_a_2542:
	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
L_a_2543:
	popl	%eax
	decl	%eax
	jl	JJ_a113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a113:
	ret

FUNC(op_6f00)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a038:
	rolw	$8,%si
	movl	%esi,%eax
	xorl	%ecx,%ecx
	movl	%eax,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_2568
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2569
L_a_2568:
	movl	$1,%ecx
L_a_2569:
	testl	%ecx,%ecx
	je	L_a_2571
	movl	GLOBL(regs)+88,%edx
	movswl	%bx,%eax
	addl	$2,%edx
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+88
	jmp	L_a_2572
	.align	2,0x90
L_a_2571:
	addl	$4,GLOBL(regs)+88
L_a_2572:
	popl	%eax
	decl	%eax
	jl	JJ_a114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a114:
	ret

FUNC(op_6f01)

	xorl	%ecx,%ecx
	movsbl	%al,%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_2596
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2597
L_a_2596:
	movl	$1,%ecx
L_a_2597:
	testl	%ecx,%ecx
	je	L_a_2599
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%ebx,%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2600
	.align	2,0x90
L_a_2599:
	addl	$2,GLOBL(regs)+88
L_a_2600:
	popl	%eax
	decl	%eax
	jl	JJ_a115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a115:
	ret

FUNC(op_6fff)

	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movl	0x2164334A+2(%eax),%ebx
RR2_a039:
	bswapl	%ebx
	movb	regflags,%al
	testb	$64,%al
	jne	L_a_2625
	shrb	$7,%al
	xorl	%edx,%edx
	movb	%al,%dl
	movb	regflags+1,%al
	shrb	$3,%al
	andl	$1,%eax
	cmpl	%eax,%edx
	je	L_a_2626
L_a_2625:
	movl	$1,%ecx
L_a_2626:
	testl	%ecx,%ecx
	je	L_a_2628
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	addl	%ebx,%eax
	movl	%eax,GLOBL(regs)+88
	jmp	L_a_2629
	.align	2,0x90
L_a_2628:
	addl	$6,GLOBL(regs)+88
L_a_2629:
	popl	%eax
	decl	%eax
	jl	JJ_a116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a116:
	ret

FUNC(op_8030)

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
RR0_a132:
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
	jne	L_a_2668
	movswl	%di,%edi
L_a_2668:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2669
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2670
	movl	%ebp,%ebx
L_a_2670:
	testl	$64,%esi
	je	L_a_2671
	movl	%ebp,%edi
L_a_2671:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2672
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a133:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2672:
	cmpl	$48,%edx
	jne	L_a_2675
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a134:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2675:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_2678
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a135:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2678:
	cmpl	$3,16-16(%esp)
	jne	L_a_2681
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a136:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2681:
	andl	$4,%esi
	jne	L_a_2684
	addl	%edi,%ebx
L_a_2684:
	cmpl	$0,16-16(%esp)
	je	L_a_2685
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_2685:
	testl	%esi,%esi
	je	L_a_2688
	addl	%edi,%ebx
L_a_2688:
	leal	(%ebp,%ebx),%edx
	jmp	L_a_2689
	.align	2,0x90
L_a_2669:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_a_2689:
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
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a117:
	ret

FUNC(op_803b)

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
RR0_a138:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_a_2723
	movswl	%di,%edi
L_a_2723:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2724
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2725
	movl	%ebp,%ebx
L_a_2725:
	testl	$64,%esi
	je	L_a_2726
	movl	%ebp,%edi
L_a_2726:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2727
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a139:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2727:
	cmpl	$48,%edx
	jne	L_a_2730
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a140:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2730:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_2733
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a141:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2733:
	cmpl	$3,16-16(%esp)
	jne	L_a_2736
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a142:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2736:
	andl	$4,%esi
	jne	L_a_2739
	addl	%edi,%ebx
L_a_2739:
	cmpl	$0,16-16(%esp)
	je	L_a_2740
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_2740:
	testl	%esi,%esi
	je	L_a_2743
	addl	%edi,%ebx
L_a_2743:
	leal	(%ebp,%ebx),%edx
	jmp	L_a_2744
	.align	2,0x90
L_a_2724:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_a_2744:
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
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a118
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a118:
	ret

FUNC(op_8070)

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
RR0_a144:
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
	jne	L_a_2793
	movswl	%di,%edi
L_a_2793:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2794
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2795
	movl	%ebp,%ebx
L_a_2795:
	testl	$64,%esi
	je	L_a_2796
	movl	%ebp,%edi
L_a_2796:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2797
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a145:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2797:
	cmpl	$48,%edx
	jne	L_a_2800
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a146:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2800:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_2803
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a147:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2803:
	cmpl	$3,16-16(%esp)
	jne	L_a_2806
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a148:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2806:
	andl	$4,%esi
	jne	L_a_2809
	addl	%edi,%ebx
L_a_2809:
	cmpl	$0,16-16(%esp)
	je	L_a_2810
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_2810:
	testl	%esi,%esi
	je	L_a_2813
	addl	%edi,%ebx
L_a_2813:
	leal	(%ebp,%ebx),%eax
	jmp	L_a_2814
	.align	2,0x90
L_a_2794:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_a_2814:
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
	orw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a119
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a119:
	ret

FUNC(op_807b)

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
RR0_a150:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_a_2855
	movswl	%di,%edi
L_a_2855:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2856
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2857
	movl	%ebp,%ebx
L_a_2857:
	testl	$64,%esi
	je	L_a_2858
	movl	%ebp,%edi
L_a_2858:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2859
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a151:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2859:
	cmpl	$48,%edx
	jne	L_a_2862
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a152:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2862:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_2865
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a153:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2865:
	cmpl	$3,16-16(%esp)
	jne	L_a_2868
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a154:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2868:
	andl	$4,%esi
	jne	L_a_2871
	addl	%edi,%ebx
L_a_2871:
	cmpl	$0,16-16(%esp)
	je	L_a_2872
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_2872:
	testl	%esi,%esi
	je	L_a_2875
	addl	%edi,%ebx
L_a_2875:
	leal	(%ebp,%ebx),%eax
	jmp	L_a_2876
	.align	2,0x90
L_a_2856:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_a_2876:
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
	orw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a120
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a120:
	ret

FUNC(op_80b0)

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
RR0_a156:
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
	jne	L_a_2928
	movswl	%di,%edi
L_a_2928:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2929
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2930
	movl	%ebp,%ebx
L_a_2930:
	testl	$64,%esi
	je	L_a_2931
	movl	%ebp,%edi
L_a_2931:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2932
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a157:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2932:
	cmpl	$48,%edx
	jne	L_a_2935
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a158:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2935:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_2938
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a159:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2938:
	cmpl	$3,16-16(%esp)
	jne	L_a_2941
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a160:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_2941:
	andl	$4,%esi
	jne	L_a_2944
	addl	%edi,%ebx
L_a_2944:
	cmpl	$0,16-16(%esp)
	je	L_a_2945
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_2945:
	testl	%esi,%esi
	je	L_a_2948
	addl	%edi,%ebx
L_a_2948:
	leal	(%ebp,%ebx),%eax
	jmp	L_a_2949
	.align	2,0x90
L_a_2929:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_a_2949:
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
	orl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a121
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a121:
	ret

FUNC(op_80bb)

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
RR0_a162:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_a_2990
	movswl	%di,%edi
L_a_2990:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_a_2991
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_a_2992
	movl	%ebp,%ebx
L_a_2992:
	testl	$64,%esi
	je	L_a_2993
	movl	%ebp,%edi
L_a_2993:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_a_2994
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_a163:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_a_2994:
	cmpl	$48,%edx
	jne	L_a_2997
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a164:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_a_2997:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_a_3000
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_a165:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_3000:
	cmpl	$3,16-16(%esp)
	jne	L_a_3003
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_a166:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_a_3003:
	andl	$4,%esi
	jne	L_a_3006
	addl	%edi,%ebx
L_a_3006:
	cmpl	$0,16-16(%esp)
	je	L_a_3007
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_a_3007:
	testl	%esi,%esi
	je	L_a_3010
	addl	%edi,%ebx
L_a_3010:
	leal	(%ebp,%ebx),%eax
	jmp	L_a_3011
	.align	2,0x90
L_a_2991:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_a_3011:
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
	orl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a122
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a122:
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


FUNC(op_6100)

	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a040:
	rolw	$8,%ax
	cwtl
	addl	$2,%eax
	addl	$4,%edx
	pushl	%eax
	pushl	%edx

	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0(%esp),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	movl	GLOBL(regs)+88,%eax
	addl	4(%esp),%eax
	movl	%eax,GLOBL(regs)+88

	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a123
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a123:
	ret

FUNC(op_6101)

	movsbl	%al,%eax
	addl	$2,%eax
	pushl	%eax
	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	pushl	%eax

	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0(%esp),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	movl	GLOBL(regs)+88,%eax
	addl	4(%esp),%eax
	movl	%eax,GLOBL(regs)+88

	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a124
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a124:
	ret

FUNC(op_61ff)

	movl	GLOBL(regs)+88,%edx
	movl	0x2164334A+2(%edx),%eax
RR2_a041:
	bswapl	%eax
	addl	$2,%eax
	addl	$6,%edx
	pushl	%eax
	pushl	%edx

	movl	GLOBL(regs)+60,%eax
	addl	$-4,%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	0(%esp),%ecx
	addl	GLOBL(W24)(%edx),%eax
	bswapl	%ecx
	movl	%ecx,(%eax)
	movl	GLOBL(regs)+88,%eax
	addl	4(%esp),%eax
	movl	%eax,GLOBL(regs)+88

	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a125
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a125:
	ret

FUNC(op_7000)

	movl	%eax,%edx
	movsbl	%dl,%eax
	shrl	$9,%edx
	andl	$7,%edx
	testl	%eax,%eax
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a126
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a126:
	ret

FUNC(op_8000)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%ecx
	movb	(%edx,%eax,4),%al
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a127
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a127:
	ret

FUNC(op_8010)

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
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a128
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a128:
	ret

FUNC(op_8018)

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
	orb	(%edi,%ebx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a129
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a129:
	ret

FUNC(op_8020)

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
	orb	(%edi,%ebx),%al
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
	jl	JJ_a130
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a130:
	ret

FUNC(op_8028)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a042:
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
	orb	(%ebx,%ecx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a131
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a131:
	ret

FUNC(op_8038)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_a043:
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
	orb	(%ebx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,(%ebx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a132
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a132:
	ret

FUNC(op_8039)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_a044:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	$GLOBL(regs),%edx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$28,%ebx
	movb	(%ecx,%eax),%al
	orb	(%ebx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,(%ebx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a133
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a133:
	ret

FUNC(op_803a)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%edx
	shrl	$7,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_a045:
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
	orb	(%ebx,%ecx),%al
	testb	%al,%al
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a134
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a134:
	ret

FUNC(op_803c)

	movl	%eax,%ecx
	movl	$GLOBL(regs),%edx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$28,%ecx
	movb	0x2164334A+3(%eax),%al
RR3_a000:
	orb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a135
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a135:
	ret

FUNC(op_8040)

	movl	%eax,%edx
	movl	%edx,%ecx
	andl	$7,%eax
	shrl	$7,%ecx
	movl	$GLOBL(regs),%edx
	andl	$28,%ecx
	movw	(%edx,%eax,4),%ax
	orw	(%ecx,%edx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a136
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a136:
	ret

FUNC(op_8050)

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
	orw	(%ecx,%edx),%ax
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a137
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a137:
	ret

FUNC(op_8058)

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
	orw	(%edi,%ebx),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a138
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a138:
	ret

FUNC(op_8060)

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
	orw	(%edi,%esi),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a139
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a139:
	ret

FUNC(op_8068)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a046:
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
	orw	(%ebx,%ecx),%ax
	testw	%ax,%ax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movw	%ax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a140
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a140:
	ret

FUNC(op_8078)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a047:
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
	jl	JJ_a141
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a141:
	ret

FUNC(op_8079)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_a048:
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
	orw	(%ecx,%eax),%dx
	testw	%dx,%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%dx,(%ecx,%eax)
	popl	%ebx
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a142
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a142:
	ret

FUNC(op_807a)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_a049:
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
	jl	JJ_a143
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a143:
	ret

FUNC(op_807c)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a050:
	rolw	$8,%si
	movl	%esi,%eax
	andl	$28,%ecx
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
	jl	JJ_a144
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a144:
	ret

FUNC(op_8080)

	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	movl	(%ecx,%eax,4),%eax
	orl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a145
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a145:
	ret

FUNC(op_8090)

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
	orl	(%edx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a146
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a146:
	ret

FUNC(op_8098)

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
	orl	(%edi,%ebx),%eax
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
	jl	JJ_a147
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a147:
	ret

FUNC(op_80a0)

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
	orl	(%edi,%esi),%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a148
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a148:
	ret

FUNC(op_80a8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a051:
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
	orl	(%ebx,%ecx),%eax
	testl	%eax,%eax
	pushfl
	popl	%edx
	movl	%edx,regflags

	movl	%eax,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a149
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a149:
	ret

FUNC(op_80b8)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_a052:
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
	orl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a150
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a150:
	ret

FUNC(op_80b9)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_a053:
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
	orl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a151
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a151:
	ret

FUNC(op_80ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_a054:
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
	orl	(%ecx,%edx),%eax
	testl	%eax,%eax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%eax,(%ecx,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_a152
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a152:
	ret

FUNC(op_80bc)

	movl	%eax,%edx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ecx
	movl	0x2164334A+2(%eax),%eax
RR2_a055:
	andl	$28,%edx
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
	jl	JJ_a153
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a153:
	ret

FUNC(op_80c0)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	movl	%edx,%esi
	movl	GLOBL(regs)+88,%ecx
	movl	$GLOBL(regs),%ebx
	andl	$28,%esi
	movw	(%ebx,%eax,4),%di
	movl	(%esi,%ebx),%ebp
	testw	%di,%di
	jne	L_a_3024
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_a_3025
	.align	2,0x90
L_a_3024:
	xorl	%eax,%eax
	movw	%di,%ax
	movl	%eax,16-16(%esp)
	movl	%ebp,%eax
	xorl	%edx,%edx
	divl	16-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ecx
	cmpl	$65535,%edi
	jbe	L_a_3027
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_a_3026
	.align	2,0x90
L_a_3027:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edi,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%esi,%ebx)
L_a_3026:
	addl	$2,GLOBL(regs)+88
L_a_3025:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a154
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a199:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a154:
	ret

FUNC(op_80d0)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%eax
	addl	$8,%eax
	movl	$GLOBL(regs),%esi
	xorl	%edx,%edx
	movb	2(%esi,%eax,4),%dl
	movl	%edx,16-16(%esp)
	xorl	%edx,%edx
	movw	(%esi,%eax,4),%dx
	shrl	$7,%ecx
	movl	16-16(%esp),%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(,%eax,4),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	GLOBL(regs)+88,%edi
	xorl	%edx,%edx
	movw	20-16(%esp),%dx
	movl	%edx,20-16(%esp)
	movl	%edx,%ebx
	movl	(%ecx,%esi),%ebp
	cmpw	$0,20-16(%esp)
	jne	L_a_3040
	pushl	%edi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_a_3041
	.align	2,0x90
L_a_3040:
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%eax,20-16(%esp)
	movl	%ebp,%eax
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ebx
	cmpl	$65535,%edi
	jbe	L_a_3043
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_a_3042
	.align	2,0x90
L_a_3043:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edi,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ecx,%esi)
L_a_3042:
	addl	$2,GLOBL(regs)+88
L_a_3041:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_a155
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_a200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_a155:
	ret

FUNC(Init020_0a)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_a000-4
	movl	%eax,RR0_a001-4
	movl	%eax,RR0_a002-4
	movl	%eax,RR0_a003-4
	movl	%eax,RR0_a004-4
	movl	%eax,RR0_a005-4
	movl	%eax,RR0_a006-4
	movl	%eax,RR0_a007-4
	movl	%eax,RR0_a008-4
	movl	%eax,RR0_a009-4
	movl	%eax,RR0_a010-4
	movl	%eax,RR0_a011-4
	movl	%eax,RR0_a012-4
	movl	%eax,RR0_a013-4
	movl	%eax,RR0_a014-4
	movl	%eax,RR0_a015-4
	movl	%eax,RR0_a016-4
	movl	%eax,RR0_a017-4
	movl	%eax,RR0_a018-4
	movl	%eax,RR0_a019-4
	movl	%eax,RR0_a020-4
	movl	%eax,RR0_a021-4
	movl	%eax,RR0_a022-4
	movl	%eax,RR0_a023-4
	movl	%eax,RR0_a024-4
	movl	%eax,RR0_a025-4
	movl	%eax,RR0_a026-4
	movl	%eax,RR0_a027-4
	movl	%eax,RR0_a028-4
	movl	%eax,RR0_a029-4
	movl	%eax,RR0_a030-4
	movl	%eax,RR0_a031-4
	movl	%eax,RR0_a032-4
	movl	%eax,RR0_a033-4
	movl	%eax,RR0_a034-4
	movl	%eax,RR0_a035-4
	movl	%eax,RR0_a036-4
	movl	%eax,RR0_a037-4
	movl	%eax,RR0_a038-4
	movl	%eax,RR0_a039-4
	movl	%eax,RR0_a040-4
	movl	%eax,RR0_a041-4
	movl	%eax,RR0_a042-4
	movl	%eax,RR0_a043-4
	movl	%eax,RR0_a044-4
	movl	%eax,RR0_a045-4
	movl	%eax,RR0_a046-4
	movl	%eax,RR0_a047-4
	movl	%eax,RR0_a048-4
	movl	%eax,RR0_a049-4
	movl	%eax,RR0_a050-4
	movl	%eax,RR0_a051-4
	movl	%eax,RR0_a052-4
	movl	%eax,RR0_a053-4
	movl	%eax,RR0_a054-4
	movl	%eax,RR0_a055-4
	movl	%eax,RR0_a056-4
	movl	%eax,RR0_a057-4
	movl	%eax,RR0_a058-4
	movl	%eax,RR0_a059-4
	movl	%eax,RR0_a060-4
	movl	%eax,RR0_a061-4
	movl	%eax,RR0_a062-4
	movl	%eax,RR0_a063-4
	movl	%eax,RR0_a064-4
	movl	%eax,RR0_a065-4
	movl	%eax,RR0_a066-4
	movl	%eax,RR0_a067-4
	movl	%eax,RR0_a068-4
	movl	%eax,RR0_a069-4
	movl	%eax,RR0_a070-4
	movl	%eax,RR0_a071-4
	movl	%eax,RR0_a072-4
	movl	%eax,RR0_a073-4
	movl	%eax,RR0_a074-4
	movl	%eax,RR0_a075-4
	movl	%eax,RR0_a076-4
	movl	%eax,RR0_a077-4
	movl	%eax,RR0_a078-4
	movl	%eax,RR0_a079-4
	movl	%eax,RR0_a080-4
	movl	%eax,RR0_a081-4
	movl	%eax,RR0_a082-4
	movl	%eax,RR0_a083-4
	movl	%eax,RR0_a084-4
	movl	%eax,RR0_a085-4
	movl	%eax,RR0_a086-4
	movl	%eax,RR0_a087-4
	movl	%eax,RR0_a088-4
	movl	%eax,RR0_a089-4
	movl	%eax,RR0_a090-4
	movl	%eax,RR0_a091-4
	movl	%eax,RR0_a092-4
	movl	%eax,RR0_a093-4
	movl	%eax,RR0_a094-4
	movl	%eax,RR0_a095-4
	movl	%eax,RR0_a096-4
	movl	%eax,RR0_a097-4
	movl	%eax,RR0_a098-4
	movl	%eax,RR0_a099-4
	movl	%eax,RR0_a100-4
	movl	%eax,RR0_a101-4
	movl	%eax,RR0_a102-4
	movl	%eax,RR0_a103-4
	movl	%eax,RR0_a104-4
	movl	%eax,RR0_a105-4
	movl	%eax,RR0_a106-4
	movl	%eax,RR0_a107-4
	movl	%eax,RR0_a108-4
	movl	%eax,RR0_a109-4
	movl	%eax,RR0_a110-4
	movl	%eax,RR0_a111-4
	movl	%eax,RR0_a112-4
	movl	%eax,RR0_a113-4
	movl	%eax,RR0_a114-4
	movl	%eax,RR0_a115-4
	movl	%eax,RR0_a116-4
	movl	%eax,RR0_a117-4
	movl	%eax,RR0_a118-4
	movl	%eax,RR0_a119-4
	movl	%eax,RR0_a120-4
	movl	%eax,RR0_a121-4
	movl	%eax,RR0_a122-4
	movl	%eax,RR0_a123-4
	movl	%eax,RR0_a124-4
	movl	%eax,RR0_a125-4
	movl	%eax,RR0_a126-4
	movl	%eax,RR0_a127-4
	movl	%eax,RR0_a128-4
	movl	%eax,RR0_a129-4
	movl	%eax,RR0_a130-4
	movl	%eax,RR0_a131-4
	movl	%eax,RR0_a132-4
	movl	%eax,RR0_a133-4
	movl	%eax,RR0_a134-4
	movl	%eax,RR0_a135-4
	movl	%eax,RR0_a136-4
	movl	%eax,RR0_a137-4
	movl	%eax,RR0_a138-4
	movl	%eax,RR0_a139-4
	movl	%eax,RR0_a140-4
	movl	%eax,RR0_a141-4
	movl	%eax,RR0_a142-4
	movl	%eax,RR0_a143-4
	movl	%eax,RR0_a144-4
	movl	%eax,RR0_a145-4
	movl	%eax,RR0_a146-4
	movl	%eax,RR0_a147-4
	movl	%eax,RR0_a148-4
	movl	%eax,RR0_a149-4
	movl	%eax,RR0_a150-4
	movl	%eax,RR0_a151-4
	movl	%eax,RR0_a152-4
	movl	%eax,RR0_a153-4
	movl	%eax,RR0_a154-4
	movl	%eax,RR0_a155-4
	movl	%eax,RR0_a156-4
	movl	%eax,RR0_a157-4
	movl	%eax,RR0_a158-4
	movl	%eax,RR0_a159-4
	movl	%eax,RR0_a160-4
	movl	%eax,RR0_a161-4
	movl	%eax,RR0_a162-4
	movl	%eax,RR0_a163-4
	movl	%eax,RR0_a164-4
	movl	%eax,RR0_a165-4
	movl	%eax,RR0_a166-4
	movl	%eax,RR0_a167-4
	movl	%eax,RR0_a168-4
	movl	%eax,RR0_a169-4
	movl	%eax,RR0_a170-4
	movl	%eax,RR0_a171-4
	movl	%eax,RR0_a172-4
	movl	%eax,RR0_a173-4
	movl	%eax,RR0_a174-4
	movl	%eax,RR0_a175-4
	movl	%eax,RR0_a176-4
	movl	%eax,RR0_a177-4
	movl	%eax,RR0_a178-4
	movl	%eax,RR0_a179-4
	movl	%eax,RR0_a180-4
	movl	%eax,RR0_a181-4
	movl	%eax,RR0_a182-4
	movl	%eax,RR0_a183-4
	movl	%eax,RR0_a184-4
	movl	%eax,RR0_a185-4
	movl	%eax,RR0_a186-4
	movl	%eax,RR0_a187-4
	movl	%eax,RR0_a188-4
	movl	%eax,RR0_a189-4
	movl	%eax,RR0_a190-4
	movl	%eax,RR0_a191-4
	movl	%eax,RR0_a192-4
	movl	%eax,RR0_a193-4
	movl	%eax,RR0_a194-4
	movl	%eax,RR0_a195-4
	movl	%eax,RR0_a196-4
	movl	%eax,RR0_a197-4
	movl	%eax,RR0_a198-4
	movl	%eax,RR0_a199-4
	movl	%eax,RR0_a200-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_a000-4
	movl	%eax,RR2_a001-4
	movl	%eax,RR2_a002-4
	movl	%eax,RR2_a003-4
	movl	%eax,RR2_a004-4
	movl	%eax,RR2_a005-4
	movl	%eax,RR2_a006-4
	movl	%eax,RR2_a007-4
	movl	%eax,RR2_a008-4
	movl	%eax,RR2_a009-4
	movl	%eax,RR2_a010-4
	movl	%eax,RR2_a011-4
	movl	%eax,RR2_a012-4
	movl	%eax,RR2_a013-4
	movl	%eax,RR2_a014-4
	movl	%eax,RR2_a015-4
	movl	%eax,RR2_a016-4
	movl	%eax,RR2_a017-4
	movl	%eax,RR2_a018-4
	movl	%eax,RR2_a019-4
	movl	%eax,RR2_a020-4
	movl	%eax,RR2_a021-4
	movl	%eax,RR2_a022-4
	movl	%eax,RR2_a023-4
	movl	%eax,RR2_a024-4
	movl	%eax,RR2_a025-4
	movl	%eax,RR2_a026-4
	movl	%eax,RR2_a027-4
	movl	%eax,RR2_a028-4
	movl	%eax,RR2_a029-4
	movl	%eax,RR2_a030-4
	movl	%eax,RR2_a031-4
	movl	%eax,RR2_a032-4
	movl	%eax,RR2_a033-4
	movl	%eax,RR2_a034-4
	movl	%eax,RR2_a035-4
	movl	%eax,RR2_a036-4
	movl	%eax,RR2_a037-4
	movl	%eax,RR2_a038-4
	movl	%eax,RR2_a039-4
	movl	%eax,RR2_a040-4
	movl	%eax,RR2_a041-4
	movl	%eax,RR2_a042-4
	movl	%eax,RR2_a043-4
	movl	%eax,RR2_a044-4
	movl	%eax,RR2_a045-4
	movl	%eax,RR2_a046-4
	movl	%eax,RR2_a047-4
	movl	%eax,RR2_a048-4
	movl	%eax,RR2_a049-4
	movl	%eax,RR2_a050-4
	movl	%eax,RR2_a051-4
	movl	%eax,RR2_a052-4
	movl	%eax,RR2_a053-4
	movl	%eax,RR2_a054-4
	movl	%eax,RR2_a055-4
	incl	%eax
	movl	%eax,RR3_a000-4
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
