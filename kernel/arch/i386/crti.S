.section .init
.global _init
.type _init, @function
_init:
    push %ebp
    movl %esp, %ebp
    # gcc will fill this with crtbegin.o's .init

.section .fini
.global _fini
.type _fini, @function
_fini:
    push %ebp
    movl %esp, %ebp
    # gcc will fill this with crtbegin.o's .fini
