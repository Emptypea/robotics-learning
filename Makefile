CC		= gcc
CFLAGS	= -Wall -Wextra -fsanitize=address

.PHONY: all clean
all: bin/list_pp

bin/list_pp: c-basics/list_pp_main.c c-basics/list_pp.c c-basics/list_pp.h
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $(filter %.c, $^)

bin/m1: c-basics/m1.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/revbits: c-basics/revbits.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bin/list_pp
	rm -f bin/m1
	rm -f bin/revbits
