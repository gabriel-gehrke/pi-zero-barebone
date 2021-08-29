#include "common.h"

u32 umin(u32 a, u32 b) {
    return a < b ? a : b;
}
u32 umax(u32 a, u32 b) {
    return a > b ? a : b;
}


u32 min(u32 a, u32 b) {
    return a < b ? a : b;
}
u32 max(u32 a, u32 b) {
    return a > b ? a : b;
}

u32 abs(i32 v) {
    return v < 0 ? -v : v;
}


u32 ulog10(u32 v) {
    return (v >= 1000000000u) ? 9 : (v >= 100000000u) ? 8 : 
        (v >= 10000000u) ? 7 : (v >= 1000000u) ? 6 : 
        (v >= 100000u) ? 5 : (v >= 10000u) ? 4 :
        (v >= 1000u) ? 3 : (v >= 100u) ? 2 : (v >= 10u) ? 1u : 0u;
}


void udiv(u32 dividend, u32 divisor, u32* result, u32* modulo) {

    if (divisor == 0) return;
    if (divisor == 1) {
        *result = dividend;
        *modulo = 0;
        return;
    }

    // short with 2 as long as possible
    while (dividend % 2 == 0 && divisor % 2 == 0) {
        dividend = dividend >> 1;
        divisor = divisor >> 1;
    }
    
    // count how many times divisor fits into dividend
    u32 res = 0;
    while (dividend >= divisor) {
        dividend -= divisor;
        res++;
    }

    *result = res; // store result (# times divisor fit in dividend)
    *modulo = dividend; // store the rest
}