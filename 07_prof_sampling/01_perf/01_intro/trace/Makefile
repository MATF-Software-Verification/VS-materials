mutex_lock.out: mutex_lock.cpp
	g++ -O3 -std=c++11 -Wall -Wextra -pedantic -pthread -g -fno-omit-frame-pointer -o $@ $<

mutex_lock_trace: mutex_lock.out
	sudo perf trace ./$<

