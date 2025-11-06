# VS Code
Before installing STM32 extensions: create a new STM32 profile in VS Code

# cmake
STM32 comes with all tools installed in a bundle. The tools are usually not on the path.

Example:
```
hello_nucleo> c:\Users\frank\.vscode\extensions\stmicroelectronics.stm32cube-ide-core-1.0.3\resources\binaries\win32\x86_64\cube.exe
cube [FLAGS] [COMMAND | RUNTIME] [OPTIONS]
Copyright (C) 2025 STMicroelectronics.
…
COMMANDS: Run '[COMMAND] --help' to get more details
        arm-none-eabi-gdb
        cmake
        cmsis-scanner
        java
        ninja
        node
        pack
        programmer
        rtos-proxy
        starm-clangd
        stlink-gdbserver
        stlink-gdbserver-pure
        stlink-server-start
        stlink-upgrade
```
# Build
After the project is configured, it can be (re-)build from the command line:
```
hello_nucleo> c:\Users\frank\.vscode\extensions\stmicroelectronics.stm32cube-ide-core-1.0.3\resources\binaries\win32\x86_64\cube.exe ninja -C .\build\Debug\
```
# Command Line Builds

## Install External Tools

No external tools are needed if you build in VS Code, 
but neccessary if you build manually from cmd line.

### Install cmake

download `cmake-4.2.0-rc2-windows-x86_64.msi` 
or newer from
https://cmake.org/download/


### Install arm gcc toolchain

download `arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi.exe` 
or newer from
https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

(`C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\14.3 rel1`)

### Install make

from cmd line: `winget install ezwinports.make`

Closing and re-opening vs code rsp. cmd is neccessary 
to find the newly installed tools on the path.


## Build Using make

from project folder cmd line: 

```
hello_nucleo> make
arm-none-eabi-gcc -DDEBUG -I./Inc -O0 -g3 -ggdb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mlittle-endian -mthumb -Wall -Wextra -Wpedantic -Wno-unused-parameter -Tstm32l432xc_flash.ld -o hello_nucleo.elf Src/main.c Src/startup_stm32l432xx.S Src/syscall.c Src/sysmem.c
arm-none-eabi-objcopy -O binary hello_nucleo.elf hello_nucleo.bin
```

This will first compile and link the `.elf` file and then
convert (load) it into the final binary image (`.bin` file).

The `.bin` file can be dragged onto the Nucleo "USB drive"
which fill effectively program it into the processor flash memory.

Make uses the `Makefile` which is easy to understand and modify.

Command line tools cannot debug on the target hardware.
