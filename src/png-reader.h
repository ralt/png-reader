#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static size_t const buffer_size = 8;

static size_t const PNG_headers_size = 8;

bool
PNG_read_headers(uint8_t headers[PNG_headers_size]);

typedef struct
{
    uint8_t length[4];
    uint8_t type[4];
    uint8_t *data;
    uint8_t crc[4];
} PNG_frame;

size_t
PNG_build_frames(size_t, PNG_frame frames[],
        uint8_t buffer[buffer_size]);
