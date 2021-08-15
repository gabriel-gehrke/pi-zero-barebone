#include <stdarg.h>
#include "mini_uart.h"

// source: https://en.cppreference.com/w/c/variadic
void printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
 
    // while end of string not reached
    for (; *fmt != '\0'; fmt++) {

        // check for percent sign
        if (*fmt == '%' && *(fmt+1) != '\0') {
            switch (*fmt) {
                case('d'):
                    continue;
            }
        }

        uart_send(*fmt);
    }
 
    va_end(args);
}