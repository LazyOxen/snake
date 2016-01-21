CC = g++
HEADERS = game.h snake.h grafx_defs.h greeting_state.h playing_state.h you_dead_state.h state.h
CPP_FILES = greeting_state.cpp you_dead_state.cpp playing_state.cpp snake.cpp game.cpp main.cpp 
CCFLAGS = --std=c++11 -DUNICODE -D_UNICODE
LINKER_FLAGS = -lgdi32


all: $(HEADERS) $(CPP_FILES)
	$(CC) -o snake $(CPP_FILES) $(CCFLAGS) $(LINKER_FLAGS)

clean:
	del *.exe
