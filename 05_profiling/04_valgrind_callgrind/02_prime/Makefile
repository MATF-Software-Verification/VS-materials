CC = gcc
CFLAGS = -O2 -fno-inline -g
CP = g++

default: algo 

algo: prime.out

prime.out: prime.o	
	$(CP) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CP) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) prime
