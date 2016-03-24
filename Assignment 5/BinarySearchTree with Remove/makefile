CC=g++
CFLAGS=-std=c++11

all: main

main:
	$(CC) $(CFLAGS) main.cpp -o main.o
run: main
	./main.o

benchmark: main
	time ./main.o

clean:
	rm *.o
