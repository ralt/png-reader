#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_TRNS
#define PNG_CHUNK_TRNS

#include "png-chunk.h"

struct PNG_chunk_tRNS {
	size_t index;

	// color type 3
	uint8_t *alpha;

	// color type 0
	uint16_t gray;

	// color type 2
	uint16_t red;
	uint16_t green;
	uint16_t blue;
};

/**
 * Checks that the chunk is an tRNS chunk.
 */
bool PNG_chunk_tRNS_check_type(struct PNG_chunk *chunk);

#endif
