## FIXED INIT
    .section	__TEXT,__cstring,cstring_literals
printintstr: .asciz	"%d"
printstringstr: .asciz "teste"
    .section	__TEXT,__text,regular,pure_instructions

## TAC_BEGINFUN
	.globl	_main 
_main:                                                            
    pushq	%rbp
	movq	%rsp, %rbp

## TAC_LELE
	leaq	printstringstr(%rip), %rsi
	movb	$0, %al
	callq	_printf
    
## TAC_ADD
	movl	_a(%rip), %esi
	addl	_b(%rip), %esi

## TAC_MUL
	movl	_a(%rip), %eax
	imull	_b(%rip), %eax

## TAC_SUB
	movl	_a(%rip), %eax
	subl	_b(%rip), %eax
	movl	%eax, _a(%rip)

## TAC_DIV
	movl	_a(%rip), %eax
	cltd
	idivl	_b(%rip)
	movl	%eax, _a(%rip)

## TAC_LST
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_GRT
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_LE
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_GE
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_EQ
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_DIF
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, _a(%rip)

## TAC_ENTRADA
	leaq	L_.str(%rip), %rdi
	movq	_a@GOTPCREL(%rip), %rsi
	movb	$0, %al
	callq	_scanf

## TAC_MOVE
	movl	_b(%rip), %eax
	movl	%eax, _a(%rip)
	xorl	%eax, %eax

## TAC_ENDFUN
	popq	%rbp
	retq

## DATA SECTION
	.section	__DATA,__data
_a: .long	6        


