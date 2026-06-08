.global _start

_start:
    @ 设置中断向量表地址
    ldr pc, =Reset_Handler
    ldr pc, =Undefined_Handler
    ldr pc, =SVC_Handler
    ldr pc, =PreAbort_Handler
    ldr pc, =DataAbort_Handler
    ldr pc, =Reserved_Handler
    ldr pc, =IRQ_Handler
    ldr pc, =FIQ_Handler

@ 复位
Reset_Handler:
    @ 第一时间关闭看门狗
    ldr r0, =0x020BC000
    mov r1, #0
    str r1, [r0]

    cpsid i  @ 关闭IRQ中断

    @ 关闭I/D Cache和MMU，修改SCTLR寄存器
    MRC p15, 0, r0, c1, c0, 0
    bic r0, r0, #(0x1<<12)  @ 关闭I Cache
    bic r0, r0, #(0x1<<11)  @ 关闭分支预测
    bic r0, r0, #(0x1<<2)   @ 关闭D Cache
    bic r0, r0, #(0x1<<1)   @ 关闭对齐检查
    bic r0, r0, #(0x1<<0)   @ 关闭MMU
    MCR p15, 0, r0, c1, c0, 0

    @ 设置中断向量偏移
    ldr r0, =0x87800000
    dsb
    isb
    MCR p15, 0, r0, c12, c0, 0  @ 设置VBAR寄存器
    dsb
    isb

    @ 清除.bss段
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0

clear_bss:
    str r2, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    ble clear_bss

    @ 设置IRQ模式
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x12
    msr cpsr, r0
    ldr sp, =0x80600000  @ 设置SP指针

    @ 设置SYS模式
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x1F
    msr cpsr, r0
    ldr sp, =0x80400000  @ 设置SP指针

    @ 设置SVC模式
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x13
    msr cpsr, r0
    ldr sp, =0x80200000  @ 设置SP指针

    cpsie i  @ 开启IRQ中断
    b main  @ 跳转到main函数


@ 未定义指令
Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0

@ SVC
SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

@ 预取中止
PreAbort_Handler:
    ldr r0, =PreAbort_Handler
    bx r0

@ 数据中止
DataAbort_Handler:
    ldr r0, =DataAbort_Handler
    bx r0

@ 保留
Reserved_Handler:
    ldr r0, =Reserved_Handler
    bx r0

@ IRQ
IRQ_Handler:
    ldr r0, =IRQ_Handler
    bx r0

@ FIQ
FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0
