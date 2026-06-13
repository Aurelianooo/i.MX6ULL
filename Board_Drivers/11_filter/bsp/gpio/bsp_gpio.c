#include "bsp_gpio.h"

/* GPIO初始化 */
void gpio_init(GPIO_Type *base, uint32_t pin, gpio_pin_config_t *config)
{
    if (config->direction == kGPIO_DigitalInput)
    {
        base->GDIR &= ~(1U << pin);
    }
    else
    {
        base->GDIR |= (1U << pin);
        gpio_write(base, pin, config->outputLogic);
    }
    gpio_intconfig(base, pin, config->interruptMode);
}

/* 控制GPIO输出 */
void gpio_write(GPIO_Type *base, uint32_t pin, uint8_t value)
{
    if (value)
    {
        base->DR |= (1U << pin);
    }
    else
    {
        base->DR &= ~(1U << pin);
    }
}

/* 读取GPIO输入 */
int gpio_read(GPIO_Type *base, uint32_t pin)
{
    return (base->DR >> pin) & 0x01;
}

/* 使能GPIO中断 */
void gpio_intenable(GPIO_Type *base, uint32_t pin)
{
    base->IMR |= (1 << pin);
}

/* 禁止GPIO中断 */
void gpio_intdisable(GPIO_Type *base, uint32_t pin)
{
    base->IMR &= ~(1 << pin);
}

/* 清除中断标志位 */
void gpio_intclear(GPIO_Type *base, uint32_t pin)
{
    base->ISR |= (1 << pin);
}

/* GPIO中断初始化 */
void gpio_intconfig(GPIO_Type *base, uint32_t pin, gpio_interrupt_mode_t int_mode)
{
    volatile uint32_t *icr;
    uint32_t icrShift = pin;

    base->EDGE_SEL &= ~(1 << pin);
    if (pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= 16;
    }
    switch (int_mode)
    {
    case kGPIO_IntLowLevel:
        *icr &= ~(3 << (2 * icrShift));
        break;
    case kGPIO_IntHighLevel:
        *icr &= ~(3 << (2 * icrShift));
        *icr |= (1 << (2 * icrShift));
        break;
    case kGPIO_IntRisingEdge:
        *icr &= ~(3 << (2 * icrShift));
        *icr |= (2 << (2 * icrShift));
        break;
    case kGPIO_IntFallingEdge:
        *icr &= ~(3 << (2 * icrShift));
        *icr |= (3 << (2 * icrShift));
        break;
    case kGPIO_IntRisingOrFallingEdge:
        base->EDGE_SEL |= (1 << pin);
        break;
    default:
        break;
    }
}
