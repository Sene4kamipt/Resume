.text
.global sum

sum:
    loop:
        ldr w3, [x2]
        add w0, w0, w3
        add x2, x2, 4
        sub x1, x1, 1
        cmp x1, 0
        bne loop

    ret

