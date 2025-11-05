# VS Code
Before installing STM32 extensions: create a new STM32 profile in VS Code

# cmake
STM32 comes with all tools installed in a bundle. The tools are usually not on the path.

Example:
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

# Build
After the project is configured, it can be (re-)build from the command line:
hello_nucleo> c:\Users\frank\.vscode\extensions\stmicroelectronics.stm32cube-ide-core-1.0.3\resources\binaries\win32\x86_64\cube.exe ninja -C .\build\Debug\

# Command line Builds

## Install External Tools

No external tools are needed if you build in VS Code, 
but neccessary if you build manually from cmd line.

### cmake

https://cmake.org/download/
cmake-4.2.0-rc2-windows-x86_64.msi

### arm gcc toolchain

https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi.exe

(C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\14.3 rel1)

### make

from cmd line: `winget install ezwinports.make`

## Run make

from project folder cmd line: `make`

hint: make uses `Makefile` which is easy to understand and modify

Command line builds cannot debug using the target hardware
