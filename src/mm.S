.arm
.text

/* r0: start address; r1: number of bytes to overwrite with 0 */
.global memzero
memzero:
    cmp r1, #0
    bxeq lr @ return if r1 is zero. (can not be smaller because input is unsigned)

    eor r2, r2, r2 @ clear r2 with xor
    add r3, r0, r1 @ calculate end address
    
memzero_loop:
    strb r2, [r0], #1 @ write zero, increment register afterwards
    cmp r0, r3 @ loop if less than end address
    bls memzero_loop

    bx lr

