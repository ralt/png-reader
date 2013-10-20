#include "byte.h"

void
read_bytes(FILE *fp, uint8_t buffer[buffer_size])
{
    size_t bytes_read = 0;
    size_t size = 1;

    bytes_read = fread(buffer, size, buffer_size, fp);

    if (bytes_read < size && ferror(fp))
    {
        printf("An error happened during file reading.\n");
        exit(1);
    }

    return bytes_read;
}
