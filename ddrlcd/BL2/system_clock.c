// CMU_CPU
#define CLK_SRC_CPU         (*(volatile unsigned int *)0x10044200)
#define CLK_DIV_CPU0            (*(volatile unsigned int *)0x10044500)
#define CLK_DIV_CPU1            (*(volatile unsigned int *)0x10044504)
// CMU_DMC
#define CLK_SRC_DMC         (*(volatile unsigned int *)0x10040200)
#define CLK_DIV_DMC0        (*(volatile unsigned int *)0x10040500)
#define CLK_DIV_DMC1        (*(volatile unsigned int *)0x10040504)
// CMU_TOP
#define CLK_SRC_TOP0            (*(volatile unsigned int *)0x1003C210)
#define CLK_SRC_TOP1            (*(volatile unsigned int *)0x1003C214)
#define CLK_DIV_TOP         (*(volatile unsigned int *)0x1003C510)
// CMU_LEFTBUS
#define CLK_SRC_LEFTBUS     (*(volatile unsigned int *)0x10034200)
#define CLK_DIV_LEFTBUS     (*(volatile unsigned int *)0x10034500)
// CMU_RIGHTBUS
#define CLK_SRC_RIGHTBUS    (*(volatile unsigned int *)0x10038200)
#define CLK_DIV_RIGHTBUS    (*(volatile unsigned int *)0x10038500)
// locktime
#define APLL_LOCK           (*(volatile unsigned int *)0x10044000)
#define MPLL_LOCK           (*(volatile unsigned int *)0x10044008)
#define EPLL_LOCK           (*(volatile unsigned int *)0x1003C010)
#define VPLL_LOCK           (*(volatile unsigned int *)0x1003C020)
// APLL
#define APLL_CON1           (*(volatile unsigned int *)0x10044104)
#define APLL_CON0           (*(volatile unsigned int *)0x10044100)
// MPLL
#define MPLL_CON0           (*(volatile unsigned int *)0x10040108)
#define MPLL_CON1           (*(volatile unsigned int *)0x1004010c)
// EPLL
#define EPLL_CON2           (*(volatile unsigned int *)0x1003C118)
#define EPLL_CON1           (*(volatile unsigned int *)0x1003C114)
#define EPLL_CON0           (*(volatile unsigned int *)0x1003C110)
// VPLL
#define VPLL_CON0           (*(volatile unsigned int *)0x1003C120)
#define VPLL_CON1           (*(volatile unsigned int *)0x1003C124)
#define VPLL_CON2           (*(volatile unsigned int *)0x1003C128)


/*
    函数名:
        system_clock_init
    功能:
        初始化4412的系统时钟
    最终结果:
        A=1400000000, M=800000000, E=96000000 V=350000000
        ARMCLK=1500000000, DMC=400000000, ACLK200=160000000
        ACLK100=100000000, ACLK160=160000000, ACLK133=133333333
*/
void system_clock_init(void)
{
    /* 1.设置CMU_CPU相关 */
    CLK_SRC_CPU = 0x0;          // 设置CMU_CPU部分中所有的MUX的源   

    /* 2.设置CMU_DMC相关 */
    /*
        CORE_TIMERS_RATIO = 0x0;
        COPY2_RATIO = 0x0;
        DMCP_RATIO = 0x1;
        DMCD_RATIO = 0x1;
        DMC_RATIO = 0x1;
        DPHY_RATIO = 0x1;
        ACP_PCLK_RATIO = 0x1;
        ACP_RATIO = 0x3;
    */
    CLK_DIV_DMC0 = ((0x0 << 28) | (0x0 << 24) | (0x1 << 20) | (0x1 << 16)    | (0x1 << 12)  | (0x1 << 8) | (0x1 << 4) | (0x3));
    CLK_DIV_DMC1 = 0x07071713;

    /* 3.设置CMU_TOP相关 */
    /*
        MUX_ONENAND_SEL = 0x0;
        MUX_ACLK_133_SEL = 0x0;
        MUX_ACLK_160_SEL = 0x0;
        MUX_ACLK_100_SEL = 0x0;
        MUX_ACLK_200_SEL = 0x0;
        MUX_VPLL_SEL = 0x1;
        MUX_EPLL_SEL = 0x1;
    */
    CLK_SRC_TOP0 = ((0x0 << 28) | (0x0 << 24) | (0x0 << 20) | (0x0 << 16)   | (0x0 << 12)   | (0x1 << 8) | (0x1 << 4));
    CLK_SRC_TOP1 = 0x01111000;
    
    /*
        ACLK_400_MCUISP_RATIO = 0x1;
        ACLK_266_GPS_RATIO = 0x2;
        ONENAND_RATIO = 0x1;
        ACLK_133_RATIO = 0x5;
        ACLK_160_RATIO = 0x4;
        ACLK_100_RATIO = 0x7;
        ACLK_200_RATIO = 0x4;
    */
    CLK_DIV_TOP = ((0x1 << 24) | (0x2 << 20) | (0x1 << 16) | (0x5 << 12) | (0x4 << 8) | (0x7 << 4) | (0x4));

    /* 3.设置CMU_LEFTBUS相关 */
    CLK_SRC_LEFTBUS = 0x10;
    
    /*
        GPL_RATIO = 0x1;
        GDL_RATIO = 0x3;
    */
    CLK_DIV_LEFTBUS = ((0x1 << 4) | (0x3));

    /* 4.设置CMU_RIGHTBUS相关 */
    CLK_SRC_RIGHTBUS = 0x10;
    
    /*
        GPR_RATIO = 0x1;
        GDR_RATIO = 0x3;
    */
    CLK_DIV_RIGHTBUS = ((0x1 << 4) | (0x3));

    /* 5.设置各个锁相环(PLL)的locktime */
    APLL_LOCK = (0x3 * 270);
    MPLL_LOCK = (0x3 * 270);
    EPLL_LOCK = (0x2 * 3000);
    VPLL_LOCK = (0x2 * 3000);
    /*
        APLL_RATIO = 0x2;
        CORE_RATIO = 0x0;
        CORE2_RATIO = 0x0;
        COREM0_RATIO = 0x3;
        COREM1_RATIO = 0x7;
        PERIPH_RATIO = 0x7;
        ATB_RATIO = 0x6;
        PCLK_DBG_RATIO = 0x1;
    */
    CLK_DIV_CPU0 = ((0x0 << 28) | (0x2 << 24) | (0x1 << 20) | (0x6 << 16) | (0x7 <<12) | (0x7 << 8) | (0x3 << 4) | (0x0));
    /*
        CORES_RATIO = 0x5;
        HPM_RATIO = 0x0;
        COPY_RATIO = 0x6;
    */
    CLK_DIV_CPU1 = ((0x5 << 8) |(0x0 << 4) | (0x6));

    /* 6.设置APLL = 1400000000 */
    APLL_CON1 = 0x00803800;
    APLL_CON0 = (1<<31 | 0xAF<<16 | 0x3<<8 | 0x0);

    /* 7.设置MPLL = 800000000 */
    MPLL_CON1 = 0x00803800;
    MPLL_CON0 = (1<<31 | 0x64<<16 | 0x3<<8 | 0x0);
    
    /* 8.设置EPLL = 96000000 */
    EPLL_CON2 = 0x00000080;
    EPLL_CON1 = 0x66010000;
    EPLL_CON0 = (1<<31 | 0x40<<16 | 0x2<<8 | 0x3);
    
    /* 9.设置VPLL = 350000000 */
    VPLL_CON2 = 0x00000080;
    VPLL_CON1 = 0x66010000;
    VPLL_CON0 = (1<<31 | 0x48<<16 | 0x2<<8 | 0x3);
    

    /*10.修改源*/
    CLK_SRC_CPU = 0x01000001;
    CLK_SRC_DMC = 0x00011000;
    CLK_SRC_TOP0 = 0x00000110;
    CLK_SRC_TOP1 = 0x01111000;
}

