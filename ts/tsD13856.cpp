// http://oj.tsinsen.com/D13856
#include <stdio.h>

int buffer[100086];
int beg = 0, end = 0;
int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  int count = 0;
  for (int i = 0; i < n; i++) {
    int cur;
    scanf("%d", &cur);
    int j;
    for (j = beg; j < end; j++) {
      if (buffer[j] == cur)
        break;
    }
    if (j == end) {
      count++;
      buffer[end++] = cur;
      if (end - beg > m) {
        beg++;
      }
    }
  }
  printf("%d\n", count);
}
