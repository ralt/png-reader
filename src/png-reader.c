#include "png-reader.h"

void
PNG_read_headers(uint8_t headers[PNG_HEADERS_SIZE])
{
    int i;
    printf("0x");
    for (i = 0; i < sizeof(headers); i++)
    {
        printf("%02x", headers[i]);
    }
    printf("\n");
}
