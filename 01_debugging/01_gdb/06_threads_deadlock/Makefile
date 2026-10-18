CC=gcc
CFLAGS=-Wall -Wextra -O0 -g -pthread

.PHONY: all clean

all: deadlock

deadlock: deadlock.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f deadlock
