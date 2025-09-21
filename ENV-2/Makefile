# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
INCLUDES = -Iinclude

# Source and object files
SRC = src/Complex.cpp src/Sort.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)

# Final target
complex_sort: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJ)

# Rule for building .o from .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
.PHONY: clean
clean:
	rm -f src/*.o complex_sort

