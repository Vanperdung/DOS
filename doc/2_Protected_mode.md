# Protected Mode

Protected mode is an operational mode of x86 processors that provides advanced features like virtual memory, access control, memory protection and much more.

## Protected Mode vs Real Mode

| Feature                      | **Real Mode**                                  | **Protected Mode**                               |
|------------------------------|----------------------------------------------|------------------------------------------------|
| **Memory Access**            | Limited to **1 MB** (20-bit addressing)      | Can access **up to 4 GB (32-bit) or more with paging** |
| **Segmentation**             | Uses **segment:offset** addressing (e.g., `CS:IP`) | Uses a **flat memory model** or advanced segmentation (GDT) |
| **Multitasking**             | ❌ No multitasking support                   | ✅ Allows multitasking                         |
| **Memory Protection**        | ❌ No protection, programs can overwrite any memory | ✅ Prevents programs from accessing others' memory (via segmentation and paging) |
| **Paging Support**           | ❌ No                                        | ✅ Yes (virtual memory support)               |
| **Privilege Levels (Security)** | ❌ Single privilege level (everything runs in Ring 0) | ✅ Supports **4 privilege levels** (Ring 0–3) for security |
| **32-bit / 64-bit Execution** | ❌ Only supports 16-bit instructions        | ✅ Supports **32-bit (protected mode)** and transitions to **64-bit (long mode)** |
| **Interrupt Handling**       | Uses the **Interrupt Vector Table (IVT)**    | Uses the **Interrupt Descriptor Table (IDT)** |
| **Speed & Efficiency**       | ❌ Slow due to segmentation and limited memory | ✅ Faster due to direct memory access and better memory management |
| **Modern OS Support**        | ❌ Only useful for legacy code (like bootloaders) | ✅ Required for all modern OSes               |

## Memory Protection

The feature of memory protection is preventing other processes from accessing the memory they don't own, reducing the crashes and security risks.

This feature is achieved using:

### Global Descriptor Table

The Global Descriptor Table (GDT) is a fundamental data structure in x86 arch, particularly in protected mode.

It defines the characteristic of various memory segments during the program execution, including base address, limit (size), access privilege.

The memory segments are the code segment, data segment, task state segment (TSS) or the local descriptor table (LDT).

Important terminologies:

- Segment: A logically contiguous chunk of memory with consistent properties (from the CPU's perspective).
- Segment Register: A register of your CPU that refers to a segment for a particular purpose (CS, DS, SS, ES) or for general use (FS, GS)
- Segment Selector: A reference to a descriptor, which you can load into a segment register; the selector is an offset into a descriptor table pointing to one of its entries.
- Segment Descriptor: An entry in a descriptor table. These are a binary data structure that tells the CPU the attributes of a given segment.

<img src="./img/2_Segment_descriptor.png" alt="Segment descriptor" width="500" height="300">

For more details, see [Global Descriptor Table](https://wiki.osdev.org/Global_Descriptor_Table)

### Paging (CR3 & Page Tables)

See [Address Translation](2_1_Address_translation.md)

## Hardware Protection

Protected mode protects hardware resources using privilege levels (Rings) and special registers.

<img src="./img/2_Protection_ring.png" alt="Protection ring" width="700" height="500">