#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

extern size_t const PNG_headers_size;
extern size_t const PNG_crc_size;
extern size_t const buffer_size;

size_t
PNG_build_frames(size_t, PNG_frame_vector *vector,
        uint8_t buffer[buffer_size]);

void
PNG_add_headers(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], size_t full_bytes_read,
        size_t buffer_offset);

void
PNG_add_data(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], signed int bytes_left);
