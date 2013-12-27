#include <stdio.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"
#include "png-frame-builder.h"

extern size_t const PNG_headers_size;
extern size_t const PNG_header_type_size;

#ifndef PNG_FILE
#define PNG_FILE

/**
 * Defines a single PNG file.
 */
struct PNG_file {
    uint8_t headers[PNG_headers_size];
    PNG_frame_vector *frames;
};

#endif

/**
 * Imports a PNG file contents in struct PNG_file struct.
 */
void PNG_file_import(struct PNG_file *file, uint8_t *content, size_t size);

/**
 * Frees a struct PNG_file struct.
 */
void PNG_file_free(struct PNG_file *file);

/**
 * Checks that all critical chunks of a PNG file are correctly implemented.
 */
bool PNG_file_check_critical_chunks(struct PNG_file *file);

/**
 * Checks the headers of the PNG file.
 */
bool PNG_file_check_headers(struct PNG_file *file);

/**
 * Checks that the IHDR chunk is correct.
 */
bool PNG_file_check_IHDR(struct PNG_file *file);

/**
 * Checks that the IDAT chunk is correct.
 */
bool PNG_file_check_IDAT(struct PNG_file *file);

/**
 * Checks that the IEND chunk is correct.
 */
bool PNG_file_check_IEND(struct PNG_file *file);
