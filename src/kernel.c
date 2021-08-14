#include "common.h"
#include "mini_uart.h"

void kernel_main() {
    uart_init();
    uart_print("Raspberry Pi Zero Bare Metal OS Initializing...\n");

    uart_print("Done!\n");
}