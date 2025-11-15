section .text
global _start
extern main
extern mc_getargc
extern mc_getargv
extern mc_getenvp
extern mc_doexit

extern __init_array_start
extern __init_array_end

_start:
    call mc_getargc
    mov rdi, rax        ; argc
    call mc_getargv
    mov rsi, rax        ; argv
    call mc_getenvp
    mov rdx, rax        ; envp

    mov rbx, __init_array_start
    mov rcx, __init_array_end
.init_loop:
    cmp rbx, rcx
    jge .done_init
    mov rax, [rbx]
    call rax
    add rbx, 8
    jmp .init_loop
.done_init:

    call main

    mov rdi, rax
    call mc_doexit

hang:
    jmp hang
