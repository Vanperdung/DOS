#include "kernel.h"
#include "text/text.h"
#include "idt/idt.h"
#include "io/io.h"

void kernel_main(void)
{
    clear_screen();
    banner_init();

    idt_init();
}