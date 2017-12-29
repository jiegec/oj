#include <stdio.h>

int map[8][8];
int ans = 0;
int vis[8] = {0};
int num[8];

void dfs(int depth, int sum) {
  if (depth == 8) {
    if (sum > ans) {
      ans = sum;
    }
  } else {
    for (int i = 0;i < 8;i++) {
      if (!vis[i]) {
        int j;
        for (j = 0;j < depth;j++) {
          if (i - num[j] == depth - j || i - num[j] == j - depth) {
            break;
          }
        }
        if (j == depth) {
          vis[i] = 1;
          num[depth] = i;
          dfs(depth + 1, sum + map[depth][i]);
          vis[i] = 0;
        }
      }
    }
  }
}

int main() {
  for (int i = 0;i < 8;i++) {
    for (int j = 0;j < 8;j++) {
      scanf("%d",&map[i][j]);
    }
  }
  dfs(0, 0);
  printf("%d\n", ans);
}
