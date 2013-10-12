#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static size_t const PNG_HEADERS_SIZE = 8;

bool
PNG_read_headers(uint8_t headers[PNG_HEADERS_SIZE]);
