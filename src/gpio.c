#include "gpio.h"
#include "utils.h"

void gpio_pin_set_func(u8 pin, GpioFunc func) {
    // math magic from tutorial
    u8 bitStart = (pin * 3) % 30;
    u8 reg = pin / 10;

    u32 selector = GPIO_REGS->func_select[reg];
    selector &= ~(7 << bitStart);
    selector |= (func << bitStart);

    GPIO_REGS->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pin) {

    GPIO_REGS->pupd_enable = 0;
    delay(150);
    GPIO_REGS->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
    delay(150);

    GPIO_REGS->pupd_enable = 0;
    GPIO_REGS->pupd_enable_clocks[pin / 32] = 0;
}