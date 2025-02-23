all:
	nasm -f bin boot.asm -o ../build/boot.bin
	if [ -f ../build/os.bin ]; then rm -rf ../build/os.bin; fi
	dd if=../build/boot.bin >> ../build/os.bin