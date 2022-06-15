// https://codeforces.com/contest/1692/problem/A
#include <stdio.h>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int res = 0;
    if (b > a) {
      res++;
    }
    if (c > a) {
      res++;
    }
    if (d > a) {
      res++;
    }
    printf("%d\n", res);
  }
  return 0;
}