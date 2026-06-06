#include "main.h"

int main(void)
{
    int i = 0;
    u8 led_state = OFF;
    u8 beep_state = OFF;
    int key_val = 0;

    clk_init();
    clk_enable();
    led_init();
    beep_init();
    key_init();

    while (1)
    {
        key_val = get_key_val();
        if (key_val)
        {
            switch (key_val)
            {
            case KEY0_VAL:
                beep_state = !beep_state;
                beep_switch(beep_state);
                break;
            }
        }

        if (i == 50)
        {
            i = 0;
            led_state = !led_state;
            led_switch(LED0, led_state);
        }
        i++;
        delay(10);
    }

    return 0;
}
