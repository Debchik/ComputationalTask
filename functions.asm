section .data
    c1 dq 0.35
    c2 dq 0.95
    c3 dq 2.7
    dc1 dq 0.7
    b1 dq 3.0
    a1 dq 2.0
    x dq 1.0
    st db `%lf\n`, 0

section .text
global f1
global f1_deriv
global f2
global f2_deriv
global f3
global f3_deriv
f1:
    push ebp
    mov ebp, esp
    sub esp, 24
    
    fld qword[c3]
    fld qword[ebp + 8]
    fld qword[c2]
    fld qword[c1]
    fld qword[ebp + 8]
    fmulp
    fsubp
    fchs
    fmulp
    faddp
    
    
    add esp, 24
    mov esp, ebp
    pop ebp
    ret

f1_deriv:
    push ebp
    mov ebp, esp
    
    fld qword[c2]
    fld qword[dc1]
    fld qword[ebp + 8]
    fmulp
    fsubp
    fchs
    
    mov esp, ebp
    pop ebp
    ret
    
f2:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[b1]
    fld qword[ebp + 8]
    fmulp
    faddp
    
    mov esp, ebp
    pop ebp
    ret

f2_deriv:
    push ebp
    mov ebp, esp
    
    fld qword[b1]
    
    mov esp, ebp
    pop ebp
    ret

f3:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[a1]
    fld qword[ebp + 8]
    faddp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

f3_deriv:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[a1]
    fld qword[ebp + 8]
    faddp
    fdivp
    fst qword[esp - 8]
    fld qword[esp - 8]
    fmulp
    fchs
    
    mov esp, ebp
    pop ebp
    ret

