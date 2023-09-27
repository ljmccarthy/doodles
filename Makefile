CFLAGS ?= -O0 -ggdb -std=c17 -Wall -Wextra -Wpedantic \
-D_FORTIFY_SOURCE=3 -fPIE -pie -Wl,-z,relro,-z,now \
-fstack-protector-strong -fstack-clash-protection -fcf-protection=full \

LDLIBS = -lm

PROGRAMS := $(basename $(wildcard *.c))

.PHONY: all clean

all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS)
