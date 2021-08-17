#include "gpio.h"
#include "utils.h"
#include "peripherals/auxiliary.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init() {
    gpio_pin_set_func(TXD, ALT5);
    gpio_pin_set_func(RXD, ALT5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    AUX_REGS->enables = 1;
    AUX_REGS->mu_control = 0;
    AUX_REGS->mu_ier = 0;
    AUX_REGS->mu_lcr = 3;
    AUX_REGS->mu_mcr = 0;

    AUX_REGS->mu_baud_rate = 270; // = 115200 @ 250 Mhz

    AUX_REGS->mu_control = 3;

    uart_send('\r');
    uart_send('\n');
    uart_send('\n');
}

void uart_send(char c) {

    // wait until transmitter empty
    while(!(AUX_REGS->mu_lsr & 0x20));

    AUX_REGS->mu_io = (u8)c;
    delay(100000);
}

char uart_recv() {
    // wait until character available
    while(!(AUX_REGS->mu_lsr & 1));

    return AUX_REGS->mu_io & 0xFF;
}

void uart_print(const char* str) {
    char c;
    for (u32 i = 0; (c = str[i]); i++) {
        if (c == '\n') {
            uart_send('\r');
        }
        uart_send(c);
    }
}