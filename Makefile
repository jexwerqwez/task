CC = g++
CPPFLAGS = -std=c++20 -Iinclude -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -pthread
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TEST_DIR = tests

SOURCES = $(filter-out $(SRC_DIR)/main.cc, $(wildcard $(SRC_DIR)/*.cc))
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))
HEADERS = $(wildcard $(INC_DIR)/*.h)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cc, $(OBJ_DIR)/%.o, $(TEST_SOURCES))
EXECUTABLE = main
TEST_EXECUTABLE = run_tests

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(OBJ_DIR)/main.o
	$(CC) $(OBJECTS) $(OBJ_DIR)/main.o -o $@

$(TEST_EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(OBJECTS) $(TEST_OBJECTS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cc $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

test: $(EXECUTABLE) $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

style:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Check for code style and formatting     )
	$(info ----------------------------------------)
	clang-format -style=Google -i src/*.cc include/*.h

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXECUTABLE)
	rm -f $(TEST_EXECUTABLE)
	rm -rf $(INC_DIR)/*.gch
	rm -rf tests/output.txt
