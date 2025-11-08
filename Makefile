# this makefile is not a part of STM32Cube for Visual Studio Code
# it was written to support simple command line builds using arm-gcc toolchain directly

PROJECT=hello_nucleo

SRC=Src/main.c Src/startup_stm32l432xx.S Src/syscall.c Src/sysmem.c

CPU_FLAGS=-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS=-DDEBUG -g -Os -I./Inc ${CPU_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter

${PROJECT}.bin: ${PROJECT}.elf Makefile
	arm-none-eabi-objcopy -O binary $< $@

${PROJECT}.elf: ${SRC} Makefile
	arm-none-eabi-gcc ${CFLAGS} -Tstm32l432xc_flash.ld -o $@ ${SRC}
