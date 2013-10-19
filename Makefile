CC=gcc
OBJ=obj
BIN=dist/png-reader
SRC=src
FLAGS=-ggdb -std=c99 -Wall

all: $(BIN)

$(BIN): $(OBJ)/main.o $(OBJ)/byte.o $(OBJ)/png-reader.o $(OBJ)/png-frame-vector.o
	$(CC) $(OBJ)/main.o $(OBJ)/byte.o $(OBJ)/png-reader.o $(OBJ)/png-frame-vector.o -o $(BIN)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(FLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/byte.o: $(SRC)/byte.c
	$(CC) $(FLAGS) -c $(SRC)/byte.c -o $(OBJ)/byte.o

$(OBJ)/png-reader.o: $(SRC)/png-reader.o
	$(CC) $(FLAGS) -c $(SRC)/png-reader.c -o $(OBJ)/png-reader.o

$(OBJ)/png-frame-vector.o: $(SRC)/png-frame-vector.o
	$(CC) $(FLAGS) -c $(SRC)/png-frame-vector.c -o $(OBJ)/png-frame-vector.o

.PHONY: clean

clean:
	rm -f $(OBJ)/* $(BIN)
