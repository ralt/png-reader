#include "png-file.h"

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
