#!/bin/bash
set -xue

QEMU=qemu-system-riscv32

CC=${CC:-gcc}

CFLAGS="-std=c++11 -O2 -g3 -Wall -Wextra -fno-stack-protector -ffreestanding -nostdlib -no-pie"

OBJCOPY=${OBJCOPY:-riscv32-none-elf-objcopy}

$CC $CFLAGS -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf src/shell.cpp src/user.cpp src/common.cpp
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
$OBJCOPY -Ibinary -Oelf32-littleriscv shell.bin shell.bin.o

$CC $CFLAGS -Isrc -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    src/kernel.cpp src/common.cpp shell.bin.o

$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf
