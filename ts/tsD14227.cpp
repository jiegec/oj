#include <stdio.h>
#include <algorithm>

int dp[1024][1024];
int num[1024], sum[1024];

int main() {
  int n;
  scanf("%d", &n);
  sum[0] = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &num[i]);
    sum[i] = sum[i - 1] + num[i];
    dp[i][i] = 0;
  }

  for (int len = 2; len <= n; len++) {
    for (int begin = 1; begin <= n - len + 1; begin++) {
      int min_sub = 0x7FFFFFFF;
      for (int mid = 1;mid < len;mid++) {
        min_sub = std::min(min_sub, dp[begin][begin+mid-1]+dp[begin+mid][begin+len-1]);
      }
      min_sub += sum[begin+len-1] - sum[begin-1];
      dp[begin][begin+len-1] = min_sub;
    }
  }
  printf("%d\n",dp[1][n]);
  return 0;
}
