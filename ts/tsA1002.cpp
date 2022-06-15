// http://oj.tsinsen.com/A1002
#include <stdio.h>
// From
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                        \
      (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                    \
      (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

// From Hacker's Delight, 2nd Edition Fig. 5-2
int pop(int x) {
  x = x - ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x0000003F;
}

int main() {
  for (unsigned int i = 0; i < 64; i++) {
    if (pop(i) & 1)
      printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(i));
  }
}
