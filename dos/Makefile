all: build kernel
	@echo "Building DOS done!"

build:
	mkdir -p build

bootloader: 
	@echo "Building bootloader..."
	make -C bootloader

kernel: bootloader
	@echo "Building kernel..."
	make -C kernel

clean:
	rm -rf build

.PHONY: bootloader kernel