#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "png-frame.h"

extern size_t const PNG_headers_size;
extern size_t const buffer_size;

void
read_bytes(FILE*, uint8_t buffer[buffer_size]);
