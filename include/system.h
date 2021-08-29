#pragma once
#include "common.h"

// based on "ARM A32 Assembly Language" by Bruce Smith, page 281
typedef enum _sysmode {
    ABORT = 0b10111,
    FIQ = 0b10001,
    IRQ = 0b10010,
    SUPERVISOR = 0b10011,
    SYSTEM = 0b11111,
    UNDEFINED = 0b11011,
    USER = 0b10000
} sysmode;

void sys_delay(u32 ticks);
void sys_put32(u32 addr, u32 val);
u32 sys_get32(u32 addr);

// copies the current value of the "Current Program Status Register" and returns it as a 32-bit-value
u32 sys_getCPSR();
// copies the current value of the "Saved Program Control Register" (only available in supervisor mode)
u32 sys_getSPSR();

sysmode sys_getmode();
void sys_setmode(sysmode mode);