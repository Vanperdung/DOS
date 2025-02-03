all:
	rm -f boot5.bin
	nasm -f bin -o boot5.bin boot5.asm
	dd if=./boot5.txt >> boot5.bin
	dd if=/dev/zero bs=512 count=1 >> boot5.bin