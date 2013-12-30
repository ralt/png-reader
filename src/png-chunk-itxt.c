#include "png-chunk-itxt.h"

bool PNG_chunk_iTXt_check_type(struct PNG_chunk * chunk)
{
	uint8_t const defaults[] = { 0x69, 0x54, 0x58, 0x74 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}

void PNG_chunk_iTXt_vector_init(struct PNG_chunk_iTXt_vector *vector,
				int capacity)
{
	vector->size = 0;
	vector->capacity = capacity;
	vector->chunks =
	    malloc(sizeof(struct PNG_chunk_iTXt) * vector->capacity);
	if (vector->chunks == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (vector->chunks == NULL) {
		exit(errno);
	}
}

void
PNG_chunk_iTXt_vector_append(struct PNG_chunk_iTXt_vector *vector,
			     struct PNG_chunk_iTXt *chunk)
{
	if (vector->size >= vector->capacity) {
		vector->capacity *= 2;
		vector->chunks = realloc(vector->chunks,
					 sizeof(struct PNG_chunk_iTXt) *
					 vector->capacity);
		if (vector->chunks == NULL) {
			exit(errno);
		}
	}
	vector->chunks[vector->size++] = chunk;
}

struct PNG_chunk_iTXt *PNG_chunk_iTXt_vector_get(struct PNG_chunk_iTXt_vector
						 *vector, int index)
{
	if (index < 0 || index >= vector->size) {
		printf("Out of bounds\n");
		exit(1);
	}
	return vector->chunks[index];
}

void
PNG_chunk_iTXt_vector_set(struct PNG_chunk_iTXt_vector *vector, int index,
			  struct PNG_chunk_iTXt *value)
{
	vector->chunks[index] = value;
}

void PNG_chunk_iTXt_vector_free(struct PNG_chunk_iTXt_vector *vector)
{
	for (size_t i = 0; i < vector->size; i++) {
		PNG_chunk_iTXt_free(PNG_chunk_iTXt_vector_get(vector, i));
	}
	free(vector);
}

void PNG_chunk_iTXt_free(struct PNG_chunk_iTXt *chunk)
{
	free(chunk->keyword);
	free(chunk->language_tag);
	free(chunk->translated_keyword);
	free(chunk->text);
	free(chunk);
}
