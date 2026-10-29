CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

.PHONY: all clean

all: service

service: service.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f service
