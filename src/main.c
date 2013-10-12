#include "main.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read = 0;
    size_t full_bytes_read = 0;
    uint8_t headers[PNG_HEADERS_SIZE];
    bool headers_read = false;

    if (argc < 2)
    {
        printf("png-reader needs at least one argument\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        exit(1);
    }

    do
    {
        bytes_read = read_bytes(fp, buffer);

        if (!headers_read)
        {
            add_bytes(headers, buffer, full_bytes_read);

            full_bytes_read += bytes_read;
            if (full_bytes_read == PNG_HEADERS_SIZE)
            {
                PNG_read_headers(headers);
                headers_read = true;
            }
        }

    } while (!feof(fp));

    fclose(fp);
    return 0;
}

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
