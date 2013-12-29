#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_IEND
#define PNG_CHUNK_IEND

#include "png-chunk.h"

struct PNG_chunk_IEND {
	size_t index;
};

/**
 * Checks that the chunk is an IEND chunk.
 */
bool PNG_chunk_IEND_check_type(struct PNG_chunk *chunk);

#endif
