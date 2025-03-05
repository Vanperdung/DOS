#include "kernel.h"
#include "text/text.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/heap.h"

void kernel_main(void)
{
    clear_screen();
    banner_init();

    idt_init();
    enable_interrupts();

    heap_mem_init();

    int *ptr = (int *)kmalloc(10000);
    int *ptr1 = (int *)kmalloc(100);

    char *ptr2 = (char *)kmalloc(10);

    if (ptr == NULL)
        print_str("Can't allocate memory for ptr");

    if (ptr1 == NULL)
        print_str("Can't allocate memory for ptr");

    if (ptr2 == NULL)
        print_str("Can't allocate memory for ptr");

    kfree(ptr);

    int *ptr3 = (int *)kmalloc(1000);

    kfree(ptr1);
    kfree(ptr2);
    kfree(ptr3);

}