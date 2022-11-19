CC = gcc
CFLAGS = -O2 -fno-inline -g
CP = g++

default: matrix 

matrix: matrix_slowest.out matrix_slower.out matrix_slow.out matrix_meduim.out matrix_meduimish.out

matrix_slowest.out: matrix_slowest.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_slower.out: matrix_slower.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_slow.out: matrix_slow.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_meduim.out: matrix_meduim.o 
	$(CP) $(CFLAGS) -o $@ $^

matrix_meduimish.out: matrix_meduimish.o 
	$(CP) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CP) $(CFLAGS) -c $< -o $@


clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) matrix_slowest matrix_slower matrix_slow matrix_meduim matrix_meduimish 
