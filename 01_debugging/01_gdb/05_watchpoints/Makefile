CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

.PHONY: all clean

all: watchpoint_demo

watchpoint_demo: watchpoint_demo.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f watchpoint_demo
