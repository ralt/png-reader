#include "png-chunk-iend.h"

bool PNG_chunk_IEND_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x49, 0x45, 0x4e, 0x44 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
