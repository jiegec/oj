// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=10798
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct state {
  int x;
  int y;
  int up;
  int right;
  int down;
  int left;
  int max;
};

bool operator<(state a, state b) { return a.max > b.max; }

const int d[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
bool visit[50][50][12][12][12][12];

int main() {
  int n;
  char map[50][50] = {{'.'}};
  while (scanf("%d\n", &n) && n) {
    memset(visit, 0, sizeof(visit));
    state start;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%c", &map[i][j]);
        if (map[i][j] == 'P') {
          start.x = i;
          start.y = j;
        }
      }
      scanf("\n");
    }
    start.up = start.right = start.down = start.left = 0;
    start.max = 0;
    visit[start.x][start.y][0][0][0][0] = true;
    priority_queue<state> pq;
    pq.push(start);
    while (!pq.empty()) {
      state current = pq.top();
      pq.pop();
      if (current.x == 0 || current.y == 0 || current.x == n - 1 ||
          current.y == n - 1) {
        printf("At most %d rose(s) trampled.\n", current.max);
        break;
      }
      for (int i = 0; i < 4; i++) {
        state temp = current;
        temp.x += d[i][0];
        temp.y += d[i][1];
        if (map[temp.x][temp.y] == 'R')
          temp.up++;
        if (map[n - 1 - temp.y][temp.x] == 'R')
          temp.left++;
        if (map[n - 1 - temp.x][n - 1 - temp.y] == 'R')
          temp.down++;
        if (map[temp.y][n - 1 - temp.x] == 'R')
          temp.right++;
        temp.max = max(temp.up, temp.right);
        temp.max = max(temp.max, temp.down);
        temp.max = max(temp.max, temp.left);
        if (!visit[temp.x][temp.y][temp.up][temp.right][temp.down][temp.left]) {
          visit[temp.x][temp.y][temp.up][temp.right][temp.down][temp.left] =
              true;
          pq.push(temp);
        }
      }
    }
  }
}
