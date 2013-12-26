#include "png-file.h"

typedef struct
{
    uint8_t headers[PNG_headers_size];
    PNG_frame_vector frames;
} PNG_file;
