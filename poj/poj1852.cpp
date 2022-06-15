// http://poj.org/problem?id=1852
#include <stdio.h>

int max2(int a, int b) { return a > b ? a : b; }

int min2(int a, int b) { return a < b ? a : b; }

int a[1000010];

int main() {
  int ncase;
  scanf("%d", &ncase);
  while (ncase--) {
    int i, l, n;
    scanf("%d%d", &l, &n);
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    int max = 0, min = 0;
    for (int i = 0; i < n; i++) {
      max = max2(max, max2(a[i], l - a[i]));
      min = max2(min, min2(a[i], l - a[i]));
    }
    printf("%d %d\n", min, max);
  }
}
