//led.c文件
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

#define GPX3CON (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT (*(volatile unsigned int *)0x11000C64)

int main(void)
{
    int val;
    int i;


/*
* 配置GPM4_0,GPM4_1,GPM4_2,GPM4_3为输出引脚
* 对应LED1/2/3/4
*/

 GPM4CON = 0x1111;

 /* 设置K1对应的GPIO(GPX3_2)为输入 */
 GPX3CON &= ~(0xf << 8);  //把[11:8]位清0

 while (1)
 {

	 val = GPX3DAT;
	 /* 读出按键引脚状态 */

	 if (val & (1<<2)) /* 按键是松开状态 : 高电平 */
	 {
	 	/* 熄灭对应LED : GPIO输出高电平 */
	 	GPM4DAT |= (15);
	 }
	 else
	 {
	 	/* 否则点亮LED : GPIO输出低电平 */
	 	GPM4DAT &= ~(15);
	 }

 }


	return 0;
}
