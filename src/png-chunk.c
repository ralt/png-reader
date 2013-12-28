#include "png-chunk.h"

size_t PNG_chunk_length(struct PNG_chunk *chunk)
{
	return (size_t) ((uint32_t) chunk->length[0] << 24 |
			 (uint32_t) chunk->length[1] << 16 |
			 (uint32_t) chunk->length[2] << 8 |
			 (uint32_t) chunk->length[3]);
}

void PNG_chunk_type(struct PNG_chunk *chunk, char **buf)
{
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		(*buf)[i] = (char) chunk->type[i];
	}
}

unsigned long PNG_chunk_crc(struct PNG_chunk *chunk)
{
	return (unsigned long)((uint32_t) chunk->crc[0] << 24 |
			       (uint32_t) chunk->crc[1] << 16 |
			       (uint32_t) chunk->crc[2] << 8 |
			       (uint32_t) chunk->crc[3]);
}

bool PNG_chunk_check_crc(struct PNG_chunk *chunk)
{
	unsigned char *buf = malloc(sizeof(unsigned char) * (PNG_chunk_length(chunk) +	//chunk->data
							     (sizeof(uint8_t) * PNG_header_type_size)	// chunk->type
				    ));
	if (buf == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	size_t buf_size = PNG_chunk_length(chunk) + PNG_header_type_size;

	for (size_t i = 0; i < buf_size; i++) {
		if (i < PNG_header_type_size) {
			buf[i] = chunk->type[i];
		} else {
			buf[i] = chunk->data[i - PNG_header_type_size];
		}
	}

	unsigned long crc_gen =
	    crc(buf, (PNG_chunk_length(chunk) + PNG_header_type_size));

	bool checked = (crc_gen == PNG_chunk_crc(chunk));

	free(buf);

	return checked;
}

void PNG_chunk_free(struct PNG_chunk *chunk)
{
	free(chunk->data);
	free(chunk);
}
