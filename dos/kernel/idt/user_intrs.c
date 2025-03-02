#include "user_intrs.h"
#include "text/text.h"
#include "io/io.h"

void no_isr_handler(void)
{
    // print_str("No interrupt handler");
    outb(0x20, 0x20);
}

void int21h_handler(void)
{
    print_str("Keyboard interrupt");
    outb(0x20, 0x20); // EOI (Interrupt Acknowledge)
}