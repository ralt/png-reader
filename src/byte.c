#include "byte.h"

size_t
read_bytes(FILE *fp, uint8_t buffer[BUFFER_SIZE])
{
    size_t bytes_read = 0;
    size_t size = 1;

    bytes_read = fread(buffer, size, BUFFER_SIZE, fp);

    if (bytes_read < size && ferror(fp))
    {
        printf("An error happened during file reading.\n");
        exit(1);
    }

    return bytes_read;
}

void
add_bytes(uint8_t headers[PNG_HEADERS_SIZE], uint8_t buffer[BUFFER_SIZE],
        size_t bytes_read)
{
    for (size_t i = bytes_read; i < BUFFER_SIZE + bytes_read; i++)
    {
        headers[i] = buffer[i - bytes_read];
    }
}
