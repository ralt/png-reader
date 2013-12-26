#include <stdio.h> // printf, FILE*
#include <stdlib.h> // exit
#include <stdint.h> // uint8_t
#include <inttypes.h> // PRIu8
#include <string.h>
#include <errno.h>

#include "png-frame-vector.h"
#include "png-frame.h"
#include "png-frame-builder.h"
#include "png-headers.h"

extern size_t const PNG_headers_size;

/**
 * Reads fname and puts its bytes in content.
 */
long read_file(char *fname, uint8_t **content);
