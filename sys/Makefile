TARGET	= vmunix
PORT	?= pdp11
TOPSRC	= $(shell pwd)
FILES 	= $(shell cat $(TOPSRC)/$(PORT)/files)
OBJS	= $(addprefix $(TOPSRC)/, $(addsuffix .o, $(basename $(FILES))))

export *

include $(TOPSRC)/$(PORT)/Makefile