	.file	"instrset_armv4.c"
	.text
	.p2align 4,,15
.globl CheckConditionFlag
	.type	CheckConditionFlag, @function
CheckConditionFlag:
	pushl	%ebp
	movl	$-1, %eax
	movl	%esp, %ebp
	subl	$12, %esp
	movl	8(%ebp), %edx
	movl	%edi, 8(%esp)
	movl	12(%ebp), %edi
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	testl	%edx, %edx
	je	.L3
	movzbl	1215(%edx), %eax
	movl	$1, %esi
	shrb	$4, %al
	andl	%eax, %esi
	shrb	%al
	movl	%eax, %edx
	shrb	%al
	andl	$1, %edx
	movl	%eax, %ebx
	shrb	%al
	andl	$1, %ebx
	movzbl	%al, %ecx
	xorl	%eax, %eax
	cmpl	$15, %edi
	jbe	.L23
.L3:
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	8(%esp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L23:
	jmp	*.L20(,%edi,4)
	.section	.rodata
	.align 4
	.align 4
.L20:
	.long	.L5
	.long	.L6
	.long	.L7
	.long	.L8
	.long	.L9
	.long	.L10
	.long	.L11
	.long	.L12
	.long	.L13
	.long	.L14
	.long	.L15
	.long	.L16
	.long	.L17
	.long	.L18
	.long	.L19
	.long	.L19
	.text
	.p2align 4,,7
	.p2align 3
.L19:
	movl	$1, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L18:
	xorl	%eax, %eax
	cmpl	%esi, %ecx
	setne	%al
	orl	%ebx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L17:
	testl	%ebx, %ebx
	sete	%dl
	xorl	%eax, %eax
	cmpl	%esi, %ecx
	sete	%al
	andl	%edx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L16:
	xorl	%eax, %eax
	cmpl	%esi, %ecx
	setne	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L15:
	xorl	%eax, %eax
	cmpl	%esi, %ecx
	sete	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L14:
	xorl	%eax, %eax
	testl	%edx, %edx
	sete	%al
	orl	%ebx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L13:
	testl	%ebx, %ebx
	sete	%al
	andl	%edx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L12:
	xorl	%eax, %eax
	testl	%esi, %esi
	sete	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L11:
	movl	%esi, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L10:
	xorl	%eax, %eax
	testl	%ecx, %ecx
	sete	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L9:
	movl	%ecx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L8:
	xorl	%eax, %eax
	testl	%edx, %edx
	sete	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L7:
	movl	%edx, %eax
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L6:
	xorl	%eax, %eax
	testl	%ebx, %ebx
	sete	%al
	jmp	.L3
	.p2align 4,,7
	.p2align 3
.L5:
	movl	%ebx, %eax
	jmp	.L3
	.size	CheckConditionFlag, .-CheckConditionFlag
	.p2align 4,,15
	.type	AddressingMode1, @function
AddressingMode1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ebx, -12(%ebp)
	movl	%eax, %ebx
	movl	%esi, -8(%ebp)
	movl	%ecx, %esi
	movl	%edi, -4(%ebp)
	movzbl	1212(%eax), %eax
	andl	$31, %eax
	testl	$33554432, %edx
	je	.L25
	movl	%edx, %ecx
	movzbl	%dl, %eax
	shrl	$7, %ecx
	andl	$30, %ecx
	rorl	%cl, %eax
	testl	%ecx, %ecx
	movl	%eax, (%esi)
	jne	.L26
.L64:
	movzbl	1215(%ebx), %eax
	movl	8(%ebp), %edx
	shrb	$5, %al
	andl	$1, %eax
	movl	%eax, (%edx)
.L63:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L25:
	movzbl	%al, %eax
	sall	$6, %eax
	testl	$33554448, %edx
	leal	(%ebx,%eax), %eax
	movl	%eax, -16(%ebp)
	jne	.L28
	movl	%edx, %edi
	shrl	$5, %edi
	andl	$3, %edi
	cmpl	$1, %edi
	je	.L30
	jle	.L71
	cmpl	$2, %edi
	je	.L31
	cmpl	$3, %edi
	.p2align 4,,7
	.p2align 3
	jne	.L63
	testl	$3968, %edx
	.p2align 4,,5
	.p2align 3
	jne	.L45
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	jne	.L63
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	movl	60(%eax), %edx
	movzbl	1215(%ebx), %eax
	addl	$8, %edx
	shrb	$5, %al
	sall	$31, %eax
	shrl	%edx
	orl	%eax, %edx
	movl	%edx, (%ecx)
	movl	-16(%ebp), %ecx
	movl	8(%ebp), %ebx
	movl	(%ecx), %eax
	movl	60(%eax), %eax
	addl	$8, %eax
	shrl	$31, %eax
	movl	%eax, (%ebx)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L28:
	movl	%edx, %eax
	andl	$33554576, %eax
	cmpl	$16, %eax
	jne	.L63
	movl	%edx, %eax
	shrl	$5, %eax
	andl	$3, %eax
	cmpl	$1, %eax
	je	.L48
	jle	.L72
	cmpl	$2, %eax
	je	.L49
	cmpl	$3, %eax
	.p2align 4,,7
	.p2align 3
	jne	.L63
	movl	-16(%ebp), %eax
	movl	%edx, %edi
	shrl	$8, %edi
	andl	$15, %edi
	movl	(%eax), %ecx
	movl	(%ecx,%edi,4), %eax
	testb	%al, %al
	je	.L73
	andl	$31, %eax
	movl	%eax, -20(%ebp)
	je	.L74
	movl	%edx, %ebx
	andl	$15, %ebx
	movl	(%ecx,%ebx,4), %eax
	movl	$32, %ecx
	subl	-20(%ebp), %ecx
	movl	%eax, %edx
	sall	%cl, %edx
	movzbl	-20(%ebp), %ecx
	shrl	%cl, %eax
	orl	%eax, %edx
	movl	-16(%ebp), %eax
	movl	%edx, (%esi)
	movl	(%eax), %edx
	movl	(%edx,%edi,4), %eax
	andl	$31, %eax
	subl	$1, %eax
	.p2align 4,,7
	.p2align 3
.L66:
	testl	%eax, (%edx,%ebx,4)
	movl	8(%ebp), %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%edx)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L26:
	movzbl	3(%esi), %eax
	movl	8(%ebp), %ecx
	shrb	$7, %al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L30:
	testl	$3968, %edx
	jne	.L36
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L75
	movl	-16(%ebp), %ecx
	movzbl	%al, %edx
	movl	8(%ebp), %ebx
	movl	(%ecx), %eax
	movl	(%eax,%edx,4), %eax
	shrl	$31, %eax
	movl	%eax, (%ebx)
.L65:
	movl	$0, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L31:
	testl	$3968, %edx
	jne	.L40
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L76
	movl	-16(%ebp), %ecx
	movzbl	%al, %edx
	movl	(%ecx), %eax
	movl	(%eax,%edx,4), %edx
	testl	%edx, %edx
	js	.L77
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	movl	$0, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L40:
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L78
	movzbl	%al, %edi
	movl	-16(%ebp), %eax
	shrl	$7, %edx
	andl	$31, %edx
	leal	-1(%edx), %ecx
	movl	(%eax), %ebx
	movl	$1, %eax
	sall	%cl, %eax
	movl	8(%ebp), %ecx
	testl	%eax, (%ebx,%edi,4)
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	movl	(%ebx,%edi,4), %eax
	movl	%edx, %ecx
	sarl	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L45:
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L79
	movl	%edx, %ecx
	movl	-16(%ebp), %edx
	movzbl	%al, %ebx
	shrl	$7, %ecx
	andl	$31, %ecx
	movl	(%edx), %eax
	movl	(%eax,%ebx,4), %eax
	rorl	%cl, %eax
	subl	$1, %ecx
	movl	%eax, (%esi)
	movl	$1, %eax
	movl	(%edx), %edx
	sall	%cl, %eax
	jmp	.L66
	.p2align 4,,7
	.p2align 3
.L36:
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L80
	movzbl	%al, %eax
	movl	%eax, -24(%ebp)
	movl	-16(%ebp), %eax
	shrl	$7, %edx
	andl	$31, %edx
	leal	-1(%edx), %ecx
	sall	%cl, %edi
	movl	-24(%ebp), %ecx
	movl	(%eax), %ebx
	xorl	%eax, %eax
	testl	%edi, (%ebx,%ecx,4)
	movl	8(%ebp), %ecx
	setne	%al
	movl	%eax, (%ecx)
	movl	-24(%ebp), %ecx
	movl	(%ebx,%ecx,4), %eax
	movl	%edx, %ecx
	shrl	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L72:
	testl	%eax, %eax
	jne	.L63
	movl	-16(%ebp), %ecx
	movl	%edx, %edi
	shrl	$8, %edi
	andl	$15, %edi
	movl	(%ecx), %eax
	movzbl	(%eax,%edi,4), %ecx
	testl	%ecx, %ecx
	je	.L69
	cmpl	$31, %ecx
	jbe	.L81
	cmpl	$32, %ecx
	je	.L82
.L68:
	movl	8(%ebp), %eax
	movl	$0, (%esi)
	movl	$0, (%eax)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L71:
	testl	%edi, %edi
	jne	.L63
	testl	$3968, %edx
	jne	.L34
	movzbl	1215(%ebx), %eax
	movl	%edx, %ecx
	movl	8(%ebp), %ebx
	andl	$15, %ecx
	movzbl	%cl, %edx
	shrb	$5, %al
	andl	$1, %eax
	cmpb	$15, %cl
	movl	%eax, (%ebx)
	movl	-16(%ebp), %ebx
	movl	(%ebx), %eax
	movl	(%eax,%edx,4), %eax
	movl	%eax, (%esi)
	jne	.L63
	addl	$8, %eax
	movl	%eax, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L34:
	movl	%edx, %eax
	andl	$15, %eax
	cmpb	$15, %al
	je	.L83
	movzbl	%al, %edi
	movl	-16(%ebp), %eax
	movl	$32, %ecx
	shrl	$7, %edx
	andl	$31, %edx
	subl	%edx, %ecx
	movl	(%eax), %ebx
	movl	$1, %eax
	sall	%cl, %eax
	movl	8(%ebp), %ecx
	testl	%eax, (%ebx,%edi,4)
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	movl	(%ebx,%edi,4), %eax
	movl	%edx, %ecx
	sall	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L69:
	andl	$15, %edx
	movl	(%eax,%edx,4), %eax
	movl	%eax, (%esi)
	movzbl	1215(%ebx), %eax
	movl	8(%ebp), %ebx
	shrb	$5, %al
	andl	$1, %eax
	movl	%eax, (%ebx)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L49:
	movl	-16(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%edx, %ecx
	shrl	$8, %ecx
	andl	$15, %ecx
	movl	%ecx, -32(%ebp)
	movzbl	(%eax,%ecx,4), %edi
	testl	%edi, %edi
	je	.L69
	cmpl	$31, %edi
	jbe	.L84
	andl	$15, %edx
	movl	(%eax,%edx,4), %eax
	testl	%eax, %eax
	jns	.L68
	movl	8(%ebp), %edx
	movl	$-1, (%esi)
	movl	$1, (%edx)
	jmp	.L63
	.p2align 4,,7
	.p2align 3
.L48:
	movl	-16(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%edx, %ecx
	shrl	$8, %ecx
	andl	$15, %ecx
	movl	%ecx, -28(%ebp)
	movzbl	(%eax,%ecx,4), %edi
	testl	%edi, %edi
	je	.L69
	cmpl	$31, %edi
	jbe	.L85
	cmpl	$32, %edi
	jne	.L68
	movl	-16(%ebp), %ecx
	andl	$15, %edx
	movl	$0, (%esi)
	movl	8(%ebp), %ebx
	movl	(%ecx), %eax
	movl	(%eax,%edx,4), %eax
	andl	$-2147483648, %eax
	movl	%eax, (%ebx)
	jmp	.L63
.L73:
	andl	$15, %edx
	movl	(%ecx,%edx,4), %eax
	movl	%eax, (%esi)
	jmp	.L64
.L79:
	movl	%edx, %ecx
	movl	-16(%ebp), %edx
	shrl	$7, %ecx
	andl	$31, %ecx
	movl	(%edx), %eax
	movl	60(%eax), %eax
	addl	$8, %eax
	rorl	%cl, %eax
	subl	$1, %ecx
	movl	%eax, (%esi)
	movl	(%edx), %eax
	movl	60(%eax), %edx
	movl	$1, %eax
	sall	%cl, %eax
	movl	8(%ebp), %ecx
	addl	$8, %edx
	testl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	jmp	.L63
.L75:
	movl	-16(%ebp), %ebx
	movl	8(%ebp), %edx
	movl	(%ebx), %eax
	movl	60(%eax), %eax
	addl	$8, %eax
	shrl	$31, %eax
	movl	%eax, (%edx)
	jmp	.L65
.L80:
	movl	-16(%ebp), %eax
	shrl	$7, %edx
	andl	$31, %edx
	leal	-1(%edx), %ecx
	sall	%cl, %edi
	movl	8(%ebp), %ecx
	movl	(%eax), %ebx
	movl	60(%ebx), %eax
	addl	$8, %eax
	testl	%edi, %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	movl	60(%ebx), %eax
	movl	%edx, %ecx
	addl	$8, %eax
	shrl	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
.L83:
	movl	-16(%ebp), %eax
	movl	%edx, %ebx
	movl	$32, %ecx
	shrl	$7, %ebx
	andl	$31, %ebx
	subl	%ebx, %ecx
	movl	(%eax), %edi
	movl	$1, %eax
	sall	%cl, %eax
	movl	%ebx, %ecx
	movl	60(%edi), %edx
	addl	$8, %edx
	testl	%eax, %edx
	movl	8(%ebp), %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%edx)
	movl	60(%edi), %eax
	addl	$8, %eax
	sall	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
.L76:
	movl	-16(%ebp), %ebx
	movl	(%ebx), %eax
	movl	60(%eax), %eax
	addl	$8, %eax
	js	.L86
	movl	8(%ebp), %edx
	movl	$0, (%edx)
	jmp	.L65
.L78:
	movl	%edx, %ebx
	movl	-16(%ebp), %edx
	movl	$1, %eax
	shrl	$7, %ebx
	andl	$31, %ebx
	leal	-1(%ebx), %ecx
	movl	(%edx), %edi
	sall	%cl, %eax
	movl	8(%ebp), %ecx
	movl	60(%edi), %edx
	addl	$8, %edx
	testl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ecx)
	movl	60(%edi), %eax
	movl	%ebx, %ecx
	addl	$8, %eax
	sarl	%cl, %eax
	movl	%eax, (%esi)
	jmp	.L63
.L77:
	movl	8(%ebp), %ebx
	movl	$1, (%ebx)
	movl	$-1, (%esi)
	jmp	.L63
.L84:
	movl	%edx, %ebx
	movl	%edi, %ecx
	andl	$15, %ebx
	movl	(%eax,%ebx,4), %eax
	sarl	%cl, %eax
	movl	-32(%ebp), %ecx
	movl	%eax, (%esi)
	movl	-16(%ebp), %eax
	movl	(%eax), %edx
.L70:
	movzbl	(%edx,%ecx,4), %eax
	subl	$1, %eax
	testl	%eax, (%edx,%ebx,4)
	movl	8(%ebp), %ebx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, (%ebx)
	jmp	.L63
.L85:
	movl	%edx, %ebx
	movl	%edi, %ecx
	andl	$15, %ebx
	movl	(%eax,%ebx,4), %eax
	shrl	%cl, %eax
	movl	-28(%ebp), %ecx
	movl	%eax, (%esi)
	movl	-16(%ebp), %eax
	movl	(%eax), %edx
	jmp	.L70
.L81:
	movl	%edx, %ebx
	andl	$15, %ebx
	movl	(%eax,%ebx,4), %eax
	sall	%cl, %eax
	movl	$32, %ecx
	movl	%eax, (%esi)
	movl	-16(%ebp), %eax
	movl	(%eax), %edx
	movzbl	(%edx,%edi,4), %eax
	subl	%eax, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	jmp	.L66
.L74:
	andl	$15, %edx
	movl	8(%ebp), %ebx
	movl	(%ecx,%edx,4), %eax
	movl	-16(%ebp), %ecx
	movl	%eax, (%esi)
	movl	(%ecx), %eax
	movl	(%eax,%edx,4), %eax
	shrl	$31, %eax
	movl	%eax, (%ebx)
	jmp	.L63
.L86:
	movl	8(%ebp), %eax
	movl	$1, (%eax)
	movl	$-1, (%ecx)
	jmp	.L63
.L82:
	movl	-16(%ebp), %ecx
	andl	$15, %edx
	movl	$0, (%esi)
	movl	8(%ebp), %ebx
	movl	(%ecx), %eax
	movl	(%eax,%edx,4), %eax
	andl	$1, %eax
	movl	%eax, (%ebx)
	jmp	.L63
	.size	AddressingMode1, .-AddressingMode1
	.p2align 4,,15
.globl ARMV4_ExecuteInstruction
	.type	ARMV4_ExecuteInstruction, @function
ARMV4_ExecuteInstruction:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	20(%ebp), %edx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	cmpl	$1, %edx
	je	.L89
	xorl	%eax, %eax
	cmpl	$2, %edx
	je	.L94
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L89:
	movl	$-1, %eax
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L94:
	movl	%ecx, %eax
	movl	%ecx, %edx
	shrl	$16, %eax
	shrl	$21, %edx
	andl	$16, %eax
	andl	$15, %edx
	orl	%edx, %eax
	movl	%ecx, 16(%ebp)
	movl	datapr.3000(,%eax,4), %ecx
	movl	%ebx, 12(%ebp)
	movl	%esi, 8(%ebp)
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	%ebp, %esp
	popl	%ebp
	jmp	*%ecx
	.size	ARMV4_ExecuteInstruction, .-ARMV4_ExecuteInstruction
	.p2align 4,,15
	.type	handler_cmn, @function
handler_cmn:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	16(%ebp), %ebx
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	%ebx, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L99
.L96:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L99:
	leal	-20(%ebp), %eax
	movl	%ebx, %edx
	movl	%eax, (%esp)
	movl	8(%ebp), %eax
	leal	-16(%ebp), %ecx
	call	AddressingMode1
	movl	8(%ebp), %ecx
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%ecx, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %eax
	movl	%ebx, %edx
	movl	8(%ebp), %ecx
	shrl	$16, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%ecx,%eax,4), %eax
	movl	(%eax), %edi
	je	.L100
.L97:
	movl	8(%ebp), %eax
	movl	-16(%ebp), %esi
	movzbl	1215(%eax), %edx
	leal	(%edi,%esi), %ebx
	movl	%ebx, %ecx
	shrl	$31, %ecx
	sall	$7, %ecx
	andl	$63, %edx
	testl	%ebx, %ebx
	sete	%al
	orl	%ecx, %edx
	sall	$6, %eax
	orl	%eax, %edx
	cmpl	%edi, %ebx
	setb	%cl
	andl	$-49, %edx
	sall	$5, %ecx
	cmpl	%edi, %ebx
	setl	%al
	orl	%ecx, %edx
	movl	8(%ebp), %ecx
	shrl	$31, %esi
	xorl	%esi, %eax
	sall	$4, %eax
	orl	%eax, %edx
	movb	%dl, 1215(%ecx)
	jmp	.L96
	.p2align 4,,7
	.p2align 3
.L100:
	addl	$8, %edi
	jmp	.L97
	.size	handler_cmn, .-handler_cmn
	.p2align 4,,15
	.type	handler_cmp, @function
handler_cmp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	16(%ebp), %ebx
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%edi, -4(%ebp)
	movl	%ebx, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L105
.L102:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L105:
	leal	-20(%ebp), %eax
	movl	%ebx, %edx
	leal	-16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %eax
	movl	%ebx, %edx
	shrl	$16, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %edi
	je	.L106
.L103:
	movl	%edi, %eax
	movzbl	1215(%esi), %edx
	subl	-16(%ebp), %eax
	movl	%eax, %ebx
	andl	$63, %edx
	shrl	$31, %ebx
	movl	%ebx, %ecx
	sall	$7, %ecx
	testl	%eax, %eax
	sete	%al
	orl	%ecx, %edx
	sall	$6, %eax
	orl	%eax, %edx
	cmpl	-16(%ebp), %edi
	setae	%cl
	andl	$-49, %edx
	sall	$5, %ecx
	cmpl	-16(%ebp), %edi
	setl	%al
	orl	%ecx, %edx
	xorl	%eax, %ebx
	sall	$4, %ebx
	orl	%ebx, %edx
	movb	%dl, 1215(%esi)
	jmp	.L102
	.p2align 4,,7
	.p2align 3
.L106:
	addl	$8, %edi
	jmp	.L103
	.size	handler_cmp, .-handler_cmp
	.p2align 4,,15
	.type	handler_teq, @function
handler_teq:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	16(%ebp), %ebx
	movl	8(%ebp), %esi
	movl	%ebx, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L111
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L111:
	leal	-16(%ebp), %eax
	movl	%ebx, %edx
	leal	-12(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-20(%ebp), %eax
	movl	%ebx, %edx
	shrl	$16, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	je	.L112
.L109:
	movl	%eax, %edx
	movzbl	1215(%esi), %eax
	xorl	-12(%ebp), %edx
	movl	%edx, %ecx
	andl	$63, %eax
	shrl	$31, %ecx
	sall	$7, %ecx
	testl	%edx, %edx
	sete	%dl
	orl	%ecx, %eax
	sall	$6, %edx
	orl	%edx, %eax
	movl	-16(%ebp), %edx
	andl	$-33, %eax
	andl	$1, %edx
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L112:
	addl	$8, %eax
	jmp	.L109
	.size	handler_teq, .-handler_teq
	.p2align 4,,15
	.type	handler_tst, @function
handler_tst:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	16(%ebp), %ebx
	movl	8(%ebp), %esi
	movl	%ebx, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L117
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L117:
	leal	-16(%ebp), %eax
	movl	%ebx, %edx
	leal	-12(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-20(%ebp), %eax
	movl	%ebx, %edx
	shrl	$16, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	je	.L118
.L115:
	movl	%eax, %edx
	movzbl	1215(%esi), %eax
	andl	-12(%ebp), %edx
	movl	%edx, %ecx
	andl	$63, %eax
	shrl	$31, %ecx
	sall	$7, %ecx
	testl	%edx, %edx
	sete	%dl
	orl	%ecx, %eax
	sall	$6, %edx
	orl	%edx, %eax
	movl	-16(%ebp), %edx
	andl	$-33, %eax
	andl	$1, %edx
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L118:
	addl	$8, %eax
	jmp	.L115
	.size	handler_tst, .-handler_tst
	.p2align 4,,15
	.type	handler_mvn, @function
handler_mvn:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	16(%ebp), %esi
	movl	8(%ebp), %ebx
	movl	%esi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L124
.L120:
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L124:
	leal	-16(%ebp), %eax
	movl	%esi, %edx
	leal	-12(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%ebx, %eax
	call	AddressingMode1
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	GetStatusRegisterMode
	movl	-20(%ebp), %eax
	movl	%esi, %edx
	shrl	$12, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%ebx,%eax,4), %ecx
	movl	-12(%ebp), %eax
	notl	%eax
	movl	%eax, (%ecx)
	je	.L125
	andl	$1048576, %esi
	je	.L120
	movl	%eax, %edx
	movzbl	1215(%ebx), %eax
	shrl	$31, %edx
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%ebx)
	movl	(%ecx), %ecx
	movl	-16(%ebp), %edx
	testl	%ecx, %ecx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	andl	$1, %edx
	sall	$5, %edx
	orl	%ecx, %eax
	orl	%edx, %eax
	movb	%al, 1215(%ebx)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L125:
	movl	%ebx, (%esp)
	call	FlushPipeline
	andl	$1048576, %esi
	je	.L120
	movl	-20(%ebp), %eax
	movl	1148(%ebx,%eax,4), %eax
	movl	%eax, 1212(%ebx)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	handler_mvn, .-handler_mvn
	.p2align 4,,15
	.type	handler_bic, @function
handler_bic:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L132
.L127:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L132:
	movl	16(%ebp), %edx
	leal	-20(%ebp), %eax
	leal	-16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%edi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%edi, (%esp)
	call	GetStatusRegisterMode
	movl	16(%ebp), %edx
	movl	-24(%ebp), %ecx
	movl	16(%ebp), %ebx
	shrl	$16, %edx
	movl	%ecx, %eax
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	movl	(%edi,%eax,4), %eax
	shrl	$12, %ebx
	andl	$15, %ebx
	cmpl	$15, %edx
	movl	(%eax), %esi
	je	.L133
.L128:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%edi,%eax,4), %ecx
	movl	-16(%ebp), %eax
	notl	%eax
	andl	%esi, %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L134
	testl	$1048576, 16(%ebp)
	je	.L127
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%edi), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	movl	(%ecx), %ebx
	movl	-20(%ebp), %edx
	testl	%ebx, %ebx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	andl	$1, %edx
	sall	$5, %edx
	orl	%ecx, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	jmp	.L127
	.p2align 4,,7
	.p2align 3
.L133:
	addl	$8, %esi
	jmp	.L128
	.p2align 4,,7
	.p2align 3
.L134:
	movl	%edi, (%esp)
	call	FlushPipeline
	testl	$1048576, 16(%ebp)
	.p2align 4,,2
	.p2align 3
	je	.L127
	movl	-24(%ebp), %eax
	movl	1148(%edi,%eax,4), %eax
	movl	%eax, 1212(%edi)
	jmp	.L127
	.size	handler_bic, .-handler_bic
	.p2align 4,,15
	.type	handler_mov, @function
handler_mov:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	16(%ebp), %esi
	movl	8(%ebp), %ebx
	movl	%esi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L140
.L136:
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L140:
	leal	-16(%ebp), %eax
	movl	%esi, %edx
	leal	-12(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%ebx, %eax
	call	AddressingMode1
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	GetStatusRegisterMode
	movl	-20(%ebp), %eax
	movl	%esi, %edx
	shrl	$12, %edx
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%ebx,%eax,4), %ecx
	movl	-12(%ebp), %eax
	movl	%eax, (%ecx)
	je	.L141
	andl	$1048576, %esi
	je	.L136
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%ebx), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%ebx)
	movl	(%ecx), %esi
	movl	-16(%ebp), %edx
	testl	%esi, %esi
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	andl	$1, %edx
	sall	$5, %edx
	orl	%ecx, %eax
	orl	%edx, %eax
	movb	%al, 1215(%ebx)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L141:
	movl	%ebx, (%esp)
	call	FlushPipeline
	andl	$1048576, %esi
	je	.L136
	movl	-20(%ebp), %eax
	movl	1148(%ebx,%eax,4), %eax
	movl	%eax, 1212(%ebx)
	addl	$32, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	handler_mov, .-handler_mov
	.p2align 4,,15
	.type	handler_orr, @function
handler_orr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L148
.L143:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L148:
	movl	16(%ebp), %edx
	leal	-20(%ebp), %eax
	leal	-16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%edi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%edi, (%esp)
	call	GetStatusRegisterMode
	movl	16(%ebp), %edx
	movl	-24(%ebp), %ecx
	movl	16(%ebp), %ebx
	shrl	$16, %edx
	movl	%ecx, %eax
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	movl	(%edi,%eax,4), %eax
	shrl	$12, %ebx
	andl	$15, %ebx
	cmpl	$15, %edx
	movl	(%eax), %esi
	je	.L149
.L144:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%edi,%eax,4), %ecx
	movl	%esi, %eax
	orl	-16(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L150
	testl	$1048576, 16(%ebp)
	je	.L143
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%edi), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	movl	(%ecx), %edx
	testl	%edx, %edx
	movl	-20(%ebp), %edx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	orl	%ecx, %eax
	andl	$1, %edx
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	jmp	.L143
	.p2align 4,,7
	.p2align 3
.L149:
	addl	$8, %esi
	jmp	.L144
	.p2align 4,,7
	.p2align 3
.L150:
	movl	%edi, (%esp)
	call	FlushPipeline
	testl	$1048576, 16(%ebp)
	.p2align 4,,2
	.p2align 3
	je	.L143
	movl	-24(%ebp), %eax
	movl	1148(%edi,%eax,4), %eax
	movl	%eax, 1212(%edi)
	jmp	.L143
	.size	handler_orr, .-handler_orr
	.p2align 4,,15
	.type	handler_rsc, @function
handler_rsc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L157
.L152:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L157:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	je	.L158
.L153:
	sall	$4, %ecx
	movl	-16(%ebp), %edx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %eax
	subl	-36(%ebp), %edx
	movl	%eax, -32(%ebp)
	movzbl	1215(%esi), %eax
	shrb	$5, %al
	xorl	$1, %eax
	andl	$1, %eax
	subl	%eax, %edx
	movl	-32(%ebp), %eax
	cmpl	$15, %ebx
	movl	%edx, (%eax)
	je	.L159
	andl	$1048576, %edi
	je	.L152
	movzbl	1215(%esi), %eax
	shrl	$31, %edx
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	-16(%ebp), %ebx
	movl	(%edx), %ecx
	testl	%ecx, %ecx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	cmpl	-36(%ebp), %ebx
	setae	%dl
	orl	%ecx, %eax
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	(%edx), %ecx
	shrl	$31, %ecx
	cmpl	-36(%ebp), %ebx
	setl	%dl
	andl	$-17, %eax
	xorl	%ecx, %edx
	sall	$4, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	jmp	.L152
	.p2align 4,,7
	.p2align 3
.L158:
	addl	$8, %eax
	movl	%eax, -36(%ebp)
	jmp	.L153
	.p2align 4,,7
	.p2align 3
.L159:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	je	.L152
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L152
	.size	handler_rsc, .-handler_rsc
	.p2align 4,,15
	.type	handler_sbc, @function
handler_sbc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L166
.L161:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L166:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	je	.L167
.L162:
	sall	$4, %ecx
	movl	-36(%ebp), %edx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %eax
	subl	-16(%ebp), %edx
	movl	%eax, -32(%ebp)
	movzbl	1215(%esi), %eax
	shrb	$5, %al
	xorl	$1, %eax
	andl	$1, %eax
	subl	%eax, %edx
	movl	-32(%ebp), %eax
	cmpl	$15, %ebx
	movl	%edx, (%eax)
	je	.L168
	andl	$1048576, %edi
	je	.L161
	movzbl	1215(%esi), %eax
	shrl	$31, %edx
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	(%edx), %ebx
	testl	%ebx, %ebx
	movl	-16(%ebp), %ebx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	cmpl	%ebx, -36(%ebp)
	setae	%dl
	orl	%ecx, %eax
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	(%edx), %ecx
	shrl	$31, %ecx
	cmpl	%ebx, -36(%ebp)
	setl	%dl
	andl	$-17, %eax
	xorl	%ecx, %edx
	sall	$4, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	jmp	.L161
	.p2align 4,,7
	.p2align 3
.L167:
	addl	$8, %eax
	movl	%eax, -36(%ebp)
	jmp	.L162
	.p2align 4,,7
	.p2align 3
.L168:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	je	.L161
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L161
	.size	handler_sbc, .-handler_sbc
	.p2align 4,,15
	.type	handler_adc, @function
handler_adc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L175
.L170:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L175:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -32(%ebp)
	je	.L176
.L171:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %ecx
	movzbl	1215(%esi), %eax
	shrb	$5, %al
	andl	$1, %eax
	addl	-16(%ebp), %eax
	addl	-32(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L177
	andl	$1048576, %edi
	je	.L170
	movzbl	1215(%esi), %edx
	shrl	$31, %eax
	sall	$7, %eax
	andl	$127, %edx
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	(%ecx), %edi
	testl	%edi, %edi
	sete	%al
	andl	$-65, %edx
	sall	$6, %eax
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	-32(%ebp), %eax
	cmpl	%eax, (%ecx)
	setb	%al
	andl	$-33, %edx
	sall	$5, %eax
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	-32(%ebp), %eax
	cmpl	%eax, (%ecx)
	movl	-16(%ebp), %eax
	setl	%cl
	andl	$-17, %edx
	shrl	$31, %eax
	xorl	%eax, %ecx
	sall	$4, %ecx
	orl	%ecx, %edx
	movb	%dl, 1215(%esi)
	jmp	.L170
	.p2align 4,,7
	.p2align 3
.L176:
	addl	$8, %eax
	movl	%eax, -32(%ebp)
	jmp	.L171
	.p2align 4,,7
	.p2align 3
.L177:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	je	.L170
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L170
	.size	handler_adc, .-handler_adc
	.p2align 4,,15
	.type	handler_add, @function
handler_add:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L184
.L179:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L184:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -32(%ebp)
	je	.L185
.L180:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %ecx
	movl	-32(%ebp), %eax
	addl	-16(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L186
	andl	$1048576, %edi
	je	.L179
	movzbl	1215(%esi), %edx
	shrl	$31, %eax
	sall	$7, %eax
	andl	$127, %edx
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	(%ecx), %eax
	testl	%eax, %eax
	sete	%al
	andl	$-65, %edx
	sall	$6, %eax
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	-32(%ebp), %eax
	cmpl	%eax, (%ecx)
	setb	%al
	andl	$-33, %edx
	sall	$5, %eax
	orl	%eax, %edx
	movb	%dl, 1215(%esi)
	movl	-32(%ebp), %eax
	cmpl	%eax, (%ecx)
	movl	-16(%ebp), %eax
	setl	%cl
	andl	$-17, %edx
	shrl	$31, %eax
	xorl	%eax, %ecx
	sall	$4, %ecx
	orl	%ecx, %edx
	movb	%dl, 1215(%esi)
	jmp	.L179
	.p2align 4,,7
	.p2align 3
.L185:
	addl	$8, %eax
	movl	%eax, -32(%ebp)
	jmp	.L180
	.p2align 4,,7
	.p2align 3
.L186:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	je	.L179
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L179
	.size	handler_add, .-handler_add
	.p2align 4,,15
	.type	handler_rsb, @function
handler_rsb:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L193
.L188:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L193:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	je	.L194
.L189:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %eax
	movl	%eax, -32(%ebp)
	movl	-16(%ebp), %eax
	movl	-32(%ebp), %edx
	subl	-36(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%edx)
	je	.L195
	andl	$1048576, %edi
	je	.L188
	movl	%eax, %edx
	movzbl	1215(%esi), %eax
	shrl	$31, %edx
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	-16(%ebp), %ebx
	movl	(%edx), %edx
	testl	%edx, %edx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	cmpl	-36(%ebp), %ebx
	setae	%dl
	orl	%ecx, %eax
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	(%edx), %ecx
	shrl	$31, %ecx
	cmpl	-36(%ebp), %ebx
	setl	%dl
	andl	$-17, %eax
	xorl	%ecx, %edx
	sall	$4, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	jmp	.L188
	.p2align 4,,7
	.p2align 3
.L194:
	addl	$8, -36(%ebp)
	jmp	.L189
	.p2align 4,,7
	.p2align 3
.L195:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	.p2align 4,,2
	.p2align 3
	je	.L188
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L188
	.size	handler_rsb, .-handler_rsb
	.p2align 4,,15
	.type	handler_sub, @function
handler_sub:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%edi, -4(%ebp)
	movl	16(%ebp), %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	movl	%edi, %eax
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L202
.L197:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L202:
	leal	-20(%ebp), %eax
	movl	%edi, %edx
	leal	-16(%ebp), %ecx
	movl	%edi, %ebx
	movl	%eax, (%esp)
	movl	%esi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	shrl	$12, %ebx
	movl	$0, 4(%esp)
	andl	$15, %ebx
	movl	%esi, (%esp)
	call	GetStatusRegisterMode
	movl	-24(%ebp), %ecx
	movl	%edi, %edx
	shrl	$16, %edx
	andl	$15, %edx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%edx, %eax
	cmpl	$15, %edx
	movl	(%esi,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	je	.L203
.L198:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%esi,%eax,4), %eax
	movl	%eax, -32(%ebp)
	movl	-36(%ebp), %eax
	movl	-32(%ebp), %edx
	subl	-16(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%edx)
	je	.L204
	andl	$1048576, %edi
	je	.L197
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%esi), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	-16(%ebp), %ebx
	movl	(%edx), %ecx
	testl	%ecx, %ecx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	cmpl	%ebx, -36(%ebp)
	setae	%dl
	orl	%ecx, %eax
	sall	$5, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	movl	-32(%ebp), %edx
	movl	(%edx), %ecx
	shrl	$31, %ecx
	cmpl	%ebx, -36(%ebp)
	setl	%dl
	andl	$-17, %eax
	xorl	%ecx, %edx
	sall	$4, %edx
	orl	%edx, %eax
	movb	%al, 1215(%esi)
	jmp	.L197
	.p2align 4,,7
	.p2align 3
.L203:
	addl	$8, -36(%ebp)
	jmp	.L198
	.p2align 4,,7
	.p2align 3
.L204:
	movl	%esi, (%esp)
	call	FlushPipeline
	andl	$1048576, %edi
	.p2align 4,,2
	.p2align 3
	je	.L197
	movl	-24(%ebp), %eax
	movl	1148(%esi,%eax,4), %eax
	movl	%eax, 1212(%esi)
	jmp	.L197
	.size	handler_sub, .-handler_sub
	.p2align 4,,15
	.type	handler_eor, @function
handler_eor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L211
.L206:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L211:
	movl	16(%ebp), %edx
	leal	-20(%ebp), %eax
	leal	-16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%edi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%edi, (%esp)
	call	GetStatusRegisterMode
	movl	16(%ebp), %edx
	movl	-24(%ebp), %ecx
	movl	16(%ebp), %ebx
	shrl	$16, %edx
	movl	%ecx, %eax
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	movl	(%edi,%eax,4), %eax
	shrl	$12, %ebx
	andl	$15, %ebx
	cmpl	$15, %edx
	movl	(%eax), %esi
	je	.L212
.L207:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%edi,%eax,4), %ecx
	movl	%esi, %eax
	xorl	-16(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L213
	testl	$1048576, 16(%ebp)
	je	.L206
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%edi), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	movl	(%ecx), %ebx
	movl	-20(%ebp), %edx
	testl	%ebx, %ebx
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	andl	$1, %edx
	sall	$5, %edx
	orl	%ecx, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	jmp	.L206
	.p2align 4,,7
	.p2align 3
.L212:
	addl	$8, %esi
	jmp	.L207
	.p2align 4,,7
	.p2align 3
.L213:
	movl	%edi, (%esp)
	call	FlushPipeline
	testl	$1048576, 16(%ebp)
	.p2align 4,,2
	.p2align 3
	je	.L206
	movl	-24(%ebp), %eax
	movl	1148(%edi,%eax,4), %eax
	movl	%eax, 1212(%edi)
	jmp	.L206
	.size	handler_eor, .-handler_eor
	.p2align 4,,15
	.type	handler_and, @function
handler_and:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	shrl	$28, %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	CheckConditionFlag
	testl	%eax, %eax
	jne	.L220
.L215:
	movl	-12(%ebp), %ebx
	xorl	%eax, %eax
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L220:
	movl	16(%ebp), %edx
	leal	-20(%ebp), %eax
	leal	-16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	%edi, %eax
	call	AddressingMode1
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%edi, (%esp)
	call	GetStatusRegisterMode
	movl	16(%ebp), %edx
	movl	-24(%ebp), %ecx
	movl	16(%ebp), %ebx
	shrl	$16, %edx
	movl	%ecx, %eax
	andl	$15, %edx
	sall	$4, %eax
	addl	%edx, %eax
	movl	(%edi,%eax,4), %eax
	shrl	$12, %ebx
	andl	$15, %ebx
	cmpl	$15, %edx
	movl	(%eax), %esi
	je	.L221
.L216:
	sall	$4, %ecx
	leal	(%ecx,%ebx), %eax
	movl	(%edi,%eax,4), %ecx
	movl	%esi, %eax
	andl	-16(%ebp), %eax
	cmpl	$15, %ebx
	movl	%eax, (%ecx)
	je	.L222
	testl	$1048576, 16(%ebp)
	je	.L215
	shrl	$31, %eax
	movl	%eax, %edx
	movzbl	1215(%edi), %eax
	sall	$7, %edx
	andl	$127, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	movl	(%ecx), %esi
	movl	-20(%ebp), %edx
	testl	%esi, %esi
	sete	%cl
	andl	$-97, %eax
	sall	$6, %ecx
	andl	$1, %edx
	sall	$5, %edx
	orl	%ecx, %eax
	orl	%edx, %eax
	movb	%al, 1215(%edi)
	jmp	.L215
	.p2align 4,,7
	.p2align 3
.L221:
	addl	$8, %esi
	jmp	.L216
	.p2align 4,,7
	.p2align 3
.L222:
	movl	%edi, (%esp)
	call	FlushPipeline
	testl	$1048576, 16(%ebp)
	.p2align 4,,2
	.p2align 3
	je	.L215
	movl	-24(%ebp), %eax
	movl	1148(%edi,%eax,4), %eax
	movl	%eax, 1212(%edi)
	jmp	.L215
	.size	handler_and, .-handler_and
	.section	.rodata
	.align 32
	.type	datapr.3000, @object
	.size	datapr.3000, 128
datapr.3000:
	.long	handler_and
	.long	handler_and
	.long	handler_eor
	.long	handler_eor
	.long	handler_sub
	.long	handler_sub
	.long	handler_rsb
	.long	handler_rsb
	.long	handler_add
	.long	handler_add
	.long	handler_adc
	.long	handler_adc
	.long	handler_sbc
	.long	handler_sbc
	.long	handler_rsc
	.long	handler_rsc
	.long	0
	.long	handler_tst
	.long	0
	.long	handler_teq
	.long	0
	.long	handler_cmp
	.long	0
	.long	handler_cmn
	.long	handler_orr
	.long	handler_orr
	.long	handler_mov
	.long	handler_mov
	.long	handler_bic
	.long	handler_bic
	.long	handler_mvn
	.long	handler_mvn
	.ident	"GCC: (Ubuntu 4.3.2-1ubuntu12) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
