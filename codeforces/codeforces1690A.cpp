// https://codeforces.com/contest1690/problem/A
#include <stdio.h>

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int n;
    scanf("%d", &n);
    if (n % 3 == 0) {
      printf("%d %d %d\n", n / 3, n / 3 + 1, n / 3 - 1);
    } else if (n % 3 == 1) {
      printf("%d %d %d\n", n / 3, n / 3 + 2, n / 3 - 1);
    } else {
      printf("%d %d %d\n", n / 3 + 1, n / 3 + 2, n / 3 - 1);
    }
  }
	return 0;
}