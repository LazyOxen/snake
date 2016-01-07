CC = g++
HEADERS = game.h snake.h grafx_defs.h
CPP_FILES = snake.cpp game.cpp main.cpp
CCFLAGS = --std=c++11 -DUNICODE -D_UNICODE
LINKER_FLAGS = -lgdi32


all: $(HEADERS) $(CPP_FILES)
	$(CC) -o snake $(CPP_FILES) $(CCFLAGS) $(LINKER_FLAGS)

clean:
	del *.exe
