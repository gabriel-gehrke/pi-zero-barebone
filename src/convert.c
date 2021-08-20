#include "common.h"

//static const char* hex_alphabet = "0123456789ABCDEF";

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
    
    /*
    u32 digits = 0;
    u32 copy = value;

    if (value == 0) {
        digits = 0;
    } else {
        while (copy > 0) {
            digits++;
            copy /= 10;
        }
    }
    */

    return buff;

    
}