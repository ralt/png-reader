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

	file->chunks = malloc(sizeof(struct PNG_chunk_vector));
	if (file->chunks == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// @TODO Calculate the average number of PNG chunks according to the
	// number of bytes if possible
	PNG_chunk_vector_init(file->chunks, 50);

	PNG_build_chunks(file->chunks, content, size, PNG_headers_size);

	PNG_build_semantic_chunks(file);

	if (!PNG_file_check_critical_chunks(file)) {
		printf("Critical chunks not OK.\n");
		exit(EXIT_FAILURE);
	}
}

void PNG_file_free(struct PNG_file *file)
{
	PNG_chunk_vector_free(file->chunks);

	free(file->IHDR_chunk);
	free(file->PLTE_chunk);
	PNG_chunk_IDAT_vector_free(file->IDAT_chunks);
	free(file->IEND_chunk);

	free(file->cHRM_chunk);
	free(file->gAMA_chunk);
	free(file->iCCP_chunk);
	free(file->sBIT_chunk);
	free(file->sRGB_chunk);

	free(file->bKGD_chunk);
	free(file->hIST_chunk);
	free(file->tRNS_chunk);

	free(file->pHYs_chunk);
	PNG_chunk_sPLT_vector_free(file->sPLT_chunks);

	free(file->tIME_chunk);
	PNG_chunk_iTXt_vector_free(file->iTXt_chunks);
	PNG_chunk_tEXt_vector_free(file->tEXt_chunks);
	PNG_chunk_xTXt_vector_free(file->xTXt_chunks);

	free(file);
}

bool PNG_file_check_critical_chunks(struct PNG_file *file)
{
	if (PNG_file_check_IHDR(file) == false)
		return false;

	if (PNG_file_check_PLTE(file) == false)
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
	// If we're sure that the chunk is IHDR, we can safely create it
	file->IHDR_chunk = malloc(sizeof(struct PNG_IHDR_chunk));
	if (file->IHDR_chunk == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (PNG_chunk_IHDR_set_dimensions(file->IHDR_chunk, IHDR_chunk) ==
	    false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_bit_depth_color_type
	    (file->IHDR_chunk, IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_compression_method
	    (file->IHDR_chunk, IHDR_chunk) == false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_filter_method(file->IHDR_chunk, IHDR_chunk) ==
	    false) {
		return false;
	}

	if (PNG_chunk_IHDR_check_interlace_method(file->IHDR_chunk, IHDR_chunk)
	    == false) {
		return false;
	}
	// We must also check that there is only one IHDR chunk.
	for (size_t i = 1; i < file->chunks->size; i++) {
		if (PNG_chunk_IHDR_check_type
		    (PNG_chunk_vector_get(file->chunks, i)) == true) {
			return false;
		}
	}

	return true;
}

/**
 * A PLTE chunk is not required. However, if it is present, it must be before
 * any IDAT chunk.
 */
bool PNG_file_check_PLTE(struct PNG_file * file)
{
	for (size_t i = 1; i < file->chunks->size - 1; i++) {
		if (PNG_chunk_PLTE_check_type
		    (PNG_chunk_vector_get(file->chunks, i)) == true) {
			// @TODO check that it's before any IDAT chunk.
			return false;
		}
	}
	return true;
}

/**
 * There must be one or multiple IDAT chunks.
 */
bool PNG_file_check_IDAT(struct PNG_file * file)
{
	// The IDAT chunk can't be the 1st or the last.
	for (size_t i = 1; i < file->chunks->size - 1; i++) {
		if (PNG_chunk_IDAT_check_type
		    (PNG_chunk_vector_get(file->chunks, i)) == true) {
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

	if (PNG_chunk_IEND_check_type(IEND_chunk) == false) {
		return false;
	}

	if (PNG_chunk_length(IEND_chunk) != 0) {
		return false;
	}
	// Thy shalt be one!
	for (size_t i = 0; i < file->chunks->size - 1; i++) {
		if (PNG_chunk_IEND_check_type
		    (PNG_chunk_vector_get(file->chunks, i)) == true) {
			return false;
		}
	}

	return true;
}
