CC=g++
FLAGS=-std=c++17 -Wall -Werror -c -ggdb3

all: program

test:
	./program

program: main.o matrix.o
	$(CC) main.o matrix.o -o program

matrix.o: matrix.cpp
	$(CC) $(FLAGS) matrix.cpp -o matrix.o

main.o: main.cpp matrix_header.hpp
	$(CC) $(FLAGS) main.cpp -o main.o

clean:
	rm -rf *.o program