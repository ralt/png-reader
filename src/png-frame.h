#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "crc.h"

#ifndef PNG_FRAME
#define PNG_FRAME

/**
 * The size of the PNG headers file.
 */
static size_t const PNG_headers_size = 8;

/**
 * A PNG chunk has 2 headers, its data, and a CRC field.
 */
static size_t const PNG_header_length_size = 4;
static size_t const PNG_header_type_size = 4;
static size_t const PNG_header_crc_size = 4;

/**
 * A single PNG frame.
 */
typedef struct
{
    uint8_t length[4];
    uint8_t type[4];
    uint8_t *data;
    uint8_t crc[4];
} PNG_frame;

#endif

/**
 * Gets the frame length according to its first field.
 */
size_t PNG_frame_length(PNG_frame *frame);

/**
 * Gets the CRC of the frame.
 */
unsigned long PNG_frame_crc(PNG_frame *frame);

/**
 * Checks if the CRC is valid by recomputing it.
 */
bool PNG_frame_crc_check(PNG_frame *frame);
