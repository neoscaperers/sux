CC 		= pdp11-aout-gcc
OBJCPY	= pdp11-aout-objcopy
LD		= pdp11-aout-ld
CFLAGS	= -nostdlib -ffreestanding -s -msoft-float -I./sys/include
LDFLAGS = --imagic -nostdlib --script=$(TOPSRC)/pdp11/link.ld --strip-all

all: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJS) $(TARGET)
	