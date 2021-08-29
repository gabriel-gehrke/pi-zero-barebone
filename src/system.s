.arm
.text

.globl sys_delay
sys_delay:
    subs r0, r0, #1
    bne sys_delay
    bx lr

.globl sys_put32
sys_put32:
    str r1, [r0]
    bx lr

.globl sys_get32
sys_get32:
    ldr r0, [r0]
    bx lr

.globl sys_getCPSR
sys_getCPSR:
    mrs r0, CPSR
    bx lr

.globl sys_getSPSR
sys_getSPSR:
    mrs r0, SPSR
    bx lr

.globl sys_getmode
sys_getmode:
    mrs r0, CPSR @ copy cpsr into r0
    and r0, r0, #0b11111 @ get last 5 bits (0-4)
    bx lr

.globl sys_setmode
sys_setmode:
    mrs r1, CPSR @ copy current cpsr into r1
    bic r1, r1, #0b11111 @ clear mode bits (0-4)
    orr r0, r1, r0 @ set mode bits
    msr CPSR, r0
    bx lr


