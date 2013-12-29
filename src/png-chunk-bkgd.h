#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_BKGD
#define PNG_CHUNK_BKGD

#include "png-chunk.h"

struct PNG_chunk_bKGD {
	size_t index;

	// color type 3
	uint8_t palette_index;

	// color type 0 and 4
	uint16_t grayscale;

	// color type 2 and 6
	uint16_t red;
	uint16_t green;
	uint16_t blue;
};

/**
 * Checks that the chunk is an bKGD chunk.
 */
bool PNG_chunk_bKGD_check_type(struct PNG_chunk *chunk);

#endif
