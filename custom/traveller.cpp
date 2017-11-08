#include <cstdio>
int bound;
bool flag;
int m,n;

int rot[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

inline int max(int a,int b){
  return a>b?a:b;
}

inline int min(int a,int b){
  return a<b?a:b;
}

struct D{
    int a[51][51];
    bool vis[51][51];
    int cur;
    int x, y;
    int step;
    int sum[51][51];
    int dp[51][51];
}s;

void rotate(int dir) {
  s.x += rot[dir][0];
  s.y += rot[dir][1];
}

#define inc(dir,rev) {s.cur+=s.a[s.x][s.y],s.vis[s.x][s.y]=true;dfs1();s.cur-=s.a[s.x][s.y],s.vis[s.x][s.y]=false,rotate(rev);}

int maxs = 0;

void dfs1(){
  for(int i=0;i<2;i++){
    int dir = i << 1;
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

int main() {
  scanf("%d%d",&m,&n);
  flag=false;
  for(int i = 0;i < m;i++) {
    for(int j = 0;j < n;j++) {
      scanf("%d",&s.a[i][j]);
      s.vis[i][j] = false;
      s.dp[i][j] = 0;
      s.sum[i][j] = s.a[i][j];
      if (j > 0) {
        s.sum[i][j] += s.sum[i][j-1];
      }
    }
  }
  if (m == n) {
    for (int i = 0;i < m;i++) {
      for (int j = 0;j < n;j++) {
        if (i > j) {
          s.dp[i][j] = s.a[i][j];
          int tmp = s.dp[i-1][j];
          if (j > 0) {
            tmp = max(tmp, s.dp[i][j-1]);
          }
          s.dp[i][j] += tmp;
        } else if (i < j) {
          s.dp[i][j] = s.a[i][j];
          int tmp = s.dp[i][j-1];
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
    int ans = 0;
    dfs1();
    ans = maxs;
    maxs = 0;
    s.x = 1,s.y = 0;s.cur = s.a[1][0];
    s.vis[m-1][n-1] = false;
    dfs1();
    printf("%d\n",ans + maxs);
     */
    printf("%d\n",s.dp[m-1][n-2]+s.dp[m-2][n-1]);
  }
}
