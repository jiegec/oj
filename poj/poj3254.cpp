// 状压DP
// http://blog.csdn.net/accry/article/details/6607703
#include <stdio.h>
#include <cstring>

#define MOD 100000000
int state[600],top = 0;
int dp[20][600];
int row[20];

int main() {
  int m, n;
  scanf("%d%d",&m,&n);

  memset(dp,0,sizeof(dp));
  for (int i = 0;i < (1 << n);i++) {
    if (i & (i<<1)) {
      continue;
    }
    state[top++] = i;
  }

  for (int i = 0;i < m;i++) {
    row[i] = 0;
    for (int j = 0;j < n;j++) {
      int temp;
      scanf("%d",&temp);
      if (temp == 0) {
        row[i] += 1 << (n - j - 1);
      }
    }
  }

  for (int i = 0;i < top;i++) {
    if (state[i] & row[0]) {
      dp[0][i] = 0;
    } else {
      dp[0][i] = 1;
    }
  }

  for (int i = 1;i < m;i++) {
    for (int j = 0;j < top;j++) {
      if (state[j] & row[i])
        continue;
      for (int k = 0;k < top;k++) {
        if (state[j] & state[k])
          continue;
        if (state[k] & row[i-1])
          continue;
        dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
      }
    }
  }
  int ans = 0;
  for (int i = 0;i < top;i++) {
    ans = (ans + dp[m-1][i]) % MOD;
  }
  printf("%d\n", ans);
}
