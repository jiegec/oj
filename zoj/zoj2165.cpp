// http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2165
#include <iostream>
#include <stdio.h>
using namespace std;

char ditu[101][101];
int h, w;
int ret = 0;
int a[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
void dfs(int x, int y) {
  ret++;
  ditu[x][y] = 0;
  for (int i = 0; i < 4; i++) {
    int tempx = x + a[i][0];
    int tempy = y + a[i][1];
    if (tempx >= 1 && tempx <= h && tempy >= 1 && tempy <= w &&
        ditu[tempx][tempy]) {
      dfs(tempx, tempy);
    }
  }
}

int main() {
  char c;
  while (1) {
    cin >> w >> h;
    if (h == 0)
      break;
    int x, y;
    ret = 0;
    for (int i = 1; i <= h; i++) {
      for (int j = 1; j <= w; j++) {
        cin >> c;
        if (c == '#')
          ditu[i][j] = 0;
        else if (c == '@') {
          ditu[i][j] = 1;
          x = i;
          y = j;
        } else {
          ditu[i][j] = 1;
        }
      }
    }
    dfs(x, y);
    cout << ret << endl;
  }
  return 0;
}
