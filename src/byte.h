#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "png-reader.h"

extern size_t const PNG_headers_size;
extern size_t const buffer_size;

size_t
read_bytes(FILE*, uint8_t buffer[buffer_size]);
