global lm_start

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

    mov dword [0xb8000], 0x2f4b2f4f
    
    hlt