#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#ifndef PNG_FILE
#define PNG_FILE

#include "png-chunk.h"
#include "png-chunk-ihdr.h"
#include "png-chunk-plte.h"
#include "png-chunk-idat.h"
#include "png-chunk-iend.h"

/**
 * Defines a single PNG file.
 */
struct PNG_file {
	char *name; // filename

	uint8_t headers[PNG_headers_size]; // PNG headers

	struct PNG_chunk_vector *chunks; // raw chunks

	// critical chunks
	struct PNG_IHDR_chunk *IHDR_chunk;
	struct PNG_PLTE_chunk *PLTE_chunk;
	struct PNG_IDAT_chunks *IDAT_chunks;
	struct PNG_IEND_chunk *IEND_chunk;

	// ancillary chunks

	// before PLTE and IDAT
	struct PNG_cHRM_chunk *cHRM_chunk;
	struct PNG_gAMA_chunk *gAMA_chunk;
	struct PNG_iCCP_chunk *iCCP_chunk;
	struct PNG_sBIT_chunk *sBIT_chunk;
	struct PNG_sRGB_chunk *sRGB_chunk;

	// after PLTE, before IDAT
	struct PNG_bKGD_chunk *bKGD_chunk;
	struct PNG_hIST_chunk *hIST_chunk;
	struct PNG_tRNS_chunk *tRNS_chunk;

	// before IDAT
	struct PNG_pHYs_chunk *pHYs_chunk;
	struct PNG_sPLT_chunks *sPLT_chunks;

	// no order
	struct PNG_tIME_chunk *tIME_chunk;
	struct PNG_iTXt_chunks *iTXt_chunks;
	struct PNG_tEXt_chunks *tEXt_chunks;
	struct PNG_xTXt_chunks *xTXt_chunks;
};

#include "png-chunk-vector.h"
#include "png-chunk-builder.h"

/**
 * Imports a PNG file contents in struct PNG_file struct.
 */
void PNG_file_import(struct PNG_file *file, uint8_t * content, size_t size);

/**
 * Frees a struct PNG_file struct.
 */
void PNG_file_free(struct PNG_file *file);

/**
 * Checks that all critical chunks of a PNG file are correctly implemented.
 */
bool PNG_file_check_critical_chunks(struct PNG_file *file);

/**
 * Checks the headers of the PNG file.
 */
bool PNG_file_check_headers(struct PNG_file *file);

/**
 * Checks that the IHDR chunk is correct.
 */
bool PNG_file_check_IHDR(struct PNG_file *file);

/**
 * Checks that the PLTE chunk is correct.
 */
bool PNG_file_check_PLTE(struct PNG_file *file);

/**
 * Checks that the IDAT chunk is correct.
 */
bool PNG_file_check_IDAT(struct PNG_file *file);

/**
 * Checks that the IEND chunk is correct.
 */
bool PNG_file_check_IEND(struct PNG_file *file);

#endif
