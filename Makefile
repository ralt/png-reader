all: dist/png-reader

dist/png-reader: obj/main.o obj/png-reader.o
	clang obj/main.o obj/png-reader.o -o dist/png-reader

obj/main.o: src/main.c
	clang -std=c99 -Wall -c src/main.c -o obj/main.o

obj/png-reader.o: src/png-reader.o
	clang -std=c99 -Wall -c src/png-reader.c -o obj/png-reader.o

.PHONY: clean

clean:
	rm -f obj/* dist/*
