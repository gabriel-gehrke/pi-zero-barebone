#include "mm.h"

.section ".text.boot"

.global _start
_start:
    ldr r0, =bss_begin
    ldr r0, [r0]

    ldr r1, =bss_end
    ldr r1, [r1]

    sub r1, r1, r0
    bl memzero

    mov sp, #LOW_MEMORY
    bl kernel_main
    b proc_hang

proc_hang:
    /* do nothing */
    b proc_hang