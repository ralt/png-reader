#include "png-chunk-ihdr.h"

bool PNG_chunk_IHDR_check_type(struct PNG_frame *frame)
{
	uint8_t const defaults[] = { 0x49, 0x48, 0x44, 0x52 };

	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != frame->type[i]) {
			return false;
		}
	}

	return true;
}

bool PNG_chunk_IHDR_set_dimensions(struct PNG_file * file,
				   struct PNG_frame * frame)
{
	if ((file->width = PNG_chunk_IHDR_width(frame)) == 0) {
		return false;
	}
	if ((file->height = PNG_chunk_IHDR_height(frame)) == 0) {
		return false;
	}
	return true;
}

int PNG_chunk_IHDR_width(struct PNG_frame *frame)
{
	return (int)((uint32_t) frame->data[0] << 24 |
		     (uint32_t) frame->data[1] << 16 |
		     (uint32_t) frame->data[2] << 8 |
		     (uint32_t) frame->data[3]);
}

int PNG_chunk_IHDR_height(struct PNG_frame *frame)
{
	return (int)((uint32_t) frame->data[4] << 24 |
		     (uint32_t) frame->data[5] << 16 |
		     (uint32_t) frame->data[6] << 8 |
		     (uint32_t) frame->data[7]);
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
bool PNG_chunk_IHDR_check_bit_depth_color_type(struct PNG_file *file,
					       struct PNG_frame *frame)
{
	return true;
}
