#include "bsp_filter.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_beep.h"

void filter_init(void)
{
    /* 初始化GPIO为中断 */
    gpio_pin_config_t key_config = {
        .direction = kGPIO_DigitalInput,
        .interruptMode = kGPIO_IntFallingEdge,
        .outputLogic = 1};

    /* 初始化IO复用为GPIO_IO18 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    gpio_init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);

    /* 注册中断服务函数 */
    system_register_irehandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_16_31_irqhandler, NULL);
    gpio_intenable(GPIO1, 18);

    /* 初始化定时器 10ms */
    filtertimer_init(66000000 / 100);
}

void filtertimer_init(u32 value)
{ /* 按键消抖定时器 */
    EPIT1->CR = 0;

    EPIT1->CR = (1 << 24 | 1 << 3 | 1 << 2 | 1 << 1);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;
    GIC_EnableIRQ(EPIT1_IRQn);

    system_register_irehandler(EPIT1_IRQn, (system_irq_handler_t)filter_irqhandler, NULL);
}

void filter_stop(void)
{ /* 关闭定时器 */
    EPIT1->CR &= ~(1 << 0);
}

void filter_restart(u32 value)
{ /* 重启定时器 */
    EPIT1->CR &= ~(1 << 0);
    EPIT1->LR = value;
    EPIT1->CR |= (1 << 0);
}

void filter_irqhandler(void)
{
    static u8 state = OFF;
    if (EPIT1->SR & 1 << 0)
    { /* 产生按键中断 */
        filter_stop();
        if (gpio_read(GPIO1, 18) == 0)
        {
            state = !state;
            beep_switch(state);
        }
    }
    EPIT1->SR |= 1 << 0; /* 清除中断标志位 */
}

void gpio1_16_31_irqhandler(void)
{
    /* 开启按键消抖定时器 10ms */
    filter_restart(66000000 / 100);
    /* 清除中断标志位 */
    gpio_intclear(GPIO1, 18);
}
