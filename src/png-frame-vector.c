#include "png-frame-vector.h"

void PNG_frame_vector_init(PNG_frame_vector *vector, int capacity)
{
    vector->size = 0;
    vector->capacity = capacity;
    vector->frames = malloc(sizeof(PNG_frame) * vector->capacity);

    if (vector->frames == NULL) {
        exit(errno);
    }
}

void PNG_frame_vector_append(PNG_frame_vector *vector, PNG_frame *frame)
{
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->frames = realloc(vector->frames,
                sizeof(PNG_frame) * vector->capacity);
        if (vector->frames == NULL) {
            exit(errno);
        }
    }

    vector->frames[vector->size++] = frame;
}

PNG_frame* PNG_frame_vector_get(PNG_frame_vector *vector, int index)
{
    if (index < 0 || index >= vector->size) {
        printf("Out of bounds\n");
        exit(1);
    }

    return vector->frames[index];
}

void PNG_frame_vector_set(PNG_frame_vector *vector, int index,
        PNG_frame *value)
{
    vector->frames[index] = value;
}

void PNG_frame_vector_free(PNG_frame_vector *vector)
{
    // All frames are allocated on the stack, so no need to free them.
    free(vector->frames);
}
