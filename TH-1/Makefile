CXX = g++
CXXFLAGS = -O2 -Wall -pthread
TARGET = array-summary
SRC = array_summary.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

