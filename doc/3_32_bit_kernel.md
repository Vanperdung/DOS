# 32-bit Kernel

## Loading 32-bit Kernel

The kernel starts from the 2nd sector, it must be loaded into the address 0x00100000 by the bootloader.

### ATA PIO Mode

In the protected mode, the INT 13h can't be called directly, direct disk access might be the only solution.

We'll access the disk through the ports (CPU IO port bus) by communicating with the motherboard's hard disk controller following the ATA disk spec.

See [ATA operations](https://wiki.osdev.org/ATA_read/write_sectors) and [ATA mode](https://wiki.osdev.org/ATA_PIO_Mode)

### Testing

Now, we'll test the OS using the GDB.

```bash
$ gdb
```

Inside the GDB terminal, we need the add the symbol table of kernel.o to 0x100000. After that, we can debug the kernel just like we would do with any executables.

```bash
(gdb) add-symbol-file ./build/kernelfull.o 0x100000

(gdb) b _start

(gdb) target remote | qemu-system-x86_64 -S -gdb stdio -hda ./build/os.bin

(gdb) c

(gdb) layout asm

(gdb) stepi
```

### Memory Alignment

The C compiler aligns stack frames, data, etc., by a multiple of 4 bytes, because memory access of 32-bit processors is a lot faster when aligned. If the content of an object file is misaligned, it may cause unexpected errors. But our kernel.asm is not a C program, thus not aligned by default.

To properly align the kernelfull.o:

- Add the padding instruction at the end of kernel.asm so that it becomes 1-sector (512 bytes) long. 

- Make sure that kernel.asm.o is the first file to be linked. That ensures kernel.asm.o is located in the .text section (linker.ld) when linked, and always starts at 0x100000. kernel.asm.o is 512 bytes long, so any other C object files linked after that are automatically aligned (First defined in FILE variable in [Makefile](../dos/kernel/Makefile)).

- In other kernel assembly files, specify .asm section so that they are linked at the end of the object file. If the assembled code is not a multiple of 4 bytes, that's okay because those files are at the end.

```
[BITS 32]
section .asm
foo:
    jmp $

```