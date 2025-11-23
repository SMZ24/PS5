# Makefile for Student Grade Monitoring System
# CSC 307 Data Structures and Algorithm Analysis, Fall 2025
# Team PS5

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Target executable name
TARGET = GradeSystem

# Source files
SOURCES = main.cpp AVLNode.cpp AVLTree.cpp

# Object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned build artifacts"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild: clean then build
rebuild: clean all

.PHONY: all clean run rebuild

