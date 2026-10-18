CC=clang
CFLAGS=-Wall -Wextra -O0 -g -fno-omit-frame-pointer
TSANFLAGS=-Wall -Wextra -O1 -g -fno-omit-frame-pointer -fsanitize=thread -pthread
TARGETS=asan_bad.out asan_fixed.out ubsan_bad.out ubsan_fixed.out lsan_bad.out lsan_fixed.out tsan_bad.out tsan_fixed.out

.PHONY: all clean

all: $(TARGETS)

asan_bad.out: 01_asan_heap_overflow.c
	$(CC) $(CFLAGS) -fsanitize=address $< -o $@

asan_fixed.out: 01_asan_heap_overflow_fixed.c
	$(CC) $(CFLAGS) -fsanitize=address $< -o $@

ubsan_bad.out: 02_ubsan_signed_overflow.c
	$(CC) $(CFLAGS) -fsanitize=undefined -fno-sanitize-recover=undefined $< -o $@

ubsan_fixed.out: 02_ubsan_signed_overflow_fixed.c
	$(CC) $(CFLAGS) -fsanitize=undefined -fno-sanitize-recover=undefined $< -o $@

lsan_bad.out: 03_lsan_leak.c
	$(CC) $(CFLAGS) -fsanitize=leak $< -o $@

lsan_fixed.out: 03_lsan_leak_fixed.c
	$(CC) $(CFLAGS) -fsanitize=leak $< -o $@

tsan_bad.out: 04_tsan_data_race.c
	$(CC) $(TSANFLAGS) $< -o $@

tsan_fixed.out: 04_tsan_data_race_fixed.c
	$(CC) $(TSANFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
