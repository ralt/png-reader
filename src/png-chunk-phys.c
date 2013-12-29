#include "png-chunk-phys.h"

bool PNG_chunk_pHYs_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x70, 0x48, 0x59, 0x73 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
