#include "png-reader.h"

bool
PNG_read_headers(uint8_t headers[PNG_HEADERS_SIZE])
{
    uint8_t defaults[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a ,0x0a };
    for (int i = 0; i < PNG_HEADERS_SIZE; i++)
    {
        if (headers[i] != defaults[i])
        {
            return false;
        }
    }
    return true;
}
