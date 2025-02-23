ORG 0x7C00
BITS 16 ; 16-bit code, ensure the assembler only assemble 16-bit code

CODE_SEG_INDEX equ gdt_code_seg - gdt_start
DATA_SEG_INDEX equ gdt_data_seg - gdt_start

_start:
    jmp short start 
    nop

times 33 db 0 ; Fill the rest of sector with 0

start: ; Entry point
    jmp 0:second_stage 

second_stage:
    cli ; Clear interrupts

    mov ax, 0x0000 ; Load boot sector address to AX register
    mov ds, ax ; Load data segment to DS register
    mov es, ax ; Load data segment to ES register
    mov ss, ax ; Load stack segment to SS register
    mov sp, 0x07C0 ; Load stack pointer to SP register

    sti ; Set interrupts

.load_protected_mode:
    cli
    lgdt [gdt_descriptor] ; Load GDT
    mov eax, cr0
    or eax, 1
    mov cr0, eax ; Enable protected mode
    jmp CODE_SEG_INDEX:load32

; GDT
gdt_start:
gdt_null:
    dd 0x0 ; Null descriptor
    dd 0x0

gdt_code_seg:
    dw 0xFFFF ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base
    db 0x9A ; Access byte: Present, Ring 0, Code segment, Executable, Readable
    db 11001111b ; Flags (4-bit) + Limit (high 4-bit) (4KB granularity, 32-bit segment)
    db 0x0 ; Base

gdt_data_seg:
    dw 0xFFFF ; Limit
    dw 0x0 ; Base
    db 0x0 ; Base
    db 0x92 ; Access byte: Present, Ring 0, Data segment, Read/Write
    db 11001111b ; Flags (4-bit) + Limit (high 4-bit) (4KB granularity, 32-bit segment)
    db 0x0 ; Base

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Limit
    dd gdt_start ; Base

[BITS 32]
load32:
    mov eax, 1 ; Represent the sector we want to load from
    mov ecx, 100 ; Number of sectors to load
    mov edi, 0x00100000 ; Destination address we want to load into
    ; 0x00100000 is the address where the kernel is loaded (defined in dos/kernel/linker.ld)
    call ata_lba_read
    jmp CODE_SEG_INDEX:0x00100000 ; Jump to the kernel

ata_lba_read:
    mov ebx, eax ; Backup LBA
    ; Send the highest 8 bits of LBA to the hard disk controller
    shr eax, 24
    or eax, 0xE0 ; Select master drive
    mov dx, 0x1F6
    out dx, al
    ; Finished sending

    ; Send the total sector to the hard disk controller
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    ; Finished sending

    ; Send more bits of the LBA
    mov eax, ebx
    mov dx, 0x1F3
    out dx, al
    ; Finished sending

    ; Send more bits of the LBA
    mov dx, 0x1F4
    mov eax, ebx
    shr eax, 8
    out dx, al
    ; Finished sending

    ; Send more bits of the LBA
    mov dx, 0x1F5
    mov eax, ebx
    shr eax, 16
    out dx, al
    ; Finished sending

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    ; Read all sectors into memory
.next_sector:
    push ecx
.try_again:
    mov dx, 0x1F7
    in al, dx
    test al, 8
    jz .try_again

    ; Read 256 words (512 bytes = 1 sector = 256 words) at a time and store it at address specified by ES:EDI
    mov ecx, 256
    mov dx, 0x1F0
    rep insw ; Input word from I/O port specified in DX into memory location specified in ES:EDI
    pop ecx
    loop .next_sector

    ; End of reading sectors into memory
    ret

times 510-($-$$) db 0 ; Fill the rest of sector with 0
dw 0xAA55 ; Boot signature