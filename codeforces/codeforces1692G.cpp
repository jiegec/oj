// https://codeforces.com/contest/1692/problem/G
#include <stdio.h>

long long a[300000];
bool small[300000] = {};
int prefix[300000] = {};

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      small[i] = a[i] < 2 * a[i + 1];
    }
    prefix[0] = small[0];
    for (int i = 1; i < n - 1; i++) {
      prefix[i] = prefix[i - 1] + small[i];
    }
    int res = 0;
    for (int i = k - 1; i <= n - 2; i++) {
      int sub = prefix[i];
      if (i >= k) {
        sub -= prefix[i - k];
      }
      if (sub == k) {
        res++;
      }
    }
    printf("%d\n", res);
  }
  return 0;
}