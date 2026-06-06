.global _start

_start:
    @ 第一时间关闭看门狗
    ldr r0, =0x020BC000
    mov r1, #0
    str r1, [r0]

    @设置SVC模式
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x13
    msr cpsr, r0

    @清除.bss段
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0

clear_bss:
    str r2, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    ble clear_bss

    @设置SP指针
    ldr sp, =0x80200000
    b main
