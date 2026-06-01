#include "bsp_beep.h"

/* 初始化蜂鸣器 */
void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);

    GPIO5->GDIR |= (1 << 1); /* 设置为输出 */
    GPIO5->DR |= (1 << 1);   /* 初始状态为高电平，蜂鸣器关闭 */
}

void beep_switch(int status)
{
    if (status)
    {
        GPIO5->DR &= ~(1 << 1);
    }
    else
    {
        GPIO5->DR |= (1 << 1);
    }
}
