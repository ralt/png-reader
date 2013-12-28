#include "png-file.h"

void PNG_file_import(struct PNG_file *file, uint8_t * content, size_t size)
{
	//Import headers.
	for (size_t i = 0; i < PNG_headers_size; i++) {
		file->headers[i] = content[i];
	}

	if (!PNG_file_check_headers(file)) {
		printf("The file %s is not a PNG file.\n", file->name);
		exit(EXIT_FAILURE);
	}


	//Import chunks.

	// @TODO Calculate the average number of PNG chunks according to the
	// number of bytes if possible
	file->chunks = malloc(sizeof(struct PNG_chunk_vector));
	if (file->chunks == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	PNG_chunk_vector_init(file->chunks, 50);

	PNG_build_chunks(file->chunks, content, size, PNG_headers_size);
}

void PNG_file_free(struct PNG_file *file)
{
	PNG_chunk_vector_free(file->chunks);
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
 * The IHDR chunk must be the first chunk. It contains:
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
	struct PNG_chunk *IHDR_chunk = PNG_chunk_vector_get(file->chunks, 0);

	if (PNG_chunk_IHDR_check_type(IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_set_dimensions(file, IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_bit_depth_color_type(file, IHDR_chunk) ==
	    false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_compression_method(file, IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_filter_method(file, IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_interlace_method(file, IHDR_chunk) == false) {
		return false;
	}

	return true;
}

/**
 * There must be one or multiple IDAT chunks.
 */
bool PNG_file_check_IDAT(struct PNG_file * file)
{
	uint8_t const defaults[] = { 0x49, 0x44, 0x41, 0x54 };
	for (size_t i = 0; i < file->chunks->size; i++) {
		bool check = true;
		for (size_t j = 0; j < PNG_header_type_size; j++) {
			if (defaults[j] != PNG_chunk_vector_get(file->chunks, i)->type[j]) {
				check = false;
			}
		}

		if (check == true) {
			return true;
		}
	}

	return false;
}

/**
 * The IEND chunk must be the last chunk and its length must be 0.
 */
bool PNG_file_check_IEND(struct PNG_file * file)
{
	struct PNG_chunk *IEND_chunk =
	    PNG_chunk_vector_get(file->chunks, file->chunks->size - 1);

	uint8_t const defaults[] = { 0x49, 0x45, 0x4e, 0x44 };
	for (size_t i = 0; i < PNG_header_type_size; i++) {
		if (defaults[i] != IEND_chunk->type[i]) {
			return false;
		}
	}

	if (PNG_chunk_length(IEND_chunk) != 0) {
		return false;
	}

	return true;
}
