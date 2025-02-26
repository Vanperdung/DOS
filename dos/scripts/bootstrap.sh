#! /bin/bash
# This script is used to bootstrap the project. It will install all the necessary dependencies and set up the project for development.

sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev

# Set up the cross compiler environment
export PREFIX="${HOME}/opt/cross"
export TARGET=i686-elf
export PATH="${PREFIX}/bin:${PATH}"

cd $HOME
mkdir -p src && cd src

if [ ! -d "binutils-2.35" ]; then
    # Download binutils
    wget https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.xz
    tar -xf binutils-2.35.tar.xz
fi

if [ ! -d "gcc-10.2.0" ]; then
    # Download gcc
    wget http://ftp.lip6.fr/pub/gcc/releases/gcc-10.2.0/gcc-10.2.0.tar.xz
    tar -xf gcc-10.2.0.tar.xz
fi

mkdir -p  build-binutils && mkdir -p build-gcc

# Build binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install
# Finished building binutils

cd $HOME/src/build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
make install-gcc
make install-target-libgcc
# Finished building gcc

echo "Bootstrap finished."