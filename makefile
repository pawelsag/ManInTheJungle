OBJS = main.cpp
# folders paths 
INC = include
SRC = src
STAGE = stage
CC = g++

INCLUDE_PATHS := -I"C:\mingw32\i686-w64-mingw32\include\SDL2"
INCLUDE_PATHS += -I"C:\SDLPRojects\SDL GAME\include"

LIB_PATHS = -L"C:\mingw32\i686-w64-mingw32\lib"

CXX_FLAGS = -Wextra -ggdb -std=c++14

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

EXEC = First_game.exe

SOURCES := $(wildcard $(SRC)/*.cpp)

OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(STAGE)/%.o)

# main target 
all: $(OBJECTS)
	$(CC) $(OBJECTS) $(INCLUDE_PATHS) $(LINKER_FLAGS) -o $(EXEC)
	
$(STAGE)/%.o : $(SRC)/%.cpp
	$(CC) -c $(INCLUDE_PATHS) $(CXX_FLAGS) $< -o $@

clean:
	@del /Q $(EXEC) $(STAGE)\*