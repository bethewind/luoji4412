
objs := start.o main.o

main.bin : $(objs)
	arm-linux-ld -Tmain.lds -o main.elf $^
	arm-linux-objcopy -O binary -S main.elf $@
	arm-linux-objdump -D -m arm  main.elf > main.dis

%.o:%.c
	arm-linux-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
	

