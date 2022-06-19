// https://codeforces.com/contest/1695/problem/C
#include <stdio.h>
#include <vector>
#include <bitset>

int grid[1024][1024];

int main() {
  int t;
  scanf("%d", &t);
  std::vector<std::bitset<2020> > dp;
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &grid[i][j]);
      }
    }

    const int SHIFT = 1000;
    dp.resize(m);
    for (int i = 0;i < n;i++) {
      for (int j = 0;j < m;j++) {
        std::bitset<2020> val(1);
        if (i == 0) {
          if (j == 0) {
            val <<= SHIFT + grid[i][j];
          } else {
            if (grid[i][j] == 1) {
              val = dp[j-1] << 1;
            } else {
              val = dp[j-1] >> 1;
            }
          }
        } else {
          if (j == 0) {
            val = dp[j];
          } else {
            val = dp[j-1] | dp[j];
          }
          if (grid[i][j] == 1) {
            val <<= 1;
          } else {
            val >>= 1;
          }
        }

        dp[j] = val;
      }
    }

    std::bitset<2020> val = dp[m-1];
    val >>= SHIFT;

    if (val[0]) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}