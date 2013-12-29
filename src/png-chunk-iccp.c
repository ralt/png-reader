#include "png-chunk-iccp.h"

bool PNG_chunk_iCCP_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x69, 0x43, 0x43, 0x50 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
