#include "bsp_beep.h"
#include "bsp_gpio.h"

/* 初始化蜂鸣器 */
void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);

    gpio_pin_config_t beep_config = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 1, /* 初始状态为高电平，蜂鸣器关闭 */
    };
    gpio_init(GPIO5, 1, &beep_config);
}

void beep_switch(int status)
{
    if (status)
    {
        gpio_write(GPIO5, 1, 0);
    }
    else
    {
        gpio_write(GPIO5, 1, 1);
    }
}
