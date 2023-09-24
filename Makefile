PROGRAMS := $(basename $(wildcard *.c))
.PHONY: all clean
all : $(PROGRAMS)
clean :
	rm -f $(PROGRAMS)
