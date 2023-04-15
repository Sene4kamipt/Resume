.intel_syntax noprefix
.global avx_sin
.text

avx_sin:
    movsd xmm7, xmm0
    vxorps xmm1, xmm1, xmm1
    vsubsd xmm1, xmm1, xmm7
    vmulsd xmm1, xmm1, xmm7
    vxorps xmm2, xmm2, xmm2
    vxorps xmm4, xmm4, xmm4
    mov rax, 1
    movsd xmm4, xmm7
    while_anything_to_add:
        comisd xmm2, xmm0
        je end
       
        movsd xmm2, xmm0
           
        add rax, 1
        cvtsi2sd xmm3, rax
        vdivsd xmm4, xmm4, xmm3
        add rax, 1
        cvtsi2sd xmm3, rax
        vdivsd xmm4, xmm4, xmm3

        vmulsd xmm4, xmm4, xmm1
        vaddsd xmm0, xmm0, xmm4
        
        jmp while_anything_to_add
    end:
        ret
