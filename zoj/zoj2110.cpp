// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2110
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n, m, t;
char map[7][7];
int endx, endy;
int a[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
bool dfs(int x, int y, int depth) {
  if (x == endx && y == endy && depth == t) {
    return true;
  }
  if (depth == t) {
    return false;
  }
  if (abs(x - endx) + abs(y - endy) > (t - depth)) {
    return false;
  }
  if ((abs(x - endx) + abs(y - endy) - (t - depth)) % 2 == 1) {
    return false;
  }

  map[x][y] = 1;
  for (int i = 0; i < 4; i++) {
    int tempx = x + a[i][0];
    int tempy = y + a[i][1];
    if (tempx >= 1 && tempx <= n && tempy >= 1 && tempy <= m &&
        map[tempx][tempy] == 0) {
      if (dfs(tempx, tempy, depth + 1))
        return true;
    }
  }
  map[x][y] = 0;
  return false;
}
int main() {
  while (1) {
    cin >> n >> m >> t;
    if (n == 0)
      break;
    int x, y;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char c;
        cin >> c;
        map[i][j] = 0;
        if (c == 'S') {
          x = i;
          y = j;
        } else if (c == 'X') {
          map[i][j] = 1;
        } else if (c == 'D') {
          endx = i;
          endy = j;
        }
      }
    }
    bool ret = dfs(x, y, 0);
    if (ret)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}
