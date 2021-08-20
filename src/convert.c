#include "common.h"
#include "intmath.h"

char* u32_to_hex(char* buff, u32 value) {

    for (int shift = 28; shift >= 0; shift -= 4) {

        u32 curr = (value & (0xF << shift)) >> shift;
        curr += curr < 10 ? '0' : ('a' - 10);

        *buff = (char) curr;
        buff++;
    }

    return buff;
}

char* u32_to_bin(char* buff, u32 value) {

    for (int shift = 31; shift >= 0; shift--) {

        u32 curr = (value & (1 << shift)) >> shift;
        curr += '0';

        *buff = (char) curr;
        buff++;
    }

    return buff;
}


char* u32_to_dec(char* buff, u32 value) {
    
    for (int i = ulog10(value); i >= 0; i--) {
        char c = (value % 10) + '0';
        buff[i] = c;
        value /= 10;
    }

    return buff;
}

char* i32_to_dec(char* buff, i32 value) {
    if (value < 0) {
        value = -value;
        *buff = '-';
        buff++;
    }
    return u32_to_dec(buff, (u32)value);
}