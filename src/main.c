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

	if (!PNG_file_check_critical_chunks(file)) {
		printf("Critical chunks not OK.\n");
		goto cleanup;
	}
	for (size_t i = 0; i < file->frames->size; i++) {
		struct PNG_frame frame = *PNG_frame_vector_get(file->frames, i);
		char type[] = { frame.type[0], frame.type[1], frame.type[2],
			frame.type[3]
		};
		printf("Frame type hex: 0x%02x 0x%02x 0x%02x 0x%02x\n",
		       frame.type[0], frame.type[1], frame.type[2],
		       frame.type[3]);
		printf("Frame type: %s\n", type);
		printf("Frame length: %zu\n", PNG_frame_length(&frame));

		bool crc = PNG_frame_check_crc(&frame);
		if (crc) {
			printf("CRC verified.\n");
		} else {
			printf("CRC invalid!\n");
		}

		bool check = true;
		char text_type[] = "tEXt";
		for (size_t i = 0; i < PNG_header_type_size; i++) {
			if (text_type[i] != (char)frame.type[i]) {
				check = false;
			}
		}

		if (check) {
			printf("Text data: ");
			for (size_t i = 0; i < PNG_frame_length(&frame); i++) {
				printf("%c", (char)frame.data[i]);
			}
			printf("\n");
		}
	}

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
