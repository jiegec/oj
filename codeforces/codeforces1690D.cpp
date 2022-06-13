// https://codeforces.com/contest1690/problem/D
#include <stdio.h>
#include <algorithm>

char str[204800];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d\n", &n, &k);
    fgets(str, 204800, stdin);
    int count = 0;
    for (int i = 0; i < k; i++) {
      count += str[i] == 'B';
    }
    int res = k - count;
    for (int i = k; i < n; i++) {
      count += str[i] == 'B';
      count -= str[i - k] == 'B';
      res = std::min(res, k - count);
    }
    printf("%d\n", res);
  }
  return 0;
}