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
	bool check = false;

	file->bit_depth = (int)frame->data[8];
	file->color_type = (int)frame->data[9];
	switch (file->color_type) {

	case 0:
		switch (file->bit_depth) {
		case 1:
		case 2:
		case 4:
		case 8:
		case 16:
			check = true;
			break;
		}
	case 2:
		switch (file->bit_depth) {
		case 8:
		case 16:
			check = true;
			break;
		}
	case 3:
		switch (file->bit_depth) {
		case 1:
		case 2:
		case 4:
		case 8:
			check = true;
			break;
		}
	case 4:
		switch (file->bit_depth) {
		case 8:
		case 16:
			check = true;
			break;
		}
	case 6:
		switch (file->bit_depth) {
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
bool PNG_chunk_IHDR_check_compression_method(struct PNG_file * file,
					     struct PNG_frame * frame)
{
	file->compression_method = (int)frame->data[10];
	return file->compression_method == 0;
}

/**
 * Accepted values: 0 (adaptive filtering with five basic filter types)
 */
bool PNG_chunk_IHDR_check_filter_method(struct PNG_file * file,
					struct PNG_frame * frame)
{
	file->filter_method = (int)frame->data[11];
	return file->filter_method == 0;
}

/**
 * Accepted values: 0 (no interlace) or 1 (Adam7 interlace)
 */
bool PNG_chunk_IHDR_check_interlace_method(struct PNG_file * file,
					   struct PNG_frame * frame)
{
	file->interlace_method = (int)frame->data[12];
	return file->interlace_method == 0 || file->interlace_method == 1;
}
