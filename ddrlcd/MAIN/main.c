#include "regs.h"

#define RGB888(r, g, b)  (((r) << 16) | ((g) << 8) | (b) )
void clean_screen(unsigned long *fb, int w, int h)
{
	// green
	int i, j;
	for (i = 0; i < h; i ++) {
		for (j = 0; j < w; j ++) {
			fb[i * w + j] = RGB888(0, 255, 0);
		}		
	}
	// blue
	for (i = 200; i < h-200; i ++) {
		for (j = 200; j < w-300; j ++) {
			fb[i * w + j] = RGB888(0, 0, 255);
		}		
	}
}

void lcd_init(unsigned long fb)
{

	//Blacklight
	GPD0CON  &= ~(0xf<<0);
	GPD0CON  |=  (0x1<<0);

	GPD0PUD  &= ~(0x3<<0);
	GPD0PUD  |=  (0x2<<0);

	GPD0DAT  &= ~(0x1<<0);
	GPD0DAT  |=  (0x0<<0);
//Blacklight
	GPX3CON  &= ~(0xf<<20);
	GPX3CON  |=  (0x1<<20);

	GPX3PUD  &= ~(0x3<<10);
	GPX3PUD  |=  (0x2<<10);

	GPX3DAT  &= ~(0x1<<5);
	GPX3DAT  |=  (0x1<<5);
    /*
     *<Exyons 4412 datasheet pg138 pg141 pg144 pg147>
     *
     * GPF0CON : [31:0] : 0x2
     * GPF1CON : [31:0] : 0x2
     * GPF2CON : [31:0] : 0x2
     * GPF3CON : [31:0] : 0x2
     * */
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON &= ~(0xffff);
	GPF3CON |= 0x2222;
    
    /*
     *<Exyons 4412 datasheet pg526>
     *CLK_DIV_LCD: 
     *          [3:0]:FIMD0_RATIO   0
     *              SCLK_FIMD0 = MOUTFIMD0/(FIMD0_RATIO + 1) 
     *                         = MOUTFIMD0/1 = 800MHz
     *              MOUTFIMD0 == SCLKmpll_user_t == 800MHz      <Exyons 4412 datasheet pg453> LCD0_BLK
     * */
	CLK_DIV_LCD &= ~0xf;
    /*
     *<Exyons 4412 datasheet pg501>
     *CLK_SRC_LCD0:
     *          [3:0]:FIMD0_SEL 0110 ===> SCLKmpll_user_t 选择时钟源为SCLKmpll_user_t
     *
     * */
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 6;
	//LCD0_SYS_PWR_REG == 7 Don't use
    
    
    /*<Exyons 4412 datasheet pg1799>
     *Using the display controller data, you can select one of the above data paths by setting LCDBLK_CFG Register
     *(0x1001_0210). For more information, refer to the "System Others" manual.
     *
     *
     * <Exyons 4412 datasheet pg880>
     * LCDBLK_CFG: 
     *          [1] : FIMD of LBLK0 Bypass Selection    1 : FIMD Bypass   使用FIMD接口
     *
     * LCDBLK_CFG :
     *          [0]:MIE0_DISPON     1 :  PWM outpupt enable 
     *
     *
     * */
	LCDBLK_CFG |= 1 << 1;
    LCDBLK_CFG2 |= 1;

    /*
     *<Exyons 4412 datasheet pg1869>
     *VIDCON0:
     *     [13:6]: CLKVAL_F     //设置lcd时钟分频系数
     *
     *  VCLK == 33.3Mhz         <S700-AT070TN92 pg14> DCLK  Frequency ===> Type : 33.3Mhz
     *  VCLK = FIMD * SCLK/(CLKVAL+1)
     *  VCLK =  800000000 / (CLKVAL + 1)   
     *  33300000 = 800000000 /(CLKVAL + 1)
     *  CLKVAL + 1 = 24.02 
     *  CLKVAL = 23
     * */
	VIDCON0 = (23 << 6);

    /*
     *<Exyons 4412 datasheet pg1870 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
     *VIDTCON1:
     *      [5]:IVSYNC  ===> 1 : Inverted(反转)
     *      [6]:IHSYNC  ===> 1 : Inverted(反转)
     *      [7]:IVCLK   ===> 1 : Fetches video data at VCLK rising edge (下降沿触发)
     *      [10:9]:FIXVCLK  ====> 01 : VCLK running 
     * */
	VIDCON1 = (1 << 9) | (1 << 7) | (1 << 5) | (1 << 6);

    /*
     *<Exyons 4412 datasheet pg1874 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
     *VIDTCON0: 
     *       [23:16]:  VBPD + 1 <------> tvpw (1 - 20)  13
     *       [15:8]: VFPD + 1 <------> tvfp 22
     *       [7:0]: VSPW  + 1 <------> tvb - tvpw = 23 - 13 = 10
     * */
	VIDTCON0 = (12 << 16) | (21 << 8) | (9);
     /*<Exyons 4412 datasheet pg1874 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
     *VIDTCON1: 
     *       [23:16]:  HBPD + 1 <------> thpw (1 - 40)  36 
     *       [15:8]:   HFPD + 1 <------> thfp 210 
     *       [7:0]:    HSPW  + 1 <------> thb - thpw = 46 - 36 = 10
     */
	VIDTCON1 = (35 << 16) | (209 << 8) | (9);

    /*
     *<Exyons 4412 datasheet pg1875>
     * 
     *HOZVAL = (Horizontal display size) – 1 and LINEVAL = (Vertical display size) – 1.
     * Horizontal(水平) display size : 800 
     *Vertical(垂直) display size : 480
     * */
	VIDTCON2 = (599 << 11) | 1023;

	//win0
#ifdef BPP565
    /*
     *<Exyons 4412 datasheet pg1877>
     *WINCON0:
     *  [16]:Specifies Half-Word swap control bit.  1 = Enables swap
     *  [5:2]: Selects Bits Per Pixel (BPP) mode for Window image : 0101 ===> 16BPP
     *  [1]:Enables/disables video output   1 = Enables
     *
     * */
	WINCON0 = (1 << 16) | (5 << 2) | 1;

    /*
     *<Exyons 4412 datasheet pg1895>
     *VIDOSD0C:Specifies the Window Size (窗口尺寸 单位为word)
     *          
     *
     * */
	VIDOSD0C = 600 * 1024 >> 1;
#else
    /*
     *<Exyons 4412 datasheet pg1877>
     *WINCON0:
     *  [5:2]: Selects Bits Per Pixel (BPP) mode for Window image : 1011 ===> 24BPP
     *  [1]:Enables/disables video output   1 = Enables
     *
     * */
	WINCON0 = (11 << 2) | 1;

    /*
     *<Exyons 4412 datasheet pg1895>
     *VIDOSD0C:Specifies the Window Size (窗口尺寸 单位为word)
     *          
     *
     * */
	VIDOSD0C = 600 * 1024;
#endif

	//SHADOWCON &= ~(1 << 5); Don't use

    /*
     *<Exyons 4412 datasheet pg1891 pg1801>
     *[0]: Enables Channel 0. 1 = Enables
     * */
    SHADOWCON |= 1;


    /*
     *<Exyons 4412 datasheet  pg1894 pg1801>
     *[18:16] Selects Channel 0's channel. ===> 001 = Window 0
     *[2:0] Selects Window 0's channel.  ===> 001 = Channel 0 
     * 
     *
     * */
	WINCHMAP2 &= ~(7 << 16);
	WINCHMAP2 |= 1 << 16;
	WINCHMAP2 &= ~7;
	WINCHMAP2 |= 1;

    /*
     *<Exyons 4412 datasheet  pg1895>
     *VIDOSD0A: LCD左上角坐标
     *VIDOSD0B: LCD右下角坐标
     */

	VIDOSD0A = 0;
	VIDOSD0B = (1023 << 11) | 599;

    /*
     *<Exyons 4412 datasheet  pg1902>
     * VIDW00ADD0B0 : window0 frame buffer 起始地址 
     *  VIDW00ADD1B0 : window0 frame buffer 结束地址
     * */
	VIDW00ADD0B0 = fb;
	VIDW00ADD1B0 = fb + 1024 * 600 * 4;
        VIDW00ADD2  = 1024;

    /*
     * <Exyons 4412 datasheet pg1869>
     * Display On: ENVID and ENVID_F are set to "1".
     *  [0]:ENVID ===> 1 = Enables
     *  [1]:ENVID_F ===> 1 = Enables 
     * */
	VIDCON0 |= 3;	
}

int main()
{
	unsigned long fb = 0x53000000;

	clean_screen(fb, 1024, 600);

    	lcd_init(fb);
		
    
}


