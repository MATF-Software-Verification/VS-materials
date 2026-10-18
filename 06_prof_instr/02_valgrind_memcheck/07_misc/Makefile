CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -O0 -g
CXXFLAGS=-Wall -Wextra -O0 -g
TARGETS=01_invalid_read.out 01_invalid_read_fixed.out 02_invalid_write.out 02_invalid_write_fixed.out 03_watch_your_pointers.out 03_watch_your_pointers_fixed.out 04_test01.out 04_test01_fixed.out 05_test02.out 05_test02_fixed.out

.PHONY: all clean

all: $(TARGETS)

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
