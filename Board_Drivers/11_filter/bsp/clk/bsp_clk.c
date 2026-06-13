#include "bsp_clk.h"

/* 使能外设时钟 */
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

/* 初始化主频为528MHz */
void clk_init(void)
{
    u32 reg = 0;

    if ((CCM->CCSR >> 2 & 0x1) == 0)
    {
        CCM->CCSR &= ~(0x1 << 8); // 切换到外部晶振 24MHz
        CCM->CCSR |= 0x1 << 2;    // 使能外部晶振
    }

    // 设置PLL_1输出频率为24MHz * 88 / 2 = 1056MHz
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7F);
    CCM->CACRR = 1; // 设置2分频
    CCM->CCSR &= ~(0x1 << 2);

    // 设置PLL_2的4路PFD
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3f3f3f3f);
    reg |= (32 << 24); // PFD3 = 297MHz
    reg |= (24 << 16); // PFD2 = 396MHz
    reg |= (16 << 8);  // PFD1 = 594MHz
    reg |= (27 << 0);  // PFD0 = 352MHz
    CCM_ANALOG->PFD_528 = reg;

    // 设置PLL_3的4路PFD
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3f3f3f3f);
    // PFD3 = 454.7MHz, PFD2 = 508.2MHz, PFD1 = 540MHz, PFD0 = 720MHz
    reg |= (19 << 24) | (17 << 16) | (16 << 8) | (12 << 0);
    CCM_ANALOG->PFD_480 = reg;

    // 设置AHB_CLK_ROOT=132MHz
    CCM->CBCMR &= ~(0x3 << 18);
    CCM->CBCMR |= (0x1 << 18);
    CCM->CBCDR &= ~(0x1 << 25);
    while (CCM->CDHIPR & (1 << 5))
        ; // 等待握手信号

    reg = CCM->CBCDR;
    reg &= ~(0x7 << 10);
    reg |= (0x2 << 10); // 3分频
    while (CCM->CDHIPR & (1 << 1))
        ; // 等待握手信号
    CCM->CBCDR = reg;

    // 设置IPG_CLK_ROOT=66MHz
    CCM->CBCDR &= ~(0x3 << 8);
    CCM->CBCDR |= (0x1 << 8); // 2分频

    // 设置PERCLK_CLK_ROOT=66MHz
    CCM->CSCMR1 &= ~(0x1 << 6);
    CCM->CSCMR1 &= ~(0x3f << 0); // 1分频
}
