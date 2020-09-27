CC=g++
CFLAFS=-c -Wall
LDFLAGS=
SOURSES=test.cpp Matrix.cpp
OBJECTS=$(SOURSES:.cpp=.o)
EXECUTABLE=tests

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	./$(EXECUTABLE)

test.o: test.cpp
	$(CC) $(OPTIMIZATION) $(CFLAFS) $< -o $@

.cpp.o:
	$(CC) $(OPTIMIZATION) $(CFLAFS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
