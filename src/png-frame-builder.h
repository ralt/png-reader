#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "png-frame.h"
#include "png-frame-vector.h"

/**
 * Builds the frames from what's in the *content array.
 */
void PNG_build_frames(struct PNG_frame_vector *frames, uint8_t *content,
        size_t size, int cursor);

/**
 * Builds a single frame.
 */
void PNG_build_frame(uint8_t *content, struct PNG_frame *frame, int cursor);
