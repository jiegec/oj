// http://oj.tsinsen.com/D14259
#include <stdio.h>
#include <queue>

int r, c;
char buffer[512];
int map[512][512];
int dxy[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int vis[512][512][4];

struct Node {
  int x;
  int y;
  int prevdir;
  int step;
};

void bfs() {
  std::queue<Node> que;
  if (map[0][1]) {
    int max_y1 = 1;
    while (map[0][max_y1] && max_y1 < c) {
      Node right = {0, max_y1, 3, 0};
      vis[0][max_y1][3] = 1;
      que.push(right);
      max_y1++;
    }
  }
  if (map[1][0]) {
    int max_x1 = 1;
    while (map[max_x1][0] && max_x1 < r) {
      Node down = {max_x1, 0, 1, 0};
      vis[max_x1][0][1] = 1;
      que.push(down);
      max_x1++;
    }
  }


  while(!que.empty()) {
    Node cur = que.front();
    que.pop();

    if (cur.x == r-1 && cur.y == c-1) {
      printf("%d\n", cur.step);
      return;
    }

    for (int i = 0;i < 4;i++) {
      if ((i^1) != cur.prevdir && i != cur.prevdir) {
        int new_x = cur.x+dxy[i][0];
        int new_y = cur.y+dxy[i][1];
        if (0 <= new_x && new_x < r && 0 <= new_y && new_y < c &&
            map[new_x][new_y]) {
          while (0 <= new_x && new_x < r && 0 <= new_y && new_y < c &&
                 map[new_x][new_y]) {
            if (vis[new_x][new_y][i] == 0) {
              vis[new_x][new_y][i] = 1;
              Node new_node = {new_x, new_y, i, cur.step+1};
              que.push(new_node);
            }
            new_x += dxy[i][0];
            new_y += dxy[i][1];
          }
        }
      }
    }
  }
}

int main() {
  scanf("%d%d\n",&r,&c);
  for(int i = 0;i < r;i++) {
    scanf("%s",buffer);
    for (int j = 0;j < c;j++) {
      map[i][j] = buffer[j] == '0'; // 1 for can walk
      vis[i][j][0] = vis[i][j][1] = vis[i][j][2] = vis[i][j][3] = 0;
    }
  }
  bfs();
}
