// https://codeforces.com/contest/1697/problem/A
#include <stdio.h>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    int a[110];
    int sum = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    if (sum > m) {
      printf("%d\n", sum - m);
    } else {
      printf("0\n");
    }
  }
  return 0;
}