CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Define the name of the final executable
TARGET = game

# Define the C++ source file(s)
SRCS = main.cpp player.cpp bullet.cpp enemy.cpp splitter.cpp powerup.cpp

# Define the object files that will be created from the source files
OBJS = $(SRCS:.cpp=.o)

# The 'all' target is the default one
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .cpp source file into a .o object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# A target to compile and run the program
run: all
	./$(TARGET)

# A target to clean up the directory
clean:
	rm -f $(TARGET) $(OBJS)

# Declare targets that are not actual files
.PHONY: all run clean