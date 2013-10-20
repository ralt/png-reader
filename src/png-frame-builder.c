#include "png-frame-builder.h"

size_t
PNG_build_frames(size_t full_bytes_read, PNG_frame_vector *frames,
        uint8_t buffer[buffer_size])
{
    if (full_bytes_read >= 0 && full_bytes_read < 8)
    {
        PNG_add_headers(frames, buffer, full_bytes_read, 0);
    }

    full_bytes_read += buffer_size;

    PNG_frame *last_frame = PNG_frame_vector_get(frames,
            frames->size - 1);

    signed int bytes_left =
        PNG_frame_length(last_frame) -
        (full_bytes_read - PNG_headers_size - PNG_crc_size);

    printf("bytes left in build: %d\n", bytes_left);
    printf("fbr in build: %d\n", full_bytes_read);
    printf("length: %d\n", PNG_frame_length(last_frame));

    if (bytes_left == 0 && PNG_frame_length(last_frame) == 0)
    {
        return 0;
    }

    PNG_add_data(frames, buffer, bytes_left);

    if (bytes_left < 0)
    {
        printf("return is : %d\n", -bytes_left);
        PNG_add_headers(frames, buffer, 0, buffer_size + bytes_left - 1);
        return -bytes_left;
    }

    return full_bytes_read;
}

/**
 * full_bytes_read lets us know if a header is already
 * started or not.
 * buffer_offset lets us know if a buffer is already
 * started or not.
 */
void
PNG_add_headers(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], size_t full_bytes_read,
        size_t buffer_offset)
{
    printf("fbr in headers: %d\n", full_bytes_read);
    printf("buffer offset: %d\n", buffer_offset);
    PNG_frame *frame;
    if (full_bytes_read == 0)
    {
        frame = malloc(sizeof(PNG_frame));
        PNG_frame_vector_append(frames, frame);
    }
    else
    {
        frame = PNG_frame_vector_get(frames, frames->size - 1);
    }
    int i;

    if (full_bytes_read < 4)
    {
        if (buffer_offset < 4)
        {
            for (i = full_bytes_read; i < 4; i++)
            {
                frame->length[i] =
                    buffer[i - full_bytes_read + buffer_offset];
            }
        }

        for (i = 4; i < 8; i++)
        {
            if ((i + buffer_offset) < buffer_size)
            {
                frame->type[i - 4] = buffer[i + buffer_offset];
            }
        }
    }
    else
    {
        for (i = full_bytes_read; i < 8; i++)
        {
            frame->type[i] = buffer[i - full_bytes_read];
        }
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
}

void
PNG_add_data(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], signed int bytes_left)
{
    printf(".\n");
}
