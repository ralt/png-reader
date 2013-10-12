CC=clang
OBJ=obj
BIN=dist/png-reader
SRC=src

all: $(BIN)

$(BIN): $(OBJ)/main.o $(OBJ)/png-reader.o
	clang $(OBJ)/main.o $(OBJ)/png-reader.o -o $(BIN)

$(OBJ)/main.o: $(SRC)/main.c
	clang -std=c99 -Wall -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/png-reader.o: $(SRC)/png-reader.o
	clang -std=c99 -Wall -c $(SRC)/png-reader.c -o $(OBJ)/png-reader.o

.PHONY: clean

clean:
	rm -f $(OBJ)/* $(BIN)
