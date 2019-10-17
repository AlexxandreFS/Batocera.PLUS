

FUNC(op_487b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7000:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_397
	movswl	%di,%edi
L_7_397:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_398
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_399
	movl	%ebp,%ebx
L_7_399:
	testl	$64,%esi
	je	L_7_400
	movl	%ebp,%edi
L_7_400:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_401
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7001:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_401:
	cmpl	$48,%edx
	jne	L_7_404
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7002:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_404:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_407
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7003:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_407:
	cmpl	$3,16-16(%esp)
	jne	L_7_410
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7004:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_410:
	andl	$4,%esi
	jne	L_7_413
	addl	%edi,%ebx
L_7_413:
	cmpl	$0,16-16(%esp)
	je	L_7_414
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_414:
	testl	%esi,%esi
	je	L_7_417
	addl	%edi,%ebx
L_7_417:
	addl	%ebp,%ebx
	jmp	L_7_418
	.align	2,0x90
L_7_398:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%ebx
L_7_418:
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
	jl	JJ_7000
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7005:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7000:
	ret

FUNC(op_4890)

	subl	$4,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7000:
	rolw	$8,%di
	movl	%edi,%eax
	movl	(%ecx,%edx,4),%esi
	movl	%eax,%edx
	shrw	$8,%ax
	movb	$0,%dh
	movw	%ax,18-16(%esp)
	testw	%dx,%dx
	je	L_7_430
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_431:
	xorl	%ebx,%ebx
	movw	%dx,%bx
	movl	%esi,%eax
	sall	$2,%ebx
	shrl	$14,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	movl	%esi,%edx
	leal	0(,%edi,4),%ecx
	andl	$1020,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$65535,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_430
	xorl	%ebx,%ebx
	movw	%dx,%bx
	movl	%esi,%eax
	sall	$2,%ebx
	shrl	$14,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	movl	%esi,%edx
	leal	0(,%edi,4),%ecx
	andl	$1020,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$65535,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_430
	xorl	%ebx,%ebx
	movw	%dx,%bx
	movl	%esi,%eax
	sall	$2,%ebx
	shrl	$14,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	movl	%esi,%edx
	leal	0(,%edi,4),%ecx
	andl	$1020,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$65535,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_430
	xorl	%ebx,%ebx
	movw	%dx,%bx
	movl	%esi,%eax
	sall	$2,%ebx
	shrl	$14,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	movl	%esi,%edx
	leal	0(,%edi,4),%ecx
	andl	$1020,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$65535,%edx
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%dx
	testw	%dx,%dx
	jne	L_7_431
L_7_430:
	cmpw	$0,18-16(%esp)
	je	L_7_442
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_437:
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	movl	%esi,%eax
	sall	$2,%ebx
	movl	%esi,%edx
	movl	GLOBL(movem_index1)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	2(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_442
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	4(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_442
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	6(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_442
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	addl	$8,%esi
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	jne	L_7_437
L_7_442:
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7001
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7006:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7001:
	ret

FUNC(op_48a0)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,20-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7001:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%edx
	movl	20-16(%esp),%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	movl	(%ecx,%eax,4),%esi
	movl	%edx,%eax
	shrw	$8,%dx
	movb	$0,%ah
	movw	%dx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_464
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_465:
	xorl	%ebx,%ebx
	movw	%ax,%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_464
	xorl	%ebx,%ebx
	movw	%ax,%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_464
	xorl	%ebx,%ebx
	movw	%ax,%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_464
	xorl	%ebx,%ebx
	movw	%ax,%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_465
L_7_464:
	cmpw	$0,18-16(%esp)
	je	L_7_476
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_471:
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%edi
	shrl	$14,%eax
	leal	0(,%edi,4),%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_476
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%edi
	shrl	$14,%eax
	leal	0(,%edi,4),%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_476
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%edi
	shrl	$14,%eax
	leal	0(,%edi,4),%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_476
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	addl	$-2,%esi
	sall	$2,%ebx
	movl	%esi,%eax
	movl	%esi,%edx
	movl	GLOBL(movem_index2)(%ebx),%edi
	shrl	$14,%eax
	leal	0(,%edi,4),%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	jne	L_7_471
L_7_476:
	movl	20-16(%esp),%eax
	addl	$8,%eax
	movl	%esi,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7002
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7007:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7002:
	ret

FUNC(op_48a8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7002:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7000:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%edx,4),%esi
	addl	%eax,%esi
	movl	%ebx,%eax
	shrw	$8,%bx
	movb	$0,%ah
	movw	%bx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_499
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_500:
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_499
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_499
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_499
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_500
L_7_499:
	cmpw	$0,18-16(%esp)
	je	L_7_511
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_506:
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	movl	%esi,%eax
	sall	$2,%ebx
	movl	%esi,%edx
	movl	GLOBL(movem_index1)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	2(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_511
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	4(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_511
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	6(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_511
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	addl	$8,%esi
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	jne	L_7_506
L_7_511:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7003
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7008:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7003:
	ret

FUNC(op_48b0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%edi
	andl	$7,%edx
	movl	%edi,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%edi),%ax
RR2_7003:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%edi,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%edi
	movl	%eax,GLOBL(regs)+88
	xorl	%ebx,%ebx
	movw	0x2164334A(%eax),%bx
RR0_7009:
	rolw	$8,%bx
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%ebx,%eax
	movl	%edi,20-16(%esp)
	shrl	$10,%eax
	movl	%edi,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	movl	%edx,%esi
	movl	%eax,16-16(%esp)
	testb	$8,%bh
	jne	L_7_534
	movswl	16-16(%esp),%edi
	movl	%edi,16-16(%esp)
L_7_534:
	movl	%ebx,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,16-16(%esp)
	testb	$1,%bh
	je	L_7_535
	xorl	%ebp,%ebp
	testb	%bl,%bl
	jge	L_7_536
	movl	%ebp,%esi
L_7_536:
	testb	$64,%bl
	je	L_7_537
	movl	%ebp,16-16(%esp)
L_7_537:
	movl	%ebx,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_538
	movl	20-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_7010:
	rolw	$8,%ax
	movl	24-16(%esp),%edi
	cwtl
	addl	$8,%edi
	addl	%eax,%esi
	movl	%edi,GLOBL(regs)+88
L_7_538:
	cmpl	$48,%edx
	jne	L_7_541
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7011:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%esi
	movl	%eax,GLOBL(regs)+88
L_7_541:
	movl	%ebx,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_7_544
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7012:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_544:
	cmpl	$3,%ecx
	jne	L_7_547
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7013:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_547:
	andl	$4,%ebx
	jne	L_7_550
	addl	16-16(%esp),%esi
L_7_550:
	testl	%ecx,%ecx
	je	L_7_551
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%esi
	bswapl	%esi
L_7_551:
	testl	%ebx,%ebx
	je	L_7_554
	addl	16-16(%esp),%esi
L_7_554:
	addl	%ebp,%esi
	jmp	L_7_555
	.align	2,0x90
L_7_535:
	movsbl	%bl,%eax
	movl	16-16(%esp),%edi
	addl	%edx,%eax
	leal	(%edi,%eax),%esi
L_7_555:
	movw	30-16(%esp),%di
	movw	30-16(%esp),%ax
	shrw	$8,%di
	movb	$0,%ah
	movw	%di,16-16(%esp)
	testw	%ax,%ax
	je	L_7_558
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_559:
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_558
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_558
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_558
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_559
L_7_558:
	cmpw	$0,16-16(%esp)
	je	L_7_570
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_565:
	xorl	%ebx,%ebx
	movw	16-16(%esp),%bx
	movl	%esi,%eax
	sall	$2,%ebx
	movl	%esi,%edx
	movl	GLOBL(movem_index1)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	2(%esi),%edx
	movw	%bx,16-16(%esp)
	testw	%bx,%bx
	je	L_7_570
	xorl	%ebx,%ebx
	movw	16-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	4(%esi),%edx
	movw	%bx,16-16(%esp)
	testw	%bx,%bx
	je	L_7_570
	xorl	%ebx,%ebx
	movw	16-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	6(%esi),%edx
	movw	%bx,16-16(%esp)
	testw	%bx,%bx
	je	L_7_570
	xorl	%ebx,%ebx
	movw	16-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	addl	$8,%esi
	movw	%bx,16-16(%esp)
	testw	%bx,%bx
	jne	L_7_565
L_7_570:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7004
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7014:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7004:
	ret

FUNC(op_48b8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7004:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7001:
	rolw	$8,%ax
	movswl	%ax,%esi
	movl	%ecx,%eax
	shrw	$8,%cx
	movb	$0,%ah
	movw	%cx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_593
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_594:
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_593
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_593
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_593
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_594
L_7_593:
	cmpw	$0,18-16(%esp)
	je	L_7_605
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_600:
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	movl	%esi,%eax
	sall	$2,%ebx
	movl	%esi,%edx
	movl	GLOBL(movem_index1)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	2(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_605
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	4(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_605
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	6(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_605
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	addl	$8,%esi
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	jne	L_7_600
L_7_605:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7005
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7015:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7005:
	ret

FUNC(op_48b9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7005:
	rolw	$8,%dx
	movl	0x2164334A+4(%eax),%esi
RR4_7002:
	bswapl	%esi
	movl	%edx,%eax
	shrw	$8,%dx
	movb	$0,%ah
	movw	%dx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_628
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_629:
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_628
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_628
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_628
	xorl	%ebx,%ebx
	movw	%ax,%bx
	movl	%esi,%edx
	sall	$2,%ebx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ebx),%edi
	andl	$65535,%edx
	leal	0(,%edi,4),%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(%ecx),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	addl	$2,%esi
	movw	(%ebx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_629
L_7_628:
	cmpw	$0,18-16(%esp)
	je	L_7_640
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_635:
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	movl	%esi,%eax
	sall	$2,%ebx
	movl	%esi,%edx
	movl	GLOBL(movem_index1)(%ebx),%ecx
	shrl	$14,%eax
	addl	$8,%ecx
	andl	$65535,%edx
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	2(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_640
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	4(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_640
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	leal	6(%esi),%edx
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	je	L_7_640
	xorl	%ebx,%ebx
	movw	18-16(%esp),%bx
	sall	$2,%ebx
	movl	%edx,%eax
	movl	GLOBL(movem_index1)(%ebx),%ecx
	andl	$65535,%edx
	addl	$8,%ecx
	shrl	$14,%eax
	movw	GLOBL(regs)(,%ecx,4),%cx
	andl	$1020,%eax
	andl	$65535,%ecx
	addl	GLOBL(W24)(%eax),%edx
	movl	%ecx,%eax
	rolw	$8,%ax
	movw	%ax,(%edx)
	movw	(%ebx,%ebp),%bx
	addl	$8,%esi
	movw	%bx,18-16(%esp)
	testw	%bx,%bx
	jne	L_7_635
L_7_640:
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7006
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7016:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7006:
	ret

FUNC(op_48d0)

	subl	$4,%esp
	movl	%eax,%edx
	movl	$GLOBL(regs),%ecx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7006:
	rolw	$8,%di
	movl	%edi,%eax
	movl	(%ecx,%edx,4),%esi
	movl	%eax,%edx
	shrw	$8,%ax
	movb	$0,%dh
	movw	%ax,18-16(%esp)
	testw	%dx,%dx
	je	L_7_666
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_667:
	xorl	%ecx,%ecx
	movw	%dx,%cx
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%esi,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_666
	xorl	%ecx,%ecx
	movw	%dx,%cx
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%esi,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_666
	xorl	%ecx,%ecx
	movw	%dx,%cx
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%esi,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%dx
	testw	%dx,%dx
	je	L_7_666
	xorl	%ecx,%ecx
	movw	%dx,%cx
	movl	%esi,%eax
	sall	$2,%ecx
	movl	%esi,%edx
	andl	$65535,%eax
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%dx
	testw	%dx,%dx
	jne	L_7_667
L_7_666:
	cmpw	$0,18-16(%esp)
	je	L_7_678
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_673:
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%esi,%edx
	movl	%esi,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	4(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_678
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	8(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_678
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	12(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_678
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	addl	$16,%esi
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	jne	L_7_673
L_7_678:
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7007
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7017:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7007:
	ret

FUNC(op_48e0)

	subl	$8,%esp
	andl	$7,%eax
	movl	%eax,20-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7007:
	rolw	$8,%di
	movl	%edi,%eax
	movl	%eax,%edx
	movl	20-16(%esp),%eax
	movl	$GLOBL(regs),%ecx
	addl	$8,%eax
	movl	(%ecx,%eax,4),%esi
	movl	%edx,%eax
	shrw	$8,%dx
	movb	$0,%ah
	movw	%dx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_700
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_701:
	xorl	%ecx,%ecx
	movw	%ax,%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%ebx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_700
	xorl	%ecx,%ecx
	movw	%ax,%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%ebx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_700
	xorl	%ecx,%ecx
	movw	%ax,%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%ebx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_700
	xorl	%ecx,%ecx
	movw	%ax,%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%ebx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_701
L_7_700:
	cmpw	$0,18-16(%esp)
	je	L_7_712
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_707:
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%edi
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_712
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%edi
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_712
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%edi
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_712
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	addl	$-4,%esi
	sall	$2,%ecx
	movl	%esi,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index2)(%ecx),%edi
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	jne	L_7_707
L_7_712:
	movl	20-16(%esp),%eax
	addl	$8,%eax
	movl	%esi,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7008
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7018:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7008:
	ret

FUNC(op_48e8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	addl	$8,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7008:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7003:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%edx,4),%esi
	addl	%eax,%esi
	movl	%ebx,%eax
	shrw	$8,%bx
	movb	$0,%ah
	movw	%bx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_735
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_736:
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_735
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_735
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_735
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_736
L_7_735:
	cmpw	$0,18-16(%esp)
	je	L_7_747
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_742:
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%esi,%edx
	movl	%esi,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	4(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_747
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	8(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_747
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	12(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_747
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	addl	$16,%esi
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	jne	L_7_742
L_7_747:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7009
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7019:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7009:
	ret

FUNC(op_48f0)

	subl	$16,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ebx
	andl	$7,%edx
	movl	%ebx,16-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7009:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	movl	%ebx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_7020:
	rolw	$8,%si
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%ebx,24-16(%esp)
	movl	%esi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,20-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%ebp
	testl	$2048,%esi
	jne	L_7_770
	movswl	%bp,%ebp
L_7_770:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%ebp
	testl	$256,%esi
	je	L_7_771
	xorl	%ecx,%ecx
	movl	%esi,%ebx
	testb	%bl,%bl
	jge	L_7_772
	movl	%ecx,20-16(%esp)
L_7_772:
	testl	$64,%esi
	je	L_7_773
	movl	%ecx,%ebp
L_7_773:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_774
	movl	24-16(%esp),%edi
	xorl	%eax,%eax
	movw	0x2164334A(%edi),%ax
RR0_7021:
	rolw	$8,%ax
	movl	16-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,20-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_7_774:
	cmpl	$48,%edx
	jne	L_7_777
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7022:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,20-16(%esp)
L_7_777:
	movl	%esi,%edi
	andl	$3,%edi
	movl	%edi,16-16(%esp)
	cmpl	$2,%edi
	jne	L_7_780
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7023:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ecx
	movl	%eax,GLOBL(regs)+88
L_7_780:
	cmpl	$3,16-16(%esp)
	jne	L_7_783
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7024:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ecx
	movl	%eax,GLOBL(regs)+88
L_7_783:
	andl	$4,%esi
	jne	L_7_786
	addl	%ebp,20-16(%esp)
L_7_786:
	cmpl	$0,16-16(%esp)
	je	L_7_787
	movl	20-16(%esp),%edx
	movl	20-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,20-16(%esp)
L_7_787:
	testl	%esi,%esi
	je	L_7_790
	addl	%ebp,20-16(%esp)
L_7_790:
	movl	20-16(%esp),%esi
	addl	%ecx,%esi
	jmp	L_7_791
	.align	2,0x90
L_7_771:
	movl	%esi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	leal	(%ebp,%eax),%esi
L_7_791:
	movw	30-16(%esp),%di
	movw	30-16(%esp),%ax
	shrw	$8,%di
	movb	$0,%ah
	movw	%di,16-16(%esp)
	testw	%ax,%ax
	je	L_7_794
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_795:
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	sall	$2,%ebx
	andl	$65535,%eax
	movl	%ebx,20-16(%esp)
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%edi
	bswapl	%edi
	movl	%edi,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_794
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	sall	$2,%ebx
	andl	$65535,%eax
	movl	%ebx,20-16(%esp)
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%edi
	bswapl	%edi
	movl	%edi,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_794
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	sall	$2,%ebx
	andl	$65535,%eax
	movl	%ebx,20-16(%esp)
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%edi
	bswapl	%edi
	movl	%edi,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_794
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	sall	$2,%ebx
	andl	$65535,%eax
	movl	%ebx,20-16(%esp)
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%edi
	bswapl	%edi
	movl	%edi,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_795
L_7_794:
	cmpw	$0,16-16(%esp)
	je	L_7_806
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_801:
	xorl	%ecx,%ecx
	movw	16-16(%esp),%cx
	movl	%esi,%edx
	movl	%esi,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	4(%esi),%eax
	movw	%cx,16-16(%esp)
	testw	%cx,%cx
	je	L_7_806
	xorl	%ecx,%ecx
	movw	16-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	8(%esi),%eax
	movw	%cx,16-16(%esp)
	testw	%cx,%cx
	je	L_7_806
	xorl	%ecx,%ecx
	movw	16-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	12(%esi),%eax
	movw	%cx,16-16(%esp)
	testw	%cx,%cx
	je	L_7_806
	xorl	%ecx,%ecx
	movw	16-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	addl	$16,%esi
	movw	%cx,16-16(%esp)
	testw	%cx,%cx
	jne	L_7_801
L_7_806:
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7010
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7025:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7010:
	ret

FUNC(op_48f8)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7010:
	rolw	$8,%ax
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7004:
	rolw	$8,%ax
	movswl	%ax,%esi
	movl	%ecx,%eax
	shrw	$8,%cx
	movb	$0,%ah
	movw	%cx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_829
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_830:
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_829
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_829
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_829
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_830
L_7_829:
	cmpw	$0,18-16(%esp)
	je	L_7_841
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_836:
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%esi,%edx
	movl	%esi,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	4(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_841
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	8(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_841
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	12(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_841
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	addl	$16,%esi
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	jne	L_7_836
L_7_841:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7011
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7026:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7011:
	ret

FUNC(op_48f9)

	subl	$4,%esp
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7011:
	rolw	$8,%dx
	movl	0x2164334A+4(%eax),%esi
RR4_7005:
	bswapl	%esi
	movl	%edx,%eax
	shrw	$8,%dx
	movb	$0,%ah
	movw	%dx,18-16(%esp)
	testw	%ax,%ax
	je	L_7_864
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_865:
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_864
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_864
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	je	L_7_864
	xorl	%ecx,%ecx
	movw	%ax,%cx
	movl	%esi,%edx
	sall	$2,%ecx
	shrl	$14,%edx
	movl	%esi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	andl	$1020,%edx
	andl	$65535,%eax
	leal	0(,%edi,4),%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(%ebx),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	addl	$4,%esi
	movw	(%ecx,%ebp),%ax
	testw	%ax,%ax
	jne	L_7_865
L_7_864:
	cmpw	$0,18-16(%esp)
	je	L_7_876
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_871:
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%esi,%edx
	movl	%esi,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	andl	$65535,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	4(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_876
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	8(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_876
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	leal	12(%esi),%eax
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	je	L_7_876
	xorl	%ecx,%ecx
	movw	18-16(%esp),%cx
	movl	%eax,%edx
	andl	$65535,%eax
	sall	$2,%ecx
	shrl	$14,%edx
	movl	GLOBL(movem_index1)(%ecx),%ebx
	andl	$1020,%edx
	addl	$8,%ebx
	addl	GLOBL(W24)(%edx),%eax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	bswapl	%ebx
	movl	%ebx,(%eax)
	movw	(%ecx,%ebp),%cx
	addl	$16,%esi
	movw	%cx,18-16(%esp)
	testw	%cx,%cx
	jne	L_7_871
L_7_876:
	addl	$8,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7012
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7027:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7012:
	ret

FUNC(op_4a30)

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
RR0_7028:
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
	jne	L_7_932
	movswl	%di,%edi
L_7_932:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_933
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_934
	movl	%ebp,%ebx
L_7_934:
	testl	$64,%esi
	je	L_7_935
	movl	%ebp,%edi
L_7_935:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_936
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7029:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_936:
	cmpl	$48,%edx
	jne	L_7_939
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7030:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_939:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_942
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7031:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_942:
	cmpl	$3,16-16(%esp)
	jne	L_7_945
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7032:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_945:
	andl	$4,%esi
	jne	L_7_948
	addl	%edi,%ebx
L_7_948:
	cmpl	$0,16-16(%esp)
	je	L_7_949
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_949:
	testl	%esi,%esi
	je	L_7_952
	addl	%edi,%ebx
L_7_952:
	leal	(%ebp,%ebx),%edx
	jmp	L_7_953
	.align	2,0x90
L_7_933:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	leal	(%edi,%eax),%edx
L_7_953:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7013
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7033:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7013:
	ret

FUNC(op_4a3b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7034:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_987
	movswl	%di,%edi
L_7_987:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_988
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_989
	movl	%ebp,%ebx
L_7_989:
	testl	$64,%esi
	je	L_7_990
	movl	%ebp,%edi
L_7_990:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_991
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7035:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_991:
	cmpl	$48,%edx
	jne	L_7_994
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7036:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_994:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_997
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7037:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_997:
	cmpl	$3,16-16(%esp)
	jne	L_7_1000
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7038:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1000:
	andl	$4,%esi
	jne	L_7_1003
	addl	%edi,%ebx
L_7_1003:
	cmpl	$0,16-16(%esp)
	je	L_7_1004
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1004:
	testl	%esi,%esi
	je	L_7_1007
	addl	%edi,%ebx
L_7_1007:
	leal	(%ebp,%ebx),%edx
	jmp	L_7_1008
	.align	2,0x90
L_7_988:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	leal	(%edi,%eax),%edx
L_7_1008:
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7014
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7039:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7014:
	ret

FUNC(op_4a70)

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
RR0_7040:
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
	jne	L_7_1061
	movswl	%di,%edi
L_7_1061:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1062
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1063
	movl	%ebp,%ebx
L_7_1063:
	testl	$64,%esi
	je	L_7_1064
	movl	%ebp,%edi
L_7_1064:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1065
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7041:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1065:
	cmpl	$48,%edx
	jne	L_7_1068
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7042:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1068:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1071
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7043:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1071:
	cmpl	$3,16-16(%esp)
	jne	L_7_1074
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7044:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1074:
	andl	$4,%esi
	jne	L_7_1077
	addl	%edi,%ebx
L_7_1077:
	cmpl	$0,16-16(%esp)
	je	L_7_1078
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1078:
	testl	%esi,%esi
	je	L_7_1081
	addl	%edi,%ebx
L_7_1081:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1082
	.align	2,0x90
L_7_1062:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_7_1082:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7015
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7045:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7015:
	ret

FUNC(op_4a7b)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7046:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_1123
	movswl	%di,%edi
L_7_1123:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1124
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1125
	movl	%ebp,%ebx
L_7_1125:
	testl	$64,%esi
	je	L_7_1126
	movl	%ebp,%edi
L_7_1126:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1127
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7047:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1127:
	cmpl	$48,%edx
	jne	L_7_1130
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7048:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1130:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1133
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7049:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1133:
	cmpl	$3,16-16(%esp)
	jne	L_7_1136
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7050:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1136:
	andl	$4,%esi
	jne	L_7_1139
	addl	%edi,%ebx
L_7_1139:
	cmpl	$0,16-16(%esp)
	je	L_7_1140
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1140:
	testl	%esi,%esi
	je	L_7_1143
	addl	%edi,%ebx
L_7_1143:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1144
	.align	2,0x90
L_7_1124:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1144:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ecx,%ecx
	movw	(%eax),%cx
	rolw	$8,%cx
	movl	%ecx,%eax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7016
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7051:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7016:
	ret

FUNC(op_4ab0)

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
RR0_7052:
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
	jne	L_7_1200
	movswl	%di,%edi
L_7_1200:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1201
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1202
	movl	%ebp,%ebx
L_7_1202:
	testl	$64,%esi
	je	L_7_1203
	movl	%ebp,%edi
L_7_1203:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1204
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7053:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1204:
	cmpl	$48,%edx
	jne	L_7_1207
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7054:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1207:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1210
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7055:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1210:
	cmpl	$3,16-16(%esp)
	jne	L_7_1213
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7056:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1213:
	andl	$4,%esi
	jne	L_7_1216
	addl	%edi,%ebx
L_7_1216:
	cmpl	$0,16-16(%esp)
	je	L_7_1217
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1217:
	testl	%esi,%esi
	je	L_7_1220
	addl	%edi,%ebx
L_7_1220:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1221
	.align	2,0x90
L_7_1201:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_7_1221:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7017
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7057:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7017:
	ret

FUNC(op_4abb)

	subl	$12,%esp
	movl	GLOBL(regs)+88,%ecx
	movl	%ecx,%edx
	movl	%ecx,24-16(%esp)
	addl	$2,%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7058:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_1262
	movswl	%di,%edi
L_7_1262:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1263
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1264
	movl	%ebp,%ebx
L_7_1264:
	testl	$64,%esi
	je	L_7_1265
	movl	%ebp,%edi
L_7_1265:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1266
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7059:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1266:
	cmpl	$48,%edx
	jne	L_7_1269
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7060:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1269:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1272
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7061:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1272:
	cmpl	$3,16-16(%esp)
	jne	L_7_1275
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7062:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1275:
	andl	$4,%esi
	jne	L_7_1278
	addl	%edi,%ebx
L_7_1278:
	cmpl	$0,16-16(%esp)
	je	L_7_1279
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1279:
	testl	%esi,%esi
	je	L_7_1282
	addl	%edi,%ebx
L_7_1282:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1283
	.align	2,0x90
L_7_1263:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1283:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7018
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7063:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7018:
	ret

FUNC(op_4af0)

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
RR0_7064:
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
	jne	L_7_1335
	movswl	%di,%edi
L_7_1335:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1336
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1337
	movl	%ebp,%ebx
L_7_1337:
	testl	$64,%esi
	je	L_7_1338
	movl	%ebp,%edi
L_7_1338:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1339
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7065:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$6,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1339:
	cmpl	$48,%edx
	jne	L_7_1342
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7066:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1342:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1345
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7067:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1345:
	cmpl	$3,16-16(%esp)
	jne	L_7_1348
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7068:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1348:
	andl	$4,%esi
	jne	L_7_1351
	addl	%edi,%ebx
L_7_1351:
	cmpl	$0,16-16(%esp)
	je	L_7_1352
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1352:
	testl	%esi,%esi
	je	L_7_1355
	addl	%edi,%ebx
L_7_1355:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1356
	.align	2,0x90
L_7_1336:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%ebp,%eax
	addl	%edi,%eax
L_7_1356:
	movl	%eax,%edx
	shrl	$14,%edx
	movl	%eax,%ecx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	orb	$-128,%al
	movb	%al,(%ecx,%edx)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7019
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7069:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7019:
	ret

FUNC(op_4c30)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,32-16(%esp)
	movl	%ecx,24-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7012:
	rolw	$8,%ax
	movw	%ax,30-16(%esp)
	andl	$7,%edx
	movl	%ecx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_7070:
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
	jne	L_7_1433
	movswl	%di,%edi
L_7_1433:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1434
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1435
	movl	%ebp,%ebx
L_7_1435:
	testl	$64,%esi
	je	L_7_1436
	movl	%ebp,%edi
L_7_1436:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1437
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7071:
	rolw	$8,%ax
	movl	24-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1437:
	cmpl	$48,%edx
	jne	L_7_1440
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7072:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1440:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1443
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7073:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1443:
	cmpl	$3,16-16(%esp)
	jne	L_7_1446
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7074:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1446:
	andl	$4,%esi
	jne	L_7_1449
	addl	%edi,%ebx
L_7_1449:
	cmpl	$0,16-16(%esp)
	je	L_7_1450
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1450:
	testl	%esi,%esi
	je	L_7_1453
	addl	%edi,%ebx
L_7_1453:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1454
	.align	2,0x90
L_7_1434:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1454:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	30-16(%esp),%ax
	pushl	%eax
	pushl	%edx
	movl	40-16(%esp),%ecx
	pushl	%ecx
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7020
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7075:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7020:
	ret

FUNC(op_4c3b)

	subl	$16,%esp
	movl	%eax,28-16(%esp)
	movl	GLOBL(regs)+88,%ebp
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebp),%ax
RR2_7013:
	rolw	$8,%ax
	movw	%ax,26-16(%esp)
	leal	4(%ebp),%edx
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7076:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_1502
	movswl	%di,%edi
L_7_1502:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1503
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1504
	movl	16-16(%esp),%ebx
L_7_1504:
	testl	$64,%esi
	je	L_7_1505
	movl	16-16(%esp),%edi
L_7_1505:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1506
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7077:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_7_1506:
	cmpl	$48,%edx
	jne	L_7_1509
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7078:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1509:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_7_1512
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7079:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_7_1512:
	cmpl	$3,%ebp
	jne	L_7_1515
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7080:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_7_1515:
	andl	$4,%esi
	jne	L_7_1518
	addl	%edi,%ebx
L_7_1518:
	testl	%ebp,%ebp
	je	L_7_1519
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1519:
	testl	%esi,%esi
	je	L_7_1522
	addl	%edi,%ebx
L_7_1522:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_7_1523
	.align	2,0x90
L_7_1503:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1523:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	26-16(%esp),%ax
	pushl	%eax
	pushl	%edx
	movl	36-16(%esp),%ecx
	pushl	%ecx
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7021
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7081:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7021:
	ret

FUNC(op_4c70)

	subl	$24,%esp
	movl	%eax,36-16(%esp)
	movl	GLOBL(regs)+88,%ecx
	movl	%eax,%edx
	movl	%ecx,%eax
	andl	$7,%edx
	addl	$2,%eax
	movl	%ecx,32-16(%esp)
	movl	%eax,GLOBL(regs)+88
	movl	%eax,28-16(%esp)
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7082:
	rolw	$8,%ax
	movw	%ax,26-16(%esp)
	addl	$8,%edx
	movl	32-16(%esp),%eax
	movl	32-16(%esp),%ecx
	addl	$4,%eax
	addl	$6,%ecx
	movl	%eax,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%eax),%si
RR0_7083:
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
	jne	L_7_1599
	movswl	%di,%edi
L_7_1599:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1600
	xorl	%ebp,%ebp
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1601
	movl	%ebp,%ebx
L_7_1601:
	testl	$64,%esi
	je	L_7_1602
	movl	%ebp,%edi
L_7_1602:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1603
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7084:
	rolw	$8,%ax
	movl	32-16(%esp),%ecx
	cwtl
	addl	$8,%ecx
	addl	%eax,%ebx
	movl	%ecx,GLOBL(regs)+88
L_7_1603:
	cmpl	$48,%edx
	jne	L_7_1606
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7085:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1606:
	movl	%esi,%ecx
	andl	$3,%ecx
	movl	%ecx,16-16(%esp)
	cmpl	$2,%ecx
	jne	L_7_1609
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7086:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1609:
	cmpl	$3,16-16(%esp)
	jne	L_7_1612
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7087:
	bswapl	%edx
	addl	$4,%eax
	movl	%edx,%ebp
	movl	%eax,GLOBL(regs)+88
L_7_1612:
	andl	$4,%esi
	jne	L_7_1615
	addl	%edi,%ebx
L_7_1615:
	cmpl	$0,16-16(%esp)
	je	L_7_1616
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1616:
	testl	%esi,%esi
	je	L_7_1619
	addl	%edi,%ebx
L_7_1619:
	leal	(%ebp,%ebx),%eax
	jmp	L_7_1620
	.align	2,0x90
L_7_1600:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1620:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%ecx
	movl	(%eax),%edx
	bswapl	%edx
	pushl	%ecx
	xorl	%eax,%eax
	movw	30-16(%esp),%ax
	pushl	%eax
	pushl	%edx
	movl	48-16(%esp),%ecx
	pushl	%ecx
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	addl	$24,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7022
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7088:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7022:
	ret

FUNC(op_4c7b)

	subl	$20,%esp
	movl	%eax,32-16(%esp)
	movl	GLOBL(regs)+88,%ebp
	leal	2(%ebp),%eax
	leal	4(%ebp),%edx
	movl	%eax,GLOBL(regs)+88
	movl	%eax,28-16(%esp)
	movl	%eax,%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7089:
	rolw	$8,%ax
	movw	%ax,26-16(%esp)
	leal	6(%ebp),%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%esi,%esi
	movw	0x2164334A(%edx),%si
RR0_7090:
	rolw	$8,%si
	movl	%esi,%eax
	movl	%ecx,20-16(%esp)
	shrl	$10,%eax
	movl	%ecx,GLOBL(regs)+88
	andl	$60,%eax
	movl	%edx,%ebx
	movl	GLOBL(regs)(%eax),%edi
	testl	$2048,%esi
	jne	L_7_1675
	movswl	%di,%edi
L_7_1675:
	movl	%esi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,%edi
	testl	$256,%esi
	je	L_7_1676
	movl	$0,16-16(%esp)
	movl	%esi,%ecx
	testb	%cl,%cl
	jge	L_7_1677
	movl	16-16(%esp),%ebx
L_7_1677:
	testl	$64,%esi
	je	L_7_1678
	movl	16-16(%esp),%edi
L_7_1678:
	movl	%esi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1679
	movl	20-16(%esp),%ecx
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7091:
	rolw	$8,%ax
	addl	$8,%ebp
	cwtl
	movl	%ebp,GLOBL(regs)+88
	addl	%eax,%ebx
L_7_1679:
	cmpl	$48,%edx
	jne	L_7_1682
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7092:
	bswapl	%edx
	addl	$4,%eax
	addl	%edx,%ebx
	movl	%eax,GLOBL(regs)+88
L_7_1682:
	movl	%esi,%ebp
	andl	$3,%ebp
	cmpl	$2,%ebp
	jne	L_7_1685
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7093:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_7_1685:
	cmpl	$3,%ebp
	jne	L_7_1688
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7094:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,16-16(%esp)
L_7_1688:
	andl	$4,%esi
	jne	L_7_1691
	addl	%edi,%ebx
L_7_1691:
	testl	%ebp,%ebp
	je	L_7_1692
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ebx
	bswapl	%ebx
L_7_1692:
	testl	%esi,%esi
	je	L_7_1695
	addl	%edi,%ebx
L_7_1695:
	movl	16-16(%esp),%ecx
	leal	(%ecx,%ebx),%eax
	jmp	L_7_1696
	.align	2,0x90
L_7_1676:
	movl	%esi,%ecx
	movsbl	%cl,%eax
	addl	%edx,%eax
	addl	%edi,%eax
L_7_1696:
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	28-16(%esp),%ecx
	movl	(%eax),%edx
	bswapl	%edx
	pushl	%ecx
	xorl	%eax,%eax
	movw	30-16(%esp),%ax
	pushl	%eax
	pushl	%edx
	movl	44-16(%esp),%ecx
	pushl	%ecx
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7023
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7095:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7023:
	ret

FUNC(op_4c90)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7014:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%ecx,%ecx
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	addl	$8,%edx
	movl	$GLOBL(regs),%eax
	movl	(%eax,%edx,4),%ebx
	testl	%ecx,%ecx
	je	L_7_1714
	movl	%eax,%ebp
	.align	2,0x90
L_7_1715:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1714
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1714
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1714
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_1715
L_7_1714:
	testl	%esi,%esi
	je	L_7_1726
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1721:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	2(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1726
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	4(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1726
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	6(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1726
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$8,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_1721
L_7_1726:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7024
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7096:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7024:
	ret

FUNC(op_4c98)

	subl	$4,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7015:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%ecx,%ecx
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	movl	16-16(%esp),%eax
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	movl	(%edx,%eax,4),%ebx
	testl	%ecx,%ecx
	je	L_7_1748
	movl	%edx,%ebp
	.align	2,0x90
L_7_1749:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1748
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1748
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1748
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_1749
L_7_1748:
	testl	%esi,%esi
	je	L_7_1760
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1755:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1760
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1760
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1760
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_1755
L_7_1760:
	movl	16-16(%esp),%eax
	addl	$8,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7025
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7097:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7025:
	ret

FUNC(op_4ca8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7016:
	rolw	$8,%ax
	xorl	%ebx,%ebx
	movb	%al,%bl
	shrw	$8,%ax
	xorl	%edi,%edi
	movw	%ax,%di
	addl	$8,%edx
	movl	%edi,16-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7006:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%edx,4),%esi
	addl	%eax,%esi
	testl	%ebx,%ebx
	je	L_7_1783
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_1784:
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebx,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_1783
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebx,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_1783
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebx,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_1783
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebx,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	jne	L_7_1784
L_7_1783:
	cmpl	$0,16-16(%esp)
	je	L_7_1795
	movl	$GLOBL(regs),%ebp
	movl	$GLOBL(movem_next),%ebx
	.align	2,0x90
L_7_1790:
	movl	%esi,%edx
	movl	%esi,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	16-16(%esp),%edi
	leal	0(,%edi,4),%ecx
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	movl	(%ecx,%ebx),%ecx
	leal	2(%esi),%eax
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_1795
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	movl	(%ecx,%ebx),%ecx
	leal	4(%esi),%eax
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_1795
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	movl	(%ecx,%ebx),%ecx
	leal	6(%esi),%eax
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_1795
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	movl	(%ecx,%ebx),%ecx
	addl	$8,%esi
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	jne	L_7_1790
L_7_1795:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7026
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7098:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7026:
	ret

FUNC(op_4cb0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ebx
	andl	$7,%edx
	movl	%ebx,32-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7017:
	rolw	$8,%ax
	movl	%eax,%esi
	shrw	$8,%ax
	xorl	%ebp,%ebp
	movw	%ax,%bp
	movl	%ebx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%edi,%edi
	movw	0x2164334A(%eax),%di
RR0_7099:
	rolw	$8,%di
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%ebx,28-16(%esp)
	movl	%edi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	andl	$255,%esi
	movl	%eax,24-16(%esp)
	testl	$2048,%edi
	jne	L_7_1818
	movswl	24-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_1818:
	movl	%edi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,24-16(%esp)
	testl	$256,%edi
	je	L_7_1819
	movl	$0,20-16(%esp)
	movl	%edi,%ebx
	testb	%bl,%bl
	jge	L_7_1820
	movl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
L_7_1820:
	testl	$64,%edi
	je	L_7_1821
	movl	20-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_1821:
	movl	%edi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1822
	movl	28-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7100:
	rolw	$8,%ax
	movl	32-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_7_1822:
	cmpl	$48,%edx
	jne	L_7_1825
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7101:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_7_1825:
	movl	%edi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_7_1828
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7102:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_1828:
	cmpl	$3,%ecx
	jne	L_7_1831
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7103:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_1831:
	andl	$4,%edi
	jne	L_7_1834
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_1834:
	testl	%ecx,%ecx
	je	L_7_1835
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_7_1835:
	testl	%edi,%edi
	je	L_7_1838
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_1838:
	movl	16-16(%esp),%ebx
	addl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
	jmp	L_7_1839
	.align	2,0x90
L_7_1819:
	movl	%edi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	24-16(%esp),%eax
	movl	%eax,16-16(%esp)
L_7_1839:
	testl	%esi,%esi
	je	L_7_1854
	movl	$GLOBL(movem_next),%edi
	.align	2,0x90
L_7_1843:
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_1854
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_1854
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_1854
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	jne	L_7_1843
L_7_1854:
	testl	%ebp,%ebp
	je	L_7_1855
	movl	$GLOBL(regs),%edi
	movl	$GLOBL(movem_next),%esi
	.align	2,0x90
L_7_1849:
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$2,%eax
	testl	%ebp,%ebp
	je	L_7_1855
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$4,%eax
	testl	%ebp,%ebp
	je	L_7_1855
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$6,%eax
	testl	%ebp,%ebp
	je	L_7_1855
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	addl	$8,16-16(%esp)
	movl	(%ecx,%esi),%ebp
	testl	%ebp,%ebp
	jne	L_7_1849
L_7_1855:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7027
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7104:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7027:
	ret

FUNC(op_4cb8)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7018:
	rolw	$8,%ax
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7007:
	rolw	$8,%ax
	movswl	%ax,%ebx
	testl	%ecx,%ecx
	je	L_7_1878
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1879:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1878
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1878
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1878
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_1879
L_7_1878:
	testl	%esi,%esi
	je	L_7_1890
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1885:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	2(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1890
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	4(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1890
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	6(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1890
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$8,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_1885
L_7_1890:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7028
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7105:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7028:
	ret

FUNC(op_4cb9)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7019:
	rolw	$8,%ax
	movb	%al,%cl
	xorl	%esi,%esi
	shrw	$8,%ax
	movl	0x2164334A+4(%edx),%ebx
RR4_7008:
	bswapl	%ebx
	movw	%ax,%si
	testl	%ecx,%ecx
	je	L_7_1925
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1914:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1925
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1925
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1925
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_1914
L_7_1925:
	testl	%esi,%esi
	je	L_7_1926
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1920:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	2(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1926
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	4(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1926
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	6(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1926
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$8,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_1920
L_7_1926:
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7029
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7106:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7029:
	ret

FUNC(op_4cba)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7020:
	rolw	$8,%ax
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7009:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%ebx
	testl	%ecx,%ecx
	je	L_7_1950
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1951:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1950
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1950
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_1950
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	sall	$2,%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	cwtl
	leal	0(,%edi,4),%edx
	movl	%eax,(%edx,%ebp)
	addl	$2,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_1951
L_7_1950:
	testl	%esi,%esi
	je	L_7_1962
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_1957:
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	2(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1962
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	4(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1962
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	leal	6(%ebx),%eax
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_1962
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%ebp,%edx,4)
	addl	$8,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_1957
L_7_1962:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7030
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7107:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7030:
	ret

FUNC(op_4cbb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebx
	xorl	%ebp,%ebp
	movl	%ebx,32-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7021:
	rolw	$8,%ax
	movl	%eax,%esi
	shrw	$8,%ax
	movl	%ebx,%edx
	movw	%ax,%bp
	addl	$4,%edx
	addl	$6,%ebx
	movl	%edx,GLOBL(regs)+88
	xorl	%edi,%edi
	movw	0x2164334A(%edx),%di
RR0_7108:
	rolw	$8,%di
	movl	%ebx,28-16(%esp)
	movl	%edi,%eax
	movl	%edx,16-16(%esp)
	shrl	$10,%eax
	movl	%ebx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	andl	$255,%esi
	movl	%eax,24-16(%esp)
	testl	$2048,%edi
	jne	L_7_1986
	movswl	24-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_1986:
	movl	%edi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,24-16(%esp)
	testl	$256,%edi
	je	L_7_1987
	movl	$0,20-16(%esp)
	movl	%edi,%ebx
	testb	%bl,%bl
	jge	L_7_1988
	movl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
L_7_1988:
	testl	$64,%edi
	je	L_7_1989
	movl	20-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_1989:
	movl	%edi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_1990
	movl	28-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7109:
	rolw	$8,%ax
	movl	32-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_7_1990:
	cmpl	$48,%edx
	jne	L_7_1993
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7110:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_7_1993:
	movl	%edi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_7_1996
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7111:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_1996:
	cmpl	$3,%ecx
	jne	L_7_1999
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7112:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_1999:
	andl	$4,%edi
	jne	L_7_2002
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2002:
	testl	%ecx,%ecx
	je	L_7_2003
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_7_2003:
	testl	%edi,%edi
	je	L_7_2006
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2006:
	movl	16-16(%esp),%ebx
	addl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
	jmp	L_7_2007
	.align	2,0x90
L_7_1987:
	movl	%edi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	24-16(%esp),%eax
	movl	%eax,16-16(%esp)
L_7_2007:
	testl	%esi,%esi
	je	L_7_2022
	movl	$GLOBL(movem_next),%edi
	.align	2,0x90
L_7_2011:
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2022
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2022
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2022
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	cwtl
	leal	0(,%ebx,4),%edx
	movl	%eax,GLOBL(regs)(%edx)
	addl	$2,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	jne	L_7_2011
L_7_2022:
	testl	%ebp,%ebp
	je	L_7_2023
	movl	$GLOBL(regs),%edi
	movl	$GLOBL(movem_next),%esi
	.align	2,0x90
L_7_2017:
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$2,%eax
	testl	%ebp,%ebp
	je	L_7_2023
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$4,%eax
	testl	%ebp,%ebp
	je	L_7_2023
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	movl	16-16(%esp),%eax
	movl	(%ecx,%esi),%ebp
	addl	$6,%eax
	testl	%ebp,%ebp
	je	L_7_2023
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	movl	GLOBL(movem_index1)(%ecx),%edx
	cwtl
	addl	$8,%edx
	movl	%eax,(%edi,%edx,4)
	addl	$8,16-16(%esp)
	movl	(%ecx,%esi),%ebp
	testl	%ebp,%ebp
	jne	L_7_2017
L_7_2023:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7031
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7113:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7031:
	ret

FUNC(op_4cd0)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7022:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%ecx,%ecx
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	addl	$8,%edx
	movl	$GLOBL(regs),%eax
	movl	(%eax,%edx,4),%ebx
	testl	%ecx,%ecx
	je	L_7_2045
	movl	%eax,%ebp
	.align	2,0x90
L_7_2046:
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2045
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2045
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2045
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_2046
L_7_2045:
	testl	%esi,%esi
	je	L_7_2057
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2052:
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	4(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2057
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	8(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2057
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	12(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2057
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$16,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_2052
L_7_2057:
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7032
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7114:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7032:
	ret

FUNC(op_4cd8)

	subl	$4,%esp
	andl	$7,%eax
	movl	%eax,16-16(%esp)
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7023:
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%ecx,%ecx
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	movl	16-16(%esp),%eax
	movl	$GLOBL(regs),%edx
	addl	$8,%eax
	movl	(%edx,%eax,4),%ebx
	testl	%ecx,%ecx
	je	L_7_2079
	movl	%edx,%ebp
	.align	2,0x90
L_7_2080:
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2079
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2079
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2079
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_2080
L_7_2079:
	testl	%esi,%esi
	je	L_7_2091
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2086:
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2091
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2091
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2091
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_2086
L_7_2091:
	movl	16-16(%esp),%eax
	addl	$8,%eax
	movl	%ebx,GLOBL(regs)(,%eax,4)
	addl	$4,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7033
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7115:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7033:
	ret

FUNC(op_4ce8)

	subl	$4,%esp
	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7024:
	rolw	$8,%ax
	xorl	%ebx,%ebx
	movb	%al,%bl
	shrw	$8,%ax
	xorl	%edi,%edi
	movw	%ax,%di
	addl	$8,%edx
	movl	%edi,16-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7010:
	rolw	$8,%ax
	movl	$GLOBL(regs),%ecx
	cwtl
	movl	(%ecx,%edx,4),%esi
	addl	%eax,%esi
	testl	%ebx,%ebx
	je	L_7_2114
	movl	$GLOBL(movem_next),%ebp
	.align	2,0x90
L_7_2115:
	movl	%esi,%eax
	movl	%esi,%edx
	leal	0(,%ebx,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_2114
	movl	%esi,%eax
	movl	%esi,%edx
	leal	0(,%ebx,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_2114
	movl	%esi,%eax
	movl	%esi,%edx
	leal	0(,%ebx,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	je	L_7_2114
	movl	%esi,%eax
	movl	%esi,%edx
	leal	0(,%ebx,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,%esi
	movl	(%ecx,%ebp),%ebx
	testl	%ebx,%ebx
	jne	L_7_2115
L_7_2114:
	cmpl	$0,16-16(%esp)
	je	L_7_2126
	movl	$GLOBL(regs),%ebp
	movl	$GLOBL(movem_next),%ebx
	.align	2,0x90
L_7_2121:
	movl	%esi,%eax
	movl	%esi,%edx
	movl	16-16(%esp),%edi
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%edi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	movl	(%ecx,%ebx),%ecx
	leal	4(%esi),%edx
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_2126
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	sall	$2,%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	movl	(%ecx,%ebx),%ecx
	leal	8(%esi),%edx
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_2126
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	sall	$2,%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	movl	(%ecx,%ebx),%ecx
	leal	12(%esi),%edx
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	je	L_7_2126
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	sall	$2,%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	movl	(%ecx,%ebx),%ecx
	addl	$16,%esi
	movl	%ecx,16-16(%esp)
	testl	%ecx,%ecx
	jne	L_7_2121
L_7_2126:
	addl	$6,GLOBL(regs)+88
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7034
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7116:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7034:
	ret

FUNC(op_4cf0)

	subl	$20,%esp
	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ebx
	andl	$7,%edx
	movl	%ebx,32-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7025:
	rolw	$8,%ax
	movl	%eax,%esi
	shrw	$8,%ax
	xorl	%ebp,%ebp
	movw	%ax,%bp
	movl	%ebx,%eax
	addl	$8,%edx
	addl	$4,%eax
	addl	$6,%ebx
	movl	%eax,GLOBL(regs)+88
	xorl	%edi,%edi
	movw	0x2164334A(%eax),%di
RR0_7117:
	rolw	$8,%di
	movl	GLOBL(regs)(,%edx,4),%edx
	movl	%ebx,28-16(%esp)
	movl	%edi,%eax
	movl	%ebx,GLOBL(regs)+88
	shrl	$10,%eax
	movl	%edx,16-16(%esp)
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	andl	$255,%esi
	movl	%eax,24-16(%esp)
	testl	$2048,%edi
	jne	L_7_2149
	movswl	24-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_2149:
	movl	%edi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,24-16(%esp)
	testl	$256,%edi
	je	L_7_2150
	movl	$0,20-16(%esp)
	movl	%edi,%ebx
	testb	%bl,%bl
	jge	L_7_2151
	movl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
L_7_2151:
	testl	$64,%edi
	je	L_7_2152
	movl	20-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_2152:
	movl	%edi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_2153
	movl	28-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7118:
	rolw	$8,%ax
	movl	32-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_7_2153:
	cmpl	$48,%edx
	jne	L_7_2156
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7119:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_7_2156:
	movl	%edi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_7_2159
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7120:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_2159:
	cmpl	$3,%ecx
	jne	L_7_2162
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7121:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_2162:
	andl	$4,%edi
	jne	L_7_2165
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2165:
	testl	%ecx,%ecx
	je	L_7_2166
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_7_2166:
	testl	%edi,%edi
	je	L_7_2169
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2169:
	movl	16-16(%esp),%ebx
	addl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
	jmp	L_7_2170
	.align	2,0x90
L_7_2150:
	movl	%edi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	24-16(%esp),%eax
	movl	%eax,16-16(%esp)
L_7_2170:
	testl	%esi,%esi
	je	L_7_2185
	movl	$GLOBL(movem_next),%edi
	.align	2,0x90
L_7_2174:
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2185
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2185
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2185
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	jne	L_7_2174
L_7_2185:
	testl	%ebp,%ebp
	je	L_7_2186
	movl	$GLOBL(regs),%edi
	movl	$GLOBL(movem_next),%esi
	.align	2,0x90
L_7_2180:
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$4,%edx
	testl	%ebp,%ebp
	je	L_7_2186
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$8,%edx
	testl	%ebp,%ebp
	je	L_7_2186
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$12,%edx
	testl	%ebp,%ebp
	je	L_7_2186
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	addl	$16,16-16(%esp)
	movl	(%ecx,%esi),%ebp
	testl	%ebp,%ebp
	jne	L_7_2180
L_7_2186:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7035
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7122:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7035:
	ret

FUNC(op_4cf8)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7026:
	rolw	$8,%ax
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7011:
	rolw	$8,%ax
	movswl	%ax,%ebx
	testl	%ecx,%ecx
	je	L_7_2209
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2210:
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2209
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2209
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2209
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_2210
L_7_2209:
	testl	%esi,%esi
	je	L_7_2221
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2216:
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	4(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2221
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	8(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2221
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	12(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2221
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$16,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_2216
L_7_2221:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7036
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7123:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7036:
	ret

FUNC(op_4cf9)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7027:
	rolw	$8,%ax
	movb	%al,%cl
	xorl	%esi,%esi
	shrw	$8,%ax
	movl	0x2164334A+4(%edx),%ebx
RR4_7012:
	bswapl	%ebx
	movw	%ax,%si
	testl	%ecx,%ecx
	je	L_7_2256
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2245:
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2256
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2256
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2256
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_2245
L_7_2256:
	testl	%esi,%esi
	je	L_7_2257
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2251:
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	4(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2257
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	8(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2257
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	12(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2257
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$16,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_2251
L_7_2257:
	addl	$8,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7037
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7124:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7037:
	ret

FUNC(op_4cfa)

	xorl	%ecx,%ecx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7028:
	rolw	$8,%ax
	movb	%al,%cl
	shrw	$8,%ax
	xorl	%esi,%esi
	movw	%ax,%si
	xorl	%eax,%eax
	movw	0x2164334A+4(%edx),%ax
RR4_7013:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%edx),%ebx
	testl	%ecx,%ecx
	je	L_7_2281
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2282:
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2281
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2281
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	je	L_7_2281
	movl	%ebx,%eax
	movl	%ebx,%edx
	sall	$2,%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%edi
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%edi,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%eax,%ebp)
	addl	$4,%ebx
	movl	GLOBL(movem_next)(%ecx),%ecx
	testl	%ecx,%ecx
	jne	L_7_2282
L_7_2281:
	testl	%esi,%esi
	je	L_7_2293
	movl	$GLOBL(regs),%ebp
	.align	2,0x90
L_7_2288:
	movl	%ebx,%eax
	movl	%ebx,%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	4(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2293
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	8(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2293
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	leal	12(%ebx),%edx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	je	L_7_2293
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%esi,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%ebp,%eax,4)
	addl	$16,%ebx
	movl	GLOBL(movem_next)(%ecx),%esi
	testl	%esi,%esi
	jne	L_7_2288
L_7_2293:
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7038
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7125:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7038:
	ret

FUNC(op_4cfb)

	subl	$20,%esp
	movl	GLOBL(regs)+88,%ebx
	xorl	%ebp,%ebp
	movl	%ebx,32-16(%esp)
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7029:
	rolw	$8,%ax
	movl	%eax,%esi
	shrw	$8,%ax
	movl	%ebx,%edx
	movw	%ax,%bp
	addl	$4,%edx
	addl	$6,%ebx
	movl	%edx,GLOBL(regs)+88
	xorl	%edi,%edi
	movw	0x2164334A(%edx),%di
RR0_7126:
	rolw	$8,%di
	movl	%ebx,28-16(%esp)
	movl	%edi,%eax
	movl	%edx,16-16(%esp)
	shrl	$10,%eax
	movl	%ebx,GLOBL(regs)+88
	andl	$60,%eax
	movl	GLOBL(regs)(%eax),%eax
	andl	$255,%esi
	movl	%eax,24-16(%esp)
	testl	$2048,%edi
	jne	L_7_2317
	movswl	24-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_2317:
	movl	%edi,%eax
	shrl	$9,%eax
	movl	%eax,%ecx
	andl	$3,%ecx
	sall	%cl,24-16(%esp)
	testl	$256,%edi
	je	L_7_2318
	movl	$0,20-16(%esp)
	movl	%edi,%ebx
	testb	%bl,%bl
	jge	L_7_2319
	movl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
L_7_2319:
	testl	$64,%edi
	je	L_7_2320
	movl	20-16(%esp),%ebx
	movl	%ebx,24-16(%esp)
L_7_2320:
	movl	%edi,%edx
	andl	$48,%edx
	cmpl	$32,%edx
	jne	L_7_2321
	movl	28-16(%esp),%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7127:
	rolw	$8,%ax
	movl	32-16(%esp),%ebx
	cwtl
	addl	$8,%ebx
	addl	%eax,16-16(%esp)
	movl	%ebx,GLOBL(regs)+88
L_7_2321:
	cmpl	$48,%edx
	jne	L_7_2324
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7128:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	addl	%edx,16-16(%esp)
L_7_2324:
	movl	%edi,%ecx
	andl	$3,%ecx
	cmpl	$2,%ecx
	jne	L_7_2327
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A(%eax),%dx
RR0_7129:
	rolw	$8,%dx
	addl	$2,%eax
	movswl	%dx,%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_2327:
	cmpl	$3,%ecx
	jne	L_7_2330
	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A(%eax),%edx
RR0_7130:
	addl	$4,%eax
	bswapl	%edx
	movl	%eax,GLOBL(regs)+88
	movl	%edx,20-16(%esp)
L_7_2330:
	andl	$4,%edi
	jne	L_7_2333
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2333:
	testl	%ecx,%ecx
	je	L_7_2334
	movl	16-16(%esp),%edx
	movl	16-16(%esp),%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%eax,16-16(%esp)
L_7_2334:
	testl	%edi,%edi
	je	L_7_2337
	movl	24-16(%esp),%ebx
	addl	%ebx,16-16(%esp)
L_7_2337:
	movl	16-16(%esp),%ebx
	addl	20-16(%esp),%ebx
	movl	%ebx,16-16(%esp)
	jmp	L_7_2338
	.align	2,0x90
L_7_2318:
	movl	%edi,%ebx
	movsbl	%bl,%eax
	addl	%edx,%eax
	addl	24-16(%esp),%eax
	movl	%eax,16-16(%esp)
L_7_2338:
	testl	%esi,%esi
	je	L_7_2353
	movl	$GLOBL(movem_next),%edi
	.align	2,0x90
L_7_2342:
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2353
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2353
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	je	L_7_2353
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	leal	0(,%esi,4),%ecx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	movl	GLOBL(movem_index1)(%ecx),%ebx
	addl	GLOBL(R24)(%eax),%edx
	leal	0(,%ebx,4),%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,GLOBL(regs)(%eax)
	addl	$4,16-16(%esp)
	movl	(%ecx,%edi),%esi
	testl	%esi,%esi
	jne	L_7_2342
L_7_2353:
	testl	%ebp,%ebp
	je	L_7_2354
	movl	$GLOBL(regs),%edi
	movl	$GLOBL(movem_next),%esi
	.align	2,0x90
L_7_2348:
	movl	16-16(%esp),%eax
	movl	16-16(%esp),%edx
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$4,%edx
	testl	%ebp,%ebp
	je	L_7_2354
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$8,%edx
	testl	%ebp,%ebp
	je	L_7_2354
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	movl	16-16(%esp),%edx
	movl	(%ecx,%esi),%ebp
	addl	$12,%edx
	testl	%ebp,%ebp
	je	L_7_2354
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$65535,%edx
	andl	$1020,%eax
	leal	0(,%ebp,4),%ecx
	addl	GLOBL(R24)(%eax),%edx
	movl	GLOBL(movem_index1)(%ecx),%eax
	addl	$8,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%edx,(%edi,%eax,4)
	addl	$16,16-16(%esp)
	movl	(%ecx,%esi),%ebp
	testl	%ebp,%ebp
	jne	L_7_2348
L_7_2354:
	addl	$20,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7039
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7131:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7039:
	ret

FUNC(op_4e73)

	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2430
	pushl	$0
	pushl	$8
	jmp	L_7_2459
	.align	2,0x90
L_7_2454:
	addl	$12,%ebx
	movl	%ebx,GLOBL(regs)+60
	jmp	L_7_2431
	.align	2,0x90
L_7_2455:
	addl	$58,%ebx
	movl	%ebx,GLOBL(regs)+60
	jmp	L_7_2431
	.align	2,0x90
L_7_2456:
	addl	$20,%ebx
	movl	%ebx,GLOBL(regs)+60
	jmp	L_7_2431
	.align	2,0x90
L_7_2457:
	addl	$32,%ebx
	movl	%ebx,GLOBL(regs)+60
	jmp	L_7_2431
	.align	2,0x90
L_7_2458:
	addl	$92,%ebx
	movl	%ebx,GLOBL(regs)+60
	jmp	L_7_2431
	.align	2,0x90
	.align	2,0x90
L_7_2430:
	movl	GLOBL(regs)+60,%ebx
	xorl	%edx,%edx
	movl	%ebx,%eax
	movb	GLOBL(regs)+62,%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	xorl	%esi,%esi
	movw	%ax,%si
	leal	2(%ebx),%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%ecx
	bswapl	%ecx
	leal	6(%ebx),%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	movl	%ecx,%ebp
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	leal	8(%ebx),%edi
	movl	%esi,%edx
	movl	%edi,GLOBL(regs)+60
	testb	$240,%ah
	je	L_7_2431
	andl	$61440,%eax
	cmpl	$4096,%eax
	je	L_7_2440
	cmpl	$8192,%eax
	je	L_7_2454
	cmpl	$32768,%eax
	je	L_7_2455
	cmpl	$36864,%eax
	je	L_7_2456
	cmpl	$40960,%eax
	je	L_7_2457
	cmpl	$45056,%eax
	je	L_7_2458
	pushl	$0
	pushl	$14
L_7_2459:
	call	GLOBL(Exception)
	addl	$8,%esp
	jmp	L_7_2429
	.align	2,0x90
L_7_2440:
	movw	%si,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	jmp	L_7_2430
	.align	2,0x90
L_7_2431:
	movw	%dx,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	movl	%ebp,GLOBL(regs)+88
L_7_2429:
	popl	%eax
	decl	%eax
	jl	JJ_7040
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7132:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7040:
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


FUNC(op_4879)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_7030:
	bswapl	%ecx
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
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7041
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7133:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7041:
	ret

FUNC(op_487a)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7031:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%ecx
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
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7042
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7134:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7042:
	ret

FUNC(op_4880)

	movl	%eax,%edx
	andl	$7,%edx
	movl	$GLOBL(regs),%ecx
	sall	$2,%edx
	movl	(%edx,%ecx),%eax
	cbtw
	testw	%ax,%ax
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movw	%ax,(%edx,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7043
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7135:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7043:
	ret

FUNC(op_48c0)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movswl	(%eax,%ecx),%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%edx,(%eax,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7044
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7136:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7044:
	ret

FUNC(op_49c0)

	andl	$7,%eax
	movl	$GLOBL(regs),%ecx
	sall	$2,%eax
	movsbl	(%eax,%ecx),%edx
	testl	%edx,%edx
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	%edx,(%eax,%ecx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7045
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7137:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7045:
	ret

FUNC(op_4a00)

	andl	$7,%eax
	movb	GLOBL(regs)(,%eax,4),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7046
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7138:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7046:
	ret

FUNC(op_4a10)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	movl	GLOBL(R24)(,%edx,4),%eax
	movb	(%ecx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7047
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7139:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7047:
	ret

FUNC(op_4a18)

	movl	%eax,%edi
	pushl	%esi
	andl	$7,%edi
	pushl	%ebx
	leal	8(%edi),%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	xorl	%eax,%eax
	movl	(%ecx,%esi),%edx
	movb	2(%ecx,%esi),%al
	movl	%edx,%ebx
	movl	GLOBL(R24)(,%eax,4),%eax
	andl	$65535,%ebx
	addl	GLOBL(areg_byteinc)(,%edi,4),%edx
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7048
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7140:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7048:
	ret

FUNC(op_4a20)

	andl	$7,%eax
	pushl	%ebx
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
	movb	(%ebx,%eax),%al
	movl	%edx,(%ecx,%esi)
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7049
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7141:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7049:
	ret

FUNC(op_4a28)

	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7032:
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
	testb	%dl,%dl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7050
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7142:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7050:
	ret

FUNC(op_4a38)

	movl	GLOBL(regs)+88,%ecx
	xorl	%edx,%edx
	movw	0x2164334A+2(%ecx),%dx
RR2_7033:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7051
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7143:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7051:
	ret

FUNC(op_4a39)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%edx
RR2_7034:
	bswapl	%edx
	movl	%edx,%eax
	shrl	$14,%eax
	andl	$1020,%eax
	andl	$65535,%edx
	movl	GLOBL(R24)(%eax),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7052
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7144:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7052:
	ret

FUNC(op_4a3a)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7035:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%eax
	movl	GLOBL(R24)(%edx),%edx
	movb	(%eax,%edx),%dl
	testb	%dl,%dl
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7053
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7145:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7053:
	ret

FUNC(op_4a3c)

	movl	GLOBL(regs)+88,%eax
	movb	0x2164334A+3(%eax),%cl
RR3_7000:
	testb	%cl,%cl
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	$4,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7054
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7146:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7054:
	ret

FUNC(op_4a40)

	andl	$7,%eax
	movw	GLOBL(regs)(,%eax,4),%ax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7055
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7147:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7055:
	ret

FUNC(op_4a48)

	andl	$7,%eax
	addl	$8,%eax
	movw	GLOBL(regs)(,%eax,4),%ax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7056
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7148:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7056:
	ret

FUNC(op_4a50)

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
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7057
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7149:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7057:
	ret

FUNC(op_4a58)

	movl	%eax,%ecx
	pushl	%esi
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
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
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7058
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7150:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7058:
	ret

FUNC(op_4a60)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%esi
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	pushl	%ebx
	sall	$2,%ecx
	movl	(%ecx,%esi),%ebx
	addl	$-2,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%edi,%edi
	movw	(%eax),%di
	rolw	$8,%di
	movl	%edi,%eax
	movl	%ebx,(%ecx,%esi)
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	popl	%esi
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7059
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7151:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7059:
	ret

FUNC(op_4a68)

	movl	%eax,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7036:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7060
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7152:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7060:
	ret

FUNC(op_4a78)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7037:
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
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7061
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7153:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7061:
	ret

FUNC(op_4a79)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%eax
RR2_7038:
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
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7062
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7154:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7062:
	ret

FUNC(op_4a7a)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7039:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	xorl	%ebx,%ebx
	movw	(%eax),%bx
	rolw	$8,%bx
	movl	%ebx,%eax
	testw	%ax,%ax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7063
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7155:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7063:
	ret

FUNC(op_4a7c)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7040:
	rolw	$8,%dx
	testw	%dx,%dx
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	$4,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7064
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7156:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7064:
	ret

FUNC(op_4a80)

	andl	$7,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7065
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7157:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7065:
	ret

FUNC(op_4a88)

	andl	$7,%eax
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7066
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7158:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7066:
	ret

FUNC(op_4a90)

	andl	$7,%eax
	addl	$8,%eax
	xorl	%edx,%edx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%ax
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7067
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7159:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7067:
	ret

FUNC(op_4a98)

	movl	%eax,%ecx
	andl	$7,%ecx
	pushl	%ebx
	addl	$8,%ecx
	movl	$GLOBL(regs),%esi
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%edx,(%ecx,%esi)
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7068
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7160:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7068:
	ret

FUNC(op_4aa0)

	movl	%eax,%ecx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	addl	$8,%ecx
	pushl	%ebx
	sall	$2,%ecx
	movl	(%ecx,%esi),%ebx
	addl	$-4,%ebx
	movl	%ebx,%edx
	movl	%ebx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,(%ecx,%esi)
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	popl	%ebx
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7069
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7161:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7069:
	ret

FUNC(op_4aa8)

	movl	%eax,%edx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7041:
	rolw	$8,%ax
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7070
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7162:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7070:
	ret

FUNC(op_4ab8)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7042:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7071
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7163:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7071:
	ret

FUNC(op_4ab9)

	movl	GLOBL(regs)+88,%ecx
	movl	0x2164334A+2(%ecx),%eax
RR2_7043:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$6,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7072
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7164:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7072:
	ret

FUNC(op_4aba)

	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7044:
	rolw	$8,%ax
	cwtl
	leal	2(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%eax
	bswapl	%eax
	testl	%eax,%eax
	pushfl
	popl	%eax
	movl	%eax,regflags

	addl	$4,%ecx
	movl	%ecx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7073
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7165:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7073:
	ret

FUNC(op_4abc)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%edx
RR2_7045:
	bswapl	%edx
	testl	%edx,%edx
	pushfl
	popl	%edx
	movl	%edx,regflags

	addl	$6,%eax
	movl	%eax,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7074
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7166:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7074:
	ret

FUNC(op_4ac0)

	movl	%eax,%ecx
	andl	$7,%ecx
	movl	$GLOBL(regs),%edx
	sall	$2,%ecx
	movb	(%ecx,%edx),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	orb	$-128,%al
	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7075
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7167:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7075:
	ret

FUNC(op_4ad0)

	andl	$7,%eax
	xorl	%edx,%edx
	addl	$8,%eax
	xorl	%ecx,%ecx
	movb	GLOBL(regs)+2(,%eax,4),%dl
	movw	GLOBL(regs)(,%eax,4),%cx
	sall	$2,%edx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	orb	$-128,%al
	movb	%al,(%ecx,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7076
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7168:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7076:
	ret

FUNC(op_4ad8)

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
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movl	GLOBL(W24)(%edx),%edx
	orb	$-128,%al
	movb	%al,(%esi,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7077
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7169:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7077:
	ret

FUNC(op_4ae0)

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
	testb	%al,%al
	pushfl
	popl	%ecx
	movl	%ecx,regflags

	movl	GLOBL(W24)(%edx),%edx
	orb	$-128,%al
	movb	%al,(%esi,%edx)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7078
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7170:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7078:
	ret

FUNC(op_4ae8)

	movl	%eax,%ecx
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7046:
	rolw	$8,%dx
	movswl	%dx,%edx
	addl	$8,%ecx
	addl	GLOBL(regs)(,%ecx,4),%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	orb	$-128,%al
	movb	%al,(%edx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7079
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7171:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7079:
	ret

FUNC(op_4af8)

	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7047:
	rolw	$8,%dx
	movswl	%dx,%edx
	movl	%edx,%ecx
	shrl	$14,%ecx
	andl	$1020,%ecx
	andl	$65535,%edx
	movl	GLOBL(R24)(%ecx),%eax
	movb	(%edx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%ecx),%ecx
	orb	$-128,%al
	movb	%al,(%edx,%ecx)
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7080
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7172:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7080:
	ret

FUNC(op_4af9)

	movl	GLOBL(regs)+88,%eax
	movl	0x2164334A+2(%eax),%ecx
RR2_7048:
	bswapl	%ecx
	movl	%ecx,%edx
	shrl	$14,%edx
	andl	$1020,%edx
	andl	$65535,%ecx
	movl	GLOBL(R24)(%edx),%eax
	movb	(%ecx,%eax),%al
	testb	%al,%al
	pushfl
	popl	%ebx
	movl	%ebx,regflags

	movl	GLOBL(W24)(%edx),%edx
	orb	$-128,%al
	movb	%al,(%ecx,%edx)
	addl	$6,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7081
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7173:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7081:
	ret

FUNC(op_4c00)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%edx
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7049:
	rolw	$8,%ax
	movl	%ebx,%ecx
	andl	$65535,%eax
	andl	$7,%ecx
	addl	$4,%edx
	movl	GLOBL(regs)(,%ecx,4),%ecx
	movl	%edx,GLOBL(regs)+88
	pushl	%eax
	pushl	%ecx
	pushl	%ebx
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7082
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7174:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7082:
	ret

FUNC(op_4c10)

	xorl	%ecx,%ecx
	movl	%eax,%edi
	movl	%edi,%edx
	andl	$7,%edx
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ebx),%ax
RR2_7050:
	rolw	$8,%ax
	movl	%eax,%esi
	addl	$8,%edx
	xorl	%eax,%eax
	movb	GLOBL(regs)+2(,%edx,4),%cl
	movw	GLOBL(regs)(,%edx,4),%ax
	addl	GLOBL(R24)(,%ecx,4),%eax
	addl	$4,%ebx
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	%si,%ax
	movl	%ebx,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%edi
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7083
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7175:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7083:
	ret

FUNC(op_4c18)

	subl	$4,%esp
	movl	%eax,%ebp
	movl	%ebp,%ecx
	andl	$7,%ecx
	movl	$GLOBL(regs),%esi
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7051:
	rolw	$8,%di
	movl	%edi,%eax
	addl	$8,%ecx
	movw	%ax,18-16(%esp)
	sall	$2,%ecx
	movl	(%ecx,%esi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%esi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	bswapl	%ebx
	movl	%edx,(%ecx,%esi)
	xorl	%eax,%eax
	movw	18-16(%esp),%ax
	addl	$4,GLOBL(regs)+88
	pushl	%eax
	pushl	%ebx
	pushl	%ebp
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7084
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7176:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7084:
	ret

FUNC(op_4c20)

	subl	$4,%esp
	movl	%eax,%ebp
	movl	$GLOBL(regs),%esi
	movl	%ebp,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edi,%edi
	movw	0x2164334A+2(%eax),%di
RR2_7052:
	rolw	$8,%di
	andl	$7,%ebx
	movl	%edi,%eax
	addl	$8,%ebx
	movw	%ax,18-16(%esp)
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	addl	$-4,%ecx
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ecx,(%ebx,%esi)
	xorl	%eax,%eax
	movw	18-16(%esp),%ax
	addl	$4,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%ebp
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7085
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7177:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7085:
	ret

FUNC(op_4c28)

	movl	%eax,%esi
	movl	%esi,%edx
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7053:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7014:
	rolw	$8,%ax
	andl	$7,%edx
	cwtl
	addl	$8,%edx
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ecx
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%ecx,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%esi
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7086
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7178:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7086:
	ret

FUNC(op_4c38)

	movl	%eax,%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7054:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7015:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ecx
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%ecx,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%esi
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7087
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7179:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7087:
	ret

FUNC(op_4c39)

	movl	%eax,%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7055:
	rolw	$8,%ax
	movl	%eax,%ebx
	movl	0x2164334A+4(%ecx),%eax
RR4_7016:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ecx
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%ecx,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%esi
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7088
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7180:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7088:
	ret

FUNC(op_4c3a)

	movl	%eax,%esi
	movl	GLOBL(regs)+88,%ecx
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7056:
	rolw	$8,%ax
	movl	%eax,%ebx
	xorl	%eax,%eax
	movw	0x2164334A+4(%ecx),%ax
RR4_7017:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ecx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ecx
	movl	(%eax),%edx
	bswapl	%edx
	xorl	%eax,%eax
	movw	%bx,%ax
	movl	%ecx,GLOBL(regs)+88
	pushl	%eax
	pushl	%edx
	pushl	%esi
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7089
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7181:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7089:
	ret

FUNC(op_4c3c)

	movl	%eax,%ebx
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7057:
	rolw	$8,%dx
	movl	0x2164334A+4(%eax),%ecx
RR4_7018:
	addl	$8,%eax
	movl	%eax,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%dx,%ax
	pushl	%eax
	bswapl	%ecx
	pushl	%ecx
	pushl	%ebx
	call	GLOBL(m68k_mull)
	addl	$12,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7090
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7182:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7090:
	ret

FUNC(op_4c40)

	movl	%eax,%esi
	movl	%esi,%ebx
	movl	GLOBL(regs)+88,%ecx
	andl	$7,%ebx
	leal	2(%ecx),%edx
	addl	$4,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%edx),%ax
RR0_7183:
	rolw	$8,%ax
	movl	GLOBL(regs)(,%ebx,4),%ebx
	movl	%ecx,GLOBL(regs)+88
	andl	$65535,%eax
	pushl	%edx
	pushl	%eax
	pushl	%ebx
	pushl	%esi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7091
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7184:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7091:
	ret

FUNC(op_4c50)

	xorl	%ecx,%ecx
	movl	%eax,%ebp
	movl	%ebp,%edx
	movl	GLOBL(regs)+88,%esi
	andl	$7,%edx
	leal	2(%esi),%ebx
	addl	$8,%edx
	movl	%ebx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7185:
	rolw	$8,%ax
	movl	%eax,%edi
	xorl	%eax,%eax
	movb	GLOBL(regs)+2(,%edx,4),%cl
	movw	GLOBL(regs)(,%edx,4),%ax
	addl	GLOBL(R24)(,%ecx,4),%eax
	addl	$4,%esi
	movl	(%eax),%edx
	bswapl	%edx
	movl	%esi,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%di,%ax
	pushl	%ebx
	pushl	%eax
	pushl	%edx
	pushl	%ebp
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7092
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7186:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7092:
	ret

FUNC(op_4c58)

	subl	$4,%esp
	movl	%eax,%ebp
	movl	%ebp,%ecx
	movl	$GLOBL(regs),%edi
	andl	$7,%ecx
	movl	GLOBL(regs)+88,%esi
	addl	$8,%ecx
	addl	$2,%esi
	sall	$2,%ecx
	movl	%esi,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%esi),%ax
RR0_7187:
	rolw	$8,%ax
	movw	%ax,18-16(%esp)
	movl	(%ecx,%edi),%edx
	xorl	%ebx,%ebx
	movl	%edx,%eax
	movb	2(%ecx,%edi),%bl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ebx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ebx
	movl	%edx,(%ecx,%edi)
	addl	$2,GLOBL(regs)+88
	bswapl	%ebx
	pushl	%esi
	xorl	%eax,%eax
	movw	22-16(%esp),%ax
	pushl	%eax
	pushl	%ebx
	pushl	%ebp
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7093
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7188:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7093:
	ret

FUNC(op_4c60)

	subl	$4,%esp
	movl	%eax,%ebp
	movl	$GLOBL(regs),%edi
	movl	GLOBL(regs)+88,%esi
	movl	%ebp,%ebx
	addl	$2,%esi
	andl	$7,%ebx
	movl	%esi,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%esi),%ax
RR0_7189:
	rolw	$8,%ax
	addl	$8,%ebx
	movw	%ax,18-16(%esp)
	sall	$2,%ebx
	movl	(%ebx,%edi),%ecx
	addl	$-4,%ecx
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	movl	(%eax),%edx
	movl	%ecx,(%ebx,%edi)
	addl	$2,GLOBL(regs)+88
	bswapl	%edx
	pushl	%esi
	xorl	%eax,%eax
	movw	22-16(%esp),%ax
	pushl	%eax
	pushl	%edx
	pushl	%ebp
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	addl	$4,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7094
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7190:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7094:
	ret

FUNC(op_4c68)

	movl	%eax,%edi
	movl	%edi,%edx
	movl	GLOBL(regs)+88,%ebx
	andl	$7,%edx
	leal	2(%ebx),%ecx
	addl	$8,%edx
	movl	%ecx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7191:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7058:
	rolw	$8,%ax
	cwtl
	addl	GLOBL(regs)(,%edx,4),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ebx
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ebx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%si,%ax
	pushl	%ecx
	pushl	%eax
	pushl	%edx
	pushl	%edi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7095
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7192:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7095:
	ret

FUNC(op_4c78)

	movl	GLOBL(regs)+88,%ebx
	leal	2(%ebx),%ecx
	movl	%eax,%edi
	movl	%ecx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7193:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7059:
	rolw	$8,%ax
	cwtl
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ebx
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ebx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%si,%ax
	pushl	%ecx
	pushl	%eax
	pushl	%edx
	pushl	%edi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7096
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7194:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7096:
	ret

FUNC(op_4c79)

	movl	GLOBL(regs)+88,%ebx
	leal	2(%ebx),%ecx
	movl	%eax,%edi
	movl	%ecx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7195:
	rolw	$8,%ax
	movl	%eax,%esi
	movl	0x2164334A+2(%ecx),%eax
RR2_7060:
	bswapl	%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$8,%ebx
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ebx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%si,%ax
	pushl	%ecx
	pushl	%eax
	pushl	%edx
	pushl	%edi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7097
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7196:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7097:
	ret

FUNC(op_4c7a)

	movl	GLOBL(regs)+88,%ebx
	leal	2(%ebx),%ecx
	movl	%eax,%edi
	movl	%ecx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%ecx),%ax
RR0_7197:
	rolw	$8,%ax
	movl	%eax,%esi
	xorl	%eax,%eax
	movw	0x2164334A+2(%ecx),%ax
RR2_7061:
	rolw	$8,%ax
	cwtl
	leal	4(%eax,%ebx),%eax
	movl	%eax,%edx
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ebx
	movl	(%eax),%edx
	bswapl	%edx
	movl	%ebx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	%si,%ax
	pushl	%ecx
	pushl	%eax
	pushl	%edx
	pushl	%edi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7098
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7198:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7098:
	ret

FUNC(op_4c7c)

	movl	GLOBL(regs)+88,%ecx
	movl	%eax,%esi
	leal	2(%ecx),%edx
	addl	$8,%ecx
	movl	%edx,GLOBL(regs)+88
	xorl	%eax,%eax
	movw	0x2164334A(%edx),%ax
RR0_7199:
	rolw	$8,%ax
	movl	0x2164334A+2(%edx),%ebx
RR2_7062:
	movl	%ecx,GLOBL(regs)+88
	andl	$65535,%eax
	pushl	%edx
	pushl	%eax
	bswapl	%ebx
	pushl	%ebx
	pushl	%esi
	call	GLOBL(m68k_divl)
	addl	$16,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7099
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7200:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7099:
	ret

FUNC(op_4e40)

	addl	$2,GLOBL(regs)+88
	andl	$15,%eax
	pushl	$0
	addl	$32,%eax
	pushl	%eax
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7100
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7201:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7100:
	ret

FUNC(op_4e50)

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
	xorl	%eax,%eax
	movw	0x2164334A+2(%edx),%ax
RR2_7063:
	rolw	$8,%ax
	cwtl
	popl	%ebx
	addl	%eax,GLOBL(regs)+60
	addl	$4,%edx
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7101
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7202:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7101:
	ret

FUNC(op_4e58)

	movl	%eax,%ebx
	andl	$7,%ebx
	addl	$8,%ebx
	movl	$GLOBL(regs),%esi
	sall	$2,%ebx
	movl	(%ebx,%esi),%ecx
	movl	%ecx,GLOBL(regs)+60
	movl	%ecx,%edx
	movl	%ecx,%eax
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$4,%ecx
	movl	(%eax),%eax
	movl	%ecx,GLOBL(regs)+60
	bswapl	%eax
	movl	%eax,(%ebx,%esi)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7102
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7203:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7102:
	ret

FUNC(op_4e60)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2396
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7103
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7204:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7103:
	ret
	.align	2,0x90
L_7_2396:
	addl	$8,%eax
	movl	GLOBL(regs)(,%eax,4),%eax
	addl	$2,GLOBL(regs)+88
	movl	%eax,GLOBL(regs)+64
	popl	%eax
	decl	%eax
	jl	JJ_7104
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7205:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7104:
	ret

FUNC(op_4e68)

	andl	$7,%eax
	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2402
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7105
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7206:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7105:
	ret
	.align	2,0x90
L_7_2402:
	leal	8(%eax),%edx
	movl	GLOBL(regs)+64,%eax
	movl	%eax,GLOBL(regs)(,%edx,4)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7106
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7207:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7106:
	ret

FUNC(op_4e70)

	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2408
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7107
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7208:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7107:
	ret
	.align	2,0x90
L_7_2408:
	call	GLOBL(customreset)
	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7108
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7209:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7108:
	ret

FUNC(op_4e71)

	addl	$2,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7109
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7210:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7109:
	ret

FUNC(op_4e72)

	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2418
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7110
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7211:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7110:
	ret
	.align	2,0x90
L_7_2418:
	movl	GLOBL(regs)+88,%eax
	xorl	%edx,%edx
	movw	0x2164334A+2(%eax),%dx
RR2_7064:
	rolw	$8,%dx
	movl	%edx,%eax
	movw	%ax,GLOBL(regs)+76
	call	GLOBL(MakeFromSR)
	movb	$1,GLOBL(regs)+83
	addl	$4,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7111
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7212:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7111:
	ret

FUNC(op_4e74)

	movl	GLOBL(regs)+60,%edx
	xorl	%ecx,%ecx
	movl	%edx,%eax
	movb	GLOBL(regs)+62,%cl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%ecx,4),%eax
	addl	$4,%edx
	movl	(%eax),%ecx
	bswapl	%ecx
	movl	%edx,GLOBL(regs)+60
	movl	GLOBL(regs)+88,%eax
	xorl	%ebx,%ebx
	movw	0x2164334A+2(%eax),%bx
RR2_7065:
	rolw	$8,%bx
	movl	%ebx,%eax
	cwtl
	movl	%ecx,GLOBL(regs)+88
	addl	%eax,%edx
	movl	%edx,GLOBL(regs)+60
	popl	%eax
	decl	%eax
	jl	JJ_7112
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7213:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7112:
	ret


FUNC(op_4e75)

	movl	GLOBL(regs)+60,%eax
	xorl	%ecx,%ecx
	movl	%eax,%edx
	movb	GLOBL(regs)+62,%cl
	andl	$65535,%edx
	addl	GLOBL(R24)(,%ecx,4),%edx
	addl	$4,%eax
	movl	(%edx),%edx
	bswapl	%edx
	movl	%eax,GLOBL(regs)+60
	movl	%edx,GLOBL(regs)+88
	popl	%eax
	decl	%eax
	jl	JJ_7113
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7214:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7113:
	ret


FUNC(op_4e76)

	movl	GLOBL(regs)+88,%eax
	addl	$2,%eax
	movl	%eax,GLOBL(regs)+88
	testb	$8,regflags+1
	je	L_7_2479
	pushl	%eax
	pushl	$7
	call	GLOBL(Exception)
	addl	$8,%esp
L_7_2479:
	popl	%eax
	decl	%eax
	jl	JJ_7114
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7215:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7114:
	ret

FUNC(op_4e77)

	call	GLOBL(MakeSR)
	movl	GLOBL(regs)+60,%ebx
	xorl	%edx,%edx
	movl	%ebx,%eax
	movb	GLOBL(regs)+62,%dl
	andl	$65535,%eax
	addl	GLOBL(R24)(,%edx,4),%eax
	xorl	%esi,%esi
	movw	(%eax),%si
	rolw	$8,%si
	movl	%esi,%eax
	movl	%eax,%ecx
	leal	2(%ebx),%eax
	movl	%eax,%edx
	movl	%eax,GLOBL(regs)+60
	shrl	$14,%edx
	andl	$65535,%eax
	andl	$1020,%edx
	addl	GLOBL(R24)(%edx),%eax
	addl	$6,%ebx
	movl	(%eax),%eax
	bswapl	%eax
	movl	%ebx,GLOBL(regs)+60
	movb	%cl,GLOBL(regs)+76
	movl	%eax,GLOBL(regs)+88
	call	GLOBL(MakeFromSR)
	popl	%eax
	decl	%eax
	jl	JJ_7115
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7216:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7115:
	ret

FUNC(op_4e7a)

	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2499
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7116
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7217:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7116:
	ret
	.align	2,0x90
L_7_2499:
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_7066:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	shrw	$12,%ax
	cwtl
	leal	GLOBL(regs)(,%eax,4),%eax
	pushl	%eax
	movl	%edx,%eax
	andl	$4095,%eax
	pushl	%eax
	call	GLOBL(m68k_movec2)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7117
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7218:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7117:
	ret

FUNC(op_4e7b)

	cmpb	$0,GLOBL(regs)+80
	jne	L_7_2507
	pushl	$0
	pushl	$8
	call	GLOBL(Exception)
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7118
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7219:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7118:
	ret
	.align	2,0x90
L_7_2507:
	movl	GLOBL(regs)+88,%eax
	xorl	%ecx,%ecx
	movw	0x2164334A+2(%eax),%cx
RR2_7067:
	rolw	$8,%cx
	movl	%ecx,%eax
	movl	%eax,%edx
	shrw	$12,%ax
	cwtl
	leal	GLOBL(regs)(,%eax,4),%eax
	pushl	%eax
	movl	%edx,%eax
	andl	$4095,%eax
	pushl	%eax
	call	GLOBL(m68k_move2c)
	addl	$4,GLOBL(regs)+88
	addl	$8,%esp
	popl	%eax
	decl	%eax
	jl	JJ_7119
	pushl	%eax
	movl	GLOBL(regs)+88,%ebx
	xorl	%eax,%eax
	movw	0x2164334A(%ebx),%ax
RR0_7220:	movl	GLOBL(cpufunctbl)(,%eax,4),%ebx
	rolw	$8,%ax
	jmp	*%ebx
JJ_7119:
	ret

FUNC(Init020_07)

	pushl	%eax
	movl	GLOBL(ROM),%eax
	movl	%eax,RR0_7000-4
	movl	%eax,RR0_7001-4
	movl	%eax,RR0_7002-4
	movl	%eax,RR0_7003-4
	movl	%eax,RR0_7004-4
	movl	%eax,RR0_7005-4
	movl	%eax,RR0_7006-4
	movl	%eax,RR0_7007-4
	movl	%eax,RR0_7008-4
	movl	%eax,RR0_7009-4
	movl	%eax,RR0_7010-4
	movl	%eax,RR0_7011-4
	movl	%eax,RR0_7012-4
	movl	%eax,RR0_7013-4
	movl	%eax,RR0_7014-4
	movl	%eax,RR0_7015-4
	movl	%eax,RR0_7016-4
	movl	%eax,RR0_7017-4
	movl	%eax,RR0_7018-4
	movl	%eax,RR0_7019-4
	movl	%eax,RR0_7020-4
	movl	%eax,RR0_7021-4
	movl	%eax,RR0_7022-4
	movl	%eax,RR0_7023-4
	movl	%eax,RR0_7024-4
	movl	%eax,RR0_7025-4
	movl	%eax,RR0_7026-4
	movl	%eax,RR0_7027-4
	movl	%eax,RR0_7028-4
	movl	%eax,RR0_7029-4
	movl	%eax,RR0_7030-4
	movl	%eax,RR0_7031-4
	movl	%eax,RR0_7032-4
	movl	%eax,RR0_7033-4
	movl	%eax,RR0_7034-4
	movl	%eax,RR0_7035-4
	movl	%eax,RR0_7036-4
	movl	%eax,RR0_7037-4
	movl	%eax,RR0_7038-4
	movl	%eax,RR0_7039-4
	movl	%eax,RR0_7040-4
	movl	%eax,RR0_7041-4
	movl	%eax,RR0_7042-4
	movl	%eax,RR0_7043-4
	movl	%eax,RR0_7044-4
	movl	%eax,RR0_7045-4
	movl	%eax,RR0_7046-4
	movl	%eax,RR0_7047-4
	movl	%eax,RR0_7048-4
	movl	%eax,RR0_7049-4
	movl	%eax,RR0_7050-4
	movl	%eax,RR0_7051-4
	movl	%eax,RR0_7052-4
	movl	%eax,RR0_7053-4
	movl	%eax,RR0_7054-4
	movl	%eax,RR0_7055-4
	movl	%eax,RR0_7056-4
	movl	%eax,RR0_7057-4
	movl	%eax,RR0_7058-4
	movl	%eax,RR0_7059-4
	movl	%eax,RR0_7060-4
	movl	%eax,RR0_7061-4
	movl	%eax,RR0_7062-4
	movl	%eax,RR0_7063-4
	movl	%eax,RR0_7064-4
	movl	%eax,RR0_7065-4
	movl	%eax,RR0_7066-4
	movl	%eax,RR0_7067-4
	movl	%eax,RR0_7068-4
	movl	%eax,RR0_7069-4
	movl	%eax,RR0_7070-4
	movl	%eax,RR0_7071-4
	movl	%eax,RR0_7072-4
	movl	%eax,RR0_7073-4
	movl	%eax,RR0_7074-4
	movl	%eax,RR0_7075-4
	movl	%eax,RR0_7076-4
	movl	%eax,RR0_7077-4
	movl	%eax,RR0_7078-4
	movl	%eax,RR0_7079-4
	movl	%eax,RR0_7080-4
	movl	%eax,RR0_7081-4
	movl	%eax,RR0_7082-4
	movl	%eax,RR0_7083-4
	movl	%eax,RR0_7084-4
	movl	%eax,RR0_7085-4
	movl	%eax,RR0_7086-4
	movl	%eax,RR0_7087-4
	movl	%eax,RR0_7088-4
	movl	%eax,RR0_7089-4
	movl	%eax,RR0_7090-4
	movl	%eax,RR0_7091-4
	movl	%eax,RR0_7092-4
	movl	%eax,RR0_7093-4
	movl	%eax,RR0_7094-4
	movl	%eax,RR0_7095-4
	movl	%eax,RR0_7096-4
	movl	%eax,RR0_7097-4
	movl	%eax,RR0_7098-4
	movl	%eax,RR0_7099-4
	movl	%eax,RR0_7100-4
	movl	%eax,RR0_7101-4
	movl	%eax,RR0_7102-4
	movl	%eax,RR0_7103-4
	movl	%eax,RR0_7104-4
	movl	%eax,RR0_7105-4
	movl	%eax,RR0_7106-4
	movl	%eax,RR0_7107-4
	movl	%eax,RR0_7108-4
	movl	%eax,RR0_7109-4
	movl	%eax,RR0_7110-4
	movl	%eax,RR0_7111-4
	movl	%eax,RR0_7112-4
	movl	%eax,RR0_7113-4
	movl	%eax,RR0_7114-4
	movl	%eax,RR0_7115-4
	movl	%eax,RR0_7116-4
	movl	%eax,RR0_7117-4
	movl	%eax,RR0_7118-4
	movl	%eax,RR0_7119-4
	movl	%eax,RR0_7120-4
	movl	%eax,RR0_7121-4
	movl	%eax,RR0_7122-4
	movl	%eax,RR0_7123-4
	movl	%eax,RR0_7124-4
	movl	%eax,RR0_7125-4
	movl	%eax,RR0_7126-4
	movl	%eax,RR0_7127-4
	movl	%eax,RR0_7128-4
	movl	%eax,RR0_7129-4
	movl	%eax,RR0_7130-4
	movl	%eax,RR0_7131-4
	movl	%eax,RR0_7132-4
	movl	%eax,RR0_7133-4
	movl	%eax,RR0_7134-4
	movl	%eax,RR0_7135-4
	movl	%eax,RR0_7136-4
	movl	%eax,RR0_7137-4
	movl	%eax,RR0_7138-4
	movl	%eax,RR0_7139-4
	movl	%eax,RR0_7140-4
	movl	%eax,RR0_7141-4
	movl	%eax,RR0_7142-4
	movl	%eax,RR0_7143-4
	movl	%eax,RR0_7144-4
	movl	%eax,RR0_7145-4
	movl	%eax,RR0_7146-4
	movl	%eax,RR0_7147-4
	movl	%eax,RR0_7148-4
	movl	%eax,RR0_7149-4
	movl	%eax,RR0_7150-4
	movl	%eax,RR0_7151-4
	movl	%eax,RR0_7152-4
	movl	%eax,RR0_7153-4
	movl	%eax,RR0_7154-4
	movl	%eax,RR0_7155-4
	movl	%eax,RR0_7156-4
	movl	%eax,RR0_7157-4
	movl	%eax,RR0_7158-4
	movl	%eax,RR0_7159-4
	movl	%eax,RR0_7160-4
	movl	%eax,RR0_7161-4
	movl	%eax,RR0_7162-4
	movl	%eax,RR0_7163-4
	movl	%eax,RR0_7164-4
	movl	%eax,RR0_7165-4
	movl	%eax,RR0_7166-4
	movl	%eax,RR0_7167-4
	movl	%eax,RR0_7168-4
	movl	%eax,RR0_7169-4
	movl	%eax,RR0_7170-4
	movl	%eax,RR0_7171-4
	movl	%eax,RR0_7172-4
	movl	%eax,RR0_7173-4
	movl	%eax,RR0_7174-4
	movl	%eax,RR0_7175-4
	movl	%eax,RR0_7176-4
	movl	%eax,RR0_7177-4
	movl	%eax,RR0_7178-4
	movl	%eax,RR0_7179-4
	movl	%eax,RR0_7180-4
	movl	%eax,RR0_7181-4
	movl	%eax,RR0_7182-4
	movl	%eax,RR0_7183-4
	movl	%eax,RR0_7184-4
	movl	%eax,RR0_7185-4
	movl	%eax,RR0_7186-4
	movl	%eax,RR0_7187-4
	movl	%eax,RR0_7188-4
	movl	%eax,RR0_7189-4
	movl	%eax,RR0_7190-4
	movl	%eax,RR0_7191-4
	movl	%eax,RR0_7192-4
	movl	%eax,RR0_7193-4
	movl	%eax,RR0_7194-4
	movl	%eax,RR0_7195-4
	movl	%eax,RR0_7196-4
	movl	%eax,RR0_7197-4
	movl	%eax,RR0_7198-4
	movl	%eax,RR0_7199-4
	movl	%eax,RR0_7200-4
	movl	%eax,RR0_7201-4
	movl	%eax,RR0_7202-4
	movl	%eax,RR0_7203-4
	movl	%eax,RR0_7204-4
	movl	%eax,RR0_7205-4
	movl	%eax,RR0_7206-4
	movl	%eax,RR0_7207-4
	movl	%eax,RR0_7208-4
	movl	%eax,RR0_7209-4
	movl	%eax,RR0_7210-4
	movl	%eax,RR0_7211-4
	movl	%eax,RR0_7212-4
	movl	%eax,RR0_7213-4
	movl	%eax,RR0_7214-4
	movl	%eax,RR0_7215-4
	movl	%eax,RR0_7216-4
	movl	%eax,RR0_7217-4
	movl	%eax,RR0_7218-4
	movl	%eax,RR0_7219-4
	movl	%eax,RR0_7220-4
	incl	%eax
	incl	%eax
	movl	%eax,RR2_7000-4
	movl	%eax,RR2_7001-4
	movl	%eax,RR2_7002-4
	movl	%eax,RR2_7003-4
	movl	%eax,RR2_7004-4
	movl	%eax,RR2_7005-4
	movl	%eax,RR2_7006-4
	movl	%eax,RR2_7007-4
	movl	%eax,RR2_7008-4
	movl	%eax,RR2_7009-4
	movl	%eax,RR2_7010-4
	movl	%eax,RR2_7011-4
	movl	%eax,RR2_7012-4
	movl	%eax,RR2_7013-4
	movl	%eax,RR2_7014-4
	movl	%eax,RR2_7015-4
	movl	%eax,RR2_7016-4
	movl	%eax,RR2_7017-4
	movl	%eax,RR2_7018-4
	movl	%eax,RR2_7019-4
	movl	%eax,RR2_7020-4
	movl	%eax,RR2_7021-4
	movl	%eax,RR2_7022-4
	movl	%eax,RR2_7023-4
	movl	%eax,RR2_7024-4
	movl	%eax,RR2_7025-4
	movl	%eax,RR2_7026-4
	movl	%eax,RR2_7027-4
	movl	%eax,RR2_7028-4
	movl	%eax,RR2_7029-4
	movl	%eax,RR2_7030-4
	movl	%eax,RR2_7031-4
	movl	%eax,RR2_7032-4
	movl	%eax,RR2_7033-4
	movl	%eax,RR2_7034-4
	movl	%eax,RR2_7035-4
	movl	%eax,RR2_7036-4
	movl	%eax,RR2_7037-4
	movl	%eax,RR2_7038-4
	movl	%eax,RR2_7039-4
	movl	%eax,RR2_7040-4
	movl	%eax,RR2_7041-4
	movl	%eax,RR2_7042-4
	movl	%eax,RR2_7043-4
	movl	%eax,RR2_7044-4
	movl	%eax,RR2_7045-4
	movl	%eax,RR2_7046-4
	movl	%eax,RR2_7047-4
	movl	%eax,RR2_7048-4
	movl	%eax,RR2_7049-4
	movl	%eax,RR2_7050-4
	movl	%eax,RR2_7051-4
	movl	%eax,RR2_7052-4
	movl	%eax,RR2_7053-4
	movl	%eax,RR2_7054-4
	movl	%eax,RR2_7055-4
	movl	%eax,RR2_7056-4
	movl	%eax,RR2_7057-4
	movl	%eax,RR2_7058-4
	movl	%eax,RR2_7059-4
	movl	%eax,RR2_7060-4
	movl	%eax,RR2_7061-4
	movl	%eax,RR2_7062-4
	movl	%eax,RR2_7063-4
	movl	%eax,RR2_7064-4
	movl	%eax,RR2_7065-4
	movl	%eax,RR2_7066-4
	movl	%eax,RR2_7067-4
	incl	%eax
	movl	%eax,RR3_7000-4
	incl	%eax
	movl	%eax,RR4_7000-4
	movl	%eax,RR4_7001-4
	movl	%eax,RR4_7002-4
	movl	%eax,RR4_7003-4
	movl	%eax,RR4_7004-4
	movl	%eax,RR4_7005-4
	movl	%eax,RR4_7006-4
	movl	%eax,RR4_7007-4
	movl	%eax,RR4_7008-4
	movl	%eax,RR4_7009-4
	movl	%eax,RR4_7010-4
	movl	%eax,RR4_7011-4
	movl	%eax,RR4_7012-4
	movl	%eax,RR4_7013-4
	movl	%eax,RR4_7014-4
	movl	%eax,RR4_7015-4
	movl	%eax,RR4_7016-4
	movl	%eax,RR4_7017-4
	movl	%eax,RR4_7018-4
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
