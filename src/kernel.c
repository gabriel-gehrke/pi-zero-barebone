#include "common.h"
#include "mini_uart.h"
#include "utils.h"

void kernel_main() {
    
    uart_init();

    // delay some cycles
    delay(1000);

    uart_print("Raspberry Pi Zero Bare Metal OS Initializing...\n\0");
    uart_print("\n\nDone!\n\0");

    while (1) {
        uart_send(uart_recv());
    }
}