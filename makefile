BIN_DIR = bin
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/Output.o $(BIN_DIR)/Vector2.o $(BIN_DIR)/Vector3.o $(BIN_DIR)/Matrix2.o $(BIN_DIR)/Matrix3.o
SOURCE = src/main.cpp src/Output.cpp headers/Vector/Vector2.cpp headers/Vector/Vector3.cpp headers/Matrix/Matrix2.cpp headers/Matrix/Matrix3.cpp
HEADER = headers/Output.h headers/Vector/Vector2.h headers/Vector/Vector3.h headers/Matrix/Matrix2.h headers/Matrix/Matrix3.h
OUT = $(BIN_DIR)/main.exe
FLAGS = -g -c -Wall
LFLAGS = 
CC = g++

all: $(OUT)

# Rule for building the executable
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

# Pattern rule for building object files
$(BIN_DIR)/%.o: src/%.cpp
	$(CC) $(FLAGS) $< -o $@

$(BIN_DIR)/%.o: headers/Vector/%.cpp
	$(CC) $(FLAGS) $< -o $@

$(BIN_DIR)/%.o: headers/Matrix/%.cpp
	$(CC) $(FLAGS) $< -o $@

# Ensure the bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Add the bin directory as a prerequisite for object files
$(OBJS): | $(BIN_DIR)

# Clean rule
clean:
	rm -f $(OBJS) $(OUT)