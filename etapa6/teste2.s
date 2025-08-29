	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 13, 0
	.globl	_teste                          ## -- Begin function teste
	.p2align	4, 0x90
_teste:                                 ## @teste
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	$9, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	_a(%rip), %edi
	callq	_teste
	movl	%eax, _c(%rip)
	cmpl	$9, _c(%rip)
	jne	LBB1_5
## %bb.1:
	jmp	LBB1_2
LBB1_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	_a(%rip), %esi
	addl	$1, %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	_c(%rip), %eax
	subl	$1, %eax
	movl	%eax, _c(%rip)
## %bb.3:                               ##   in Loop: Header=BB1_2 Depth=1
	cmpl	$0, _c(%rip)
	jg	LBB1_2
## %bb.4:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB1_6
LBB1_5:
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB1_6:
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_a                              ## @a
	.p2align	2
_a:
	.long	2                               ## 0x2

	.globl	_b                              ## @b
	.p2align	2
_b:
	.long	1                               ## 0x1

	.globl	_c                              ## @c
	.p2align	2
_c:
	.long	4                               ## 0x4

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"

L_.str.1:                               ## @.str.1
	.asciz	"\nAqui"

L_.str.2:                               ## @.str.2
	.asciz	"\nTeste"

L_.str.3:                               ## @.str.3
	.asciz	"\nOi"

.subsections_via_symbols
