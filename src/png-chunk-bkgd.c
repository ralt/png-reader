#include "png-chunk-bkgd.h"

bool PNG_chunk_bKGD_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x62, 0x4b, 0x47, 0x44 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
