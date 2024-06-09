# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I files/headers -Wall -g

# Source directory
SRC_DIR = files/sources

# Header directory
INC_DIR = files/headers

# Find all .cc files in the source directory
SRC = $(wildcard $(SRC_DIR)/*.cc)

# Output executable
TARGET = main

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up build artifacts
clean:
	rm -f $(TARGET) *.o
