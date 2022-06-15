#include <stdio.h>
#include <string.h>

int main() {
  int action;
  char buffer[1024];
  scanf("%d%s", &action, buffer);
  int len = strlen(buffer);
  int i;
  char begin;
  int begin_pos;

  switch (action) {
  case 1:
    for (i = 0; i < len; i++) {
      if ('a' <= buffer[i] && buffer[i] <= 'z') {
        putchar(buffer[i] - 'a' + 'A');
      } else {
        putchar(buffer[i]);
      }
    }
    break;
  case 2:
    for (i = 0; i < len; i++) {
      if ('A' <= buffer[i] && buffer[i] <= 'Z') {
        putchar(buffer[i] - 'A' + 'a');
      } else {
        putchar(buffer[i]);
      }
    }
    break;
  case 3:
    for (i = len - 1; i >= 0; i--) {
      putchar(buffer[i]);
    }
    break;
  case 4:
    for (i = 0; i < len; i++) {
      if ('A' <= buffer[i] && buffer[i] <= 'Z') {
        putchar(buffer[i] - 'A' + 'a');
      } else {
        putchar(buffer[i] - 'a' + 'A');
      }
    }
    break;
  case 5:
    for (i = 0; i < len; i++) {
      if ('A' <= buffer[i] && buffer[i] <= 'Z') {
        buffer[i] = buffer[i] - 'A' + 'a';
      }
    }
    begin = buffer[0];
    begin_pos = 0;
    for (i = 1; i <= len; i++) {
      if (buffer[i] != begin + (i - begin_pos)) {

        putchar(begin);
        if (i - begin_pos >= 3) {
          putchar('-');
        }
        if (i - begin_pos >= 2) {
          putchar(begin + (i - begin_pos - 1));
        }

        begin = buffer[i];
        begin_pos = i;
      }
    }

    // putchar(begin);
    // if (i - begin_pos >= 3) {
    //   putchar('-');
    // }
    // if (i - begin_pos >= 2) {
    //   putchar(begin+(i-begin_pos-1));
    // }

    break;
  default:
    break;
  }

  return 0;
}
