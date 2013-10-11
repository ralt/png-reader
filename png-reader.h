#include <stdio.h> // printf, FILE*
#include <stdlib.h> // exit
#include <stdint.h> // uint8_t
#include <inttypes.h> // PRIu8

#define BUFFER_SIZE 4

size_t read_bytes(FILE*, uint8_t *buffer[BUFFER_SIZE]);
