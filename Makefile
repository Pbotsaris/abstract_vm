SRC=src
OBJ=obj
TEST_OBJ=tests/obj
BIN=bin

CFLAGS += -Wall -Wextra -g3 -Iinclude -fsanitize=address 
CPP_FLAGS = -Wpedantic -std=c++17 -Wcast-qual -Wnon-virtual-dtor -Woverloaded-virtual -Wold-style-cast

CC=g++
TARGET=$(BIN)/my_abstract_vm
RM=rm -rf

$(shell mkdir -p obj bin)

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

all: $(TARGET)

run: ${TARGET}
	./${TARGET}

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(CPP_FLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(CPP_FLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)/*.o 

test_clean:
	$(RM) $(TARGET) $(TEST)/test $(TEST_OBJ)/*.o 

.PHONY:
	all run clean 
