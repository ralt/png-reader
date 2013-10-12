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
                headers_read = true;
                bool valid = PNG_read_headers(headers);
                if (!valid)
                {
                    printf("The headers do not match a PNG file\n");
                    exit(1);
                }
                else
                {
                    printf("The headers match!\n");
                }
            }
        }

    } while (!feof(fp));

    fclose(fp);
    return 0;
}
