.intel_syntax noprefix

.text
.global sum

sum:
	mov eax, [rdx]  
	add eax, [rsi]
	mov [rcx], eax
	add rdx, 4
	add rsi, 4
	add rcx, 4

	sub rdi, 1
    cmp rdi, 0
	jnz sum
	ret
