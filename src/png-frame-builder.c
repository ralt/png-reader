#include "png-frame-builder.h"

void PNG_build_frames(PNG_frame_vector *frames, uint8_t *content, size_t size,
        int cursor)
{
    PNG_frame *frame = malloc(sizeof(PNG_frame));
    for (size_t i = 0; i < PNG_header_length_size; i++) {
        frame->length[i] = content[cursor + i];
    }

    PNG_build_frame(content, frame, cursor);
    PNG_frame_vector_append(frames, frame);

    cursor += PNG_header_length_size + PNG_header_type_size +
        PNG_header_crc_size + PNG_frame_length(frame);

    if (cursor < size) {
        PNG_build_frames(frames, content, size, cursor);
    }
}

void PNG_build_frame(uint8_t *content, PNG_frame *frame, int cursor)
{
    size_t frame_length = PNG_frame_length(frame);
    for (size_t i = 0; i < PNG_header_type_size; i++) {
        frame->type[i] = content[cursor + PNG_header_length_size + i];
    }

    frame->data = malloc(sizeof(uint8_t) * frame_length);

    for (size_t i = 0; i < frame_length; i++) {
        frame->data[i] = content[cursor + PNG_header_length_size +
            PNG_header_type_size + i];
    }

    for (size_t i = 0; i < PNG_header_crc_size; i++) {
        frame->crc[i] = content[cursor + PNG_header_length_size +
            PNG_header_type_size + frame_length + i];
    }
}
