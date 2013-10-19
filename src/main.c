#include "main.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    uint8_t buffer[buffer_size];
    size_t bytes_read = 0;
    bool headers_read = false;
    size_t full_bytes_read = 0;
    PNG_frame_vector frames;
    PNG_frame_vector_init(&frames, 100);

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
            headers_read = true;
            read_headers(buffer);
        }
        else
        {
            full_bytes_read = PNG_build_frames(full_bytes_read,
                    &frames, buffer);

            PNG_frame *frame = PNG_frame_vector_get(&frames, 0);
            int length = (int) frame->length[0] << 24 |
                (int) frame->length[1] << 16 |
                (int) frame->length[2] << 8 |
                (int) frame->length[3];
            printf("Frame 0 length: %d\n", length);
        }
    } while (!feof(fp));

    fclose(fp);

    return 0;
}

void
read_headers(uint8_t buffer[buffer_size])
{
    if (!PNG_read_headers(buffer))
    {
        printf("The headers do not match a PNG file\n");
        exit(1);
    }
    else
    {
        printf("The headers match!\n");
    }
}
