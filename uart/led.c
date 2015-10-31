// GPIO
#define GPA0CON (*(volatile unsigned int *)0x11400000)
// MPLL
#define MPLL_CON0 (*(volatile unsigned int *)0x10040108)
#define CLK_SRC_DMC (*(volatile unsigned int *)0x10040200)
#define CLK_SRC_TOP1 (*(volatile unsigned int *)0x1003C214)
// system clock
#define CLK_SRC_PERIL0 (*(volatile unsigned int *)0x1003C250)
#define CLK_DIV_PERIL0 (*(volatile unsigned int *)0x1003C550)
// UART
#define UFCON0 (*(volatile unsigned int *)0x13800008)
#define ULCON0 (*(volatile unsigned int *)0x13800000)
#define UCON0 (*(volatile unsigned int *)0x13800004)
#define UBRDIV0 (*(volatile unsigned int *)0x13800028)
#define UFRACVAL0 (*(volatile unsigned int *)0x1380002c)
#define UTXH0 (*(volatile unsigned int *)0x13800020)
#define URXH0 (*(volatile unsigned int *)0x13800024)
 
#define UTRSTAT0 (*(volatile unsigned int *)0x13800010)
 
void UartInit()
{
/* 1.设置相应的GPIO用于串口功能 */
unsigned long tmp = 0;
 
tmp = GPA0CON;
tmp &= ~(0xff); //设置UART0对应的GPIO为UART功能
tmp |= 0x22;
GPA0CON = tmp;
 

MPLL_CON0 = (1<<31 | 0x64<<16 | 0x3<<8 | 0x0);  //设置MPLL 输出 800MHz，FOUT = MDIV x FIN / (PDIV x 2 ^ SDIV) = 0x64 x 24MHz / (3 x 2^ 0) = 800MHz
 
CLK_SRC_DMC = 0x00011000; //bit[12]即MUX_MPLL_SEL=1, SCLKMPLLL使用MPLL的输出
 
CLK_SRC_TOP1 = 0x01111000; //bit[12]即MUX_MPLL_USER_SEL_T=1, MUXMPLL使用SCLKMPLLL

CLK_SRC_PERIL0 = ((0 << 24) | (0 << 20) | (6 << 16) | (6 << 12) | (6<< 8) | (6 << 4) | (6)); //bit[3:0]即UART0_SEL=6, MOUTUART0使用SCLKMPLL_USER_T，所以, MOUTUART0即等于MPLL的输出, 800MHz
 
CLK_DIV_PERIL0 = ((7 << 20) | (7 << 16) | (7 << 12) | (7 << 8) | (7 << 4) | (7)); //bit[3:0]即UART0_RATIO=7,所以SCLK_UART0=MOUTUART0/(7+1)=100MHz
 
/* 3.设置串口0相关 */
/* 设置FIFO中断触发阈值
* 使能FIFO
*/
UFCON0 = 0x111;
 
/* 设置数据格式: 8n1, 即8个数据位,没有较验位,1个停止位 */
ULCON0 = 0x3;
 
/* 工作于中断/查询模式
* 另一种是DMA模式,本章不使用
*/
UCON0 = 0x5;
 
/* SCLK_UART0=100MHz, 波特率设置为115200
* 寄存器的值如下计算:
* DIV_VAL = 100,000,000 / (115200 * 16) - 1 = 53.25
* UBRDIVn0 = 整数部分 = 53
* UFRACVAL0 = 小数部分 x 16 = 0.25 * 16 = 4
*/
UBRDIV0 = 53;
UFRACVAL0 = 4;
 
}
 
char getc(void)
{
char c;
/* 查询状态寄存器，直到有有效数据 */
while (!(UTRSTAT0 & (1<<0)));
 
c = URXH0; /* 读取接收寄存器的值 */
 
return c;
}
 
void putc(char c)
{
/* 查询状态寄存器，直到发送缓存为空 */
while (!(UTRSTAT0 & (1<<2)));
 
UTXH0 = c; /* 写入发送寄存器 */
 
return;
}
 
void puts(char *s)
{
while (*s)
{
putc(*s);
s++;
}
}

int main(void)
{
char rec;
 
UartInit();
 
while(1)
{
rec = getc();
rec++;
putc('\r');
putc('\n');
putc(rec);
}
 
return 0;
}
