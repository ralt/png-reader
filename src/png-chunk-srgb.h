#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_SRGB
#define PNG_CHUNK_SRGB

#include "png-chunk.h"

struct PNG_chunk_sRGB {
	size_t index;
	uint8_t rendering_intent;
};

/**
 * Checks that the chunk is an sRGB chunk.
 */
bool PNG_chunk_sRGB_check_type(struct PNG_chunk * chunk);

#endif
