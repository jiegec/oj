// http://oj.tsinsen.com/D14536
#include <stdio.h>

int map[33][33];
int dist[33];
int vis[33];

int main() {
  int n, k;
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d", &n);
  for (int i = 1;i <= n;i++) {
    for (int j = 1;j <= n;j++) {
      scanf("%d", &map[i][j]);
    }
    dist[i] = -1;
    vis[i] = 0;
  }
  scanf("%d", &k);
  vis[k] = 1;
  dist[k] = 0;
  for (int i = 1;i <= n;i++) {
    if (map[k][i] != 0) {
      dist[i] = map[k][i];
    }
  }
  for (int i = 1;i <= n;i++) {
    int min_dist = 2147483647;
    int min_index = 0;
    for (int j = 1;j <= n;j++) {
      if (vis[j] == 0 && dist[j] != -1 && dist[j] < min_dist) {
        min_dist = dist[j];
        min_index = j;
      }
    }
    if (min_index == 0) {
      break;
    }
    vis[min_index] = 1;
    for (int k = 1;k <= n;k++) {
      if (map[min_index][k] != 0) {
        if (dist[k] == -1 || dist[k] > min_dist + map[min_index][k]) {
          dist[k] = min_dist + map[min_index][k];
        }
      }
    }
  }
  for (int i = 1;i <= n;i++) {
    if (i != k) {
      printf("%d ", dist[i]);
    }
  }
  printf("\n");
  return 0;
}
