#include "png-chunk-gama.h"

bool PNG_chunk_gAMA_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x67, 0x41, 0x4d, 0x41 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
