// https://codeforces.com/contest1697/problem/B
#include <stdio.h>
#include <algorithm>

int p[1000010];
long long sum[1000010];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0;i < n;i++) {
    scanf("%d", &p[i]);
  }
  std::sort(&p[0], &p[n]);
  sum[0] = p[0];
  for (int i = 1;i < n;i++) {
    sum[i] = sum[i-1] + p[i];
  }


  for (int i = 0;i < q;i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    int from = n - x;
    int to = from + y - 1;
    long long ans = sum[to];
    if (from > 0) {
      ans -= sum[from-1];
    }
    printf("%lld\n", ans);
  }
	return 0;
}