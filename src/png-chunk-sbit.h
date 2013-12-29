#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_SBIT
#define PNG_CHUNK_SBIT

#include "png-chunk.h"

struct PNG_chunk_sBIT {
	size_t index;
	unsigned int sbit_number;
};

/**
 * Checks that the chunk is an sBIT chunk.
 */
bool PNG_chunk_sBIT_check_type(struct PNG_chunk *chunk);

#endif
