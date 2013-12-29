#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "png-chunk.h"
#include "png-chunk-vector.h"

/**
 * Builds the chunks from what's in the *content array.
 */
void
PNG_build_chunks(struct PNG_chunk_vector *chunks, uint8_t * content,
		 size_t size, int cursor);

/**
 * Builds a single chunk.
 */
void PNG_build_chunk(uint8_t * content, struct PNG_chunk *chunk, int cursor);

/**
 * Builds chunks semantically and attach them on the file.
 */
void PNG_build_semantic_chunks(struct PNG_file * file);
