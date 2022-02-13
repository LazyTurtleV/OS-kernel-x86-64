global gdt_flush

CODE_SEG_OFFSET EQU 0x10
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, CODE_SEG_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    push .flush
    retf
.flush
    ret