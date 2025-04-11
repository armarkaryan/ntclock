CC=g++
CFLAGS=-c -Wall -Isrc
LDFLAGS=-lncurses -lpthread
SOURCES=src/ntclock.cpp
OBJECTS=$(SOURCES:src/%.cpp=obj/%.o)
EXECUTABLE=build/ntclock

all: $(SOURCES) | build obj $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) $< -o $@

# Создание директорий, если их нет
build:
	mkdir -p build

obj:
	mkdir -p obj

clean:
	rm -rf obj build

.PHONY: all clean