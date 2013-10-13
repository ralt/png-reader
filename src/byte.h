#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern size_t const PNG_headers_size;

static size_t const BUFFER_SIZE = 4;

size_t
read_bytes(FILE*, uint8_t buffer[BUFFER_SIZE]);

void
add_bytes(uint8_t headers[PNG_headers_size], uint8_t buffer[BUFFER_SIZE],
        size_t);
