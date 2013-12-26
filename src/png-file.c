#include "png-file.h"

void PNG_file_import(PNG_file *file, uint8_t *content, size_t size)
{
    // Import headers.
    for (size_t i = 0; i < PNG_headers_size; i++) {
        file->headers[i] = content[i];
    }

    // Import frames.

    // @TODO Calculate the average number of PNG frames according to the
    // number of bytes.
    PNG_frame_vector_init(&file->frames, 50);

    PNG_build_frames(&file->frames, content, size, PNG_headers_size);
}

void PNG_file_free(PNG_file *file)
{
    PNG_frame_vector_free(&file->frames);
}

bool PNG_file_check_critical_chunks(PNG_file *file)
{
    return true;
}

bool PNG_file_check_headers(PNG_file *file)
{
    // PNG headers
    uint8_t const defaults[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a,
        0x0a };
    for (int i = 0; i < PNG_headers_size; i++) {
        if (file->headers[i] != defaults[i]) {
            return false;
        }
    }
    return true;
}
