CC=g++

all: test

test: test.o Matrix.o
	$(CC) -o test test.o Matrix.o
	./test

Matrix.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp

test.o: test.cpp Matrix.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
