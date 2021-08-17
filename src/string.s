.arm
.text

.global strcpy
strcpy: @ r0: dest pointer, r1: src pointer
    ldrb r2, [r1], #1 @ load from src, increment pointer

    cmp r2, #0 @ return if end of src was reached
    bxeq lr

    strb r2, [r0], #1 @ store in dest, increment pointer
    b strcpy @ loop

.global strcat
strcat: @ r0: dest ptr, r1: src ptr
    push {lr}
    push {r0, r1}
    bl strlen @ calc length of dest string to jump to its null terminator
    movs r2, r0 @ copy calculated string length into r2
    pop {r0, r1}
    add r0, r0, r2 @ add strlen to string pointer
    bl strcpy @ perform concatenation by executing strcpy
    pop {pc}

.global strlen
strlen: @ r0: string pointer
    mov r1, r0 @ copy start point
strlen_loop:
    ldrb r2, [r0] @ load byte

    cmp r2, #0 @ check if loaded byte was null-terminator
    subeq r0, r1, r0  @ if yes, calculate string length and return
    bxeq lr

    add r2, r2, #1 @ increment pointer
    b strlen_loop
    