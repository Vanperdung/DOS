[BITS 32] ; Switch to 32-bit code
global _start ; Make _start global so it can be seen from linker script

extern kernel_main

CODE_SEG_INDEX equ 0x08
DATA_SEG_INDEX equ 0x10

_start:
    mov ax, DATA_SEG_INDEX
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000 ; Set stack pointer to 2MB
    mov esp, ebp    

    ; Enable A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    call kernel_main
    
    jmp $

times 512-($-$$) db 0 ; Ensure the kernel.asm has 512 bytes long
