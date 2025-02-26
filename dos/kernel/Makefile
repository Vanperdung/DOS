FILE = ../build/kernel.asm.o ../build/kernel.o ../build/text.o ../build/idt.asm.o ../build/idt.o ../build/vendor_intrs.o ../build/mem_utils.o 
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
	i686-elf-gcc ${C_FLAGS} -T linker.ld -o ../build/kernelfull.bin ../build/kernelfull.o

../build/kernel.asm.o: kernel.asm
	nasm -f elf32 -g kernel.asm -o ../build/kernel.asm.o

../build/kernel.o: kernel.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c kernel.c -o ../build/kernel.o

../build/text.o: text/text.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c text/text.c -o ../build/text.o

../build/idt.asm.o: idt/idt.asm
	nasm -f elf32 -g idt/idt.asm -o ../build/idt.asm.o

../build/idt.o: idt/idt.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c idt/idt.c -o ../build/idt.o

../build/vendor_intrs.o: idt/vendor_intrs.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c idt/vendor_intrs.c -o ../build/vendor_intrs.o

../build/mem_utils.o: utils/mem_utils.c
	i686-elf-gcc ${INCLUDE} ${C_FLAGS} -std=gnu99 -c utils/mem_utils.c -o ../build/mem_utils.o

