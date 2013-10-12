#include <stdio.h> // printf, FILE*
#include <stdlib.h> // exit
#include <stdint.h> // uint8_t
#include <inttypes.h> // PRIu8
#include <errno.h>
#include <string.h>

#include "png-reader.h"

#define BUFFER_SIZE 4

size_t
read_bytes(FILE*, uint8_t buffer[BUFFER_SIZE]);

void
add_bytes(uint8_t headers[PNG_HEADERS_SIZE], uint8_t buffer[BUFFER_SIZE]);
