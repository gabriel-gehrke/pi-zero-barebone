#include "common.h"
#include "mini_uart.h"
#include "system.h"
#include "stdio.h"
#include "string.h"
#include "convert.h"

static const char* b64_test_string = "Hello World!";

void kernel_main() {
    
    uart_init();

    // delay some cycles
    delay(1000);

    uart_print("\nRaspberry Pi Zero Bare Metal OS Initializing...\n\0");
    uart_print("\n\nDone!\n\0");

    u32 len = 12;
    uart_printf("\"%s\" ist %u Zeichen lang!\n", b64_test_string, len);

    char buff[len + (len / 3) + 1];
    *chars_to_base64(buff, b64_test_string, len) = '\0';

    uart_print(buff);
    uart_send('\n');

    if (streql(buff, "ABcDeFg")) {
        uart_print("Die Strings waren gleich!");
    }


    while (1) {
        char c = uart_recv();
        uart_print_hex(c);
        uart_send('\n');
    }
}