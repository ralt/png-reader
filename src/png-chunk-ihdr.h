#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_IHDR
#define PNG_CHUNK_IHDR

#include "png-file.h"
#include "png-frame.h"

/**
 * Checks the frame to assert that it's an IHDR chunk.
 */
bool PNG_chunk_IHDR_check_type(struct PNG_frame *frame);

/**
 * Sets the width and height of the image on PNG_file.
 * Returns true or false if the dimensions violate the PNG spec.
 */
bool PNG_chunk_IHDR_set_dimensions(struct PNG_file *file,
				   struct PNG_frame *frame);

int PNG_chunk_IHDR_width(struct PNG_frame *frame);

int PNG_chunk_IHDR_height(struct PNG_frame *frame);

bool PNG_chunk_IHDR_check_bit_depth_color_type(struct PNG_file *file,
					       struct PNG_frame *frame);

#endif
