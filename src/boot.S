#include "mm.h"

.arm
.section ".text.boot"

.globl _start
_start:
    /* zero out bss region */
    @ldr r0, =bss_begin
    @ldr r1, =bss_end
    @sub r1, r1, r0
    @bl memzero

    /* setup stack pointer, go to kernel_main */
    mov sp, #LOW_MEMORY
    bl kernel_main
    b proc_hang
proc_hang:
    /* do nothing */
    b proc_hang
