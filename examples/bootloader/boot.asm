; Compile: nasm -f bin boot.asm -o boot.bin
; Run: qemu-system-x86_64 -hda boot.bin
; This is a simple boot sector that prints 'D' on the screen, the BIOS finds the boot signature (0x55AA) at the end of the sector and loads the boot sector to 0x7C00

ORG 0x7C00 ; BIOS loads boot sector to 0x7C00
BITS 16 ; 16-bit code, ensure the assembler only assemble 16-bit code

start: ; Entry point
    mov ah, 0x0E ; BIOS teletype function
    mov al, 'D' ; Character to print 
    mov bx, 0x00 ; Page number
    int 0x10 ; Call BIOS (http://www.ctyme.com/intr/rb-0106.htm)

    jmp $ ; Infinite loop

times 510-($-$$) db 0 ; Fill the rest of sector with 0
dw 0xAA55 ; Boot signature