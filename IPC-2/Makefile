CXX      = g++
CXXFLAGS = -Wall -Wextra -O2

TARGET   = primes
OBJ      = primeCalculator.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

primeCalculator.o: primeCalculator.cpp
	$(CXX) $(CXXFLAGS) -c primeCalculator.cpp

clean:
	rm -f $(OBJ) $(TARGET)

