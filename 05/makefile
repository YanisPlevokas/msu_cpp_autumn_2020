CC=g++
FLAGS=-std=c++17 -Wall -Werror -c -ggdb3

all: program

test:
	./program

program: main.o
	$(CC) -o program $^

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -rf *.o program