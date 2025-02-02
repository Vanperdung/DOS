; This is a simple boot sector that prints "Hello, World!" to the screen

ORG 0x7C00 ; BIOS loads boot sector to 0x7C00
BITS 16 ; 16-bit code, ensure the assembler only assemble 16-bit code

start: ; Entry point
    mov si, message ; Load message address to SI register
    call print ; Call print function

    jmp $ ; Infinite loop

print: ; Print function
    mov bx, 0 ; Page number
.loop:
    lodsb ; Load byte from SI to AL and increment SI
    cmp al, 0 ; Check if AL is null
    je .done ; If AL is null, jump to done
    mov ah, 0x0E ; BIOS teletype function
    int 0x10 ; Call BIOS (http://www.ctyme.com/intr/rb-0106.htm)
    jmp .loop ; Loop
.done:
    ret ; Return

message: db 'Hello, World!', 0 ; Null-terminated string

times 510-($-$$) db 0 ; Fill the rest of sector with 0
dw 0xAA55 ; Boot signature