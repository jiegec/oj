// http://oj.tsinsen.com/D14258
#include <queue>
#include <stdio.h>

int n, m;
int map[512][512];
int vis[512][512];
int prevdir[512][512];
int step[512];

int dxy[][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
char name[] = "DLRU";

int x = 0, y = 0, bound, k = 0;
bool flag = false;

int idastar(int s) {
  int hv = (n - 1 - x) + (m - 1 - y);
  if (s + hv > bound)
    return s + hv;
  if (hv == 0) {
    flag = true;
    printf("%d\n", k);
    return s;
  }
  int nxt = 0x7FFFFF, tmp;
  vis[x][y] = 1;
  int orig_x = x, orig_y = y;
  for (int i = 0; i < 4; i++) {
    int new_x = x + dxy[i][0];
    int new_y = y + dxy[i][1];
    if (0 <= new_x && 0 <= new_y && new_x < n && new_y < m &&
        vis[new_x][new_y] == 0 && map[new_x][new_y] == 0) {
      k++;
      x = new_x;
      y = new_y;
      tmp = idastar(s + 1);
      x = orig_x;
      y = orig_y;
      k--;
      if (flag) {
        step[k] = i;
        return tmp;
      }
      if (nxt > tmp)
        nxt = tmp;
    }
  }
  vis[x][y] = 0;
  return nxt;
}

struct Node {
  int x;
  int y;
};

void bfs() {
  Node begin = {0, 0};
  std::queue<Node> que;
  que.push(begin);
  vis[0][0] = 1;

  while (!que.empty()) {
    Node cur = que.front();
    que.pop();

    if (cur.x == n - 1 && cur.y == m - 1) {
      int temp_x = cur.x;
      int temp_y = cur.y;
      while (temp_x != 0 || temp_y != 0) {
        int dir = prevdir[temp_x][temp_y];
        step[k++] = prevdir[temp_x][temp_y];
        temp_x -= dxy[dir][0];
        temp_y -= dxy[dir][1];
      }
      break;
    }

    for (int i = 0; i < 4; i++) {
      int new_x = cur.x + dxy[i][0];
      int new_y = cur.y + dxy[i][1];
      if (0 <= new_x && new_x < n && 0 <= new_y && new_y < m &&
          vis[new_x][new_y] == 0 && map[new_x][new_y] == 0) {
        Node next = {new_x, new_y};
        vis[new_x][new_y] = 1;
        prevdir[new_x][new_y] = i;
        que.push(next);
      }
    }
  }
}

int main() {
  char buffer[512];
  scanf("%d%d\n", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", buffer);
    for (int j = 0; j < m; j++) {
      map[i][j] = buffer[j] - '0';
      vis[i][j] = 0;
    }
  }
  // for (bound = (n - 1) + (m - 1); !flag; bound = idastar(0))
  //   ;
  // for (int i = 0; i < bound; i++) {
  //   putchar(name[step[i]]);
  // }
  // putchar('\n');
  bfs();
  printf("%d\n", k);
  for (int i = k - 1; i >= 0; i--) {
    putchar(name[step[i]]);
  }
  putchar('\n');
  return 0;
}
