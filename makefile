CXX = g++
CXXFLAGS = -std=c++11 -Iincludes

SRC_DIR = src
INCLUDE_DIR = includes
BUILD_DIR = build
EXECUTABLE = main

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lncurses

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)