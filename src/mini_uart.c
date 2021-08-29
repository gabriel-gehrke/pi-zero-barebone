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

    sys_delay(2000);

    uart_send('\n');
    uart_send('\n');
    uart_print("Mini-UART interface was successfully initailized!\n");
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

void uart_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
 
    // while end of string not reached
    for (; *fmt != '\0'; fmt++) {

        // check for percent sign
        if (*fmt == '%') {

            char buff[16]; // allocate temporary buffer for string building (4 words big)
            memzero(buff, sizeof(buff));

            // switch format character
            switch (*(fmt+1)) {
                case('x'):
                case('X'):
                    buff[0] = '0';
                    buff[1] = 'x';
                    u32_to_hex(buff + 2, va_arg(args, u32));
                    uart_print(buff);
                    break;
                case('s'):
                    uart_print(va_arg(args, char*));
                    break;
                case('u'):
                    u32_to_dec(buff, va_arg(args, u32));
                    uart_print(buff);
                    break;
                case('d'):
                    i32_to_dec(buff, va_arg(args, i32));
                    uart_print(buff);
                    break;
                case('b'):
                    buff[0] = '0';
                    buff[1] = 'b';
                    u32_to_bin(buff, va_arg(args, u32));
                    uart_printf(buff);
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