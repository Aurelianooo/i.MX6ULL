#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "fsl_iomuxc.h"

typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOutput = 1U,
} gpio_pin_direction_t; /*!< GPIO direction, input or output. */

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction;
    uint8_t outputLogic; /*!< Set a default output logic, which has no use in input. */
} gpio_pin_config_t;

void gpio_init(GPIO_Type *base, uint32_t pin, gpio_pin_config_t *config);
void gpio_write(GPIO_Type *base, uint32_t pin, uint8_t value);
int gpio_read(GPIO_Type *base, uint32_t pin);

#endif /* __BSP_GPIO_H */
