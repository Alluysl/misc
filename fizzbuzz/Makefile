EXE = fizzbuzz
CC = gcc
CFLAGS += -std=c89 -Wall -Wextra -Wpedantic -Werror -O2

$(EXE): fizzbuzz.c arrayinttostring.c arrayinttostring.h
	$(CC) $(CFLAGS) -o $@ fizzbuzz.c arrayinttostring.c

test: $(EXE)
	./$<

valgrind: $(EXE)
	valgrind ./$<

clean:
	rm $(EXE)
