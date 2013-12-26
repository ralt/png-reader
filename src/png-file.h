#include <stdio.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

extern size_t const PNG_headers_size;

#ifndef PNG_FILE
#define PNG_FILE

typedef struct
{
    uint8_t headers[PNG_headers_size];
    PNG_frame_vector frames;
} PNG_file;

#endif

bool PNG_file_check_critical_chunks(PNG_file *file);

bool PNG_file_check_headers(PNG_file *file);
