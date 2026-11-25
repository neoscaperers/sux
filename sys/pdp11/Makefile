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

bootdisk: all
	$(CC) $(CFLAGS) -c $(TOPSRC)/pdp11/bootblk/bootrk.S -o $(TOPSRC)/bootblk.tmp
	$(OBJCPY) -O binary $(TOPSRC)/bootblk.tmp $(TOPSRC)/bootblk.tmp
	mkdir $(TOPSRC)/staging
	cp $(TARGET) $(TOPSRC)/staging
#	makefs -t ffs -B le -o version=1,bsize=8192,fsize=1024 -s 2m $(TOPSRC)/bootdisk.img $(TOPSRC)/staging
	dd if=/dev/zero of=$(TOPSRC)/bootdisk.img bs=512 count=4596
#	mkfs.ext2 -b 8192 -d $(TOPSRC)/staging 
	dd if=$(TOPSRC)/bootblk.tmp of=$(TOPSRC)/bootdisk.img bs=512 count=2 conv=notrunc
	rm -r $(TOPSRC)/staging
	rm $(TOPSRC)/bootblk.tmp
	$(CC) $(CFLAGS) -Ttext=0x200 -c $(TOPSRC)/pdp11/bootblk/bstrap.S -o $(TOPSRC)/bootstrap.bin
	$(OBJCPY) -O binary $(TOPSRC)/bootstrap.bin $(TOPSRC)/bootstrap.bin

clean:
	rm $(OBJS)
	