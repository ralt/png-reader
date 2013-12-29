#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_HIST
#define PNG_CHUNK_HIST

#include "png-chunk.h"

struct PNG_chunk_hIST {
	size_t index;
	uint16_t *data;
};

/**
 * Checks that the chunk is an hIST chunk.
 */
bool PNG_chunk_hIST_check_type(struct PNG_chunk *chunk);

#endif
