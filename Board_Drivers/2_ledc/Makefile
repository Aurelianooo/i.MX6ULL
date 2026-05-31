objs = start.o main.o

led.bin : $(objs)
	arm-linux-gnueabihf-ld -Timx6u.lds $^ -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf $@
	arm-linux-gnueabihf-objdump -D led.elf > led.dis

%.o : %.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 $< -o $@

%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 $< -o $@

clean:
	rm -f *.o *.elf *.bin *.dis
.PHONY: clean
