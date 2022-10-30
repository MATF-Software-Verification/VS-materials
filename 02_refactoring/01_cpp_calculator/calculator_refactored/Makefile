CC=g++
CCFLAGS=-Wall -Wextra

OBJECTS = main.o calculator.o

calculator.out: $(OBJECTS)
	$(CXX) $(CCFLAGS) -o $@ $^

$(OBJECTS): calculator.hpp