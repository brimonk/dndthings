LINKER=
CFLAGS=-Wall -g3 -march=native

SRC=src/main.c
OBJ=$(SRC:.c=.o)
DEP=$(OBJ:.o=.d)

GENSRC=generator.c
GENOBJ=$(GENSRC:.c=.o)
GENDEP=$(GENOBJ:.o=.d)

all: generator dndmaps

%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

-include $(DEP)

dndmaps: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LINKER)

generator: generator.c
	$(CC) $(CFLAGS) -o $@ $^ $(LINKER)
	./$@ > src/generated.h

clean:
	rm -f $(OBJ) $(OBJ)
	rm -f src/generated.h
	rm -f generator dndmaps
