// http://acm.hdu.edu.cn/showproblem.php?pid=2602
#include <stdio.h>

int main() {
  int t, n, v, w[1001], p[1001];
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    int f[1001] = {0};
    scanf("%d %d", &n, &v);
    for (int j = 0; j < n; j++) {
      scanf("%d", &p[j]);
    }
    for (int j = 0; j < n; j++) {
      scanf("%d", &w[j]);
    }
    for (int j = 0; j < n; j++) {
      for (int k = v; k >= w[j]; k--) {
        if (f[k] < f[k - w[j]] + p[j]) {
          f[k] = f[k - w[j]] + p[j];
        }
      }
    }
    printf("%d\n", f[v]);
  }
}
