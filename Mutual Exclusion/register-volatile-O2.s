	.file	"register-volatile.c"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	movl	$20, j(%rip)
	movl	j(%rip), %eax
	cmpl	$199, %eax
	jg	.L3
	.p2align 4,,10
	.p2align 3
.L4:
	movl	j(%rip), %eax
	addl	$1, %eax
	movl	%eax, j(%rip)
	movl	j(%rip), %eax
	cmpl	$199, %eax
	jle	.L4
.L3:
	movl	$300, k(%rip)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.comm	k,4,4
	.comm	j,4,4
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
