led.bin : led.S
	arm-linux-gcc -c -o led.o led.S
	arm-linux-ld -Tled.lds -N led.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D -m arm led.elf > led.dis
clean:
	rm -f *.dis *.bin *.elf *.o
