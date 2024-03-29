// http://acm.hdu.edu.cn/showproblem.php?pid=1506
#include <cstdio>

long long numbers[100010];
int l[100010], r[100010];
int main() {
  int n = 0, i;
  long long max, temp;
  while (scanf("%d", &n), n) {
    numbers[0] = numbers[n + 1] = -1;
    for (i = 1; i <= n; i++) {
      scanf("%lld", &numbers[i]);
      l[i] = r[i] = i;
    }
    for (i = 1; i <= n; i++) {
      while (numbers[l[i] - 1] >= numbers[i]) {
        l[i] = l[l[i] - 1];
      }
    }
    for (i = n; i >= 1; i--) {
      while (numbers[i] <= numbers[r[i] + 1]) {
        r[i] = r[r[i] + 1];
      }
    }
    max = 0;
    for (i = 1; i <= n; i++) {
      temp = numbers[i] * (r[i] - l[i] + 1);
      if (temp > max) {
        max = temp;
      }
    }
    printf("%lld\n", max);
  }
}
