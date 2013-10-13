#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern size_t const PNG_headers_size;

static size_t const buffer_size = 8;

size_t
read_bytes(FILE*, uint8_t buffer[buffer_size]);
