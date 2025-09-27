CXX = g++
CXXFLAGS = -g -Wextra -Wall -Iinc -std=c++17

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/exe

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

run : $(TARGET)
	./$(TARGET)

clean : 
	rm -f $(OBJ_DIR)/*.o $(TARGET)

