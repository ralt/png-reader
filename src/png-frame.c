#include "png-frame.h"

size_t PNG_frame_length(PNG_frame *frame)
{
    return (size_t) ((uint32_t) frame->length[0] << 24 |
        (uint32_t) frame->length[1] << 16 |
        (uint32_t) frame->length[2] << 8 |
        (uint32_t) frame->length[3]);
}

size_t PNG_frame_type(PNG_frame *frame, unsigned char type[4])
{
    for (int i = 0; i < sizeof(type); i++) {
        type[i] = frame->type[i];
    }

    return sizeof(type);
}
