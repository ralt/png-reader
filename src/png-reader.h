#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static size_t const PNG_headers_size = 8;

bool
PNG_read_headers(uint8_t headers[PNG_headers_size]);
