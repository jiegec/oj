#include <cstdio>
#include <cstring>

long bound;
bool flag;
long m, n;

long rot[][2] = {{0,  1},
                 {0,  -1},
                 {1,  0},
                 {-1, 0}};

inline long max(long a, long b) {
  return a>b?a:b;
}

inline long min(long a, long b) {
  return a<b?a:b;
}

struct D{
    long a[51][51];
    bool vis[51][51];
    long cur;
    long x, y;
    long step;
    long sum[51][51];
    long dp[51][51];
}s;

void rotate(long dir) {
  s.x += rot[dir][0];
  s.y += rot[dir][1];
}

#define inc(dir,rev) {s.cur+=s.a[s.x][s.y],s.vis[s.x][s.y]=true;dfs1();s.cur-=s.a[s.x][s.y],s.vis[s.x][s.y]=false,rotate(rev);}

long maxs = 0;

void dfs1(){
  for (long i = 0; i < 2; i++) {
    long dir = i << 1;
    rotate(dir);
    if (s.x == m-1 && s.y == n-1) {
      maxs = max(maxs, s.cur);
      rotate(dir^1);
      return ;
    } else if (s.x < 0 || s.y < 0 || s.x >= m || s.y >= n || s.vis[s.x][s.y] || s.x == s.y) {
      rotate(dir^1);
      continue;
    }
    inc(dir, dir^1);
  }
}

long DP[51][51][51];// DP[i][j][k]: 第i行 第1条路径从j下来，第2条路径从k下来
int main() {
  scanf("%ld%ld", &m, &n);
  flag=false;
  for (long i = 0; i < m; i++) {
    for (long j = 0; j < n; j++) {
      scanf("%ld", &s.a[i][j]);
      s.vis[i][j] = false;
      s.dp[i][j] = 0;
      s.sum[i][j] = s.a[i][j];
      if (j > 0) {
        s.sum[i][j] += s.sum[i][j-1];
      }
    }
  }
  if (m == n && 0) {
    for (long i = 0; i < m; i++) {
      for (long j = 0; j < n; j++) {
        if (i > j) {
          s.dp[i][j] = s.a[i][j];
          long tmp = s.dp[i - 1][j];
          if (j > 0) {
            tmp = max(tmp, s.dp[i][j-1]);
          }
          s.dp[i][j] += tmp;
        } else if (i < j) {
          s.dp[i][j] = s.a[i][j];
          long tmp = s.dp[i][j - 1];
          if (i > 0) {
            tmp = max(tmp, s.dp[i-1][j]);
          }
          s.dp[i][j] += tmp;
        }
      }
    }
    /*
    s.x = s.y = s.step = 0;
    s.y = 1;s.cur = s.a[0][1];
    long ans = 0;
    dfs1();
    ans = maxs;
    maxs = 0;
    s.x = 1,s.y = 0;s.cur = s.a[1][0];
    s.vis[m-1][n-1] = false;
    dfs1();
    prlongf("%ld\n",ans + maxs);
     */
    printf("%ld\n", s.dp[m - 1][n - 2] + s.dp[m - 2][n - 1]);
  } else {
    // row 2
    memset(DP, -1, sizeof(DP));
    for (long i = 1; i < n; i++) {
      DP[1][0][i] = s.sum[0][i];
    }
    for (long i = 2; i < m; i++) {
      for (long j = 0; j < n; j++) {
        for (long k = j + 1; k < n; k++) {
          for (long jj = 0; jj <= j; jj++) {
            for (long kk = jj + 1; kk <= k; kk++) {
              if (DP[i - 1][jj][kk] == -1)
                continue;
              long temp = DP[i - 1][jj][kk] + s.sum[i - 1][j] + s.sum[i - 1][k];
              if (jj > 0) {
                temp -= s.sum[i - 1][jj - 1];
              }
              if (kk > 0) {
                temp -= s.sum[i - 1][kk - 1];
              }
              DP[i][j][k] = max(DP[i][j][k], temp);
            }
          }
        }
      }
    }
    long ans = 0;
    for (long i = 0; i < n - 1; i++) {
      long temp = DP[m - 1][i][n - 1] + s.sum[m - 1][n - 1];
      if (i > 0) {
        temp -= s.sum[m - 1][i - 1];
      }
      ans = max(ans, temp);
    }
    printf("%ld\n", ans);
  }
}
