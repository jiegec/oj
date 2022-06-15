// http://oj.tsinsen.com/D13609
#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if ((i + j) * (j - i + 1) == 2 * n) {
        printf("%d %d\n", i, j);
      }
    }
  }
}
