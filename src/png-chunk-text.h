#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_TEXT
#define PNG_CHUNK_TEXT

#include "png-chunk.h"

struct PNG_chunk_tEXt {
	size_t index;

	char *keyword;
	char *text;

};

struct PNG_chunk_tEXt_vector {
	size_t size;
	int capacity;
	struct PNG_chunk_tEXt **chunks;
};

/**
 * Checks that the chunk is an tEXt chunk.
 */
bool PNG_chunk_tEXt_check_type(struct PNG_chunk *chunk);

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_tEXt_vector_init(struct PNG_chunk_tEXt_vector *vector,
				int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_tEXt_vector_append(struct PNG_chunk_tEXt_vector *vector,
				  struct PNG_chunk_tEXt *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk_tEXt *PNG_chunk_tEXt_vector_get(struct PNG_chunk_tEXt_vector
						 *vector, int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void PNG_chunk_tEXt_vector_set(struct PNG_chunk_tEXt_vector *vector, int index,
			       struct PNG_chunk_tEXt *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_tEXt_vector_free(struct PNG_chunk_tEXt_vector *vector);

/**
 * Frees the memory of a single tEXt chunk.
 */
void PNG_chunk_tEXt_free(struct PNG_chunk_tEXt *chunk);

#endif
