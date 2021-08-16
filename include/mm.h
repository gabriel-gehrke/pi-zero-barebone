#pragma once

#define LOW_MEMORY 0x8000

#ifndef __ASSEMBLER__

#include "common.h"
extern void memzero (u32 addr, u32 n);

#endif