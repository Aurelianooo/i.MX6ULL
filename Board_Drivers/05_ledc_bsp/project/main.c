#include "main.h"

int main(void)
{
    clk_enable();
    led_init();

    while (1)
    {
        led_on();
        delay(1000);

        led_off();
        delay(1000);
    }

    return 0;
}
