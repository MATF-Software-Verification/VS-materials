CC = gcc
CFLAGS = -O2 -fno-inline -g
CP = g++

default: loops

loops: loops-fast.out loops-slow.out


loops-fast.out: loops-fast.o
	$(CC) $(CFLAGS) -o $@ $^

loops-slow.out: loops-slow.o
	$(CC) $(CFLAGS) -o $@ $^

	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CP) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) loops-fast loops-slow
