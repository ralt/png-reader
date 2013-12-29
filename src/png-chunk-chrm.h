#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_CHRM
#define PNG_CHUNK_CHRM

#include "png-chunk.h"

struct PNG_chunk_cHRM {
	size_t index;
	int white_point_x;
	int white_point_y;
	int red_x;
	int red_y;
	int green_x;
	int green_y;
	int blue_x;
	int blue_y;
};

/**
 * Checks that the chunk is an cHRM chunk.
 */
bool PNG_chunk_cHRM_check_type(struct PNG_chunk *chunk);

#endif
