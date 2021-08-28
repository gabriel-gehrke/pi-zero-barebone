#include <stdio.h>
#include <string.h>
#include "../include/base64.h"

int main(int argc, char** args) {
    if (argc > 1) {
        // get first param as string and calc it's length
        char* str = args[1];
        size_t len = strlen(str);

        // allocate buffer for encoding to base64
        char encoded[((len * 4) / 3) + 2];

        // encode, write 0-terminator
        *base64_encode(encoded, str, len) = 0;
    
        puts(encoded);
    }
}
