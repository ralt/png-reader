#include "png-chunk-plte.h"

bool PNG_chunk_PLTE_check_type(struct PNG_chunk *chunk)
{
	// @TODO find the PLTE hex values
	uint8_t const defaults[] = { 0x00, 0x00, 0x00, 0x00 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
