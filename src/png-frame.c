#include "png-frame.h"

size_t PNG_frame_length(struct PNG_frame *frame)
{
	return (size_t) ((uint32_t) frame->length[0] << 24 |
			 (uint32_t) frame->length[1] << 16 |
			 (uint32_t) frame->length[2] << 8 |
			 (uint32_t) frame->length[3]);
}

unsigned long PNG_frame_crc(struct PNG_frame *frame)
{
	return (unsigned long)((uint32_t) frame->crc[0] << 24 |
			       (uint32_t) frame->crc[1] << 16 |
			       (uint32_t) frame->crc[2] << 8 |
			       (uint32_t) frame->crc[3]);
}

bool PNG_frame_check_crc(struct PNG_frame *frame)
{
	unsigned char *buf = malloc(sizeof(unsigned char) * (PNG_frame_length(frame) +	//frame->data
							     (sizeof(uint8_t) * PNG_header_type_size)	// frame->type
				    ));
	if (buf == NULL) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	size_t buf_size = PNG_frame_length(frame) + PNG_header_type_size;

	for (size_t i = 0; i < buf_size; i++) {
		if (i < PNG_header_type_size) {
			buf[i] = frame->type[i];
		} else {
			buf[i] = frame->data[i - PNG_header_type_size];
		}
	}

	unsigned long crc_gen =
	    crc(buf, (PNG_frame_length(frame) + PNG_header_type_size));

	bool checked = (crc_gen == PNG_frame_crc(frame));

	free(buf);

	return checked;
}

void PNG_frame_free(struct PNG_frame *frame)
{
	free(frame->data);
	free(frame);
}
