SOURCES = test.cpp
OBJECTS = test.o

test: test.cpp
	g++ -o test test.cpp

CXXFLAGS = -std=c++11 -D_GNU_SOURCE -Wall
