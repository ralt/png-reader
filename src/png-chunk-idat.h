#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_IDAT
#define PNG_CHUNK_IDAT

#include "png-chunk.h"

struct PNG_chunk_IDAT {
	size_t index;
	int length;
	uint8_t *data;
};

struct PNG_chunk_IDAT_vector {
	size_t size;
	int capacity;
	struct PNG_chunk_IDAT **chunks;
};

/**
 * Checks that the chunk is an IDAT chunk.
 */
bool PNG_chunk_IDAT_check_type(struct PNG_chunk *chunk);

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_IDAT_vector_init(struct PNG_chunk_IDAT_vector *vector,
				int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_IDAT_vector_append(struct PNG_chunk_IDAT_vector *vector,
				  struct PNG_chunk_IDAT *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk_IDAT *PNG_chunk_IDAT_vector_get(struct PNG_chunk_IDAT_vector
						 *vector, int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void PNG_chunk_IDAT_vector_set(struct PNG_chunk_IDAT_vector *vector, int index,
			       struct PNG_chunk_IDAT *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_IDAT_vector_free(struct PNG_chunk_IDAT_vector *vector);

#endif
