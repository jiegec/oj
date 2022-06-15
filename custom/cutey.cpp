#include <stdio.h>

inline int max(int a, int b) { return a > b ? a : b; }

int a[50010], dp[50010], reach[50010];

int main() {
  int n, p, q;
  scanf("%d%d%d", &n, &p, &q);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  dp[0] = a[0];
  reach[0] = 1;
  for (int i = 1; i < n; i++) {
    if (a[i] == -1) {
      dp[i] = 0;
      reach[i] = 0;
    } else {
      int acc = 0;
      if (i >= p) {
        acc = max(acc, dp[i - p]);
      }
      if (i >= q) {
        acc = max(acc, dp[i - q]);
      }
      if (acc != 0) {
        dp[i] = a[i] + acc;
        reach[i] = 1;
      } else {
        dp[i] = 0;
        reach[i] = 0;
      }
    }
  }
  if (reach[n - 1])
    printf("%d\n", dp[n - 1]);
  else
    printf("-1\n");
}
