#include <stdio.h>

int n, m, a, b, c;
int map[1024][1024];
int step[1024];
char name[] = "rgb";
// char vis[1024][1024][334];

bool dfs(int x, int y, int num_c, int depth) {
  if (x == n-1 && y == m-1) {
    return true;
  }
  int new_x, new_y, cur_b = x - 3 * num_c, cur_a = (y - cur_b) / 2;
  if (cur_a < a) {
    new_x = x;
    new_y = y + 2;
    if (new_x < n && new_y < m && map[new_x][new_y])
      if (dfs(new_x, new_y, num_c, depth+1)) {
        step[depth] = 0;
        return true;
      }
  }
  if (cur_b < b) {
    new_x = x+1;
    new_y = y+1;
    if (new_x < n && new_y < m && map[new_x][new_y])
      if (dfs(new_x, new_y, num_c, depth+1)) {
        step[depth] = 1;
        return true;
      }
  }
  if (num_c < c) {
    new_x = x + 3;
    new_y = y;
    if (new_x < n && new_y < m && map[new_x][new_y])
      if (dfs(new_x, new_y, num_c+1, depth+1)) {
        step[depth] = 2;
        return true;
      }
  }
  return false;
}

int main() {
  scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
  for (int i = 0;i < n;i++) {
    for (int j = 0;j < m;j++) {
      scanf("%d", &map[i][j]);
    }
  }
  if (dfs(0, 0, 0, 0)) {
    for (int i = 0;i < a+b+c;i++) {
      putchar(name[step[i]]);
    }
    putchar('\n');
  } else {
    puts("-1\n");
  }
}
