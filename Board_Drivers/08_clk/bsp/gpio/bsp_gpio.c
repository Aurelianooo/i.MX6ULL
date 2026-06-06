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
