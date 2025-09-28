TARGET = read-file
CC = g++

all: $(TARGET)

read-file.o: read-file.cpp
	$(CC) -c read-file.cpp -o read-file.o

$(TARGET): read-file.o
	$(CC) read-file.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
