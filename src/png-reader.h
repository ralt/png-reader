#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

#ifndef PNG_READER
#define PNG_READER
static size_t const buffer_size = 8;

static size_t const PNG_headers_size = 8;
#endif

bool
PNG_read_headers(uint8_t headers[PNG_headers_size]);

size_t
PNG_build_frames(size_t, PNG_frame_vector *vector,
        uint8_t buffer[buffer_size]);

void
PNG_add_headers(PNG_frame_vector *vector,
        uint8_t buffer[buffer_size]);
