/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#pragma once

#define EINT0CON0 (*(volatile unsigned long *)0x7F008900)
#define EINT0MASK (*(volatile unsigned long *)0x7F008920)
#define EINT0PEND (*(volatile unsigned long *)0x7F008924)

#define GPMCON (*(volatile unsigned long *)0x7F008820)
#define GPMDAT (*(volatile unsigned long *)0x7F008824)
#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)

#define GPOCON (*(volatile unsigned long *)0x7F008140)
#define GPPCON (*(volatile unsigned long *)0x7F008160)

#define VIC0VECTADDR0 (*(volatile unsigned long *)0x71200100)
#define VIC0VECTADDR26 (*(volatile unsigned long *)0x71200168)
#define VIC0IRQSTATUS (*(volatile unsigned long *)0x71200000)
#define VIC0ADDRESS   (*(volatile unsigned long *)0x71200f00)
#define VIC0INTENABLE (*(volatile unsigned long *)0x71200010)
#define VIC0INTSELECT (*(volatile unsigned long *)0x7120000C)
#define VIC0SOFTINT   (*(volatile unsigned long *)0x71200018)
#define VIC0SOFTINTCLEAR (*(volatile unsigned long *)0x7120001c)

#define VIC1VECTADDR0 (*(volatile unsigned long *)   0x71300100)
#define VIC1VECTADDR26 (*(volatile unsigned long *)  0x71300168)
#define VIC1IRQSTATUS (*(volatile unsigned long *)   0x71300000)
#define VIC1ADDRESS   (*(volatile unsigned long *)   0x71300f00)
#define VIC1INTENABLE (*(volatile unsigned long *)   0x71300010)
#define VIC1INTSELECT (*(volatile unsigned long *)   0x7130000C)
#define VIC1SOFTINT   (*(volatile unsigned long *)   0x71300018)
#define VIC1SOFTINTCLEAR (*(volatile unsigned long *)0x7130001c)

#define WTCON  (*(volatile unsigned long *)0x7E004000)
#define WTDAT  (*(volatile unsigned long *)0x7E004004)
#define WTCNT  (*(volatile unsigned long *)0x7E004008)
#define WTCLRINT  (*(volatile unsigned long *)0x7E00400C)


#define ADCCON 			(*(volatile unsigned long *)0x7E00B000)
#define ADCTSC 			(*(volatile unsigned long *)0x7E00B004)
#define ADCDLY 			(*(volatile unsigned long *)0x7E00B008)
#define ADCDAT0 		(*(volatile unsigned long *)0x7E00B00C)
#define ADCDAT1 		(*(volatile unsigned long *)0x7E00B010)
#define ADCUPDN 		(*(volatile unsigned long *)0x7E00B014)
#define ADCCLRINT 		(*(volatile unsigned long *)0x7E00B018)
#define ADCCLRINTPNDNUP   	(*(volatile unsigned long *)0x7E00B020)

#define ULCON1 		(*(volatile unsigned long *)0x7F005400)
#define UCON1 		(*(volatile unsigned long *)0x7F005404)
#define UFCON1 		(*(volatile unsigned long *)0x7F005408)
#define UMCON1 		(*(volatile unsigned long *)0x7F00540C)
#define UTRSTAT1 	(*(volatile unsigned long *)0x7F005410)
#define UERSTAT1 	(*(volatile unsigned long *)0x7F005414)
#define UFSTAT1 	(*(volatile unsigned long *)0x7F005418)
#define UMSTAT1 	(*(volatile unsigned long *)0x7F00541C)
#define UTXH1 		(*(volatile unsigned char *)0x7F005420)
#define URXH1 		(*(volatile unsigned char *)0x7F005424)
#define UBRDIV1 	(*(volatile unsigned long *)0x7F005428)
#define UDIVSLOT1 	(*(volatile unsigned long *)0x7F00542C)
#define UINTP1 		(*(volatile unsigned long *)0x7F005430)
#define UINTSP1 	(*(volatile unsigned long *)0x7F005434)
#define UINTM1 		(*(volatile unsigned long *)0x7F005438)

#define  ULCON3   (*(volatile unsigned long *)0x7F005C00) 
#define   UCON3   (*(volatile unsigned long *)0x7F005C04) 
#define  UFCON3   (*(volatile unsigned long *)0x7F005C08) 
#define UTRSTAT3  (*(volatile unsigned long *)0x7F005C10) 
#define UERSTAT3  (*(volatile unsigned long *)0x7F005C14) 
#define  UFSTAT3  (*(volatile unsigned long *)0x7F005C18) 
#define   UTXH3   (*(volatile unsigned char *)0x7F005C20) 
#define   URXH3   (*(volatile unsigned char *)0x7F005C24) 
#define  UBRDIV3  (*(volatile unsigned long *)0x7F005C28) 
#define UDIVSLOT3 (*(volatile unsigned long *)0x7F005C2C) 
#define    INTP3  (*(volatile unsigned long *)0x7F005C30) 
#define  UINTSP3  (*(volatile unsigned long *)0x7F005C34) 
#define   UINTM3  (*(volatile unsigned long *)0x7F005C38)

#define GPACON  (*(volatile unsigned long *)0x7F008000)
#define GPBCON  (*(volatile unsigned long *)0x7F008020)

#define NFCONF 		(*(volatile unsigned long *)0x70200000)
#define NFCONT 		(*(volatile unsigned long *)0x70200004)
#define NFCMMD 		(*(volatile unsigned char *)0x70200008)
#define NFADDR		(*(volatile unsigned char *)0x7020000c)
#define NFDATA		(*(volatile unsigned char *)0x70200010)
#define NFMECCD0 	(*(volatile unsigned long *)0x70200014)
#define NFMECCD1 	(*(volatile unsigned long *)0x70200018)
#define NFSECCD 	(*(volatile unsigned long *)0x7020001C)
#define NFSBLK 		(*(volatile unsigned long *)0x70200020)
#define NFEBLK 		(*(volatile unsigned long *)0x70200024)
#define NFSTAT 		(*(volatile unsigned long *)0x70200028)
#define NFECCERR0 	(*(volatile unsigned long *)0x7020002C)
#define NFECCERR1 	(*(volatile unsigned long *)0x70200030)
#define NFMECC0 	(*(volatile unsigned long *)0x70200034)
#define NFMECC1 	(*(volatile unsigned long *)0x70200038)
#define NFSECC 		(*(volatile unsigned long *)0x7020003C)
#define NFMLCBITPT 	(*(volatile unsigned long *)0x70200040)
#define NF8ECCERR0 	(*(volatile unsigned long *)0x70200044)
#define NF8ECCERR1 	(*(volatile unsigned long *)0x70200048)
#define NF8ECCERR2 	(*(volatile unsigned long *)0x7020004C)
#define NFM8ECC0 	(*(volatile unsigned long *)0x70200050)
#define NFM8ECC1 	(*(volatile unsigned long *)0x70200054)
#define NFM8ECC2 	(*(volatile unsigned long *)0x70200058)
#define NFM8ECC3 	(*(volatile unsigned long *)0x7020005C)
#define NFMLC8BITPT0 	(*(volatile unsigned long *)0x70200060)
#define NFMLC8BITPT1 	(*(volatile unsigned long *)0x70200064)

#define MEM_SYS_CFG 	(*(volatile unsigned long *)0x7E00F120) //pg160

#define P1MEMSTAT 	(*(volatile unsigned long *)0x7E001000)
#define P1MEMCCMD 	(*(volatile unsigned long *)0x7E001004)
#define P1DIRECTCMD 	(*(volatile unsigned long *)0x7E001008)
#define P1MEMCFG 	(*(volatile unsigned long *)0x7E00100C)
#define P1REFRESH 	(*(volatile unsigned long *)0x7E001010)
#define P1CASLAT 	(*(volatile unsigned long *)0x7E001014)
#define P1T_DQSS 	(*(volatile unsigned long *)0x7E001018)
#define P1T_MRD 	(*(volatile unsigned long *)0x7E00101C)
#define P1T_RAS 	(*(volatile unsigned long *)0x7E001020)
#define P1T_RC 		(*(volatile unsigned long *)0x7E001024)
#define P1T_RCD 	(*(volatile unsigned long *)0x7E001028)
#define P1T_RFC 	(*(volatile unsigned long *)0x7E00102C)
#define P1T_RP 		(*(volatile unsigned long *)0x7E001030)
#define P1T_RRD 	(*(volatile unsigned long *)0x7E001034)
#define P1T_WR 		(*(volatile unsigned long *)0x7E001038)
#define P1T_WTR 	(*(volatile unsigned long *)0x7E00103C)
#define P1T_XP 		(*(volatile unsigned long *)0x7E001040)
#define P1T_XSR 	(*(volatile unsigned long *)0x7E001044)
#define P1T_ESR 	(*(volatile unsigned long *)0x7E001048)
#define P1MEMCFG2 	(*(volatile unsigned long *)0x7E00104C)
#define P1MEMCFG3 	(*(volatile unsigned long *)0x7E001050)
#define P1_chip_0_cfg 	(*(volatile unsigned long *)0x7E001200)
#define P1_chip_1_cfg 	(*(volatile unsigned long *)0x7E001204)
#define P1_user_stat 	(*(volatile unsigned long *)0x7E001300)
#define P1_user_cfg 	(*(volatile unsigned long *)0x7E001304)















