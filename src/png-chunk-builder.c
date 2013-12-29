#include "png-chunk-builder.h"

void
PNG_build_chunks(struct PNG_chunk_vector *chunks, uint8_t * content,
		 size_t size, int cursor)
{
	struct PNG_chunk *chunk = malloc(sizeof(struct PNG_chunk));
	if (chunk == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < PNG_header_length_size; i++) {
		chunk->length[i] = content[cursor + i];
	}

	PNG_build_chunk(content, chunk, cursor);
	PNG_chunk_vector_append(chunks, chunk);

	cursor += PNG_header_length_size + PNG_header_type_size +
	    PNG_header_crc_size + PNG_chunk_length(chunk);

	if (cursor < size) {
		PNG_build_chunks(chunks, content, size, cursor);
	}
}

void PNG_build_chunk(uint8_t * content, struct PNG_chunk *chunk, int cursor)
{
	size_t chunk_length = PNG_chunk_length(chunk);
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		chunk->type[i] = content[cursor + PNG_header_length_size + i];
	}

	chunk->data = malloc(sizeof(uint8_t) * chunk_length);
	if (chunk->data == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < chunk_length; i++) {
		chunk->data[i] = content[cursor + PNG_header_length_size +
					 PNG_header_type_size + i];
	}

	for (size_t i = 0; i < PNG_header_crc_size; i++) {
		chunk->crc[i] = content[cursor + PNG_header_length_size +
					PNG_header_type_size + chunk_length +
					i];
	}
}

void PNG_build_semantic_chunks(struct PNG_file *file)
{
}
