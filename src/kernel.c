#include "common.h"
#include "mini_uart.h"
#include "utils.h"

void kernel_main() {
    
    uart_init();

    /*
    for (u32 i = 0; i < 10000; i++) {
        uart_send('.');
    }
    uart_send('\n');

    uart_print("Raspberry Pi Zero Bare Metal OS Initializing...\n\0");
    uart_print("\n\nDone!\n\0");

    while (1) {
        uart_send(uart_recv());
    }
    */

    for (;;) {
        uart_send('.');
        uart_send('\r');
        uart_send('\n');
        delay(10000000);
        uart_print("Raspberry Pi Zero Bare Metal OS Initializing...\n\0");
        delay(10000000);
    }
}