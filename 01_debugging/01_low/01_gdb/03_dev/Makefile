CC=gcc
CFLAGS=-Wall -Wextra -O2 -g
TARGETS=sample sample-fixed

.PHONY: all clean

all: $(TARGETS)

sample: main.c
	$(CC) $(CFLAGS) $^ -o $@

sample-fixed: main-fixed.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGETS)
