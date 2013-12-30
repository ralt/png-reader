#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "crc.h"

#ifndef PNG_FRAME
#define PNG_FRAME

/**
 * The size of the PNG headers file.
 */
#define PNG_headers_size 8

/**
 * A PNG chunk has 2 headers, its data, and a CRC field.
 */
#define PNG_header_length_size 4
#define PNG_header_type_size 4
#define PNG_header_crc_size 4

/**
 * A single PNG chunk.
 */
struct PNG_chunk {
	uint8_t length[4];
	uint8_t type[4];
	uint8_t *data;
	uint8_t crc[4];
};

#endif

/**
 * Gets the chunk length according to its first field.
 */
size_t PNG_chunk_length(struct PNG_chunk *chunk);

/**
 * Sets the type of the chunk.
 */
void PNG_chunk_type(struct PNG_chunk *chunk, char **buf);

/**
 * Gets the CRC of the chunk.
 */
unsigned long PNG_chunk_crc(struct PNG_chunk *chunk);

/**
 * Checks if the CRC is valid by recomputing it.
 */
bool PNG_chunk_check_crc(struct PNG_chunk *chunk);

/**
 * Frees the PNG_chunk struct.
 */
void PNG_chunk_free(struct PNG_chunk *chunk);
