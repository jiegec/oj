#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

double dist[15][15];
double dp[32769][15][15];

#define INF 10000000.0

int main() {
  int T;
  scanf("%d",&T);
  while(T--) {
    int n;
    scanf("%d",&n);
    int x[16],y[16];
    for(int i = 0;i < n;i++) {
      scanf("%d%d",&x[i],&y[i]);
    }
    for(int i = 0;i < n;i++) {
      dist[i][i] = 0;
      for(int j = i+1;j < n;j++) {
        dist[i][j] = dist[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      }
    }
    int m = (1 << n) - 1;
    for(int s = 3;s <= m;s++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          dp[s][j][k] = INF;
        }
      }
    }
    for(int s = 3;s <= m;s++) {
      for(int j = 0;j < n;j++) {
        for(int k = 0;k < n;k++) {
          if (j == k)
            continue;
          if (s & (1 << j) && s & (1 << k)) {
            if (s == ((1 << j) | (1 << k))) {
              dp[s][j][k] = dist[j][k];
            } else {
              for (int l = 0; l < n; l++) {
                if (s & (1 << l) && l != j && l != k)
                  dp[s][j][k] = min(dp[s][j][k], dp[s^(1<<k)][j][l] + dist[l][k]);
              }
            }
          }
        }
      }
    }
    double min_length = INF;
    for(int i = 0;i < n;i++) {
      for(int j = 0;j < n;j++) {
        if(i == j)
          continue;
        min_length = min(min_length, dp[m][i][j]);
      }
    }
    printf("%.2f\n",min_length);
  }
}
