## FIXED INIT
	.section	__TEXT,__cstring,cstring_literals
printintstr: .asciz	"%d"
printstringstr: .asciz "%s"
scanfintstr: .asciz "%d"

	.section	__TEXT,__text,regular,pure_instructions

## TAC_BEGINFUN
	.globl	_main
_main: 
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string0(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_ENTRADA
	leaq	scanfintstr(%rip), %rdi
	movq	__temp0@GOTPCREL(%rip), %rsi
	movb	$0, %al
	callq	_scanf

## TAC_MOVE
	movl	__temp0(%rip), %eax
	movl	%eax, _a(%rip)

## TAC_MOVE_VEC
	movl	_5(%rip), %eax
	movl	%eax, _v(%rip)

## TAC_GRT
	movl	_b(%rip), %eax
	cmpl	_0(%rip), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp3(%rip)

## TAC_IFZ
	movl	__temp3(%rip), %eax
	andl	$1, %eax
	jz	__label2

## TAC_LABEL
	 __label1:

## TAC_GE
	movl	_a(%rip), %eax
	cmpl	_0(%rip), %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp2(%rip)

## TAC_IFZ
	movl	__temp2(%rip), %eax
	andl	$1, %eax
	jz	__label0

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string1(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_VECINDEX
	movl	_a(%rip), %eax
	movl	%eax, _v(%rip)

## TAC_LELE	(int)
	leaq	printintstr(%rip), %rdi
	movl	_v(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string2(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string3(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(int)
	leaq	printintstr(%rip), %rdi
	movl	_c(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string2(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_SUB
	movl	_a(%rip), %eax
	subl	_1(%rip), %eax
	movl	%eax, __temp1(%rip)

## TAC_MOVE
	movl	__temp1(%rip), %eax
	movl	%eax, _a(%rip)

## TAC_JUMP
	jmp	__label1

## TAC_LABEL
	 __label0:

## TAC_LABEL
	 __label2:

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string4(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_VECINDEX
	movl	_0(%rip), %eax
	movl	%eax, _v(%rip)

## TAC_LELE	(int)
	leaq	printintstr(%rip), %rdi
	movl	_v(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string2(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_ENDFUN
	popq	%rbp
	retq

## TAC_BEGINFUN
	.globl	_teste
_teste: 
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_ARG
	movl %eax, _a(%rip)

## TAC_CALL
	callq _fnc
	movl	%eax, __temp4(%rip)

## TAC_MOVE
	movl	__temp4(%rip), %eax
	movl	%eax, _b(%rip)

## TAC_RET
	movl	_8(%rip), %eax
	popq	%rbp
	retq

## TAC_ENDFUN
	popq	%rbp
	retq

## TAC_BEGINFUN
	.globl	_fnc
_fnc: 
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string5(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(int)
	leaq	printintstr(%rip), %rdi
	movl	_a(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string2(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_LELE	(string)
	leaq	printstringstr(%rip), %rdi
	leaq	_string6(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_ADD
	movl	_4(%rip), %eax
	addl	_5(%rip), %eax
	movl	%eax, __temp5(%rip)

## TAC_RET
	movl	__temp5(%rip), %eax
	popq	%rbp
	retq

## TAC_ENDFUN
	popq	%rbp
	retq

## DATA SECTION
	.section	__DATA,__data
_0:	.long	0
_1:	.long	1
_2:	.long	2
_3:	.long	3
_4:	.long	4
_5:	.long	5
_6:	.long	6
_7:	.long	7
_8:	.long	8
_9:	.long	9
_a:	.long	1
_b:	.long	2
_c:	.long	6
__temp4:	.long	0
_i:	.long	1
_v:
	.long	0
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	8
	.long	9
_string4:	.string	"\nO vetor fica "
_string3:	.string	"c vale "
__temp2:	.long	0
__temp0:	.long	0
_10:	.long	10
__temp5:	.long	0
_string6:	.string	"Vou retornar o valor do contador \n"
_100:	.long	100
__temp3:	.long	0
_string5:	.string	"X vale: "
_a.5:	.long	'a'
_string0:	.string	"Digite um numero: \n"
_string1:	.string	"Percorrendo o vetor ao contrario fica assim: "
__temp1:	.long	0
_string2:	.string	"\n"
