#include "png-chunk-plte.h"

bool PNG_chunk_PLTE_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x50, 0x4c, 0x54, 0x45 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
