#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "fsl_iomuxc.h"

void beep_init(void);
void beep_switch(int status);

#endif /* __BSP_BEEP_H__ */
