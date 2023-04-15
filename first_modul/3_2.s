.text
.global solve

solve:

mov w8, 0
loop:
    madd w9, w0, w8, w1
    madd w9, w9, w8, w2
    madd w9, w9, w8, w3
    add w8, w8, 1
    cmp w9, 0
    bne loop
mov w0, w8
sub x0, x0, 1
ret

