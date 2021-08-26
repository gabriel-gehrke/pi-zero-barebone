#include "../include/base64.h"

static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(char* dest, const char* src, u32 src_len) {

    for ( ; src_len >= 3; src_len -= 3) {
        /*
            3 bytes get converted into 4 bytes:
            - 3 bytes are 24 bits
            - divide 24 bits into 4x6 bits
            - get corresponding char from base64 lookup array
        */

        char a = *src++;
        char b = *src++;
        char c = *src++;

        *dest++ = b64[(a & 0b11111100) >> 2]; // get first 6 bits
        *dest++ = b64[((a & 0b00000011) << 4) | ((b & 0b11110000) >> 4)]; // get second 6 bits
        *dest++ = b64[((b & 0b00001111) << 2) | ((c & 0b11000000) >> 6)]; // get third 6 bits
        *dest++ = b64[(c & 0b00111111)]; // get last 6 bits

    }

    // 1 or 2 bytes might remain
    if (src_len > 0) {
        dest[0] = b64[(src[0] & 0b11111100) >> 2];
        dest[3] = '=';

        if (src_len == 1) {
            // 1 byte remained
            dest[1] = b64[(src[0] & 0b00000011) << 4];
            dest[2] = '=';
        } else {
            // 2 bytes remained
            dest[1] = b64[((src[0] & 0b00000011) << 4) | ((src[1] & 0b11110000) >> 4)];
            dest[2] = b64[(src[1] & 0b00001111) << 2];
        }

        dest += 4;
    }

    return dest;
}

char* base64_decode(char* dest, const char* src, u32 src_len) {

    if (src_len == 0)
        return dest;

    /*
        Convert 4 bytes back into 3 bytes.

        For that: convert all base 64 characters back into their corresponding value bytes.
        Then: extract the original 6 bits, combine them into three 8-bit values.
    */

    // convert base64 back into bytes: ignore all none-base64 bytes
    char bytes[src_len];
    u32 len = 0;
    for (u32 i = 0; i < src_len; i++) {

        char c = src[i];

        if (c >= 'A' && c <= 'Z') {
            c -= 'A';
        } else if (c >= 'a' && c <= 'z') {
            c = (c - 'a') + 26;
        } else if (c >= '0' && c <= '9') {
            c = (c - '0') + (2 * 26);
        } else if (c == '+') {
            c = 62;
        } else if (c == '/') {
            c = 63;
        } else if (c == '=') {
            c = 0;
        } else {
            continue;
        }

        bytes[len] = c;
        len++;
    }

    if (len % 4 != 0) {
        return null;
    }

    for (u32 i = 0; i <= len - 4; i+=4) {
        
        *dest++ = (bytes[i + 0] << 2) | ((bytes[i + 1] & 0b00110000) >> 4);
        *dest++ = ((bytes[i + 1] & 0b00001111) << 4) | ((bytes[i + 2] & 0b00111100) >> 2);
        *dest++ = ((bytes[i + 2] & 0b00000011) << 6) | (bytes[i + 3] & 0b00111111);
    }

    return dest;
}