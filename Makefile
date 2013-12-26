CC=clang
OBJ=obj
BIN=dist/png-reader
SRC=src
FLAGS=-std=c99 -Wall

all: $(BIN)

debug: FLAGS += -ggdb
debug: all


$(BIN): $(OBJ)/png-frame.o $(OBJ)/png-frame-builder.o $(OBJ)/png-frame-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o $(OBJ)/main.o
	$(CC) $(FLAGS) $(OBJ)/main.o $(OBJ)/png-frame.o $(OBJ)/png-frame-builder.o $(OBJ)/png-frame-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o -o $(BIN)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(FLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/png-frame.o: $(SRC)/png-frame.c
	$(CC) $(FLAGS) -c $(SRC)/png-frame.c -o $(OBJ)/png-frame.o

$(OBJ)/png-frame-builder.o: $(SRC)/png-frame-builder.c
	$(CC) $(FLAGS) -c $(SRC)/png-frame-builder.c -o $(OBJ)/png-frame-builder.o

$(OBJ)/png-frame-vector.o: $(SRC)/png-frame-vector.c
	$(CC) $(FLAGS) -c $(SRC)/png-frame-vector.c -o $(OBJ)/png-frame-vector.o

$(OBJ)/crc.o: $(SRC)/crc.c
	$(CC) $(FLAGS) -c $(SRC)/crc.c -o $(OBJ)/crc.o

$(OBJ)/png-file.o: $(SRC)/png-file.c
	$(CC) $(FLAGS) -c $(SRC)/png-file.c -o $(OBJ)/png-file.o

.PHONY: clean debug

clean:
	rm -f $(OBJ)/* $(BIN)
