#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_IHDR
#define PNG_CHUNK_IHDR

#include "png-file.h"
#include "png-chunk.h"

/**
 * Checks the chunk to assert that it's an IHDR chunk.
 */
bool PNG_chunk_IHDR_check_type(struct PNG_chunk *chunk);

/**
 * Sets the width and height of the image on PNG_file.
 * Returns true or false if the dimensions violate the PNG spec.
 */
bool PNG_chunk_IHDR_set_dimensions(struct PNG_file *file,
				   struct PNG_chunk *chunk);

/**
 * Sets the width of the file.
 */
int PNG_chunk_IHDR_width(struct PNG_chunk *chunk);

/**
 * Sets the height of the file.
 */
int PNG_chunk_IHDR_height(struct PNG_chunk *chunk);

/**
 * Checks that bit depth and color type are spec-compliant.
 *
 * Also sets the values on the PNG_file struct.
 */
bool PNG_chunk_IHDR_check_bit_depth_color_type(struct PNG_file *file,
					       struct PNG_chunk *chunk);

/**
 * Checks that the compression method is spec-compliant.
 *
 * Also sets the value on the PNG_file struct.
 */
bool PNG_chunk_IHDR_check_compression_method(struct PNG_file *file,
					     struct PNG_chunk *chunk);

/**
 * Checks that the filter method is spec-compliant.
 *
 * Also sets the value on the PNG_file struct.
 */
bool PNG_chunk_IHDR_check_filter_method(struct PNG_file *file,
					struct PNG_chunk *chunk);

/**
 * Checks that the interlace method is spec-compliant.
 *
 * Also sets the value on the PNG_file struct.
 */
bool PNG_chunk_IHDR_check_interlace_method(struct PNG_file *file,
					   struct PNG_chunk *chunk);

#endif
