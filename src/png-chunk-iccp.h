#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_ICCP
#define PNG_CHUNK_ICCP

#include "png-chunk.h"

struct PNG_chunk_iCCP {
	size_t index;
	char *profile_name;
	uint8_t compression_method;
	uint8_t *compressed_profile;
};

/**
 * Checks that the chunk is an iCCP chunk.
 */
bool PNG_chunk_iCCP_check_type(struct PNG_chunk *chunk);

#endif
