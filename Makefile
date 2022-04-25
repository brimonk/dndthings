CC=gcc
LINKER=
CFLAGS=-Wall -g3 -march=native
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
DEP=$(OBJ:.o=.d)

.PHONY: all

all: generator dndmaps

%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

-include $(DEP)

dndmaps: src/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LINKER)

generator: src/generator.o
	$(CC) $(CFLAGS) -o $@ $^ $(LINKER)

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f generator dndmaps
