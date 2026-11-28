CC 		= pdp11-aout-gcc
OBJCPY	= pdp11-aout-objcopy
LD		= pdp11-aout-ld
LDFLAGS = --imagic -nostdlib --script=$(TOPSRC)/pdp11/link.ld --strip-all
CFLAGS	+= -m45 -msoft-float -lgcc

all: linkmach $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.S
	$(CC) $(CFLAGS) -D_ASM -c $^ -o $@

linkmach:
	ln -sf $(TOPSRC)/pdp11/machdef.h $(TOPSRC)/sys/machdef.h

clean:
	unlink $(TOPSRC)/sys/machdef.h
	rm $(OBJS) $(TARGET)

simh: all
	python3 $(TOPSRC)/aout2simh.py