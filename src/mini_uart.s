/* 
.arm
.text
.global uart_print
/
*   params:
*   r0: char pointer of string to print
*
*   registers:
*   r0: used as parameter register for subroutines
*   r4: used to load char/byte into
*   r5: actual string pointer
*
*
uart_print:
    push {r4, r5, lr}
    mov r5, r0 @ copy address to r5
uart_print_loop:
    ldrb r4, [r5], #1 @ load char at r5 into r4
    cmp r4, #0 @ check if string ended (null terminator), return then
    popeq {r4, r5, pc}

    cmp r4, #10 @ check if char is '\n'
    moveq r0, #13 @ if so, load '\r' into r0 and send it via uart
    bleq uart_send

    mov r0, r4 @ load r4 character into r0, print it
    bl uart_send

    b uart_print_loop




*/
    

