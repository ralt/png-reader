#include <stdio.h> // printf, FILE*
#include <stdlib.h> // exit
#include <stdint.h> // uint8_t
#include <inttypes.h> // PRIu8
#include <string.h>
#include <errno.h>

#include "png-file.h"

/**
 * Reads fname and puts its bytes in content.
 */
size_t read_file(char *fname, uint8_t **content);
