FILE = ../build/kernel.asm.o ../build/kernel.o ../build/text.o
INCLUDE = -I.
C_FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parammeter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc -std=gnu99

all: ../build/kernel.bin
	dd if=../build/kernelfull.bin >> ../build/os.bin
# The os.bin file should be larger than one sector (512 bytes) to be bootable.
	dd if=/dev/zero bs=512 count=100 >> ../build/os.bin

../build/kernel.bin: ${FILE}
# Linking the Assembly Object Files
	i686-elf-ld -g -relocatable ${FILE} -o ../build/kernelfull.o 
# Linking the Kernel Binary
# -T linker.ld → Specifies the linker script (linker.ld), which tells the linker where to place different sections in memory.
# -ffreestanding → Indicates that the code doesn’t rely on a standard C runtime (important for OS development).
# -O0 → No optimization (useful during development for debugging).
# -nostdlib → Do not use the standard C library (libc), as it's not available in a bare-metal environment.
	i686-elf-gcc ${C_FLAGS} -T linker.ld -o ../build/kernelfull.bin ../build/kernelfull.o

../build/kernel.asm.o: kernel.asm
	nasm -f elf32 -g kernel.asm -o ../build/kernel.asm.o

../build/kernel.o: kernel.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c kernel.c -o ../build/kernel.o

../build/text.o: text/text.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c text/text.c -o ../build/text.o