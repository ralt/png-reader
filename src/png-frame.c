#include "png-frame.h"

size_t PNG_frame_length(PNG_frame *frame)
{
    return (size_t) ((uint32_t) frame->length[0] << 24 |
        (uint32_t) frame->length[1] << 16 |
        (uint32_t) frame->length[2] << 8 |
        (uint32_t) frame->length[3]);
}
