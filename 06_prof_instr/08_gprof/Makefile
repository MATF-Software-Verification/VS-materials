CC=gcc
CFLAGS=-Wall -Wextra -O0 -g -pg
LDFLAGS=-pg

.PHONY: all clean

all: sort_workload

sort_workload: sort_workload.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f sort_workload gmon.out gmon.sum gprof.txt
