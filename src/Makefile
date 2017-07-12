CC=gcc-6
OUTPUT_OPTION=-MMD -MP -o $@

CFLAGS += -Wall -Ofast --std=c99 -Wvla -I../include
MODULES := options file
CFLAGS += $(patsubst %,-I%,$(MODULES))

LIBS :=
SRC := main.c
include $(patsubst %,%/module.mk,$(MODULES))
OBJ := $(patsubst %.c,%.o,$(filter %.c,$(SRC)))
DEP := $(patsubst %.c,%.d,$(filter %.c,$(SRC)))

all : prog

prog : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

debug : CFLAGS += -O0 -g
debug : clean prog

valgrind: debug
	valgrind ./prog

-include $(DEP)

.PHONY: clean

clean:
	rm -f $(OBJ) $(DEP) prog
	rm -rf *.dSYM
