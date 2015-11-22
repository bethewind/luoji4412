
//IIC
#define iic_base 0x13860000
#define I2CCON0 (*(volatile unsigned int *)(iic_base+0x0000))
#define I2CSTAT0 (*(volatile unsigned int *)(iic_base+0x0004))
#define I2CADD0 (*(volatile unsigned int *)(iic_base+0x0008))
#define I2CDS0 (*(volatile unsigned int *)(iic_base+0x000C))
#define I2CLC0 (*(volatile unsigned int *)(iic_base+0x0010))
#define GPD1CON (*(volatile unsigned int *)0x114000C0)
#define GPD1PUD (*(volatile unsigned int *)0x114000C8)

void (*uart_asm_putc)(int c) = 0x02023918;
void (*uart_asm_putx)(int x) = 0x0202393c;

void udelay(volatile int u)
{

volatile int i,j; 
for(j=0;j<u;j++) 
{ for(i=0 ; i < 1000 ; i++) { } }

}

void printf(char *str)
{
	while (*str)
	{
	 uart_asm_putc(*str);
         str++;
	}
}

void iic_init()
{
  GPD1CON &= ~(0xff);
  GPD1CON |= (0x22);
  GPD1PUD = 0;

  I2CCON0 = 0x1 | (1 << 5) | (1 << 6);
  //I2CADD0 = 0xc0;
  I2CSTAT0 = 0x10;
  I2CLC0 = 7;
}

void iic_dest(void)
{
  I2CCON0 = 0;
  I2CSTAT0 = 0;
}

void iic_master_write(unsigned long slave_addr, unsigned long reg, char val)
{
  char data[2];
  int cnt = 2;

  data[0] = reg;
  data[1] = val;

  while(I2CSTAT0 & (1 << 5));

  I2CCON0 |= (1 << 7);
  I2CDS0 = slave_addr;
  I2CSTAT0 = 0xf0;
  udelay(10);

  int pt = 0;
  while(cnt >= 0) {
       if (I2CCON0 & 0x10) {
		if (0 == cnt)
			break;

		cnt--;
		I2CDS0 = data[pt++];
		udelay(1);
		I2CCON0 &= ~(1 << 4);
	}
  }

  I2CSTAT0 = 0xd0;
  I2CCON0 &= ~(1 << 4);
  udelay(10);

}

void iic_master_read(unsigned long slave_addr, unsigned long reg, unsigned char* val)
{
  int cnt = 1;

  while(I2CSTAT0 & (1 << 5));

  udelay(10);  
  I2CCON0 |= (1 << 7);
  I2CDS0 = slave_addr;
  I2CSTAT0 = 0xf0;
  udelay(10);

  while(cnt >= 0) {
       if (I2CCON0 & 0x10) {
		if ((cnt--) == 0)
			break;

		I2CDS0 = reg;
		udelay(1);
		I2CCON0 &= ~(1 << 4);
	}
  }

  I2CSTAT0 = 0xd0;
  I2CCON0 &= ~(1 << 4);
  udelay(10);

  //-------------------read
  char data[3];
  while(I2CSTAT0 & (1 << 5));
  udelay(10);
  I2CCON0 |= (1 << 7);
  udelay(10);
  I2CDS0 = slave_addr;
  I2CSTAT0 = 0xb0;
  udelay(10);

  cnt = 0;
  while (cnt < 3) {
	if (I2CCON0 & 0x10) {
		data[cnt] = I2CDS0;
 		cnt++;

		I2CCON0 &= ~(1 << 4);
		udelay(10);
	}
  }
  I2CSTAT0 = 0x90;
  udelay(10);
  *val = data[1];
}

int main(void)
{
char rec;
unsigned char value = 0;

printf("\n\r\n\r");

iic_init();

printf("\n\r");
iic_master_write(0xa0, 0x3, 0x15);
iic_master_read(0xa0, 0x3, &value);
printf("addr 0x3 value is: ");
uart_asm_putx(value);
printf("\n\r");

iic_dest();
 
return 0;
}
