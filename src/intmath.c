#include "common.h"
#include "intmath.h"


u32 ulog10(u32 v) {
    return (v >= 1000000000u) ? 9 : (v >= 100000000u) ? 8 : 
        (v >= 10000000u) ? 7 : (v >= 1000000u) ? 6 : 
        (v >= 100000u) ? 5 : (v >= 10000u) ? 4 :
        (v >= 1000u) ? 3 : (v >= 100u) ? 2 : (v >= 10u) ? 1u : 0u;
}


u32 umod(u32 val, u32 mod) {
    /* because of gcc's optimization features, this method gets optimized to a shorter length than udiv */
    u32 ignore = 0; // ignore, we do not need the division's result
    u32 remainder = 0; // we only need the remainder
    udiv(val, mod, &ignore, &remainder);
    return remainder;
}

void udiv(u32 dividend, u32 divisor, u32* result, u32* remainder) {

    if (divisor == 0) return;
    if (divisor == 1) {
        *result = dividend;
        *remainder = 0;
        return;
    }

    // short with 2 as long as possible
    while (dividend % 2 == 0 && divisor % 2 == 0) {
        dividend >>= 1;
        divisor >>= 1;
    }
    
    // count how many times divisor fits into dividend
    u32 res = 0;
    while (dividend >= divisor) {
        dividend -= divisor;
        res++;
    }

    *result = res; // store result (# times divisor fit in dividend)
    *remainder = dividend; // store the rest
}