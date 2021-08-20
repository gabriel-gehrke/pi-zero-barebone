#include "common.h"
#include "mini_uart.h"
#include "system.h"
#include "stdio.h"

void kernel_main() {
    
    uart_init();

    // delay some cycles
    delay(1000);

    uart_print("\nRaspberry Pi Zero Bare Metal OS Initializing...\n\0");
    uart_print("\n\nDone!\n\0");

    uart_printf("%s TEST %s LUL %x hihi 69\n", "TEST", "TESSSST", (u32)0x69);

    while (1) {
        char c = uart_recv();
        uart_print_hex(c);
        uart_send('\n');
    }
}