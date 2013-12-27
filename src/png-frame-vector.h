#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "png-frame.h"

#ifndef PNG_FRAME_VECTOR
#define PNG_FRAME_VECTOR

typedef struct
{
    size_t size;
    int capacity;
    PNG_frame **frames;
} PNG_frame_vector;

#endif

/**
 * Initializes the memory for a vector of frames with defined capacity.
 */
void PNG_frame_vector_init(PNG_frame_vector *vector, int capacity);

/**
 * Appends a PNG_frame on the vector. If needed, it reallocates memory.
 */
void PNG_frame_vector_append(PNG_frame_vector *vector, PNG_frame *frame);

/**
 * Returns the PNG_frame at index.
 */
PNG_frame* PNG_frame_vector_get(PNG_frame_vector *vector, int index);

/**
 * Defines the PNG_frame stored at index.
 */
void PNG_frame_vector_set(PNG_frame_vector *vector, int index,
        PNG_frame *value);

/**
 * Frees the memory for the vector.
 */
void PNG_frame_vector_free(PNG_frame_vector *vector);
