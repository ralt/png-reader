#include <stdio.h>

/**
 * Documentation found here: http://www.libpng.org/pub/png/spec/1.2/PNG-CRCAppendix.html
 */

void make_crc_table(void);

unsigned long update_crc(unsigned long crc, unsigned char *buf, int len);

unsigned long crc(unsigned char *buf, int len);
