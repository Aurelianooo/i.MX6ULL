
section .text
   global _start     ;必须声明为链接器（ld）
_start:             ;告诉链接器入口点
        
   ;写名字“Alex Mo”
   mov  edx,9       ;message length
   mov  ecx, name   ;message to write
   mov  ebx,1       ;file descriptor (stdout)
   mov  eax,4       ;system call number (sys_write)
   int  0x80        ;call kernel
        
   mov  [name],  dword 'Feng'    ; Changed the name to Feng Mo
        
   ;writing the name 'Feng Mo'
   mov  edx,9       ;message length
   mov  ecx,name    ;message to write
   mov  ebx,1       ;file descriptor (stdout)
   mov  eax,4       ;system call number (sys_write)
   int  0x80        ;call kernel
        
   mov  eax,1       ;system call number (sys_exit)
   int  0x80        ;call kernel

section .data
name db 'Alex Mo ', 0xa
