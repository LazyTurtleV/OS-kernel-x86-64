global idt_flush

bits 32

extern int_handler

idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret

%macro INT_HAND_NOERR 1
    global i%1h
    i%1h:
        cli
        push byte 0
        push byte %1
        jmp common_handler
%endmacro

%macro INT_HAND 1
    global i%1h
    i%1h:
        cli
        push byte %1
        jmp common_handler
%endmacro

INT_HAND_NOERR 0
INT_HAND_NOERR 1
INT_HAND_NOERR 2
INT_HAND_NOERR 3
INT_HAND_NOERR 4
INT_HAND_NOERR 5
INT_HAND_NOERR 6
INT_HAND_NOERR 7
INT_HAND 8
INT_HAND_NOERR 9
INT_HAND 10
INT_HAND 11
INT_HAND 12
INT_HAND 13
INT_HAND 14
INT_HAND_NOERR 15
INT_HAND_NOERR 16
INT_HAND_NOERR 17
INT_HAND_NOERR 18
INT_HAND_NOERR 19
INT_HAND_NOERR 20
INT_HAND_NOERR 21
INT_HAND_NOERR 22
INT_HAND_NOERR 23
INT_HAND_NOERR 24
INT_HAND_NOERR 25
INT_HAND_NOERR 26
INT_HAND_NOERR 27
INT_HAND_NOERR 28
INT_HAND_NOERR 29
INT_HAND_NOERR 30
INT_HAND_NOERR 31

CODE_SEG_OFFSET EQU 0x10

common_handler:
    pusha

    mov ax, ds
    push eax

    mov ax, CODE_SEG_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call int_handler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 8
    sti
    iret
