CC=g++
FLAGS=-std=c++14 -Wall -Werror -c -O2 -pthread

all: program

test:
	./program

program: main.o
	$(CC) -o program $^

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -rf *.o program