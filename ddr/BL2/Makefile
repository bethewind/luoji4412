
objs := start.o system_clock.o mem_init_tiny4412.o mmc_relocate.o

make_bl2.bin : $(objs)
	arm-linux-ld -Tbl2.lds -o make_bl2.elf $^
	arm-linux-objcopy -O binary -S make_bl2.elf $@
	arm-linux-objdump -D -m arm  make_bl2.elf > make_bl2.dis

%.o:%.c
	arm-linux-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
	

