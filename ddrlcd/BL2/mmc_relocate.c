
#define eFUSE_SIZE		(1 * 512)	// 512 Byte eFuse, 512 Byte reserved
#define MOVI_BLKSIZE		(1<<9) /* 512 bytes */
#define PART_SIZE_BL1		(16 * 1024)
#define PART_SIZE_UBOOT		(328 * 1024)
#define PART_SIZE_KERNEL	(6 * 1024 * 1024)
#define PART_SIZE_ROOTFS	(26 * 1024 * 1024)
#define PART_SIZE_TZSW		(160 * 1024)

#define MOVI_FWBL1_BLKCNT	(PART_SIZE_FWBL1 / MOVI_BLKSIZE)
#define MOVI_BL1_BLKCNT		(PART_SIZE_BL1 / MOVI_BLKSIZE)
#define MOVI_ENV_BLKCNT		(CONFIG_ENV_SIZE / MOVI_BLKSIZE)	/* 16KB */
#define MOVI_UBOOT_BLKCNT	(PART_SIZE_UBOOT / MOVI_BLKSIZE)	/* 328KB */
#define MOVI_ZIMAGE_BLKCNT	(PART_SIZE_KERNEL / MOVI_BLKSIZE)	/* 6MB */
#define MOVI_ROOTFS_BLKCNT	(PART_SIZE_ROOTFS / MOVI_BLKSIZE)	/* 26MB */
#define MOVI_TZSW_BLKCNT	(PART_SIZE_TZSW / MOVI_BLKSIZE)		/* 160KB */

#define MOVI_UBOOT_POS		((eFUSE_SIZE / MOVI_BLKSIZE) + MOVI_FWBL1_BLKCNT + MOVI_BL1_BLKCNT)

extern void uart_asm_putc(int c);
extern void uart_asm_putx(int x);


typedef unsigned int  (*copy_sd_mmc_to_mem) \
	(unsigned int start_block, unsigned int block_count, unsigned int* dest_addr);

//typedef unsigned int (*copy_sd_mmc_to_mem) (unsigned int  channel, unsigned int  start_block, unsigned char block_size, unsigned int  *trg, unsigned int  init);

#define ISRAM_ADDRESS	0x02020000
#define SECURE_CONTEXT_BASE 0x02023000
#define EXTERNAL_FUNC_ADDRESS	(ISRAM_ADDRESS + 0x0030)
#define EXT_eMMC43_BL2_ByCPU_ADDRESS	(EXTERNAL_FUNC_ADDRESS + 0x4)
#define MSH_ReadFromFIFO_eMMC_ADDRESS	(EXTERNAL_FUNC_ADDRESS + 0x14)
#define MSH_EndBootOp_eMMC_ADDRESS	(EXTERNAL_FUNC_ADDRESS + 0x18)
#define LoadImageFromUsb_ADDRESS	(EXTERNAL_FUNC_ADDRESS + 0x40)


/* DRAM Base */
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_MAPPED_RAM_BASE + 0x3e00000
#define CONFIG_PHY_UBOOT_BASE		CONFIG_SYS_SDRAM_BASE + 0x3e00000



#define SDMMC_ReadBlocks(uStartBlk, uNumOfBlks, uDstAddr)	\
	(((void(*)(unsigned int, unsigned int, unsigned int*))(*((unsigned int *)EXTERNAL_FUNC_ADDRESS)))(uStartBlk, uNumOfBlks, uDstAddr))


void copy_code_to_dram(void)
{
	//unsigned long ch;
	void (*user_bin)(void);
	//ch = *(volatile unsigned int *)(0xD0037488);//need modify

	// 函数指针
	//copy_sd_mmc_to_mem copy_bl2 = (copy_sd_mmc_to_mem) (*(unsigned int *) (0xD0037F98));
	//copy_bl2(0, 49, 32,(unsigned int *)0x23E00000, 0);

		// 49:源,代码位于扇区49,1 sector = 512 bytes
		// 32:长度，拷贝32 sector，即16K
		// 0x23E00000:目的,链接地址0x23E00000
	
	volatile unsigned long  count=0x100000;
	while(count>0){
		count--;}

	//uart_asm_putc('C');
	//uart_asm_putc('O');
	//uart_asm_putc('P');
	//uart_asm_putc('Y');
	//uart_asm_putc('\r');
	//uart_asm_putc('\n');
	
	SDMMC_ReadBlocks(49,32,(unsigned int *)0x43e00000);
	//uart_asm_putx("now copy OVER!!!!/n");

	//uart_asm_putc('O');
	//uart_asm_putc('V');
	//uart_asm_putc('E');
	//uart_asm_putc('R');
	//uart_asm_putc('\r');
	//uart_asm_putc('\n');


	unsigned int *p;
	int i;
	

	p = (unsigned int *) 0x43e00000;
	for (i = 0; i < 100; i++) {
	//uart_asm_putx(*(p+i));
	//uart_asm_putc(' ');
	}
	
	
	// 跳转到DRAM
    user_bin = (void *)0x43e00000;
    (*user_bin)();
}
