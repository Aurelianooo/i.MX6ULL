#include "bsp_led.h"

/* 初始化LED */
void led_init(void)
{
    /* 配置IO复用、电气属性 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);

    /* 配置GPIO */
    GPIO1->GDIR |= (1 << 3);
    GPIO1->DR &= ~(1 << 3);
}

void led_on(void)
{
    GPIO1->DR &= ~(1 << 3);
}

void led_off(void)
{
    GPIO1->DR |= (1 << 3);
}

void led_switch(int led, int state)
{
    switch (led)
    {
    case LED0:
        if (state)
            led_on();
        else
            led_off();
        break;
    default:
        break;
    }
}
