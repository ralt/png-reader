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
