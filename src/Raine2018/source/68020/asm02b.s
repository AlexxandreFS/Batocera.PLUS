

FUNC(op_80d8)

	subl	$4,%esp
	movl	%eax,%ebx
	movl	%ebx,%ecx
	movl	$GLOBL(regs),%edi
	andl	$7,%ecx
	movl	%ebx,%esi
	addl	$8,%ecx
	shrl	$7,%esi
	sall	$2,%ecx
	xorl	%ebx,%ebx
	movl	(%ecx,%edi),%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,16-16(%esp)
	xorl	%eax,%eax
	movw	16-16(%esp),%ax
	movl	%eax,16-16(%esp)
	movl	(%ecx,%edi),%edx
	movl	GLOBL(regs)+88,%ebp
	addl	$2,%edx
	andl	$28,%esi
	movl	%edx,(%ecx,%edi)
	movl	%eax,%ebx
	movl	(%esi,%edi),%ecx
	cmpw	$0,16-16(%esp)
	jne	L_b_375
	pushl	%ebp
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_376
	.align	2,0x90
L_b_375:
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%eax,16-16(%esp)
	movl	%ecx,%eax
	xorl	%edx,%edx
	divl	16-16(%esp)
	movl	%eax,%ebx
	movl	%edx,%ecx
	cmpl	$65535,%ebx
	jbe	L_b_378
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_377
	.align	2,0x90
L_b_378:
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%esi,%edi)
L_b_377:
	addl	$2,GLOBL(regs)+88
L_b_376:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b000:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b000:
	ret

FUNC(op_80e0)

	subl	$12,%esp
	movl	%eax,%ebx
	movl	$GLOBL(regs),%ebp
	movl	%ebx,%ecx
	movl	GLOBL(regs)+88,%eax
	andl	$7,%ecx
	movl	%ebx,%esi
	addl	$8,%ecx
	movl	%eax,24-16(%esp)
	sall	$2,%ecx
	shrl	$7,%esi
	movl	(%ecx,%ebp),%ebx
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
	movl	%edx,20-16(%esp)
	xorl	%eax,%eax
	movw	20-16(%esp),%ax
	movl	%eax,20-16(%esp)
	movl	%ebx,(%ecx,%ebp)
	movl	%esi,%ebx
	andl	$28,%ebx
	movl	%eax,%edi
	movl	(%ebx,%ebp),%ecx
	cmpw	$0,20-16(%esp)
	jne	L_b_384
	movl	24-16(%esp),%edx
	pushl	%edx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_385
	.align	2,0x90
L_b_384:
	xorl	%eax,%eax
	movw	%di,%ax
	movl	%eax,20-16(%esp)
	movl	%ecx,%eax
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ecx
	cmpl	$65535,%edi
	jbe	L_b_387
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_386
	.align	2,0x90
L_b_387:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edi,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ebx,%ebp)
L_b_386:
	addl	$2,GLOBL(regs)+88
L_b_385:
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b001:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b001:
	ret

FUNC(op_80e8)

	subl	$8,%esp
	movl	%eax,%ecx
	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)+88,%edi
	xorl	%edx,%edx
	movw	0x2164334A+2(%edi),%dx
RR2_b000:
	rolw	$8,%dx
	movl	%edx,20-16(%esp)
	movl	%eax,16-16(%esp)
	movl	$GLOBL(regs),%esi
	movswl	20-16(%esp),%eax
	movl	16-16(%esp),%edx
	addl	(%esi,%edx,4),%eax
	movl	%eax,20-16(%esp)
	shrl	$14,%eax
	andl	$1020,%eax
	movl	%eax,16-16(%esp)
	movl	20-16(%esp),%eax
	movl	16-16(%esp),%edx
	andl	$65535,%eax
	shrl	$7,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,20-16(%esp)
	andl	$28,%ecx
	xorl	%eax,%eax
	movw	20-16(%esp),%ax
	movl	%eax,20-16(%esp)
	movl	%eax,%ebx
	movl	(%ecx,%esi),%ebp
	cmpw	$0,20-16(%esp)
	jne	L_b_394
	pushl	%edi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_395
	.align	2,0x90
L_b_394:
	xorl	%edx,%edx
	movw	%bx,%dx
	movl	%ebp,%eax
	movl	%edx,20-16(%esp)
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ebx
	cmpl	$65535,%edi
	jbe	L_b_397
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_396
	.align	2,0x90
L_b_397:
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
L_b_396:
	addl	$4,GLOBL(regs)+88
L_b_395:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b002:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b002:
	ret

FUNC(op_80f0)

	subl	$20,%esp
	movl	%eax,%ecx
	shrl	$9,%ecx
	andl	$7,%eax
	movl	%ecx,%edx
	movl	%eax,16-16(%esp)
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	movl	%edx,32-16(%esp)
	movl	%eax,28-16(%esp)
	movl	16-16(%esp),%edx
	addl	$2,%eax
	addl	$8,%edx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_b003:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%ebp
	movl	28-16(%esp),%eax
	movl	%esi,%edx
	addl	$4,%eax
	shrl	$10,%edx
	movl	%eax,24-16(%esp)
	movl	%eax,GLOBL(regs)+88
	andl	$60,%edx
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%edx),%edi
	testl	$2048,%esi
	jne	L_b_403
	movswl	%di,%edi
L_b_403:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_404
	xorl	%ebp,%ebp
	movl	%esi,%eax
	testb	%al,%al
	jge	L_b_405
	movl	%ebp,%ebx
L_b_405:
	testl	$64,%esi
	je	L_b_406
	movl	%ebp,%edi
L_b_406:
	movl	%esi,%ecx
	andl	$48,%ecx
	cmpl	$32,%ecx
	jne	L_b_407
	movl	24-16(%esp),%edx
	xorl	%eax,%eax
	movw	0x2164334A(%edx),%ax
RR0_b004:
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	28-16(%esp),%edx
	addl	$6,%edx
	movswl	20-16(%esp),%eax
	movl	%edx,GLOBL(regs)+88
	addl	%eax,%ebx
L_b_407:
	cmpl	$48,%ecx
	jne	L_b_410
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b005:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_410:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_413
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b006:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_413:
	cmpl	$3,%ecx
	jne	L_b_416
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b007:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_416:
	andl	$4,%esi
	jne	L_b_419
	addl	%edi,%ebx
L_b_419:
	testl	%ecx,%ecx
	je	L_b_420
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_420:
	testl	%esi,%esi
	je	L_b_423
	addl	%edi,%ebx
L_b_423:
	leal	(%ebp,%ebx),%ecx
	jmp	L_b_424
	.align	2,0x90
L_b_404:
	movl	%esi,%edx
	movsbl	%dl,%esi
	movl	%esi,20-16(%esp)
	leal	(%esi,%ebp),%eax
	movl	%eax,%ecx
	addl	%edi,%ecx
L_b_424:
	movl	%ecx,%edx
	andl	$65535,%ecx
	shrl	$14,%edx
	movl	%ecx,%eax
	andl	$1020,%edx
	movl	$GLOBL(regs),%esi
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,20-16(%esp)
	xorl	%eax,%eax
	movw	20-16(%esp),%ax
	movl	32-16(%esp),%edx
	movl	%eax,20-16(%esp)
	leal	0(,%edx,4),%ebx
	movl	%eax,%ecx
	movl	(%ebx,%esi),%edi
	cmpw	$0,20-16(%esp)
	jne	L_b_428
	movl	28-16(%esp),%eax
	pushl	%eax
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_429
	.align	2,0x90
L_b_428:
	xorl	%edx,%edx
	movw	%cx,%dx
	movl	%edi,%eax
	movl	%edx,20-16(%esp)
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ecx
	cmpl	$65535,%edi
	jbe	L_b_431
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_429
	.align	2,0x90
L_b_431:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edi,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ebx,%esi)
L_b_429:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b008:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b003:
	ret

FUNC(op_80fa)

	subl	$8,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_b001:
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movswl	20-16(%esp),%edx
	leal	2(%edx,%ebx),%eax
	movl	%eax,20-16(%esp)
	shrl	$7,%ecx
	shrl	$14,%eax
	movl	20-16(%esp),%edx
	andl	$1020,%eax
	andl	$65535,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	$GLOBL(regs),%edi
	xorl	%edx,%edx
	movw	20-16(%esp),%dx
	movl	%edx,20-16(%esp)
	movl	%edx,%esi
	movl	(%ecx,%edi),%ebp
	cmpw	$0,20-16(%esp)
	jne	L_b_479
	pushl	%ebx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_480
	.align	2,0x90
L_b_479:
	xorl	%eax,%eax
	movw	%si,%ax
	movl	%eax,20-16(%esp)
	movl	%ebp,%eax
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%esi
	movl	%edx,%ebx
	cmpl	$65535,%esi
	jbe	L_b_482
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_481
	.align	2,0x90
L_b_482:
	testw	%si,%si
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%esi,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ecx,%edi)
L_b_481:
	addl	$4,GLOBL(regs)+88
L_b_480:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b009:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b004:
	ret

FUNC(op_80fb)

	subl	$20,%esp
	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	%ecx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edx
	movl	%eax,32-16(%esp)
	movl	%edx,%ebp
	movl	%edx,28-16(%esp)
	addl	$2,%ebp
	addl	$4,%edx
	movl	%ebp,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%ebp),%si
RR0_b010:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%edx,24-16(%esp)
	shrl	$10,%eax
	movl	%edx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%ebp,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_b_489
	movswl	%di,%edi
L_b_489:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_490
	xorl	%ebp,%ebp
	movl	%esi,%edx
	testb	%dl,%dl
	jge	L_b_491
	movl	%ebp,%ebx
L_b_491:
	testl	$64,%esi
	je	L_b_492
	movl	%ebp,%edi
L_b_492:
	movl	%esi,%ecx
	andl	$48,%ecx
	cmpl	$32,%ecx
	jne	L_b_493
	movl	24-16(%esp),%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b011:
	rolw	$8,%dx
	movl	%edx,20-16(%esp)
	movl	28-16(%esp),%eax
	addl	$6,%eax
	movswl	20-16(%esp),%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,%ebx
L_b_493:
	cmpl	$48,%ecx
	jne	L_b_496
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b012:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_496:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_499
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b013:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_499:
	cmpl	$3,%ecx
	jne	L_b_502
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b014:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_502:
	andl	$4,%esi
	jne	L_b_505
	addl	%edi,%ebx
L_b_505:
	testl	%ecx,%ecx
	je	L_b_506
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_506:
	testl	%esi,%esi
	je	L_b_509
	addl	%edi,%ebx
L_b_509:
	leal	(%ebp,%ebx),%ecx
	jmp	L_b_510
	.align	2,0x90
L_b_490:
	movl	%esi,%eax
	movsbl	%al,%esi
	movl	%esi,20-16(%esp)
	leal	(%esi,%ebp),%edx
	movl	%edx,%ecx
	addl	%edi,%ecx
L_b_510:
	movl	%ecx,%eax
	andl	$65535,%ecx
	shrl	$14,%eax
	movl	%ecx,%edx
	andl	$1020,%eax
	movl	$GLOBL(regs),%esi
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	xorl	%edx,%edx
	movw	20-16(%esp),%dx
	movl	32-16(%esp),%eax
	movl	%edx,20-16(%esp)
	leal	0(,%eax,4),%ebx
	movl	%edx,%ecx
	movl	(%ebx,%esi),%edi
	cmpw	$0,20-16(%esp)
	jne	L_b_514
	movl	28-16(%esp),%edx
	pushl	%edx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_515
	.align	2,0x90
L_b_514:
	xorl	%eax,%eax
	movw	%cx,%ax
	movl	%eax,20-16(%esp)
	movl	%edi,%eax
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%edi
	movl	%edx,%ecx
	cmpl	$65535,%edi
	jbe	L_b_517
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_515
	.align	2,0x90
L_b_517:
	testw	%di,%di
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%edi,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ebx,%esi)
L_b_515:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b005:
	ret

FUNC(op_8100)

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
	movb	%bl,%dl
	andl	$15,%eax
	andl	$15,%edx
	subl	%eax,%edx
	movb	%bl,20-16(%esp)
	movl	%edx,%eax
	testb	$1,regflags+4
	je	L_b_536
	decl	%eax
L_b_536:
	movl	%eax,%ecx
	movb	20-16(%esp),%dl
	movb	24-16(%esp),%al
	andl	$240,%edx
	andl	$240,%eax
	subw	%ax,%dx
	cmpw	$9,%cx
	jbe	L_b_537
	addl	$-6,%ecx
	addl	$-16,%edx
L_b_537:
	movl	%ecx,%eax
	andl	$15,%eax
	addl	%edx,%eax
	movw	%ax,18-16(%esp)
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
	je	L_b_538
	addw	$-96,18-16(%esp)
L_b_538:
	cmpb	$0,18-16(%esp)
	je	L_b_539
	andb	$191,%al
	movb	%al,regflags
L_b_539:
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
	je	L_b_540
	cmpl	%eax,%esi
	setne	%al
	movb	%al,%cl
L_b_540:
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
	jl	JJ_b006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b016:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b006:
	ret

FUNC(op_8108)

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
	movb	20-16(%esp),%dl
	movb	24-16(%esp),%al
	andl	$15,%edx
	andl	$15,%eax
	subl	%eax,%edx
	movl	%edx,%eax
	testb	$1,regflags+4
	je	L_b_545
	decl	%eax
L_b_545:
	movl	%eax,%ecx
	movb	20-16(%esp),%dl
	movb	24-16(%esp),%al
	andl	$240,%edx
	andl	$240,%eax
	subw	%ax,%dx
	cmpw	$9,%cx
	jbe	L_b_546
	addl	$-6,%ecx
	addl	$-16,%edx
L_b_546:
	movl	%ecx,%eax
	movl	%edx,%ebx
	andl	$15,%eax
	addl	%eax,%ebx
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
	je	L_b_547
	addl	$-96,%ebx
L_b_547:
	testb	%bl,%bl
	je	L_b_548
	andb	$191,%al
	movb	%al,regflags
L_b_548:
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
	je	L_b_549
	cmpl	%eax,%esi
	setne	%al
	movb	%al,%cl
L_b_549:
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
	jl	JJ_b007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b007:
	ret

FUNC(op_8130)

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
RR0_b018:
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
	jne	L_b_589
	movswl	%di,%edi
L_b_589:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_590
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_b_591
	movl	%ebp,16-16(%esp)
L_b_591:
	testl	$64,%esi
	je	L_b_592
	movl	%ebp,%edi
L_b_592:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_593
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b019:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_b_593:
	cmpl	$48,%edx
	jne	L_b_596
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b020:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_b_596:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_599
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b021:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_599:
	cmpl	$3,%ecx
	jne	L_b_602
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b022:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_602:
	andl	$4,%esi
	jne	L_b_605
	addl	%edi,16-16(%esp)
L_b_605:
	testl	%ecx,%ecx
	je	L_b_606
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_b_606:
	testl	%esi,%esi
	je	L_b_609
	addl	%edi,16-16(%esp)
L_b_609:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_b_610
	.align	2,0x90
L_b_590:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_610:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	orb	%al,31-16(%esp)
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
	jl	JJ_b008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b023:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b008:
	ret

FUNC(op_8148)

	subl	$4,%esp
	movl	%eax,%esi
	shrl	$9,%eax
	andl	$7,%eax
	andl	$7,%esi
	movl	%eax,16-16(%esp)
	leal	8(%esi),%ebx
	sall	$2,%esi
	sall	$2,%ebx
	movl	GLOBL(areg_byteinc)(%esi),%eax
	movl	GLOBL(regs)(%ebx),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	movl	%edx,GLOBL(regs)(%ebx)
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%eax
	subl	GLOBL(areg_byteinc)(%esi),%edx
	movzbw	(%ecx,%eax),%bp
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,GLOBL(regs)(%ebx)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_b002:
	rolw	$8,%bx
	xorl	%eax,%eax
	movb	(%edx,%ecx),%al
	salw	$8,%ax
	orl	%ebp,%eax
	movl	%eax,%ebp
	addl	%ebx,%ebp
	movl	16-16(%esp),%eax
	addl	$8,%eax
	movl	16-16(%esp),%edi
	sall	$2,%eax
	movl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movl	GLOBL(regs)(%eax),%edi
	subl	%edx,%edi
	movl	%edi,%edx
	movl	%edx,GLOBL(regs)(%eax)
	movl	%ebp,%eax
	shrw	$4,%ax
	movb	%al,%bl
	andb	$240,%bl
	movl	%edx,%eax
	movl	%ebp,%ecx
	shrl	$14,%eax
	andb	$15,%cl
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	orb	%cl,%bl
	movb	%bl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b024:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b009:
	ret

FUNC(op_8170)

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
RR0_b025:
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
	jne	L_b_700
	movswl	%di,%edi
L_b_700:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_701
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_b_702
	movl	%ebp,16-16(%esp)
L_b_702:
	testl	$64,%esi
	je	L_b_703
	movl	%ebp,%edi
L_b_703:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_704
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b026:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_b_704:
	cmpl	$48,%edx
	jne	L_b_707
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b027:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_b_707:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_710
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b028:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_710:
	cmpl	$3,%ecx
	jne	L_b_713
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b029:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_713:
	andl	$4,%esi
	jne	L_b_716
	addl	%edi,16-16(%esp)
L_b_716:
	testl	%ecx,%ecx
	je	L_b_717
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_b_717:
	testl	%esi,%esi
	je	L_b_720
	addl	%edi,16-16(%esp)
L_b_720:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_b_721
	.align	2,0x90
L_b_701:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_721:
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
	orw	%ax,30-16(%esp)
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
	jl	JJ_b010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b030:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b010:
	ret

FUNC(op_8188)

	subl	$12,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	leal	8(%eax),%ecx
	movl	%edx,%ebx
	movl	$GLOBL(areg_byteinc),%edi
	andl	$7,%ebx
	sall	$2,%ecx
	movl	%ebx,24-16(%esp)
	movl	$GLOBL(regs),%esi
	movl	(%edi,%eax,4),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,(%ecx,%esi)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movzbw	(%edx,%eax),%bp
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_b003:
	rolw	$8,%cx
	movl	%ebp,%eax
	movl	%ebp,%edx
	salw	$4,%ax
	andl	$15,%edx
	andl	$3840,%eax
	orl	%edx,%eax
	movl	%eax,%ebp
	addl	%ecx,%ebp
	movl	24-16(%esp),%ecx
	sall	$2,%ebx
	addl	$8,%ecx
	movl	%ebx,16-16(%esp)
	sall	$2,%ecx
	movl	(%ebx,%edi),%eax
	movl	(%ecx,%esi),%edx
	subl	%eax,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,(%ecx,%esi)
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(W24)(%eax),%eax
	movl	%ebp,%ebx
	movb	%bl,(%edx,%eax)
	movl	16-16(%esp),%ebx
	movl	(%ecx,%esi),%edx
	movl	(%ebx,%edi),%eax
	subl	%eax,%edx
	movl	%edx,(%ecx,%esi)
	movl	%edx,%eax
	movl	%ebp,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	shrw	$8,%cx
	movl	GLOBL(W24)(%eax),%eax
	movb	%cl,(%edx,%eax)
	addl	$4,GLOBL(regs)+88
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b031:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b011:
	ret

FUNC(op_81b0)

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
RR0_b032:
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
	jne	L_b_821
	movswl	%di,%edi
L_b_821:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_822
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_b_823
	movl	%ebp,16-16(%esp)
L_b_823:
	testl	$64,%esi
	je	L_b_824
	movl	%ebp,%edi
L_b_824:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_825
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b033:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_b_825:
	cmpl	$48,%edx
	jne	L_b_828
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b034:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_b_828:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_831
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b035:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_831:
	cmpl	$3,%ecx
	jne	L_b_834
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b036:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_834:
	andl	$4,%esi
	jne	L_b_837
	addl	%edi,16-16(%esp)
L_b_837:
	testl	%ecx,%ecx
	je	L_b_838
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_b_838:
	testl	%esi,%esi
	je	L_b_841
	addl	%edi,16-16(%esp)
L_b_841:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_b_842
	.align	2,0x90
L_b_822:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_842:
	movl	%eax,%ecx
	shrl	$14,%ecx
	movl	%eax,%edx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	addl	%edx,%eax
	movl	(%eax),%eax
	bswapl	%eax
	orl	%eax,28-16(%esp)
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
	jl	JJ_b012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b037:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b012:
	ret

FUNC(op_81d0)

	subl	$8,%esp
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$9,%ecx
	andl	$7,%edx
	movl	%ecx,%ebp
	xorl	%ecx,%ecx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%ebx
	movl	%eax,16-16(%esp)
	xorl	%edi,%edi
	movb	2(%ebx,%edx,4),%cl
	movw	(%ebx,%edx,4),%di
	addl	GLOBL(R24)(,%ecx,4),%edi
	xorl	%eax,%eax
	movw	(%edi),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	andl	$7,%ebp
	xorl	%edi,%edi
	movw	20-16(%esp),%di
	movl	%edi,20-16(%esp)
	movl	%edi,%edx
	movl	(%ebx,%ebp,4),%esi
	cmpw	$0,20-16(%esp)
	jne	L_b_897
	movl	16-16(%esp),%eax
	pushl	%eax
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_898
	.align	2,0x90
L_b_897:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,20-16(%esp)
	cltd
	idivl	20-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_900
	cmpl	$-32768,%edx
	je	L_b_900
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_899
	.align	2,0x90
L_b_900:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_902
	negw	%bx
L_b_902:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_899:
	addl	$2,GLOBL(regs)+88
L_b_898:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b038:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b013:
	ret

FUNC(op_81d8)

	subl	$8,%esp
	movl	%eax,%edx
	movl	%edx,%ecx
	shrl	$9,%edx
	andl	$7,%ecx
	addl	$8,%ecx
	sall	$2,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	$GLOBL(regs),%esi
	movl	%eax,16-16(%esp)
	movl	%edx,%ebp
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%edi
	movb	2(%ecx,%esi),%bl
	andl	$65535,%edi
	addl	GLOBL(R24)(,%ebx,4),%edi
	xorl	%eax,%eax
	movw	(%edi),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	addl	$2,%edx
	xorl	%edi,%edi
	movw	20-16(%esp),%di
	movl	%edi,20-16(%esp)
	andl	$7,%ebp
	movl	%edx,(%ecx,%esi)
	movl	%edi,%ebx
	movl	(%esi,%ebp,4),%esi
	cmpw	$0,20-16(%esp)
	jne	L_b_907
	movl	16-16(%esp),%eax
	pushl	%eax
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_908
	.align	2,0x90
L_b_907:
	movswl	%bx,%ebx
	movl	%esi,%eax
	movl	%ebx,20-16(%esp)
	cltd
	idivl	%ebx
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_910
	cmpl	$-32768,%edx
	je	L_b_910
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_909
	.align	2,0x90
L_b_910:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_912
	negw	%bx
L_b_912:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_909:
	addl	$2,GLOBL(regs)+88
L_b_908:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b039:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b014:
	ret

FUNC(op_81e0)

	subl	$8,%esp
	movl	%eax,%edx
	movl	%edx,%ebx
	movl	$GLOBL(regs),%esi
	andl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	addl	$8,%ebx
	movl	%eax,16-16(%esp)
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	shrl	$9,%edx
	addl	$-2,%ecx
	movl	%edx,%ebp
	movl	%ecx,%edx
	movl	%ecx,%edi
	shrl	$14,%edx
	andl	$65535,%edi
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%edi
	xorl	%eax,%eax
	movw	(%edi),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	xorl	%edi,%edi
	movw	20-16(%esp),%di
	movl	%edi,20-16(%esp)
	andl	$7,%ebp
	movl	%ecx,(%ebx,%esi)
	movl	%edi,%edx
	movl	(%esi,%ebp,4),%esi
	cmpw	$0,20-16(%esp)
	jne	L_b_917
	movl	16-16(%esp),%eax
	pushl	%eax
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_918
	.align	2,0x90
L_b_917:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,20-16(%esp)
	cltd
	idivl	20-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_920
	cmpl	$-32768,%edx
	je	L_b_920
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_919
	.align	2,0x90
L_b_920:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_922
	negw	%bx
L_b_922:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_919:
	addl	$2,GLOBL(regs)+88
L_b_918:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b040:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b015:
	ret

FUNC(op_81e8)

	subl	$4,%esp
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$9,%ecx
	andl	$7,%edx
	movl	%ecx,%ebp
	movl	$GLOBL(regs),%ecx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_b004:
	rolw	$8,%ax
	movl	%eax,16-16(%esp)
	addl	$8,%edx
	movswl	16-16(%esp),%edi
	addl	(%ecx,%edx,4),%edi
	movl	%edi,%edx
	shrl	$14,%edx
	andl	$65535,%edi
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%edi
	xorl	%eax,%eax
	movw	(%edi),%ax
	rolw	$8,%ax
	movl	%eax,16-16(%esp)
	andl	$7,%ebp
	xorl	%edi,%edi
	movw	16-16(%esp),%di
	movl	%edi,16-16(%esp)
	movl	%edi,%edx
	movl	(%ecx,%ebp,4),%esi
	cmpw	$0,16-16(%esp)
	jne	L_b_928
	pushl	%ebx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_929
	.align	2,0x90
L_b_928:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,16-16(%esp)
	cltd
	idivl	16-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_931
	cmpl	$-32768,%edx
	je	L_b_931
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_930
	.align	2,0x90
L_b_931:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_933
	negw	%bx
L_b_933:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_930:
	addl	$4,GLOBL(regs)+88
L_b_929:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b041:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b016:
	ret

FUNC(op_81f0)

	subl	$20,%esp
	movl	%eax,%ecx
	movl	%ecx,%edx
	shrl	$9,%ecx
	andl	$7,%edx
	movl	%ecx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edi
	addl	$8,%edx
	movl	%edi,28-16(%esp)
	movl	%eax,32-16(%esp)
	addl	$2,%edi
	movl	28-16(%esp),%eax
	movl	%edi,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edi),%si
RR0_b042:
	rolw	$8,%si
	addl	$4,%eax
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%esi,%edi
	movl	%eax,24-16(%esp)
	shrl	$10,%edi
	movl	%eax,GLOBL(regs)+88
	andl	$60,%edi
	movl	GLOBL(regs)(%edi),%eax
	movl	%edx,%ebx
	movl	%eax,16-16(%esp)
	testl	$2048,%esi
	jne	L_b_938
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_b_938:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_939
	xorl	%ebp,%ebp
	movl	%esi,%eax
	testb	%al,%al
	jge	L_b_940
	movl	%ebp,%ebx
L_b_940:
	testl	$64,%esi
	je	L_b_941
	movl	%ebp,16-16(%esp)
L_b_941:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_942
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b043:
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	28-16(%esp),%edi
	addl	$6,%edi
	movswl	20-16(%esp),%eax
	movl	%edi,GLOBL(regs)+88
	addl	%eax,%ebx
L_b_942:
	cmpl	$48,%edx
	jne	L_b_945
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b044:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_945:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_948
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b045:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_948:
	cmpl	$3,%ecx
	jne	L_b_951
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b046:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_951:
	andl	$4,%esi
	jne	L_b_954
	addl	16-16(%esp),%ebx
L_b_954:
	testl	%ecx,%ecx
	je	L_b_955
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_955:
	testl	%esi,%esi
	je	L_b_958
	addl	16-16(%esp),%ebx
L_b_958:
	leal	(%ebp,%ebx),%edx
	jmp	L_b_959
	.align	2,0x90
L_b_939:
	movl	%esi,%eax
	movsbl	%al,%esi
	movl	%esi,20-16(%esp)
	addl	%esi,%edx
	addl	16-16(%esp),%edx
L_b_959:
	movl	%edx,%edi
	shrl	$14,%edi
	andl	$65535,%edx
	andl	$1020,%edi
	addl	GLOBL(R24)(%edi),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	xorl	%edi,%edi
	movw	20-16(%esp),%di
	movl	32-16(%esp),%eax
	movl	%edi,20-16(%esp)
	movl	%edi,%edx
	movl	GLOBL(regs)(,%eax,4),%esi
	cmpw	$0,20-16(%esp)
	jne	L_b_963
	movl	28-16(%esp),%edi
	pushl	%edi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_964
	.align	2,0x90
L_b_963:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,20-16(%esp)
	cltd
	idivl	20-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_966
	cmpl	$-32768,%edx
	je	L_b_966
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_964
	.align	2,0x90
L_b_966:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_968
	negw	%bx
L_b_968:
	testw	%cx,%cx
	pushfl
	popl	%edi
	movl	%edi,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	32-16(%esp),%edi
	movl	%edx,GLOBL(regs)(,%edi,4)
L_b_964:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b047:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b017:
	ret

FUNC(op_81f8)

	subl	$4,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_b005:
	rolw	$8,%ax
	movl	%eax,16-16(%esp)
	shrl	$9,%edx
	movswl	16-16(%esp),%edi
	movl	%edx,%ebp
	movl	%edi,%edx
	shrl	$14,%edx
	andl	$65535,%edi
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%edi
	xorl	%eax,%eax
	movw	(%edi),%ax
	rolw	$8,%ax
	movl	%eax,16-16(%esp)
	andl	$7,%ebp
	xorl	%edi,%edi
	movw	16-16(%esp),%di
	movl	%edi,16-16(%esp)
	movl	%edi,%edx
	movl	GLOBL(regs)(,%ebp,4),%esi
	cmpw	$0,16-16(%esp)
	jne	L_b_974
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_975
	.align	2,0x90
L_b_974:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,16-16(%esp)
	cltd
	idivl	16-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_977
	cmpl	$-32768,%edx
	je	L_b_977
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_976
	.align	2,0x90
L_b_977:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_979
	negw	%bx
L_b_979:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_976:
	addl	$4,GLOBL(regs)+88
L_b_975:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b048:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b018:
	ret

FUNC(op_81f9)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%ecx
	movl	%edx,%ebp
	movl	0x2164334A+2(%ecx),%eax
RR2_b006:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,16-16(%esp)
	andl	$7,%ebp
	xorl	%eax,%eax
	movw	16-16(%esp),%ax
	movl	%eax,16-16(%esp)
	movl	%eax,%edx
	movl	GLOBL(regs)(,%ebp,4),%esi
	cmpw	$0,16-16(%esp)
	jne	L_b_985
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_986
	.align	2,0x90
L_b_985:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,16-16(%esp)
	cltd
	idivl	16-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_988
	cmpl	$-32768,%edx
	je	L_b_988
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_987
	.align	2,0x90
L_b_988:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_990
	negw	%bx
L_b_990:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_987:
	addl	$6,GLOBL(regs)+88
L_b_986:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b049:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b019:
	ret

FUNC(op_81fa)

	subl	$4,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_b007:
	rolw	$8,%ax
	movl	%eax,16-16(%esp)
	movswl	16-16(%esp),%edi
	shrl	$9,%edx
	leal	2(%edi,%ecx),%eax
	movl	%edx,%ebp
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,16-16(%esp)
	andl	$7,%ebp
	xorl	%eax,%eax
	movw	16-16(%esp),%ax
	movl	%eax,16-16(%esp)
	movl	%eax,%edx
	movl	GLOBL(regs)(,%ebp,4),%esi
	cmpw	$0,16-16(%esp)
	jne	L_b_997
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_998
	.align	2,0x90
L_b_997:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,16-16(%esp)
	cltd
	idivl	16-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_1000
	cmpl	$-32768,%edx
	je	L_b_1000
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_999
	.align	2,0x90
L_b_1000:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_1002
	negw	%bx
L_b_1002:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%ebp,4)
L_b_999:
	addl	$4,GLOBL(regs)+88
L_b_998:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b050:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b020:
	ret

FUNC(op_81fb)

	subl	$20,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	movl	%edx,%eax
	andl	$7,%eax
	movl	GLOBL(regs)+88,%edi
	movl	%eax,32-16(%esp)
	movl	%edi,%edx
	movl	%edi,28-16(%esp)
	addl	$2,%edx
	addl	$4,%edi
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_b051:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%edi,24-16(%esp)
	shrl	$10,%eax
	movl	%edi,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%edi
	movl	%edx,%ebx
	movl	%edi,16-16(%esp)
	testl	$2048,%esi
	jne	L_b_1008
	movswl	16-16(%esp),%eax
	movl	%eax,16-16(%esp)
L_b_1008:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_1009
	xorl	%ebp,%ebp
	movl	%esi,%eax
	testb	%al,%al
	jge	L_b_1010
	movl	%ebp,%ebx
L_b_1010:
	testl	$64,%esi
	je	L_b_1011
	movl	%ebp,16-16(%esp)
L_b_1011:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1012
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b052:
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	28-16(%esp),%edi
	addl	$6,%edi
	movswl	20-16(%esp),%eax
	movl	%edi,GLOBL(regs)+88
	addl	%eax,%ebx
L_b_1012:
	cmpl	$48,%edx
	jne	L_b_1015
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b053:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1015:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_1018
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b054:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1018:
	cmpl	$3,%ecx
	jne	L_b_1021
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b055:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1021:
	andl	$4,%esi
	jne	L_b_1024
	addl	16-16(%esp),%ebx
L_b_1024:
	testl	%ecx,%ecx
	je	L_b_1025
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1025:
	testl	%esi,%esi
	je	L_b_1028
	addl	16-16(%esp),%ebx
L_b_1028:
	leal	(%ebp,%ebx),%edx
	jmp	L_b_1029
	.align	2,0x90
L_b_1009:
	movl	%esi,%eax
	movsbl	%al,%esi
	movl	%esi,20-16(%esp)
	addl	%esi,%edx
	addl	16-16(%esp),%edx
L_b_1029:
	movl	%edx,%edi
	shrl	$14,%edi
	andl	$65535,%edx
	andl	$1020,%edi
	addl	GLOBL(R24)(%edi),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	xorl	%edi,%edi
	movw	20-16(%esp),%di
	movl	32-16(%esp),%eax
	movl	%edi,20-16(%esp)
	movl	%edi,%edx
	movl	GLOBL(regs)(,%eax,4),%esi
	cmpw	$0,20-16(%esp)
	jne	L_b_1033
	movl	28-16(%esp),%edi
	pushl	%edi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_1034
	.align	2,0x90
L_b_1033:
	movswl	%dx,%edx
	movl	%esi,%eax
	movl	%edx,20-16(%esp)
	cltd
	idivl	20-16(%esp)
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_1036
	cmpl	$-32768,%edx
	je	L_b_1036
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_1034
	.align	2,0x90
L_b_1036:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_1038
	negw	%bx
L_b_1038:
	testw	%cx,%cx
	pushfl
	popl	%edi
	movl	%edi,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	32-16(%esp),%edi
	movl	%edx,GLOBL(regs)(,%edi,4)
L_b_1034:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b056:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b021:
	ret

FUNC(op_9030)

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
RR0_b057:
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
	jne	L_b_1090
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_b_1090:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_1091
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1092
	movl	%ebp,%ebx
L_b_1092:
	testl	$64,%esi
	je	L_b_1093
	movl	%ebp,16-16(%esp)
L_b_1093:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1094
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b058:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1094:
	cmpl	$48,%edx
	jne	L_b_1097
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b059:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1097:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_b_1100
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b060:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1100:
	cmpl	$3,20-16(%esp)
	jne	L_b_1103
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b061:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1103:
	andl	$4,%esi
	jne	L_b_1106
	addl	16-16(%esp),%ebx
L_b_1106:
	cmpl	$0,20-16(%esp)
	je	L_b_1107
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1107:
	testl	%esi,%esi
	je	L_b_1110
	addl	16-16(%esp),%ebx
L_b_1110:
	leal	(%ebp,%ebx),%edx
	jmp	L_b_1111
	.align	2,0x90
L_b_1091:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_b_1111:
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
	subb	(%ebx,%edi),%cl
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
	jl	JJ_b022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b062:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b022:
	ret

FUNC(op_903b)

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
RR0_b063:
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
	jne	L_b_1145
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_b_1145:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_1146
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1147
	movl	%ebp,%ebx
L_b_1147:
	testl	$64,%esi
	je	L_b_1148
	movl	%ebp,16-16(%esp)
L_b_1148:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1149
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b064:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1149:
	cmpl	$48,%edx
	jne	L_b_1152
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b065:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1152:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_b_1155
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b066:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1155:
	cmpl	$3,20-16(%esp)
	jne	L_b_1158
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b067:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1158:
	andl	$4,%esi
	jne	L_b_1161
	addl	16-16(%esp),%ebx
L_b_1161:
	cmpl	$0,20-16(%esp)
	je	L_b_1162
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1162:
	testl	%esi,%esi
	je	L_b_1165
	addl	16-16(%esp),%ebx
L_b_1165:
	leal	(%ebp,%ebx),%edx
	jmp	L_b_1166
	.align	2,0x90
L_b_1146:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_b_1166:
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
	subb	(%ebx,%edi),%cl
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
	jl	JJ_b023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b068:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b023:
	ret

FUNC(op_9070)

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
RR0_b069:
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
	jne	L_b_1219
	movswl	%di,%edi
L_b_1219:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1220
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1221
	movl	%ebp,%ebx
L_b_1221:
	testl	$64,%esi
	je	L_b_1222
	movl	%ebp,%edi
L_b_1222:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1223
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_b070:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1223:
	cmpl	$48,%edx
	jne	L_b_1226
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b071:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1226:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_b_1229
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b072:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1229:
	cmpl	$3,16-16(%esp)
	jne	L_b_1232
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b073:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1232:
	andl	$4,%esi
	jne	L_b_1235
	addl	%edi,%ebx
L_b_1235:
	cmpl	$0,16-16(%esp)
	je	L_b_1236
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1236:
	testl	%esi,%esi
	je	L_b_1239
	addl	%edi,%ebx
L_b_1239:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1240
	.align	2,0x90
L_b_1220:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_1240:
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
	subw	16-16(%esp),%cx
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
	jl	JJ_b024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b074:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b024:
	ret

FUNC(op_907b)

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
RR0_b075:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_b_1281
	movswl	%di,%edi
L_b_1281:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1282
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1283
	movl	%ebp,%ebx
L_b_1283:
	testl	$64,%esi
	je	L_b_1284
	movl	%ebp,%edi
L_b_1284:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1285
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_b076:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1285:
	cmpl	$48,%edx
	jne	L_b_1288
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b077:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1288:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_b_1291
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b078:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1291:
	cmpl	$3,16-16(%esp)
	jne	L_b_1294
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b079:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1294:
	andl	$4,%esi
	jne	L_b_1297
	addl	%edi,%ebx
L_b_1297:
	cmpl	$0,16-16(%esp)
	je	L_b_1298
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1298:
	testl	%esi,%esi
	je	L_b_1301
	addl	%edi,%ebx
L_b_1301:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1302
	.align	2,0x90
L_b_1282:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_1302:
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
	subw	16-16(%esp),%cx
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
	jl	JJ_b025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b080:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b025:
	ret

FUNC(op_90b0)

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
RR0_b081:
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
	jne	L_b_1358
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_b_1358:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_1359
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1360
	movl	%ebp,%ebx
L_b_1360:
	testl	$64,%esi
	je	L_b_1361
	movl	%ebp,16-16(%esp)
L_b_1361:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1362
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b082:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1362:
	cmpl	$48,%edx
	jne	L_b_1365
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b083:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1365:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_b_1368
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b084:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1368:
	cmpl	$3,20-16(%esp)
	jne	L_b_1371
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b085:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1371:
	andl	$4,%esi
	jne	L_b_1374
	addl	16-16(%esp),%ebx
L_b_1374:
	cmpl	$0,20-16(%esp)
	je	L_b_1375
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1375:
	testl	%esi,%esi
	je	L_b_1378
	addl	16-16(%esp),%ebx
L_b_1378:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1379
	.align	2,0x90
L_b_1359:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_b_1379:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edi,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b086:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b026:
	ret

FUNC(op_90bb)

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
RR0_b087:
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
	jne	L_b_1420
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_b_1420:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testl	$256,%esi
	je	L_b_1421
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1422
	movl	%ebp,%ebx
L_b_1422:
	testl	$64,%esi
	je	L_b_1423
	movl	%ebp,16-16(%esp)
L_b_1423:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1424
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_b088:
	rolw	$8,%ax
	movl	28-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1424:
	cmpl	$48,%edx
	jne	L_b_1427
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b089:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1427:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,20-16(%esp)
	cmpl	$2,%edi
	jne	L_b_1430
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b090:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1430:
	cmpl	$3,20-16(%esp)
	jne	L_b_1433
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b091:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1433:
	andl	$4,%esi
	jne	L_b_1436
	addl	16-16(%esp),%ebx
L_b_1436:
	cmpl	$0,20-16(%esp)
	je	L_b_1437
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1437:
	testl	%esi,%esi
	je	L_b_1440
	addl	16-16(%esp),%ebx
L_b_1440:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1441
	.align	2,0x90
L_b_1421:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	16-16(%esp),%eax
L_b_1441:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	32-16(%esp),%edi
	addl	GLOBL(R24)(%edx),%eax
	movl	GLOBL(regs)(,%edi,4),%ecx
	movl	(%eax),%eax
	bswapl	%eax
	subl	%eax,%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(,%edi,4)
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b092:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b027:
	ret

FUNC(op_90f0)

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
RR0_b093:
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
	jne	L_b_1497
	movswl	%di,%edi
L_b_1497:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1498
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1499
	movl	%ebp,%ebx
L_b_1499:
	testl	$64,%esi
	je	L_b_1500
	movl	%ebp,%edi
L_b_1500:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1501
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_b094:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1501:
	cmpl	$48,%edx
	jne	L_b_1504
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b095:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1504:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_b_1507
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b096:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1507:
	cmpl	$3,16-16(%esp)
	jne	L_b_1510
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b097:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1510:
	andl	$4,%esi
	jne	L_b_1513
	addl	%edi,%ebx
L_b_1513:
	cmpl	$0,16-16(%esp)
	je	L_b_1514
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1514:
	testl	%esi,%esi
	je	L_b_1517
	addl	%edi,%ebx
L_b_1517:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1518
	.align	2,0x90
L_b_1498:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_1518:
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
	subl	%eax,GLOBL(regs)(,%edx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b028:
	ret

FUNC(op_90fb)

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
RR0_b099:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_b_1559
	movswl	%di,%edi
L_b_1559:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1560
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1561
	movl	%ebp,%ebx
L_b_1561:
	testl	$64,%esi
	je	L_b_1562
	movl	%ebp,%edi
L_b_1562:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1563
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_b100:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1563:
	cmpl	$48,%edx
	jne	L_b_1566
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b101:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1566:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_b_1569
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b102:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1569:
	cmpl	$3,16-16(%esp)
	jne	L_b_1572
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b103:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1572:
	andl	$4,%esi
	jne	L_b_1575
	addl	%edi,%ebx
L_b_1575:
	cmpl	$0,16-16(%esp)
	je	L_b_1576
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1576:
	testl	%esi,%esi
	je	L_b_1579
	addl	%edi,%ebx
L_b_1579:
	leal	(%ebp,%ebx),%eax
	jmp	L_b_1580
	.align	2,0x90
L_b_1560:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_1580:
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
	subl	%eax,GLOBL(regs)(,%edx,4)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b029:
	ret

FUNC(op_9100)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	movl	%edx,%ebp
	andl	$7,%ebp
	movl	$GLOBL(regs),%edx
	andl	$7,%eax
	movsbl	(%edx,%ebp,4),%ecx
	movsbl	(%edx,%eax,4),%eax
	movl	%ecx,%edi
	subl	%eax,%edi
	testb	$1,regflags+4
	je	L_b_1592
	decl	%edi
L_b_1592:
	movl	%eax,%esi
	movl	%edi,%ebx
	shrl	$31,%esi
	movsbl	%bl,%eax
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	shrl	$31,%ecx
	xorl	%eax,%eax
	testl	%esi,%esi
	jne	L_b_1601
	testl	%ecx,%ecx
	je	L_b_1593
	cmpl	$0,16-16(%esp)
	je	L_b_1594
	jmp	L_b_1593
	.align	2,0x90
L_b_1601:
	testl	%ecx,%ecx
	jne	L_b_1593
	cmpl	$0,16-16(%esp)
	je	L_b_1593
L_b_1594:
	movl	$1,%eax
L_b_1593:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_b_1598
	testl	%ecx,%ecx
	je	L_b_1597
L_b_1598:
	cmpl	$0,16-16(%esp)
	je	L_b_1596
	testl	%ecx,%ecx
	je	L_b_1597
	testl	%esi,%esi
	je	L_b_1596
L_b_1597:
	movl	$1,%edx
L_b_1596:
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
	je	L_b_1599
	andb	$191,%cl
	movb	%cl,regflags
L_b_1599:
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
	jl	JJ_b030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b030:
	ret

FUNC(op_9108)

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
	movl	%eax,%edi
	subl	%edx,%edi
	testb	$1,regflags+4
	je	L_b_1605
	decl	%edi
L_b_1605:
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
	jne	L_b_1615
	testl	%ecx,%ecx
	je	L_b_1606
	cmpl	$0,16-16(%esp)
	je	L_b_1607
	jmp	L_b_1606
	.align	2,0x90
L_b_1615:
	testl	%ecx,%ecx
	jne	L_b_1606
	cmpl	$0,16-16(%esp)
	je	L_b_1606
L_b_1607:
	movl	$1,%eax
L_b_1606:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_b_1611
	testl	%ecx,%ecx
	je	L_b_1610
L_b_1611:
	cmpl	$0,16-16(%esp)
	je	L_b_1609
	testl	%ecx,%ecx
	je	L_b_1610
	testl	%esi,%esi
	je	L_b_1609
L_b_1610:
	movl	$1,%edx
L_b_1609:
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
	je	L_b_1612
	andb	$191,%cl
	movb	%cl,regflags
L_b_1612:
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
	jl	JJ_b031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b031:
	ret

FUNC(op_9130)

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
RR0_b107:
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
	jne	L_b_1653
	movswl	%di,%edi
L_b_1653:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1654
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_b_1655
	movl	%ebp,%ebx
L_b_1655:
	testl	$64,%esi
	je	L_b_1656
	movl	%ebp,%edi
L_b_1656:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1657
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_b108:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_b_1657:
	cmpl	$48,%edx
	jne	L_b_1660
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b109:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_b_1660:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_b_1663
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b110:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1663:
	cmpl	$3,16-16(%esp)
	jne	L_b_1666
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b111:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1666:
	andl	$4,%esi
	jne	L_b_1669
	addl	%edi,%ebx
L_b_1669:
	cmpl	$0,16-16(%esp)
	je	L_b_1670
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_b_1670:
	testl	%esi,%esi
	je	L_b_1673
	addl	%edi,%ebx
L_b_1673:
	leal	(%ebp,%ebx),%edx
	jmp	L_b_1674
	.align	2,0x90
L_b_1654:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_b_1674:
	movl	%edx,%eax
	shrl	$14,%eax
	movl	%edx,%ecx
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	movb	(%ecx,%edx),%dl
	subb	31-16(%esp),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b112:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b032:
	ret

FUNC(op_9140)

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
	movl	%ecx,%edi
	subl	%eax,%edi
	testb	$1,regflags+4
	je	L_b_1700
	decl	%edi
L_b_1700:
	movl	%eax,%esi
	shrl	$31,%esi
	movswl	%di,%eax
	movl	%eax,%ebx
	shrl	$31,%ecx
	shrl	$31,%ebx
	xorl	%eax,%eax
	testl	%esi,%esi
	jne	L_b_1709
	testl	%ecx,%ecx
	je	L_b_1701
	testl	%ebx,%ebx
	je	L_b_1702
	jmp	L_b_1701
	.align	2,0x90
L_b_1709:
	testl	%ecx,%ecx
	jne	L_b_1701
	testl	%ebx,%ebx
	je	L_b_1701
L_b_1702:
	movl	$1,%eax
L_b_1701:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_b_1706
	testl	%ecx,%ecx
	je	L_b_1705
L_b_1706:
	testl	%ebx,%ebx
	je	L_b_1704
	testl	%ecx,%ecx
	je	L_b_1705
	testl	%esi,%esi
	je	L_b_1704
L_b_1705:
	movl	$1,%edx
L_b_1704:
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
	je	L_b_1707
	andb	$191,%cl
	movb	%cl,regflags
L_b_1707:
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
	jl	JJ_b033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b033:
	ret

FUNC(op_9148)

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
	movl	%edx,%ecx
	subl	%eax,%ecx
	testb	$1,regflags+4
	je	L_b_1715
	decl	%ecx
L_b_1715:
	shrl	$31,%eax
	movl	%eax,16-16(%esp)
	movswl	%cx,%eax
	movl	%edx,%ebx
	movl	%eax,%esi
	shrl	$31,%ebx
	shrl	$31,%esi
	xorl	%eax,%eax
	cmpl	$0,16-16(%esp)
	jne	L_b_1726
	testl	%ebx,%ebx
	je	L_b_1716
	testl	%esi,%esi
	je	L_b_1717
	jmp	L_b_1716
	.align	2,0x90
L_b_1726:
	testl	%ebx,%ebx
	jne	L_b_1716
	testl	%esi,%esi
	je	L_b_1716
L_b_1717:
	movl	$1,%eax
L_b_1716:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	cmpl	$0,16-16(%esp)
	je	L_b_1721
	testl	%ebx,%ebx
	je	L_b_1720
L_b_1721:
	testl	%esi,%esi
	je	L_b_1719
	testl	%ebx,%ebx
	je	L_b_1720
	cmpl	$0,16-16(%esp)
	je	L_b_1719
L_b_1720:
	movl	$1,%edx
L_b_1719:
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
	je	L_b_1722
	andb	$191,%bl
	movb	%bl,regflags
L_b_1722:
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
	jl	JJ_b034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b034:
	ret

FUNC(op_9170)

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
RR0_b115:
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
	jne	L_b_1780
	movswl	%di,%edi
L_b_1780:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_b_1781
	xorl	%ebp,%ebp
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_b_1782
	movl	%ebp,16-16(%esp)
L_b_1782:
	testl	$64,%esi
	je	L_b_1783
	movl	%ebp,%edi
L_b_1783:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_b_1784
	movl	20-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b116:
	rolw	$8,%ax
	movl	24-16(%esp),%ebx
	cwtl
	addl	$6,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_b_1784:
	cmpl	$48,%edx
	jne	L_b_1787
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b117:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_b_1787:
	movl	%esi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_b_1790
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_b118:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1790:
	cmpl	$3,%ecx
	jne	L_b_1793
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_b119:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_b_1793:
	andl	$4,%esi
	jne	L_b_1796
	addl	%edi,16-16(%esp)
L_b_1796:
	testl	%ecx,%ecx
	je	L_b_1797
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_b_1797:
	testl	%esi,%esi
	je	L_b_1800
	addl	%edi,16-16(%esp)
L_b_1800:
	movl	16-16(%esp),%eax
	addl	%ebp,%eax
	jmp	L_b_1801
	.align	2,0x90
L_b_1781:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_b_1801:
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
	subw	30-16(%esp),%ax
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
	jl	JJ_b035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b120:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b035:
	ret

FUNC(op_9180)

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
	movl	%eax,%edi
	subl	%ecx,%edi
	testb	$1,regflags+4
	je	L_b_1837
	decl	%edi
L_b_1837:
	movl	%ecx,%esi
	movl	%edi,%ebx
	shrl	$31,%esi
	movl	%eax,%ecx
	shrl	$31,%ebx
	shrl	$31,%ecx
	xorl	%eax,%eax
	testl	%esi,%esi
	jne	L_b_1846
	testl	%ecx,%ecx
	je	L_b_1838
	testl	%ebx,%ebx
	je	L_b_1839
	jmp	L_b_1838
	.align	2,0x90
L_b_1846:
	testl	%ecx,%ecx
	jne	L_b_1838
	testl	%ebx,%ebx
	je	L_b_1838
L_b_1839:
	movl	$1,%eax
L_b_1838:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_b_1843
	testl	%ecx,%ecx
	je	L_b_1842
L_b_1843:
	testl	%ebx,%ebx
	je	L_b_1841
	testl	%ecx,%ecx
	je	L_b_1842
	testl	%esi,%esi
	je	L_b_1841
L_b_1842:
	movl	$1,%edx
L_b_1841:
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
	je	L_b_1844
	andb	$191,%cl
	movb	%cl,regflags
L_b_1844:
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
	jl	JJ_b036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b121:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b036:
	ret

FUNC(op_9188)

	subl	$4,%esp
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
	movl	%eax,16-16(%esp)
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
	bswapl	%eax
	movl	%eax,%edi
	subl	16-16(%esp),%edi
	testb	$1,regflags+4
	je	L_b_1852
	decl	%edi
L_b_1852:
	movl	16-16(%esp),%esi
	movl	%eax,%ecx
	movl	%edi,%ebx
	shrl	$31,%esi
	shrl	$31,%ecx
	shrl	$31,%ebx
	xorl	%eax,%eax
	testl	%esi,%esi
	jne	L_b_1863
	testl	%ecx,%ecx
	je	L_b_1853
	testl	%ebx,%ebx
	je	L_b_1854
	jmp	L_b_1853
	.align	2,0x90
L_b_1863:
	testl	%ecx,%ecx
	jne	L_b_1853
	testl	%ebx,%ebx
	je	L_b_1853
L_b_1854:
	movl	$1,%eax
L_b_1853:
	movb	%al,%dl
	andb	$1,%dl
	movb	regflags+1,%al
	salb	$3,%dl
	andb	$247,%al
	orb	%dl,%al
	xorl	%edx,%edx
	movb	%al,regflags+1
	testl	%esi,%esi
	je	L_b_1858
	testl	%ecx,%ecx
	je	L_b_1857
L_b_1858:
	testl	%ebx,%ebx
	je	L_b_1856
	testl	%ecx,%ecx
	je	L_b_1857
	testl	%esi,%esi
	je	L_b_1856
L_b_1857:
	movl	$1,%edx
L_b_1856:
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
	je	L_b_1859
	andb	$191,%cl
	movb	%cl,regflags
L_b_1859:
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
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b037:
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


FUNC(op_80f8)

	subl	$8,%esp
	movl	%eax,%ecx
	movl	GLOBL(regs)+88,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%esi),%ax
RR2_b008:
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movswl	20-16(%esp),%edx
	movl	%edx,20-16(%esp)
	shrl	$7,%ecx
	shrl	$14,%edx
	movl	20-16(%esp),%eax
	andl	$1020,%edx
	andl	$65535,%eax
	andl	$28,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edx,%edx
	movw	(%eax),%dx
	rolw	$8,%dx
	movl	%edx,20-16(%esp)
	movl	$GLOBL(regs),%edi
	xorl	%eax,%eax
	movw	20-16(%esp),%ax
	movl	%eax,20-16(%esp)
	movl	%eax,%ebx
	movl	(%ecx,%edi),%ebp
	cmpw	$0,20-16(%esp)
	jne	L_b_438
	pushl	%esi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_439
	.align	2,0x90
L_b_438:
	xorl	%edx,%edx
	movw	%bx,%dx
	movl	%ebp,%eax
	movl	%edx,20-16(%esp)
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%esi
	movl	%edx,%ebx
	cmpl	$65535,%esi
	jbe	L_b_441
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_440
	.align	2,0x90
L_b_441:
	testw	%si,%si
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%esi,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ecx,%edi)
L_b_440:
	addl	$4,GLOBL(regs)+88
L_b_439:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b038:
	ret

FUNC(op_80f9)

	subl	$8,%esp
	movl	GLOBL(regs)+88,%esi
	movl	%eax,%ecx
	movl	0x2164334A+2(%esi),%eax
RR2_b009:
	bswapl	%eax
	movl	%eax,20-16(%esp)
	shrl	$7,%ecx
	shrl	$14,%eax
	movl	20-16(%esp),%edx
	andl	$1020,%eax
	andl	$65535,%edx
	andl	$28,%ecx
	addl	GLOBL(R24)(%eax),%edx
	xorl	%eax,%eax
	movw	(%edx),%ax
	rolw	$8,%ax
	movl	%eax,20-16(%esp)
	movl	$GLOBL(regs),%edi
	xorl	%edx,%edx
	movw	20-16(%esp),%dx
	movl	%edx,20-16(%esp)
	movl	%edx,%ebx
	movl	(%ecx,%edi),%ebp
	cmpw	$0,20-16(%esp)
	jne	L_b_458
	pushl	%esi
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_459
	.align	2,0x90
L_b_458:
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%eax,20-16(%esp)
	movl	%ebp,%eax
	xorl	%edx,%edx
	divl	20-16(%esp)
	movl	%eax,%esi
	movl	%edx,%ebx
	cmpl	$65535,%esi
	jbe	L_b_461
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_460
	.align	2,0x90
L_b_461:
	testw	%si,%si
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%esi,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%ecx,%edi)
L_b_460:
	addl	$6,GLOBL(regs)+88
L_b_459:
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b039:
	ret

FUNC(op_80fc)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	$GLOBL(regs),%edi
	movl	%edx,%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_b010:
	rolw	$8,%ax
	andl	$28,%esi
	movl	%eax,%ebx
	movl	(%esi,%edi),%ebp
	testw	%ax,%ax
	jne	L_b_522
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_523
	.align	2,0x90
L_b_522:
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%eax,16-16(%esp)
	movl	%ebp,%eax
	xorl	%edx,%edx
	divl	16-16(%esp)
	movl	%eax,%ebx
	movl	%edx,%ecx
	cmpl	$65535,%ebx
	jbe	L_b_525
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_524
	.align	2,0x90
L_b_525:
	testw	%bx,%bx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ebx,%edx
	movl	%ecx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,(%esi,%edi)
L_b_524:
	addl	$4,GLOBL(regs)+88
L_b_523:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b040:
	ret

FUNC(op_8110)

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
	orb	(%ebx,%eax),%cl
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
	jl	JJ_b041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b126:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b041:
	ret

FUNC(op_8118)

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
	orb	%al,23-16(%esp)
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
	jl	JJ_b042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b127:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b042:
	ret

FUNC(op_8120)

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
	orb	%al,19-12(%esp)
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
	jl	JJ_b043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b128:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b043:
	ret

FUNC(op_8128)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b011:
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
	orb	(%edx,%eax),%bl
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
	jl	JJ_b044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b129:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b044:
	ret

FUNC(op_8138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b012:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	andl	$28,%ebx
	shrl	$14,%ecx
	andl	$65535,%edx
	andl	$1020,%ecx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%ecx),%eax
	orb	(%edx,%eax),%bl
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
	jl	JJ_b045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b130:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b045:
	ret

FUNC(op_8139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_b013:
	bswapl	%ecx
	movl	%ecx,%edx
	andl	$28,%ebx
	shrl	$14,%edx
	andl	$65535,%ecx
	andl	$1020,%edx
	movb	GLOBL(regs)(%ebx),%bl
	movl	GLOBL(R24)(%edx),%eax
	orb	(%ecx,%eax),%bl
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
	jl	JJ_b046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b046:
	ret

FUNC(op_8140)

	movl	%eax,%edx
	movl	%eax,%ebx
	movl	$GLOBL(regs),%ecx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_b014:
	rolw	$8,%di
	movl	%edi,%eax
	andl	$7,%edx
	movl	%eax,%esi
	addw	(%ecx,%edx,4),%si
	andl	$28,%ebx
	movl	%esi,%eax
	movl	(%ebx,%ecx),%edx
	shrw	$4,%ax
	xorb	%dl,%dl
	andl	$240,%eax
	orl	%eax,%edx
	movl	%esi,%eax
	andl	$15,%eax
	orl	%eax,%edx
	movl	%edx,(%ebx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b047:
	ret

FUNC(op_8150)

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
	orw	(%ebx,%esi),%ax
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
	jl	JJ_b048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b048:
	ret

FUNC(op_8158)

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
	orl	%eax,%edi
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
	jl	JJ_b049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b049:
	ret

FUNC(op_8160)

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
	orl	%eax,%edi
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
	jl	JJ_b050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b050:
	ret

FUNC(op_8168)

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
RR2_b015:
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
	orw	(%ebx,%esi),%ax
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
	jl	JJ_b051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b051:
	ret

FUNC(op_8178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b016:
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
	orw	GLOBL(regs)(%ebx),%ax
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
	jl	JJ_b052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b052:
	ret

FUNC(op_8179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_b017:
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
	orw	GLOBL(regs)(%ebx),%ax
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
	jl	JJ_b053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b053:
	ret

FUNC(op_8180)

	movl	%eax,%edx
	pushl	%ebx
	movl	%edx,%ecx
	andl	$7,%eax
	movl	$GLOBL(regs),%ebx
	shrl	$7,%ecx
	movw	(%ebx,%eax,4),%dx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b018:
	rolw	$8,%si
	movl	%edx,%eax
	salw	$4,%ax
	andl	$15,%edx
	andl	$3840,%eax
	orl	%edx,%eax
	andl	$28,%ecx
	addl	%esi,%eax
	movw	%ax,(%ecx,%ebx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b054:
	ret

FUNC(op_8190)

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
	orl	(%ebx,%esi),%eax
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
	jl	JJ_b055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b055:
	ret

FUNC(op_8198)

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
	orl	%eax,%ebp
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
	jl	JJ_b056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b056:
	ret

FUNC(op_81a0)

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
	orl	%eax,%ebp
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
	jl	JJ_b057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b057:
	ret

FUNC(op_81a8)

	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b019:
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
	orl	(%ebx,%esi),%eax
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
	jl	JJ_b058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b058:
	ret

FUNC(op_81b8)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b020:
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
	orl	GLOBL(regs)(%ebx),%eax
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
	jl	JJ_b059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b059:
	ret

FUNC(op_81b9)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_b021:
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
	orl	GLOBL(regs)(%ebx),%eax
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
	jl	JJ_b060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b060:
	ret

FUNC(op_81c0)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	movl	%edx,%edi
	andl	$7,%edi
	movl	$GLOBL(regs),%edx
	movl	GLOBL(regs)+88,%ecx
	movw	(%edx,%eax,4),%bx
	movl	(%edx,%edi,4),%esi
	testw	%bx,%bx
	jne	L_b_879
	pushl	%ecx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_880
	.align	2,0x90
L_b_879:
	movswl	%bx,%ebx
	movl	%esi,%eax
	movl	%ebx,12-12(%esp)
	cltd
	idivl	%ebx
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_882
	cmpl	$-32768,%edx
	je	L_b_882
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_881
	.align	2,0x90
L_b_882:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_884
	negw	%bx
L_b_884:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%edi,4)
L_b_881:
	addl	$2,GLOBL(regs)+88
L_b_880:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b061:
	ret

FUNC(op_81fc)

	subl	$4,%esp
	shrl	$9,%eax
	movl	%eax,%edi
	andl	$7,%edi
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_b022:
	rolw	$8,%ax
	movl	%eax,%ecx
	movl	GLOBL(regs)(,%edi,4),%esi
	testw	%ax,%ax
	jne	L_b_1042
	pushl	%edx
	pushl	$5
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_b_1043
	.align	2,0x90
L_b_1042:
	movswl	%cx,%ecx
	movl	%esi,%eax
	movl	%ecx,12-12(%esp)
	cltd
	idivl	%ecx
	movl	%eax,%ecx
	movl	%edx,%ebx
	movl	%ecx,%edx
	andl	$-32768,%edx
	je	L_b_1045
	cmpl	$-32768,%edx
	je	L_b_1045
	movb	regflags,%al
	orb	$128,%al
	movb	%al,regflags
	andb	$254,%al
	orb	$8,regflags+1
	movb	%al,regflags
	jmp	L_b_1044
	.align	2,0x90
L_b_1045:
	movswl	%bx,%eax
	movl	%esi,%edx
	shrl	$31,%eax
	shrl	$31,%edx
	cmpl	%edx,%eax
	je	L_b_1047
	negw	%bx
L_b_1047:
	testw	%cx,%cx
	pushfl
	popl	%eax
	movl	%eax,regflags

	movl	%ecx,%edx
	movl	%ebx,%eax
	andl	$65535,%edx
	sall	$16,%eax
	orl	%eax,%edx
	movl	%edx,GLOBL(regs)(,%edi,4)
L_b_1044:
	addl	$4,GLOBL(regs)+88
L_b_1043:
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b062:
	ret

FUNC(op_9000)

	subl	$4,%esp
	movl	%eax,%ecx
	movl	%eax,%edx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	andl	$7,%ecx
	movb	(%edx,%eax),%bl
	subb	(%eax,%ecx,4),%bl
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
	jl	JJ_b063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b063:
	ret

FUNC(op_9010)

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
	subb	(%esi,%eax),%bl
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
	jl	JJ_b064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b064:
	ret

FUNC(op_9018)

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
	subb	%al,%dl
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
	jl	JJ_b065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b065:
	ret

FUNC(op_9020)

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
	subb	%al,%bl
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
	jl	JJ_b066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b066:
	ret

FUNC(op_9028)

	movl	%eax,%edx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_b023:
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
	subb	(%eax,%edx),%cl
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,%eax
	movb	%al,GLOBL(regs)(%ebx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b067:
	ret

FUNC(op_9038)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b024:
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
	subb	(%edx,%esi),%bl
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
	jl	JJ_b068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b068:
	ret

FUNC(op_9039)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_b025:
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
	subb	(%edx,%esi),%bl
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
	jl	JJ_b069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b069:
	ret

FUNC(op_903a)

	subl	$4,%esp
	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_b026:
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
	subb	(%edx,%esi),%bl
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
	jl	JJ_b070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b070:
	ret

FUNC(op_903c)

	subl	$4,%esp
	movl	%eax,%edx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	movl	GLOBL(regs)+88,%ecx
	movb	(%edx,%eax),%bl
	subb	0x2164334A+3(%ecx),%bl
RR3_b000:
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
	jl	JJ_b071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b071:
	ret

FUNC(op_9040)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	andl	$7,%ecx
	movw	(%edx,%eax),%si
	subw	(%eax,%ecx,4),%si
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
	jl	JJ_b072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b072:
	ret

FUNC(op_9048)

	movl	%eax,%ecx
	movl	%eax,%edx
	pushl	%ebx
	andl	$7,%ecx
	shrl	$7,%edx
	movl	$GLOBL(regs),%eax
	andl	$28,%edx
	addl	$8,%ecx
	movw	(%edx,%eax),%si
	subw	(%eax,%ecx,4),%si
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
	jl	JJ_b073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b073:
	ret

FUNC(op_9050)

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
	subw	%ax,%si
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
	jl	JJ_b074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b074:
	ret

FUNC(op_9058)

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
	subw	%ax,%dx
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
	jl	JJ_b075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b075:
	ret

FUNC(op_9060)

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
	subw	%ax,%cx
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
	jl	JJ_b076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b076:
	ret

FUNC(op_9068)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b027:
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
	subw	%ax,%si
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
	jl	JJ_b077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b077:
	ret

FUNC(op_9078)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b028:
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
	subw	%dx,%si
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
	jl	JJ_b078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b078:
	ret

FUNC(op_9079)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_b029:
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
	subw	%dx,%si
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
	jl	JJ_b079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b079:
	ret

FUNC(op_907a)

	movl	%eax,%ecx
	pushl	%ebx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b030:
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
	subw	%dx,%si
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
	jl	JJ_b080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b080:
	ret

FUNC(op_907c)

	movl	%eax,%edx
	pushl	%ebx
	shrl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_b031:
	rolw	$8,%cx
	andl	$28,%edx
	movl	$GLOBL(regs),%eax
	movw	(%edx,%eax),%si
	subw	%cx,%si
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
	jl	JJ_b081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b081:
	ret

FUNC(op_9080)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$28,%edx
	andl	$7,%eax
	movl	GLOBL(regs)(%edx),%ecx
	subl	GLOBL(regs)(,%eax,4),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b082:
	ret

FUNC(op_9088)

	movl	%eax,%edx
	shrl	$7,%edx
	andl	$7,%eax
	andl	$28,%edx
	addl	$8,%eax
	movl	GLOBL(regs)(%edx),%ecx
	subl	GLOBL(regs)(,%eax,4),%ecx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ecx,GLOBL(regs)(%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b083:
	ret

FUNC(op_9090)

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
	subl	%eax,%esi
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%esi,(%ecx,%edx)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b084:
	ret

FUNC(op_9098)

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
	subl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%edx,(%edi,%ebx)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b085:
	ret

FUNC(op_90a0)

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
	subl	%eax,%edx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%edx,(%edi,%esi)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b086:
	ret

FUNC(op_90a8)

	movl	%eax,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%ecx
	movl	%eax,%ebx
	andl	$7,%edx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b032:
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
	subl	%eax,%esi
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%esi,(%ebx,%ecx)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b087:
	ret

FUNC(op_90b8)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_b033:
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
	subl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b088:
	ret

FUNC(op_90b9)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_b034:
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
	subl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b089:
	ret

FUNC(op_90ba)

	movl	%eax,%ecx
	shrl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b035:
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
	subl	%eax,%ebx
	pushfl
	popl	%eax
	movl	%eax,regflags
	movl	%eax,regflags+4

	movl	%ebx,GLOBL(regs)(%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b090:
	ret

FUNC(op_90bc)

	movl	GLOBL(regs)+88,%edx
	shrl	$7,%eax
	movl	0x2164334A+2(%edx),%edx
RR2_b036:
	andl	$28,%eax
	bswapl	%edx
	movl	GLOBL(regs)(%eax),%ecx
	subl	%edx,%ecx
	pushfl
	popl	%edx
	movl	%edx,regflags
	movl	%edx,regflags+4

	movl	%ecx,GLOBL(regs)(%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b091:
	ret

FUNC(op_90c0)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%edx
	andl	$7,%eax
	addl	$8,%edx
	movswl	GLOBL(regs)(,%eax,4),%eax
	subl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b092:
	ret

FUNC(op_90c8)

	movl	%eax,%edx
	shrl	$9,%edx
	andl	$7,%eax
	andl	$7,%edx
	addl	$8,%eax
	addl	$8,%edx
	movswl	GLOBL(regs)(,%eax,4),%eax
	subl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b093:
	ret

FUNC(op_90d0)

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
	subl	%eax,(%ecx,%edx,4)
	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b094:
	ret

FUNC(op_90d8)

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
	subl	%eax,(%ebx,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b095:
	ret

FUNC(op_90e0)

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
	subl	%eax,(%esi,%edi,4)
	addl	$2,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_b096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b096:
	ret

FUNC(op_90e8)

	movl	%eax,%edx
	movl	%eax,%ecx
	pushl	%ebx
	andl	$7,%edx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b037:
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
	subl	%eax,(%ebx,%ecx,4)
	popl	%ebx
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b097:
	ret

FUNC(op_90f8)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_b038:
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
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b183:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b098:
	ret

FUNC(op_90f9)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_b039:
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
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b099:
	ret

FUNC(op_90fa)

	movl	%eax,%ecx
	shrl	$9,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_b040:
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
	subl	%eax,GLOBL(regs)(,%ecx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b185:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b100:
	ret

FUNC(op_90fc)

	movl	%eax,%edx
	shrl	$9,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_b041:
	rolw	$8,%cx
	movl	%ecx,%eax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	subl	%eax,GLOBL(regs)(,%edx,4)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b101:
	ret

FUNC(op_9110)

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
	subb	(%ecx,%esi),%dl
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
	jl	JJ_b102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b187:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b102:
	ret

FUNC(op_9118)

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
	subb	19-16(%esp),%cl
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
	jl	JJ_b103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b103:
	ret

FUNC(op_9120)

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
	subb	15-12(%esp),%cl
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
	jl	JJ_b104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b189:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b104:
	ret

FUNC(op_9128)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_b042:
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
	subb	(%ebx,%esi),%cl
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
	jl	JJ_b105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b105:
	ret

FUNC(op_9138)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b043:
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
	subb	GLOBL(regs)(%ebx),%cl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%edx),%edx
	movb	%cl,(%eax,%edx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b191:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b106:
	ret

FUNC(op_9139)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_b044:
	bswapl	%ecx
	movl	%ecx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%ecx
	movl	GLOBL(R24)(%eax),%edx
	andl	$28,%ebx
	movb	(%ecx,%edx),%dl
	subb	GLOBL(regs)(%ebx),%dl
	pushfl
	popl	%ebx
	movl	%ebx,regflags
	movl	%ebx,regflags+4

	movl	GLOBL(W24)(%eax),%eax
	movb	%dl,(%ecx,%eax)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_b107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b107:
	ret

FUNC(op_9150)

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
	subw	(%ebx,%esi),%ax
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
	jl	JJ_b108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b193:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b108:
	ret

FUNC(op_9158)

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
	jl	JJ_b109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b109:
	ret

FUNC(op_9160)

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
	jl	JJ_b110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b195:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b110:
	ret

FUNC(op_9168)

	movl	%eax,%edx
	pushl	%esi
	andl	$7,%edx
	pushl	%ebx
	movl	$GLOBL(regs),%esi
	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_b045:
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
	subw	(%ebx,%esi),%dx
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
	jl	JJ_b111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b111:
	ret

FUNC(op_9178)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%esi,%esi
	movw	0x2164334A+2(%eax),%si
RR2_b046:
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
	subw	GLOBL(regs)(%ebx),%dx
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
	jl	JJ_b112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b197:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b112:
	ret

FUNC(op_9179)

	movl	%eax,%ebx
	shrl	$7,%ebx
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%eax
RR2_b047:
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
	subw	GLOBL(regs)(%ebx),%dx
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
	jl	JJ_b113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_b198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_b113:
	ret

FUNC(Init020_0b)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_b000-4
	movl	%eax,RR0_b001-4
	movl	%eax,RR0_b002-4
	movl	%eax,RR0_b003-4
	movl	%eax,RR0_b004-4
	movl	%eax,RR0_b005-4
	movl	%eax,RR0_b006-4
	movl	%eax,RR0_b007-4
	movl	%eax,RR0_b008-4
	movl	%eax,RR0_b009-4
	movl	%eax,RR0_b010-4
	movl	%eax,RR0_b011-4
	movl	%eax,RR0_b012-4
	movl	%eax,RR0_b013-4
	movl	%eax,RR0_b014-4
	movl	%eax,RR0_b015-4
	movl	%eax,RR0_b016-4
	movl	%eax,RR0_b017-4
	movl	%eax,RR0_b018-4
	movl	%eax,RR0_b019-4
	movl	%eax,RR0_b020-4
	movl	%eax,RR0_b021-4
	movl	%eax,RR0_b022-4
	movl	%eax,RR0_b023-4
	movl	%eax,RR0_b024-4
	movl	%eax,RR0_b025-4
	movl	%eax,RR0_b026-4
	movl	%eax,RR0_b027-4
	movl	%eax,RR0_b028-4
	movl	%eax,RR0_b029-4
	movl	%eax,RR0_b030-4
	movl	%eax,RR0_b031-4
	movl	%eax,RR0_b032-4
	movl	%eax,RR0_b033-4
	movl	%eax,RR0_b034-4
	movl	%eax,RR0_b035-4
	movl	%eax,RR0_b036-4
	movl	%eax,RR0_b037-4
	movl	%eax,RR0_b038-4
	movl	%eax,RR0_b039-4
	movl	%eax,RR0_b040-4
	movl	%eax,RR0_b041-4
	movl	%eax,RR0_b042-4
	movl	%eax,RR0_b043-4
	movl	%eax,RR0_b044-4
	movl	%eax,RR0_b045-4
	movl	%eax,RR0_b046-4
	movl	%eax,RR0_b047-4
	movl	%eax,RR0_b048-4
	movl	%eax,RR0_b049-4
	movl	%eax,RR0_b050-4
	movl	%eax,RR0_b051-4
	movl	%eax,RR0_b052-4
	movl	%eax,RR0_b053-4
	movl	%eax,RR0_b054-4
	movl	%eax,RR0_b055-4
	movl	%eax,RR0_b056-4
	movl	%eax,RR0_b057-4
	movl	%eax,RR0_b058-4
	movl	%eax,RR0_b059-4
	movl	%eax,RR0_b060-4
	movl	%eax,RR0_b061-4
	movl	%eax,RR0_b062-4
	movl	%eax,RR0_b063-4
	movl	%eax,RR0_b064-4
	movl	%eax,RR0_b065-4
	movl	%eax,RR0_b066-4
	movl	%eax,RR0_b067-4
	movl	%eax,RR0_b068-4
	movl	%eax,RR0_b069-4
	movl	%eax,RR0_b070-4
	movl	%eax,RR0_b071-4
	movl	%eax,RR0_b072-4
	movl	%eax,RR0_b073-4
	movl	%eax,RR0_b074-4
	movl	%eax,RR0_b075-4
	movl	%eax,RR0_b076-4
	movl	%eax,RR0_b077-4
	movl	%eax,RR0_b078-4
	movl	%eax,RR0_b079-4
	movl	%eax,RR0_b080-4
	movl	%eax,RR0_b081-4
	movl	%eax,RR0_b082-4
	movl	%eax,RR0_b083-4
	movl	%eax,RR0_b084-4
	movl	%eax,RR0_b085-4
	movl	%eax,RR0_b086-4
	movl	%eax,RR0_b087-4
	movl	%eax,RR0_b088-4
	movl	%eax,RR0_b089-4
	movl	%eax,RR0_b090-4
	movl	%eax,RR0_b091-4
	movl	%eax,RR0_b092-4
	movl	%eax,RR0_b093-4
	movl	%eax,RR0_b094-4
	movl	%eax,RR0_b095-4
	movl	%eax,RR0_b096-4
	movl	%eax,RR0_b097-4
	movl	%eax,RR0_b098-4
	movl	%eax,RR0_b099-4
	movl	%eax,RR0_b100-4
	movl	%eax,RR0_b101-4
	movl	%eax,RR0_b102-4
	movl	%eax,RR0_b103-4
	movl	%eax,RR0_b104-4
	movl	%eax,RR0_b105-4
	movl	%eax,RR0_b106-4
	movl	%eax,RR0_b107-4
	movl	%eax,RR0_b108-4
	movl	%eax,RR0_b109-4
	movl	%eax,RR0_b110-4
	movl	%eax,RR0_b111-4
	movl	%eax,RR0_b112-4
	movl	%eax,RR0_b113-4
	movl	%eax,RR0_b114-4
	movl	%eax,RR0_b115-4
	movl	%eax,RR0_b116-4
	movl	%eax,RR0_b117-4
	movl	%eax,RR0_b118-4
	movl	%eax,RR0_b119-4
	movl	%eax,RR0_b120-4
	movl	%eax,RR0_b121-4
	movl	%eax,RR0_b122-4
	movl	%eax,RR0_b123-4
	movl	%eax,RR0_b124-4
	movl	%eax,RR0_b125-4
	movl	%eax,RR0_b126-4
	movl	%eax,RR0_b127-4
	movl	%eax,RR0_b128-4
	movl	%eax,RR0_b129-4
	movl	%eax,RR0_b130-4
	movl	%eax,RR0_b131-4
	movl	%eax,RR0_b132-4
	movl	%eax,RR0_b133-4
	movl	%eax,RR0_b134-4
	movl	%eax,RR0_b135-4
	movl	%eax,RR0_b136-4
	movl	%eax,RR0_b137-4
	movl	%eax,RR0_b138-4
	movl	%eax,RR0_b139-4
	movl	%eax,RR0_b140-4
	movl	%eax,RR0_b141-4
	movl	%eax,RR0_b142-4
	movl	%eax,RR0_b143-4
	movl	%eax,RR0_b144-4
	movl	%eax,RR0_b145-4
	movl	%eax,RR0_b146-4
	movl	%eax,RR0_b147-4
	movl	%eax,RR0_b148-4
	movl	%eax,RR0_b149-4
	movl	%eax,RR0_b150-4
	movl	%eax,RR0_b151-4
	movl	%eax,RR0_b152-4
	movl	%eax,RR0_b153-4
	movl	%eax,RR0_b154-4
	movl	%eax,RR0_b155-4
	movl	%eax,RR0_b156-4
	movl	%eax,RR0_b157-4
	movl	%eax,RR0_b158-4
	movl	%eax,RR0_b159-4
	movl	%eax,RR0_b160-4
	movl	%eax,RR0_b161-4
	movl	%eax,RR0_b162-4
	movl	%eax,RR0_b163-4
	movl	%eax,RR0_b164-4
	movl	%eax,RR0_b165-4
	movl	%eax,RR0_b166-4
	movl	%eax,RR0_b167-4
	movl	%eax,RR0_b168-4
	movl	%eax,RR0_b169-4
	movl	%eax,RR0_b170-4
	movl	%eax,RR0_b171-4
	movl	%eax,RR0_b172-4
	movl	%eax,RR0_b173-4
	movl	%eax,RR0_b174-4
	movl	%eax,RR0_b175-4
	movl	%eax,RR0_b176-4
	movl	%eax,RR0_b177-4
	movl	%eax,RR0_b178-4
	movl	%eax,RR0_b179-4
	movl	%eax,RR0_b180-4
	movl	%eax,RR0_b181-4
	movl	%eax,RR0_b182-4
	movl	%eax,RR0_b183-4
	movl	%eax,RR0_b184-4
	movl	%eax,RR0_b185-4
	movl	%eax,RR0_b186-4
	movl	%eax,RR0_b187-4
	movl	%eax,RR0_b188-4
	movl	%eax,RR0_b189-4
	movl	%eax,RR0_b190-4
	movl	%eax,RR0_b191-4
	movl	%eax,RR0_b192-4
	movl	%eax,RR0_b193-4
	movl	%eax,RR0_b194-4
	movl	%eax,RR0_b195-4
	movl	%eax,RR0_b196-4
	movl	%eax,RR0_b197-4
	movl	%eax,RR0_b198-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_b000-4
	movl	%eax,RR2_b001-4
	movl	%eax,RR2_b002-4
	movl	%eax,RR2_b003-4
	movl	%eax,RR2_b004-4
	movl	%eax,RR2_b005-4
	movl	%eax,RR2_b006-4
	movl	%eax,RR2_b007-4
	movl	%eax,RR2_b008-4
	movl	%eax,RR2_b009-4
	movl	%eax,RR2_b010-4
	movl	%eax,RR2_b011-4
	movl	%eax,RR2_b012-4
	movl	%eax,RR2_b013-4
	movl	%eax,RR2_b014-4
	movl	%eax,RR2_b015-4
	movl	%eax,RR2_b016-4
	movl	%eax,RR2_b017-4
	movl	%eax,RR2_b018-4
	movl	%eax,RR2_b019-4
	movl	%eax,RR2_b020-4
	movl	%eax,RR2_b021-4
	movl	%eax,RR2_b022-4
	movl	%eax,RR2_b023-4
	movl	%eax,RR2_b024-4
	movl	%eax,RR2_b025-4
	movl	%eax,RR2_b026-4
	movl	%eax,RR2_b027-4
	movl	%eax,RR2_b028-4
	movl	%eax,RR2_b029-4
	movl	%eax,RR2_b030-4
	movl	%eax,RR2_b031-4
	movl	%eax,RR2_b032-4
	movl	%eax,RR2_b033-4
	movl	%eax,RR2_b034-4
	movl	%eax,RR2_b035-4
	movl	%eax,RR2_b036-4
	movl	%eax,RR2_b037-4
	movl	%eax,RR2_b038-4
	movl	%eax,RR2_b039-4
	movl	%eax,RR2_b040-4
	movl	%eax,RR2_b041-4
	movl	%eax,RR2_b042-4
	movl	%eax,RR2_b043-4
	movl	%eax,RR2_b044-4
	movl	%eax,RR2_b045-4
	movl	%eax,RR2_b046-4
	movl	%eax,RR2_b047-4
	incl	%eax
	movl	%eax,RR3_b000-4
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
