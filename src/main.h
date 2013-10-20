#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "png-frame-vector.h"
#include "png-frame.h"
#include "png-frame-builder.h"
#include "byte.h"

extern size_t const PNG_headers_size;
extern size_t const buffer_size;

void
read_headers(uint8_t buffer[buffer_size]);
