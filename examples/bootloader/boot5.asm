ORG 0
BITS 16 ; 16-bit code, ensure the assembler only assemble 16-bit code

_start:
    jmp short start 
    nop

times 33 db 0 ; Fill the rest of sector with 0

start: ; Entry point
    jmp 0x07C0:second_stage

second_stage:
    cli ; Clear interrupts

    mov ax, 0x07C0 ; Load boot sector address to AX register
    mov ds, ax ; Load data segment to DS register
    mov es, ax ; Load data segment to ES register

    mov ax, 0x0000
    mov ss, ax ; Load stack segment to SS register
    mov sp, 0x07C0 ; Load stack pointer to SP register

    sti ; Set interrupts

    mov ah, 0x02 ; Read disk command
    mov al, 0x01 ; Number of sectors to read
    mov ch, 0x00 ; Cylinder number
    mov cl, 0x02 ; Sector number
    mov dh, 0x00 ; Head number
    mov bx, buffer ; Buffer address
    int 0x13 ; Call BIOS disk interrupt

    jc error ; If carry flag is set, jump to error

    mov si, buffer ; Load buffer address to SI register
    call print ; Call print function

    jmp $ ; Infinite loop

error:
    mov si, error_message ; Load error message address to SI register
    call print ; Call print function
    ret

print: ; Print function
    mov bx, 0 ; Page number
.loop:
    lodsb ; Load byte from DS:SI to AL and increment SI
    cmp al, 0 ; Check if AL is null
    je .done ; If AL is null, jump to done
    mov ah, 0x0E ; BIOS teletype function
    int 0x10 ; Call BIOS (http://www.ctyme.com/intr/rb-0106.htm)
    jmp .loop ; Loop
.done:
    ret ; Return

error_message: db 'Error reading disk', 0 ; Null-terminated string

times 510-($-$$) db 0 ; Fill the rest of sector with 0
dw 0xAA55 ; Boot signature

buffer: