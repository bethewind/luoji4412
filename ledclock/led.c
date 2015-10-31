//led.c文件
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)
// CMU_CPU
#define CLK_SRC_CPU (*(volatile unsigned int *)0x10044200)
#define CLK_DIV_CPU0 (*(volatile unsigned int *)0x10044500)
#define CLK_DIV_CPU1 (*(volatile unsigned int *)0x10044504)
// CMU_DMC
#define CLK_SRC_DMC (*(volatile unsigned int *)0x10040200)
#define CLK_DIV_DMC0 (*(volatile unsigned int *)0x10040500)
#define CLK_DIV_DMC1 (*(volatile unsigned int *)0x10040504)
// CMU_TOP
#define CLK_SRC_TOP0 (*(volatile unsigned int *)0x1003C210)
#define CLK_SRC_TOP1 (*(volatile unsigned int *)0x1003C214)
#define CLK_DIV_TOP (*(volatile unsigned int *)0x1003C510)
// CMU_LEFTBUS
#define CLK_SRC_LEFTBUS (*(volatile unsigned int *)0x10034200)
#define CLK_DIV_LEFTBUS (*(volatile unsigned int *)0x10034500)
// CMU_RIGHTBUS
#define CLK_SRC_RIGHTBUS (*(volatile unsigned int *)0x10038200)
#define CLK_DIV_RIGHTBUS (*(volatile unsigned int *)0x10038500)
// locktime
#define APLL_LOCK (*(volatile unsigned int *)0x10044000)
#define MPLL_LOCK (*(volatile unsigned int *)0x10044008)
#define EPLL_LOCK (*(volatile unsigned int *)0x1003C010)
#define VPLL_LOCK (*(volatile unsigned int *)0x1003C020)
// APLL
#define APLL_CON1 (*(volatile unsigned int *)0x10044104)
#define APLL_CON0 (*(volatile unsigned int *)0x10044100)
// MPLL
#define MPLL_CON0 (*(volatile unsigned int *)0x10040108)
#define MPLL_CON1 (*(volatile unsigned int *)0x1004010c)
// EPLL
#define EPLL_CON2 (*(volatile unsigned int *)0x1003C118)
#define EPLL_CON1 (*(volatile unsigned int *)0x1003C114)
#define EPLL_CON0 (*(volatile unsigned int *)0x1003C110)
// VPLL
#define VPLL_CON0 (*(volatile unsigned int *)0x1003C120)
#define VPLL_CON1 (*(volatile unsigned int *)0x1003C124)
#define VPLL_CON2 (*(volatile unsigned int *)0x1003C128)

void clock_common_cfg(void)
{
CLK_SRC_CPU = 0x01000001;
CLK_DIV_DMC0 = 0x00111713;
CLK_DIV_DMC1 = 0x01011171;
CLK_SRC_TOP0 = 0x01110000;
CLK_SRC_TOP1 = 0x00001000;
CLK_DIV_TOP = 0x00015470;
CLK_SRC_LEFTBUS = 0x00000001;
CLK_DIV_LEFTBUS = 0x00000013;
CLK_SRC_RIGHTBUS = 0x00000001;
CLK_DIV_RIGHTBUS = 0x00000013;
APLL_LOCK = 0x00000960;
MPLL_LOCK = 0x00000000;
EPLL_LOCK = 0x00000FFF;
VPLL_LOCK = 0x00000FFF;
CLK_DIV_CPU0 = 0x00773730;
CLK_DIV_CPU1 = 0x00000077;
APLL_CON1 = 0x00003800;
APLL_CON0 = 0xA0640301;
MPLL_CON1 = 0x00003800;
MPLL_CON0 = 0xA0640301;
EPLL_CON2 = 0x00000080;
EPLL_CON1 = 0x66010000;
EPLL_CON0 = 0x00600302;
VPLL_CON2 = 0x00000080;
VPLL_CON1 = 0x66016000;
VPLL_CON0 = 0x006F0302;
CLK_SRC_CPU = 0x01000001;
CLK_SRC_DMC = 0x00111000;
CLK_SRC_TOP0 = 0x01110000;
CLK_SRC_TOP1 = 0x00001000;

}

void system_clock_14G_init(void)
{

 /*
* 1. 在设置APLL之前, 先设置时钟源为晶振
*/
 CLK_SRC_CPU = 0x0;  //MUXAPLL选FINPLL，MUXCORE选MOUTAPLL
 

APLL_LOCK = 270 * 3;  //设置锁定时间: APLL_CON0中PDIV=3, 所以APLL_LOCK = 270x3 */
 
 CLK_SRC_CPU = 0x0;  //MUXAPLL选FINPLL，MUXCORE选MOUTAPLL
 CLK_DIV_CPU0 = 0x00773730; // CORE_RATIO,CORE2_RATIO配0
 
APLL_CON1 = 0x00803800; //默认
 
/*
* 设置APLL的M,P,S值, APLL输出 = 0xAF x 24MHz / (3 x 2 ^ 0) = 1.4GHz
* 使能APLL
*/
APLL_CON0 = (1<<31 | 0xAF<<16 | 3<<8 | 0x0);
 
/* 3. 设置MUX, 使用APLL的输出 */
CLK_SRC_CPU = 0x01000001;
}
 
void system_clock_24M_init(void)
{

 CLK_SRC_CPU = 0x0;  //MUXAPLL选FINPLL，MUXCORE选MOUTAPLL
 CLK_DIV_CPU0 = 0x00773730; // CORE_RATIO,CORE2_RATIO配0
}

void delay(volatile int time)
{
      for(; time > 0; time-- )
;
}


int main(void)
{

unsigned long tmp = 0;

//system_clock_24M_init();  //24M打开这句
system_clock_14G_init(); //1.4G打开这句


/*
* set GPM4_0 as output
*/
 tmp = GPM4CON;
 tmp &= ~0xffff;
 tmp |= 0x1111;
 GPM4CON = tmp;

while(1){
 /* GPM4_0 output low */
 GPM4DAT &= ~0xf;
delay(9999999);
GPM4DAT |= 0xf;
delay(9999999);
}


return 0;
 }
