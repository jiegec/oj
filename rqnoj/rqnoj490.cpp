// http://www.rqnoj.cn/problem/490
#include <stdio.h>
#include <string.h>
int n, stone[1000 * 2], max[1000 * 2][1000 * 2], min[1000 * 2][1000 * 2],
    sum[1000 * 2];
int min2(int a, int b) { return a > b ? b : a; }
int max2(int a, int b) { return a > b ? a : b; }
int main() {

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &stone[i]);
    stone[i + n] = stone[i];
  }
  sum[0] = 0;
  for (int i = 1; i <= n * 2; i++) {
    sum[i] = sum[i - 1] + stone[i];
  }
  for (int i = 1; i <= n * 2; i++) {
    for (int j = 1; j <= n * 2; j++) {
      min[i][j] = 99999999;
      max[i][j] = 0;
    }
  }

  for (int i = 1; i <= n * 2; i++) {
    min[i][i] = 0;
  }
  for (int length = 1; length <= n - 1; length++) {
    for (int start = 1; start <= n * 2 - length; start++) {
      int end = start + length;
      for (int i = start; i < end; i++) {
        min[start][end] =
            min2(min[start][end], min[start][i] + min[i + 1][end]);
        max[start][end] =
            max2(max[start][end], max[start][i] + max[i + 1][end]);
      }
      min[start][end] += sum[end] - sum[start - 1];
      max[start][end] += sum[end] - sum[start - 1];
    }
  }
  int maxans = -999999;
  int minans = 999999;
  for (int i = 1; i <= n; i++)
    maxans = max2(maxans, max[i][i + n - 1]);
  for (int i = 1; i <= n; i++)
    minans = min2(minans, min[i][i + n - 1]);
  printf("%d\n", minans);
  printf("%d\n", maxans);
}
