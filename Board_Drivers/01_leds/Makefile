led.bin : led.S
	arm-linux-gnueabihf-gcc -g -c led.S -o led.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 led.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
	arm-linux-gnueabihf-objdump -D led.elf > led.dis

clean:
	rm -f *.o *.elf *.bin *.dis
.PHONY: clean
