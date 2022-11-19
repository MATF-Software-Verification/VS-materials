CC = gcc
CFLAGS = -O2 -fno-inline -g
CP = g++

default: loops matrix algo 

loops: loops-fast loops-slow
matrix: matrix_slowest matrix_slower matrix_slow matrix_meduim matrix_meduimish
algo: pattern_search prime


loops-fast: loops-fast.o
	$(CC) $(CFLAGS) -o $@ $^

loops-slow: loops-slow.o
	$(CC) $(CFLAGS) -o $@ $^


matrix_slowest: matrix_slowest.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_slower: matrix_slower.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_slow: matrix_slow.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_meduim: matrix_meduim.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_meduimish: matrix_meduimish.o 
	$(CP) $(CFLAGS) -o $@ $^

pattern_search: pattern_search.o
	$(CC) $(CFLAGS) -o $@ $^

prime: prime.o	
	$(CP) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CP) $(CFLAGS) -c $< -o $@



clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) loops-fast loops-slow
	$(RM) matrix_slowest matrix_slower matrix_slow matrix_meduim matrix_meduimish 
	$(RM) pattern_search prime
