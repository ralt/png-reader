#include "png-chunk-trns.h"

bool PNG_chunk_tRNS_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x74, 0x52, 0x4e, 0x53 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
