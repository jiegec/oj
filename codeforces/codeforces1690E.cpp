// https://codeforces.com/contest1690/problem/E
#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
      int num;
      scanf("%d", &num);
      a.push_back(num);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
      ans += a[i] / k;
      a[i] %= k;
    }
    std::sort(a.begin(), a.end());
    int left = 0, right = a.size() - 1;
    while (left < right) {
      if (a[left] + a[right] >= k) {
        left++;
        right--;
        ans++;
      } else {
        left++;
      }
    }

    printf("%lld\n", ans);
  }
  return 0;
}