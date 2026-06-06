#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "fsl_iomuxc.h"

void led_init(void);
void led_on(void);
void led_off(void);
void led_switch(int led, int state);

enum led_num
{
    LED0 = 0,
};

#endif /* __BSP_LED_H */
