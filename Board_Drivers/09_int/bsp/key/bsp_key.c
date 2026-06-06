#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"

void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0U);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080u);

    gpio_pin_config_t key_config = {
        .direction = kGPIO_DigitalInput,
    };
    gpio_init(GPIO1, 18, &key_config);
}

int get_key_val(void)
{
    int ret = 0;
    static u8 release = 1;
    if (gpio_read(GPIO1, 18) == 0 && release == 1)
    {              // 按键按下
        delay(10); // 消抖
        release = 0;
        if (gpio_read(GPIO1, 18) == 0)
        {
            ret = KEY0_VAL;
        }
    }
    else if (gpio_read(GPIO1, 18) == 1)
    { // 按键释放
        ret = KEY_NONE;
        release = 1;
    }

    return ret;
}
