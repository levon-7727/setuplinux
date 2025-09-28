TARGET = simple-copy
CC = g++

all: $(TARGET)

$(TARGET): simple-copy.o
	$(CC)  simple-copy.o -o $(TARGET)

simple-copy.o: simple-copy.cpp
	$(CC)  -c simple-copy.cpp -o simple-copy.o

clean:
	rm -f *.o $(TARGET)
