objs = start.o main.o

ld := arm-linux-gnueabihf-ld
gcc := arm-linux-gnueabihf-gcc
objcopy := arm-linux-gnueabihf-objcopy
objdump := arm-linux-gnueabihf-objdump

led.bin : $(objs)
	$(ld) -Timx6u.lds $^ -o led.elf
	$(objcopy) -O binary -S -g led.elf $@
	$(objdump) -D led.elf > led.dis

%.o : %.S
	$(gcc) -Wall -nostdlib -c -O2 $< -o $@

%.o : %.c
	$(gcc) -Wall -nostdlib -c -O2 $< -o $@

clean:
	rm -f *.o *.elf *.bin *.dis
.PHONY: clean
