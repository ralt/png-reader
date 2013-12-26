#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("png-reader needs at least one argument\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *content = NULL;
    long fsize = read_file(argv[1], &content);

    for (size_t i = 0; i < fsize; i++) {
        printf("0x%02x\n", content[i]);
    }

    exit(EXIT_SUCCESS);
}

long read_file(char *fname, uint8_t **content)
{
    FILE *fp;
    fp = fopen(fname, "rb");
    if (fp == NULL)
        goto fatal_error;

    long fsize;
    if (fseek(fp, 0, SEEK_END) == -1)
        goto fatal_error;

    if ((fsize = ftell(fp)) == -1)
        goto fatal_error;

    if (fseek(fp, 0, SEEK_SET) == -1)
        goto fatal_error;

    if ((*content = (uint8_t*) malloc(fsize)) == NULL)
        goto fatal_error;

    size_t bytes_read;
    bytes_read = fread(*content, 1, fsize, fp);

    if (bytes_read < fsize && ferror(fp))
        goto fatal_error;

    if (fclose(fp) == EOF)
        goto fatal_error;

    return fsize;

fatal_error:
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}
