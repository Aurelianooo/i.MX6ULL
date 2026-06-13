#include "bsp_epit.h"
#include "bsp_led.h"
#include "bsp_int.h"

void epit1_init(u32 frac, u32 value)
{
    frac &= 0xfff;

    EPIT1->CR = 0; /* 清零CR寄存器 */

    /**
     * bit25-24: 01 时钟选择Peripheral clock = 66MHz
     * bit15: 4 frac分频值
     * bit3: 1 计数器从LR加载数值
     * bit2: 1 比较中断使能
     * bit1: 1 计数器初始值来自LR寄存器
     * bit0: 0 初始化完成前关闭EPIT1
     */
    EPIT1->CR = (1 << 24 | frac << 4 | 1 << 3 | 1 << 2 | 1 << 1);

    EPIT1->LR = value;
    EPIT1->CMPR = 0; /* 比较寄存器值，当计数器值与其相等时产生中断 */

    /* 使能GIC对应中断 */
    GIC_EnableIRQ(EPIT1_IRQn);

    /* 注册中断服务函数 */
    system_register_irehandler(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL);

    /* 使能EPIT1 */
    EPIT1->CR |= 1 << 0;
}

void epit1_irqhandler(void)
{
    static u8 state = 0;
    state = !state;
    if (EPIT1->SR & (1 << 0))
    { /* 比较中断发生 */
        led_switch(LED0, state);
    }
    /* 清除中断标志位 */
    EPIT1->SR |= 1 << 0;
}
