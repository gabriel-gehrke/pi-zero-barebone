#pragma once
#include "common.h"
#include "peripherals/gpio.h"

typedef enum _GpioFunc {
    INPUT = 0,
    OUTPUT = 1,
    ALT0 = 4,
    ALT1 = 5,
    ALT2 = 6,
    ALT3 = 7,
    ALT4 = 3,
    ALT5 = 2
} GpioFunc;

void gpio_pin_set_func(u8 pin, GpioFunc func);
void gpio_pin_enable(u8 pin);
