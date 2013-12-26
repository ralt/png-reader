#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("png-reader needs at least one argument\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *content = NULL;
    long fsize = read_file(argv[1], &content);

    uint8_t headers[PNG_headers_size];
    for (size_t i = 0; i < PNG_headers_size; i++) {
        headers[i] = content[i];
    }

    if (!PNG_read_headers(headers)) {
        free(content);
        printf("The file %s is not a PNG file.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // @TODO Calculate the average number of PNG frames according to the
    // number of bytes.
    PNG_frame_vector frames;
    PNG_frame_vector_init(&frames, 50);

    PNG_build_frames(&frames, &content, fsize, PNG_headers_size);

    for (size_t i = 0; i < frames.size; i++) {
        printf("%s", (char*) PNG_frame_vector_get(&frames, i)->type);
    }

    PNG_frame_vector_free(&frames);

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
