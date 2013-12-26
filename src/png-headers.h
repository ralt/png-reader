#include <stdint.h>
#include <stdbool.h>

#include "png-frame.h"

extern size_t const PNG_headers_size;

bool PNG_read_headers(uint8_t headers[PNG_headers_size]);
