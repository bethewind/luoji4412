//led.c文件
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

void delay(volatile int time)
{
      for(; time > 0; time-- )
;
}


int main(void)
{

unsigned long tmp = 0;


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
