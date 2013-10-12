#include "png-reader.h"

void
PNG_read_headers(uint8_t headers[PNG_HEADERS_SIZE])
{
    int i;
    printf("headers: 0x");
    for (i = 0; i < PNG_HEADERS_SIZE; i++)
    {
        printf("%02x", headers[i]);
    }
    printf("\n");
}
