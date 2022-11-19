CC = gcc
CFLAGS = -O2 -fno-inline -g
CP = g++

default: algo 

algo: pattern_search.out

pattern_search.out: pattern_search.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CP) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) pattern_search
