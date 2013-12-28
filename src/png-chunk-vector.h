#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "png-chunk.h"

#ifndef PNG_FRAME_VECTOR
#define PNG_FRAME_VECTOR

struct PNG_chunk_vector {
	size_t size;
	int capacity;
	struct PNG_chunk **chunks;
};

#endif

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_vector_init(struct PNG_chunk_vector *vector, int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_vector_append(struct PNG_chunk_vector *vector,
			     struct PNG_chunk *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk *PNG_chunk_vector_get(struct PNG_chunk_vector *vector,
				       int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void
PNG_chunk_vector_set(struct PNG_chunk_vector *vector, int index,
		     struct PNG_chunk *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_vector_free(struct PNG_chunk_vector *vector);
