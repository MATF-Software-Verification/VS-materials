CC = g++
CFLAGS = -O2 -fno-inline -g -Wall

students.out: students.o 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o callgrind.out.* cachegrind.out*
	$(RM) students.out
