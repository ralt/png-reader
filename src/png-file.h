#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#ifndef PNG_FILE
#define PNG_FILE

#include "png-chunk.h"

/**
 * Defines a single PNG file.
 */
struct PNG_file {
	char *name;
	uint8_t headers[PNG_headers_size];
	struct PNG_chunk_vector *chunks;
	struct PNG_IHDR_chunk *IHDR_chunk;
};

#include "png-chunk-vector.h"
#include "png-chunk-builder.h"
#include "png-chunk-ihdr.h"
#include "png-chunk-plte.h"
#include "png-chunk-idat.h"
#include "png-chunk-iend.h"

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
