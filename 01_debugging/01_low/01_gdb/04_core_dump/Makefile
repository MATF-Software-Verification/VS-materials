CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

.PHONY: all clean

all: crash

crash: crash.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f crash core core.*
