#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_IDAT
#define PNG_CHUNK_IDAT

#include "png-chunk.h"

/**
 * Checks that the chunk is an IDAT chunk.
 */
bool PNG_chunk_IDAT_check_type(struct PNG_chunk * chunk);

#endif
