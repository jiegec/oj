// https://codeforces.com/contest/1695/problem/A
#include <algorithm>
#include <stdio.h>

int matrix[50][50];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &matrix[i][j]);
      }
    }

    int max_i = 0, max_j = 0;
    int max_num = matrix[0][0];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (matrix[i][j] > max_num) {
          max_num = matrix[i][j];
          max_i = i;
          max_j = j;
        }
      }
    }

    int x_max = std::max(max_i + 1, n - max_i);
    int y_max = std::max(max_j + 1, m - max_j);
    printf("%d\n", x_max * y_max);
  }
  return 0;
}