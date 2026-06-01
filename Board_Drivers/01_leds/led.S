.global _start

_start:
    @使能所有外设时钟
    ldr r0, =0x020c4068 @CCGR0
    ldr r1, =0xffffffff @将要写入CCGR0的值，启用所有外设时钟
    str r1, [r0] @写入CCGR0寄存器

    ldr r0, =0x020c406c @CCGR1
    str r1, [r0]
    
    ldr r0, =0x020c4070 @CCGR2
    str r1, [r0]

    ldr r0, =0x020c4074 @CCGR3
    str r1, [r0]

    ldr r0, =0x020c4078 @CCGR4
    str r1, [r0]

    ldr r0, =0x020c407c @CCGR5
    str r1, [r0]

    ldr r0, =0x020c4080 @CCGR6
    str r1, [r0]

    @配置GPIO1_IO03输出模式
    ldr r0, =0x020e0068
    ldr r1, =0x5
    str r1, [r0]

    @配置GPIO1_IO03电气属性
    ldr r0, =0x020e02f4
    ldr r1, =0x10b0
    str r1, [r0]
    
    @设置GPIO_GDIR寄存器，配置GPIO1_IO03为输出
    ldr r0, =0x0209c004
    ldr r1, =0x8
    str r1, [r0]

    @LED闪烁
    ldr r0, =0x0209c000 @GPIO1_DR寄存器地址
loop:
    @点亮LED
    ldr r1, =0x0
    str r1, [r0]

    @延时
    ldr r2, =0x100000
delay1:
    subs r2, r2, #1
    bne delay1

    @熄灭LED
    ldr r1, =0x8
    str r1, [r0]

    @延时
    ldr r2, =0x100000
delay2:
    subs r2, r2, #1
    bne delay2
    b loop @重复循环
