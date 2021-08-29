#include "common.h"
#include "mini_uart.h"
#include "system.h"
#include "stdio.h"
#include "string.h"
#include "base64.h"

static void initialize_os();

void kernel_main() {
    
    initialize_os();
    uart_print("\nWelcome to the Raspberry Pi Zero Bare Metal OS created by Gabriel Gehrke!\n\n");

    while (1) {
        uart_send(uart_recv());
        uart_send('\n');
    }
}

void initialize_os() {
    // initialize the uart interface for communication
    uart_init();

    // delay some cycles
    sys_delay(10000);

    // fetch boot mode
    u32 mode = sys_getmode();
    uart_printf("Booted mode: %b\n", mode);



}