# Real Mode

Real mode is an operating mode of x86-compatible CPUs. It is characterized by:

- Direct access to all memory, I/O addresses, and hardware.
- A 16-bit segmented memory address space, allowing access to 1 MB of memory.
- No memory protection or multitasking capabilities.

Real mode is primarily used for bootstrapping and running legacy software.

## 1 MB of RAM accessible

- Memory access is done through the segmentation memory model
- Only 1 MB of RAM is accessible and addressable, it does not matter if you have 4 GB RAM

## No Security

- Provides no memory security
- Provides no hardware security
- Therefore, simple user program can destroy the operating system with no way for us to stop them

## [Segmentation Memory Model](https://wiki.osdev.org/Segmentation)

- Memory is accessed by a segment and an offset
- Programs can be loaded in different areas of memory but run without any problems
- Multiple segments are available through the use of segment registers

In Real Mode you use a logical address in the form A:B to address memory. This is translated into a physical address using the equation:

```
Physical address = (A * 0x10) + B
```

## Segment Registers

In Real Mode, the x86 architecture uses several segment registers to access different parts of memory. Each segment register points to a specific segment in memory:

- **CS (Code Segment):** Points to the segment containing the current program code. The instruction pointer (IP) uses this segment to fetch instructions.
- **DS (Data Segment):** Points to the segment where data is stored. This is the default segment for most data operations.
- **SS (Stack Segment):** Points to the segment containing the stack. The stack pointer (SP) and base pointer (BP) use this segment for stack operations.
- **ES (Extra Segment):** An additional data segment used for string and memory operations.
- **FS and GS:** Additional segment registers available in later x86 processors for general-purpose use.

These segment registers allow the CPU to access different areas of memory efficiently and are essential for the segmented memory model used in Real Mode.