section .multiboot_header

MULTI_BOOT EQU 0xE85250d6
PROTECTED_MODE EQU 0
HEADER_LENGTH EQU header_end - header_start

header_start:
    dd MULTI_BOOT
    dd PROTECTED_MODE
    
    dd HEADER_LENGTH
    ;checksum
    dd 0x100000000 - (MULTI_BOOT + 0 + (HEADER_LENGTH))
    
    ;end tag
    dw 0
    dw 0
    dd 8
header_end: