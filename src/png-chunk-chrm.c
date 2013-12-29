#include "png-chunk-chrm.h"

bool PNG_chunk_cHRM_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x63, 0x48, 0x52, 0x4d };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
