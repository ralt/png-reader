#include "png-file.h"

void PNG_file_import(struct PNG_file *file, uint8_t * content, size_t size)
{
	//Import headers.
	for (size_t i = 0; i < PNG_headers_size; i++) {
		file->headers[i] = content[i];
	}

	//Import frames.

	// @TODO Calculate the average number of PNG frames according to the
	// number of bytes if possible
	file->frames = malloc(sizeof(struct PNG_frame_vector));
	if (file->frames == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	PNG_frame_vector_init(file->frames, 50);

	PNG_build_frames(file->frames, content, size, PNG_headers_size);
}

void PNG_file_free(struct PNG_file *file)
{
	PNG_frame_vector_free(file->frames);
	free(file);
}

bool PNG_file_check_critical_chunks(struct PNG_file *file)
{
	if (PNG_file_check_IHDR(file) == false)
		return false;

	if (PNG_file_check_IDAT(file) == false)
		return false;

	if (PNG_file_check_IEND(file) == false)
		return false;

	return true;
}

bool PNG_file_check_headers(struct PNG_file * file)
{
	//PNG headers
	uint8_t const defaults[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a,
		0x0a
	};
	for (int i = 0; i < PNG_headers_size; i++) {
		if (file->headers[i] != defaults[i]) {
			return false;
		}
	}
	return true;
}

/**
 * The IHDR chunk must be the first frame. It contains:
 *   - Width: 4 bytes
 *   - Height: 4 bytes
 *   - Bit depth: 1 byte
 *   - Color type: 1 byte
 *   - Compression method: 1 byte
 *   - Filter method: 1 byte
 *   - Interlace method: 1 byte
 *
 * @see http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR
 */
bool PNG_file_check_IHDR(struct PNG_file * file)
{
	struct PNG_frame *IHDR_frame = PNG_frame_vector_get(file->frames, 0);

	if (PNG_chunk_IHDR_check_type(IHDR_frame) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_set_dimensions(file, IHDR_frame) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_bit_depth_color_type(file, IHDR_frame) ==
	    false) {
		return false;
	}

	return true;
}

bool PNG_file_check_IDAT(struct PNG_file * file)
{
	return true;
}

bool PNG_file_check_IEND(struct PNG_file * file)
{
	return true;
}
