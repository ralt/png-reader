#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_GAMA
#define PNG_CHUNK_GAMA

#include "png-chunk.h"

struct PNG_chunk_GAMA {
	size_t index;
	unsigned int gamma;
};

/**
 * Checks that the chunk is an gAMA chunk.
 */
bool PNG_chunk_gAMA_check_type(struct PNG_chunk *chunk);

#endif
