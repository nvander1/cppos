# C++OS

A minimal OS written in C++. Just trying to learn more about OS.
Lots of help from [OSDev](https://wiki.osdev.org).

## Building

You need a gcc cross compiler targeted for i686-elf. See [here](https://wiki.osdev.org/GCC_Cross-Compiler)
for information on compiling one.

Build it with make.

    make

To run it you need qemu installed with i386 support.

    make test
