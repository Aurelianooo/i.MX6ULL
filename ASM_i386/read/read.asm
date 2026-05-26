
section .data                           ;数据段
   userMsg db 'Please enter a number: ' ;询问用户键盘输入一个数字
   lenUserMsg equ $-userMsg             ;消息的长度
   dispMsg db 'You have entered: '
   lenDispMsg equ $-dispMsg                 

section .bss           ;未初始化的数据
   num resb 5
        
section .text          ;代码段
   global _start

_start:                ;用户提示
   mov eax, 4
   mov ebx, 1
   mov ecx, userMsg
   mov edx, lenUserMsg
   int 80h

   ;读取并存储用户输入
   mov eax, 3
   mov ebx, 0
   mov ecx, num  
   mov edx, 5          ;该信息的5个字节(数字，1表示符号)
   int 80h
        
   ;输出消息'You have entered:'
   mov eax, 4
   mov ebx, 1
   mov ecx, dispMsg
   mov edx, lenDispMsg
   int 80h  

   ;输出输入的数字
   mov eax, 4
   mov ebx, 1
   mov ecx, num
   mov edx, 5
   int 80h  
    
   ; Exit code
   mov eax, 1
   mov ebx, 0
   int 80h
