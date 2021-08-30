#pragma once
#include "common.h"

#define MAX(x,y) (x >= y ? x : y)
#define MIN(x,y) (x <= y ? x : y)

static inline u32 umin(u32 a, u32 b) {
    return MIN(a, b);
}
static inline u32 umax(u32 a, u32 b) {
    return MAX(a, b);
}

static inline i32 min(i32 a, i32 b) {
    return MIN(a, b);
}
static inline i32 max(i32 a, i32 b) {
    return MAX(a, b);
}

static inline u32 iabs(i32 v) {
    return v < 0 ? -v : v;
}

// calculates the logarithm to base 10
u32 ulog10(u32 v);

// calculates the division remainder of (val / mod), in other words, it calculates "val" modulo "mod" (val % mod)
u32 umod(u32 val, u32 mod);

// divides "dividend" by "divisor" and stores the result and the division remainder at the given pointers
void udiv(u32 dividend, u32 divisor, u32* result, u32* remainder);