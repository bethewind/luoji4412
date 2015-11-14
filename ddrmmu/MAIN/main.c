


#include "regs.h"

void (*uart_asm_putc)(int c) = 0x0202391c;
void (*uart_asm_putx)(int x) = 0x02023940;

#define GPM4CON (*(volatile unsigned int *)0xB10002E0)
#define GPM4DAT (*(volatile unsigned int *)0xB10002E4)

void init_ttb(unsigned long *ttb_base);
void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa);
void memset(char *buf, char ch, int size);
void led_blink(void);

void delay(volatile int time)
{
      for(; time > 0; time-- )
;
}

void main(void)
{	
	unsigned long c1_flags, ttb = 0x73000000;
	volatile int *p = 0x52345678;

	*p = 0x8;	

	init_ttb(ttb);
	mmap(ttb, 0x12345678, 0x52345678);
	mmap(ttb, 0xB10002E0, 0x110002E0);

	c1_flags = 1 | (1 << 3) | ( 1 << 11) | (1 << 28);

	__asm__ __volatile__ (
		"mvn r0, #0 \n"			
		"mcr p15, 0, r0, c3, c0, 0\n"

		"mcr p15, 0, %1, c2, c0, 0\n" //configure ttb

		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr %0, r0, %0\n"
		"mcr p15, 0, %0, c1, c0, 0\n" //enable mmu
		:
		: "r" (c1_flags), "r" (ttb)
		: "r0"
	);

	p = 0x12345678;
	uart_asm_putc('\r');
	uart_asm_putc('\n');
	uart_asm_putc('c');
	uart_asm_putc('y');
	uart_asm_putc('j');
	uart_asm_putc(':');
	uart_asm_putx(*p);
	uart_asm_putc('\r');
	uart_asm_putc('\n');
     
   	led_blink();
}

void init_ttb(unsigned long *ttb_base)
{
	unsigned long va, pa;

	memset(ttb_base, 0x00, 16 * 1024 );		

	for (va = 0x00000000; va < 0x10000000; va += 0x100000) { //Others
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}

	for (va = 0x10000000; va < 0x14000000; va += 0x100000) { //SFR
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
	}

	for (va = 0x40000000; va < 0x80000000; va += 0x100000) { //DRAM
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}
	
}

void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa)
{
	ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
}

void memset(char *buf, char ch, int size)
{
	int i;
	for (i = 0; i < size; i ++)
		buf[i] = ch;
}

void led_blink(void)
{

unsigned long tmp = 0;
	int i = 0;

	/*
	 *  GPM4_0-GPM4_3 设置为输出功能
	 */
	tmp = GPM4CON;
	tmp &= ~0xffff;
	tmp |= 0x1111;
	GPM4CON = tmp;
	
	/*
	 *  实现流水灯
	 */
	 while(1)
	 {
		GPM4DAT = i;
		if (++i == 16)
  			i = 0;
  		delay(9999999);
	 }
	
 }











