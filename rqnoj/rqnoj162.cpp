// http://www.rqnoj.cn/problem/162
#include <stdio.h>

int main() {
  long n, m, f[100000] = {0};
  scanf("%ld %ld", &n, &m);
  for (int i = 1; i <= m; i++)
    f[i] = -1000000;
  for (int i = 0; i < n; i++) {
    long w, q;
    scanf("%ld %ld", &w, &q);
    for (int j = w; j <= m; j++) {
      if (f[j] < f[j - w] + q) {
        f[j] = f[j - w] + q;
      }
    }
  }
  printf("%ld", f[m]);
}
