CC=gcc
CFLAGS=-Wall -Wextra -O0 -g
TARGETS=dhat_churn_bad.out dhat_churn_fixed.out

.PHONY: all clean

all: $(TARGETS)

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS) dhat.out.*
