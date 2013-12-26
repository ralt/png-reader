#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef PNG_FRAME
#define PNG_FRAME

static size_t const buffer_size = 8;

static size_t const PNG_headers_size = 8;

static size_t const PNG_crc_size = 4;

static size_t const PNG_header_length_size = 4;
static size_t const PNG_header_type_size = 4;
static size_t const PNG_header_crc_size = 4;

typedef struct
{
    uint8_t length[4];
    uint8_t type[4];
    uint8_t *data;
    uint8_t crc[4];
} PNG_frame;

#endif

size_t PNG_frame_length(PNG_frame *frame);

size_t PNG_frame_type(PNG_frame *frame, unsigned char[4]);
