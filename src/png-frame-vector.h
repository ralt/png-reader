#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "png-frame.h"

void
PNG_frame_vector_init(PNG_frame_vector *vector, int capacity);

void
PNG_frame_vector_append(PNG_frame_vector *vector, PNG_frame *frame);

PNG_frame*
PNG_frame_vector_get(PNG_frame_vector *vector, int index);

void
PNG_frame_vector_set(PNG_frame_vector *vector, int index,
        PNG_frame *value);

void
PNG_frame_vector_free(PNG_frame_vector *vector);
