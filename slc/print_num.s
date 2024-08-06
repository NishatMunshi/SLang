; prints 64 bit unsigned integer in rax, modifies rax, rbx, rdx, rdi, rsi
global print_num
print_num:
    ; setup stack frame
    push rbp
    mov rbp, rsp
    
    ; actual function
    mov rbx, 10     ; divisor
    push 10         ; '\n', marks the end of printing the number
digits:
    xor rdx, rdx    ; zero out the upper 8 bytes of rdx:rax
    div rbx         ; divide by 10
    add rdx, '0'    ; get a char out of remainder
    push rdx        ; save this digit
    or rax, rax     ; check if quotient is zero
    jnz digits      ; if quotient == 0 we're done

print:
    mov rax, 1      ; write call number, __NR_write from unistd_64.h
    mov rdi, 1      ; write to stdout (int fd=1)
    mov rsi, rsp    ; use char on stack
    mov rdx, 1      ; size_t len = 1 char to write.
    syscall         ; call the kernel, it looks at registers to decide what to do
    pop rdx         ; pop this digit
    sub rdx, 10     ; test if it is '\n'
    jnz print       ; if it is '\n', we are done

    ; return
    mov rsp, rbp
    pop rbp 
    ret
