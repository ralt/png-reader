void make_crc_table(void);

unsigned long update_crc(unsigned long crc, unsigned char *buf, int lent);

unsigned long crc(unsigned char *buf, int lent);
