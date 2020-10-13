CC=g++
FLAGS=-std=c++17 -Wall -Pedantic -Wextra -Wno-unused-variable

all: test

test: main.o allocator.o
	$(CC) main.o allocator.o -o my_prog

allocator.o: allocator.cpp
	$(CC) $(FLAGS) allocator.cpp -o allocator.o

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -o main.o

clean:
 rm -rf *.o my_prog