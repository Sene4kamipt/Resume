.intel_syntax noprefix
.global dot_product
.text

dot_product:
    vxorps xmm0, xmm0, xmm0
    while_can_read_8:
        cmp rdi, 8
        jl end
        vmovups ymm2, [4*rdi-32+rsi]
        vmovups ymm1, [4*rdi-32+rdx]
        
        vmulps ymm2, ymm2, ymm1
        vhaddps ymm2, ymm2, ymm2
        vhaddps ymm2, ymm2, ymm2
        
	vextractf128 xmm3, ymm2, 0
        vextractf128 xmm2, ymm2, 1
	vaddss xmm0, xmm0, xmm3 
	vaddss xmm0, xmm0, xmm2
        
        sub rdi, 8
        jmp while_can_read_8
    end:
        cmp rdi, 4
        jl last_end
        
        vmovups xmm2, [4*rdi -16+rsi]
        vmovups xmm1, [4*rdi-16+rdx]
        
        vmulps xmm2, xmm2, xmm1
        vhaddps xmm2, xmm2, xmm2
        vhaddps xmm2, xmm2, xmm2
        
        vaddss xmm0, xmm0, xmm2
        
        sub rdi, 4
    last_end:
        cmp rdi, 0
        je exit
        
        movups xmm2, [4*rdi-4+rsi]
        movups xmm1, [4*rdi-4+rdx]
        mulss xmm1, xmm2
        addss xmm0, xmm1
        
        sub rdi, 1
        jmp last_end
        
    exit:
        ret
