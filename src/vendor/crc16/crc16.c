unsigned short crc16(char *ptr, int size) {
  int crc;
  crc = 0;
  while (--size >= 0) {
    crc = crc ^ (int)*ptr++ << 8;
    int i = 8;
    do {
      if (crc & 0x8000)
        crc = crc << 1 ^ 0x1021;
      else
        crc = crc << 1;
    } while (--i);
  }
  return crc;
}