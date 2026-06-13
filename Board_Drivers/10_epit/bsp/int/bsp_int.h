#ifndef __BSP_INT_H
#define __BSP_INT_H

#include "fsl_iomuxc.h"

/* 定义中断函数指针 */
typedef void (*system_irq_handler_t)(u32 gicciar, void *param);

/* 中断处理函数结构体 */
typedef struct _sys_irq_handle
{
    system_irq_handler_t irqHandler;
    void *param;
} sys_irq_handle_t;

void int_init(void);
void system_register_irehandler(IRQn_Type irq, system_irq_handler_t handler, void *param);
void system_irqhandler(u32 gicciar);
void default_irqhandler(u32 gicciar, void *param);

#endif