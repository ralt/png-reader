#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PNG_CHUNK_ITXT
#define PNG_CHUNK_ITXT

#include "png-chunk.h"

struct PNG_chunk_iTXt {
	size_t index;

	char *keyword;
	uint8_t compression_flag;
	uint8_t compression_method;
	char *language_tag;
	char *translated_keyword;
	char *text;

};

struct PNG_chunk_iTXt_vector {
	size_t size;
	int capacity;
	struct PNG_chunk_iTXt **chunks;
};

/**
 * Checks that the chunk is an iTXt chunk.
 */
bool PNG_chunk_iTXt_check_type(struct PNG_chunk *chunk);

/**
 * Initializes the memory for a vector of chunks with defined capacity.
 */
void PNG_chunk_iTXt_vector_init(struct PNG_chunk_iTXt_vector *vector,
				int capacity);

/**
 * Appends a PNG_chunk on the vector. If needed, it reallocates memory.
 */
void PNG_chunk_iTXt_vector_append(struct PNG_chunk_iTXt_vector *vector,
				  struct PNG_chunk_iTXt *chunk);

/**
 * Returns the PNG_chunk at index.
 */
struct PNG_chunk_iTXt *PNG_chunk_iTXt_vector_get(struct PNG_chunk_iTXt_vector
						 *vector, int index);

/**
 * Defines the PNG_chunk stored at index.
 */
void PNG_chunk_iTXt_vector_set(struct PNG_chunk_iTXt_vector *vector, int index,
			       struct PNG_chunk_iTXt *value);

/**
 * Frees the memory for the vector.
 */
void PNG_chunk_iTXt_vector_free(struct PNG_chunk_iTXt_vector *vector);

/**
 * Frees the memory of a single iTXt chunk.
 */
void PNG_chunk_iTXt_free(struct PNG_chunk_iTXt *chunk);

#endif
