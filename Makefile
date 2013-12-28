CC=clang
OBJ=obj
BIN=dist/png-reader
SRC=src
FLAGS=-std=c99 -Wall

all: $(BIN)

debug: FLAGS += -ggdb
debug: all


$(BIN): $(OBJ)/png-chunk.o $(OBJ)/png-chunk-builder.o $(OBJ)/png-chunk-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o $(OBJ)/png-chunk-ihdr.o $(OBJ)/main.o
	$(CC) $(FLAGS) $(OBJ)/main.o $(OBJ)/png-chunk-ihdr.o $(OBJ)/png-chunk.o $(OBJ)/png-chunk-builder.o $(OBJ)/png-chunk-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o -o $(BIN)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(FLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/png-chunk.o: $(SRC)/png-chunk.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk.c -o $(OBJ)/png-chunk.o

$(OBJ)/png-chunk-builder.o: $(SRC)/png-chunk-builder.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-builder.c -o $(OBJ)/png-chunk-builder.o

$(OBJ)/png-chunk-vector.o: $(SRC)/png-chunk-vector.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-vector.c -o $(OBJ)/png-chunk-vector.o

$(OBJ)/crc.o: $(SRC)/crc.c
	$(CC) $(FLAGS) -c $(SRC)/crc.c -o $(OBJ)/crc.o

$(OBJ)/png-file.o: $(SRC)/png-file.c
	$(CC) $(FLAGS) -c $(SRC)/png-file.c -o $(OBJ)/png-file.o

$(OBJ)/png-chunk-ihdr.o: $(SRC)/png-chunk-ihdr.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-ihdr.c -o $(OBJ)/png-chunk-ihdr.o

.PHONY: clean debug

clean:
	rm -f $(OBJ)/* $(BIN)
