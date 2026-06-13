#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "fsl_iomuxc.h"

typedef enum _gpio_interrupt_mode
{
    kGPIO_NoIntmode = 0U,              /* 无中断功能*/
    kGPIO_IntLowLevel = 1U,            /*低电平触发*/
    kGPIO_IntHighLevel = 2U,           /*高电平触发*/
    kGPIO_IntRisingEdge = 3U,          /*上升沿触发*/
    kGPIO_IntFallingEdge = 4U,         /*下降沿触发*/
    kGPIO_IntRisingOrFallingEdge = 5U, /*上升沿或下降沿触发*/
} gpio_interrupt_mode_t;

typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,
    kGPIO_DigitalOutput = 1U,
} gpio_pin_direction_t; /*!< GPIO direction, input or output. */

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction;
    uint8_t outputLogic;
    gpio_interrupt_mode_t interruptMode;
} gpio_pin_config_t;

void gpio_init(GPIO_Type *base, uint32_t pin, gpio_pin_config_t *config);
void gpio_write(GPIO_Type *base, uint32_t pin, uint8_t value);
int gpio_read(GPIO_Type *base, uint32_t pin);
void gpio_intenable(GPIO_Type *base, uint32_t pin);
void gpio_intdisable(GPIO_Type *base, uint32_t pin);
void gpio_intclear(GPIO_Type *base, uint32_t pin);
void gpio_intconfig(GPIO_Type *base, uint32_t pin, gpio_interrupt_mode_t int_mode);

#endif /* __BSP_GPIO_H */
