// http://poj.org/problem?id=1376
#include <queue>
#include <stdio.h>

using namespace std;

const int up = 0;
const int right = 1;
const int down = 2;
const int left = 3;

int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct state {
  int direct;
  int x;
  int y;
  int steps;
};

int main() {
  int m, n, f, fromx, fromy, tox, toy;
  char direction[10];
  while (scanf("%d%d", &m, &n) == 2 && m && n) {
    queue<state> que;
    int ans = -1;
    bool visit[64][64][4] = {{{false}}};
    bool map[64][64] = {{false}};
    bool go[64][64] = {{false}};
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &f);
        map[i][j] = f;
      }
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (!(map[i - 1][j - 1] || map[i][j - 1] || map[i - 1][j] ||
              map[i][j])) {
          go[i][j] = true;
        }
      }
    }
    scanf("%d%d%d%d %s", &fromx, &fromy, &tox, &toy, direction);
    state st;
    st.x = fromx;
    st.y = fromy;
    st.steps = 0;
    if (direction[0] == 'n') {
      st.direct = up;
    } else if (direction[0] == 'e') {
      st.direct = right;
    } else if (direction[0] == 's') {
      st.direct = down;
    } else if (direction[0] == 'w') {
      st.direct = left;
    }
    visit[st.x][st.y][st.direct] = true;
    if (fromx == tox && fromy == toy) {
      printf("0\n");
      continue;
    }
    if (!go[fromx][fromy] || !go[tox][toy]) {
      printf("-1\n");
      continue;
    }
    que.push(st);
    while (!que.empty()) {
      state current = que.front();
      que.pop();
      // printf("%d %d %d
      // %d\n",current.x,current.y,current.direct,current.steps);

      if (current.x == tox && current.y == toy) {
        ans = current.steps;
        break;
      }
      for (int i = 1; i <= 3; i++) {
        int xx = current.x + d[current.direct][0] * i;
        int yy = current.y + d[current.direct][1] * i;
        if (go[xx][yy] == 0)
          break;
        if (!visit[xx][yy][current.direct]) {
          state temp;
          temp.x = xx;
          temp.y = yy;
          temp.steps = current.steps + 1;
          temp.direct = current.direct;
          visit[temp.x][temp.y][temp.direct] = true;
          que.push(temp);
        }
      }

      int leftdir = (current.direct + 3) % 4;
      if (!visit[current.x][current.y][leftdir]) {
        state temp;
        temp.x = current.x;
        temp.y = current.y;
        temp.direct = leftdir;
        temp.steps = current.steps + 1;
        visit[temp.x][temp.y][temp.direct] = true;
        que.push(temp);
      }

      int rightdir = (current.direct + 1) % 4;
      if (!visit[current.x][current.y][rightdir]) {
        state temp;
        temp.x = current.x;
        temp.y = current.y;
        temp.direct = rightdir;
        temp.steps = current.steps + 1;
        visit[temp.x][temp.y][temp.direct] = true;
        que.push(temp);
      }
    }
    printf("%d\n", ans);
  }
}
