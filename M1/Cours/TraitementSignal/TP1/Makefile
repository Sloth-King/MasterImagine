# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

# Directories
SRC_DIR = src
SOUNDS_DIR = $(SRC_DIR)/Sounds
OBJ_DIR = obj

# Source and object files
SRCS = main.cpp $(SRC_DIR)/Wave.cpp
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# Target executable
TARGET = tp1

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule to remove compiled files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
