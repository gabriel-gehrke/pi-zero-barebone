.arm

.text

.global memzero
memzero:
    cmp r1, #0
    bxls lr @ return if r1 (n) is <= 0

    eor r2, r2, r2 @ clear r2 with xor
    add r3, r0, r1 @ calculate end address
    
memzero_loop:
    str r2, [r0] @ overwrite curr addr with zero, increment addr
    add r0, r0, #1

    cmp r0, r3 @ loop if less than end address
    bls memzero_loop

    bx lr

