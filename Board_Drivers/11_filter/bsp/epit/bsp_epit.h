#ifndef __BSP_EPIT_H
#define __BSP_EPIT_H

#include "fsl_iomuxc.h"

void epit1_irqhandler(void);
void epit1_init(u32 frac, u32 value);

#endif
