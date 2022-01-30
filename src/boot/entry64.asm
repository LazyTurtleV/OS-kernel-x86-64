global lm_start

extern kernel_main

section .text
bits 64
lm_start:
    ;clean an important registries up
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call kernel_main
    
    hlt