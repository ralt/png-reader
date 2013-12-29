#include "png-chunk-time.h"

bool PNG_chunk_tIME_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x74, 0x49, 0x4d, 0x45 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
