CC=g++
FLAGS=-std=c++17 -Wall -Werror -c -ggdb3

all: program

test:
	./program

program: main.o allocator.o
	$(CC) main.o allocator.o -o program

allocator.o: allocator.cpp
	$(CC) $(FLAGS) allocator.cpp -o allocator.o

main.o: main.cpp allocator_header.hpp
	$(CC) $(FLAGS) main.cpp -o main.o

clean:
	rm -rf *.o my_prog
