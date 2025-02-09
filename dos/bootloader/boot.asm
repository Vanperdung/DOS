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
    jmp CODE_SEG_INDEX:0x00100000 ; Jump to 32-bit code
    ; 0x00100000 is the address where the kernel is loaded (defined in dos/kernel/linker.ld)

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

times 510-($-$$) db 0 ; Fill the rest of sector with 0
dw 0xAA55 ; Boot signature