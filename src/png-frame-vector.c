#include "png-frame-vector.h"

void PNG_frame_vector_init(struct PNG_frame_vector *vector, int capacity)
{
    vector->size = 0;
    vector->capacity = capacity;
    vector->frames = malloc(sizeof(PNG_frame) * vector->capacity);
    if (vector->frames == NULL) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (vector->frames == NULL) {
        exit(errno);
    }
}

void PNG_frame_vector_append(struct PNG_frame_vector *vector, PNG_frame *frame)
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

PNG_frame* PNG_frame_vector_get(struct PNG_frame_vector *vector, int index)
{
    if (index < 0 || index >= vector->size) {
        printf("Out of bounds\n");
        exit(1);
    }

    return vector->frames[index];
}

void PNG_frame_vector_set(struct PNG_frame_vector *vector, int index,
        PNG_frame *value)
{
    vector->frames[index] = value;
}

void PNG_frame_vector_free(struct PNG_frame_vector *vector)
{
    for (size_t i = 0; i < vector->size; i++) {
        PNG_frame_free(PNG_frame_vector_get(vector, i));
    }
    free(vector);
}
