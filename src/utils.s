.global delay
delay:
    subs r0, r0, #1
    bne delay
    bx lr

.global put32
put32:
    str r1, [r0]
    bx lr

.global get32
get32:
    ldr r0, [r0]
    bx lr

