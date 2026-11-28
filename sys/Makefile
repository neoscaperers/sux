TARGET	= vmunix
PORT	?= pdp11
TOPSRC	= $(shell pwd)
FILES 	= $(shell cat $(TOPSRC)/$(PORT)/files)
FILES	+= $(shell cat $(TOPSRC)/kern/files)
OBJS	= $(addprefix $(TOPSRC)/, $(addsuffix .o, $(basename $(FILES))))
CFLAGS	= -ansi -nostdlib -ffreestanding -s -I$(TOPSRC) -D_KERN -Wpedantic -Werror -O3

export *

include $(TOPSRC)/$(PORT)/Makefile