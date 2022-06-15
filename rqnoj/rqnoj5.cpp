// http://www.rqnoj.cn/problem/5
#include <stdio.h>
#include <string.h>
int dp[345][345];
int max(int a, int b) { return a > b ? a : b; }
int main() {
  int n, numbers[234];
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &numbers[i]);
    numbers[i + n] = numbers[i];
  }
  for (int i = 0; i <= 300; i++) {
    for (int j = 0; j <= 300; j++) {
      dp[i][j] = 0;
    }
  }
  for (int length = 2; length <= n; length++) {
    for (int start = 1; start <= n * 2 - length + 1; start++) {
      int end = start + length;
      for (int i = start + 1; i <= end - 1; i++) {
        dp[start][end] =
            max(dp[start][end], dp[start][i] + dp[i][end] +
                                    numbers[start] * numbers[i] * numbers[end]);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans = max(ans, dp[i][i + n]);
  printf("%d\n", ans);
}
