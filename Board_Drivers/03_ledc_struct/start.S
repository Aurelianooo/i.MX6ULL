.global _start

.global _bss_start
_bss_start :
    .word __bss_start

.global _bss_end
_bss_end :
    .word __bss_end

_start:
    @设置SVC模式
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x13
    msr cpsr, r0

    @清除.bss段
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0

clear_bss:
    str r2, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    ble clear_bss

    @设置SP指针
    ldr sp, =0x80200000
    b main
