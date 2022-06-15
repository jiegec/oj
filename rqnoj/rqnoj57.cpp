// http://www.rqnoj.cn/problem/57
#include <stdio.h>

int main() {
  int n, rmb[111], rp[111], time[111], f[111][111] = {0}, t[111][111] = {0};
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &rmb[i], &rp[i], &time[i]);
  }
  int m, r, max = 0;
  scanf("%d %d", &m, &r);
  for (int i = 0; i < n; i++) {
    for (int j = m; j >= rmb[i]; j--) {
      for (int k = r; k >= rp[i]; k--) {
        if (f[j][k] < f[j - rmb[i]][k - rp[i]] + 1 ||
            (f[j][k] == f[j - rmb[i]][k - rp[i]] + 1 &&
             t[j][k] > t[j - rmb[i]][k - rp[i]] + time[i])) {
          f[j][k] = f[j - rmb[i]][k - rp[i]] + 1;
          t[j][k] = t[j - rmb[i]][k - rp[i]] + time[i];
        }
        if (f[j][k] > max) {
          max = f[j][k];
        }
      }
    }
  }
  int min = 1000000;
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= r; j++) {
      if (f[i][j] == max && t[i][j] < min) {
        min = t[i][j];
      }
    }
  }
  printf("%d", min);
}
