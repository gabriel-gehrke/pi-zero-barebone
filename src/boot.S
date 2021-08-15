#include "mm.h"

.section ".text.boot"

.global _start
_start:
    /* load bss start/end address, calculate length, clear with memzero */
    ldr r0, =bss_begin
    ldr r1, =bss_end
    sub r1, r1, r0 @ length
    bl memzero

    /* setup stack pointer, go to kernel_main */
    mov sp, #LOW_MEMORY
    bl kernel_main
    b proc_hang

proc_hang:
    /* do nothing */
    b proc_hang