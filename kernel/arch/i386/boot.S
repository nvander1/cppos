# multiboot header constants
.set ALIGN,     1<<0              # align loaded modules on page boundary
.set MEMINFO,   1<<1              # provide memory map
.set FLAGS,     ALIGN | MEMINFO   # multiboot flag field
.set MAGIC,     0x1BADB002        # magic number for multiboot header
.set CHECKSUM,  -(MAGIC + FLAGS)  # checksum of above


# multiboot header
# bootloader searches for this in first 8KB aligned on 32 bit boundary
# placed in its own section to force within first 8KB
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


# multiboot does not define stack pointer (esp) and kernel must provide stack
# allocates room for 16KB stack
# stack grows downward on x86
#
#================
#|              |  <- top     (0xffff)
#|    STACK     |
#|              |
#|--------------|  <- bottom  (0xeeee) (esp)
#.     ...      .
#|--------------|
#|              |
#|     HEAP     |
#|              |
#================
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


# linker script specifies _start as entry point to kernel
# and bootloader jumps to this once kernel has been loaded
.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp     # set up the stack

    # here is good place to setup crucial processor state:
    # floating point instructions set up
    # ISA extensions set up
    # GDT should be loaded here
    # paging should be enabled here
    # C++ things like global constructors and exceptions need runtime support
    call _init

    # enter kernel
    # ABI requires stack be 16 byte aligned at the time of call
    # then it pushes return poiner of size 4 bytes
    call kernel_main

    # put system into infinite loop if nothing else to do
    # 1) disable interrupts
    # 2) wait for next interrup (this locks computer since they disabled)
    # 3) jump to hlt in event of non-maskable interrupt
    cli
1:  hlt
    jmp 1b

    # set size of _start symbol to location minus start
    # useful for debugging or implementing call tracing
.size _start, . - _start
