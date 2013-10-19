#include "png-reader.h"

bool
PNG_read_headers(uint8_t headers[PNG_headers_size])
{
    // PNG headers
    uint8_t const defaults[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a ,0x0a };
    for (int i = 0; i < PNG_headers_size; i++)
    {
        if (headers[i] != defaults[i])
        {
            return false;
        }
    }
    return true;
}

size_t
PNG_build_frames(size_t full_bytes_read, PNG_frame_vector *frames,
        uint8_t buffer[buffer_size])
{
    if (full_bytes_read == 0)
    {
        PNG_add_headers(frames, buffer);
    }
    return full_bytes_read;
}

void
PNG_add_headers(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size])
{
    PNG_frame *frame = malloc(sizeof(PNG_frame));
    int i;

    for (i = 0; i < 4; i++)
    {
        frame->length[i] = buffer[i];
    }

    for (i = 4; i < 8; i++)
    {
        frame->type[i] = buffer[i];
    }

    PNG_frame_vector_append(frames, frame);
}
