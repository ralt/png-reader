#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_PLTE
#define PNG_CHUNK_PLTE

#include "png-chunk.h"

struct PNG_PLTE_chunk {
	size_t index;
	int length;
	uint8_t *data;
};

/**
 * Checks that the chunk is a PLTE chunk.
 */
bool PNG_chunk_PLTE_check_type(struct PNG_chunk *chunk);

#endif
