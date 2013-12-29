CC=clang
OBJ=obj
BIN=dist/png-reader
SRC=src
FLAGS=-std=c99 -Wall

all: $(BIN)

debug: FLAGS += -ggdb
debug: all


$(BIN): $(OBJ)/png-chunk.o $(OBJ)/png-chunk-builder.o $(OBJ)/png-chunk-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o $(OBJ)/png-chunk-ihdr.o $(OBJ)/png-chunk-plte.o $(OBJ)/png-chunk-idat.o $(OBJ)/png-chunk-iend.o $(OBJ)/png-chunk-chrm.o $(OBJ)/png-chunk-gama.o $(OBJ)/png-chunk-iccp.o $(OBJ)/png-chunk-sbit.o $(OBJ)/png-chunk-srgb.o $(OBJ)/main.o
	$(CC) $(FLAGS) $(OBJ)/main.o $(OBJ)/png-chunk-ihdr.o $(OBJ)/png-chunk-plte.o $(OBJ)/png-chunk-idat.o $(OBJ)/png-chunk-iend.o $(OBJ)/png-chunk-chrm.o $(OBJ)/png-chunk-gama.o $(OBJ)/png-chunk-iccp.o $(OBJ)/png-chunk-sbit.o $(OBJ)/png-chunk-srgb.o $(OBJ)/png-chunk.o $(OBJ)/png-chunk-builder.o $(OBJ)/png-chunk-vector.o $(OBJ)/crc.o $(OBJ)/png-file.o -o $(BIN)

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

$(OBJ)/png-chunk-iend.o: $(SRC)/png-chunk-iend.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-iend.c -o $(OBJ)/png-chunk-iend.o

$(OBJ)/png-chunk-idat.o: $(SRC)/png-chunk-idat.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-idat.c -o $(OBJ)/png-chunk-idat.o

$(OBJ)/png-chunk-plte.o: $(SRC)/png-chunk-plte.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-plte.c -o $(OBJ)/png-chunk-plte.o

$(OBJ)/png-chunk-chrm.o: $(SRC)/png-chunk-chrm.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-chrm.c -o $(OBJ)/png-chunk-chrm.o

$(OBJ)/png-chunk-gama.o: $(SRC)/png-chunk-gama.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-gama.c -o $(OBJ)/png-chunk-gama.o

$(OBJ)/png-chunk-iccp.o: $(SRC)/png-chunk-iccp.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-iccp.c -o $(OBJ)/png-chunk-iccp.o

$(OBJ)/png-chunk-sbit.o: $(SRC)/png-chunk-sbit.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-sbit.c -o $(OBJ)/png-chunk-sbit.o

$(OBJ)/png-chunk-srgb.o: $(SRC)/png-chunk-srgb.c
	$(CC) $(FLAGS) -c $(SRC)/png-chunk-srgb.c -o $(OBJ)/png-chunk-srgb.o

.PHONY: clean debug

clean:
	rm -f $(OBJ)/* $(BIN)
