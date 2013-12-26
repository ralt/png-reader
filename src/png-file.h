#include <stdio.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

extern size_t const PNG_headers_size;

#ifndef PNG_FILE
#define PNG_FILE

/**
 * Defines a single PNG file.
 */
typedef struct
{
    uint8_t headers[PNG_headers_size];
    PNG_frame_vector frames;
} PNG_file;

#endif

/**
 * Checks that all critical chunks of a PNG file are correctly implemented.
 */
bool PNG_file_check_critical_chunks(PNG_file *file);

/**
 * Checks the headers of the PNG file.
 */
bool PNG_file_check_headers(PNG_file *file);
