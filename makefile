OBJS = main.cpp
# folders paths 
INC = include
SRC = src
STAGE = stage
CC = g++



LIB_PATHS := -L"C:\mingw32\i686-w64-mingw32\lib"

CXX_FLAGS := -Wextra -ggdb -std=c++14 -O3

INCLUDE_PATHS := -I"./include"
LINKER_FLAGS := -lSDL2main -lSDL2 -lSDL2_image

ifeq ($(OS),Windows_NT)
	LINKER_FLAGS += -lmingw32
	INCLUDE_PATHS := -I"C:\mingw32\i686-w64-mingw32\include\SDL2"
endif
EXEC = First_game

SOURCES := $(wildcard $(SRC)/*.cpp)

OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(STAGE)/%.o)

# main target 
all: $(OBJECTS)
	$(CC) $(OBJECTS) $(INCLUDE_PATHS) $(LINKER_FLAGS) -o $(EXEC)

$(STAGE)/%.o : $(SRC)/%.cpp
	$(CC) -c $(INCLUDE_PATHS) $(CXX_FLAGS) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	@del /Q $(EXEC) $(STAGE)\*
else
	@rm -rf ./$(EXEC) ./$(STAGE)\*
endif
