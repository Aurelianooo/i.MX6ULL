#include "main.h"

int main(void)
{
    u8 led_state = OFF;

    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    exti_init();

    while (1)
    {
        led_state = !led_state;
        led_switch(LED0, led_state);
        delay(500);
    }

    return 0;
}
