// https://codeforces.com/contest/1692/problem/B
#include <stdio.h>
#include <algorithm>

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int nums[100];
    int n;
    scanf("%d", &n);
    for (int i = 0;i < n;i++) {
      scanf("%d", &nums[i]);
    }

    std::sort(&nums[0], &nums[n]);
    auto last = std::unique(&nums[0], &nums[n]);
    int count = last - &nums[0];

    int ans = count;
    if ((n - count) % 2) {
      ans --;
    }

    printf("%d\n", ans);
  }
	return 0;
}