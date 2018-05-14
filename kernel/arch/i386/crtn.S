.section .init
    # gcc will fill in this section with crtend.o's .init
    popl %ebp
    ret

.section .fini
    # gcc will fill in this section with crtend.o's .fini
    popl %ebp
    ret
