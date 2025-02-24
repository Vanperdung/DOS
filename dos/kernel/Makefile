export PREFIX="${HOME}/opt/cross"
export TARGET=i686-elf
export PATH := $(PREFIX)/bin:$(shell echo $$PATH)

all: ../build/kernel.bin
	dd if=../build/kernel.bin >> ../build/os.bin
# The os.bin file should be larger than one sector (512 bytes) to be bootable.
	dd if=/dev/zero bs=512 count=100 >> ../build/os.bin

../build/kernel.asm.o: kernel.asm
	nasm -f elf32 -g kernel.asm -o ../build/kernel.asm.o

../build/kernel.bin: ../build/kernel.asm.o
# Linking the Assembly Object File
	i686-elf-ld -g -relocatable ../build/kernel.asm.o -o ../build/kernel.o 
# Linking the Kernel Binary
# -T linker.ld → Specifies the linker script (linker.ld), which tells the linker where to place different sections in memory.
# -ffreestanding → Indicates that the code doesn’t rely on a standard C runtime (important for OS development).
# -O0 → No optimization (useful during development for debugging).
# -nostdlib → Do not use the standard C library (libc), as it's not available in a bare-metal environment.
	i686-elf-gcc -T linker.ld -o ../build/kernel.bin -ffreestanding -O0 -nostdlib ../build/kernel.o
