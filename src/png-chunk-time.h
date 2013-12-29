#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_TIME
#define PNG_CHUNK_TIME

#include "png-chunk.h"

struct PNG_chunk_tIME {
	size_t index;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};

/**
 * Checks that the chunk is an tIME chunk.
 */
bool PNG_chunk_tIME_check_type(struct PNG_chunk *chunk);

#endif
