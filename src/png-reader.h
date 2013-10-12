#include <stdio.h>
#include <stdint.h>

static size_t const PNG_HEADERS_SIZE = 8;

void
PNG_read_headers(uint8_t headers[PNG_HEADERS_SIZE]);
