#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("png-reader needs at least one argument\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    fp = fopen(argv[1], "rb");
    if (fp == NULL)
        goto fatal_error;

    long fsize;
    if (fseek(fp, 0, SEEK_END) == -1)
        goto fatal_error;

    if ((fsize = ftell(fp)) == -1)
        goto fatal_error;

    if (fseek(fp, 0, SEEK_SET) == -1)
        goto fatal_error;

    uint8_t *content;
    if ((content = (uint8_t*) malloc(fsize)) == NULL)
        goto fatal_error;

    size_t bytes_read;
    bytes_read = fread(content, 1, fsize, fp);

    if (bytes_read < fsize && ferror(fp))
        goto fatal_error;

    for (size_t i = 0; i < fsize; i++) {
        printf("0x%02x\n", content[i]);
    }

    if (fclose(fp) == EOF)
        goto fatal_error;

    exit(EXIT_SUCCESS);

fatal_error:
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}
