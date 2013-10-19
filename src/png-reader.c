#include "png-reader.h"

bool
PNG_read_headers(uint8_t headers[PNG_headers_size])
{
    // PNG headers
    uint8_t const defaults[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a,
        0x0a };
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
    // Headers of a new frame
    if (full_bytes_read == 0)
    {
        PNG_add_headers(frames, buffer);
        return PNG_headers_size;
    }

    full_bytes_read += buffer_size;

    PNG_frame *last_frame = PNG_frame_vector_get(frames,
            frames->size - 1);

    int bytes_left = PNG_frame_length(last_frame) - full_bytes_read;

    PNG_add_data(frames, buffer, bytes_left);

    if (bytes_left == 0)
    {
        return 0;
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
        frame->type[i - 4] = buffer[i];
    }

    {
        printf("Frame %d type : ", frames->size);
        unsigned char type[4];
        PNG_frame_type(frame, type);
        for (i = 0; i < 4; i++)
        {
            printf("%c", type[i]);
        }
        printf("\n");

        printf("Frame %d length : %d\n", frames->size,
                PNG_frame_length(frame));
    }

    PNG_frame_vector_append(frames, frame);
}

void
PNG_add_data(PNG_frame_vector *vector,
        uint8_t buffer[buffer_size], size_t bytes_left)
{
    printf(".");
}

int
PNG_frame_length(PNG_frame *frame)
{
    return (int) frame->length[0] << 24 |
        (int) frame->length[1] << 16 |
        (int) frame->length[2] << 8 |
        (int) frame->length[3];
}

size_t
PNG_frame_type(PNG_frame *frame, unsigned char type[4])
{
    for (int i = 0; i < sizeof(type); i++)
    {
        type[i] = frame->type[i];
    }

    return sizeof(type);
}
