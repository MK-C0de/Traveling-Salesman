CC= g++
CXXFLAGS= -std=c++11 -g -Wall -c

main: main.o tourManager.o permutation.o
	$(CC) $^ -o p3

main.o: main.cpp tourManager.hpp
	$(CC) $(CXXFLAGS) main.cpp

tourManager.o: tourManager.cpp permutation.hpp
	$(CC) $(CXXFLAGS) tourManager.cpp

permutation.o: permutation.cpp
	$(CC) $(CXXFLAGS) permutation.cpp

clean:
	rm *.o
