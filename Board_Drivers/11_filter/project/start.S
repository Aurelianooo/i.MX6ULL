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

#if 0
    @ 设置中断向量偏移
    ldr r0, =0x87800000
    dsb
    isb
    MCR p15, 0, r0, c12, c0, 0  @ 设置VBAR寄存器
    dsb
    isb
#endif

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
    push {lr}
    push {r0-r3, r12}   @ 保存现场

    mrs r0, spsr
    push {r0}          @ 保存SPSR

    mrc p15, 4, r1, c15, c0, 0  @ 读取CBAR寄存器中GIC内存映射首地址
    add r1, r1, #0x2000  @ GIC的CPU接口寄存器偏移地址
    ldr r0, [r1, #0x0c]  @ 读取GICC_IAR寄存器，获取中断ID
    push {r0, r1}  @ 保存中断ID和GIC基地址

    cps #0x13  @ 切换到SVC模式
    push {lr}
    ldr r2, =system_irqhandler
    blx r2  @ 调用系统中断处理函数

    pop {lr}
    cps #0x12  @ 切换回IRQ模式
    pop {r0, r1}  @ 恢复中断ID和GIC基地址
    str r0, [r1, #0x10]  @ 写回GICC_EOIR寄存器，完成中断处理

    pop {r0}  @ 恢复SPSR
    msr spsr_cxsf, r0  @ 恢复SPSR

    pop {r0-r3, r12}   @ 恢复现场
    pop {lr}
    subs pc, lr, #4 @ 将lr-4赋值给pc

@ FIQ
FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0
