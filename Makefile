CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -march=native

SRC_DIR = src
BIN_DIR = bin

all: $(BIN_DIR)/case_serial $(BIN_DIR)/case_simd $(BIN_DIR)/generator

$(BIN_DIR)/case_serial: $(SRC_DIR)/case_converter_serial.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/case_simd: $(SRC_DIR)/case_converter_SIMD.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -mavx2 $< -o $@

$(BIN_DIR)/generator: $(SRC_DIR)/generator.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)
