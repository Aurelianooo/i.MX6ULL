#include "bsp_int.h"

static u32 irqNesting;

/* 中断向量表 */
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

/* 初始化中断向量表 */
static void system_irqtable_init(void)
{
    u32 i = 0;
    irqNesting = 0;
    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        irqTable[i].irqHandler = default_irqhandler;
        irqTable[i].param = NULL;
    }
}

void int_init(void)
{
    GIC_Init();
    system_irqtable_init();

    /* 设置中断向量偏移 */
    __set_VBAR(0x87800000);
}

/* 注册中断处理函数 */
void system_register_irehandler(IRQn_Type irq, system_irq_handler_t handler, void *param)
{
    irqTable[irq].irqHandler = handler;
    irqTable[irq].param = param;
}

/* 中断处理函数入口 */
void system_irqhandler(u32 gicciar)
{
    u32 tmp = gicciar & 0x3ff;
    if (tmp >= NUMBER_OF_INT_VECTORS)
    {
        return;
    }
    irqNesting++;
    irqTable[tmp].irqHandler(tmp, irqTable[tmp].param);
    irqNesting--;
}

/* 默认中断处理函数 */
void default_irqhandler(u32 gicciar, void *param)
{
    while (1)
    {
    }
}