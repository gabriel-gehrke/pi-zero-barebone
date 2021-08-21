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

static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char* chars_to_base64(char* dest, const char* src, u32 src_len) {

    for ( ; src_len >= 3; src_len -= 3) {

        // inspired by https://fm4dd.com/programming/base64/base64_algorithm.shtm

        u32 a = (src[0] & 0b11111100) >> 2; // get first 6 bits
        u32 b = ((src[0] & 0b00000011) << 4) | ((src[1] & 0b11110000) >> 4); // get second 6 bits
        u32 c = ((src[1] & 0b00001111) << 2) | ((src[2] & 0b11000000) >> 6); // get third 6 bits
        u32 d = (src[2] & 0b00111111); // get last 6 bits

        src += 3;

        dest[0] = b64[a];
        dest[1] = b64[b];
        dest[2] = b64[c];
        dest[3] = b64[d];

        dest += 4;

    }

    // 1 or 2 bytes might remain
    if (src_len > 0) {
        *dest++ = (src[0] & 0b11111100) >> 2;

        switch (src_len) {
            case 1:
                *dest++ = b64[(src[0] & 0b00000011) << 4];
                *dest++ = '=';
                *dest++ = '=';
                break;
            case 2:
                *dest++ = b64[((src[0] & 0b00000011) << 4) | ((src[1] & 0b11110000) >> 4)];
                *dest++ = b64[(src[1] & 0b00001111) << 2];
                *dest++ = '=';
                break;
        }
    }

    return dest;
}