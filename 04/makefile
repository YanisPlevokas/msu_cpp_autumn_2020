CC=g++
FLAGS=-std=c++17 -Wall -Werror -c -ggdb3

all: program

test:
	./program

program: main.o bigint.o
	$(CC) main.o bigint.o -o program

bigint.o: bigint.cpp
	$(CC) $(FLAGS) bigint.cpp -o bigint.o

main.o: main.cpp bigint.hpp
	$(CC) $(FLAGS) main.cpp -o main.o

clean:
	rm -rf *.o program