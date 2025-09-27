CXX = g++
CXXFLAGS = -g -Wextra -Wall -Iinc -fPIC -std=c++17

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

TARGET = $(BIN_DIR)/exe
LIBNAME_DYNAMIC = libcaesar.so
LIBNAME_STATIC = libunittest.a

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
LIB_OBJ = $(OBJ_DIR)/Encoder.o $(OBJ_DIR)/Decoder.o $(OBJ_DIR)/Print.o
LIB_STC_OBJ = $(OBJ_DIR)/unit_test.o

all : $(LIB_DIR)/$(LIBNAME_DYNAMIC) $(LIB_DIR)/$(LIBNAME_STATIC) $(TARGET)

$(TARGET) : $(SRC_DIR)/main.cpp $(LIB_DIR)/$(LIBNAME_DYNAMIC) $(LIB_DIR)/$(LIBNAME_STATIC) 
	$(CXX) -o $@ $< -Llib -lcaesar -lunittest -Iinc -Wl,-rpath=$(LIB_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIBNAME_DYNAMIC) : $(LIB_OBJ)
	$(CXX) -shared -o $@ $^

$(LIB_DIR)/$(LIBNAME_STATIC) : $(LIB_STC_OBJ)
	ar rcs $@ $^


run : $(TARGET)
	./$(TARGET)

clean : 
	rm -f $(OBJ_DIR)/*.o $(TARGET) $(LIB_DIR)/$(LIBNAME_DYNAMIC) $(LIB_DIR)/$(LIBNAME_STATIC) 

