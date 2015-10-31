.text
.globl _start
_start:
 
/*
* set GPM4_0 as output
*/
ldr r0, =0x110002E0 // GPM4CON的地址是0x110002E0
ldr r1, [r0] // 先读出原值
bic r1, r1, #0xf // 清除bit[3:0]
orr r1, r1, #1 // 设置bit[3:0]为0b0001
str r1, [r0] // 写入GPM4CON


leds_loop:
/*
*set GPM4_0 as Low
*/
ldr r0, =0x110002E4 // GPM4DAT的地址是0x110002E4
ldr r1, [r0] // 读出原值
bic r1, r1, #1 // 清除bit[0]为0,led亮
str r1, [r0] // 写入GPM4_0
ldr r2,=0xffffff
bl delay

orr r1, r1, #0xf
str r1, [r0] // 写1 led灭
ldr r2,=0xffffff
bl delay

b leds_loop
halt_loop:
b halt_loop
 
delay:
sub r2,r2,#1 //sub 减法
cmp r2,#0x0 //将r0 与0比较
bne delay //b是跳 ne 是不相等 ，不相等就跳到delay
mov pc,lr //lr 里存的是调用函数时的下一条指令，让Pc指针指向lr就可以完成函数的返回
