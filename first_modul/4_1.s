.global main

.data
Scan: .string "%i %i"
Print: .string "%i"

.text
main:	
	sub sp, sp, 8
	str x30, [sp, 8]
	
	adr x0, Scan
	add x1, sp, 4
	mov x2, sp
	bl scanf

	ldr w1, [sp, 4]
	ldr w2, [sp]
	add w1, w1, w2
 
	adr x0, Print
	bl printf

	ldr x30, [sp, 8]
	add sp, sp, 8

	mov w0, 0
	ret
