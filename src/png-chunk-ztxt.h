#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_ZTXT
#define PNG_CHUNK_ZTXT

#include "png-chunk.h"

struct PNG_chunk_zTXt {
	size_t index;

	char *keyword;
	uint8_t compression_method;
	char *compressed_text;

};

struct PNG_chunk_zTXt_vector {
	size_t size;
	int capacity;
	struct PNG_chunk_zTXt **chunks;
};

/**
 * Checks that the chunk is an zTXt chunk.
 */
bool PNG_chunk_zTXt_check_type(struct PNG_chunk *chunk);

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_zTXt_vector_init(struct PNG_chunk_zTXt_vector *vector,
				int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_zTXt_vector_append(struct PNG_chunk_zTXt_vector *vector,
				  struct PNG_chunk_zTXt *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk_zTXt *PNG_chunk_zTXt_vector_get(struct PNG_chunk_zTXt_vector
						 *vector, int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void PNG_chunk_zTXt_vector_set(struct PNG_chunk_zTXt_vector *vector, int index,
			       struct PNG_chunk_zTXt *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_zTXt_vector_free(struct PNG_chunk_zTXt_vector *vector);

/**
 * Frees the memory of a single zTXt chunk.
 */
void PNG_chunk_zTXt_free(struct PNG_chunk_zTXt *chunk);

#endif
