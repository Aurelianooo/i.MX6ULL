#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_beep.h"

void exti_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0U);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080u);

    /* 初始化GPIO为外部中断 */
    gpio_pin_config_t key_config = {
        .direction = kGPIO_DigitalInput,
        .interruptMode = kGPIO_IntFallingEdge,
        .outputLogic = 1,
    };
    gpio_init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irehandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_16_31_irqhandler, NULL);
    gpio_intenable(GPIO1, 18);
}

void gpio1_16_31_irqhandler(void)
{
    static u8 state = 0;

    delay(10); /* 中断不要使用忙等延时，此处仅为演示消抖 */
    if (gpio_read(GPIO1, 18) == 0)
    {
        state = !state;
        beep_switch(state);
    }

    gpio_intclear(GPIO1, 18); /* 清除中断标志位 */
}
