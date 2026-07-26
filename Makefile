# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Define directories
SRC_DIR = src
OUT_DIR = run_code
GV := libraries/graphviz-build

# Target executable name
TARGET = $(OUT_DIR)/graph_search

# Build rule
all:
	$(CXX) $(CXXFLAGS) -I$(GV)/include/graphviz \
	$(SRC_DIR)/main.cpp $(SRC_DIR)/adjacency.cpp \
	$(SRC_DIR)/visualization/visualization.cpp $(SRC_DIR)/utils.cpp \
	-L$(GV)/lib -lgvc -lcgraph -lcdt \
	-Wl,-rpath,@loader_path/../$(GV)/lib \
	-o $(TARGET)

clean:
	rm -f $(TARGET)