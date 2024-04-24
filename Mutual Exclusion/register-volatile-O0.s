	.file	"register-volatile.c"
	.comm	j,4,4
	.comm	k,4,4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movl	$10, %ebx
	jmp	.L2
.L3:
	addl	$1, %ebx
.L2:
	cmpl	$99, %ebx
	jle	.L3
	movl	$20, j(%rip)
	jmp	.L4
.L5:
	movl	j(%rip), %eax
	addl	$1, %eax
	movl	%eax, j(%rip)
.L4:
	movl	j(%rip), %eax
	cmpl	$199, %eax
	jle	.L5
	movl	$30, k(%rip)
	jmp	.L6
.L7:
	movl	k(%rip), %eax
	addl	$1, %eax
	movl	%eax, k(%rip)
.L6:
	movl	k(%rip), %eax
	cmpl	$299, %eax
	jle	.L7
	movl	$0, %eax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
