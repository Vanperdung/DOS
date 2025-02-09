ENTRY(_start) 
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x00100000; /* Load the program should be loaded at 1MB */
    .text :
    {
        *(.text) /* All text sections from all object files */
    }

    .rodata :
    {
        *(.rodata) /* All rodata sections from all object files */
    }

    .data :
    {
        *(.data) /* All data sections from all object files */
    }

    .bss :
    {
        *(COMMON) /* All COMMON sections from all object files */
        *(.bss) /* All bss sections from all object files */
    }
}