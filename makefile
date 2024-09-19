CXXFLAGS2 =-Wall -Wextra -Werror -pedantic -pedantic-errors -O3 -g -std=c++11 

all: main

main: main.cpp Derivee_Generic_station_parser.cpp Grade.o 
	g++ -o Metro main.cpp Derivee_Generic_station_parser.cpp Grade.o $(CXXFLAGS)
