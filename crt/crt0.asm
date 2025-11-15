section .text
global _start
extern main
extern mc_getargc
extern mc_getargv
extern mc_getenvp
extern mc_doexit

_start:
    call mc_getargc
    mov rdi, rax        ; argc

    call mc_getargv
    mov rsi, rax        ; argv

    call mc_getenvp
    mov rdx, rax        ; envp

    call main

    mov rdi, rax        ; exit code
    call mc_doexit

hang:
    jmp hang            ; never return
