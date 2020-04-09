

FUNC(op_e3f0)

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
RR0_f000:
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
	jne	L_f_412
	movswl	%di,%edi
L_f_412:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_f_413
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_414
	movl	%ebp,%ebx
L_f_414:
	testl	$64,%esi
	je	L_f_415
	movl	%ebp,%edi
L_f_415:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_416
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_416:
	cmpl	$48,%edx
	jne	L_f_419
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_419:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_f_422
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_422:
	cmpl	$3,16-16(%esp)
	jne	L_f_425
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_425:
	andl	$4,%esi
	jne	L_f_428
	addl	%edi,%ebx
L_f_428:
	cmpl	$0,16-16(%esp)
	je	L_f_429
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_429:
	testl	%esi,%esi
	je	L_f_432
	addl	%edi,%ebx
L_f_432:
	leal	(%ebp,%ebx),%eax
	jmp	L_f_433
	.align	2,0x90
L_f_413:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_f_433:
	movl	%eax,%ebx
	shrl	$14,%ebx
	movl	%eax,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	movl	%edx,%eax
	addw	%dx,%dx
	andl	$32768,%eax
	testw	%dx,%dx
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	testl	%eax,%eax
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%dx,%ax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f000:
	ret

FUNC(op_e4d0)

	andl	$7,%eax
	pushl	%edi
	xorl	%edx,%edx
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%edi,%edi
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%di
	leal	0(,%edx,4),%ebp
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_471
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_471:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f006:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f001:
	ret

FUNC(op_e4d8)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	movl	(%edx,%ebx),%ecx
	movb	2(%edx,%ebx),%al
	movl	%ecx,%edi
	leal	0(,%eax,4),%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	$2,%ecx
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_478
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_478:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f007:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f002:
	ret

FUNC(op_e4e0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%ecx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_485
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_485:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f008:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f003:
	ret

FUNC(op_e4e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_f000:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebp
	movl	%eax,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_493
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_493:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f009:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f004:
	ret

FUNC(op_e4f0)

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
RR0_f010:
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
	jne	L_f_500
	movswl	%di,%edi
L_f_500:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_f_501
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_502
	movl	%ebp,%ebx
L_f_502:
	testl	$64,%esi
	je	L_f_503
	movl	%ebp,%edi
L_f_503:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_504
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f011:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_504:
	cmpl	$48,%edx
	jne	L_f_507
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f012:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_507:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_f_510
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f013:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_510:
	cmpl	$3,16-16(%esp)
	jne	L_f_513
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f014:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_513:
	andl	$4,%esi
	jne	L_f_516
	addl	%edi,%ebx
L_f_516:
	cmpl	$0,16-16(%esp)
	je	L_f_517
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_517:
	testl	%esi,%esi
	je	L_f_520
	addl	%edi,%ebx
L_f_520:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_521
	.align	2,0x90
L_f_501:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_f_521:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	movl	%ebx,%ebp
	shrw	$1,%bx
	andl	$1,%ebp
	testb	$1,regflags+4
	je	L_f_525
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_525:
	movb	regflags+4,%dl
	movl	%ebp,%eax
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	movl	%ebp,%ecx
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%esi),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f005:
	ret

FUNC(op_e4f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_f001:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebp
	movl	%eax,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_533
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_533:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f016:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f006:
	ret

FUNC(op_e4f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_f002:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%edx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	shrw	$1,%bx
	andl	$1,%ecx
	testb	$1,regflags+4
	je	L_f_541
	movl	$32768,%eax
	orl	%eax,%ebx
L_f_541:
	movb	regflags+4,%dl
	movb	%cl,%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f007:
	ret

FUNC(op_e5d0)

	andl	$7,%eax
	pushl	%edi
	xorl	%edx,%edx
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%edi,%edi
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%di
	leal	0(,%edx,4),%ebp
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_548
	orl	$1,%ebx
L_f_548:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f008:
	ret

FUNC(op_e5d8)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	movl	(%edx,%ebx),%ecx
	movb	2(%edx,%ebx),%al
	movl	%ecx,%edi
	leal	0(,%eax,4),%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	$2,%ecx
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_555
	orl	$1,%ebx
L_f_555:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f009:
	ret

FUNC(op_e5e0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%ecx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_562
	orl	$1,%ebx
L_f_562:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f020:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f010:
	ret

FUNC(op_e5e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_f003:
	rolw	$8,%si
	movl	%esi,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebp
	movl	%eax,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_570
	orl	$1,%ebx
L_f_570:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f021:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f011:
	ret

FUNC(op_e5f0)

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
RR0_f022:
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
	jne	L_f_577
	movswl	%di,%edi
L_f_577:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_f_578
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_579
	movl	%ebp,%ebx
L_f_579:
	testl	$64,%esi
	je	L_f_580
	movl	%ebp,%edi
L_f_580:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_581
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f023:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_581:
	cmpl	$48,%edx
	jne	L_f_584
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f024:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_584:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_f_587
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f025:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_587:
	cmpl	$3,16-16(%esp)
	jne	L_f_590
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f026:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_590:
	andl	$4,%esi
	jne	L_f_593
	addl	%edi,%ebx
L_f_593:
	cmpl	$0,16-16(%esp)
	je	L_f_594
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_594:
	testl	%esi,%esi
	je	L_f_597
	addl	%edi,%ebx
L_f_597:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_598
	.align	2,0x90
L_f_578:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_f_598:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%esi
	movl	%edx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebx
	movl	%ebx,%ebp
	addw	%bx,%bx
	andl	$32768,%ebp
	testb	$1,regflags+4
	je	L_f_602
	orl	$1,%ebx
L_f_602:
	movb	regflags+4,%dl
	testl	%ebp,%ebp
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ebp,%ebp
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%esi),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f027:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f012:
	ret

FUNC(op_e5f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_f004:
	rolw	$8,%si
	movl	%esi,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%ebp
	movl	%eax,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_610
	orl	$1,%ebx
L_f_610:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f028:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f013:
	ret

FUNC(op_e5f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_f005:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%edx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ebx
	movl	%ebx,%ecx
	addw	%bx,%bx
	andl	$32768,%ecx
	testb	$1,regflags+4
	je	L_f_618
	orl	$1,%ebx
L_f_618:
	movb	regflags+4,%dl
	testl	%ecx,%ecx
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%ecx,%ecx
	setne	%cl
	andb	$254,%al
	andb	$-2,%dl
	orb	%cl,%al
	orb	%cl,%dl
	movb	%al,regflags
	movb	%dl,regflags+4
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f014:
	ret

FUNC(op_e6f0)

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
RR0_f030:
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
	jne	L_f_683
	movswl	%di,%edi
L_f_683:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_f_684
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_685
	movl	%ebp,%ebx
L_f_685:
	testl	$64,%esi
	je	L_f_686
	movl	%ebp,%edi
L_f_686:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_687
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_687:
	cmpl	$48,%edx
	jne	L_f_690
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_690:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_f_693
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_693:
	cmpl	$3,16-16(%esp)
	jne	L_f_696
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_696:
	andl	$4,%esi
	jne	L_f_699
	addl	%edi,%ebx
L_f_699:
	cmpl	$0,16-16(%esp)
	je	L_f_700
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_700:
	testl	%esi,%esi
	je	L_f_703
	addl	%edi,%ebx
L_f_703:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_704
	.align	2,0x90
L_f_684:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_f_704:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edi
	movl	%edi,%edx
	shrw	$1,%di
	andl	$1,%edx
	je	L_f_708
	movl	$32768,%eax
	orl	%eax,%edi
L_f_708:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%di,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f015:
	ret

FUNC(op_e7f0)

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
RR0_f036:
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
	jne	L_f_805
	movswl	%di,%edi
L_f_805:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_f_806
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_807
	movl	%ebp,%ebx
L_f_807:
	testl	$64,%esi
	je	L_f_808
	movl	%ebp,%edi
L_f_808:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_809
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f037:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_809:
	cmpl	$48,%edx
	jne	L_f_812
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_812:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_f_815
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_815:
	cmpl	$3,16-16(%esp)
	jne	L_f_818
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_818:
	andl	$4,%esi
	jne	L_f_821
	addl	%edi,%ebx
L_f_821:
	cmpl	$0,16-16(%esp)
	je	L_f_822
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_822:
	testl	%esi,%esi
	je	L_f_825
	addl	%edi,%ebx
L_f_825:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_826
	.align	2,0x90
L_f_806:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_f_826:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edi
	movl	%edi,%edx
	addw	%di,%di
	andl	$32768,%edx
	je	L_f_830
	orl	$1,%edi
L_f_830:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%di,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f016:
	ret

FUNC(op_e8c0)

	subl	$4,%esp
	movl	%eax,%ebx
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_f006:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%edx
	testb	$8,%dh
	je	L_f_868
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	jmp	L_f_869
	.align	2,0x90
L_f_868:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
L_f_869:
	testb	$32,%dl
	je	L_f_870
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_873
	.align	2,0x90
L_f_870:
	movswl	%dx,%eax
L_f_873:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%edx
	andl	$31,%ecx
	movl	GLOBL(regs)(,%ebx,4),%ebx
	movl	$32,%eax
	sall	%cl,%ebx
	movl	%eax,%ecx
	subl	%edx,%ecx
	movl	%ebx,8-8(%esp)
	shrl	%cl,8-8(%esp)
	leal	-1(%edx),%eax
	movl	8-8(%esp),%esi
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	addl	$4,GLOBL(regs)+88
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	addl	$4,%esp
	movb	%al,regflags
	popl	%eax
	decl	%eax
	jl	JJ_f017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f042:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f017:
	ret

FUNC(op_e8d0)

	subl	$12,%esp
	andl	$7,%eax
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f007:
	rolw	$8,%cx
	movl	%ecx,%edx
	movl	(%esi,%eax,4),%ebx
	testb	$8,%dh
	je	L_f_876
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%esi,%eax,4),%esi
	jmp	L_f_877
	.align	2,0x90
L_f_876:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_877:
	testb	$32,%dl
	je	L_f_878
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_886
	.align	2,0x90
L_f_878:
	movswl	%dx,%eax
L_f_886:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_880
	orl	$-536870912,%eax
L_f_880:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-8(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-8(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,24-8(%esp)
	shrl	%cl,24-8(%esp)
	leal	-1(%ebp),%eax
	movl	24-8(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	addl	$4,GLOBL(regs)+88
	salb	$6,%dl
	andb	$-65,%al
	popl	%ebx
	orb	%dl,%al
	popl	%esi
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f018:
	ret

FUNC(op_e8e8)

	subl	$16,%esp
	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ebp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f008:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f000:
	rolw	$8,%ax
	cwtl
	movl	(%ebp,%edx,4),%esi
	addl	%eax,%esi
	testb	$8,%bh
	je	L_f_890
	movl	%ebx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebp,%eax,4),%eax
	movl	%eax,16-4(%esp)
	jmp	L_f_891
	.align	2,0x90
L_f_890:
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-4(%esp)
L_f_891:
	testb	$32,%bl
	je	L_f_892
	movl	%ebx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_900
	.align	2,0x90
L_f_892:
	movswl	%bx,%eax
L_f_900:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-4(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-4(%esp)
	jge	L_f_894
	orl	$-536870912,%eax
L_f_894:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-4(%esp)
	movl	%edx,%eax
	movl	16-4(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-4(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-4(%esp)
	shrl	%cl,28-4(%esp)
	leal	-1(%ebp),%eax
	movl	28-4(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	addl	$6,GLOBL(regs)+88
	salb	$6,%dl
	andb	$-65,%al
	popl	%ebx
	orb	%dl,%al
	popl	%esi
	movb	%al,regflags
	popl	%edi
	andb	$254,%al
	movb	%al,regflags
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f044:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f019:
	ret

FUNC(op_e8f0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f009:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f045:
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
	jne	L_f_905
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_905:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_906
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_907
	movl	%ebp,%ebx
L_f_907:
	testl	$64,%esi
	je	L_f_908
	movl	%ebp,16-16(%esp)
L_f_908:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_909
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f046:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_909:
	cmpl	$48,%edx
	jne	L_f_912
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f047:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_912:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_915
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f048:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_915:
	cmpl	$3,20-16(%esp)
	jne	L_f_918
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f049:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_918:
	andl	$4,%esi
	jne	L_f_921
	addl	16-16(%esp),%ebx
L_f_921:
	cmpl	$0,20-16(%esp)
	je	L_f_922
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_922:
	testl	%esi,%esi
	je	L_f_925
	addl	16-16(%esp),%ebx
L_f_925:
	addl	%ebp,%ebx
	jmp	L_f_926
	.align	2,0x90
L_f_906:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_926:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_928
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_929
	.align	2,0x90
L_f_928:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_929:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_930
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_938
	.align	2,0x90
L_f_930:
	movswl	32-16(%esp),%eax
L_f_938:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_932
	orl	$-536870912,%eax
L_f_932:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,20-16(%esp)
	shrl	%cl,20-16(%esp)
	leal	-1(%ebp),%eax
	movl	20-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f050:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f020:
	ret

FUNC(op_e8f8)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f010:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f001:
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%ebx
	testb	$8,%dh
	je	L_f_942
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_943
	.align	2,0x90
L_f_942:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_943:
	testb	$32,%dl
	je	L_f_944
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_952
	.align	2,0x90
L_f_944:
	movswl	%dx,%eax
L_f_952:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_946
	orl	$-536870912,%eax
L_f_946:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,24-16(%esp)
	shrl	%cl,24-16(%esp)
	leal	-1(%ebp),%eax
	movl	24-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	addl	$6,GLOBL(regs)+88
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f051:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f021:
	ret

FUNC(op_e8f9)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f011:
	rolw	$8,%ax
	movl	%eax,%ebp
	movl	0x2164334A+4(%edx),%ebx
RR4_f002:
	bswapl	%ebx
	testl	$2048,%ebp
	je	L_f_956
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_957
	.align	2,0x90
L_f_956:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_957:
	testl	$32,%ebp
	je	L_f_958
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_966
	.align	2,0x90
L_f_958:
	movswl	%bp,%eax
L_f_966:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_960
	orl	$-536870912,%eax
L_f_960:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,24-16(%esp)
	shrl	%cl,24-16(%esp)
	leal	-1(%ebp),%eax
	movl	24-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	addl	$8,GLOBL(regs)+88
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f022:
	ret

FUNC(op_e8fa)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f012:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_f003:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%ebx
	testl	$2048,%ebp
	je	L_f_971
	movl	%ebp,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_972
	.align	2,0x90
L_f_971:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_972:
	testl	$32,%ebp
	je	L_f_973
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_981
	.align	2,0x90
L_f_973:
	movswl	%bp,%eax
L_f_981:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_975
	orl	$-536870912,%eax
L_f_975:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,24-16(%esp)
	shrl	%cl,24-16(%esp)
	leal	-1(%ebp),%eax
	movl	24-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	addl	$6,GLOBL(regs)+88
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f023:
	ret

FUNC(op_e8fb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_f013:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_f054:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_987
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_987:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_988
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_989
	movl	24-16(%esp),%ebx
L_f_989:
	testl	$64,%esi
	je	L_f_990
	movl	24-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_990:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_991
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f055:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_f_991:
	cmpl	$48,%edx
	jne	L_f_994
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f056:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_994:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_f_997
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f057:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_997:
	cmpl	$3,%ebp
	jne	L_f_1000
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f058:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1000:
	andl	$4,%esi
	jne	L_f_1003
	addl	16-16(%esp),%ebx
L_f_1003:
	testl	%ebp,%ebp
	je	L_f_1004
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1004:
	testl	%esi,%esi
	je	L_f_1007
	addl	16-16(%esp),%ebx
L_f_1007:
	addl	24-16(%esp),%ebx
	jmp	L_f_1008
	.align	2,0x90
L_f_988:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_1008:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1010
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1011
	.align	2,0x90
L_f_1010:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1011:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1012
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1020
	.align	2,0x90
L_f_1012:
	movswl	32-16(%esp),%eax
L_f_1020:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1014
	orl	$-536870912,%eax
L_f_1014:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,20-16(%esp)
	shrl	%cl,20-16(%esp)
	leal	-1(%ebp),%eax
	movl	20-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f024:
	ret

FUNC(op_e9c0)

	subl	$4,%esp
	movl	%eax,%ebp
	andl	$7,%ebp
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_f014:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%esi
	testl	$2048,%esi
	je	L_f_1023
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ecx
	jmp	L_f_1024
	.align	2,0x90
L_f_1023:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
L_f_1024:
	testl	$32,%esi
	je	L_f_1025
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1028
	.align	2,0x90
L_f_1025:
	movswl	%si,%eax
L_f_1028:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%edx
	movl	$GLOBL(regs),%ebx
	andl	$31,%ecx
	movl	(%ebx,%ebp,4),%ebp
	movl	$32,%eax
	sall	%cl,%ebp
	movl	%eax,%ecx
	subl	%edx,%ecx
	movl	%ebp,16-16(%esp)
	shrl	%cl,16-16(%esp)
	leal	-1(%edx),%eax
	movl	16-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,(%ebx,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f060:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f025:
	ret

FUNC(op_e9d0)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f015:
	rolw	$8,%cx
	movl	%ecx,%edx
	addl	$8,%eax
	movl	%edx,%esi
	movl	$GLOBL(regs),%edx
	movl	(%edx,%eax,4),%ebx
	testl	$2048,%esi
	je	L_f_1031
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edx,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1032
	.align	2,0x90
L_f_1031:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1032:
	testl	$32,%esi
	je	L_f_1033
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1041
	.align	2,0x90
L_f_1033:
	movswl	%si,%eax
L_f_1041:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1035
	orl	$-536870912,%eax
L_f_1035:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-16(%esp)
	shrl	%cl,28-16(%esp)
	leal	-1(%ebp),%eax
	movl	28-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f026:
	ret

FUNC(op_e9e8)

	subl	$16,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ebp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f016:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f004:
	rolw	$8,%ax
	cwtl
	movl	(%ebp,%edx,4),%ebx
	addl	%eax,%ebx
	testl	$2048,%esi
	je	L_f_1045
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebp,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1046
	.align	2,0x90
L_f_1045:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1046:
	testl	$32,%esi
	je	L_f_1047
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1055
	.align	2,0x90
L_f_1047:
	movswl	%si,%eax
L_f_1055:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1049
	orl	$-536870912,%eax
L_f_1049:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-16(%esp)
	shrl	%cl,28-16(%esp)
	leal	-1(%ebp),%eax
	movl	28-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f027:
	ret

FUNC(op_e9f0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f017:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f063:
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
	jne	L_f_1060
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1060:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1061
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1062
	movl	%ebp,%ebx
L_f_1062:
	testl	$64,%esi
	je	L_f_1063
	movl	%ebp,16-16(%esp)
L_f_1063:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1064
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f064:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1064:
	cmpl	$48,%edx
	jne	L_f_1067
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f065:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1067:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1070
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f066:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1070:
	cmpl	$3,20-16(%esp)
	jne	L_f_1073
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f067:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1073:
	andl	$4,%esi
	jne	L_f_1076
	addl	16-16(%esp),%ebx
L_f_1076:
	cmpl	$0,20-16(%esp)
	je	L_f_1077
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1077:
	testl	%esi,%esi
	je	L_f_1080
	addl	16-16(%esp),%ebx
L_f_1080:
	addl	%ebp,%ebx
	jmp	L_f_1081
	.align	2,0x90
L_f_1061:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_1081:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1083
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1084
	.align	2,0x90
L_f_1083:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1084:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1085
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1093
	.align	2,0x90
L_f_1085:
	movswl	32-16(%esp),%eax
L_f_1093:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1087
	orl	$-536870912,%eax
L_f_1087:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,20-16(%esp)
	shrl	%cl,20-16(%esp)
	leal	-1(%ebp),%eax
	movl	20-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f068:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f028:
	ret

FUNC(op_e9f8)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f018:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f005:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%edx,%esi
	movswl	%ax,%ebx
	testl	$2048,%esi
	je	L_f_1097
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1098
	.align	2,0x90
L_f_1097:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1098:
	testl	$32,%esi
	je	L_f_1099
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1107
	.align	2,0x90
L_f_1099:
	movswl	%si,%eax
L_f_1107:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1101
	orl	$-536870912,%eax
L_f_1101:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-16(%esp)
	shrl	%cl,28-16(%esp)
	leal	-1(%ebp),%eax
	movl	28-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f069:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f029:
	ret

FUNC(op_e9f9)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f019:
	rolw	$8,%ax
	movl	%eax,%esi
	movl	0x2164334A+4(%edx),%ebx
RR4_f006:
	bswapl	%ebx
	testl	$2048,%esi
	je	L_f_1111
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1112
	.align	2,0x90
L_f_1111:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1112:
	testl	$32,%esi
	je	L_f_1113
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1121
	.align	2,0x90
L_f_1113:
	movswl	%si,%eax
L_f_1121:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1115
	orl	$-536870912,%eax
L_f_1115:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-16(%esp)
	shrl	%cl,28-16(%esp)
	leal	-1(%ebp),%eax
	movl	28-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$8,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f070:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f030:
	ret

FUNC(op_e9fa)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f020:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_f007:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%ebx
	testl	$2048,%esi
	je	L_f_1126
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1127
	.align	2,0x90
L_f_1126:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1127:
	testl	$32,%esi
	je	L_f_1128
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1136
	.align	2,0x90
L_f_1128:
	movswl	%si,%eax
L_f_1136:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1130
	orl	$-536870912,%eax
L_f_1130:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,28-16(%esp)
	shrl	%cl,28-16(%esp)
	leal	-1(%ebp),%eax
	movl	28-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f071:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f031:
	ret

FUNC(op_e9fb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_f021:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_f072:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1142
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1142:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1143
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1144
	movl	24-16(%esp),%ebx
L_f_1144:
	testl	$64,%esi
	je	L_f_1145
	movl	24-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1145:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1146
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f073:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_f_1146:
	cmpl	$48,%edx
	jne	L_f_1149
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f074:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1149:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_f_1152
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f075:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1152:
	cmpl	$3,%ebp
	jne	L_f_1155
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f076:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1155:
	andl	$4,%esi
	jne	L_f_1158
	addl	16-16(%esp),%ebx
L_f_1158:
	testl	%ebp,%ebp
	je	L_f_1159
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1159:
	testl	%esi,%esi
	je	L_f_1162
	addl	16-16(%esp),%ebx
L_f_1162:
	addl	24-16(%esp),%ebx
	jmp	L_f_1163
	.align	2,0x90
L_f_1143:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_1163:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1165
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1166
	.align	2,0x90
L_f_1165:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1166:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1167
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1175
	.align	2,0x90
L_f_1167:
	movswl	32-16(%esp),%eax
L_f_1175:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1169
	orl	$-536870912,%eax
L_f_1169:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	subl	%ebp,%eax
	orl	%edi,%edx
	movl	%eax,%ecx
	movl	%edx,20-16(%esp)
	shrl	%cl,20-16(%esp)
	leal	-1(%ebp),%eax
	movl	20-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	%edi,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f032:
	ret

FUNC(op_eac0)

	subl	$16,%esp
	andl	$7,%eax
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f022:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	testb	$8,%dh
	je	L_f_1178
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1179
	.align	2,0x90
L_f_1178:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
	movl	%esi,16-16(%esp)
L_f_1179:
	testb	$32,%dl
	je	L_f_1180
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1186
	.align	2,0x90
L_f_1180:
	movswl	%dx,%eax
L_f_1186:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	28-16(%esp),%ecx
	movl	16-16(%esp),%edi
	leal	0(,%ecx,4),%ebx
	andl	$31,%edi
	movl	GLOBL(regs)(%ebx),%esi
	movl	%edi,%ecx
	sall	%cl,%esi
	movl	$32,%ecx
	subl	%ebp,%ecx
	leal	-1(%ebp),%eax
	shrl	%cl,%esi
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	andb	$247,regflags+1
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	notl	%esi
	salb	$6,%dl
	andb	$-65,%al
	sall	%cl,%esi
	orb	%dl,%al
	movl	%edi,%ecx
	movb	%al,regflags
	movl	%esi,%edx
	andb	$254,%al
	shrl	%cl,%edx
	movb	%al,regflags
	testl	%edi,%edi
	je	L_f_1182
	movl	$32,%ecx
	subl	%edi,%ecx
	movl	$-1,%eax
	sall	%cl,%eax
	andl	GLOBL(regs)(%ebx),%eax
	orl	%edx,%eax
	jmp	L_f_1183
	.align	2,0x90
L_f_1182:
	movl	%edx,%eax
L_f_1183:
	movl	%eax,%edx
	movl	16-16(%esp),%eax
	andl	$31,%eax
	leal	(%ebp,%eax),%edi
	cmpl	$31,%edi
	jg	L_f_1184
	movl	$-1,%eax
	movl	%edi,%ecx
	movl	28-16(%esp),%esi
	shrl	%cl,%eax
	andl	GLOBL(regs)(,%esi,4),%eax
	orl	%eax,%edx
L_f_1184:
	movl	%edx,GLOBL(regs)(%ebx)
	addl	$4,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f033:
	ret

FUNC(op_ead0)

	subl	$32,%esp
	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f023:
	rolw	$8,%cx
	movl	$GLOBL(regs),%ebx
	movl	%ecx,%edx
	movl	(%ebx,%eax,4),%ebp
	testb	$8,%dh
	je	L_f_1189
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_1190
	.align	2,0x90
L_f_1189:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1190:
	testb	$32,%dl
	je	L_f_1191
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1204
	.align	2,0x90
L_f_1191:
	movswl	%dx,%eax
L_f_1204:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1193
	orl	$-536870912,%eax
L_f_1193:
	addl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	leal	4(%ebp),%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	notl	%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1198
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1198:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1201
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1201:
	addl	$4,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f034:
	ret

FUNC(op_eae8)

	subl	$32,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f024:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f008:
	rolw	$8,%ax
	cwtl
	movl	(%edi,%edx,4),%edx
	addl	%eax,%edx
	testb	$8,%bh
	je	L_f_1208
	movl	%ebx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edi,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1209
	.align	2,0x90
L_f_1208:
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1209:
	testb	$32,%bl
	je	L_f_1210
	movl	%ebx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1223
	.align	2,0x90
L_f_1210:
	movswl	%bx,%eax
L_f_1223:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1212
	orl	$-536870912,%eax
L_f_1212:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	movl	16-16(%esp),%esi
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%esi
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movl	%esi,16-16(%esp)
	movb	%al,regflags
	notl	%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	%esi,%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1217
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1217:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1220
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1220:
	addl	$6,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f035:
	ret

FUNC(op_eaf0)

	subl	$44,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,52-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f025:
	rolw	$8,%ax
	movw	%ax,56-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f081:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,48-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1228
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1228:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1229
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1230
	movl	%ebp,%ebx
L_f_1230:
	testl	$64,%esi
	je	L_f_1231
	movl	%ebp,16-16(%esp)
L_f_1231:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1232
	movl	48-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f082:
	rolw	$8,%ax
	movl	52-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1232:
	cmpl	$48,%edx
	jne	L_f_1235
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f083:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1235:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1238
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f084:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1238:
	cmpl	$3,20-16(%esp)
	jne	L_f_1241
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f085:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1241:
	andl	$4,%esi
	jne	L_f_1244
	addl	16-16(%esp),%ebx
L_f_1244:
	cmpl	$0,20-16(%esp)
	je	L_f_1245
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1245:
	testl	%esi,%esi
	je	L_f_1248
	addl	16-16(%esp),%ebx
L_f_1248:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_1249
	.align	2,0x90
L_f_1229:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_f_1249:
	movl	56-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1251
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1252
	.align	2,0x90
L_f_1251:
	movl	56-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1252:
	movl	56-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1253
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1266
	.align	2,0x90
L_f_1253:
	movswl	56-16(%esp),%eax
L_f_1266:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1255
	orl	$-536870912,%eax
L_f_1255:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%esi
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%esi,%ecx
	subl	%esi,%eax
	movl	16-16(%esp),%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	movl	44-16(%esp),%edi
	orb	%dl,%al
	addl	%esi,%edi
	movb	%al,regflags
	notl	%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	16-16(%esp),%edx
	sall	%cl,%eax
	movl	%esi,%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	movl	%edi,20-16(%esp)
	orl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_1260
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	16-16(%esp),%eax
	orl	%eax,%edx
L_f_1260:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1265
	leal	-32(%esi),%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%edi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%edi
	movb	%cl,(%edi,%eax)
L_f_1265:
	addl	$44,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f086:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f036:
	ret

FUNC(op_eaf8)

	subl	$32,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f026:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f009:
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%ebp
	testb	$8,%dh
	je	L_f_1270
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1271
	.align	2,0x90
L_f_1270:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1271:
	testb	$32,%dl
	je	L_f_1272
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1285
	.align	2,0x90
L_f_1272:
	movswl	%dx,%eax
L_f_1285:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1274
	orl	$-536870912,%eax
L_f_1274:
	addl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	leal	4(%ebp),%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	notl	%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1279
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1279:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1282
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1282:
	addl	$6,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f087:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f037:
	ret

FUNC(op_eaf9)

	subl	$32,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f027:
	rolw	$8,%ax
	movl	%eax,%edi
	movl	0x2164334A+4(%edx),%edx
RR4_f010:
	bswapl	%edx
	testl	$2048,%edi
	je	L_f_1289
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1290
	.align	2,0x90
L_f_1289:
	movl	%edi,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1290:
	testl	$32,%edi
	je	L_f_1291
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1304
	.align	2,0x90
L_f_1291:
	movswl	%di,%eax
L_f_1304:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1293
	orl	$-536870912,%eax
L_f_1293:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(R24)(%esi),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	notl	%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1298
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1298:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1301
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1301:
	addl	$8,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f038:
	ret

FUNC(op_ebc0)

	movl	%eax,%ebx
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f028:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%esi
	testl	$2048,%esi
	je	L_f_1307
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%edx
	jmp	L_f_1308
	.align	2,0x90
L_f_1307:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edx
	andl	$31,%edx
L_f_1308:
	testl	$32,%esi
	je	L_f_1309
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1314
	.align	2,0x90
L_f_1309:
	movswl	%si,%eax
L_f_1314:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%edi
	movl	%edx,%ecx
	movl	GLOBL(regs)(,%ebx,4),%ebx
	andl	$31,%ecx
	movl	$32,%eax
	sall	%cl,%ebx
	movl	%eax,%ecx
	subl	%edi,%ecx
	leal	-1(%edi),%eax
	shrl	%cl,%ebx
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1311
	cmpl	$32,%edi
	je	L_f_1311
	movl	$-1,%eax
	movl	%edi,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1311:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f089:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f039:
	ret

FUNC(op_ebd0)

	subl	$12,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f029:
	rolw	$8,%cx
	movl	%ecx,%edx
	addl	$8,%eax
	movl	%edx,%esi
	movl	$GLOBL(regs),%edx
	movl	(%edx,%eax,4),%ebx
	testl	$2048,%esi
	je	L_f_1317
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edx,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1318
	.align	2,0x90
L_f_1317:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1318:
	testl	$32,%esi
	je	L_f_1319
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1329
	.align	2,0x90
L_f_1319:
	movswl	%si,%eax
L_f_1329:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1321
	orl	$-536870912,%eax
L_f_1321:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1326
	cmpl	$32,%ebp
	je	L_f_1326
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1326:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f040:
	ret

FUNC(op_ebe8)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ebp
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f030:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f011:
	rolw	$8,%ax
	cwtl
	movl	(%ebp,%edx,4),%ebx
	addl	%eax,%ebx
	testl	$2048,%esi
	je	L_f_1333
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebp,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1334
	.align	2,0x90
L_f_1333:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1334:
	testl	$32,%esi
	je	L_f_1335
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1345
	.align	2,0x90
L_f_1335:
	movswl	%si,%eax
L_f_1345:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1337
	orl	$-536870912,%eax
L_f_1337:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1342
	cmpl	$32,%ebp
	je	L_f_1342
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1342:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f041:
	ret

FUNC(op_ebf0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f031:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f092:
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
	jne	L_f_1350
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1350:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1351
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1352
	movl	%ebp,%ebx
L_f_1352:
	testl	$64,%esi
	je	L_f_1353
	movl	%ebp,16-16(%esp)
L_f_1353:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1354
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f093:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1354:
	cmpl	$48,%edx
	jne	L_f_1357
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f094:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1357:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1360
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f095:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1360:
	cmpl	$3,20-16(%esp)
	jne	L_f_1363
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f096:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1363:
	andl	$4,%esi
	jne	L_f_1366
	addl	16-16(%esp),%ebx
L_f_1366:
	cmpl	$0,20-16(%esp)
	je	L_f_1367
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1367:
	testl	%esi,%esi
	je	L_f_1370
	addl	16-16(%esp),%ebx
L_f_1370:
	addl	%ebp,%ebx
	jmp	L_f_1371
	.align	2,0x90
L_f_1351:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_1371:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1373
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1374
	.align	2,0x90
L_f_1373:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1374:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1375
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1385
	.align	2,0x90
L_f_1375:
	movswl	32-16(%esp),%eax
L_f_1385:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1377
	orl	$-536870912,%eax
L_f_1377:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1382
	cmpl	$32,%ebp
	je	L_f_1382
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1382:
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f042:
	ret

FUNC(op_ebf8)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f032:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f012:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%edx,%esi
	movswl	%ax,%ebx
	testl	$2048,%esi
	je	L_f_1389
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1390
	.align	2,0x90
L_f_1389:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%edi
	andl	$31,%edi
	movl	%edi,16-16(%esp)
L_f_1390:
	testl	$32,%esi
	je	L_f_1391
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1401
	.align	2,0x90
L_f_1391:
	movswl	%si,%eax
L_f_1401:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1393
	orl	$-536870912,%eax
L_f_1393:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1398
	cmpl	$32,%ebp
	je	L_f_1398
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1398:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f043:
	ret

FUNC(op_ebf9)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f033:
	rolw	$8,%ax
	movl	%eax,%esi
	movl	0x2164334A+4(%edx),%ebx
RR4_f013:
	bswapl	%ebx
	testl	$2048,%esi
	je	L_f_1405
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1406
	.align	2,0x90
L_f_1405:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1406:
	testl	$32,%esi
	je	L_f_1407
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1417
	.align	2,0x90
L_f_1407:
	movswl	%si,%eax
L_f_1417:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1409
	orl	$-536870912,%eax
L_f_1409:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1414
	cmpl	$32,%ebp
	je	L_f_1414
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1414:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$8,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f044:
	ret

FUNC(op_ebfa)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f034:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_f014:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%ebx
	testl	$2048,%esi
	je	L_f_1422
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1423
	.align	2,0x90
L_f_1422:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1423:
	testl	$32,%esi
	je	L_f_1424
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1434
	.align	2,0x90
L_f_1424:
	movswl	%si,%eax
L_f_1434:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1426
	orl	$-536870912,%eax
L_f_1426:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,24-16(%esp)
	movl	%edx,%eax
	movl	16-16(%esp),%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	24-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1431
	cmpl	$32,%ebp
	je	L_f_1431
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1431:
	movl	%esi,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f045:
	ret

FUNC(op_ebfb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_f035:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_f101:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1440
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1440:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1441
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1442
	movl	24-16(%esp),%ebx
L_f_1442:
	testl	$64,%esi
	je	L_f_1443
	movl	24-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1443:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1444
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f102:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_f_1444:
	cmpl	$48,%edx
	jne	L_f_1447
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f103:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1447:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_f_1450
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f104:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1450:
	cmpl	$3,%ebp
	jne	L_f_1453
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f105:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1453:
	andl	$4,%esi
	jne	L_f_1456
	addl	16-16(%esp),%ebx
L_f_1456:
	testl	%ebp,%ebp
	je	L_f_1457
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1457:
	testl	%esi,%esi
	je	L_f_1460
	addl	16-16(%esp),%ebx
L_f_1460:
	addl	24-16(%esp),%ebx
	jmp	L_f_1461
	.align	2,0x90
L_f_1441:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_f_1461:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1463
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1464
	.align	2,0x90
L_f_1463:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1464:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1465
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1475
	.align	2,0x90
L_f_1465:
	movswl	32-16(%esp),%eax
L_f_1475:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1467
	orl	$-536870912,%eax
L_f_1467:
	addl	%eax,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%ebx),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%esi,%ebx
	shrl	$14,%eax
	andl	$7,%ebx
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%ebx,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%ebx
	subl	%ebp,%eax
	orl	%edx,%ebx
	movl	%eax,%ecx
	shrl	%cl,%ebx
	leal	-1(%ebp),%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$-2,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testb	$128,%al
	je	L_f_1472
	cmpl	$32,%ebp
	je	L_f_1472
	movl	$-1,%eax
	movl	%ebp,%ecx
	sall	%cl,%eax
	orl	%eax,%ebx
L_f_1472:
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f046:
	ret

FUNC(op_ecc0)

	subl	$12,%esp
	andl	$7,%eax
	movl	%eax,24-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f036:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	testb	$8,%dh
	je	L_f_1478
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1479
	.align	2,0x90
L_f_1478:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
	movl	%esi,16-16(%esp)
L_f_1479:
	testb	$32,%dl
	je	L_f_1480
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1486
	.align	2,0x90
L_f_1480:
	movswl	%dx,%eax
L_f_1486:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	24-16(%esp),%ecx
	movl	16-16(%esp),%edi
	movl	$32,%eax
	leal	0(,%ecx,4),%ebx
	andl	$31,%edi
	movl	GLOBL(regs)(%ebx),%esi
	movl	%edi,%ecx
	subl	%ebp,%eax
	sall	%cl,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	leal	-1(%ebp),%eax
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	andb	$247,regflags+1
	movb	%al,regflags
	testl	%edi,%edi
	je	L_f_1482
	movl	$32,%ecx
	subl	%edi,%ecx
	movl	$-1,%eax
	sall	%cl,%eax
	andl	GLOBL(regs)(%ebx),%eax
	jmp	L_f_1483
	.align	2,0x90
L_f_1482:
	movl	%edi,%eax
L_f_1483:
	movl	%eax,%edx
	movl	16-16(%esp),%eax
	andl	$31,%eax
	leal	(%ebp,%eax),%edi
	cmpl	$31,%edi
	jg	L_f_1484
	movl	$-1,%eax
	movl	%edi,%ecx
	movl	24-16(%esp),%esi
	shrl	%cl,%eax
	andl	GLOBL(regs)(,%esi,4),%eax
	orl	%eax,%edx
L_f_1484:
	movl	%edx,GLOBL(regs)(%ebx)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f047:
	ret

FUNC(op_ecd0)

	subl	$36,%esp
	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f037:
	rolw	$8,%cx
	movl	(%ebx,%eax,4),%eax
	movl	%ecx,%edx
	movl	%eax,16-16(%esp)
	testb	$8,%dh
	je	L_f_1489
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_1490
	.align	2,0x90
L_f_1489:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1490:
	testb	$32,%dl
	je	L_f_1491
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1504
	.align	2,0x90
L_f_1491:
	movswl	%dx,%eax
L_f_1504:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1493
	orl	$-536870912,%eax
L_f_1493:
	addl	%eax,16-16(%esp)
	movl	16-16(%esp),%eax
	shrl	$14,%eax
	movl	16-16(%esp),%edi
	andl	$1020,%eax
	andl	$65535,%edi
	movl	%eax,44-16(%esp)
	movl	%edi,40-16(%esp)
	movl	%edi,%eax
	movl	44-16(%esp),%ecx
	movl	16-16(%esp),%edx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,32-16(%esp)
	movl	%eax,36-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%esi,%edi
	movl	$8,%eax
	movl	%ecx,16-16(%esp)
	subl	%ebx,%eax
	movl	%ebx,%ecx
	movl	%eax,24-16(%esp)
	sall	%cl,%edi
	movl	16-16(%esp),%eax
	movl	24-16(%esp),%ecx
	shrl	%cl,%eax
	orl	%edi,%eax
	movl	%eax,48-16(%esp)
	movl	$32,%eax
	subl	%ebp,%eax
	movl	%eax,%ecx
	shrl	%cl,48-16(%esp)
	leal	-1(%ebp),%eax
	movl	48-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$247,regflags+1
	andb	$254,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	leal	(%ebp,%ebx),%edi
	movl	$-16777216,%eax
	movl	%esi,%edx
	sall	%cl,%eax
	movl	%edi,20-16(%esp)
	andl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_1498
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	%esi,%eax
	orl	%eax,%edx
L_f_1498:
	movl	40-16(%esp),%eax
	movl	44-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1501
	leal	-32(%ebx),%eax
	movl	36-16(%esp),%edi
	leal	(%eax,%ebp),%edx
	movl	$255,%eax
	movl	%edx,%ecx
	sarl	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%edx
	andb	%al,%cl
	movl	32-16(%esp),%edi
	movb	%cl,(%edi,%edx)
L_f_1501:
	addl	$4,GLOBL(regs)+88
	addl	$36,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f048:
	ret

FUNC(op_ece8)

	subl	$36,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f038:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f015:
	rolw	$8,%ax
	cwtl
	movl	(%edi,%edx,4),%edx
	addl	%eax,%edx
	testb	$8,%bh
	je	L_f_1508
	movl	%ebx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edi,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1509
	.align	2,0x90
L_f_1508:
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
	movl	%esi,16-16(%esp)
L_f_1509:
	testb	$32,%bl
	je	L_f_1510
	movl	%ebx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1523
	.align	2,0x90
L_f_1510:
	movswl	%bx,%eax
L_f_1523:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1512
	orl	$-536870912,%eax
L_f_1512:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,44-16(%esp)
	movl	%ecx,40-16(%esp)
	movl	%ecx,%eax
	movl	44-16(%esp),%esi
	addl	GLOBL(R24)(%esi),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,32-16(%esp)
	movl	%eax,36-16(%esp)
	movl	16-16(%esp),%ecx
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%ecx
	movzbl	(%edx,%eax),%edi
	movl	$8,%eax
	movl	%ebx,%esi
	subl	%ecx,%eax
	sall	%cl,%esi
	movl	%eax,24-16(%esp)
	movl	%ecx,16-16(%esp)
	movl	%edi,%eax
	movl	24-16(%esp),%ecx
	shrl	%cl,%eax
	orl	%esi,%eax
	movl	%eax,48-16(%esp)
	movl	$32,%eax
	subl	%ebp,%eax
	movl	%eax,%ecx
	shrl	%cl,48-16(%esp)
	leal	-1(%ebp),%eax
	movl	48-16(%esp),%esi
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	andb	$254,%al
	movl	16-16(%esp),%esi
	movb	%al,regflags
	addl	%ebp,%esi
	movl	$-16777216,%eax
	movl	%ebx,%edx
	sall	%cl,%eax
	movl	%esi,20-16(%esp)
	andl	%eax,%edx
	cmpl	$31,%esi
	jg	L_f_1517
	movl	$-1,%eax
	movl	%esi,%ecx
	shrl	%cl,%eax
	andl	%ebx,%eax
	orl	%eax,%edx
L_f_1517:
	movl	40-16(%esp),%eax
	movl	44-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1520
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	leal	(%eax,%ebp),%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	36-16(%esp),%esi
	sarl	%cl,%eax
	movl	%edi,%ecx
	movl	GLOBL(W24)(%esi),%edx
	andb	%al,%cl
	movl	32-16(%esp),%esi
	movb	%cl,(%esi,%edx)
L_f_1520:
	addl	$6,GLOBL(regs)+88
	addl	$36,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f049:
	ret

FUNC(op_ecf0)

	subl	$40,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,48-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f039:
	rolw	$8,%ax
	movw	%ax,52-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f110:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,44-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1528
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1528:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1529
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1530
	movl	%ebp,%ebx
L_f_1530:
	testl	$64,%esi
	je	L_f_1531
	movl	%ebp,16-16(%esp)
L_f_1531:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1532
	movl	44-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f111:
	rolw	$8,%ax
	movl	48-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1532:
	cmpl	$48,%edx
	jne	L_f_1535
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f112:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1535:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1538
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f113:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1538:
	cmpl	$3,20-16(%esp)
	jne	L_f_1541
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f114:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1541:
	andl	$4,%esi
	jne	L_f_1544
	addl	16-16(%esp),%ebx
L_f_1544:
	cmpl	$0,20-16(%esp)
	je	L_f_1545
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1545:
	testl	%esi,%esi
	je	L_f_1548
	addl	16-16(%esp),%ebx
L_f_1548:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_1549
	.align	2,0x90
L_f_1529:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_f_1549:
	movl	52-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1551
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	jmp	L_f_1552
	.align	2,0x90
L_f_1551:
	movl	52-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%esi
	andl	$31,%esi
L_f_1552:
	movl	52-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1553
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1566
	.align	2,0x90
L_f_1553:
	movswl	52-16(%esp),%eax
L_f_1566:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%esi,%eax
	sarl	$3,%eax
	testl	%esi,%esi
	jge	L_f_1555
	orl	$-536870912,%eax
L_f_1555:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%esi
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%ebx,%edi
	movl	$8,%eax
	movl	%ecx,16-16(%esp)
	subl	%esi,%eax
	movl	%esi,%ecx
	movl	%eax,24-16(%esp)
	sall	%cl,%edi
	movl	16-16(%esp),%eax
	movl	24-16(%esp),%ecx
	shrl	%cl,%eax
	orl	%edi,%eax
	movl	%eax,20-16(%esp)
	movl	$32,%eax
	subl	%ebp,%eax
	movl	%eax,%ecx
	shrl	%cl,20-16(%esp)
	leal	-1(%ebp),%eax
	movl	20-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$247,regflags+1
	andb	$254,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	leal	(%ebp,%esi),%edi
	movl	$-16777216,%eax
	movl	%ebx,%edx
	sall	%cl,%eax
	movl	%edi,20-16(%esp)
	andl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_1560
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	%ebx,%eax
	orl	%eax,%edx
L_f_1560:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1565
	leal	-32(%esi),%eax
	movl	32-16(%esp),%edi
	leal	(%eax,%ebp),%edx
	movl	$255,%eax
	movl	%edx,%ecx
	sarl	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%edx
	andb	%al,%cl
	movl	28-16(%esp),%edi
	movb	%cl,(%edi,%edx)
L_f_1565:
	addl	$40,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f050:
	ret

FUNC(op_ecf8)

	subl	$36,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f040:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f016:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,16-16(%esp)
	testb	$8,%dh
	je	L_f_1570
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1571
	.align	2,0x90
L_f_1570:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1571:
	testb	$32,%dl
	je	L_f_1572
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1585
	.align	2,0x90
L_f_1572:
	movswl	%dx,%eax
L_f_1585:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1574
	orl	$-536870912,%eax
L_f_1574:
	addl	%eax,16-16(%esp)
	movl	16-16(%esp),%eax
	shrl	$14,%eax
	movl	16-16(%esp),%edi
	andl	$1020,%eax
	andl	$65535,%edi
	movl	%eax,44-16(%esp)
	movl	%edi,40-16(%esp)
	movl	%edi,%eax
	movl	44-16(%esp),%ecx
	movl	16-16(%esp),%edx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,32-16(%esp)
	movl	%eax,36-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%esi,%edi
	movl	$8,%eax
	movl	%ecx,16-16(%esp)
	subl	%ebx,%eax
	movl	%ebx,%ecx
	movl	%eax,24-16(%esp)
	sall	%cl,%edi
	movl	16-16(%esp),%eax
	movl	24-16(%esp),%ecx
	shrl	%cl,%eax
	orl	%edi,%eax
	movl	%eax,48-16(%esp)
	movl	$32,%eax
	subl	%ebp,%eax
	movl	%eax,%ecx
	shrl	%cl,48-16(%esp)
	leal	-1(%ebp),%eax
	movl	48-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$247,regflags+1
	andb	$254,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	leal	(%ebp,%ebx),%edi
	movl	$-16777216,%eax
	movl	%esi,%edx
	sall	%cl,%eax
	movl	%edi,20-16(%esp)
	andl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_1579
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	%esi,%eax
	orl	%eax,%edx
L_f_1579:
	movl	40-16(%esp),%eax
	movl	44-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1582
	leal	-32(%ebx),%eax
	movl	36-16(%esp),%edi
	leal	(%eax,%ebp),%edx
	movl	$255,%eax
	movl	%edx,%ecx
	sarl	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%edx
	andb	%al,%cl
	movl	32-16(%esp),%edi
	movb	%cl,(%edi,%edx)
L_f_1582:
	addl	$6,GLOBL(regs)+88
	addl	$36,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f051:
	ret

FUNC(op_ecf9)

	subl	$36,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f041:
	rolw	$8,%ax
	movl	%eax,%esi
	movl	0x2164334A+4(%edx),%edx
RR4_f017:
	bswapl	%edx
	testl	$2048,%esi
	je	L_f_1589
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1590
	.align	2,0x90
L_f_1589:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1590:
	testl	$32,%esi
	je	L_f_1591
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1604
	.align	2,0x90
L_f_1591:
	movswl	%si,%eax
L_f_1604:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1593
	orl	$-536870912,%eax
L_f_1593:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,44-16(%esp)
	movl	%ecx,40-16(%esp)
	movl	%ecx,%eax
	movl	44-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%esi
	bswapl	%esi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,32-16(%esp)
	movl	%eax,36-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	movl	%esi,%edi
	movl	$8,%eax
	movl	%ecx,16-16(%esp)
	subl	%ebx,%eax
	movl	%ebx,%ecx
	movl	%eax,24-16(%esp)
	sall	%cl,%edi
	movl	16-16(%esp),%eax
	movl	24-16(%esp),%ecx
	shrl	%cl,%eax
	orl	%edi,%eax
	movl	%eax,48-16(%esp)
	movl	$32,%eax
	subl	%ebp,%eax
	movl	%eax,%ecx
	shrl	%cl,48-16(%esp)
	leal	-1(%ebp),%eax
	movl	48-16(%esp),%edi
	btl	%eax,%edi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%edi,%edi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$247,regflags+1
	andb	$254,%al
	movl	24-16(%esp),%ecx
	movb	%al,regflags
	leal	(%ebp,%ebx),%edi
	movl	$-16777216,%eax
	movl	%esi,%edx
	sall	%cl,%eax
	movl	%edi,20-16(%esp)
	andl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_1598
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	%esi,%eax
	orl	%eax,%edx
L_f_1598:
	movl	40-16(%esp),%eax
	movl	44-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1601
	leal	-32(%ebx),%eax
	movl	36-16(%esp),%edi
	leal	(%eax,%ebp),%edx
	movl	$255,%eax
	movl	%edx,%ecx
	sarl	%cl,%eax
	movb	16-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%edx
	andb	%al,%cl
	movl	32-16(%esp),%edi
	movb	%cl,(%edi,%edx)
L_f_1601:
	addl	$8,GLOBL(regs)+88
	addl	$36,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f052:
	ret

FUNC(op_edc0)

	subl	$4,%esp
	movl	%eax,%esi
	andl	$7,%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f042:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%ebp
	testl	$2048,%ebp
	je	L_f_1607
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1608
	.align	2,0x90
L_f_1607:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1608:
	testl	$32,%ebp
	je	L_f_1609
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1634
	.align	2,0x90
L_f_1609:
	movswl	%bp,%eax
L_f_1634:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%edx
	movl	%ebx,%eax
	andl	$31,%eax
	movl	GLOBL(regs)(,%esi,4),%esi
	movl	%eax,%ecx
	sall	%cl,%esi
	movl	$32,%eax
	subl	%edx,%eax
	movl	%eax,%ecx
	shrl	%cl,%esi
	leal	-1(%edx),%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,16-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1612
	.align	2,0x90
L_f_1613:
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1612
	testl	%esi,%eax
	jne	L_f_1612
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1613
L_f_1612:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f053:
	ret

FUNC(op_edd0)

	subl	$16,%esp
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f043:
	rolw	$8,%cx
	movl	%ecx,%edx
	addl	$8,%eax
	movl	%edx,%ebp
	movl	$GLOBL(regs),%edx
	movl	(%edx,%eax,4),%esi
	testl	$2048,%ebp
	je	L_f_1637
	movl	%ebp,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edx,%eax,4),%ebx
	jmp	L_f_1638
	.align	2,0x90
L_f_1637:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1638:
	testl	$32,%ebp
	je	L_f_1639
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1669
	.align	2,0x90
L_f_1639:
	movswl	%bp,%eax
L_f_1669:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1641
	orl	$-536870912,%eax
L_f_1641:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	28-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	16-16(%esp),%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	16-16(%esp),%eax
	decl	%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1647
	.align	2,0x90
L_f_1648:
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1647
	testl	%esi,%eax
	jne	L_f_1647
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1648
L_f_1647:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f054:
	ret

FUNC(op_ede8)

	subl	$16,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f044:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f018:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ebx
	cwtl
	movl	(%ebx,%edx,4),%esi
	addl	%eax,%esi
	testl	$2048,%ebp
	je	L_f_1673
	movl	%ebp,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_1674
	.align	2,0x90
L_f_1673:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1674:
	testl	$32,%ebp
	je	L_f_1675
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1705
	.align	2,0x90
L_f_1675:
	movswl	%bp,%eax
L_f_1705:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1677
	orl	$-536870912,%eax
L_f_1677:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	28-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	16-16(%esp),%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	16-16(%esp),%eax
	decl	%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1683
	.align	2,0x90
L_f_1684:
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1683
	testl	%esi,%eax
	jne	L_f_1683
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1684
L_f_1683:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f055:
	ret

FUNC(op_edf0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,28-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f045:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f121:
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
	jne	L_f_1710
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1710:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1711
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1712
	movl	%ebp,%ebx
L_f_1712:
	testl	$64,%esi
	je	L_f_1713
	movl	%ebp,16-16(%esp)
L_f_1713:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1714
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f122:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1714:
	cmpl	$48,%edx
	jne	L_f_1717
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f123:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1717:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1720
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f124:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1720:
	cmpl	$3,20-16(%esp)
	jne	L_f_1723
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f125:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1723:
	andl	$4,%esi
	jne	L_f_1726
	addl	16-16(%esp),%ebx
L_f_1726:
	cmpl	$0,20-16(%esp)
	je	L_f_1727
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1727:
	testl	%esi,%esi
	je	L_f_1730
	addl	16-16(%esp),%ebx
L_f_1730:
	leal	(%ebp,%ebx),%esi
	jmp	L_f_1731
	.align	2,0x90
L_f_1711:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%esi
L_f_1731:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1733
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1734
	.align	2,0x90
L_f_1733:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1734:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1735
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1765
	.align	2,0x90
L_f_1735:
	movswl	32-16(%esp),%eax
L_f_1765:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1737
	orl	$-536870912,%eax
L_f_1737:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	%ebp,%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	leal	-1(%ebp),%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1743
	.align	2,0x90
L_f_1744:
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1743
	testl	%esi,%eax
	jne	L_f_1743
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1744
L_f_1743:
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f056:
	ret

FUNC(op_edf8)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f046:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f019:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%edx,%ebp
	movswl	%ax,%esi
	testl	$2048,%ebp
	je	L_f_1769
	movl	%ebp,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1770
	.align	2,0x90
L_f_1769:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1770:
	testl	$32,%ebp
	je	L_f_1771
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1801
	.align	2,0x90
L_f_1771:
	movswl	%bp,%eax
L_f_1801:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1773
	orl	$-536870912,%eax
L_f_1773:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	28-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	16-16(%esp),%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	16-16(%esp),%eax
	decl	%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1779
	.align	2,0x90
L_f_1780:
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1779
	testl	%esi,%eax
	jne	L_f_1779
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1780
L_f_1779:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f057:
	ret

FUNC(op_edf9)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f047:
	rolw	$8,%ax
	movl	%eax,%ebp
	movl	0x2164334A+4(%edx),%esi
RR4_f020:
	bswapl	%esi
	testl	$2048,%ebp
	je	L_f_1805
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1806
	.align	2,0x90
L_f_1805:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1806:
	testl	$32,%ebp
	je	L_f_1807
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1837
	.align	2,0x90
L_f_1807:
	movswl	%bp,%eax
L_f_1837:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1809
	orl	$-536870912,%eax
L_f_1809:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	28-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	16-16(%esp),%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	16-16(%esp),%eax
	decl	%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1815
	.align	2,0x90
L_f_1816:
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1815
	testl	%esi,%eax
	jne	L_f_1815
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1816
L_f_1815:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$8,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f058:
	ret

FUNC(op_edfa)

	subl	$16,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f048:
	rolw	$8,%ax
	movl	%eax,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_f021:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%esi
	testl	$2048,%ebp
	je	L_f_1842
	movl	%ebp,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1843
	.align	2,0x90
L_f_1842:
	movl	%ebp,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1843:
	testl	$32,%ebp
	je	L_f_1844
	movl	%ebp,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1874
	.align	2,0x90
L_f_1844:
	movswl	%bp,%eax
L_f_1874:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1846
	orl	$-536870912,%eax
L_f_1846:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,28-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	28-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	16-16(%esp),%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	16-16(%esp),%eax
	decl	%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1852
	.align	2,0x90
L_f_1853:
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1852
	testl	%esi,%eax
	jne	L_f_1852
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1853
L_f_1852:
	movl	%ebp,%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f059:
	ret

FUNC(op_edfb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_f049:
	rolw	$8,%ax
	movw	%ax,32-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_f130:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,28-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1880
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1880:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1881
	movl	$0,24-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1882
	movl	24-16(%esp),%ebx
L_f_1882:
	testl	$64,%esi
	je	L_f_1883
	movl	24-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1883:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1884
	movl	28-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_f131:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_f_1884:
	cmpl	$48,%edx
	jne	L_f_1887
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f132:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1887:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_f_1890
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f133:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1890:
	cmpl	$3,%ebp
	jne	L_f_1893
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f134:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,24-16(%esp)
L_f_1893:
	andl	$4,%esi
	jne	L_f_1896
	addl	16-16(%esp),%ebx
L_f_1896:
	testl	%ebp,%ebp
	je	L_f_1897
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_1897:
	testl	%esi,%esi
	je	L_f_1900
	addl	16-16(%esp),%ebx
L_f_1900:
	movl	24-16(%esp),%edi
	leal	(%edi,%ebx),%esi
	jmp	L_f_1901
	.align	2,0x90
L_f_1881:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%esi
L_f_1901:
	movl	32-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_1903
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_1904
	.align	2,0x90
L_f_1903:
	movl	32-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1904:
	movl	32-16(%esp),%edi
	testl	$32,%edi
	je	L_f_1905
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1935
	.align	2,0x90
L_f_1905:
	movswl	32-16(%esp),%eax
L_f_1935:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1907
	orl	$-536870912,%eax
L_f_1907:
	addl	%eax,%esi
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	leal	4(%esi),%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	movl	%edx,%eax
	movl	%ebx,%esi
	shrl	$14,%eax
	andl	$7,%esi
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movb	(%edx,%eax),%dl
	movl	20-16(%esp),%edi
	movl	$8,%eax
	sall	%cl,%edi
	subl	%esi,%eax
	andl	$255,%edx
	movl	%eax,%ecx
	shrl	%cl,%edx
	movl	$32,%eax
	movl	%edi,%esi
	subl	%ebp,%eax
	orl	%edx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	leal	-1(%ebp),%eax
	movl	$1,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	testl	%edi,%esi
	setne	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movl	%edi,20-16(%esp)
	movb	%al,regflags
	andb	$247,regflags+1
	movl	%edi,%eax
	testl	%eax,%eax
	je	L_f_1913
	.align	2,0x90
L_f_1914:
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	je	L_f_1913
	testl	%esi,%eax
	jne	L_f_1913
	shrl	$1,%eax
	incl	%ebx
	testl	%eax,%eax
	jne	L_f_1914
L_f_1913:
	movl	32-16(%esp),%eax
	sarw	$12,%ax
	andl	$7,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f060:
	ret

FUNC(op_eec0)

	subl	$20,%esp
	andl	$7,%eax
	movl	%eax,32-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f050:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	testb	$8,%dh
	je	L_f_1938
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1939
	.align	2,0x90
L_f_1938:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
	movl	%ebx,16-16(%esp)
L_f_1939:
	testb	$32,%dl
	je	L_f_1940
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1946
	.align	2,0x90
L_f_1940:
	movswl	%dx,%eax
L_f_1946:
	decl	%eax
	andl	$31,%eax
	leal	1(%eax),%ebp
	movl	32-16(%esp),%ecx
	movl	16-16(%esp),%edi
	movl	$32,%ebx
	leal	-1(%ebp),%eax
	sall	$2,%ecx
	andl	$31,%edi
	movl	%ecx,20-16(%esp)
	subl	%ebp,%ebx
	movl	GLOBL(regs)(%ecx),%esi
	movl	%edi,%ecx
	movl	%ebx,28-16(%esp)
	sall	%cl,%esi
	movl	%ebx,%ecx
	andb	$247,regflags+1
	shrl	%cl,%esi
	movl	20-16(%esp),%ebx
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	movl	%ebx,24-16(%esp)
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	movl	$-1,%esi
	salb	$6,%dl
	andb	$-65,%al
	sall	%cl,%esi
	orb	%dl,%al
	movl	%edi,%ecx
	movb	%al,regflags
	movl	%esi,%edx
	andb	$254,%al
	shrl	%cl,%edx
	movb	%al,regflags
	testl	%edi,%edi
	je	L_f_1942
	movl	$32,%esi
	subl	%edi,%esi
	movl	$-1,%eax
	movl	%esi,%ecx
	sall	%cl,%eax
	movl	$GLOBL(regs),%ecx
	andl	(%ebx,%ecx),%eax
	orl	%edx,%eax
	jmp	L_f_1943
	.align	2,0x90
L_f_1942:
	movl	%edx,%eax
L_f_1943:
	movl	%eax,%edx
	movl	16-16(%esp),%eax
	andl	$31,%eax
	leal	(%ebp,%eax),%esi
	cmpl	$31,%esi
	jg	L_f_1944
	movl	$-1,%eax
	movl	%esi,%ecx
	movl	32-16(%esp),%ebx
	shrl	%cl,%eax
	andl	GLOBL(regs)(,%ebx,4),%eax
	orl	%eax,%edx
L_f_1944:
	movl	$GLOBL(regs),%ecx
	movl	24-16(%esp),%ebx
	movl	%edx,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f061:
	ret

FUNC(op_eed0)

	subl	$32,%esp
	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f051:
	rolw	$8,%cx
	movl	$GLOBL(regs),%ebx
	movl	%ecx,%edx
	movl	(%ebx,%eax,4),%ebp
	testb	$8,%dh
	je	L_f_1949
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_1950
	.align	2,0x90
L_f_1949:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_1950:
	testb	$32,%dl
	je	L_f_1951
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1964
	.align	2,0x90
L_f_1951:
	movswl	%dx,%eax
L_f_1964:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_1953
	orl	$-536870912,%eax
L_f_1953:
	addl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	leal	4(%ebp),%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-1,%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1958
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1958:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1961
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1961:
	addl	$4,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f062:
	ret

FUNC(op_eee8)

	subl	$32,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f052:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f022:
	rolw	$8,%ax
	cwtl
	movl	(%edi,%edx,4),%edx
	addl	%eax,%edx
	testb	$8,%bh
	je	L_f_1968
	movl	%ebx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%edi,%eax,4),%eax
	movl	%eax,16-16(%esp)
	jmp	L_f_1969
	.align	2,0x90
L_f_1968:
	movl	%ebx,%eax
	sarw	$6,%ax
	movl	%eax,%ecx
	andl	$31,%ecx
	movl	%ecx,16-16(%esp)
L_f_1969:
	testb	$32,%bl
	je	L_f_1970
	movl	%ebx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_1983
	.align	2,0x90
L_f_1970:
	movswl	%bx,%eax
L_f_1983:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	16-16(%esp),%eax
	sarl	$3,%eax
	cmpl	$0,16-16(%esp)
	jge	L_f_1972
	orl	$-536870912,%eax
L_f_1972:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	movl	16-16(%esp),%esi
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%esi
	movl	GLOBL(R24)(%eax),%eax
	movl	%esi,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movl	%esi,16-16(%esp)
	movb	%al,regflags
	movl	$-1,%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	%esi,%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_1977
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_1977:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_1980
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_1980:
	addl	$6,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f063:
	ret

FUNC(op_eef0)

	subl	$44,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,52-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f053:
	rolw	$8,%ax
	movw	%ax,56-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f139:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,48-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_1988
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_1988:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_1989
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_1990
	movl	%ebp,%ebx
L_f_1990:
	testl	$64,%esi
	je	L_f_1991
	movl	%ebp,16-16(%esp)
L_f_1991:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_1992
	movl	48-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f140:
	rolw	$8,%ax
	movl	52-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_1992:
	cmpl	$48,%edx
	jne	L_f_1995
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f141:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_1995:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_1998
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f142:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_1998:
	cmpl	$3,20-16(%esp)
	jne	L_f_2001
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f143:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_2001:
	andl	$4,%esi
	jne	L_f_2004
	addl	16-16(%esp),%ebx
L_f_2004:
	cmpl	$0,20-16(%esp)
	je	L_f_2005
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_2005:
	testl	%esi,%esi
	je	L_f_2008
	addl	16-16(%esp),%ebx
L_f_2008:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_2009
	.align	2,0x90
L_f_1989:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_f_2009:
	movl	56-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_2011
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2012
	.align	2,0x90
L_f_2011:
	movl	56-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2012:
	movl	56-16(%esp),%edi
	testl	$32,%edi
	je	L_f_2013
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2026
	.align	2,0x90
L_f_2013:
	movswl	56-16(%esp),%eax
L_f_2026:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2015
	orl	$-536870912,%eax
L_f_2015:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%esi
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%esi,%ecx
	subl	%esi,%eax
	movl	16-16(%esp),%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	movl	44-16(%esp),%edi
	orb	%dl,%al
	addl	%esi,%edi
	movb	%al,regflags
	movl	$-1,%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	16-16(%esp),%edx
	sall	%cl,%eax
	movl	%esi,%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	movl	%edi,20-16(%esp)
	orl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_2020
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	16-16(%esp),%eax
	orl	%eax,%edx
L_f_2020:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2025
	leal	-32(%esi),%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%edi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%edi
	movb	%cl,(%edi,%eax)
L_f_2025:
	addl	$44,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f064:
	ret

FUNC(op_eef8)

	subl	$32,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f054:
	rolw	$8,%dx
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f023:
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%ebp
	testb	$8,%dh
	je	L_f_2030
	movl	%edx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2031
	.align	2,0x90
L_f_2030:
	movl	%edx,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2031:
	testb	$32,%dl
	je	L_f_2032
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2045
	.align	2,0x90
L_f_2032:
	movswl	%dx,%eax
L_f_2045:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2034
	orl	$-536870912,%eax
L_f_2034:
	addl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,40-16(%esp)
	movl	%esi,36-16(%esp)
	movl	%esi,%eax
	movl	40-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	leal	4(%ebp),%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-1,%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_2039
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_2039:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2042
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_2042:
	addl	$6,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f065:
	ret

FUNC(op_eef9)

	subl	$32,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f055:
	rolw	$8,%ax
	movl	%eax,%edi
	movl	0x2164334A+4(%edx),%edx
RR4_f024:
	bswapl	%edx
	testl	$2048,%edi
	je	L_f_2049
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2050
	.align	2,0x90
L_f_2049:
	movl	%edi,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2050:
	testl	$32,%edi
	je	L_f_2051
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2064
	.align	2,0x90
L_f_2051:
	movswl	%di,%eax
L_f_2064:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2053
	orl	$-536870912,%eax
L_f_2053:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(R24)(%esi),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	$-1,%ebx
	andb	$254,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movl	24-16(%esp),%ecx
	movl	$-16777216,%eax
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	andb	$247,regflags+1
	shrl	%cl,%eax
	addl	44-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_2058
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_2058:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2061
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_2061:
	addl	$8,GLOBL(regs)+88
	addl	$32,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f066:
	ret

FUNC(op_efc0)

	subl	$20,%esp
	andl	$7,%eax
	movl	%eax,32-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_f056:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edi
	testl	$2048,%edi
	je	L_f_2067
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	movl	%eax,28-16(%esp)
	jmp	L_f_2068
	.align	2,0x90
L_f_2067:
	movl	%edi,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
	movl	%ebx,28-16(%esp)
L_f_2068:
	testl	$32,%edi
	je	L_f_2069
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2075
	.align	2,0x90
L_f_2069:
	movswl	%di,%eax
L_f_2075:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,16-16(%esp)
	movl	32-16(%esp),%ecx
	movl	28-16(%esp),%ebp
	sall	$2,%ecx
	movl	$GLOBL(regs),%ebx
	movl	%ecx,24-16(%esp)
	andl	$31,%ebp
	movl	(%ecx,%ebx),%esi
	movl	%ebp,%ecx
	sall	%cl,%esi
	movl	$32,%ecx
	movl	16-16(%esp),%eax
	subl	16-16(%esp),%ecx
	decl	%eax
	shrl	%cl,%esi
	btl	%eax,%esi
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%esi,%esi
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%edi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%esi
	sall	%cl,%esi
	movl	%ebp,%ecx
	movl	%esi,%edx
	movl	24-16(%esp),%edi
	shrl	%cl,%edx
	testl	%ebp,%ebp
	je	L_f_2071
	movl	$32,%ecx
	subl	%ebp,%ecx
	movl	$-1,%eax
	sall	%cl,%eax
	andl	GLOBL(regs)(%edi),%eax
	orl	%edx,%eax
	jmp	L_f_2072
	.align	2,0x90
L_f_2071:
	movl	%edx,%eax
L_f_2072:
	movl	%eax,%edx
	movl	28-16(%esp),%eax
	movl	16-16(%esp),%ebx
	andl	$31,%eax
	leal	(%ebx,%eax),%esi
	cmpl	$31,%esi
	jg	L_f_2073
	movl	$-1,%eax
	movl	%esi,%ecx
	movl	32-16(%esp),%ebx
	shrl	%cl,%eax
	andl	GLOBL(regs)(,%ebx,4),%eax
	orl	%eax,%edx
L_f_2073:
	movl	%edx,GLOBL(regs)(%edi)
	addl	$4,GLOBL(regs)+88
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f067:
	ret

FUNC(op_efd0)

	subl	$40,%esp
	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%edx
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%edx),%cx
RR2_f057:
	rolw	$8,%cx
	movl	%ecx,%edx
	movl	$GLOBL(regs),%ebx
	movw	%dx,24-16(%esp)
	movl	(%ebx,%eax,4),%edx
	movl	24-16(%esp),%esi
	testl	$2048,%esi
	je	L_f_2078
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_2079
	.align	2,0x90
L_f_2078:
	movl	24-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2079:
	movl	24-16(%esp),%ecx
	testb	$32,%cl
	je	L_f_2080
	movl	%ecx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2093
	.align	2,0x90
L_f_2080:
	movswl	24-16(%esp),%eax
L_f_2093:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,52-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2082
	orl	$-536870912,%eax
L_f_2082:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,48-16(%esp)
	movl	%esi,44-16(%esp)
	movl	%esi,%eax
	movl	48-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,36-16(%esp)
	movl	%eax,40-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,32-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	32-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	52-16(%esp),%eax
	movl	%eax,28-16(%esp)
	movl	%eax,%ecx
	movl	52-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	24-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	sall	%cl,%ebx
	movl	$-16777216,%eax
	movl	32-16(%esp),%ecx
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	shrl	%cl,%eax
	addl	52-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_2087
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_2087:
	movl	44-16(%esp),%eax
	movl	48-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2090
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	52-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	40-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	32-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	36-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_2090:
	addl	$4,GLOBL(regs)+88
	addl	$40,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f068:
	ret

FUNC(op_efe8)

	subl	$36,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f058:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_f025:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ebx
	cwtl
	movl	(%ebx,%edx,4),%edx
	addl	%eax,%edx
	testl	$2048,%esi
	je	L_f_2097
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	(%ebx,%eax,4),%ebx
	jmp	L_f_2098
	.align	2,0x90
L_f_2097:
	movl	%esi,%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2098:
	testl	$32,%esi
	je	L_f_2099
	movl	%esi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2112
	.align	2,0x90
L_f_2099:
	movswl	%si,%eax
L_f_2112:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,48-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2101
	orl	$-536870912,%eax
L_f_2101:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%ebp
	bswapl	%ebp
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	movl	GLOBL(R24)(%eax),%eax
	xorl	%ecx,%ecx
	movb	(%edx,%eax),%cl
	andl	$7,%ebx
	movl	%ecx,44-16(%esp)
	movl	$8,%eax
	movl	%ebx,%ecx
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%ebp,%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	44-16(%esp),%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	48-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	48-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	%esi,%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	sall	%cl,%ebx
	movl	$-16777216,%eax
	movl	24-16(%esp),%ecx
	movl	%ebp,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	movl	%ecx,%esi
	shrl	%cl,%eax
	addl	48-16(%esp),%esi
	orl	%eax,%edx
	cmpl	$31,%esi
	jg	L_f_2106
	movl	$-1,%eax
	movl	%esi,%ecx
	shrl	%cl,%eax
	andl	%ebp,%eax
	orl	%eax,%edx
L_f_2106:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,%esi
	jle	L_f_2109
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	48-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%edi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	44-16(%esp),%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%edi
	movb	%cl,(%edi,%eax)
L_f_2109:
	addl	$6,GLOBL(regs)+88
	addl	$36,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f069:
	ret

FUNC(op_eff0)

	subl	$44,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	movl	%ecx,52-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_f059:
	rolw	$8,%ax
	movw	%ax,56-16(%esp)
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_f150:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%eax
	movl	%ecx,48-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_f_2117
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_f_2117:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_f_2118
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_f_2119
	movl	%ebp,%ebx
L_f_2119:
	testl	$64,%esi
	je	L_f_2120
	movl	%ebp,16-16(%esp)
L_f_2120:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_f_2121
	movl	48-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_f151:
	rolw	$8,%ax
	movl	52-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_f_2121:
	cmpl	$48,%edx
	jne	L_f_2124
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f152:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_f_2124:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_f_2127
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_f153:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_2127:
	cmpl	$3,20-16(%esp)
	jne	L_f_2130
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_f154:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_f_2130:
	andl	$4,%esi
	jne	L_f_2133
	addl	16-16(%esp),%ebx
L_f_2133:
	cmpl	$0,20-16(%esp)
	je	L_f_2134
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_f_2134:
	testl	%esi,%esi
	je	L_f_2137
	addl	16-16(%esp),%ebx
L_f_2137:
	leal	(%ebp,%ebx),%edx
	jmp	L_f_2138
	.align	2,0x90
L_f_2118:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_f_2138:
	movl	56-16(%esp),%ecx
	testb	$8,%ch
	je	L_f_2140
	movl	%ecx,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2141
	.align	2,0x90
L_f_2140:
	movl	56-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2141:
	movl	56-16(%esp),%edi
	testl	$32,%edi
	je	L_f_2142
	movl	%edi,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2155
	.align	2,0x90
L_f_2142:
	movswl	56-16(%esp),%eax
L_f_2155:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,44-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2144
	orl	$-536870912,%eax
L_f_2144:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	%eax,40-16(%esp)
	movl	%ecx,36-16(%esp)
	movl	%ecx,%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(R24)(%edi),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,28-16(%esp)
	movl	%eax,32-16(%esp)
	movl	%ebx,%esi
	movl	GLOBL(R24)(%eax),%eax
	andl	$7,%esi
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%esi,%ecx
	subl	%esi,%eax
	movl	16-16(%esp),%edx
	movl	%eax,24-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	24-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	44-16(%esp),%eax
	movl	%eax,20-16(%esp)
	movl	%eax,%ecx
	movl	44-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	56-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	movl	44-16(%esp),%edi
	sall	%cl,%ebx
	movl	$-16777216,%eax
	movl	24-16(%esp),%ecx
	movl	16-16(%esp),%edx
	sall	%cl,%eax
	movl	%esi,%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	addl	%esi,%edi
	shrl	%cl,%eax
	movl	%edi,20-16(%esp)
	orl	%eax,%edx
	cmpl	$31,%edi
	jg	L_f_2149
	movl	$-1,%eax
	movl	%edi,%ecx
	shrl	%cl,%eax
	andl	16-16(%esp),%eax
	orl	%eax,%edx
L_f_2149:
	movl	36-16(%esp),%eax
	movl	40-16(%esp),%edi
	addl	GLOBL(W24)(%edi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2154
	leal	-32(%esi),%eax
	movl	44-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	32-16(%esp),%edi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	24-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%edi),%eax
	orb	%dl,%cl
	movl	28-16(%esp),%edi
	movb	%cl,(%edi,%eax)
L_f_2154:
	addl	$44,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f070:
	ret

FUNC(op_eff8)

	subl	$40,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f060:
	rolw	$8,%dx
	movw	%dx,24-16(%esp)
	xorl	%ecx,%ecx
	movw	0x2164334A+4(%eax),%cx
RR4_f026:
	rolw	$8,%cx
	movl	%ecx,%eax
	movswl	%ax,%edx
	movl	24-16(%esp),%esi
	testl	$2048,%esi
	je	L_f_2159
	movl	%esi,%eax
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2160
	.align	2,0x90
L_f_2159:
	movl	24-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2160:
	movl	24-16(%esp),%ecx
	testb	$32,%cl
	je	L_f_2161
	movl	%ecx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2174
	.align	2,0x90
L_f_2161:
	movswl	24-16(%esp),%eax
L_f_2174:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,52-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2163
	orl	$-536870912,%eax
L_f_2163:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,48-16(%esp)
	movl	%esi,44-16(%esp)
	movl	%esi,%eax
	movl	48-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,36-16(%esp)
	movl	%eax,40-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,32-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	32-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	52-16(%esp),%eax
	movl	%eax,28-16(%esp)
	movl	%eax,%ecx
	movl	52-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	24-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	sall	%cl,%ebx
	movl	$-16777216,%eax
	movl	32-16(%esp),%ecx
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	shrl	%cl,%eax
	addl	52-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_2168
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_2168:
	movl	44-16(%esp),%eax
	movl	48-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2171
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	52-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	40-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	32-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	36-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_2171:
	addl	$6,GLOBL(regs)+88
	addl	$40,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f071:
	ret

FUNC(op_eff9)

	subl	$40,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_f061:
	rolw	$8,%ax
	movw	%ax,24-16(%esp)
	movl	0x2164334A+4(%edx),%edx
RR4_f027:
	bswapl	%edx
	testb	$8,%ah
	je	L_f_2178
	sarw	$6,%ax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	jmp	L_f_2179
	.align	2,0x90
L_f_2178:
	movl	24-16(%esp),%eax
	sarw	$6,%ax
	movl	%eax,%ebx
	andl	$31,%ebx
L_f_2179:
	movl	24-16(%esp),%ecx
	testb	$32,%cl
	je	L_f_2180
	movl	%ecx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	jmp	L_f_2193
	.align	2,0x90
L_f_2180:
	movswl	24-16(%esp),%eax
L_f_2193:
	decl	%eax
	andl	$31,%eax
	incl	%eax
	movl	%eax,52-16(%esp)
	movl	%ebx,%eax
	sarl	$3,%eax
	testl	%ebx,%ebx
	jge	L_f_2182
	orl	$-536870912,%eax
L_f_2182:
	addl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%esi
	andl	$1020,%eax
	andl	$65535,%esi
	movl	%eax,48-16(%esp)
	movl	%esi,44-16(%esp)
	movl	%esi,%eax
	movl	48-16(%esp),%ecx
	addl	GLOBL(R24)(%ecx),%eax
	addl	$4,%edx
	movl	(%eax),%edi
	bswapl	%edi
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	%edx,36-16(%esp)
	movl	%eax,40-16(%esp)
	andl	$7,%ebx
	movl	GLOBL(R24)(%eax),%eax
	movl	%ebx,%ecx
	movzbl	(%edx,%eax),%ebp
	movl	$8,%eax
	movl	%ebx,16-16(%esp)
	subl	%ecx,%eax
	movl	%edi,%edx
	movl	%eax,32-16(%esp)
	sall	%cl,%edx
	movl	%ebp,%eax
	movl	32-16(%esp),%ecx
	movl	%edx,%ebx
	shrl	%cl,%eax
	orl	%eax,%ebx
	movl	$32,%eax
	subl	52-16(%esp),%eax
	movl	%eax,28-16(%esp)
	movl	%eax,%ecx
	movl	52-16(%esp),%eax
	shrl	%cl,%ebx
	decl	%eax
	btl	%eax,%ebx
	setb	%dl
	movb	regflags,%al
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	andb	$254,%al
	movb	%al,regflags
	movl	24-16(%esp),%eax
	sarw	$12,%ax
	andb	$247,regflags+1
	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%ebx
	sall	%cl,%ebx
	movl	$-16777216,%eax
	movl	32-16(%esp),%ecx
	movl	%edi,%edx
	sall	%cl,%eax
	movl	16-16(%esp),%ecx
	andl	%eax,%edx
	movl	%ebx,%eax
	shrl	%cl,%eax
	addl	52-16(%esp),%ecx
	orl	%eax,%edx
	movl	%ecx,20-16(%esp)
	cmpl	$31,%ecx
	jg	L_f_2187
	movl	$-1,%eax
	shrl	%cl,%eax
	andl	%edi,%eax
	orl	%eax,%edx
L_f_2187:
	movl	44-16(%esp),%eax
	movl	48-16(%esp),%esi
	addl	GLOBL(W24)(%esi),%eax
	bswapl	%edx
	movl	%edx,(%eax)
	cmpl	$32,20-16(%esp)
	jle	L_f_2190
	movl	16-16(%esp),%eax
	addl	$-32,%eax
	movl	52-16(%esp),%edx
	addl	%eax,%edx
	movl	$255,%eax
	movl	%edx,%ecx
	movl	40-16(%esp),%esi
	sarl	%cl,%eax
	movl	%ebx,%edx
	movl	32-16(%esp),%ecx
	andl	%ebp,%eax
	sall	%cl,%edx
	movl	%eax,20-16(%esp)
	movb	20-16(%esp),%cl
	movl	GLOBL(W24)(%esi),%eax
	orb	%dl,%cl
	movl	36-16(%esp),%esi
	movb	%cl,(%esi,%eax)
L_f_2190:
	addl	$8,GLOBL(regs)+88
	addl	$40,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f072:
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


FUNC(op_e3d8)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	movl	$GLOBL(regs),%ebp
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movzbl	2(%edx,%ebp),%esi
	movl	(%edx,%ebp),%edi
	sall	$2,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	(%edx,%ebp),%ecx
	addl	$2,%ecx
	movl	%eax,%ebx
	movl	%ecx,(%edx,%ebp)
	movl	%ebx,%eax
	addw	%bx,%bx
	andl	$32768,%eax
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%bx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f073:
	ret

FUNC(op_e3e0)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ebp
	sall	$2,%edx
	movl	(%edx,%ebp),%ecx
	addl	$-2,%ecx
	movl	%ecx,%esi
	movl	%ecx,16-16(%esp)
	shrl	$14,%esi
	movl	%ecx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	movl	%eax,%ebx
	movl	%ecx,(%edx,%ebp)
	movl	%ebx,%eax
	addw	%bx,%bx
	andl	$32768,%eax
	testw	%bx,%bx
	pushfl
	popl	%edx
	movl	%edx,regflags

	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%bx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_f074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f074:
	ret

FUNC(op_e3e8)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f062:
	rolw	$8,%dx
	movswl	%dx,%edx
	addl	GLOBL(regs)(,%ecx,4),%edx
	movl	%edx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%edx
	movl	GLOBL(R24)(%esi),%eax
	addl	%edx,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%eax
	addw	%cx,%cx
	andl	$32768,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	testl	%eax,%eax
	setne	%bl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f075:
	ret

FUNC(op_e3f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_f063:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%edx
	movl	GLOBL(R24)(%esi),%eax
	addl	%edx,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%eax
	addw	%cx,%cx
	andl	$32768,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	testl	%eax,%eax
	setne	%bl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f076:
	ret

FUNC(op_e3f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_f064:
	bswapl	%edx
	movl	%edx,%esi
	shrl	$14,%esi
	andl	$1020,%esi
	andl	$65535,%edx
	movl	GLOBL(R24)(%esi),%eax
	addl	%edx,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%eax
	addw	%cx,%cx
	andl	$32768,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	testl	%eax,%eax
	setne	%bl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%bl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edx
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f077:
	ret

FUNC(op_e6d0)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%esi,%esi
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%si
	leal	0(,%edx,4),%ebx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_625
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_625:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f078:
	ret

FUNC(op_e6d8)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	movl	(%edx,%ebx),%ecx
	movb	2(%edx,%ebx),%al
	movl	%ecx,%edi
	leal	0(,%eax,4),%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	$2,%ecx
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_639
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_639:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f079:
	ret

FUNC(op_e6e0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%ecx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_653
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_653:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f080:
	ret

FUNC(op_e6e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_f065:
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
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_668
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_668:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f081:
	ret

FUNC(op_e6f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_f066:
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
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_716
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_716:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f082:
	ret

FUNC(op_e6f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_f067:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrw	$1,%cx
	andl	$1,%edx
	je	L_f_732
	movl	$32768,%eax
	orl	%eax,%ecx
L_f_732:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f083:
	ret

FUNC(op_e7d0)

	andl	$7,%eax
	xorl	%edx,%edx
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%esi,%esi
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%si
	leal	0(,%edx,4),%ebx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_747
	orl	$1,%ecx
L_f_747:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f084:
	ret

FUNC(op_e7d8)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	movl	(%edx,%ebx),%ecx
	movb	2(%edx,%ebx),%al
	movl	%ecx,%edi
	leal	0(,%eax,4),%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	$2,%ecx
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_761
	orl	$1,%ecx
L_f_761:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f085:
	ret

FUNC(op_e7e0)

	movl	%eax,%edx
	pushl	%edi
	andl	$7,%edx
	pushl	%esi
	addl	$8,%edx
	pushl	%ebx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	%eax,%ebp
	movl	%ecx,%edi
	andl	$1020,%ebp
	andl	$65535,%edi
	movl	GLOBL(R24)(%ebp),%eax
	addl	%edi,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,(%edx,%ebx)
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_775
	orl	$1,%ecx
L_f_775:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebp),%edx
	rolw	$8,%ax
	addl	%edi,%edx
	movw	%ax,(%edx)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f086:
	ret

FUNC(op_e7e8)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_f068:
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
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_790
	orl	$1,%ecx
L_f_790:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f087:
	ret

FUNC(op_e7f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_f069:
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
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_838
	orl	$1,%ecx
L_f_838:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f088:
	ret

FUNC(op_e7f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_f070:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%ecx
	movl	%ecx,%edx
	addw	%cx,%cx
	andl	$32768,%edx
	je	L_f_854
	orl	$1,%ecx
L_f_854:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movb	regflags,%al
	testl	%edx,%edx
	setne	%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%esi,%edx
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_f089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_f174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_f089:
	ret

FUNC(Init020_0f)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_f000-4
	movl	%eax,RR0_f001-4
	movl	%eax,RR0_f002-4
	movl	%eax,RR0_f003-4
	movl	%eax,RR0_f004-4
	movl	%eax,RR0_f005-4
	movl	%eax,RR0_f006-4
	movl	%eax,RR0_f007-4
	movl	%eax,RR0_f008-4
	movl	%eax,RR0_f009-4
	movl	%eax,RR0_f010-4
	movl	%eax,RR0_f011-4
	movl	%eax,RR0_f012-4
	movl	%eax,RR0_f013-4
	movl	%eax,RR0_f014-4
	movl	%eax,RR0_f015-4
	movl	%eax,RR0_f016-4
	movl	%eax,RR0_f017-4
	movl	%eax,RR0_f018-4
	movl	%eax,RR0_f019-4
	movl	%eax,RR0_f020-4
	movl	%eax,RR0_f021-4
	movl	%eax,RR0_f022-4
	movl	%eax,RR0_f023-4
	movl	%eax,RR0_f024-4
	movl	%eax,RR0_f025-4
	movl	%eax,RR0_f026-4
	movl	%eax,RR0_f027-4
	movl	%eax,RR0_f028-4
	movl	%eax,RR0_f029-4
	movl	%eax,RR0_f030-4
	movl	%eax,RR0_f031-4
	movl	%eax,RR0_f032-4
	movl	%eax,RR0_f033-4
	movl	%eax,RR0_f034-4
	movl	%eax,RR0_f035-4
	movl	%eax,RR0_f036-4
	movl	%eax,RR0_f037-4
	movl	%eax,RR0_f038-4
	movl	%eax,RR0_f039-4
	movl	%eax,RR0_f040-4
	movl	%eax,RR0_f041-4
	movl	%eax,RR0_f042-4
	movl	%eax,RR0_f043-4
	movl	%eax,RR0_f044-4
	movl	%eax,RR0_f045-4
	movl	%eax,RR0_f046-4
	movl	%eax,RR0_f047-4
	movl	%eax,RR0_f048-4
	movl	%eax,RR0_f049-4
	movl	%eax,RR0_f050-4
	movl	%eax,RR0_f051-4
	movl	%eax,RR0_f052-4
	movl	%eax,RR0_f053-4
	movl	%eax,RR0_f054-4
	movl	%eax,RR0_f055-4
	movl	%eax,RR0_f056-4
	movl	%eax,RR0_f057-4
	movl	%eax,RR0_f058-4
	movl	%eax,RR0_f059-4
	movl	%eax,RR0_f060-4
	movl	%eax,RR0_f061-4
	movl	%eax,RR0_f062-4
	movl	%eax,RR0_f063-4
	movl	%eax,RR0_f064-4
	movl	%eax,RR0_f065-4
	movl	%eax,RR0_f066-4
	movl	%eax,RR0_f067-4
	movl	%eax,RR0_f068-4
	movl	%eax,RR0_f069-4
	movl	%eax,RR0_f070-4
	movl	%eax,RR0_f071-4
	movl	%eax,RR0_f072-4
	movl	%eax,RR0_f073-4
	movl	%eax,RR0_f074-4
	movl	%eax,RR0_f075-4
	movl	%eax,RR0_f076-4
	movl	%eax,RR0_f077-4
	movl	%eax,RR0_f078-4
	movl	%eax,RR0_f079-4
	movl	%eax,RR0_f080-4
	movl	%eax,RR0_f081-4
	movl	%eax,RR0_f082-4
	movl	%eax,RR0_f083-4
	movl	%eax,RR0_f084-4
	movl	%eax,RR0_f085-4
	movl	%eax,RR0_f086-4
	movl	%eax,RR0_f087-4
	movl	%eax,RR0_f088-4
	movl	%eax,RR0_f089-4
	movl	%eax,RR0_f090-4
	movl	%eax,RR0_f091-4
	movl	%eax,RR0_f092-4
	movl	%eax,RR0_f093-4
	movl	%eax,RR0_f094-4
	movl	%eax,RR0_f095-4
	movl	%eax,RR0_f096-4
	movl	%eax,RR0_f097-4
	movl	%eax,RR0_f098-4
	movl	%eax,RR0_f099-4
	movl	%eax,RR0_f100-4
	movl	%eax,RR0_f101-4
	movl	%eax,RR0_f102-4
	movl	%eax,RR0_f103-4
	movl	%eax,RR0_f104-4
	movl	%eax,RR0_f105-4
	movl	%eax,RR0_f106-4
	movl	%eax,RR0_f107-4
	movl	%eax,RR0_f108-4
	movl	%eax,RR0_f109-4
	movl	%eax,RR0_f110-4
	movl	%eax,RR0_f111-4
	movl	%eax,RR0_f112-4
	movl	%eax,RR0_f113-4
	movl	%eax,RR0_f114-4
	movl	%eax,RR0_f115-4
	movl	%eax,RR0_f116-4
	movl	%eax,RR0_f117-4
	movl	%eax,RR0_f118-4
	movl	%eax,RR0_f119-4
	movl	%eax,RR0_f120-4
	movl	%eax,RR0_f121-4
	movl	%eax,RR0_f122-4
	movl	%eax,RR0_f123-4
	movl	%eax,RR0_f124-4
	movl	%eax,RR0_f125-4
	movl	%eax,RR0_f126-4
	movl	%eax,RR0_f127-4
	movl	%eax,RR0_f128-4
	movl	%eax,RR0_f129-4
	movl	%eax,RR0_f130-4
	movl	%eax,RR0_f131-4
	movl	%eax,RR0_f132-4
	movl	%eax,RR0_f133-4
	movl	%eax,RR0_f134-4
	movl	%eax,RR0_f135-4
	movl	%eax,RR0_f136-4
	movl	%eax,RR0_f137-4
	movl	%eax,RR0_f138-4
	movl	%eax,RR0_f139-4
	movl	%eax,RR0_f140-4
	movl	%eax,RR0_f141-4
	movl	%eax,RR0_f142-4
	movl	%eax,RR0_f143-4
	movl	%eax,RR0_f144-4
	movl	%eax,RR0_f145-4
	movl	%eax,RR0_f146-4
	movl	%eax,RR0_f147-4
	movl	%eax,RR0_f148-4
	movl	%eax,RR0_f149-4
	movl	%eax,RR0_f150-4
	movl	%eax,RR0_f151-4
	movl	%eax,RR0_f152-4
	movl	%eax,RR0_f153-4
	movl	%eax,RR0_f154-4
	movl	%eax,RR0_f155-4
	movl	%eax,RR0_f156-4
	movl	%eax,RR0_f157-4
	movl	%eax,RR0_f158-4
	movl	%eax,RR0_f159-4
	movl	%eax,RR0_f160-4
	movl	%eax,RR0_f161-4
	movl	%eax,RR0_f162-4
	movl	%eax,RR0_f163-4
	movl	%eax,RR0_f164-4
	movl	%eax,RR0_f165-4
	movl	%eax,RR0_f166-4
	movl	%eax,RR0_f167-4
	movl	%eax,RR0_f168-4
	movl	%eax,RR0_f169-4
	movl	%eax,RR0_f170-4
	movl	%eax,RR0_f171-4
	movl	%eax,RR0_f172-4
	movl	%eax,RR0_f173-4
	movl	%eax,RR0_f174-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_f000-4
	movl	%eax,RR2_f001-4
	movl	%eax,RR2_f002-4
	movl	%eax,RR2_f003-4
	movl	%eax,RR2_f004-4
	movl	%eax,RR2_f005-4
	movl	%eax,RR2_f006-4
	movl	%eax,RR2_f007-4
	movl	%eax,RR2_f008-4
	movl	%eax,RR2_f009-4
	movl	%eax,RR2_f010-4
	movl	%eax,RR2_f011-4
	movl	%eax,RR2_f012-4
	movl	%eax,RR2_f013-4
	movl	%eax,RR2_f014-4
	movl	%eax,RR2_f015-4
	movl	%eax,RR2_f016-4
	movl	%eax,RR2_f017-4
	movl	%eax,RR2_f018-4
	movl	%eax,RR2_f019-4
	movl	%eax,RR2_f020-4
	movl	%eax,RR2_f021-4
	movl	%eax,RR2_f022-4
	movl	%eax,RR2_f023-4
	movl	%eax,RR2_f024-4
	movl	%eax,RR2_f025-4
	movl	%eax,RR2_f026-4
	movl	%eax,RR2_f027-4
	movl	%eax,RR2_f028-4
	movl	%eax,RR2_f029-4
	movl	%eax,RR2_f030-4
	movl	%eax,RR2_f031-4
	movl	%eax,RR2_f032-4
	movl	%eax,RR2_f033-4
	movl	%eax,RR2_f034-4
	movl	%eax,RR2_f035-4
	movl	%eax,RR2_f036-4
	movl	%eax,RR2_f037-4
	movl	%eax,RR2_f038-4
	movl	%eax,RR2_f039-4
	movl	%eax,RR2_f040-4
	movl	%eax,RR2_f041-4
	movl	%eax,RR2_f042-4
	movl	%eax,RR2_f043-4
	movl	%eax,RR2_f044-4
	movl	%eax,RR2_f045-4
	movl	%eax,RR2_f046-4
	movl	%eax,RR2_f047-4
	movl	%eax,RR2_f048-4
	movl	%eax,RR2_f049-4
	movl	%eax,RR2_f050-4
	movl	%eax,RR2_f051-4
	movl	%eax,RR2_f052-4
	movl	%eax,RR2_f053-4
	movl	%eax,RR2_f054-4
	movl	%eax,RR2_f055-4
	movl	%eax,RR2_f056-4
	movl	%eax,RR2_f057-4
	movl	%eax,RR2_f058-4
	movl	%eax,RR2_f059-4
	movl	%eax,RR2_f060-4
	movl	%eax,RR2_f061-4
	movl	%eax,RR2_f062-4
	movl	%eax,RR2_f063-4
	movl	%eax,RR2_f064-4
	movl	%eax,RR2_f065-4
	movl	%eax,RR2_f066-4
	movl	%eax,RR2_f067-4
	movl	%eax,RR2_f068-4
	movl	%eax,RR2_f069-4
	movl	%eax,RR2_f070-4
	incl	%eax
	incl	%eax
	movl	%eax,RR4_f000-4
	movl	%eax,RR4_f001-4
	movl	%eax,RR4_f002-4
	movl	%eax,RR4_f003-4
	movl	%eax,RR4_f004-4
	movl	%eax,RR4_f005-4
	movl	%eax,RR4_f006-4
	movl	%eax,RR4_f007-4
	movl	%eax,RR4_f008-4
	movl	%eax,RR4_f009-4
	movl	%eax,RR4_f010-4
	movl	%eax,RR4_f011-4
	movl	%eax,RR4_f012-4
	movl	%eax,RR4_f013-4
	movl	%eax,RR4_f014-4
	movl	%eax,RR4_f015-4
	movl	%eax,RR4_f016-4
	movl	%eax,RR4_f017-4
	movl	%eax,RR4_f018-4
	movl	%eax,RR4_f019-4
	movl	%eax,RR4_f020-4
	movl	%eax,RR4_f021-4
	movl	%eax,RR4_f022-4
	movl	%eax,RR4_f023-4
	movl	%eax,RR4_f024-4
	movl	%eax,RR4_f025-4
	movl	%eax,RR4_f026-4
	movl	%eax,RR4_f027-4
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
