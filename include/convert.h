#pragma once
#include "common.h"

// converts the given u32 value into hex and stores it into the given buffer. The return value is a pointer pointing to the first character after the hex string.
char* u32_to_hex(char* buff, u32 value);

char* u32_to_bin(char* buff, u32 value);

char* u32_to_dec(char* buff, u32 value);