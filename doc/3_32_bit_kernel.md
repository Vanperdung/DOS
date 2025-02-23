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
(gdb) add-symbol-file ./build/kernel.o 0x100000

(gdb) b _start

(gdb) target remote | qemu-system-x86_64 -S -gdb stdio -hda ./build/os.bin

(gdb) c

(gdb) layout asm

(gdb) stepi
```