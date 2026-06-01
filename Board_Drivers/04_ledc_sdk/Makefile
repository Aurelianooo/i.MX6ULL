CROSS_COMPILE 	?= arm-linux-gnueabihf-
TARGET 			?= ledc

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

OBJS := start.o main.o

$(TARGET).bin: $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

%.o: %.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

%.o: %.S
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).dis
