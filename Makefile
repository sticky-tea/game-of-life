CC=g++
LIBS=-lSDL2
SRC=life.cpp gamelife.cpp
EXEC=gamelife


all:
	$(CC) $(LIBS) $(SRC) -o $(EXEC)
