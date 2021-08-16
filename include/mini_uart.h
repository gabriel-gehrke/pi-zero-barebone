#pragma once

#include "common.h"

void uart_init();
char uart_recv();
void uart_send(char c);
void uart_print(const char* str);