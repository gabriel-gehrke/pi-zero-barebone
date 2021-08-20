#pragma once

#include "common.h"

void uart_init();
char uart_recv();
void uart_send(char c);
void uart_print(const char* str);
void uart_print_hex(u32 val);
void uart_print_int(i32 val);
void uart_print_uint(u32 val);
void uart_printf(const char* fmt, ...);