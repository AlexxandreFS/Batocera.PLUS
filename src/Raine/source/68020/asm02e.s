

FUNC(op_d0fb)

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
RR0_e000:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_e_407
	movswl	%di,%edi
L_e_407:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_408
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_409
	movl	%ebp,%ebx
L_e_409:
	testl	$64,%esi
	je	L_e_410
	movl	%ebp,%edi
L_e_410:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_411
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_411:
	cmpl	$48,%edx
	jne	L_e_414
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_414:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_417
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_417:
	cmpl	$3,16-16(%esp)
	jne	L_e_420
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_420:
	andl	$4,%esi
	jne	L_e_423
	addl	%edi,%ebx
L_e_423:
	cmpl	$0,16-16(%esp)
	je	L_e_424
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_424:
	testl	%esi,%esi
	je	L_e_427
	addl	%edi,%ebx
L_e_427:
	leal	(%ebp,%ebx),%eax
	jmp	L_e_428
	.align	2,0x90
L_e_408:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_e_428:
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
	jl	JJ_e000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e000:
	ret

FUNC(op_d100)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	movsbl	(%edx,%ebp,4),%ecx
	movsbl	(%edx,%eax,4),%eax
	leal	(%eax,%ecx),%edi
	testb	$1,regflags+4
	je	L_e_440
	incl	%edi
L_e_440:
	movl	%eax,%esi
	movl	%edi,%ebx
	shrl	$31,%esi
	movsbl	%bl,%eax
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	shrl	$31,%ecx
	xorl	%eax,%eax
	testl	%esi,%esi
	je	L_e_449
	testl	%ecx,%ecx
	je	L_e_441
	cmpl	$0,16-16(%esp)
	je	L_e_442
	jmp	L_e_441
	.align	2,0x90
L_e_449:
	testl	%ecx,%ecx
	jne	L_e_441
	cmpl	$0,16-16(%esp)
	je	L_e_441
L_e_442:
	movl	$1,%eax
L_e_441:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_e_446
	testl	%ecx,%ecx
	jne	L_e_445
L_e_446:
	cmpl	$0,16-16(%esp)
	jne	L_e_444
	testl	%ecx,%ecx
	jne	L_e_445
	testl	%esi,%esi
	je	L_e_444
L_e_445:
	movl	$1,%edx
L_e_444:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	movl	%edi,%ebx
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_e_447
	andb	$191,%cl
	movb	%cl,regflags
L_e_447:
	movl	%edi,%edx
	movb	regflags,%al
	andb	$128,%dl
	andb	$127,%al
	orb	%dl,%al
	movl	%edi,%ebx
	movb	%al,regflags
	movb	%bl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e006:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e001:
	ret

FUNC(op_d108)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%eax
	movl	$GLOBL(areg_byteinc),%ebp
	movl	$GLOBL(regs),%edi
	movl	%edx,%esi
	leal	8(%eax),%ebx
	shrl	$9,%esi
	sall	$2,%ebx
	movl	(%ebp,%eax,4),%eax
	movl	(%ebx,%edi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ecx,%eax),%cl
	movb	%cl,23-16(%esp)
	andl	$7,%esi
	movl	%edx,(%ebx,%edi)
	leal	8(%esi),%edx
	sall	$2,%edx
	movl	(%ebp,%esi,4),%eax
	movl	(%edx,%edi),%ebp
	subl	%eax,%ebp
	movl	%ebp,%eax
	shrl	$14,%eax
	movl	%ebp,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%ecx,%eax),%al
	movl	%ebp,(%edx,%edi)
	movsbl	%al,%eax
	movsbl	23-16(%esp),%edx
	leal	(%edx,%eax),%edi
	testb	$1,regflags+4
	je	L_e_453
	incl	%edi
L_e_453:
	movl	%eax,%ecx
	movl	%edi,%ebx
	shrl	$31,%ecx
	movsbl	%bl,%eax
	shrl	$31,%eax
	movl	%edx,%esi
	movl	%eax,16-16(%esp)
	shrl	$31,%esi
	xorl	%eax,%eax
	testl	%esi,%esi
	je	L_e_463
	testl	%ecx,%ecx
	je	L_e_454
	cmpl	$0,16-16(%esp)
	je	L_e_455
	jmp	L_e_454
	.align	2,0x90
L_e_463:
	testl	%ecx,%ecx
	jne	L_e_454
	cmpl	$0,16-16(%esp)
	je	L_e_454
L_e_455:
	movl	$1,%eax
L_e_454:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_e_459
	testl	%ecx,%ecx
	jne	L_e_458
L_e_459:
	cmpl	$0,16-16(%esp)
	jne	L_e_457
	testl	%ecx,%ecx
	jne	L_e_458
	testl	%esi,%esi
	je	L_e_457
L_e_458:
	movl	$1,%edx
L_e_457:
	movb	%dl,%al
	movb	regflags,%cl
	andb	$1,%al
	andb	$254,%cl
	orb	%al,%cl
	movb	regflags+4,%al
	andb	$254,%al
	movl	%edi,%ebx
	orb	%dl,%al
	movb	%cl,regflags
	movb	%al,regflags+4
	testb	%bl,%bl
	je	L_e_460
	andb	$191,%cl
	movb	%cl,regflags
L_e_460:
	movl	%edi,%edx
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
	movl	%edi,%ebx
	movb	%bl,(%edx,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e007:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e002:
	ret

FUNC(op_d130)

	subl	$16,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	andl	$7,%edx
	movb	GLOBL(regs)(%eax),%al
	movl	GLOBL(regs)+88,%ecx
	movb	%al,31-16(%esp)
	addl	$8,%edx
	movl	%ecx,%eax
	movl	%ecx,24-16(%esp)
	addl	$2,%eax
	addl	$4,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_e008:
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
	jne	L_e_501
	movswl	%di,%edi
L_e_501:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_502
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_503
	movl	%ebp,%ebx
L_e_503:
	testl	$64,%esi
	je	L_e_504
	movl	%ebp,%edi
L_e_504:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_505
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e009:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_505:
	cmpl	$48,%edx
	jne	L_e_508
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e010:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_508:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_511
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e011:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_511:
	cmpl	$3,16-16(%esp)
	jne	L_e_514
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e012:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_514:
	andl	$4,%esi
	jne	L_e_517
	addl	%edi,%ebx
L_e_517:
	cmpl	$0,16-16(%esp)
	je	L_e_518
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_518:
	testl	%esi,%esi
	je	L_e_521
	addl	%edi,%ebx
L_e_521:
	leal	(%ebp,%ebx),%edx
	jmp	L_e_522
	.align	2,0x90
L_e_502:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_e_522:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	addb	31-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e013:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e003:
	ret

FUNC(op_d140)

	movl	%eax,%edx
	pushl	%edi
	shrl	$9,%edx
	pushl	%esi
	movl	%edx,%ebp
	pushl	%ebx
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	movswl	(%edx,%ebp,4),%ecx
	movswl	(%edx,%eax,4),%eax
	leal	(%eax,%ecx),%edi
	testb	$1,regflags+4
	je	L_e_548
	incl	%edi
L_e_548:
	movl	%eax,%esi
	shrl	$31,%esi
	movswl	%di,%eax
	movl	%eax,%ebx
	shrl	$31,%ecx
	shrl	$31,%ebx
	xorl	%eax,%eax
	testl	%esi,%esi
	je	L_e_557
	testl	%ecx,%ecx
	je	L_e_549
	testl	%ebx,%ebx
	je	L_e_550
	jmp	L_e_549
	.align	2,0x90
L_e_557:
	testl	%ecx,%ecx
	jne	L_e_549
	testl	%ebx,%ebx
	je	L_e_549
L_e_550:
	movl	$1,%eax
L_e_549:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_e_554
	testl	%ecx,%ecx
	jne	L_e_553
L_e_554:
	testl	%ebx,%ebx
	jne	L_e_552
	testl	%ecx,%ecx
	jne	L_e_553
	testl	%esi,%esi
	je	L_e_552
L_e_553:
	movl	$1,%edx
L_e_552:
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
	testw	%di,%di
	je	L_e_555
	andb	$191,%cl
	movb	%cl,regflags
L_e_555:
	movl	%edi,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movw	%di,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e014:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e004:
	ret

FUNC(op_d148)

	subl	$8,%esp
	movl	%eax,%esi
	andl	$7,%esi
	addl	$8,%esi
	sall	$2,%esi
	movl	GLOBL(regs)(%esi),%ebx
	movl	%eax,%ecx
	addl	$-2,%ebx
	shrl	$9,%ecx
	movl	%ebx,%edx
	movl	%ebx,%eax
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
	movw	%ax,22-16(%esp)
	sall	$2,%ecx
	movl	%ebx,GLOBL(regs)(%esi)
	movl	GLOBL(regs)(%ecx),%ebp
	addl	$-2,%ebp
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
	movl	%ebp,GLOBL(regs)(%ecx)
	movswl	%ax,%edx
	movswl	22-16(%esp),%eax
	leal	(%eax,%edx),%ecx
	testb	$1,regflags+4
	je	L_e_563
	incl	%ecx
L_e_563:
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	movswl	%cx,%eax
	movl	%edx,%ebx
	movl	%eax,%esi
	shrl	$31,%ebx
	shrl	$31,%esi
	xorl	%eax,%eax
	cmpl	$0,16-16(%esp)
	je	L_e_574
	testl	%ebx,%ebx
	je	L_e_564
	testl	%esi,%esi
	je	L_e_565
	jmp	L_e_564
	.align	2,0x90
L_e_574:
	testl	%ebx,%ebx
	jne	L_e_564
	testl	%esi,%esi
	je	L_e_564
L_e_565:
	movl	$1,%eax
L_e_564:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	cmpl	$0,16-16(%esp)
	je	L_e_569
	testl	%ebx,%ebx
	jne	L_e_568
L_e_569:
	testl	%esi,%esi
	jne	L_e_567
	testl	%ebx,%ebx
	jne	L_e_568
	cmpl	$0,16-16(%esp)
	je	L_e_567
L_e_568:
	movl	$1,%edx
L_e_567:
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
	je	L_e_570
	andb	$191,%bl
	movb	%bl,regflags
L_e_570:
	movl	%ecx,%eax
	shrl	$8,%eax
	movb	%al,%dl
	andb	$128,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
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
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e005:
	ret

FUNC(op_d170)

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
RR0_e016:
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
	jne	L_e_628
	movswl	%di,%edi
L_e_628:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_629
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_e_630
	movl	%ebp,16-16(%esp)
L_e_630:
	testl	$64,%esi
	je	L_e_631
	movl	%ebp,%edi
L_e_631:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_632
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e017:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_e_632:
	cmpl	$48,%edx
	jne	L_e_635
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e018:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_e_635:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_e_638
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e019:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_638:
	cmpl	$3,%ecx
	jne	L_e_641
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e020:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_641:
	andl	$4,%esi
	jne	L_e_644
	addl	%edi,16-16(%esp)
L_e_644:
	testl	%ecx,%ecx
	je	L_e_645
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_e_645:
	testl	%esi,%esi
	je	L_e_648
	addl	%edi,16-16(%esp)
L_e_648:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_e_649
	.align	2,0x90
L_e_629:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_e_649:
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
	addw	30-16(%esp),%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%eax
	addl	GLOBL(W24)(%edx),%ecx
	rolw	$8,%ax
	movw	%ax,(%ecx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e021:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e006:
	ret

FUNC(op_d180)

	movl	%eax,%edx
	pushl	%edi
	shrl	$9,%edx
	pushl	%esi
	andl	$7,%eax
	movl	%edx,%ebp
	pushl	%ebx
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	movl	(%edx,%eax,4),%ecx
	movl	(%edx,%ebp,4),%eax
	leal	(%ecx,%eax),%edi
	testb	$1,regflags+4
	je	L_e_685
	incl	%edi
L_e_685:
	movl	%ecx,%esi
	movl	%edi,%ebx
	shrl	$31,%esi
	movl	%eax,%ecx
	shrl	$31,%ebx
	shrl	$31,%ecx
	xorl	%eax,%eax
	testl	%esi,%esi
	je	L_e_694
	testl	%ecx,%ecx
	je	L_e_686
	testl	%ebx,%ebx
	je	L_e_687
	jmp	L_e_686
	.align	2,0x90
L_e_694:
	testl	%ecx,%ecx
	jne	L_e_686
	testl	%ebx,%ebx
	je	L_e_686
L_e_687:
	movl	$1,%eax
L_e_686:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_e_691
	testl	%ecx,%ecx
	jne	L_e_690
L_e_691:
	testl	%ebx,%ebx
	jne	L_e_689
	testl	%ecx,%ecx
	jne	L_e_690
	testl	%esi,%esi
	je	L_e_689
L_e_690:
	movl	$1,%edx
L_e_689:
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
	testl	%edi,%edi
	je	L_e_692
	andb	$191,%cl
	movb	%cl,regflags
L_e_692:
	movl	%edi,%eax
	shrl	$31,%eax
	movb	%al,%dl
	salb	$7,%dl
	movb	regflags,%al
	andb	$127,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	%edi,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e022:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e007:
	ret

FUNC(op_d188)

	subl	$8,%esp
	movl	%eax,%esi
	andl	$7,%esi
	movl	$GLOBL(regs),%edi
	addl	$8,%esi
	sall	$2,%esi
	movl	(%esi,%edi),%ebx
	movl	%eax,%ecx
	addl	$-4,%ebx
	shrl	$9,%ecx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	andl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
	sall	$2,%ecx
	movl	%ebx,(%esi,%edi)
	movl	(%ecx,%edi),%ebp
	addl	$-4,%ebp
	movl	%ebp,%edx
	movl	%ebp,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	movl	%ebp,(%ecx,%edi)
	movl	20-16(%esp),%ebx
	bswapl	%eax
	leal	(%ebx,%eax),%edi
	testb	$1,regflags+4
	je	L_e_700
	incl	%edi
L_e_700:
	movl	20-16(%esp),%esi
	movl	%eax,%ecx
	movl	%edi,%ebx
	shrl	$31,%esi
	shrl	$31,%ecx
	shrl	$31,%ebx
	xorl	%eax,%eax
	movl	%ebx,16-16(%esp)
	testl	%esi,%esi
	je	L_e_711
	testl	%ecx,%ecx
	je	L_e_701
	testl	%ebx,%ebx
	je	L_e_702
	jmp	L_e_701
	.align	2,0x90
L_e_711:
	testl	%ecx,%ecx
	jne	L_e_701
	cmpl	$0,16-16(%esp)
	je	L_e_701
L_e_702:
	movl	$1,%eax
L_e_701:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_e_706
	testl	%ecx,%ecx
	jne	L_e_705
L_e_706:
	cmpl	$0,16-16(%esp)
	jne	L_e_704
	testl	%ecx,%ecx
	jne	L_e_705
	testl	%esi,%esi
	je	L_e_704
L_e_705:
	movl	$1,%edx
L_e_704:
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
	testl	%edi,%edi
	je	L_e_707
	andb	$191,%cl
	movb	%cl,regflags
L_e_707:
	movl	%edi,%eax
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
	bswapl	%edi
	movl	%edi,(%eax)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e008:
	ret

FUNC(op_d1b0)

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
RR0_e024:
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
	jne	L_e_765
	movswl	%di,%edi
L_e_765:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_766
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_e_767
	movl	%ebp,16-16(%esp)
L_e_767:
	testl	$64,%esi
	je	L_e_768
	movl	%ebp,%edi
L_e_768:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_769
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e025:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_e_769:
	cmpl	$48,%edx
	jne	L_e_772
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e026:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_e_772:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_e_775
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e027:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_775:
	cmpl	$3,%ecx
	jne	L_e_778
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e028:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_778:
	andl	$4,%esi
	jne	L_e_781
	addl	%edi,16-16(%esp)
L_e_781:
	testl	%ecx,%ecx
	je	L_e_782
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_e_782:
	testl	%esi,%esi
	je	L_e_785
	addl	%edi,16-16(%esp)
L_e_785:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_e_786
	.align	2,0x90
L_e_766:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_e_786:
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
	jl	JJ_e009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e029:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e009:
	ret

FUNC(op_d1f0)

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
RR0_e030:
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
	jne	L_e_866
	movswl	%di,%edi
L_e_866:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_867
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_868
	movl	%ebp,%ebx
L_e_868:
	testl	$64,%esi
	je	L_e_869
	movl	%ebp,%edi
L_e_869:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_870
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e031:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_870:
	cmpl	$48,%edx
	jne	L_e_873
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e032:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_873:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_876
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e033:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_876:
	cmpl	$3,16-16(%esp)
	jne	L_e_879
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e034:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_879:
	andl	$4,%esi
	jne	L_e_882
	addl	%edi,%ebx
L_e_882:
	cmpl	$0,16-16(%esp)
	je	L_e_883
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_883:
	testl	%esi,%esi
	je	L_e_886
	addl	%edi,%ebx
L_e_886:
	leal	(%ebp,%ebx),%eax
	jmp	L_e_887
	.align	2,0x90
L_e_867:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_e_887:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	addl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e035:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e010:
	ret

FUNC(op_d1fb)

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
RR0_e036:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_e_928
	movswl	%di,%edi
L_e_928:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_929
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_930
	movl	%ebp,%ebx
L_e_930:
	testl	$64,%esi
	je	L_e_931
	movl	%ebp,%edi
L_e_931:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_932
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e037:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_932:
	cmpl	$48,%edx
	jne	L_e_935
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e038:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_935:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_938
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e039:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_938:
	cmpl	$3,16-16(%esp)
	jne	L_e_941
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e040:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_941:
	andl	$4,%esi
	jne	L_e_944
	addl	%edi,%ebx
L_e_944:
	cmpl	$0,16-16(%esp)
	je	L_e_945
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_945:
	testl	%esi,%esi
	je	L_e_948
	addl	%edi,%ebx
L_e_948:
	leal	(%ebp,%ebx),%eax
	jmp	L_e_949
	.align	2,0x90
L_e_929:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_e_949:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	28-16(%esp),%eax
	addl	$8,%eax
	addl	%edx,GLOBL(regs)(,%eax,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e011:
	ret

FUNC(op_e000)

	subl	$8,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	shrl	$7,%eax
	movb	GLOBL(regs)(,%ebp,4),%cl
	andl	$28,%eax
	movl	%ecx,%esi
	movb	%cl,20-16(%esp)
	andl	$255,%esi
	movl	GLOBL(imm8_table)(%eax),%eax
	andb	$247,regflags+1
	movl	%esi,%edi
	andl	$63,%eax
	andl	$128,%edi
	movl	%eax,16-16(%esp)
	testl	%eax,%eax
	jne	L_e_961
	andb	$254,regflags
	jmp	L_e_962
	.align	2,0x90
L_e_961:
	cmpl	$7,16-16(%esp)
	jbe	L_e_963
	movb	$0,20-16(%esp)
	testl	%edi,%edi
	je	L_e_964
	movb	$255,20-16(%esp)
L_e_964:
	movb	regflags+4,%dl
	testl	%edi,%edi
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_962
	.align	2,0x90
L_e_963:
	movl	16-16(%esp),%eax
	decl	%eax
	movl	%esi,%ebx
	movl	%eax,%ecx
	sarl	%cl,%ebx
	movl	%ebx,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movl	16-16(%esp),%ecx
	movb	regflags,%al
	movl	%esi,%ebx
	andb	$254,%al
	sarl	%cl,%ebx
	orb	%dl,%al
	movb	%bl,20-16(%esp)
	movb	%al,regflags
	testl	%edi,%edi
	je	L_e_962
	movl	$8,%eax
	movl	%eax,%ecx
	subl	16-16(%esp),%ecx
	movl	$255,%eax
	sall	%cl,%eax
	orb	%al,%bl
	movb	%bl,20-16(%esp)
L_e_962:
	testl	%edi,%edi
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	cmpb	$0,20-16(%esp)
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	20-16(%esp),%cl
	movb	%dl,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e042:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e012:
	ret

FUNC(op_e008)

	subl	$12,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	shrl	$7,%eax
	movb	GLOBL(regs)(,%ebp,4),%cl
	andl	$28,%eax
	movb	%cl,24-16(%esp)
	movl	GLOBL(imm8_table)(%eax),%eax
	andl	$63,%eax
	movl	$128,%edi
	movl	%eax,16-16(%esp)
	testl	%eax,%eax
	jne	L_e_970
	andb	$254,regflags
	jmp	L_e_971
	.align	2,0x90
L_e_970:
	cmpl	$7,16-16(%esp)
	jbe	L_e_972
	cmpl	$8,16-16(%esp)
	jne	L_e_973
	xorl	%eax,%eax
	movb	24-16(%esp),%al
	testl	%eax,%edi
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	movl	%ebx,16-16(%esp)
	jmp	L_e_974
	.align	2,0x90
L_e_973:
	movl	$0,16-16(%esp)
L_e_974:
	movb	16-16(%esp),%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	16-16(%esp),%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	$0,24-16(%esp)
	movb	%al,regflags
	jmp	L_e_971
	.align	2,0x90
L_e_972:
	xorl	%ecx,%ecx
	movb	24-16(%esp),%cl
	movl	16-16(%esp),%eax
	movl	%ecx,20-16(%esp)
	decl	%eax
	movl	%ecx,%ebx
	movl	%eax,%ecx
	sarl	%cl,%ebx
	movl	%ebx,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	16-16(%esp),%ecx
	andb	$254,%al
	movl	20-16(%esp),%ebx
	orb	%dl,%al
	sarl	%cl,%ebx
	movb	%al,regflags
	movb	%bl,24-16(%esp)
L_e_971:
	xorl	%ecx,%ecx
	movb	24-16(%esp),%cl
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	cmpb	$0,24-16(%esp)
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e043:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e013:
	ret

FUNC(op_e010)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$28,%eax
	andl	$7,%ebp
	movl	$128,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movb	GLOBL(regs)(,%ebp,4),%bl
	andl	$63,%esi
	je	L_e_979
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_981
	cmpl	$3,%eax
	jge	L_e_987
	cmpl	$2,%eax
	jge	L_e_988
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_991
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_991:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_988:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_994
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_994:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_987:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_997
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_997:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_979
	.align	2,0x90
L_e_981:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1000
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_1000:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrb	$1,%bl
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1003
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_1003:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrb	$1,%bl
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1006
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_1006:
	andb	$-2,%dl
	andb	$1,%al
	movb	%dl,19-16(%esp)
	orb	%al,19-16(%esp)
	movb	19-16(%esp),%cl
	movl	%ebx,%eax
	shrb	$1,%bl
	movb	%cl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1009
	movl	%edi,%ecx
	orb	%cl,%bl
L_e_1009:
	movb	%al,%dl
	andb	$1,%dl
	movb	19-16(%esp),%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_981
L_e_979:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movb	%bl,%cl
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e044:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e014:
	ret

FUNC(op_e018)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	andl	$28,%eax
	movl	$128,%esi
	movl	GLOBL(imm8_table)(%eax),%edx
	movb	GLOBL(regs)(,%edi,4),%bl
	andl	$63,%edx
	jne	L_e_1021
	andb	$254,regflags
	jmp	L_e_1013
	.align	2,0x90
L_e_1021:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1017
	cmpl	$3,%eax
	jge	L_e_1024
	cmpl	$2,%eax
	jge	L_e_1025
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1027
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1027:
	decl	%edx
L_e_1025:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1030
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1030:
	decl	%edx
L_e_1024:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1033
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1033:
	decl	%edx
	jz	L_e_1022
	.align	2,0x90
L_e_1017:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1036
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1036:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1039
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1039:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1042
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1042:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1045
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1045:
	addl	$-4,%edx
	jne	L_e_1017
L_e_1022:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1013:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e045:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e015:
	ret

FUNC(op_e020)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	%edx,20-16(%esp)
	movl	$GLOBL(regs),%edx
	movl	20-16(%esp),%ecx
	shrl	$7,%eax
	movb	(%edx,%ecx,4),%bl
	andl	$28,%eax
	movl	%ebx,%edi
	movb	(%eax,%edx),%al
	andl	$255,%edi
	andb	$247,regflags+1
	movl	%edi,%ebp
	andb	$63,%al
	andl	$128,%ebp
	testb	%al,%al
	jne	L_e_1049
	andb	$254,regflags
	jmp	L_e_1050
	.align	2,0x90
L_e_1049:
	cmpb	$7,%al
	jle	L_e_1051
	xorl	%ebx,%ebx
	testl	%ebp,%ebp
	je	L_e_1052
	movb	$255,%bl
L_e_1052:
	movb	regflags+4,%dl
	testl	%ebp,%ebp
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_1050
	.align	2,0x90
L_e_1051:
	movsbl	%al,%eax
	movl	%eax,16-16(%esp)
	decl	%eax
	movl	%edi,%esi
	movl	%eax,%ecx
	sarl	%cl,%esi
	movl	%esi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%edi,%ebx
	andb	$254,%al
	movl	16-16(%esp),%ecx
	orb	%dl,%al
	sarl	%cl,%ebx
	movb	%al,regflags
	testl	%ebp,%ebp
	je	L_e_1050
	movl	$8,%eax
	movl	%eax,%ecx
	subl	16-16(%esp),%ecx
	movl	$255,%eax
	sall	%cl,%eax
	orb	%al,%bl
L_e_1050:
	testl	%ebp,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testb	%bl,%bl
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	20-16(%esp),%esi
	movb	%bl,GLOBL(regs)(,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e046:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e016:
	ret

FUNC(op_e028)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$7,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	$128,%edi
	movb	(%eax,%edx),%al
	movb	(%edx,%ebp,4),%bl
	andb	$63,%al
	jne	L_e_1058
	andb	$254,regflags
	jmp	L_e_1059
	.align	2,0x90
L_e_1058:
	cmpb	$7,%al
	jle	L_e_1060
	cmpb	$8,%al
	jne	L_e_1061
	xorl	%eax,%eax
	movb	%bl,%al
	testl	%eax,%edi
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	jmp	L_e_1062
	.align	2,0x90
L_e_1061:
	xorl	%ebx,%ebx
L_e_1062:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	%bl,%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1059
	.align	2,0x90
L_e_1060:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movsbl	%al,%ebx
	movl	%ecx,16-16(%esp)
	leal	-1(%ebx),%eax
	movl	%ecx,%esi
	movl	%eax,%ecx
	sarl	%cl,%esi
	movl	%esi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebx,%ecx
	andb	$254,%al
	movl	16-16(%esp),%esi
	orb	%dl,%al
	sarl	%cl,%esi
	movb	%al,regflags
	movl	%esi,%ebx
L_e_1059:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e017:
	ret

FUNC(op_e030)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%edi
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movb	(%edx,%edi,4),%bl
	movb	(%eax,%edx),%dl
	andb	$63,%dl
	movl	$128,%esi
	movb	%dl,19-16(%esp)
	testb	%dl,%dl
	je	L_e_1067
	movb	%dl,%al
	negb	%al
	andb	$3,%al
	je	L_e_1069
	cmpb	$3,%al
	jge	L_e_1075
	cmpb	$2,%al
	jge	L_e_1076
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1079
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1079:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	19-16(%esp)
	movb	%al,regflags+4
L_e_1076:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1082
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1082:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	19-16(%esp)
	movb	%al,regflags+4
L_e_1075:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1085
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1085:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	19-16(%esp)
	jmp	L_e_1099
	.align	2,0x90
	.align	2,0x90
L_e_1069:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1088
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1088:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrb	$1,%bl
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1091
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1091:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrb	$1,%bl
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1094
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1094:
	andb	$-2,%dl
	movl	%edx,%ebp
	andb	$1,%al
	movl	%ebp,%ecx
	orb	%al,%cl
	movl	%ebx,%eax
	movl	%ecx,%ebp
	shrb	$1,%bl
	andl	$1,%eax
	movb	%cl,regflags+4
	testb	$1,regflags+4
	je	L_e_1097
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1097:
	movb	%al,%dl
	andb	$1,%dl
	movl	%ebp,%eax
	andb	$-2,%al
	orb	%dl,%al
	addb	$-4,19-16(%esp)
L_e_1099:
	movb	%al,regflags+4
	cmpb	$0,19-16(%esp)
	jne	L_e_1069
L_e_1067:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movb	%bl,%cl
	orb	%dl,%al
	testl	%ecx,%esi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e048:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e018:
	ret

FUNC(op_e038)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movb	(%edx,%edi,4),%bl
	movb	(%eax,%edx),%dl
	movl	$128,%esi
	andb	$63,%dl
	jne	L_e_1110
	andb	$254,regflags
	jmp	L_e_1102
	.align	2,0x90
L_e_1110:
	movb	%dl,%al
	negb	%al
	andb	$3,%al
	je	L_e_1106
	cmpb	$3,%al
	jge	L_e_1113
	cmpb	$2,%al
	jge	L_e_1114
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1116
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1116:
	decb	%dl
L_e_1114:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1119
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1119:
	decb	%dl
L_e_1113:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1122
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1122:
	decb	%dl
	je	L_e_1111
	.align	2,0x90
L_e_1106:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1125
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1125:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1128
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1128:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1131
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1131:
	movl	%ebx,%eax
	shrb	$1,%bl
	andl	$1,%eax
	je	L_e_1134
	movl	%esi,%ecx
	orb	%cl,%bl
L_e_1134:
	addb	$-4,%dl
	jne	L_e_1106
L_e_1111:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1102:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e019:
	ret

FUNC(op_e040)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	%edx,20-16(%esp)
	xorl	%ecx,%ecx
	movw	GLOBL(regs)(,%edx,4),%si
	shrl	$7,%eax
	movw	%si,%cx
	andl	$28,%eax
	movl	%ecx,%ebp
	movl	%ecx,16-16(%esp)
	andl	$32768,%ebp
	movl	GLOBL(imm8_table)(%eax),%ebx
	andb	$247,regflags+1
	andl	$63,%ebx
	jne	L_e_1138
	andb	$254,regflags
	jmp	L_e_1139
	.align	2,0x90
L_e_1138:
	cmpl	$15,%ebx
	jbe	L_e_1140
	xorl	%esi,%esi
	testl	%ebp,%ebp
	je	L_e_1141
	movl	$-1,%esi
L_e_1141:
	movb	regflags+4,%dl
	testl	%ebp,%ebp
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_1139
	.align	2,0x90
L_e_1140:
	leal	-1(%ebx),%eax
	movl	16-16(%esp),%edi
	movl	%eax,%ecx
	sarl	%cl,%edi
	movl	%edi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	16-16(%esp),%esi
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sarl	%cl,%esi
	movb	%al,regflags
	testl	%ebp,%ebp
	je	L_e_1139
	movl	$16,%eax
	movl	%eax,%ecx
	subl	%ebx,%ecx
	movl	$65535,%eax
	sall	%cl,%eax
	orl	%eax,%esi
L_e_1139:
	testl	%ebp,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testw	%si,%si
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	20-16(%esp),%edi
	movw	%si,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e050:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e020:
	ret

FUNC(op_e048)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movl	$32768,%ebp
	movl	GLOBL(imm8_table)(%eax),%ebx
	movw	GLOBL(regs)(,%edx,4),%si
	andl	$63,%ebx
	jne	L_e_1147
	andb	$254,regflags
	jmp	L_e_1148
	.align	2,0x90
L_e_1147:
	cmpl	$15,%ebx
	jbe	L_e_1149
	cmpl	$16,%ebx
	jne	L_e_1150
	xorl	%eax,%eax
	movw	%si,%ax
	testl	%eax,%ebp
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	jmp	L_e_1151
	.align	2,0x90
L_e_1150:
	xorl	%ebx,%ebx
L_e_1151:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	jmp	L_e_1154
	.align	2,0x90
L_e_1149:
	xorl	%ecx,%ecx
	movw	%si,%cx
	leal	-1(%ebx),%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,%edi
	movl	%eax,%ecx
	sarl	%cl,%edi
	movl	%edi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	20-16(%esp),%esi
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sarl	%cl,%esi
L_e_1154:
	movb	%al,regflags
L_e_1148:
	xorl	%edi,%edi
	movw	%si,%di
	movb	regflags,%al
	testl	%edi,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	andb	$247,regflags+1
	orb	%dl,%al
	testw	%si,%si
	sete	%dl
	movl	16-16(%esp),%ecx
	salb	$6,%dl
	andb	$-65,%al
	movl	%edi,20-16(%esp)
	orb	%dl,%al
	movl	20-16(%esp),%edi
	movb	%al,regflags
	movw	%di,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e051:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e021:
	ret

FUNC(op_e050)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	pushl	%ebx
	andl	$28,%eax
	movl	$32768,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movw	GLOBL(regs)(,%ebp,4),%bx
	andl	$63,%esi
	je	L_e_1157
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1159
	cmpl	$3,%eax
	jge	L_e_1165
	cmpl	$2,%eax
	jge	L_e_1166
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1169
	orl	%edi,%ebx
L_e_1169:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1166:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1172
	orl	%edi,%ebx
L_e_1172:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1165:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1175
	orl	%edi,%ebx
L_e_1175:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1157
	.align	2,0x90
L_e_1159:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1178
	orl	%edi,%ebx
L_e_1178:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1181
	orl	%edi,%ebx
L_e_1181:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1184
	orl	%edi,%ebx
L_e_1184:
	movb	%dl,%cl
	andb	$1,%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%cl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1187
	orl	%edi,%ebx
L_e_1187:
	movb	%al,%dl
	andb	$1,%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1159
L_e_1157:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movw	%bx,%cx
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e052:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e022:
	ret

FUNC(op_e058)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	andl	$28,%eax
	movl	$32768,%esi
	movl	GLOBL(imm8_table)(%eax),%edx
	movw	GLOBL(regs)(,%edi,4),%bx
	andl	$63,%edx
	jne	L_e_1199
	andb	$254,regflags
	jmp	L_e_1191
	.align	2,0x90
L_e_1199:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1195
	cmpl	$3,%eax
	jge	L_e_1202
	cmpl	$2,%eax
	jge	L_e_1203
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1205
	orl	%esi,%ebx
L_e_1205:
	decl	%edx
L_e_1203:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1208
	orl	%esi,%ebx
L_e_1208:
	decl	%edx
L_e_1202:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1211
	orl	%esi,%ebx
L_e_1211:
	decl	%edx
	jz	L_e_1200
	.align	2,0x90
L_e_1195:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1214
	orl	%esi,%ebx
L_e_1214:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1217
	orl	%esi,%ebx
L_e_1217:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1220
	orl	%esi,%ebx
L_e_1220:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1223
	orl	%esi,%ebx
L_e_1223:
	addl	$-4,%edx
	jne	L_e_1195
L_e_1200:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1191:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e053:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e023:
	ret

FUNC(op_e060)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	movl	%edx,20-16(%esp)
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	20-16(%esp),%ecx
	xorl	%edi,%edi
	movw	(%edx,%ecx,4),%bx
	movw	(%eax,%edx),%ax
	movw	%bx,%di
	andb	$247,regflags+1
	movl	%edi,%ebp
	andl	$63,%eax
	andl	$32768,%ebp
	testw	%ax,%ax
	jne	L_e_1227
	andb	$254,regflags
	jmp	L_e_1228
	.align	2,0x90
L_e_1227:
	cmpw	$15,%ax
	jle	L_e_1229
	xorl	%ebx,%ebx
	testl	%ebp,%ebp
	je	L_e_1230
	movl	$-1,%ebx
L_e_1230:
	movb	regflags+4,%dl
	testl	%ebp,%ebp
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_1228
	.align	2,0x90
L_e_1229:
	cwtl
	movl	%eax,16-16(%esp)
	decl	%eax
	movl	%edi,%esi
	movl	%eax,%ecx
	sarl	%cl,%esi
	movl	%esi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%edi,%ebx
	andb	$254,%al
	movl	16-16(%esp),%ecx
	orb	%dl,%al
	sarl	%cl,%ebx
	movb	%al,regflags
	testl	%ebp,%ebp
	je	L_e_1228
	movl	$16,%eax
	movl	%eax,%ecx
	subl	16-16(%esp),%ecx
	movl	$65535,%eax
	sall	%cl,%eax
	orl	%eax,%ebx
L_e_1228:
	testl	%ebp,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testw	%bx,%bx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	20-16(%esp),%esi
	movw	%bx,GLOBL(regs)(,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e054:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e024:
	ret

FUNC(op_e068)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$7,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	$32768,%edi
	movw	(%eax,%edx),%ax
	movw	(%edx,%ebp,4),%bx
	andl	$63,%eax
	jne	L_e_1236
	andb	$254,regflags
	jmp	L_e_1237
	.align	2,0x90
L_e_1236:
	cmpw	$15,%ax
	jle	L_e_1238
	cmpw	$16,%ax
	jne	L_e_1239
	xorl	%eax,%eax
	movw	%bx,%ax
	testl	%eax,%edi
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	jmp	L_e_1240
	.align	2,0x90
L_e_1239:
	xorl	%ebx,%ebx
L_e_1240:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1237
	.align	2,0x90
L_e_1238:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movswl	%ax,%ebx
	movl	%ecx,16-16(%esp)
	leal	-1(%ebx),%eax
	movl	%ecx,%esi
	movl	%eax,%ecx
	sarl	%cl,%esi
	movl	%esi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebx,%ecx
	andb	$254,%al
	movl	16-16(%esp),%esi
	orb	%dl,%al
	sarl	%cl,%esi
	movb	%al,regflags
	movl	%esi,%ebx
L_e_1237:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e055:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e025:
	ret

FUNC(op_e070)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	pushl	%ebx
	andl	$28,%eax
	movl	$32768,%edi
	movw	(%eax,%edx),%si
	movw	(%edx,%ebp,4),%bx
	andl	$63,%esi
	je	L_e_1245
	movl	%esi,%eax
	negw	%ax
	andl	$3,%eax
	je	L_e_1247
	cmpw	$3,%ax
	jge	L_e_1253
	cmpw	$2,%ax
	jge	L_e_1254
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1257
	orl	%edi,%ebx
L_e_1257:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1254:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1260
	orl	%edi,%ebx
L_e_1260:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1253:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1263
	orl	%edi,%ebx
L_e_1263:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	jmp	L_e_1277
	.align	2,0x90
	.align	2,0x90
L_e_1247:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1266
	orl	%edi,%ebx
L_e_1266:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1269
	orl	%edi,%ebx
L_e_1269:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1272
	orl	%edi,%ebx
L_e_1272:
	movb	%dl,%cl
	andb	$1,%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	shrw	$1,%bx
	movb	%cl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1275
	orl	%edi,%ebx
L_e_1275:
	movb	%al,%dl
	andb	$1,%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
L_e_1277:
	movb	%al,regflags+4
	testw	%si,%si
	jne	L_e_1247
L_e_1245:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movw	%bx,%cx
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e056:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e026:
	ret

FUNC(op_e078)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movw	(%edx,%edi,4),%bx
	movw	(%eax,%edx),%dx
	movl	$32768,%esi
	andl	$63,%edx
	jne	L_e_1288
	andb	$254,regflags
	jmp	L_e_1280
	.align	2,0x90
L_e_1288:
	movl	%edx,%eax
	negw	%ax
	andl	$3,%eax
	je	L_e_1284
	cmpw	$3,%ax
	jge	L_e_1291
	cmpw	$2,%ax
	jge	L_e_1292
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1294
	orl	%esi,%ebx
L_e_1294:
	decl	%edx
L_e_1292:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1297
	orl	%esi,%ebx
L_e_1297:
	decl	%edx
L_e_1291:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1300
	orl	%esi,%ebx
L_e_1300:
	decw	%dx
	je	L_e_1289
	.align	2,0x90
L_e_1284:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1303
	orl	%esi,%ebx
L_e_1303:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1306
	orl	%esi,%ebx
L_e_1306:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1309
	orl	%esi,%ebx
L_e_1309:
	movl	%ebx,%eax
	shrw	$1,%bx
	andl	$1,%eax
	je	L_e_1312
	orl	%esi,%ebx
L_e_1312:
	addw	$-4,%dx
	jne	L_e_1284
L_e_1289:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1280:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e057:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e027:
	ret

FUNC(op_e080)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	movl	GLOBL(regs)(,%ebp,4),%esi
	movl	%esi,%ecx
	shrl	$7,%eax
	andl	$-2147483648,%ecx
	andl	$28,%eax
	movl	%ecx,16-16(%esp)
	movl	GLOBL(imm8_table)(%eax),%ebx
	andb	$247,regflags+1
	andl	$63,%ebx
	jne	L_e_1316
	andb	$254,regflags
	jmp	L_e_1317
	.align	2,0x90
L_e_1316:
	cmpl	$31,%ebx
	jbe	L_e_1318
	xorl	%esi,%esi
	cmpl	$0,16-16(%esp)
	je	L_e_1319
	movl	$-1,%esi
L_e_1319:
	movb	regflags+4,%dl
	cmpl	$0,16-16(%esp)
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_1317
	.align	2,0x90
L_e_1318:
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	shrl	%cl,%edi
	movl	%edi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	shrl	%cl,%esi
	movb	%al,regflags
	cmpl	$0,16-16(%esp)
	je	L_e_1317
	movl	$32,%eax
	movl	%eax,%ecx
	subl	%ebx,%ecx
	movl	$-1,%eax
	sall	%cl,%eax
	orl	%eax,%esi
L_e_1317:
	cmpl	$0,16-16(%esp)
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	%esi,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e058:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e028:
	ret

FUNC(op_e088)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movl	$-2147483648,%ebp
	movl	GLOBL(imm8_table)(%eax),%ebx
	movl	GLOBL(regs)(,%edx,4),%esi
	andl	$63,%ebx
	jne	L_e_1325
	andb	$254,regflags
	jmp	L_e_1326
	.align	2,0x90
L_e_1325:
	cmpl	$31,%ebx
	jbe	L_e_1327
	cmpl	$32,%ebx
	jne	L_e_1328
	testl	%esi,%ebp
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	jmp	L_e_1329
	.align	2,0x90
L_e_1328:
	xorl	%ebx,%ebx
L_e_1329:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	jmp	L_e_1332
	.align	2,0x90
L_e_1327:
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	shrl	%cl,%edi
	movl	%edi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	shrl	%cl,%esi
L_e_1332:
	movb	%al,regflags
L_e_1326:
	testl	%esi,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	16-16(%esp),%edi
	movl	%esi,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e059:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e029:
	ret

FUNC(op_e090)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	pushl	%ebx
	andl	$28,%eax
	movl	$-2147483648,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movl	GLOBL(regs)(,%ebp,4),%ebx
	andl	$63,%esi
	je	L_e_1335
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1337
	cmpl	$3,%eax
	jge	L_e_1343
	cmpl	$2,%eax
	jge	L_e_1344
	movl	%ebx,%eax
	andl	$1,%eax
	shrl	$1,%ebx
	testb	$1,regflags+4
	je	L_e_1347
	orl	%edi,%ebx
L_e_1347:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1344:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1350
	orl	%edi,%ebx
L_e_1350:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1343:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1353
	orl	%edi,%ebx
L_e_1353:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1335
	.align	2,0x90
L_e_1337:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1356
	orl	%edi,%ebx
L_e_1356:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1359
	orl	%edi,%ebx
L_e_1359:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1362
	orl	%edi,%ebx
L_e_1362:
	movb	%dl,%cl
	andb	$1,%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%cl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1365
	orl	%edi,%ebx
L_e_1365:
	movb	%al,%dl
	andb	$1,%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1337
L_e_1335:
	movb	regflags+4,%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	testl	%ebx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	%ebx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e060:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e030:
	ret

FUNC(op_e0a0)

	subl	$4,%esp
	movl	%eax,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	movl	(%edx,%ebp,4),%esi
	movl	%esi,%ecx
	shrl	$7,%eax
	andl	$-2147483648,%ecx
	andl	$28,%eax
	movl	%ecx,16-16(%esp)
	movl	(%eax,%edx),%ebx
	andb	$247,regflags+1
	andl	$63,%ebx
	jne	L_e_1388
	andb	$254,regflags
	jmp	L_e_1389
	.align	2,0x90
L_e_1388:
	cmpl	$31,%ebx
	jle	L_e_1390
	xorl	%esi,%esi
	cmpl	$0,16-16(%esp)
	je	L_e_1391
	movl	$-1,%esi
L_e_1391:
	movb	regflags+4,%dl
	cmpl	$0,16-16(%esp)
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags+4
	movb	regflags,%dl
	andb	$254,%dl
	orb	%al,%dl
	movb	%dl,regflags
	jmp	L_e_1389
	.align	2,0x90
L_e_1390:
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	shrl	%cl,%edi
	movl	%edi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	shrl	%cl,%esi
	movb	%al,regflags
	cmpl	$0,16-16(%esp)
	je	L_e_1389
	movl	$32,%eax
	movl	%eax,%ecx
	subl	%ebx,%ecx
	movl	$-1,%eax
	sall	%cl,%eax
	orl	%eax,%esi
L_e_1389:
	cmpl	$0,16-16(%esp)
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	%esi,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e061:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e031:
	ret

FUNC(op_e0a8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movl	$-2147483648,%edi
	movl	$GLOBL(regs),%edx
	movl	16-16(%esp),%ecx
	movl	(%eax,%edx),%ebp
	movl	(%edx,%ecx,4),%ebx
	andl	$63,%ebp
	jne	L_e_1397
	andb	$254,regflags
	jmp	L_e_1398
	.align	2,0x90
L_e_1397:
	cmpl	$31,%ebp
	jle	L_e_1399
	cmpl	$32,%ebp
	jne	L_e_1400
	testl	%ebx,%edi
	setne	%al
	xorl	%ebx,%ebx
	movb	%al,%bl
	jmp	L_e_1401
	.align	2,0x90
L_e_1400:
	xorl	%ebx,%ebx
L_e_1401:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	jmp	L_e_1404
	.align	2,0x90
L_e_1399:
	leal	-1(%ebp),%eax
	movl	%ebx,%esi
	movl	%eax,%ecx
	shrl	%cl,%esi
	movl	%esi,%eax
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebp,%ecx
	orb	%dl,%al
	shrl	%cl,%ebx
L_e_1404:
	movb	%al,regflags
L_e_1398:
	testl	%ebx,%edi
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%ebx,%ebx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	16-16(%esp),%esi
	movl	%ebx,GLOBL(regs)(,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e032:
	ret

FUNC(op_e0b0)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	pushl	%ebx
	andl	$28,%eax
	movl	$-2147483648,%edi
	movl	(%eax,%edx),%esi
	movl	(%edx,%ebp,4),%ebx
	andl	$63,%esi
	je	L_e_1407
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1409
	cmpl	$3,%eax
	jge	L_e_1415
	cmpl	$2,%eax
	jge	L_e_1416
	movl	%ebx,%eax
	andl	$1,%eax
	shrl	$1,%ebx
	testb	$1,regflags+4
	je	L_e_1419
	orl	%edi,%ebx
L_e_1419:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1416:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1422
	orl	%edi,%ebx
L_e_1422:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1415:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1425
	orl	%edi,%ebx
L_e_1425:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1407
	.align	2,0x90
L_e_1409:
	movl	%ebx,%eax
	shrl	$1,%ebx
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1428
	orl	%edi,%ebx
L_e_1428:
	movb	regflags+4,%dl
	andb	$1,%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1431
	orl	%edi,%ebx
L_e_1431:
	andb	$1,%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%dl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1434
	orl	%edi,%ebx
L_e_1434:
	movb	%dl,%cl
	andb	$1,%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	shrl	$1,%ebx
	movb	%cl,regflags+4
	andl	$1,%eax
	testb	$1,regflags+4
	je	L_e_1437
	orl	%edi,%ebx
L_e_1437:
	movb	%al,%dl
	andb	$1,%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1409
L_e_1407:
	movb	regflags+4,%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	testl	%ebx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	%ebx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e063:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e033:
	ret

FUNC(op_e0d0)

	subl	$4,%esp
	andl	$7,%eax
	addl	$8,%eax
	xorl	%edi,%edi
	movzbl	GLOBL(regs)+2(,%eax,4),%esi
	movw	GLOBL(regs)(,%eax,4),%di
	sall	$2,%esi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%eax,%ecx
	movl	%ecx,%ebx
	andl	$1,%ebx
	movl	%ebx,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%ebp
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%ebp
	orb	%dl,%al
	testl	%ebp,%ebp
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%ebp,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	andb	$247,regflags+1
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e064:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e034:
	ret

FUNC(op_e0d8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	sall	$2,%edx
	movl	$GLOBL(regs),%esi
	xorl	%ebx,%ebx
	movb	2(%edx,%esi),%bl
	sall	$2,%ebx
	movl	%ebx,20-16(%esp)
	movl	(%edx,%esi),%ebp
	movl	GLOBL(R24)(%ebx),%eax
	andl	$65535,%ebp
	addl	%ebp,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	(%edx,%esi),%ebx
	addl	$2,%ebx
	movl	%eax,%ecx
	movl	%ebx,(%edx,%esi)
	movl	%ecx,%ebx
	andl	$1,%ebx
	movl	%ebx,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%esi
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%esi
	orb	%dl,%al
	testl	%esi,%esi
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%esi,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%ebx),%edx
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e065:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e035:
	ret

FUNC(op_e0e0)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	sall	$2,%edx
	movl	$GLOBL(regs),%esi
	movl	(%edx,%esi),%ebx
	addl	$-2,%ebx
	movl	%ebx,%edi
	shrl	$14,%edi
	andl	$1020,%edi
	movl	%ebx,%ebp
	movl	%edi,16-16(%esp)
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ebx,(%edx,%esi)
	movl	%eax,%ecx
	movl	%ecx,%ebx
	andl	$1,%ebx
	movb	regflags+4,%al
	movb	%bl,%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%esi
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	andl	$32768,%esi
	orb	%dl,%al
	testl	%esi,%esi
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%esi,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	16-16(%esp),%edi
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	GLOBL(W24)(%edi),%edx
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e066:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e036:
	ret

FUNC(op_e0e8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_e000:
	rolw	$8,%bx
	movswl	%bx,%ebx
	addl	GLOBL(regs)(,%edx,4),%ebx
	movl	%ebx,%edi
	shrl	$14,%edi
	andl	$1020,%edi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	movl	%ecx,%esi
	andl	$1,%esi
	movl	%esi,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%ebp
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%ebp
	orb	%dl,%al
	testl	%ebp,%ebp
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%ebp,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	andb	$247,regflags+1
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%edi),%ebx
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e067:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e037:
	ret

FUNC(op_e0f0)

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
RR0_e068:
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
	jne	L_e_1487
	movswl	%di,%edi
L_e_1487:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_1488
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_e_1489
	movl	%ebp,16-16(%esp)
L_e_1489:
	testl	$64,%esi
	je	L_e_1490
	movl	%ebp,%edi
L_e_1490:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_1491
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e069:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_e_1491:
	cmpl	$48,%edx
	jne	L_e_1494
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e070:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_e_1494:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_e_1497
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e071:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_1497:
	cmpl	$3,%ecx
	jne	L_e_1500
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e072:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_1500:
	andl	$4,%esi
	jne	L_e_1503
	addl	%edi,16-16(%esp)
L_e_1503:
	testl	%ecx,%ecx
	je	L_e_1504
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_e_1504:
	testl	%esi,%esi
	je	L_e_1507
	addl	%edi,16-16(%esp)
L_e_1507:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_e_1508
	.align	2,0x90
L_e_1488:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_e_1508:
	movl	%eax,%esi
	shrl	$14,%esi
	movl	%eax,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	%eax,%ecx
	movl	%ecx,%ebx
	andl	$1,%ebx
	movl	%ebx,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%ebp
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%ebp
	orb	%dl,%al
	testl	%ebp,%ebp
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%ebp,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	andb	$247,regflags+1
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e073:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e038:
	ret

FUNC(op_e0f8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_e001:
	rolw	$8,%bx
	movswl	%bx,%ebx
	movl	%ebx,%edi
	shrl	$14,%edi
	andl	$1020,%edi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	movl	%ecx,%esi
	andl	$1,%esi
	movl	%esi,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%ebp
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%ebp
	orb	%dl,%al
	testl	%ebp,%ebp
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%ebp,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	andb	$247,regflags+1
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%edi),%ebx
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e074:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e039:
	ret

FUNC(op_e0f9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ebx
RR2_e002:
	bswapl	%ebx
	movl	%ebx,%edi
	shrl	$14,%edi
	andl	$1020,%edi
	andl	$65535,%ebx
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebx,%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	movl	%ecx,%esi
	andl	$1,%esi
	movl	%esi,16-16(%esp)
	movb	regflags+4,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andb	$1,%dl
	orb	%dl,%al
	movb	%al,regflags+4
	movl	%ecx,%ebp
	movb	regflags,%al
	movb	16-16(%esp),%dl
	andb	$254,%al
	andl	$32768,%ebp
	orb	%dl,%al
	testl	%ebp,%ebp
	setne	%dl
	shrw	$1,%cx
	salb	$7,%dl
	andb	$127,%al
	orl	%ebp,%ecx
	orb	%dl,%al
	testw	%cx,%cx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	andb	$247,regflags+1
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%edi),%ebx
	rolw	$8,%ax
	movw	%ax,(%ebx)
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e075:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e040:
	ret

FUNC(op_e100)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movb	regflags+1,%cl
	movb	GLOBL(regs)(,%edx,4),%bl
	movl	GLOBL(imm8_table)(%eax),%esi
	movb	%cl,27-16(%esp)
	movl	$128,%ebp
	andb	$247,%cl
	andl	$63,%esi
	movb	%cl,regflags+1
	jne	L_e_1530
	andb	$254,regflags
	jmp	L_e_1531
	.align	2,0x90
L_e_1530:
	cmpl	$7,%esi
	jbe	L_e_1532
	testb	%bl,%bl
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movb	%al,regflags+1
	cmpl	$8,%esi
	jne	L_e_1533
	andl	$1,%ebx
	jmp	L_e_1534
	.align	2,0x90
L_e_1533:
	xorl	%ebx,%ebx
L_e_1534:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1531
	.align	2,0x90
L_e_1532:
	movl	$7,%eax
	subl	%esi,%eax
	movl	$255,%edx
	movl	%eax,%ecx
	andl	$255,%ebx
	sall	%cl,%edx
	leal	-1(%esi),%eax
	movl	%ebx,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andl	$255,%edx
	andb	$254,%al
	movl	%ebx,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1536
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1536:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%esi,%ecx
	orb	%dl,%al
	sall	%cl,%ebx
	movb	%al,regflags+1
L_e_1531:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	movl	16-16(%esp),%edi
	salb	$6,%dl
	andb	$-65,%al
	movl	%ecx,20-16(%esp)
	orb	%dl,%al
	movb	20-16(%esp),%cl
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e076:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e041:
	ret

FUNC(op_e108)

	subl	$12,%esp
	movl	%eax,%edx
	movl	%edx,%esi
	andl	$7,%esi
	shrl	$7,%eax
	movb	GLOBL(regs)(,%esi,4),%cl
	andl	$28,%eax
	movb	%cl,24-16(%esp)
	movl	GLOBL(imm8_table)(%eax),%ebp
	movl	$128,%edi
	andl	$63,%ebp
	jne	L_e_1539
	andb	$254,regflags
	jmp	L_e_1540
	.align	2,0x90
L_e_1539:
	cmpl	$7,%ebp
	jbe	L_e_1541
	cmpl	$8,%ebp
	jne	L_e_1542
	movb	24-16(%esp),%bl
	andl	$1,%ebx
	movl	%ebx,%ebp
	jmp	L_e_1543
	.align	2,0x90
L_e_1542:
	xorl	%ebp,%ebp
L_e_1543:
	movl	%ebp,%edx
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebp,%edx
	andb	$254,%al
	orb	%dl,%al
	movb	$0,24-16(%esp)
	movb	%al,regflags
	jmp	L_e_1540
	.align	2,0x90
L_e_1541:
	xorl	%ecx,%ecx
	movb	24-16(%esp),%cl
	leal	-1(%ebp),%eax
	movl	%ecx,20-16(%esp)
	movl	%ecx,%ebx
	movl	%eax,%ecx
	sall	%cl,%ebx
	movl	%ebx,%eax
	testl	%eax,%edi
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebp,%ecx
	andb	$254,%al
	movl	20-16(%esp),%ebx
	orb	%dl,%al
	sall	%cl,%ebx
	movb	%al,regflags
	movb	%bl,24-16(%esp)
L_e_1540:
	xorl	%ecx,%ecx
	movb	24-16(%esp),%cl
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	cmpb	$0,24-16(%esp)
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	movl	%ecx,16-16(%esp)
	orb	%dl,%al
	movb	16-16(%esp),%bl
	movb	%al,regflags
	movb	%bl,GLOBL(regs)(,%esi,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e077:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e042:
	ret

FUNC(op_e110)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	pushl	%ebx
	andl	$28,%eax
	movl	$128,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movb	GLOBL(regs)(,%ebp,4),%bl
	andl	$63,%esi
	je	L_e_1548
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1550
	cmpl	$3,%eax
	jge	L_e_1556
	cmpl	$2,%eax
	jge	L_e_1557
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1560
	orb	$1,%bl
L_e_1560:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1557:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1563
	orb	$1,%bl
L_e_1563:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1556:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1566
	orb	$1,%bl
L_e_1566:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1548
	.align	2,0x90
L_e_1550:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1569
	orb	$1,%bl
L_e_1569:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%dl,regflags+4
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1572
	orb	$1,%bl
L_e_1572:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%dl,regflags+4
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1575
	orb	$1,%bl
L_e_1575:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%cl,regflags+4
	andl	%edi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1578
	orb	$1,%bl
L_e_1578:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1550
L_e_1548:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movb	%bl,%cl
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e078:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e043:
	ret

FUNC(op_e118)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	andl	$28,%eax
	movl	$128,%esi
	movl	GLOBL(imm8_table)(%eax),%edx
	movb	GLOBL(regs)(,%edi,4),%bl
	andl	$63,%edx
	jne	L_e_1590
	andb	$254,regflags
	jmp	L_e_1582
	.align	2,0x90
L_e_1590:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1586
	cmpl	$3,%eax
	jge	L_e_1593
	cmpl	$2,%eax
	jge	L_e_1594
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1596
	orb	$1,%bl
L_e_1596:
	decl	%edx
L_e_1594:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1599
	orb	$1,%bl
L_e_1599:
	decl	%edx
L_e_1593:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testl	%eax,%eax
	je	L_e_1602
	orb	$1,%bl
L_e_1602:
	decl	%edx
	jz	L_e_1591
	.align	2,0x90
L_e_1586:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1605
	orb	$1,%bl
L_e_1605:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1608
	orb	$1,%bl
L_e_1608:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1611
	orb	$1,%bl
L_e_1611:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testl	%eax,%eax
	je	L_e_1614
	orb	$1,%bl
L_e_1614:
	addl	$-4,%edx
	jne	L_e_1586
L_e_1591:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1582:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e079:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e044:
	ret

FUNC(op_e120)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	movl	%edx,16-16(%esp)
	movl	$128,%ebp
	movl	$GLOBL(regs),%edx
	movl	16-16(%esp),%ecx
	andl	$28,%eax
	movb	(%edx,%ecx,4),%bl
	movb	regflags+1,%cl
	movb	(%eax,%edx),%dl
	movb	%cl,27-16(%esp)
	andb	$63,%dl
	andb	$247,%cl
	movl	%edx,%esi
	movb	%cl,regflags+1
	testb	%dl,%dl
	jne	L_e_1618
	andb	$254,regflags
	jmp	L_e_1619
	.align	2,0x90
L_e_1618:
	movl	%esi,%ecx
	cmpb	$7,%cl
	jle	L_e_1620
	testb	%bl,%bl
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movb	%al,regflags+1
	cmpb	$8,%cl
	jne	L_e_1621
	andl	$1,%ebx
	jmp	L_e_1622
	.align	2,0x90
L_e_1621:
	xorl	%ebx,%ebx
L_e_1622:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1619
	.align	2,0x90
L_e_1620:
	movl	%esi,%ecx
	movl	$7,%eax
	movsbl	%cl,%esi
	subl	%esi,%eax
	movl	$255,%edx
	movl	%eax,%ecx
	andl	$255,%ebx
	sall	%cl,%edx
	leal	-1(%esi),%eax
	movl	%ebx,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andl	$255,%edx
	andb	$254,%al
	movl	%ebx,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1624
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1624:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%esi,%ecx
	orb	%dl,%al
	sall	%cl,%ebx
	movb	%al,regflags+1
L_e_1619:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	movl	16-16(%esp),%edi
	salb	$6,%dl
	andb	$-65,%al
	movl	%ecx,20-16(%esp)
	orb	%dl,%al
	movb	20-16(%esp),%cl
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e045:
	ret

FUNC(op_e128)

	subl	$8,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$7,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	$128,%edi
	movb	(%eax,%edx),%al
	movb	(%edx,%ebp,4),%bl
	andb	$63,%al
	jne	L_e_1627
	andb	$254,regflags
	jmp	L_e_1628
	.align	2,0x90
L_e_1627:
	cmpb	$7,%al
	jle	L_e_1629
	cmpb	$8,%al
	jne	L_e_1630
	andl	$1,%ebx
	jmp	L_e_1631
	.align	2,0x90
L_e_1630:
	xorl	%ebx,%ebx
L_e_1631:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1628
	.align	2,0x90
L_e_1629:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movsbl	%al,%ebx
	movl	%ecx,20-16(%esp)
	leal	-1(%ebx),%eax
	movl	%ecx,%esi
	movl	%eax,%ecx
	sall	%cl,%esi
	movl	%esi,%eax
	testl	%eax,%edi
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebx,%ecx
	andb	$254,%al
	movl	20-16(%esp),%esi
	orb	%dl,%al
	sall	%cl,%esi
	movb	%al,regflags
	movl	%esi,%ebx
L_e_1628:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	movl	%ecx,16-16(%esp)
	orb	%dl,%al
	movb	16-16(%esp),%cl
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e046:
	ret

FUNC(op_e130)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%edi
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movb	(%edx,%edi,4),%bl
	movb	(%eax,%edx),%dl
	andb	$63,%dl
	movl	$128,%esi
	movb	%dl,15-12(%esp)
	testb	%dl,%dl
	je	L_e_1636
	movb	%dl,%al
	negb	%al
	andb	$3,%al
	je	L_e_1638
	cmpb	$3,%al
	jge	L_e_1644
	cmpb	$2,%al
	jge	L_e_1645
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1648
	orb	$1,%bl
L_e_1648:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	15-12(%esp)
	movb	%al,regflags+4
L_e_1645:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1651
	orb	$1,%bl
L_e_1651:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	15-12(%esp)
	movb	%al,regflags+4
L_e_1644:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1654
	orb	$1,%bl
L_e_1654:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decb	15-12(%esp)
	jmp	L_e_1668
	.align	2,0x90
	.align	2,0x90
L_e_1638:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1657
	orb	$1,%bl
L_e_1657:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%dl,regflags+4
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1660
	orb	$1,%bl
L_e_1660:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%dl,regflags+4
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1663
	orb	$1,%bl
L_e_1663:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	xorl	%eax,%eax
	movb	%bl,%al
	movb	%cl,regflags+4
	andl	%esi,%eax
	addb	%bl,%bl
	testb	$1,regflags+4
	je	L_e_1666
	orb	$1,%bl
L_e_1666:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addb	$-4,15-12(%esp)
L_e_1668:
	movb	%al,regflags+4
	cmpb	$0,15-12(%esp)
	jne	L_e_1638
L_e_1636:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movb	%bl,%cl
	orb	%dl,%al
	testl	%ecx,%esi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e082:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e047:
	ret

FUNC(op_e138)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movb	(%edx,%edi,4),%bl
	movb	(%eax,%edx),%dl
	movl	$128,%esi
	andb	$63,%dl
	jne	L_e_1679
	andb	$254,regflags
	jmp	L_e_1671
	.align	2,0x90
L_e_1679:
	movb	%dl,%al
	negb	%al
	andb	$3,%al
	je	L_e_1675
	cmpb	$3,%al
	jge	L_e_1682
	cmpb	$2,%al
	jge	L_e_1683
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1685
	orb	$1,%bl
L_e_1685:
	decb	%dl
L_e_1683:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1688
	orb	$1,%bl
L_e_1688:
	decb	%dl
L_e_1682:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testl	%eax,%eax
	je	L_e_1691
	orb	$1,%bl
L_e_1691:
	decb	%dl
	je	L_e_1680
	.align	2,0x90
L_e_1675:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1694
	orb	$1,%bl
L_e_1694:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1697
	orb	$1,%bl
L_e_1697:
	xorl	%eax,%eax
	movb	%bl,%al
	addb	%bl,%bl
	testl	%eax,%esi
	je	L_e_1700
	orb	$1,%bl
L_e_1700:
	xorl	%eax,%eax
	movb	%bl,%al
	andl	%esi,%eax
	addb	%bl,%bl
	testl	%eax,%eax
	je	L_e_1703
	orb	$1,%bl
L_e_1703:
	addb	$-4,%dl
	jne	L_e_1675
L_e_1680:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1671:
	xorl	%ecx,%ecx
	movb	%bl,%cl
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testb	%bl,%bl
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movb	%cl,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e083:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e048:
	ret

FUNC(op_e140)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movb	regflags+1,%cl
	movw	GLOBL(regs)(,%edx,4),%bx
	movl	GLOBL(imm8_table)(%eax),%esi
	movb	%cl,27-16(%esp)
	movl	$32768,%ebp
	andb	$247,%cl
	andl	$63,%esi
	movb	%cl,regflags+1
	jne	L_e_1707
	andb	$254,regflags
	jmp	L_e_1708
	.align	2,0x90
L_e_1707:
	cmpl	$15,%esi
	jbe	L_e_1709
	testw	%bx,%bx
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movb	%al,regflags+1
	cmpl	$16,%esi
	jne	L_e_1710
	andl	$1,%ebx
	jmp	L_e_1711
	.align	2,0x90
L_e_1710:
	xorl	%ebx,%ebx
L_e_1711:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1708
	.align	2,0x90
L_e_1709:
	movl	$15,%eax
	subl	%esi,%eax
	movl	$65535,%edx
	movl	%eax,%ecx
	andl	$65535,%ebx
	sall	%cl,%edx
	leal	-1(%esi),%eax
	movl	%ebx,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andl	$65535,%edx
	andb	$254,%al
	movl	%ebx,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1713
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1713:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%esi,%ecx
	orb	%dl,%al
	sall	%cl,%ebx
	movb	%al,regflags+1
L_e_1708:
	xorl	%edi,%edi
	movw	%bx,%di
	movb	regflags,%al
	testl	%edi,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	movl	16-16(%esp),%ecx
	salb	$6,%dl
	andb	$-65,%al
	movl	%edi,20-16(%esp)
	orb	%dl,%al
	movl	20-16(%esp),%edi
	movb	%al,regflags
	movw	%di,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e084:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e049:
	ret

FUNC(op_e148)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movl	$32768,%ebp
	movl	GLOBL(imm8_table)(%eax),%ebx
	movw	GLOBL(regs)(,%edx,4),%si
	andl	$63,%ebx
	jne	L_e_1716
	andb	$254,regflags
	jmp	L_e_1717
	.align	2,0x90
L_e_1716:
	cmpl	$15,%ebx
	jbe	L_e_1718
	cmpl	$16,%ebx
	jne	L_e_1719
	movl	%esi,%ebx
	andl	$1,%ebx
	jmp	L_e_1720
	.align	2,0x90
L_e_1719:
	xorl	%ebx,%ebx
L_e_1720:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	jmp	L_e_1723
	.align	2,0x90
L_e_1718:
	xorl	%ecx,%ecx
	movw	%si,%cx
	leal	-1(%ebx),%eax
	movl	%ecx,24-16(%esp)
	movl	%ecx,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	24-16(%esp),%esi
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sall	%cl,%esi
L_e_1723:
	movb	%al,regflags
L_e_1717:
	xorl	%edi,%edi
	movw	%si,%di
	movb	regflags,%al
	testl	%edi,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	andb	$247,regflags+1
	orb	%dl,%al
	testw	%si,%si
	sete	%dl
	movl	16-16(%esp),%ecx
	salb	$6,%dl
	andb	$-65,%al
	movl	%edi,20-16(%esp)
	orb	%dl,%al
	movl	20-16(%esp),%edi
	movb	%al,regflags
	movw	%di,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e085:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e050:
	ret

FUNC(op_e150)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	pushl	%ebx
	andl	$28,%eax
	movl	$32768,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movw	GLOBL(regs)(,%ebp,4),%bx
	andl	$63,%esi
	je	L_e_1726
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1728
	cmpl	$3,%eax
	jge	L_e_1734
	cmpl	$2,%eax
	jge	L_e_1735
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1738
	orl	$1,%ebx
L_e_1738:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1735:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1741
	orl	$1,%ebx
L_e_1741:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1734:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1744
	orl	$1,%ebx
L_e_1744:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1726
	.align	2,0x90
L_e_1728:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1747
	orl	$1,%ebx
L_e_1747:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%dl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1750
	orl	$1,%ebx
L_e_1750:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%dl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1753
	orl	$1,%ebx
L_e_1753:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%cl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1756
	orl	$1,%ebx
L_e_1756:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1728
L_e_1726:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movw	%bx,%cx
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e086:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e051:
	ret

FUNC(op_e158)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	andl	$28,%eax
	movl	$32768,%esi
	movl	GLOBL(imm8_table)(%eax),%edx
	movw	GLOBL(regs)(,%edi,4),%bx
	andl	$63,%edx
	jne	L_e_1768
	andb	$254,regflags
	jmp	L_e_1760
	.align	2,0x90
L_e_1768:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1764
	cmpl	$3,%eax
	jge	L_e_1771
	cmpl	$2,%eax
	jge	L_e_1772
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1774
	orl	$1,%ebx
L_e_1774:
	decl	%edx
L_e_1772:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1777
	orl	$1,%ebx
L_e_1777:
	decl	%edx
L_e_1771:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%esi,%eax
	addw	%bx,%bx
	testl	%eax,%eax
	je	L_e_1780
	orl	$1,%ebx
L_e_1780:
	decl	%edx
	jz	L_e_1769
	.align	2,0x90
L_e_1764:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1783
	orl	$1,%ebx
L_e_1783:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1786
	orl	$1,%ebx
L_e_1786:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1789
	orl	$1,%ebx
L_e_1789:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%esi,%eax
	addw	%bx,%bx
	testl	%eax,%eax
	je	L_e_1792
	orl	$1,%ebx
L_e_1792:
	addl	$-4,%edx
	jne	L_e_1764
L_e_1769:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1760:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e087:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e052:
	ret

FUNC(op_e160)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	%edx,16-16(%esp)
	shrl	$7,%eax
	movl	$GLOBL(regs),%edx
	movl	16-16(%esp),%ecx
	andl	$28,%eax
	movw	(%edx,%ecx,4),%bx
	movb	regflags+1,%cl
	movw	(%eax,%edx),%si
	movb	%cl,27-16(%esp)
	movl	$32768,%ebp
	andb	$247,%cl
	andl	$63,%esi
	movb	%cl,regflags+1
	jne	L_e_1796
	andb	$254,regflags
	jmp	L_e_1797
	.align	2,0x90
L_e_1796:
	cmpw	$15,%si
	jle	L_e_1798
	testw	%bx,%bx
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movb	%al,regflags+1
	cmpw	$16,%si
	jne	L_e_1799
	andl	$1,%ebx
	jmp	L_e_1800
	.align	2,0x90
L_e_1799:
	xorl	%ebx,%ebx
L_e_1800:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1797
	.align	2,0x90
L_e_1798:
	movswl	%si,%esi
	movl	$15,%eax
	subl	%esi,%eax
	movl	$65535,%edx
	movl	%eax,%ecx
	andl	$65535,%ebx
	sall	%cl,%edx
	leal	-1(%esi),%eax
	movl	%ebx,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andl	$65535,%edx
	andb	$254,%al
	movl	%ebx,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1802
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1802:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%esi,%ecx
	orb	%dl,%al
	sall	%cl,%ebx
	movb	%al,regflags+1
L_e_1797:
	xorl	%edi,%edi
	movw	%bx,%di
	movb	regflags,%al
	testl	%edi,%ebp
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	movl	16-16(%esp),%ecx
	salb	$6,%dl
	andb	$-65,%al
	movl	%edi,20-16(%esp)
	orb	%dl,%al
	movl	20-16(%esp),%edi
	movb	%al,regflags
	movw	%di,GLOBL(regs)(,%ecx,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e053:
	ret

FUNC(op_e168)

	subl	$8,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$7,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	$32768,%edi
	movw	(%eax,%edx),%ax
	movw	(%edx,%ebp,4),%bx
	andl	$63,%eax
	jne	L_e_1805
	andb	$254,regflags
	jmp	L_e_1806
	.align	2,0x90
L_e_1805:
	cmpw	$15,%ax
	jle	L_e_1807
	cmpw	$16,%ax
	jne	L_e_1808
	andl	$1,%ebx
	jmp	L_e_1809
	.align	2,0x90
L_e_1808:
	xorl	%ebx,%ebx
L_e_1809:
	movb	%bl,%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	%bl,%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%ebx,%ebx
	movb	%al,regflags
	jmp	L_e_1806
	.align	2,0x90
L_e_1807:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movswl	%ax,%ebx
	movl	%ecx,20-16(%esp)
	leal	-1(%ebx),%eax
	movl	%ecx,%esi
	movl	%eax,%ecx
	sall	%cl,%esi
	movl	%esi,%eax
	testl	%eax,%edi
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movl	%ebx,%ecx
	andb	$254,%al
	movl	20-16(%esp),%esi
	orb	%dl,%al
	sall	%cl,%esi
	movb	%al,regflags
	movl	%esi,%ebx
L_e_1806:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%edi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	andb	$247,regflags+1
	salb	$6,%dl
	andb	$-65,%al
	movl	%ecx,16-16(%esp)
	orb	%dl,%al
	movl	16-16(%esp),%esi
	movb	%al,regflags
	movw	%si,GLOBL(regs)(,%ebp,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e089:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e054:
	ret

FUNC(op_e170)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	pushl	%ebx
	andl	$28,%eax
	movl	$32768,%edi
	movw	(%eax,%edx),%si
	movw	(%edx,%ebp,4),%bx
	andl	$63,%esi
	je	L_e_1814
	movl	%esi,%eax
	negw	%ax
	andl	$3,%eax
	je	L_e_1816
	cmpw	$3,%ax
	jge	L_e_1822
	cmpw	$2,%ax
	jge	L_e_1823
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1826
	orl	$1,%ebx
L_e_1826:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1823:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1829
	orl	$1,%ebx
L_e_1829:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1822:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1832
	orl	$1,%ebx
L_e_1832:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	jmp	L_e_1846
	.align	2,0x90
	.align	2,0x90
L_e_1816:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1835
	orl	$1,%ebx
L_e_1835:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%dl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1838
	orl	$1,%ebx
L_e_1838:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%dl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1841
	orl	$1,%ebx
L_e_1841:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	xorl	%eax,%eax
	movw	%bx,%ax
	movb	%cl,regflags+4
	andl	%edi,%eax
	addw	%bx,%bx
	testb	$1,regflags+4
	je	L_e_1844
	orl	$1,%ebx
L_e_1844:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
L_e_1846:
	movb	%al,regflags+4
	testw	%si,%si
	jne	L_e_1816
L_e_1814:
	movb	regflags+4,%dl
	movb	regflags,%al
	xorl	%ecx,%ecx
	andb	$1,%dl
	andb	$254,%al
	movw	%bx,%cx
	orb	%dl,%al
	testl	%ecx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e090:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e055:
	ret

FUNC(op_e178)

	movl	%eax,%edx
	pushl	%esi
	movl	%edx,%edi
	pushl	%ebx
	shrl	$7,%eax
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movw	(%edx,%edi,4),%bx
	movw	(%eax,%edx),%dx
	movl	$32768,%esi
	andl	$63,%edx
	jne	L_e_1857
	andb	$254,regflags
	jmp	L_e_1849
	.align	2,0x90
L_e_1857:
	movl	%edx,%eax
	negw	%ax
	andl	$3,%eax
	je	L_e_1853
	cmpw	$3,%ax
	jge	L_e_1860
	cmpw	$2,%ax
	jge	L_e_1861
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1863
	orl	$1,%ebx
L_e_1863:
	decl	%edx
L_e_1861:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1866
	orl	$1,%ebx
L_e_1866:
	decl	%edx
L_e_1860:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%esi,%eax
	addw	%bx,%bx
	testl	%eax,%eax
	je	L_e_1869
	orl	$1,%ebx
L_e_1869:
	decw	%dx
	je	L_e_1858
	.align	2,0x90
L_e_1853:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1872
	orl	$1,%ebx
L_e_1872:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1875
	orl	$1,%ebx
L_e_1875:
	xorl	%eax,%eax
	movw	%bx,%ax
	addw	%bx,%bx
	testl	%eax,%esi
	je	L_e_1878
	orl	$1,%ebx
L_e_1878:
	xorl	%eax,%eax
	movw	%bx,%ax
	andl	%esi,%eax
	addw	%bx,%bx
	testl	%eax,%eax
	je	L_e_1881
	orl	$1,%ebx
L_e_1881:
	addw	$-4,%dx
	jne	L_e_1853
L_e_1858:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1849:
	xorl	%ecx,%ecx
	movw	%bx,%cx
	movb	regflags,%al
	testl	%ecx,%esi
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movw	%cx,GLOBL(regs)(,%edi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e091:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e056:
	ret

FUNC(op_e180)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movb	regflags+1,%cl
	movl	GLOBL(regs)(,%edx,4),%esi
	movl	GLOBL(imm8_table)(%eax),%ebx
	movb	%cl,27-16(%esp)
	movl	$-2147483648,%ebp
	andb	$247,%cl
	andl	$63,%ebx
	movb	%cl,regflags+1
	jne	L_e_1885
	andb	$254,regflags
	jmp	L_e_1886
	.align	2,0x90
L_e_1885:
	cmpl	$31,%ebx
	jbe	L_e_1887
	testl	%esi,%esi
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movl	$0,20-16(%esp)
	movb	%al,regflags+1
	cmpl	$32,%ebx
	jne	L_e_1888
	andl	$1,%esi
	movl	%esi,20-16(%esp)
L_e_1888:
	movb	20-16(%esp),%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	20-16(%esp),%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	movb	%al,regflags
	jmp	L_e_1886
	.align	2,0x90
L_e_1887:
	movl	$31,%eax
	subl	%ebx,%eax
	movl	$-1,%edx
	movl	%eax,%ecx
	sall	%cl,%edx
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%esi,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1891
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1891:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sall	%cl,%esi
	movb	%al,regflags+1
L_e_1886:
	testl	%esi,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	16-16(%esp),%edi
	movl	%esi,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e092:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e057:
	ret

FUNC(op_e188)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	%edx,16-16(%esp)
	movl	$-2147483648,%ebp
	movl	GLOBL(imm8_table)(%eax),%ebx
	movl	GLOBL(regs)(,%edx,4),%esi
	andl	$63,%ebx
	jne	L_e_1894
	andb	$254,regflags
	jmp	L_e_1895
	.align	2,0x90
L_e_1894:
	cmpl	$31,%ebx
	jbe	L_e_1896
	movl	$0,20-16(%esp)
	cmpl	$32,%ebx
	jne	L_e_1897
	andl	$1,%esi
	movl	%esi,20-16(%esp)
L_e_1897:
	movb	20-16(%esp),%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	20-16(%esp),%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	jmp	L_e_1901
	.align	2,0x90
L_e_1896:
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sall	%cl,%esi
L_e_1901:
	movb	%al,regflags
L_e_1895:
	testl	%esi,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	16-16(%esp),%edi
	movl	%esi,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e093:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e058:
	ret

FUNC(op_e190)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	pushl	%ebx
	andl	$28,%eax
	movl	$-2147483648,%edi
	movl	GLOBL(imm8_table)(%eax),%esi
	movl	GLOBL(regs)(,%ebp,4),%ebx
	andl	$63,%esi
	je	L_e_1904
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1906
	cmpl	$3,%eax
	jge	L_e_1912
	cmpl	$2,%eax
	jge	L_e_1913
	movl	%ebx,%eax
	andl	%edi,%eax
	addl	%ebx,%ebx
	testb	$1,regflags+4
	je	L_e_1916
	orl	$1,%ebx
L_e_1916:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1913:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1919
	orl	$1,%ebx
L_e_1919:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_1912:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1922
	orl	$1,%ebx
L_e_1922:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1904
	.align	2,0x90
L_e_1906:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1925
	orl	$1,%ebx
L_e_1925:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%dl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1928
	orl	$1,%ebx
L_e_1928:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%dl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1931
	orl	$1,%ebx
L_e_1931:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%cl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_1934
	orl	$1,%ebx
L_e_1934:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1906
L_e_1904:
	movb	regflags+4,%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	testl	%ebx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	%ebx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e094:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e059:
	ret

FUNC(op_e198)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%esi
	shrl	$7,%eax
	andl	$7,%esi
	andl	$28,%eax
	movl	$-2147483648,%ebx
	movl	GLOBL(imm8_table)(%eax),%edx
	movl	GLOBL(regs)(,%esi,4),%ecx
	andl	$63,%edx
	jne	L_e_1946
	andb	$254,regflags
	jmp	L_e_1938
	.align	2,0x90
L_e_1946:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1942
	cmpl	$3,%eax
	jge	L_e_1949
	cmpl	$2,%eax
	jge	L_e_1950
	movl	%ecx,%eax
	andl	%ebx,%eax
	addl	%ecx,%ecx
	testl	%eax,%eax
	je	L_e_1952
	orl	$1,%ecx
L_e_1952:
	decl	%edx
L_e_1950:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1955
	orl	$1,%ecx
L_e_1955:
	decl	%edx
L_e_1949:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1958
	orl	$1,%ecx
L_e_1958:
	decl	%edx
	jz	L_e_1947
	.align	2,0x90
L_e_1942:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1961
	orl	$1,%ecx
L_e_1961:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1964
	orl	$1,%ecx
L_e_1964:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1967
	orl	$1,%ecx
L_e_1967:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_1970
	orl	$1,%ecx
L_e_1970:
	addl	$-4,%edx
	jne	L_e_1942
L_e_1947:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1938:
	testl	%ecx,%ebx
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%ecx,%ecx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	%ecx,GLOBL(regs)(,%esi,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e060:
	ret

FUNC(op_e1a0)

	subl	$12,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	%edx,16-16(%esp)
	shrl	$7,%eax
	movl	$GLOBL(regs),%edx
	movl	16-16(%esp),%ecx
	andl	$28,%eax
	movl	(%edx,%ecx,4),%esi
	movb	regflags+1,%cl
	movl	(%eax,%edx),%ebx
	movb	%cl,27-16(%esp)
	movl	$-2147483648,%ebp
	andb	$247,%cl
	andl	$63,%ebx
	movb	%cl,regflags+1
	jne	L_e_1974
	andb	$254,regflags
	jmp	L_e_1975
	.align	2,0x90
L_e_1974:
	cmpl	$31,%ebx
	jle	L_e_1976
	testl	%esi,%esi
	setne	%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	movl	$0,20-16(%esp)
	movb	%al,regflags+1
	cmpl	$32,%ebx
	jne	L_e_1977
	andl	$1,%esi
	movl	%esi,20-16(%esp)
L_e_1977:
	movb	20-16(%esp),%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	20-16(%esp),%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	movb	%al,regflags
	jmp	L_e_1975
	.align	2,0x90
L_e_1976:
	movl	$31,%eax
	subl	%ebx,%eax
	movl	$-1,%edx
	movl	%eax,%ecx
	sall	%cl,%edx
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%cl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%cl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%esi,%edi
	orb	%cl,%al
	andl	%edx,%edi
	movb	%al,regflags
	movl	%edi,20-16(%esp)
	xorl	%eax,%eax
	cmpl	%edx,%edi
	je	L_e_1980
	testl	%edi,%edi
	setne	%al
	andl	$255,%eax
L_e_1980:
	movb	%al,%dl
	andb	$1,%dl
	movb	27-16(%esp),%al
	salb	$3,%dl
	andb	$247,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sall	%cl,%esi
	movb	%al,regflags+1
L_e_1975:
	testl	%esi,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	movb	%dl,regflags
	movl	16-16(%esp),%edi
	movl	%esi,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e061:
	ret

FUNC(op_e1a8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	shrl	$7,%eax
	movl	$-2147483648,%ebp
	movl	%edx,16-16(%esp)
	andl	$28,%eax
	movl	$GLOBL(regs),%edx
	movl	16-16(%esp),%ecx
	movl	(%eax,%edx),%ebx
	movl	(%edx,%ecx,4),%esi
	andl	$63,%ebx
	jne	L_e_1983
	andb	$254,regflags
	jmp	L_e_1984
	.align	2,0x90
L_e_1983:
	cmpl	$31,%ebx
	jle	L_e_1985
	movl	$0,20-16(%esp)
	cmpl	$32,%ebx
	jne	L_e_1986
	andl	$1,%esi
	movl	%esi,20-16(%esp)
L_e_1986:
	movb	20-16(%esp),%dl
	movb	regflags+4,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	movb	20-16(%esp),%dl
	andb	$254,%al
	orb	%dl,%al
	xorl	%esi,%esi
	jmp	L_e_1990
	.align	2,0x90
L_e_1985:
	leal	-1(%ebx),%eax
	movl	%esi,%edi
	movl	%eax,%ecx
	sall	%cl,%edi
	movl	%edi,%eax
	testl	%eax,%ebp
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	movl	%ebx,%ecx
	orb	%dl,%al
	sall	%cl,%esi
L_e_1990:
	movb	%al,regflags
L_e_1984:
	testl	%esi,%ebp
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%esi,%esi
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	16-16(%esp),%edi
	movl	%esi,GLOBL(regs)(,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e062:
	ret

FUNC(op_e1b0)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ebp
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	pushl	%ebx
	andl	$28,%eax
	movl	$-2147483648,%edi
	movl	(%eax,%edx),%esi
	movl	(%edx,%ebp,4),%ebx
	andl	$63,%esi
	je	L_e_1993
	movl	%esi,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1995
	cmpl	$3,%eax
	jge	L_e_2001
	cmpl	$2,%eax
	jge	L_e_2002
	movl	%ebx,%eax
	andl	%edi,%eax
	addl	%ebx,%ebx
	testb	$1,regflags+4
	je	L_e_2005
	orl	$1,%ebx
L_e_2005:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_2002:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2008
	orl	$1,%ebx
L_e_2008:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	decl	%esi
	movb	%al,regflags+4
L_e_2001:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2011
	orl	$1,%ebx
L_e_2011:
	testl	%eax,%eax
	setne	%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	decl	%esi
	jz	L_e_1993
	.align	2,0x90
L_e_1995:
	movl	%ebx,%eax
	addl	%ebx,%ebx
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2014
	orl	$1,%ebx
L_e_2014:
	movb	regflags+4,%dl
	testl	%eax,%eax
	setne	%al
	andb	$254,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%dl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2017
	orl	$1,%ebx
L_e_2017:
	testl	%eax,%eax
	setne	%al
	andb	$-2,%dl
	orb	%al,%dl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%dl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2020
	orl	$1,%ebx
L_e_2020:
	movb	%dl,%cl
	testl	%eax,%eax
	setne	%al
	andb	$-2,%cl
	orb	%al,%cl
	movl	%ebx,%eax
	addl	%ebx,%ebx
	movb	%cl,regflags+4
	andl	%edi,%eax
	testb	$1,regflags+4
	je	L_e_2023
	orl	$1,%ebx
L_e_2023:
	testl	%eax,%eax
	setne	%dl
	movb	%cl,%al
	andb	$-2,%al
	orb	%dl,%al
	addl	$-4,%esi
	movb	%al,regflags+4
	jne	L_e_1995
L_e_1993:
	movb	regflags+4,%dl
	movb	regflags,%al
	andb	$1,%dl
	andb	$254,%al
	orb	%dl,%al
	testl	%ebx,%edi
	setne	%dl
	salb	$7,%dl
	andb	$127,%al
	orb	%dl,%al
	testl	%ebx,%ebx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	andb	$247,regflags+1
	movb	%al,regflags
	movl	%ebx,GLOBL(regs)(,%ebp,4)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e063:
	ret

FUNC(op_e1d0)

	subl	$8,%esp
	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ebp,%ebp
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%bp
	leal	0(,%edx,4),%edi
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2048
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2048:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e099:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e064:
	ret

FUNC(op_e1d8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	xorl	%eax,%eax
	movb	2(%edx,%ebx),%al
	movl	(%edx,%ebx),%ebp
	leal	0(,%eax,4),%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	(%edx,%ebx),%ecx
	addl	$2,%ecx
	movl	%ecx,(%edx,%ebx)
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2055
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2055:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e100:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e065:
	ret

FUNC(op_e1e0)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	sall	$2,%edx
	movl	$GLOBL(regs),%ebx
	movl	(%edx,%ebx),%ecx
	addl	$-2,%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	movl	%ecx,16-16(%esp)
	movl	%eax,%edi
	movl	%ecx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	16-16(%esp),%ecx
	movl	%ecx,(%edx,%ebx)
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2062
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2062:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$2,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e101:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e066:
	ret

FUNC(op_e1e8)

	subl	$8,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_e003:
	rolw	$8,%cx
	movl	%ecx,%eax
	addl	$8,%edx
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%edi
	movl	%eax,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2070
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2070:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e102:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e067:
	ret

FUNC(op_e1f0)

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
RR0_e103:
	rolw	$8,%si
	movl	GLOBL(regs)(,%eax,4),%ebp
	movl	%esi,%eax
	movl	%ecx,24-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_e_2077
	movswl	%di,%edi
L_e_2077:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_2078
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_2079
	movl	%ebp,%ebx
L_e_2079:
	testl	$64,%esi
	je	L_e_2080
	movl	%ebp,%edi
L_e_2080:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_2081
	movl	24-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e104:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_2081:
	cmpl	$48,%edx
	jne	L_e_2084
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e105:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_2084:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_2087
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e106:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_2087:
	cmpl	$3,16-16(%esp)
	jne	L_e_2090
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e107:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_2090:
	andl	$4,%esi
	jne	L_e_2093
	addl	%edi,%ebx
L_e_2093:
	cmpl	$0,16-16(%esp)
	je	L_e_2094
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_2094:
	testl	%esi,%esi
	je	L_e_2097
	addl	%edi,%ebx
L_e_2097:
	leal	(%ebp,%ebx),%edx
	jmp	L_e_2098
	.align	2,0x90
L_e_2078:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_e_2098:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2102
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2102:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e108:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e068:
	ret

FUNC(op_e1f8)

	subl	$8,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_e004:
	rolw	$8,%cx
	movl	%ecx,%eax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%edx,%edi
	movl	%eax,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2110
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2110:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e109:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e069:
	ret

FUNC(op_e1f9)

	subl	$8,%esp
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_e005:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%eax,%edi
	movl	%edx,%ebp
	andl	$1020,%edi
	andl	$65535,%ebp
	movl	GLOBL(R24)(%edi),%eax
	addl	%ebp,%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	movb	regflags+1,%cl
	andb	$247,%cl
	movl	%eax,%ebx
	movb	%cl,23-16(%esp)
	movb	%cl,regflags+1
	movl	%ebx,%ecx
	movb	regflags+4,%al
	andl	$32768,%ecx
	andb	$254,%al
	testl	%ecx,%ecx
	setne	%dl
	orb	%dl,%al
	movb	%al,regflags+4
	xorl	%esi,%esi
	movb	regflags,%al
	addw	%bx,%bx
	andb	$254,%al
	movw	%bx,%si
	orb	%dl,%al
	movl	%esi,%edx
	movb	%al,regflags
	andl	$32768,%edx
	cmpl	%ecx,%edx
	je	L_e_2118
	movb	23-16(%esp),%cl
	orb	$8,%cl
	movb	%cl,regflags+1
L_e_2118:
	testl	%edx,%edx
	setne	%dl
	andb	$127,%al
	salb	$7,%dl
	orb	%dl,%al
	testw	%bx,%bx
	sete	%dl
	salb	$6,%dl
	andb	$-65,%al
	orb	%dl,%al
	movb	%al,regflags
	movl	GLOBL(W24)(%edi),%edx
	movl	%esi,%eax
	rolw	$8,%ax
	addl	%ebp,%edx
	movw	%ax,(%edx)
	addl	$6,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e110:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e070:
	ret

FUNC(op_e2f0)

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
RR0_e111:
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
	jne	L_e_2175
	movswl	%di,%edi
L_e_2175:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_e_2176
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_e_2177
	movl	%ebp,%ebx
L_e_2177:
	testl	$64,%esi
	je	L_e_2178
	movl	%ebp,%edi
L_e_2178:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_e_2179
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_e112:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_e_2179:
	cmpl	$48,%edx
	jne	L_e_2182
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e113:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_e_2182:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_e_2185
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_e114:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_2185:
	cmpl	$3,16-16(%esp)
	jne	L_e_2188
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_e115:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_e_2188:
	andl	$4,%esi
	jne	L_e_2191
	addl	%edi,%ebx
L_e_2191:
	cmpl	$0,16-16(%esp)
	je	L_e_2192
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_e_2192:
	testl	%esi,%esi
	je	L_e_2195
	addl	%edi,%ebx
L_e_2195:
	leal	(%ebp,%ebx),%eax
	jmp	L_e_2196
	.align	2,0x90
L_e_2176:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_e_2196:
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
	shrw	$1,%dx
	andl	$1,%eax
	testw	%dx,%dx
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,16-16(%esp)
	movb	regflags+4,%al
	andb	$254,%al
	orb	16-16(%esp),%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	16-16(%esp),%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%dx,%ax
	addl	GLOBL(W24)(%ebx),%esi
	rolw	$8,%ax
	movw	%ax,(%esi)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e071:
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
.comm	_F3SystemEEPROMAccess,4
.comm	_RAMSize,4
.comm	_SourceSeg,4
.comm	_DestSeg,4
.comm	_SourceStart,4
.comm	_DestStart,4
.comm	_BlitWidth,4
.comm	_BlitHeight,4
.comm	_SourceAdd,4
.comm	_DestAdd,4
.comm	_TimerCounter,4
.comm	_TimerCounterB,4
.comm	_RefreshBuffers,4
.comm	regflags,8
.comm	GLOBL(regs),180


FUNC(op_d0f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_e006:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
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
	cwtl
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e117:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e072:
	ret

FUNC(op_d0f9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_e007:
	bswapl	%eax
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
	cwtl
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e118:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e073:
	ret

FUNC(op_d0fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_e008:
	rolw	$8,%dx
	movswl	%dx,%edx
	leal	2(%edx,%eax),%eax
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
	cwtl
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e119:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e074:
	ret

FUNC(op_d0fc)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_e009:
	rolw	$8,%cx
	movl	%ecx,%eax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	addl	%eax,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e075:
	ret

FUNC(op_d110)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%edx
	movl	$GLOBL(regs),%esi
	xorl	%eax,%eax
	addl	$8,%edx
	xorl	%ebx,%ebx
	movb	2(%esi,%edx,4),%al
	movw	(%esi,%edx,4),%bx
	sall	$2,%eax
	shrl	$7,%ecx
	movl	GLOBL(R24)(%eax),%edx
	andl	$28,%ecx
	movb	(%ebx,%edx),%dl
	addb	(%ecx,%esi),%dl
	pushfl
	popl	%ecx
	movl	%ecx,regflags
	movl	%ecx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ebx,%eax)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e076:
	ret

FUNC(op_d118)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	movl	%edx,%ebp
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%ebp
	movb	(%eax,%esi),%al
	leal	8(%ebp),%ebx
	movb	%al,19-16(%esp)
	sall	$2,%ebx
	xorl	%edx,%edx
	movl	(%ebx,%esi),%ecx
	movb	2(%ebx,%esi),%dl
	movl	%ecx,%edi
	sall	$2,%edx
	andl	$65535,%edi
	movl	GLOBL(R24)(%edx),%eax
	addl	GLOBL(areg_byteinc)(,%ebp,4),%ecx
	movb	(%edi,%eax),%al
	movl	%ecx,(%ebx,%esi)
	movb	%al,%cl
	addb	19-16(%esp),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e077:
	ret

FUNC(op_d120)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%eax
	andl	$28,%eax
	movl	$GLOBL(regs),%esi
	andl	$7,%edx
	movb	(%eax,%esi),%al
	leal	8(%edx),%ebx
	movb	%al,15-12(%esp)
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(,%edx,4),%eax
	movl	(%ebx,%esi),%ecx
	subl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	movl	%ecx,%edi
	andl	$1020,%edx
	andl	$65535,%edi
	movl	GLOBL(R24)(%edx),%eax
	movb	(%edi,%eax),%al
	movl	%ecx,(%ebx,%esi)
	movb	%al,%cl
	addb	15-12(%esp),%cl
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	GLOBL(W24)(%edx),%eax
	movb	%cl,(%edi,%eax)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e078:
	ret

FUNC(op_d128)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_e010:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%edx
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	shrl	$7,%ebx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%ecx
	andl	$28,%ebx
	movb	(%eax,%ecx),%cl
	addb	(%ebx,%esi),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e079:
	ret

FUNC(op_d138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_e011:
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
	addb	GLOBL(regs)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e080:
	ret

FUNC(op_d139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_e012:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	andl	$28,%ebx
	movb	(%ecx,%edx),%dl
	addb	GLOBL(regs)(%ebx),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e081:
	ret

FUNC(op_d150)

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
	addw	(%ebx,%esi),%ax
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
	jl	JJ_e082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e082:
	ret

FUNC(op_d158)

	movl	%eax,%edx
	pushl	%edi
	movl	%edx,%ecx
	pushl	%esi
	shrl	$7,%eax
	andl	$7,%ecx
	pushl	%ebx
	andl	$28,%eax
	addl	$8,%ecx
	movw	GLOBL(regs)(%eax),%bp
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	GLOBL(regs)(%ecx),%edx
	movb	GLOBL(regs)+2(%ecx),%bl
	movl	%edx,%esi
	sall	$2,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	$2,%edx
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
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
	jl	JJ_e083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e083:
	ret

FUNC(op_d160)

	movl	%eax,%edx
	movl	%edx,%ecx
	pushl	%edi
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	GLOBL(regs)(%ecx),%edx
	shrl	$7,%eax
	addl	$-2,%edx
	andl	$28,%eax
	movl	%edx,%ebx
	movw	GLOBL(regs)(%eax),%bp
	shrl	$14,%ebx
	movl	%edx,%esi
	andl	$1020,%ebx
	andl	$65535,%esi
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%edx,GLOBL(regs)(%ecx)
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
	jl	JJ_e084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e084:
	ret

FUNC(op_d168)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_e013:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%edx
	cwtl
	addl	(%esi,%edx,4),%eax
	movl	%eax,%ecx
	shrl	$14,%ecx
	shrl	$7,%ebx
	andl	$1020,%ecx
	andl	$65535,%eax
	movl	GLOBL(R24)(%ecx),%edx
	andl	$28,%ebx
	addl	%eax,%edx
	xorl	%edi,%edi
	movw	(%edx),%di
	rolw	$8,%di
	movl	%edi,%edx
	addw	(%ebx,%esi),%dx
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	andl	$65535,%edx
	addl	GLOBL(W24)(%ecx),%eax
	rolw	$8,%dx
	movw	%dx,(%eax)
	popl	%ebx
	popl	%esi
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e085:
	ret

FUNC(op_d178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_e014:
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
	addw	GLOBL(regs)(%ebx),%dx
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
	jl	JJ_e086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e086:
	ret

FUNC(op_d179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_e015:
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
	addw	GLOBL(regs)(%ebx),%dx
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
	jl	JJ_e087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e087:
	ret

FUNC(op_d190)

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
	addl	(%ebx,%esi),%eax
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
	jl	JJ_e088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e088:
	ret

FUNC(op_d198)

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
	addl	%ebp,%eax
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
	jl	JJ_e089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e089:
	ret

FUNC(op_d1a0)

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
	jl	JJ_e090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e090:
	ret

FUNC(op_d1a8)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_e016:
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
	addl	(%ebx,%esi),%edx
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
	jl	JJ_e091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e091:
	ret

FUNC(op_d1b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_e017:
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
	addl	GLOBL(regs)(%ebx),%edx
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
	jl	JJ_e092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e092:
	ret

FUNC(op_d1b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_e018:
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
	addl	GLOBL(regs)(%ebx),%edx
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
	jl	JJ_e093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e093:
	ret

FUNC(op_d1c0)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	addl	$8,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	addl	GLOBL(regs)(,%eax,4),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e094:
	ret

FUNC(op_d1c8)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(,%edx,4),%ecx
	addl	GLOBL(regs)(,%eax,4),%ecx
	movl	%ecx,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e095:
	ret

FUNC(op_d1d0)

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
	addl	%eax,(%ecx,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e096:
	ret

FUNC(op_d1d8)

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
	addl	%eax,(%ebx,%esi,4)
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e097:
	ret

FUNC(op_d1e0)

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
	addl	%eax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e098:
	ret

FUNC(op_d1e8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$9,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_e019:
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
	addl	%eax,(%ecx,%ebx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e099:
	ret

FUNC(op_d1f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_e020:
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
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e100:
	ret

FUNC(op_d1f9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_e021:
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
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e101:
	ret

FUNC(op_d1fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_e022:
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
	addl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e102:
	ret

FUNC(op_d1fc)

	shrl	$9,%eax
	movl	GLOBL(regs)+88,%edx
	andl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_e023:
	addl	$8,%eax
	bswapl	%edx
	addl	%edx,GLOBL(regs)(,%eax,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e103:
	ret

FUNC(op_e098)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%esi
	shrl	$7,%eax
	andl	$7,%esi
	andl	$28,%eax
	movl	$-2147483648,%ebx
	movl	GLOBL(imm8_table)(%eax),%edx
	movl	GLOBL(regs)(,%esi,4),%ecx
	andl	$63,%edx
	jne	L_e_2243
	andb	$254,regflags
	jmp	L_e_1369
	.align	2,0x90
L_e_2243:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1373
	cmpl	$3,%eax
	jge	L_e_2246
	cmpl	$2,%eax
	jge	L_e_2247
	movl	%ecx,%eax
	andl	$1,%eax
	shrl	$1,%ecx
	testl	%eax,%eax
	je	L_e_2249
	orl	%ebx,%ecx
L_e_2249:
	decl	%edx
L_e_2247:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2252
	orl	%ebx,%ecx
L_e_2252:
	decl	%edx
L_e_2246:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2255
	orl	%ebx,%ecx
L_e_2255:
	decl	%edx
	jz	L_e_2244
	.align	2,0x90
L_e_1373:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2258
	orl	%ebx,%ecx
L_e_2258:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2261
	orl	%ebx,%ecx
L_e_2261:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2264
	orl	%ebx,%ecx
L_e_2264:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2267
	orl	%ebx,%ecx
L_e_2267:
	addl	$-4,%edx
	jne	L_e_1373
L_e_2244:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1369:
	testl	%ecx,%ebx
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%ecx,%ecx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	%ecx,GLOBL(regs)(,%esi,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e104:
	ret

FUNC(op_e0b8)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%esi
	shrl	$7,%eax
	andl	$7,%esi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movl	(%edx,%esi,4),%ecx
	movl	(%eax,%edx),%edx
	movl	$-2147483648,%ebx
	andl	$63,%edx
	jne	L_e_2270
	andb	$254,regflags
	jmp	L_e_1441
	.align	2,0x90
L_e_2270:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_1445
	cmpl	$3,%eax
	jge	L_e_2273
	cmpl	$2,%eax
	jge	L_e_2274
	movl	%ecx,%eax
	andl	$1,%eax
	shrl	$1,%ecx
	testl	%eax,%eax
	je	L_e_2276
	orl	%ebx,%ecx
L_e_2276:
	decl	%edx
L_e_2274:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2279
	orl	%ebx,%ecx
L_e_2279:
	decl	%edx
L_e_2273:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2282
	orl	%ebx,%ecx
L_e_2282:
	decl	%edx
	jz	L_e_2271
	.align	2,0x90
L_e_1445:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2285
	orl	%ebx,%ecx
L_e_2285:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2288
	orl	%ebx,%ecx
L_e_2288:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2291
	orl	%ebx,%ecx
L_e_2291:
	movl	%ecx,%eax
	shrl	$1,%ecx
	andl	$1,%eax
	je	L_e_2294
	orl	%ebx,%ecx
L_e_2294:
	addl	$-4,%edx
	jne	L_e_1445
L_e_2271:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_1441:
	testl	%ecx,%ebx
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%ecx,%ecx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	%ecx,GLOBL(regs)(,%esi,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e105:
	ret

FUNC(op_e1b8)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%esi
	shrl	$7,%eax
	andl	$7,%esi
	movl	$GLOBL(regs),%edx
	andl	$28,%eax
	movl	(%edx,%esi,4),%ecx
	movl	(%eax,%edx),%edx
	movl	$-2147483648,%ebx
	andl	$63,%edx
	jne	L_e_2297
	andb	$254,regflags
	jmp	L_e_2027
	.align	2,0x90
L_e_2297:
	movl	%edx,%eax
	negl	%eax
	andl	$3,%eax
	je	L_e_2031
	cmpl	$3,%eax
	jge	L_e_2300
	cmpl	$2,%eax
	jge	L_e_2301
	movl	%ecx,%eax
	andl	%ebx,%eax
	addl	%ecx,%ecx
	testl	%eax,%eax
	je	L_e_2303
	orl	$1,%ecx
L_e_2303:
	decl	%edx
L_e_2301:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2306
	orl	$1,%ecx
L_e_2306:
	decl	%edx
L_e_2300:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2309
	orl	$1,%ecx
L_e_2309:
	decl	%edx
	jz	L_e_2298
	.align	2,0x90
L_e_2031:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2312
	orl	$1,%ecx
L_e_2312:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2315
	orl	$1,%ecx
L_e_2315:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2318
	orl	$1,%ecx
L_e_2318:
	movl	%ecx,%eax
	addl	%ecx,%ecx
	andl	%ebx,%eax
	je	L_e_2321
	orl	$1,%ecx
L_e_2321:
	addl	$-4,%edx
	jne	L_e_2031
L_e_2298:
	testl	%eax,%eax
	setne	%dl
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
L_e_2027:
	testl	%ecx,%ebx
	setne	%al
	movb	regflags,%dl
	salb	$7,%al
	andb	$127,%dl
	orb	%al,%dl
	testl	%ecx,%ecx
	sete	%al
	salb	$6,%al
	andb	$-65,%dl
	orb	%al,%dl
	andb	$247,regflags+1
	movb	%dl,regflags
	movl	%ecx,GLOBL(regs)(,%esi,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e106:
	ret

FUNC(op_e2d0)

	andl	$7,%eax
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%esi,%esi
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%bl
	movw	GLOBL(regs)(,%eax,4),%si
	sall	$2,%ebx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%edx
	movl	%edx,%eax
	shrw	$1,%dx
	andl	$1,%eax
	testw	%dx,%dx
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movb	%al,%cl
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
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e107:
	ret

FUNC(op_e2d8)

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
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	(%edx,%ebp),%ebx
	addl	$2,%ebx
	movl	%eax,%ecx
	movl	%ebx,(%edx,%ebp)
	movl	%ecx,%eax
	shrw	$1,%cx
	andl	$1,%eax
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	popl	%ebx
	popl	%esi
	popl	%edi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e108:
	ret

FUNC(op_e2e0)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	$GLOBL(regs),%ebp
	sall	$2,%edx
	movl	(%edx,%ebp),%ebx
	addl	$-2,%ebx
	movl	%ebx,%esi
	movl	%ebx,16-16(%esp)
	shrl	$14,%esi
	movl	%ebx,%edi
	andl	$1020,%esi
	andl	$65535,%edi
	movl	GLOBL(R24)(%esi),%eax
	addl	%edi,%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	16-16(%esp),%ebx
	movl	%eax,%ecx
	movl	%ebx,(%edx,%ebp)
	movl	%ecx,%eax
	shrw	$1,%cx
	andl	$1,%eax
	testw	%cx,%cx
	pushfl
	popl	%edx
	movl	%edx,regflags

	movb	%al,%dl
	movb	regflags+4,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags+4
	movb	regflags,%al
	andb	$254,%al
	orb	%dl,%al
	movb	%al,regflags
	xorl	%eax,%eax
	movw	%cx,%ax
	addl	GLOBL(W24)(%esi),%edi
	rolw	$8,%ax
	movw	%ax,(%edi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_e109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e109:
	ret

FUNC(op_e2e8)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_e024:
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
	shrw	$1,%cx
	andl	$1,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,%bl
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
	jl	JJ_e110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e110:
	ret

FUNC(op_e2f8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_e025:
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
	shrw	$1,%cx
	andl	$1,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,%bl
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
	jl	JJ_e111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e111:
	ret

FUNC(op_e2f9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_e026:
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
	shrw	$1,%cx
	andl	$1,%eax
	testw	%cx,%cx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movb	%al,%bl
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
	jl	JJ_e112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e112:
	ret

FUNC(op_e3d0)

	andl	$7,%eax
	pushl	%esi
	addl	$8,%eax
	pushl	%ebx
	xorl	%esi,%esi
	xorl	%ebx,%ebx
	movb	GLOBL(regs)+2(,%eax,4),%bl
	movw	GLOBL(regs)(,%eax,4),%si
	sall	$2,%ebx
	movl	GLOBL(R24)(%ebx),%eax
	addl	%esi,%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
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
	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_e113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_e158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_e113:
	ret

FUNC(Init020_0e)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_e000-4
	movl	%eax,RR0_e001-4
	movl	%eax,RR0_e002-4
	movl	%eax,RR0_e003-4
	movl	%eax,RR0_e004-4
	movl	%eax,RR0_e005-4
	movl	%eax,RR0_e006-4
	movl	%eax,RR0_e007-4
	movl	%eax,RR0_e008-4
	movl	%eax,RR0_e009-4
	movl	%eax,RR0_e010-4
	movl	%eax,RR0_e011-4
	movl	%eax,RR0_e012-4
	movl	%eax,RR0_e013-4
	movl	%eax,RR0_e014-4
	movl	%eax,RR0_e015-4
	movl	%eax,RR0_e016-4
	movl	%eax,RR0_e017-4
	movl	%eax,RR0_e018-4
	movl	%eax,RR0_e019-4
	movl	%eax,RR0_e020-4
	movl	%eax,RR0_e021-4
	movl	%eax,RR0_e022-4
	movl	%eax,RR0_e023-4
	movl	%eax,RR0_e024-4
	movl	%eax,RR0_e025-4
	movl	%eax,RR0_e026-4
	movl	%eax,RR0_e027-4
	movl	%eax,RR0_e028-4
	movl	%eax,RR0_e029-4
	movl	%eax,RR0_e030-4
	movl	%eax,RR0_e031-4
	movl	%eax,RR0_e032-4
	movl	%eax,RR0_e033-4
	movl	%eax,RR0_e034-4
	movl	%eax,RR0_e035-4
	movl	%eax,RR0_e036-4
	movl	%eax,RR0_e037-4
	movl	%eax,RR0_e038-4
	movl	%eax,RR0_e039-4
	movl	%eax,RR0_e040-4
	movl	%eax,RR0_e041-4
	movl	%eax,RR0_e042-4
	movl	%eax,RR0_e043-4
	movl	%eax,RR0_e044-4
	movl	%eax,RR0_e045-4
	movl	%eax,RR0_e046-4
	movl	%eax,RR0_e047-4
	movl	%eax,RR0_e048-4
	movl	%eax,RR0_e049-4
	movl	%eax,RR0_e050-4
	movl	%eax,RR0_e051-4
	movl	%eax,RR0_e052-4
	movl	%eax,RR0_e053-4
	movl	%eax,RR0_e054-4
	movl	%eax,RR0_e055-4
	movl	%eax,RR0_e056-4
	movl	%eax,RR0_e057-4
	movl	%eax,RR0_e058-4
	movl	%eax,RR0_e059-4
	movl	%eax,RR0_e060-4
	movl	%eax,RR0_e061-4
	movl	%eax,RR0_e062-4
	movl	%eax,RR0_e063-4
	movl	%eax,RR0_e064-4
	movl	%eax,RR0_e065-4
	movl	%eax,RR0_e066-4
	movl	%eax,RR0_e067-4
	movl	%eax,RR0_e068-4
	movl	%eax,RR0_e069-4
	movl	%eax,RR0_e070-4
	movl	%eax,RR0_e071-4
	movl	%eax,RR0_e072-4
	movl	%eax,RR0_e073-4
	movl	%eax,RR0_e074-4
	movl	%eax,RR0_e075-4
	movl	%eax,RR0_e076-4
	movl	%eax,RR0_e077-4
	movl	%eax,RR0_e078-4
	movl	%eax,RR0_e079-4
	movl	%eax,RR0_e080-4
	movl	%eax,RR0_e081-4
	movl	%eax,RR0_e082-4
	movl	%eax,RR0_e083-4
	movl	%eax,RR0_e084-4
	movl	%eax,RR0_e085-4
	movl	%eax,RR0_e086-4
	movl	%eax,RR0_e087-4
	movl	%eax,RR0_e088-4
	movl	%eax,RR0_e089-4
	movl	%eax,RR0_e090-4
	movl	%eax,RR0_e091-4
	movl	%eax,RR0_e092-4
	movl	%eax,RR0_e093-4
	movl	%eax,RR0_e094-4
	movl	%eax,RR0_e095-4
	movl	%eax,RR0_e096-4
	movl	%eax,RR0_e097-4
	movl	%eax,RR0_e098-4
	movl	%eax,RR0_e099-4
	movl	%eax,RR0_e100-4
	movl	%eax,RR0_e101-4
	movl	%eax,RR0_e102-4
	movl	%eax,RR0_e103-4
	movl	%eax,RR0_e104-4
	movl	%eax,RR0_e105-4
	movl	%eax,RR0_e106-4
	movl	%eax,RR0_e107-4
	movl	%eax,RR0_e108-4
	movl	%eax,RR0_e109-4
	movl	%eax,RR0_e110-4
	movl	%eax,RR0_e111-4
	movl	%eax,RR0_e112-4
	movl	%eax,RR0_e113-4
	movl	%eax,RR0_e114-4
	movl	%eax,RR0_e115-4
	movl	%eax,RR0_e116-4
	movl	%eax,RR0_e117-4
	movl	%eax,RR0_e118-4
	movl	%eax,RR0_e119-4
	movl	%eax,RR0_e120-4
	movl	%eax,RR0_e121-4
	movl	%eax,RR0_e122-4
	movl	%eax,RR0_e123-4
	movl	%eax,RR0_e124-4
	movl	%eax,RR0_e125-4
	movl	%eax,RR0_e126-4
	movl	%eax,RR0_e127-4
	movl	%eax,RR0_e128-4
	movl	%eax,RR0_e129-4
	movl	%eax,RR0_e130-4
	movl	%eax,RR0_e131-4
	movl	%eax,RR0_e132-4
	movl	%eax,RR0_e133-4
	movl	%eax,RR0_e134-4
	movl	%eax,RR0_e135-4
	movl	%eax,RR0_e136-4
	movl	%eax,RR0_e137-4
	movl	%eax,RR0_e138-4
	movl	%eax,RR0_e139-4
	movl	%eax,RR0_e140-4
	movl	%eax,RR0_e141-4
	movl	%eax,RR0_e142-4
	movl	%eax,RR0_e143-4
	movl	%eax,RR0_e144-4
	movl	%eax,RR0_e145-4
	movl	%eax,RR0_e146-4
	movl	%eax,RR0_e147-4
	movl	%eax,RR0_e148-4
	movl	%eax,RR0_e149-4
	movl	%eax,RR0_e150-4
	movl	%eax,RR0_e151-4
	movl	%eax,RR0_e152-4
	movl	%eax,RR0_e153-4
	movl	%eax,RR0_e154-4
	movl	%eax,RR0_e155-4
	movl	%eax,RR0_e156-4
	movl	%eax,RR0_e157-4
	movl	%eax,RR0_e158-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_e000-4
	movl	%eax,RR2_e001-4
	movl	%eax,RR2_e002-4
	movl	%eax,RR2_e003-4
	movl	%eax,RR2_e004-4
	movl	%eax,RR2_e005-4
	movl	%eax,RR2_e006-4
	movl	%eax,RR2_e007-4
	movl	%eax,RR2_e008-4
	movl	%eax,RR2_e009-4
	movl	%eax,RR2_e010-4
	movl	%eax,RR2_e011-4
	movl	%eax,RR2_e012-4
	movl	%eax,RR2_e013-4
	movl	%eax,RR2_e014-4
	movl	%eax,RR2_e015-4
	movl	%eax,RR2_e016-4
	movl	%eax,RR2_e017-4
	movl	%eax,RR2_e018-4
	movl	%eax,RR2_e019-4
	movl	%eax,RR2_e020-4
	movl	%eax,RR2_e021-4
	movl	%eax,RR2_e022-4
	movl	%eax,RR2_e023-4
	movl	%eax,RR2_e024-4
	movl	%eax,RR2_e025-4
	movl	%eax,RR2_e026-4
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
