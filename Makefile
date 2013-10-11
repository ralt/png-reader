all:
	clang -ggdb -Wall -pedantic -std=c99 png-reader.c -o png-reader

clean:
	rm -f png-reader
