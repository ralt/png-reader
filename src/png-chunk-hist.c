#include "png-chunk-hist.h"

bool PNG_chunk_hIST_check_type(struct PNG_chunk * chunk)
{
	uint8_t const defaults[] = { 0x68, 0x49, 0x53, 0x54 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}
