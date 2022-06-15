#include <stdio.h>
#include <string.h>

int main() {
  char buffer[1024];
  int len, i;
  while (scanf("%s", buffer) != EOF) {
    len = strlen(buffer);
    for (i = 0; i < len; i++) {
      if (buffer[i] != buffer[len - i - 1]) {
        printf("n\n");
        break;
      }
    }

    if (i == len) {
      printf("y\n");
    }
  }
  return 0;
}
