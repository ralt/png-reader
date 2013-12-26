#include "png-frame-builder.h"

void PNG_build_frames(PNG_frame_vector *frames, uint8_t **content, long fsize,
        int cursor)
{
    PNG_frame frame;
    for (size_t i = 0; i < PNG_header_length_size; i++) {
        frame.length[i] = *content[cursor + i];
    }

    PNG_build_frame(content, &frame, cursor);
    PNG_frame_vector_append(frames, &frame);

    cursor += PNG_header_length_size + PNG_header_type_size +
        PNG_header_crc_size + PNG_frame_length(&frame);

    if (cursor <= fsize) {
        PNG_build_frames(frames, content, fsize, cursor);
    }
}

void PNG_build_frame(uint8_t **content, PNG_frame *frame, int cursor)
{
    size_t frame_length = PNG_frame_length(frame);
    for (size_t i = 0; i < PNG_header_type_size; i++) {
        frame->type[i] = *content[cursor + PNG_header_length_size + i];
    }

    frame->data = malloc(frame_length);

    for (size_t i = 0; i < frame_length; i++) {
        frame->data[i] = *content[cursor + PNG_header_length_size +
            PNG_header_type_size + i];
    }

    for (size_t i = 0; i < PNG_header_crc_size; i++) {
        frame->crc[i] = *content[cursor + PNG_header_length_size +
            PNG_header_type_size + frame_length + i];
    }
}

/*
size_t PNG_build_frames(size_t full_bytes_read, PNG_frame_vector *frames,
        uint8_t buffer[buffer_size])
{
    if (full_bytes_read >= 0 && full_bytes_read < 8) {
        PNG_add_headers(frames, buffer, full_bytes_read, 0);
    }

    full_bytes_read += buffer_size;

    PNG_frame *last_frame = PNG_frame_vector_get(frames,
            frames->size - 1);

    signed int bytes_left =
        PNG_frame_length(last_frame) -
        (full_bytes_read - PNG_headers_size - PNG_crc_size);

    if (bytes_left == 0 && PNG_frame_length(last_frame) == 0) {
        return 0;
    }

    PNG_add_data(frames, buffer, bytes_left);

    if (bytes_left < 0) {
        printf("return is : %d\n", -bytes_left);
        PNG_add_headers(frames, buffer, 0, buffer_size + bytes_left);
        return -bytes_left;
    }

    return full_bytes_read;
}
*/

/**
 * full_bytes_read lets us know if a header is already
 * started or not.
 * buffer_offset lets us know if a buffer is already
 * started or not.
 */
void PNG_add_headers(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], size_t full_bytes_read,
        size_t buffer_offset)
{
    PNG_frame *frame;
    int i;

    if (full_bytes_read == 0) {
        frame = malloc(sizeof(PNG_frame));
        if (frame == NULL) {
            exit(errno);
        }

        PNG_frame_vector_append(frames, frame);
    }
    else {
        frame = PNG_frame_vector_get(frames, frames->size - 1);
    }

    if (full_bytes_read < 4 && buffer_offset < 4) {
        for (i = buffer_offset; i < 4; i++) {
            frame->length[i] =
                buffer[i - full_bytes_read + buffer_offset];
        }
    }

    if (full_bytes_read < 4) {
        for (i = 4; i < 8; i++) {
            if ((i + buffer_offset) < buffer_size) {
                frame->type[i - 4] = buffer[i + buffer_offset];
            }
        }
    }
    else {
        for (i = full_bytes_read; i < 8; i++) {
            frame->type[i] = buffer[i - full_bytes_read + buffer_offset];
        }
    }

    {
        printf("Frame %d type : ", (int) frames->size);
        unsigned char type[4];
        PNG_frame_type(frame, type);
        for (i = 0; i < 4; i++)
        {
            printf("%c", type[i]);
        }
        printf("\n");

        printf("Frame %d length : %d\n", (int) frames->size,
                (int) PNG_frame_length(frame));
    }
}

void PNG_add_data(PNG_frame_vector *frames,
        uint8_t buffer[buffer_size], signed int bytes_left)
{
    printf(".");
}
