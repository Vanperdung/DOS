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

See [Global Descriptor Table](2_2_Global_descriptor_table.md)

### Paging (CR3 & Page Tables)

See [Address Translation](2_1_Address_translation.md)

## Hardware Protection

Protected mode protects hardware resources using privilege levels (Rings) and special registers.

<img src="./img/2_Protection_ring.png" alt="Protection ring" width="700" height="500">

NEED TO BE COMPLETED

## Entering Protected Mode

