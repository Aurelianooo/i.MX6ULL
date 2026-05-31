#include "main.h"

/* 使能外设时钟 */
void clk_enable(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;
}

/* 初始化LED */
void led_init(void)
{
    /* 配置IO复用、电气属性 */
    SW_MUX_GPIO1_IO03 = 0x5;
    SW_PAD_GPIO1_IO03 = 0x10B0;

    /* 配置GPIO */
    GPIO1_GDIR |= (1 << 3);
    GPIO1_DR &= ~(1 << 3);
}

int main(void)
{
    clk_enable();
    led_init();

    volatile int i;
    /* 设置LED闪烁 */
    while (1)
    {
        GPIO1_DR ^= (1 << 3);
        for (i = 0; i < 0xeff; i++)
            ;
    }

    return 0;
}
