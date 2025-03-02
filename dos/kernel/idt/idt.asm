section .asm

extern int21h_handler
extern no_isr_handler

global idt_load
global int21h
global no_isr

idt_load:
    push ebp
    mov ebp, esp
    mov ebx, [ebp + 8]
    lidt [ebx]
    pop ebp
    ret

int21h:
    cli
    pushad
    call int21h_handler
    popad
    sti
    iret


no_isr:
    cli
    pushad
    call no_isr_handler
    popad
    sti
    iret