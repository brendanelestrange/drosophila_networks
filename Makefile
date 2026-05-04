# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Define directories
SRC_DIR = src
OUT_DIR = run_code

# Target executable name
TARGET = $(OUT_DIR)/graph_test

# Build rule
all:
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp $(SRC_DIR)/adjacency.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)