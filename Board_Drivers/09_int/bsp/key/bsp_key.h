#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "fsl_iomuxc.h"

enum key_val{
    KEY_NONE = 0,
    KEY0_VAL,
};

void key_init(void);
int get_key_val(void);

#endif // __BSP_KEY_H
