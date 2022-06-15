// http://oj.tsinsen.com/A1001
#include <stdio.h>
// From
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                        \
      (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                    \
      (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

int main() {
  for (unsigned int i = 0; i < 64; i++) {
    printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(i));
  }
}
