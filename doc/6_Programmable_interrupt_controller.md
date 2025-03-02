# Programmable Interrupt Controller

Programmable Interrupt Controller allows different types of hardware to interrupt the processor, such as keyboard, hardisk. This is the most important chips that make up x86 architecture.

For example, the Industry Standard Architecture (ISA) defines IRQ 0 as a timer interrupt, IRQ 1 as a keyboard interrupt, and so on. IRQs will communicate with PIC, and PIC will raise the interrupt line which is connected to the processor.

The system has two PICs, one for master ports and other for slave ports. The master ports handle IRQs 0-7 and slave ports handle IRQs 8-15. The master PIC control ports are 0x20 (command) and 0x21 (data), and the slave PIC control ports are 0xA0 (command) and 0xA1 (data).

In protected mode, some IRQs are mapped to interrupts 8-15, but this is a problem as these interrupts are reserved in protected mode for exceptions. For that reason, We need to remap the PIC. Without remapping, it would be difficult to distinguish between software errors and IRQs.

A common choice is to remap IRQs to the beginning of the available INT range, which is INT 0x20 for the master and INT 0x28 for the slave.

In conclusion, PIC:

- Allows hardware to interrupt the processor
- Programmable
- Requires interrupt ACK

See also: [PIC](http://wiki.osdev.org/8259_PIC)

## Interrupt Acknowledgment

Whenever a PIC calls us (the kernel) that an interrupt has happened, we must acknowledge that we have handled the interrupt. If we don't respond, PIC will never call us again for other interrupts. For this reason, we implement `int_noop_handler` which acknowledges the interrupts without doing anything.

## Handling The Interrupts

Assuming we've remapped IRQ 0 to 0x20, that means we'll receive timer interrupts (IRQ 0) as INT 0x20, keyboard interrupt (IRQ 1) as 0x21, and so on.

Previously, we implemented IDT (Interrupt Descriptor Table) where we define the mapping between exceptions and their handlers. This is the time we start using IDT. We can define IDT for INT 0x21, for example, to handle the keyboard interrupts.

However, before handling the interrupt, we'll need to disable interrupts while in the handler block, store the register contents before handling the interrupt so that we can go back to the previous state, and enable interrupts again. For these reasons, just calling idt_set with a C function to its argument isn't enough. We'll create a wrapper in assembly for that. See [idt.asm](../dos/kernel/idt/idt.asm)

Also, remember that we need to respond with acknowledgment to IRQ from PIC. For now, we just call outb(0x20, 0x20).

## Multi-Tasking?

Imagine handling IRQ 0 timer interrupts (mapped to INT 20h) will allow us to switch between tasks, which will create an illusion of a multi-tasking system even on a single-core processor.


