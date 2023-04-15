.global R
.global calculate

.data
R: .zero 8


.text
calculate:
	ldr x0, A
	ldr x1, B
	ldr x2, C
	ldr x3, D
	mul x0, x0, x1
	mul x2, x2, x3
	add x0, x0, x2

	adr x5, R
	str x0, [x5]
	ret
