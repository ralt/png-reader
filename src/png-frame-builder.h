#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

extern size_t const PNG_headers_size;

extern size_t const PNG_header_length_size;
extern size_t const PNG_header_type_size;
extern size_t const PNG_header_crc_size;

void PNG_build_frames(PNG_frame_vector *frames, uint8_t *content, long fsize,
        int cursor);

void PNG_build_frame(uint8_t *content, PNG_frame *frame, int cursor);