.arm
.text

.globl memzero
memzero:
    /* r0: start address; r1: number of bytes to overwrite with 0 */
    cmp r1, #0
    bxeq lr @ return if r1 is zero. (can not be smaller because input is unsigned)
    mov r2, #0 @ load 0 into r2
memzero_loop:
    strb r2, [r0], #1 @ write zero, increment register afterwards
    subs r1, r1, #1 @ decrement counter
    bne memzero_loop @ loop if not zero

    bx lr

