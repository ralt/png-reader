#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_SPLT
#define PNG_CHUNK_SPLT

#include "png-chunk.h"

struct PNG_chunk_sPLT_palette_entry {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
	unsigned int frequency;
};

struct PNG_chunk_sPLT {
	size_t index;

	char *palette_name;
	uint8_t sample_depth;

	struct PNG_chunk_sPLT_palette_entry **palette_entries;
};

struct PNG_chunk_sPLT_vector {
	size_t size;
	int capacity;
	struct PNG_chunk_sPLT **chunks;
};

/**
 * Checks that the chunk is an sPLT chunk.
 */
bool PNG_chunk_sPLT_check_type(struct PNG_chunk *chunk);

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_sPLT_vector_init(struct PNG_chunk_sPLT_vector *vector,
				int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_sPLT_vector_append(struct PNG_chunk_sPLT_vector *vector,
				  struct PNG_chunk_sPLT *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk_sPLT *PNG_chunk_sPLT_vector_get(struct PNG_chunk_sPLT_vector
						 *vector, int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void PNG_chunk_sPLT_vector_set(struct PNG_chunk_sPLT_vector *vector, int index,
			       struct PNG_chunk_sPLT *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_sPLT_vector_free(struct PNG_chunk_sPLT_vector *vector);

/**
 * Frees the memory of a single sPLT chunk.
 */
void PNG_chunk_sPLT_free(struct PNG_chunk_sPLT *chunk);

#endif
