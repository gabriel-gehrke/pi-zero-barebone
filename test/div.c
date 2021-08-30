#include "../include/intmath.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 1000000; i++) {
        u32 dividend = rand();
        u32 divisor = rand() / 100000;
        u32 result = dividend / divisor;
        u32 remainder = dividend % divisor;

        u32 udiv_res = 0;
        u32 udiv_remainder = 0;
        udiv(dividend, divisor, &udiv_res, &udiv_remainder);

        printf("%u/%u = %u R %u\n", dividend, divisor, result, remainder);
        if (result == udiv_res && remainder == udiv_remainder) {
            puts("CORRECT\n");
        } else {
            printf("ERR: udiv res: %u R %u\n\n", udiv_res, udiv_remainder);
            return 1;
        }
    }
}
