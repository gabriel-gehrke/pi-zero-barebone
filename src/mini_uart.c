#include <stdarg.h>
#include "gpio.h"
#include "system.h"
#include "peripherals/auxiliary.h"
#include "convert.h"
#include "mini_uart.h"
#include "mm.h"

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

    delay(2000);

    uart_send('\n');
    uart_send('\n');
}

void uart_send(char c) {

    if (c == '\n') {
        uart_send('\r');
    }

    // wait until transmitter empty
    while(!(AUX_REGS->mu_lsr & 0x20));

    AUX_REGS->mu_io = (u8)c;
}

char uart_recv() {
    // wait until character available
    while(!(AUX_REGS->mu_lsr & 1));

    return AUX_REGS->mu_io & 0xFF;
}

void uart_print(const char* str) {
    char c;
    for (u32 i = 0; (c = str[i]); i++) {
        uart_send(c);
    }
}

static char* uart_print_hex_buff = "0x00000000";
void uart_print_hex(u32 val) {
    u32_to_hex(uart_print_hex_buff + 2, val);
    uart_print(uart_print_hex_buff);
}

void uart_print_int(i32 val) {
    char buff[12];
    memzero(buff, 12);
    i32_to_dec(buff, val);
    uart_print(buff);
}

void uart_print_uint(u32 val) {
    char buff[12];
    memzero(buff, 12);
    u32_to_dec(buff, val);
    uart_print(buff);
}

void uart_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
 
    // while end of string not reached
    for (; *fmt != '\0'; fmt++) {

        // check for percent sign
        if (*fmt == '%') {

            // switch format character
            switch (*(fmt+1)) {
                case('x'):
                case('X'):
                    uart_print_hex(va_arg(args, u32));
                    break;
                case('s'):
                    uart_print(va_arg(args, char*));
                    break;
                case('u'):
                    uart_print_uint(va_arg(args, u32));
                    break;
                case('d'):
                    uart_print_int(va_arg(args, i32));
                    break;
                default:
                    // send percent, format character was not recognized
                    uart_send('%');
                    continue;
            }

            // a control character was recognized and formatting was executed -> increment pointer by 2 and continue
            fmt++;
            continue;
        } 
        else {
            uart_send(*fmt);
        }
    }
 
    va_end(args);
}