#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_PHYS
#define PNG_CHUNK_PHYS

#include "png-chunk.h"

struct PNG_chunk_pHYs {
	size_t index;

	unsigned int px_per_unit_x;
	unsigned int px_per_unit_y;

	uint8_t unit_specifier;
};

/**
 * Checks that the chunk is an pHYs chunk.
 */
bool PNG_chunk_pHYs_check_type(struct PNG_chunk *chunk);

#endif
