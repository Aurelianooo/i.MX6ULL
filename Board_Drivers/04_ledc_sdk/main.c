#include "fsl_iomuxc.h"

/* 使能外设时钟 */
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

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

int main(void)
{
    clk_enable();
    led_init();

    volatile int i;
    /* 设置LED闪烁 */
    while (1)
    {
        GPIO1->DR ^= (1 << 3);
        for (i = 0; i < 0xeff; i++)
            ;
    }

    return 0;
}
