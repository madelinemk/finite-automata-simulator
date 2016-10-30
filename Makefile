CXX= g++
CXXFLAGS= -g -Wall -std=gnu++11

all: dfa.exe

dfa.exe: dfa.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.exe *.o
