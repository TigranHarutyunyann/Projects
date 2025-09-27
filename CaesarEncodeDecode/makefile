CXX = g++
CXXFLAGS = -g -Wextra -Wall -Iinc -fPIC -std=c++17

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

TARGET = $(BIN_DIR)/exe
LIBNAME = libcaesar.so

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
LIB_OBJ = $(OBJ_DIR)/Encoder.o $(OBJ_DIR)/Decoder.o $(OBJ_DIR)/Print.o

all : $(LIB_DIR)/$(LIBNAME) $(TARGET)

$(TARGET) : $(SRC_DIR)/main.cpp $(LIB_DIR)/$(LIBNAME)
	$(CXX) -o $@ $< -Llib -lcaesar -Iinc -Wl,-rpath=$(LIB_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIBNAME) : $(LIB_OBJ)
	$(CXX) -shared -o $@ $^


run : $(TARGET)
	./$(TARGET)

clean : 
	rm -f $(OBJ_DIR)/*.o $(TARGET) $(LIB_DIR)/$(LIBNAME)

