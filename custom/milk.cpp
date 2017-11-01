#include <stdio.h>

int m[300010];
int dp[300010] = {0};
int beg[300010] = {0};

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &m[i]);
  }
  dp[0] = m[0];
  beg[0] = 0;
  int maxdp = 0;
  for (int i = 1; i < n; i++) {
    if (m[i] == dp[i - 1]) {
      dp[i] = m[i] + 1;
      for (int j = beg[i - 1] - 1; j >= 0; j--) {
        if (m[j] == dp[i - 1] + beg[i - 1] - j) {
          dp[i] = m[j] + 1;
        }
      }
    } else {
      dp[i] = m[i];
      beg[i] = i;
      if (m[i] == m[i - 1]) {
        dp[i] = 2;
        beg[i] = i - 1;
      }
    }
    if (maxdp < dp[i])
      maxdp = dp[i];
  }
  printf("%d\n", maxdp);
}
