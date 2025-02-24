ENTRY(_start) 
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x00100000; /* Load the program at 1MB */
    .text : ALIGN(4096)
    {
        *(.text) /* All text sections from all object files */
    }

    .rodata : ALIGN(4096)
    {
        *(.rodata) /* All rodata sections from all object files */
    }

    .data : ALIGN(4096)
    {
        *(.data) /* All data sections from all object files */
    }

    .bss : ALIGN(4096)
    {
        *(COMMON) /* All COMMON sections from all object files */
        *(.bss) /* All bss sections from all object files */
    }

    .asm : ALIGN(4096)
    {
        *(.asm) /* All asm sections from all object files */
    }
}