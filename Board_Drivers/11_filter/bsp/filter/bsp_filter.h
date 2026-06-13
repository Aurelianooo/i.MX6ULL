#ifndef __BSP_FILTER_H
#define __BSP_FILTER_H

#include "fsl_iomuxc.h"

void filter_init(void);
void gpio1_16_31_irqhandler(void);

void filtertimer_init(u32 value);
void filter_irqhandler(void);

#endif
