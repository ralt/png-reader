#include "png-chunk-ihdr.h"

bool PNG_chunk_IHDR_check_type(struct PNG_chunk *chunk)
{
	uint8_t const defaults[] = { 0x49, 0x48, 0x44, 0x52 };

	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != chunk->type[i]) {
			return false;
		}
	}

	return true;
}

bool PNG_chunk_IHDR_set_dimensions(struct PNG_chunk_IHDR * IHDR_chunk,
				   struct PNG_chunk * chunk)
{
	if ((IHDR_chunk->width = PNG_chunk_IHDR_width(chunk)) == 0) {
		return false;
	}
	if ((IHDR_chunk->height = PNG_chunk_IHDR_height(chunk)) == 0) {
		return false;
	}
	return true;
}

int PNG_chunk_IHDR_width(struct PNG_chunk *chunk)
{
	return (int)((uint32_t) chunk->data[0] << 24 |
		     (uint32_t) chunk->data[1] << 16 |
		     (uint32_t) chunk->data[2] << 8 |
		     (uint32_t) chunk->data[3]);
}

int PNG_chunk_IHDR_height(struct PNG_chunk *chunk)
{
	return (int)((uint32_t) chunk->data[4] << 24 |
		     (uint32_t) chunk->data[5] << 16 |
		     (uint32_t) chunk->data[6] << 8 |
		     (uint32_t) chunk->data[7]);
}

/**
 * There are 5 color types allowed. Each color type has its set of allowed
 * bit depths. Here is the list:
 *
 *   Color type | Bit depths
 *   0          | 1, 2, 4, 8, 16
 *   2          | 8, 16
 *   3          | 1, 2, 4, 8
 *   4          | 8, 16
 *   6          | 8, 16
 */
bool PNG_chunk_IHDR_check_bit_depth_color_type(struct PNG_chunk_IHDR
					       *IHDR_chunk,
					       struct PNG_chunk *chunk)
{
	bool check = false;

	IHDR_chunk->bit_depth = (int)chunk->data[8];
	IHDR_chunk->color_type = (int)chunk->data[9];
	switch (IHDR_chunk->color_type) {

	case 0:
		switch (IHDR_chunk->bit_depth) {
		case 1:
		case 2:
		case 4:
		case 8:
		case 16:
			check = true;
			break;
		}
	case 2:
		switch (IHDR_chunk->bit_depth) {
		case 8:
		case 16:
			check = true;
			break;
		}
	case 3:
		switch (IHDR_chunk->bit_depth) {
		case 1:
		case 2:
		case 4:
		case 8:
			check = true;
			break;
		}
	case 4:
		switch (IHDR_chunk->bit_depth) {
		case 8:
		case 16:
			check = true;
			break;
		}
	case 6:
		switch (IHDR_chunk->bit_depth) {
		case 8:
		case 16:
			check = true;
			break;
		}
	}

	return check;
}

/**
 * Accepted values: 0 (deflate/inflate compression with a sliding window of at most 32768 bytes)
 */
bool PNG_chunk_IHDR_check_compression_method(struct PNG_chunk_IHDR * IHDR_chunk,
					     struct PNG_chunk * chunk)
{
	IHDR_chunk->compression_method = (int)chunk->data[10];
	return IHDR_chunk->compression_method == 0;
}

/**
 * Accepted values: 0 (adaptive filtering with five basic filter types)
 */
bool PNG_chunk_IHDR_check_filter_method(struct PNG_chunk_IHDR * IHDR_chunk,
					struct PNG_chunk * chunk)
{
	IHDR_chunk->filter_method = (int)chunk->data[11];
	return IHDR_chunk->filter_method == 0;
}

/**
 * Accepted values: 0 (no interlace) or 1 (Adam7 interlace)
 */
bool PNG_chunk_IHDR_check_interlace_method(struct PNG_chunk_IHDR * IHDR_chunk,
					   struct PNG_chunk * chunk)
{
	IHDR_chunk->interlace_method = (int)chunk->data[12];
	return IHDR_chunk->interlace_method == 0
	    || IHDR_chunk->interlace_method == 1;
}
