#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "fsl_iomuxc.h"

void exti_init(void);
void gpio1_16_31_irqhandler(void);

#endif
