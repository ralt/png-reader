#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#ifndef PNG_FILE
#define PNG_FILE

#include "png-frame.h"

/**
 * Defines a single PNG file.
 */
struct PNG_file {
	uint8_t headers[PNG_headers_size];
	struct PNG_frame_vector *frames;
	int width;
	int height;
	int bit_depth;
	int color_type;
	int compression_method;
	int filter_method;
	int interlace_method;
};

#include "png-frame-vector.h"
#include "png-frame-builder.h"
#include "png-chunk-ihdr.h"

/**
 * Imports a PNG file contents in struct PNG_file struct.
 */
void PNG_file_import(struct PNG_file *file, uint8_t * content, size_t size);

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

#endif
