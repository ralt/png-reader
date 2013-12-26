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

    char *content;
    if ((content = (char*) malloc(fsize + 1)) == NULL)
        goto fatal_error;

    size_t bytes_read;
    bytes_read = fread(content, sizeof(uint8_t), fsize, fp);

    if (bytes_read < fsize && ferror(fp))
        goto fatal_error;

    content[fsize] = 0;

    int i = 0;
    uint8_t byte;
    while ((byte = (uint8_t) content[i])) {
        printf("0x%02x\n", byte);
        i++;
    }

    if (fclose(fp) == EOF)
        goto fatal_error;

    exit(EXIT_SUCCESS);

fatal_error:
    printf("%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}
