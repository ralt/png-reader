#include "png-chunk-srgb.h"

bool PNG_chunk_sRGB_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x73, 0x52, 0x47, 0x42 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
