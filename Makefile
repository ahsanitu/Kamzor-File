CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = kamzor_file
TEST_TARGET = test_kamzor_file

SRC = main.cpp Node.cpp FrequencyAnalyzer.cpp HuffmanTree.cpp HuffmanCompressor.cpp
OBJ = $(SRC:.cpp=.o)

TEST_SRC = test.cpp Node.cpp FrequencyAnalyzer.cpp HuffmanTree.cpp HuffmanCompressor.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Default build for main program
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Build unit test binary
test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^

# Run tests (always depends on test build)
run_test: test
	./$(TEST_TARGET)

# Run main program with args, e.g.
# make run_main ARGS="compress input.txt output.huff"
run_main: $(TARGET)
	./$(TARGET) $(ARGS)

# Clean all binaries and object files
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) MetaData* *.huff
