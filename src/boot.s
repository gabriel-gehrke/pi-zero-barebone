.global _start
_start:
    /* setup stack pointer, go to kernel_main */
    mov sp, #0x8000
    bl kernel_main
proc_hang:
    /* do nothing */
    b proc_hang

