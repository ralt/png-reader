FLAGS=-std=c99 -Wall

all: dist/png-reader

debug: FLAGS += -ggdb
debug: all

dist/png-reader: obj/main.o obj/png-reader.o
	clang obj/main.o obj/png-reader.o -o dist/png-reader

obj/main.o: src/main.c
	clang $(FLAGS) -c src/main.c -o obj/main.o

obj/png-reader.o: src/png-reader.o
	clang $(FLAGS) -c src/png-reader.c -o obj/png-reader.o

.PHONY: clean debug

clean:
	rm -f obj/* dist/*
