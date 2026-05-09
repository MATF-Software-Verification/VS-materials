CXX=clang++
CXXFLAGS=-Wall -Wextra -O1 -g -fxray-instrument -fxray-instruction-threshold=1

.PHONY: all clean

all: xray_workload

xray_workload: xray_workload.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f xray_workload xray-log.* xray-account.txt xray-stacks.txt
