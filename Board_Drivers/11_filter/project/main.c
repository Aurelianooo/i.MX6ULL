#include "main.h"

int main(void)
{
    u8 state = OFF;

    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    filter_init();

    while (1)
    {
        state = !state;
        led_switch(LED0, state);
        delay(500);
    }

    return 0;
}
