#include "main.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("png-reader needs at least one argument\n");
		exit(EXIT_FAILURE);
	}
	uint8_t *content = NULL;
	size_t fsize = read_file(argv[1], &content);

	struct PNG_file *file = malloc(sizeof(struct PNG_file));
	if (file == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	file->name = malloc(sizeof(char) * sizeof(argv[1]));
	if (file->name == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	file->name = argv[1];

	PNG_file_import(file, content, fsize);

	for (size_t i = 0; i < file->chunks->size; i++) {
		struct PNG_chunk chunk = *PNG_chunk_vector_get(file->chunks, i);
		char type[] = { chunk.type[0], chunk.type[1], chunk.type[2],
			chunk.type[3]
		};
		printf("Frame type hex: 0x%02x 0x%02x 0x%02x 0x%02x\n",
		       chunk.type[0], chunk.type[1], chunk.type[2],
		       chunk.type[3]);
		printf("Frame type: %s\n", type);
		printf("Frame length: %zu\n", PNG_chunk_length(&chunk));

		bool crc = PNG_chunk_check_crc(&chunk);
		if (crc) {
			printf("CRC verified.\n");
		} else {
			printf("CRC invalid!\n");
		}

		char text_type[] = "tEXt";
		char *chunk_type = malloc(sizeof(char) * PNG_header_type_size);
		if (chunk_type == NULL) {
			printf("%s\n", strerror(errno));
			goto cleanup;
		}

		PNG_chunk_type(&chunk, &chunk_type);
		if (strncmp(chunk_type, text_type, PNG_header_type_size) == 0) {
			printf("Text data: ");
			for (size_t i = 0; i < PNG_chunk_length(&chunk); i++) {
				printf("%c", (char)chunk.data[i]);
			}
			printf("\n");
		}
		free(chunk_type);
	}

	free(content);

	PNG_file_free(file);

	exit(EXIT_SUCCESS);

 cleanup:
	free(content);
	exit(EXIT_FAILURE);
}

size_t read_file(char *fname, uint8_t ** content)
{
	FILE *fp;
	fp = fopen(fname, "rb");
	if (fp == NULL)
		goto fatal_error;

	size_t fsize;
	if (fseek(fp, 0, SEEK_END) == -1)
		goto fatal_error;

	if ((fsize = ftell(fp)) == -1)
		goto fatal_error;

	if (fseek(fp, 0, SEEK_SET) == -1)
		goto fatal_error;

	if ((*content = (uint8_t *) malloc(fsize)) == NULL)
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
