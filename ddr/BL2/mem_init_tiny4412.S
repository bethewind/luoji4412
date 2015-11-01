/*
 * (C) Copyright 2011 Samsung Electronics Co. Ltd
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "tiny4412.h"
#include "exynos4412.h"
#include "tiny4412_val.h"


#define MCLK_400 1


	.globl mem_init
mem_init:

	/* Async bridge configuration at CPU_core:
	 * 1: half_sync
	 * 0: full_sync */
	ldr	r0, =0x10010350
	mov	r1, #1
	str	r1, [r0]


/*****************************************************************/
/*DREX0***********************************************************/
/*****************************************************************/

	ldr	r0, =APB_DMC_0_BASE

	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	ldr	r1, =0xE3854C03
	str	r1, [r0, #DMC_PHYZQCONTROL]

	mov	r2, #0x100000
1:	subs	r2, r2, #1
	bne	1b

	ldr	r1, =0xe000008e
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	ldr	r1, =0x71101008
	str	r1, [r0, #DMC_PHYCONTROL0]
	ldr	r1, =0x7110100A
	str	r1, [r0, #DMC_PHYCONTROL0]

	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0x7110100B
	str	r1, [r0, #DMC_PHYCONTROL0]

	ldr	r1, =0x00000000
	str	r1, [r0, #DMC_PHYCONTROL2]

	ldr	r1, =0x0FFF301A
	str	r1, [r0, #DMC_CONCONTROL]
	ldr	r1, =0x00312640
	str	r1, [r0, #DMC_MEMCONTROL]

	ldr	r1, =0x40e01323
	str	r1, [r0, #DMC_MEMCONFIG0]
	ldr	r1, =0x60e01323
	str	r1, [r0, #DMC_MEMCONFIG1]

#ifdef CONFIG_IV_SIZE
	ldr	r1, =(0x80000000 | CONFIG_IV_SIZE)
#else
	ldr	r1, =0x08
#endif
	str	r1, [r0, #DMC_IVCONTROL]

	ldr	r1, =0xff000000
	str	r1, [r0, #DMC_PRECHCONFIG]

	ldr	r1, =0x000000BB
	str	r1, [r0, #DMC_TIMINGAREF] @TimingAref

#ifdef MCLK_330
	ldr	r1, =0x3545548d
	str	r1, [r0, #DMC_TIMINGROW]
	ldr	r1, =0x45430506
	str	r1, [r0, #DMC_TIMINGDATA]
	ldr	r1, =0x46000A3c
	str	r1, [r0, #DMC_TIMINGPOWER]
#endif
#ifdef MCLK_400
	ldr	r1, =0x4046654f
	str	r1, [r0, #DMC_TIMINGROW] @TimingRow
	ldr	r1, =0x46400506
	str	r1, [r0, #DMC_TIMINGDATA] @TimingData
	ldr	r1, =0x52000a3c
	str	r1, [r0, #DMC_TIMINGPOWER] @TimingPower
#endif

	/* chip 0 */
	ldr	r1, =0x07000000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
2:	subs	r2, r2, #1
	bne	2b

	ldr	r1, =0x00020000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00030000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00010002
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00000328
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
3:	subs	r2, r2, #1
	bne	3b

	ldr	r1, =0x0a000000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
4:	subs	r2, r2, #1
	bne	4b

#if 1
	/* chip 1 */
	ldr	r1, =0x07100000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
5:	subs	r2, r2, #1
	bne	5b

	ldr	r1, =0x00120000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00130000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00110002
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00100328
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
6:	subs	r2, r2, #1
	bne	6b

	ldr	r1, =0x0a100000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
7:	subs	r2, r2, #1
	bne	7b
#endif

	ldr	r1, =0xe000008e
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	mov	r2, #0x100000
8:	subs	r2, r2, #1
	bne	8b


/*****************************************************************/
/*DREX1***********************************************************/
/*****************************************************************/

	ldr	r0, =APB_DMC_1_BASE

	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	ldr	r1, =0xE3854C03
	str	r1, [r0, #DMC_PHYZQCONTROL]

	mov	r2, #0x100000
1:	subs	r2, r2, #1
	bne	1b

	ldr	r1, =0xe000008e
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	ldr	r1, =0x71101008
	str	r1, [r0, #DMC_PHYCONTROL0]
	ldr	r1, =0x7110100A
	str	r1, [r0, #DMC_PHYCONTROL0]

	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0x7110100B
	str	r1, [r0, #DMC_PHYCONTROL0]

	ldr	r1, =0x00000000
	str	r1, [r0, #DMC_PHYCONTROL2]

	ldr	r1, =0x0FFF301A
	str	r1, [r0, #DMC_CONCONTROL]
	ldr	r1, =0x00312640
	str	r1, [r0, #DMC_MEMCONTROL]

	ldr	r1, =0x40e01323			@Interleaved?
	str	r1, [r0, #DMC_MEMCONFIG0]
	ldr	r1, =0x60e01323
	str	r1, [r0, #DMC_MEMCONFIG1]

#ifdef CONFIG_IV_SIZE
	ldr	r1, =(0x80000000 | CONFIG_IV_SIZE)
#else
	ldr	r1, =0x08
#endif
	str	r1, [r0, #DMC_IVCONTROL]

	ldr	r1, =0xff000000
	str	r1, [r0, #DMC_PRECHCONFIG]

	ldr	r1, =0x000000BB
	str	r1, [r0, #DMC_TIMINGAREF] @TimingAref

#ifdef MCLK_330
	ldr	r1, =0x3545548d
	str	r1, [r0, #DMC_TIMINGROW]
	ldr	r1, =0x45430506
	str	r1, [r0, #DMC_TIMINGDATA]
	ldr	r1, =0x46000A3c
	str	r1, [r0, #DMC_TIMINGPOWER]
#endif
#ifdef MCLK_400
	ldr	r1, =0x4046654f
	str	r1, [r0, #DMC_TIMINGROW] @TimingRow
	ldr	r1, =0x46400506
	str	r1, [r0, #DMC_TIMINGDATA] @TimingData
	ldr	r1, =0x52000a3c
	str	r1, [r0, #DMC_TIMINGPOWER] @TimingPower
#endif

	/* chip 0 */
	ldr	r1, =0x07000000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
2:	subs	r2, r2, #1
	bne	2b

	ldr	r1, =0x00020000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00030000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00010002
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00000328
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
3:	subs	r2, r2, #1
	bne	3b

	ldr	r1, =0x0a000000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
4:	subs	r2, r2, #1
	bne	4b

#if 1
	/* chip 1 */
	ldr	r1, =0x07100000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
5:	subs	r2, r2, #1
	bne	5b

	ldr	r1, =0x00120000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00130000
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00110002
	str	r1, [r0, #DMC_DIRECTCMD]
	ldr	r1, =0x00100328
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
6:	subs	r2, r2, #1
	bne	6b

	ldr	r1, =0x0a100000
	str	r1, [r0, #DMC_DIRECTCMD]

	mov	r2, #0x100000
7:	subs	r2, r2, #1
	bne	7b
#endif

	ldr	r1, =0xe000008e
	str	r1, [r0, #DMC_PHYCONTROL1]
	ldr	r1, =0xe0000086
	str	r1, [r0, #DMC_PHYCONTROL1]

	mov	r2, #0x100000
8:	subs	r2, r2, #1
	bne	8b


/*****************************************************************/
/*Finalize********************************************************/
/*****************************************************************/

	ldr	r0, =APB_DMC_0_BASE
	ldr	r1, =0x0FFF303A
	str	r1, [r0, #DMC_CONCONTROL]

	ldr	r0, =APB_DMC_1_BASE
	ldr	r1, =0x0FFF303A
	str	r1, [r0, #DMC_CONCONTROL]
	

	/* led (GPM4_0~3) on */
		ldr r0, =0x110002E0
		ldr r1, =0x00001111
		str r1, [r0]
		ldr r1, =0x0D
		str r1, [r0, #0x04]


	mov	pc, lr



	
		
	
	/*
	 * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
	 * void uart_asm_init(void)
	 */
		.globl uart_asm_init
	uart_asm_init:
	
		/* set GPIO to enable UART */
		@ GPIO setting for UART for UART0/1/2/3
		
		ldr r0, =0x11400000
		ldr r1, =0x22222222
		str r1, [r0]
		ldr r0, =0x11400020
		ldr r1, =0x222222
		str r1, [r0]
	
		ldr r0, =S5PV310_CLOCK_BASE
		ldr r1, =CLK_SRC_PERIL0_VAL
		ldr r2, =CLK_SRC_PERIL0_OFFSET
		str r1, [r0, r2]
		ldr r1, =CLK_DIV_PERIL0_VAL
		ldr r2, =CLK_DIV_PERIL0_OFFSET
		str r1, [r0, r2]
	
		ldr r0, =S5PV310_UART_CONSOLE_BASE
		ldr r1, =0x111
		str r1, [r0, #UFCON_OFFSET]
	
		mov r1, #0x3
		str r1, [r0, #ULCON_OFFSET]
	
		ldr r1, =0x3c5
		str r1, [r0, #UCON_OFFSET]
	
		ldr r1, =UART_UBRDIV_VAL
		str r1, [r0, #UBRDIV_OFFSET]
	
		ldr r1, =UART_UDIVSLOT_VAL
		str r1, [r0, #UDIVSLOT_OFFSET]
	
		ldr r1, =0x4f4f4f4f
		str r1, [r0, #UTXH_OFFSET]		@'O'
	
		mov pc, lr
	
	
			.globl uart_asm_putc
	uart_asm_putc:
		push	{r9}
	
		ldr r9, =S5PV310_UART_CONSOLE_BASE
		str r0, [r9, #UTXH_OFFSET]
		ldr r9, =0x20000				@delay
	
	
	
	.Luartputc:
		sub r9, r9, #1
		cmp r9, #0
		bne .Luartputc
	
		pop {r9}
		mov pc, lr
	
		.globl uart_asm_putx
	uart_asm_putx:
		stmfd sp!, {r3, r4, r5, lr}
	
		mov r5, r0
		mov r4, #28
	
	.Luartputx:
		mov r0, r5, asr r4
		and r0, r0, #15
		cmp r0, #9
		addle	r0, r0, #48
		addgt	r0, r0, #55
		bl	uart_asm_putc
		sub r4, r4, #4
		cmn r4, #4
		bne .Luartputx
	
		ldmfd sp!, {r3, r4, r5, pc}
	
