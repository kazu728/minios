#!/bin/bash
set -xue

QEMU=qemu-system-riscv32

CC=${CC:-gcc}

CFLAGS="-std=c++11 -O2 -g3 -Wall -Wextra -fno-stack-protector -ffreestanding -nostdlib -no-pie"

$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.cpp

$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf