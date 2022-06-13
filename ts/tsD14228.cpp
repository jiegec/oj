// http://oj.tsinsen.com/D14228
#include <stdio.h>
#include <algorithm>

int dp[1024], arr[1024];

int main() {
  int n;
  scanf("%d",&n);
  for (int i = 0;i < n;i++) {
    scanf("%d",&arr[i]);
  }
  dp[0] = 1;
  int ans = 1;
  for (int i = 1;i < n;i++) {
    dp[i] = 1;
    for (int j = 0;j < i;j++) {
      if (arr[j] < arr[i]) {
        dp[i] = std::max(dp[i], dp[j] + 1);
        ans = std::max(dp[i], ans);
      }
    }
  }
  printf("%d\n",ans);
  return 0;
}
