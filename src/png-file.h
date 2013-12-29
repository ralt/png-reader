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
#include "png-chunk-chrm.h"
#include "png-chunk-gama.h"
#include "png-chunk-iccp.h"
#include "png-chunk-sbit.h"
#include "png-chunk-srgb.h"
#include "png-chunk-bkgd.h"
#include "png-chunk-hist.h"
#include "png-chunk-trns.h"
#include "png-chunk-phys.h"
#include "png-chunk-splt.h"
#include "png-chunk-time.h"
#include "png-chunk-itxt.h"
#include "png-chunk-text.h"
#include "png-chunk-xtxt.h"

/**
 * Defines a single PNG file.
 */
struct PNG_file {
	char *name;		// filename

	uint8_t headers[PNG_headers_size];	// PNG headers

	struct PNG_chunk_vector *chunks;	// raw chunks

	// critical chunks
	struct PNG_chunk_IHDR *IHDR_chunk;
	struct PNG_chunk_PLTE *PLTE_chunk;
	struct PNG_chunk_IDAT_vector *IDAT_chunks;
	struct PNG_chunk_IEND *IEND_chunk;

	// ancillary chunks

	// before PLTE and IDAT
	struct PNG_chunk_cHRM *cHRM_chunk;
	struct PNG_chunk_gAMA *gAMA_chunk;
	struct PNG_chunk_iCCP *iCCP_chunk;
	struct PNG_chunk_sBIT *sBIT_chunk;
	struct PNG_chunk_sRGB *sRGB_chunk;

	// after PLTE, before IDAT
	struct PNG_chunk_bKGD *bKGD_chunk;
	struct PNG_chunk_hIST *hIST_chunk;
	struct PNG_chunk_tRNS *tRNS_chunk;

	// before IDAT
	struct PNG_chunk_pHYs *pHYs_chunk;
	struct PNG_chunk_sPLT_vector *sPLT_chunks;

	// no order
	struct PNG_chunk_tIME *tIME_chunk;
	struct PNG_chunk_iTXt_vector *iTXt_chunks;
	struct PNG_chunk_tEXt_vector *tEXt_chunks;
	struct PNG_chunk_xTXt_vector *xTXt_chunks;
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
