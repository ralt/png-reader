#include "png-reader.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read = 0;

    if (!argv[1])
    {
        printf("png-reader needs at least one argument\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    do {
        bytes_read = read_bytes(fp, &buffer);
        if (bytes_read > 0) {
            printf("0x%02x%02x%02x%02x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        }
    } while (!feof(fp));

    fclose(fp);
    return 0;
}

size_t read_bytes(FILE *fp, uint8_t *buffer[BUFFER_SIZE])
{
    size_t bytes_read = 0;
    size_t size = 1;

    bytes_read = fread(buffer, size, BUFFER_SIZE, fp);

    if (bytes_read < size && ferror(fp)) {
        printf("An error happened during file reading.\n");
        exit(1);
    }

    return bytes_read;
}
