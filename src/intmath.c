#include "../include/common.h"
#include "../include/intmath.h"


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
    
    /*
     * Division ALgorithm:
     *
     * Count, how many times DIVISOR fits into DIVIDEND.
     * To optimize this process, DIVISOR gets copied and multiplied by 2 until it is bigger than DIVIDEND.
     * 
     * Then that DIVISOR gets subtracted from DIVIDEND.
     * 
     * This process repeats until DIVISOR is bigger than DIVIDEND.
     *
     */
    u32 res = 0;
    while (dividend >= divisor) {
        u32 div = divisor; // copy divisor
        u32 q = 1; // temporarily store quotient

        // multiply div by 2, until bigger than dividend
        while (dividend >= div)
        {
            div <<= 1;
            q <<= 1;
        }
        
        dividend -= (div >> 1); // decrement dividend
        res += (q >> 1); // add quotient to result
    }

    *result = res; // store result (# times divisor fit in dividend)
    *remainder = dividend; // store the rest
}