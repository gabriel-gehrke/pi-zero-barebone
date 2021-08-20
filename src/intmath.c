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