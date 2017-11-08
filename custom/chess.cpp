#include <stdio.h>

char is_prime[210] = {0};
int prime[50], count = 0;
int n, m;
int map[11][11];
bool vis[200] = {false};

inline int max(int a, int b) {
  return a > b ? a : b;
}

bool dfs(int x, int y) {
  if (x == n && y == 0) {
    for (int i = 0;i < n;i++) {
      for (int j = 0;j < m-1;j++) {
        printf("%d ",map[i][j]);
      }
      printf("%d\n",map[i][m-1]);
    }
    return true;
  }
  int nx = x,ny = y;
  ny++;
  if (ny == m) {
    ny = 0;
    nx ++;
  }
  int mm = 0;
  if (x == 0 && y == 0) {
    for (int i = 1;i <= n*m;i++) {
      map[0][0] = i;
      vis[i] = true;
      if (dfs(nx,ny)) {
        return true;
      }
      vis[i] = false;
    }
  } else {
    if (y > 0) {
      mm = map[x][y-1];
    }
    if (x > 0) {
      mm = max(mm, map[x-1][y]);
    }
    for (int i = 0;i < count;i++) {
      if (prime[i] <= mm || vis[prime[i]-mm]) {
        continue;
      }
      if (prime[i] - mm > m*n) {
        break;
      }
      if (y > 0 && is_prime[prime[i] - mm + map[x][y-1]] != 1)
        continue;
      if (x > 0 && is_prime[prime[i] - mm + map[x-1][y]] != 1)
        continue;
      map[x][y] = prime[i] - mm;
      vis[map[x][y]] = true;
      if (dfs(nx, ny)) {
        return true;
      }
      vis[map[x][y]] = false;
    }
  }
  return false;
}

int main() {
  scanf("%d%d",&n,&m);
  int nm = n*m*2;
  for (int i = 2;i <= nm;i++) {
    if(is_prime[i] == 0) {
      is_prime[i] = 1;
      prime[count++] = i;
      for (int j = i*i;j <= nm;j += i) {
        is_prime[j] = 2;
      }
    }
  }
  dfs(0,0);
}
