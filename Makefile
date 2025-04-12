CC := g++
CFLAGS := -c -Wall -Isrc
LDFLAGS := -lncurses -lpthread
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := obj

# Автоматически находим все .cpp файлы в src/
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
#SOURCES := $(SRC_DIR)/ntclock.cpp $(SRC_DIR)/ntdisplay.cpp
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BUILD_DIR)/ntclock

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Создание необходимых директорий
$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)