.intel_syntax noprefix

.section .rodata
format_scanf: .string "%d"
format_printf: .string "%lld\n"

.text
.global very_important_function

very_important_function:
	push rbp
	mov rbp, rsp
	
	push r12
	push r13
	push r14
	sub rsp, 8
	mov r13, A
	mov r12, rdi

loop_part:
	mov rdi, offset format_scanf
	mov rsi, rsp
	call scanf

	movsxd rax, [rsp]
	movsxd r14, [r13]
	imul rax, r14
	add r13, 4
	
	mov rdi, offset format_printf
	mov rsi, rax
	call printf

	dec r12
	jnz loop_part
	
	add rsp, 8
	pop r14
	pop r13
	pop r12
	pop rbp
	ret
