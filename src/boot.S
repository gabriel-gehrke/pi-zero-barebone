#include "mm.h"

.arm
.section ".text.boot"

.globl _start
_start:
    /* set stack pointer to lower mem */
    mov sp, #LOW_MEMORY

    /* zero out bss region */
    ldr r0, =bss_begin
    ldr r1, =bss_end
    sub r1, r1, r0
    bl memzero

    /* go to kernel_main */
    bl kernel_main
proc_hang:
    /* do nothing */
    b proc_hang
