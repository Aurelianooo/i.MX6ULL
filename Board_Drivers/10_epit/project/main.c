#include "main.h"

int main(void)
{
    int_init();
    clk_init();
    clk_enable();
    led_init();
    beep_init();
    key_init();
    epit1_init(0, 66000000 / 2);    /* EPIT1定时器周期为500ms */

    while (1)
    {
        delay(500);
    }

    return 0;
}
