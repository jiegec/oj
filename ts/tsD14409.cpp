// http://oj.tsinsen.com/D14409
#include <stdio.h>

int edge_from[10010];
int edge_to[10010];
int edge_weight[10010];
int edge_num = 1;
int adj[110][10010] = {{0}};
int adj_weight[110][10010] = {{0}};
int adj_num[110] = {0};
int link_matrix[110][10010] = {{0}};
int edge_list[3][10010] = {0};
int zhengxiangbiao_a[110] = {0};
int zhengxiangbiao_b[10010] = {0};
int zhengxiangbiao_z[10010] = {0};
int zhengxiangbiao_current = 1;
int n;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int weight;
      scanf("%d", &weight);
      if (weight) {
        edge_from[edge_num] = i;
        edge_to[edge_num] = j;
        edge_weight[edge_num] = weight;
        edge_num++;

        adj[i][adj_num[i]] = j;
        adj_weight[i][adj_num[i]] = weight;
        adj_num[i]++;
      }
    }
  }

  // guanlian
  for (int i = 1; i < edge_num; i++) {
    link_matrix[edge_from[i]][i] = 1;
    link_matrix[edge_to[i]][i] = -1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < edge_num; j++) {
      printf("%d ", link_matrix[i][j]);
    }
    printf("\n");
  }

  // bianliebiao
  for (int i = 1; i < edge_num; i++) {
    edge_list[0][i] = edge_from[i];
    edge_list[1][i] = edge_to[i];
    edge_list[2][i] = edge_weight[i];
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < edge_num; j++) {
      printf("%d ", edge_list[i][j]);
    }
    printf("\n");
  }

  // zhengxiangbiao
  for (int i = 1; i <= n; i++) {
    zhengxiangbiao_a[i] = zhengxiangbiao_current;
    for (int j = 0; j < adj_num[i]; j++) {
      zhengxiangbiao_b[zhengxiangbiao_current] = adj[i][j];
      zhengxiangbiao_z[zhengxiangbiao_current] = adj_weight[i][j];
      zhengxiangbiao_current++;
    }
  }
  zhengxiangbiao_a[n + 1] = zhengxiangbiao_current;

  for (int i = 1; i <= n + 1; i++) {
    printf("%d ", zhengxiangbiao_a[i]);
  }
  printf("\n");

  for (int i = 1; i < zhengxiangbiao_current; i++) {
    printf("%d ", zhengxiangbiao_b[i]);
  }
  printf("\n");

  for (int i = 1; i < zhengxiangbiao_current; i++) {
    printf("%d ", zhengxiangbiao_z[i]);
  }
  printf("\n");

  // linjiebiao
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < adj_num[i]; j++) {
      printf("%d %d ", adj_weight[i][j], adj[i][j]);
    }
    printf("\n");
  }
  return 0;
}
