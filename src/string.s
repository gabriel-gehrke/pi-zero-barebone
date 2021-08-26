.arm
.text

.globl strcpy
strcpy: @ r0: dest pointer, r1: src pointer
    ldrb r2, [r1], #1 @ load from src, increment pointer

    cmp r2, #0 @ return if end of src was reached
    bxeq lr

    strb r2, [r0], #1 @ store in dest, increment pointer
    b strcpy @ loop

.globl strcat
strcat: @ r0: dest ptr, r1: src ptr
    push {lr}
    push {r0, r1}
    bl strlen @ calc length of dest string to jump to its null terminator
    movs r2, r0 @ copy calculated string length into r2
    pop {r0, r1}
    add r0, r0, r2 @ add strlen to string pointer
    bl strcpy @ perform concatenation by executing strcpy
    pop {pc}

.globl strlen
strlen: @ r0: string pointer
    mov r1, r0 @ copy start point
strlen_loop:
    ldrb r2, [r0] @ load byte

    cmp r2, #0 @ check if loaded byte was null-terminator
    subeq r0, r1, r0  @ if yes, calculate string length and return
    bxeq lr

    add r0, r0, #1 @ increment pointer
    b strlen_loop

.globl strcmp
strcmp: @ r0: first string, r1: second string

    @ load 2 bytes
    ldrb r2, [r0], #1
    ldrb r3, [r1], #1

    @ first string terminated
    cmp r2, #0
    subeq r0, r2, r3 @ return negative value if r2 < r3, return 0 if r2 == r3
    bxeq lr

    @ second string terminated, first one did not
    cmp r3, #0
    moveq r0, r2 @ return positive value if r2 > 0, return 0 otherwise
    bxeq lr

    @ both strings are not 0, but are still equal (loop)
    subs r2, r2, r3
    beq strcmp

    @ the strings are different
    mov r0, r2 @ use result from subtraction in prior step
    bx lr




    