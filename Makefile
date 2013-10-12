CC=clang
OBJ=obj
BIN=dist/png-reader
SRC=src
FLAGS=-std=c99 -Wall

all: $(BIN)

$(BIN): $(OBJ)/main.o $(OBJ)/byte.o $(OBJ)/png-reader.o
	clang $(OBJ)/main.o $(OBJ)/byte.o $(OBJ)/png-reader.o -o $(BIN)

$(OBJ)/main.o: $(SRC)/main.c
	clang $(FLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/byte.o: $(SRC)/byte.c
	clang $(FLAGS) -c $(SRC)/byte.c -o $(OBJ)/byte.o

$(OBJ)/png-reader.o: $(SRC)/png-reader.o
	clang $(FLAGS) -c $(SRC)/png-reader.c -o $(OBJ)/png-reader.o

.PHONY: clean

clean:
	rm -f $(OBJ)/* $(BIN)
