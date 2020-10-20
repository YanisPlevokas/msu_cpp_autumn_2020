CC=g++
FLAGS=-std=c++17 -Wall -Werror -c -ggdb3

all: program

test:
	./program

program: main.o parser.o
	$(CC) main.o parser.o -o program

parser.o: parser.cpp
	$(CC) $(FLAGS) parser.cpp -o parser.o

main.o: main.cpp parser_header.hpp
	$(CC) $(FLAGS) main.cpp -o main.o

clean:
	rm -rf *.o my_prog