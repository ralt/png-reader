#include "png-chunk-text.h"

bool PNG_chunk_tEXt_check_type(struct PNG_chunk * chunk)
{
	uint8_t const defaults[] = { 0x74, 0x45, 0x58, 0x74 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}

void PNG_chunk_tEXt_vector_init(struct PNG_chunk_tEXt_vector *vector,
				int capacity)
{
	vector->size = 0;
	vector->capacity = capacity;
	vector->chunks =
	    malloc(sizeof(struct PNG_chunk_tEXt) * vector->capacity);
	if (vector->chunks == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (vector->chunks == NULL) {
		exit(errno);
	}
}

void
PNG_chunk_tEXt_vector_append(struct PNG_chunk_tEXt_vector *vector,
			     struct PNG_chunk_tEXt *chunk)
{
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->chunks = realloc(vector->chunks,
					 sizeof(struct PNG_chunk_tEXt) *
					 vector->capacity);
		if (vector->chunks == NULL) {
			exit(errno);
		}
	}
	vector->chunks[vector->size++] = chunk;
}

struct PNG_chunk_tEXt *PNG_chunk_tEXt_vector_get(struct PNG_chunk_tEXt_vector
						 *vector, int index)
{
	if (index < 0 || index >= vector->size) {
		printf("Out of bounds\n");
		exit(1);
	}
	return vector->chunks[index];
}

void
PNG_chunk_tEXt_vector_set(struct PNG_chunk_tEXt_vector *vector, int index,
			  struct PNG_chunk_tEXt *value)
{
	vector->chunks[index] = value;
}

void PNG_chunk_tEXt_vector_free(struct PNG_chunk_tEXt_vector *vector)
{
	for (size_t i = 0; i < vector->size; i++) {
		PNG_chunk_tEXt_free(PNG_chunk_tEXt_vector_get(vector, i));
	}
	free(vector);
}

void PNG_chunk_tEXt_free(struct PNG_chunk_tEXt *chunk)
{
	free(chunk->keyword);
	free(chunk->text);
	free(chunk);
}
