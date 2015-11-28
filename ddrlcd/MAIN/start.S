.global _start

_start:
	ldr sp, =0x73000000
	ldr pc, =main			

halt:
	b halt
