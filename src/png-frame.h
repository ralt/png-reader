#ifndef PNG_FRAME_STRUCTS
#define PNG_FRAME_STRUCTS

typedef struct
{
    uint8_t length[4];
    uint8_t type[4];
    uint8_t *data;
    uint8_t crc[4];
} PNG_frame;

typedef struct
{
    size_t size;
    int capacity;
    PNG_frame **frames;
} PNG_frame_vector;

#endif
